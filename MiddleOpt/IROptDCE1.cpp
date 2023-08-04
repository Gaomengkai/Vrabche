//
// Created by gaome on 2023/7/19.
//

#include "IROptDCE1.h"
#include "MiddleIRType.h"
#include <map>
#include <memory>
#include <queue>

using std::map;
using std::unordered_map;


namespace MiddleIR::Optimizer
{
void IROptDCE1::run()
{
    // 这个优化仅仅针对于一个函数只有一个基本块的情况
    // 以后再考虑多个基本块的情况
    // 也就是说，这个优化仅仅针对于没有跳转的情况
    hasChanged = false;
    for (auto& func : _irast->funcDefs) {
        if (func->getBasicBlocks().size() > 1) { continue; }
        IR_ASSERT(func->getBasicBlocks().size() == 1, "A Func Must Have At Least One BasicBlock");
        auto& bb     = func->getBasicBlocks()[0];
        using SPInst = shared_ptr<MiddleIRInst>;
        using SPVal  = shared_ptr<MiddleIRVal>;
        unordered_map<SPVal, std::list<SPInst>> instUsedBy;
        vector<SPVal>                           instLineNum;   // 行号，方便设置删除。
        unordered_map<SPVal, bool> isUseless;   // 从顶向下的分析（从return/call指令开始）
        unordered_map<SPVal, bool> isUseless2;   // 底向上的分析（从alloca []指令开始）
        for (auto& i : bb->_instructions) {
            for (auto& used : i->getUseList()) { instUsedBy[*used].emplace_back(i); }
            instLineNum.emplace_back(i);
            isUseless[i]  = true;
            isUseless2[i] = true;
        }
        // 无用变量分析（指通过alloca创建的变量）
        // （副作用逆向覆盖，没有被覆盖的变量就是无用变量）
        std::list<SPVal> sideEffect;
        sideEffect.emplace_back(bb->getTerminator());

        for (auto& i : bb->_instructions) {
            // call, 全局变量存储, 返回指令都有副作用（或修改值，或修改内存，或终结函数）
            if (i->isCallInst() || i->isReturnInst()) {
                sideEffect.emplace_back(i);
                continue;
            }
            if (i->isStoreInst()) {
                // 是否是全局变量存储？
                auto storeInst = std::dynamic_pointer_cast<StoreInst>(i);
                auto to        = storeInst->getTo();
                if (!to->getName().empty() && to->getName()[0] == '@') {
                    sideEffect.emplace_back(i);
                    continue;
                }
                // 是否是数组的存储？
                if (auto toInst = dynamic_pointer_cast<MiddleIRInst>(to)) {
                    if (toInst->isGetElementPtrInst()) {
                        sideEffect.emplace_back(i);
                        continue;
                    }
                }
                // 兼容后端，是否是函数参数的存储？
                if(storeInst->getFrom()->getName().substr(0, 5) == "%arg_") {
                    sideEffect.emplace_back(i);
                    continue;
                }
            }

        }
        bool changed = true;
        while (changed) {
            changed = false;
            // 如果alloca被覆盖，则覆盖所有的store xxx, alloca
            for (auto& i : bb->_instructions) {
                if (i->isStoreInst()) {
                    auto storeInst = std::dynamic_pointer_cast<StoreInst>(i);
                    auto to        = storeInst->getTo();
                    if (isUseless[to]) continue;
                    auto from = storeInst->getFrom();
                    if (auto fromInst = dynamic_pointer_cast<MiddleIRInst>(from)) {
                        sideEffect.emplace_back(i);
                    } else {
                        isUseless[i] = false;
                    }
                }
            }
            // 开始覆盖isUseless
            for (const auto& side : sideEffect) {
                // BFS
                if (auto sideInst = dynamic_pointer_cast<MiddleIRInst>(side)) {
                    std::queue<SPInst> q;
                    q.push(sideInst);
                    while (!q.empty()) {
                        auto cur = q.front();
                        q.pop();
                        if(isUseless[cur]) {
                            isUseless[cur] = false;
                            changed         = true;
                        }
                        for (auto& used : cur->getUseList()) {
                            if (isUseless[*used]) {
                                if (auto usedInst = dynamic_pointer_cast<MiddleIRInst>(*used)) {
                                    q.push(usedInst);
                                }
                            }
                        }
                    }
                }
            }
            sideEffect.clear();
        }

        // 遍历所有use，如果没有被覆盖，那么就是无用变量
        for (auto& inst : bb->_instructions) {
            if (isUseless[inst]) {
                inst->setDeleted(true);
                hasChanged = true;
                std::cout << "del ";
                if (auto store = dynamic_pointer_cast<StoreInst>(inst)) {
                    std::cout << "store " << store->getFrom()->getName() << "->"
                              << store->getTo()->getName() << std::endl;
                } else
                    std::cout << inst->getName() << std::endl;
            }
        }
        // 真删除
        bb->_instructions.remove_if([](const SPInst& inst) { return inst->isDeleted(); });
        // 结果：
        std::cout << bb->_instructions.size() << std::endl;
    }
    LOGW("DCE1 Done");
}
}   // namespace MiddleIR::Optimizer