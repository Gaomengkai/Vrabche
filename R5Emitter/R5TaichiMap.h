//
// Created by gaome on 2023/7/25.
//

#ifndef IRBACKENDR5_R5TAICHIMAP_H
#define IRBACKENDR5_R5TAICHIMAP_H
#include "R5Def.h"
#include <list>
#include <unordered_map>
namespace R5Emitter
{


struct MemoryBlock {
    int64_t address;
    int64_t size;
    bool    allocated;

    MemoryBlock(int64_t addr, int64_t sz);
};


// 太极图
// 用于记录alloca和spill中相对于sp的正偏移。
// 也需要对已经释放的内存进行回收。
class R5TaichiMap
{
private:
    std::list<MemoryBlock*>                       memory;        // 内存块链表
    std::unordered_map<std::string, MemoryBlock*> allocations;   // 变量名到内存块的映射
    bool                                inverted;   // 是否反转（从-16开始向下分配）
    int64_t                             preserveSize;    // 保留的内存大小(保存s0&ra)
    int64_t                             maxSize=0;         // 最大内存大小
    std::unordered_map<string, int64_t> allocatedSize;   // 变量名已经分配的空间大小

private:
    int64_t invert(int64_t offset, int64_t size) const;
    int64_t allocateImpl(const std::string& variableName, int64_t size);

public:
    explicit R5TaichiMap();
    explicit R5TaichiMap(bool inverted);
    [[maybe_unused]] explicit R5TaichiMap(int64_t preserveSize_);
    // 分配新的内存块，并返回变量的地址
    int64_t allocate(const std::string& variableName, int64_t size);

    // 释放内存块
    void release(const std::string& variableName);

    // 查询变量地址（-1为不合法地址）
    int64_t query(const std::string& variableName);

    // 获取内存大小
    int64_t getSize() const;

    int64_t getMaxSize() const;

    ~R5TaichiMap();
};




}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5TAICHIMAP_H
