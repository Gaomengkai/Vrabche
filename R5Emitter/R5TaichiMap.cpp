//
// Created by Merky on 2023/7/25.
//

#include "R5TaichiMap.h"
#include <iostream>
namespace R5Emitter
{

MemoryBlock::MemoryBlock(int64_t addr, int64_t sz)
    : address(addr)
    , size(sz)
    , allocated(false)
{
}

int64_t R5TaichiMap::allocateImpl(const std::string& variableName, int64_t size)
{
    // 4字节对齐
    int64_t alignedSize = (size + 3) & (~3);
    // 8字节align
    bool eightAlign = size % 8 == 0;

    // 查询已有的变量，确保不会重复分配
    if (allocations.find(variableName) != allocations.end()) {
        std::cout << "Error: Variable '" << variableName << "' has already been allocated.\n";
        // LOGE("Variable '" + variableName + "' has already been allocated.");
        return -1;   // 返回负数表示分配失败
    }

    // 在内存块链表中找到第一个满足大小的空闲内存块
    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if (!(*it)->allocated && (*it)->size >= alignedSize) {
            // 未分配不代表可以分配，还要看对齐情况
            // 如果这个内存块大小合适，且对齐，那么就可以分配
            if (eightAlign && (*it)->address % 8 != 0) {
                auto alignedAddr = (*it)->address + 8 - (*it)->address % 8;
                if ((*it)->size >= alignedSize + alignedAddr - (*it)->address) {
                    // 分割前边的空余部分，分配后边的对齐部分，分割后面的空余部分
                    auto newBlock       = new MemoryBlock(alignedAddr, alignedSize);
                    newBlock->allocated = true;
                    auto prevBlock = new MemoryBlock((*it)->address, alignedAddr - (*it)->address);
                    auto nextBlock = new MemoryBlock(
                        alignedAddr + alignedSize, (*it)->size - alignedAddr + (*it)->address
                    );
                    // 使用以上三个块来替换当前块
                    memory.insert(it, prevBlock);
                    // 删除当前块，并且更新it
                    it = memory.erase(it);
                    // 插入新块
                    it                        = memory.insert(it, newBlock);
                    allocations[variableName] = (*it);
                    if (nextBlock->size >= 0) {
                        // 如果后面的块大小大于0，那么插入后面的块
                        memory.insert(it, nextBlock);
                    } else {
                        delete nextBlock;
                    }
                    return alignedAddr;
                }
            } else {
                auto newBlock       = new MemoryBlock((*it)->address, alignedSize);
                newBlock->allocated = true;
                auto nextBlock =
                    new MemoryBlock((*it)->address + alignedSize, (*it)->size - alignedSize);
                memory.insert(it, newBlock);
                it = memory.erase(it);
                it--;
                allocations[variableName] = (*it);
                if (nextBlock->size >= 0) {
                    // 如果后面的块大小大于0，那么插入后面的块
                    memory.insert(std::next(it), nextBlock);
                } else
                    delete nextBlock;
                return newBlock->address;
            }
        }
    }

    // 链表中没有满足大小的空闲内存块，那么就新建一个
    // 注意对齐。
    auto lastAddr = memory.empty() ? 0 : memory.back()->address + memory.back()->size;
    // 如果对齐，但是地址不对齐，那么就对齐
    if (eightAlign && lastAddr % 8 != 0) {
        // 加一个块，大小为8-addr%8
        auto newBlock = new MemoryBlock(lastAddr, 8 - lastAddr % 8);
        memory.push_back(newBlock);
        lastAddr += 8 - lastAddr % 8;
    }
    // 加一个块，大小为alignedSize
    auto newBlock = new MemoryBlock(lastAddr, alignedSize);
    memory.push_back(newBlock);
    memory.back()->allocated  = true;
    allocations[variableName] = memory.back();
    return lastAddr;
}

int64_t R5TaichiMap::allocate(const std::string& variableName, int64_t size)
{
    auto x = allocateImpl(variableName, size);
     if (x < 0) return x;
    allocatedSize[variableName] = size;
    maxSize = std::max(maxSize, getSize());
    return invert(x, size);
}

void R5TaichiMap::release(const std::string& variableName)
{
    auto it = allocations.find(variableName);
    if (it != allocations.end()) {
        it->second->allocated = false;
        allocations.erase(it);
        allocatedSize.erase(variableName);
    } else {
        std::cout << "Error: Variable '" << variableName << "' has not been allocated.\n";
        // LOGE("Variable '" + variableName + "' has not been allocated.");
    }
    // 重新整理内存块链表
    for (auto iterator = memory.begin(); iterator != memory.end(); ++iterator) {
        if (!((*iterator)->allocated)) {
            // 如果当前块未分配，那么就看看后面的块是否未分配
            auto nextIt = iterator;
            for (++nextIt; nextIt != memory.end(); ++nextIt) {
                if (!(*nextIt)->allocated) {
                    // 如果后面的块也未分配，那么就合并
                    (*iterator)->size += (*nextIt)->size;
                    delete (*nextIt);
                    nextIt = memory.erase(nextIt);
                    --nextIt;
                } else {
                    // 如果后面的块已经分配了，那么就不用再看了
                    break;
                }
            }
        }
    }
    // 删除最后的空闲块
    while (!memory.empty() && !memory.back()->allocated) {
        delete memory.back();
        memory.pop_back();
    }
}

int64_t R5TaichiMap::query(const std::string& variableName)
{
    auto it = allocations.find(variableName);
    if (it != allocations.end()) {
        return invert(it->second->address, allocatedSize.at(variableName));
    } else
        return -1;
}

int64_t R5TaichiMap::getSize() const
{
    // 返回一个8字节对齐的大小
    return ((memory.empty() ? 0 : (memory.back()->address + memory.back()->size)) + 7) & (~7);
}
R5TaichiMap::~R5TaichiMap()
{
    for (auto& it : memory) { delete it; }
}
R5TaichiMap::R5TaichiMap()
    : inverted(false)
    , preserveSize(0)
{
}
R5TaichiMap::R5TaichiMap(bool inverted)
    : inverted(inverted)
    , preserveSize(16)
{
}
[[maybe_unused]] R5TaichiMap::R5TaichiMap(int64_t preserveSize_)
    : preserveSize(preserveSize_)
    , inverted(true)
{
}
int64_t R5TaichiMap::invert(int64_t offset, int64_t size) const
{
    if (inverted) {
        return -preserveSize - offset - size;
    } else {
        return offset;
    }
}
int64_t R5TaichiMap::getMaxSize() const
{
    return std::max(maxSize, getSize());
}


}   // namespace R5Emitter