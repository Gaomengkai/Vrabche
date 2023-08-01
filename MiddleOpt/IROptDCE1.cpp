//
// Created by gaome on 2023/7/19.
//

#include "IROptDCE1.h"
#include <map>
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
    for (auto& func : _irast->funcDefs) {
        if (func->getBasicBlocks().size() > 1) { continue; }
        IR_ASSERT(func->getBasicBlocks().size() == 1, "A Func Must Have At Least One BasicBlock");
        auto& bb     = func->getBasicBlocks()[0];
        using SPInst = shared_ptr<MiddleIRInst>;
        using SPVal  = shared_ptr<MiddleIRVal>;
        unordered_map<SPVal, std::list<SPInst>> instUsedBy;
        vector<SPVal>                           instLineNum;   // 行号，方便设置删除。
        unordered_map<SPVal, bool>              isUseless;
        for (auto& i : bb->_instructions) {
            for (auto& used : i->getUseList()) { instUsedBy[*used].emplace_back(i); }
            instLineNum.emplace_back(i);
            isUseless[i] = true;
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
            }
        }

        // 开始覆盖isUseless
        for (const auto& side : sideEffect) {
            isUseless[side] = false;
            // BFS
            if (auto sideInst = dynamic_pointer_cast<MiddleIRInst>(side)) {
                std::queue<SPInst> q;
                q.push(sideInst);
                while (!q.empty()) {
                    auto cur = q.front();
                    q.pop();
                    for (auto& used : cur->getUseList()) {
                        if (isUseless[*used]) {
                            isUseless[*used] = false;
                            if (auto usedInst = dynamic_pointer_cast<MiddleIRInst>(*used)) {
                                q.push(usedInst);
                            }
                        }
                    }
                }
            }
        }

        // 如果alloca被覆盖，则覆盖所有的store xxx, alloca
        for (auto& i : bb->_instructions) {
            if (i->isStoreInst()) {
                auto storeInst = std::dynamic_pointer_cast<StoreInst>(i);
                auto to        = storeInst->getTo();
                if (isUseless[to]) continue;
                isUseless[i] = false;
                auto from = storeInst->getFrom();
                isUseless[from] = false;
                // BFS
                if (auto fromInst = dynamic_pointer_cast<MiddleIRInst>(from)) {
                    std::queue<SPInst> q;
                    q.push(fromInst);
                    while (!q.empty()) {
                        auto cur = q.front();
                        q.pop();
                        for (auto& used : cur->getUseList()) {
                            if (isUseless[*used]) {
                                isUseless[*used] = false;
                                if (auto usedInst = dynamic_pointer_cast<MiddleIRInst>(*used)) {
                                    q.push(usedInst);
                                }
                            }
                        }
                    }
                }
            }
        }

        // 遍历所有use，如果没有被覆盖，那么就是无用变量
        for (auto& inst : bb->_instructions) {
            if (isUseless[inst]) { inst->setDeleted(true); }
        }
        // 真删除
        bb->_instructions.remove_if([](const SPInst& inst) { return inst->isDeleted(); });
        // 结果：
        std::cout << bb->_instructions.size() << std::endl;
    }
}
}   // namespace MiddleIR::Optimizer