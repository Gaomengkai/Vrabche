//
// Created by gaome on 2023/8/5.
//

#include "IROptDCE2.h"
#include "MiddleIRType.h"
#include <map>
#include <memory>
#include <queue>

using std::map;
using std::unordered_map;


namespace MiddleIR::Optimizer
{
IROptDCE2::IROptDCE2(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptDCE2::run()
{
    // 用于删除每个基本块中不可达的代码（非内存型）
    // 比如v5 = addi v3, 1
    // 后续没有使用v5的话，就可以删除这条语句
    hasChanged = false;   // 如果发生改动，hasChanged置为true
    //若只有一个基本块，会在DCE1中就干掉，所以这里不用考虑
    for (auto& func : _irast->funcDefs) {
        if (func->getBasicBlocks().size() == 1) { continue; }
        IR_ASSERT(func->getBasicBlocks().size() > 1, "A Func Must Have At Least One BasicBlock");
        using SPInst = shared_ptr<MiddleIRInst>;
        using SPVal  = shared_ptr<MiddleIRVal>;
        unordered_map<SPVal, std::list<SPInst>> instUsedBy;//记录每个变量被哪些指令使用
        unordered_map<SPVal, bool> isUseless;   // 记录每个指令是否无用
        //先遍历所有基本块，记录每个变量被哪些指令使用，并将所有指令标记为无用
        // 同时保留所有有副作用的指令，包括call, 全局变量存储, 数组元素存储 , 和所有的terminator

        std::list<SPVal> sideEffect;
        for (auto& bb : func->getBasicBlocks()) {
            sideEffect.emplace_back(bb->getTerminator());
            for (auto& i : bb->_instructions) {
                for (auto& used : i->getUseList()) { instUsedBy[*used].emplace_back(i); }
                isUseless[i] = true;

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
                    if (storeInst->getFrom()->getName().substr(0, 5) == "%arg_") {
                        sideEffect.emplace_back(i);
                        continue;
                    }
                }
            }
        }

        bool change = true;
        while (change) {
            change = false;
            //向sideEffect中添加所有向有用的指令赋值的指令
            for (auto& bb : func->getBasicBlocks()) {
                for (auto& inst : bb->_instructions) {
                    if (inst->isStoreInst()) {
                        auto storeInst = std::dynamic_pointer_cast<StoreInst>(inst);
                        auto to = storeInst->getTo();
                        if (isUseless[to]) continue;
                        auto from = storeInst->getFrom();
                        if (auto fromInst = dynamic_pointer_cast<MiddleIRInst>(from)) {
                            sideEffect.emplace_back(inst);
                        } else {
                            isUseless[inst] = false;
                        }
                    }
                }
            }

            // 从所有有副作用的指令开始，向前遍历，将所有相关的指令标记为有用
            for (auto &i :sideEffect) {
                std::queue<SPInst> usefulInst;
                if (auto sideVal = std::dynamic_pointer_cast<MiddleIRInst>(i)) {
//                    if (!isUseless[sideVal]) continue;
                    isUseless[sideVal] = false;
                    usefulInst.push(sideVal);
                    while (!usefulInst.empty()) {
                        auto sideInst = usefulInst.front();
//                        if (!sideInst->getName().empty()) LOGW("正常的" + sideInst->getName());
//
//                        else {
//                            switch (sideInst->getInstType()) {
//                            case 2:
//                                LOGW("br");
//                                break;
//                            case 1:
//                                LOGW("ret");
//                                break;
//                            case 8:
//                                LOGW("store");
//                                break;
//                            case 12:
//                                LOGW("call");
//                                break;
//                            }
//                        }
                        usefulInst.pop();
                        for (auto &used : sideInst->getUseList()) {
                            if (auto usedInst = std::dynamic_pointer_cast<MiddleIRInst>(*used)) {
                                if (isUseless[usedInst]) {
                                    change = true;
                                    usefulInst.push(usedInst);
                                    isUseless[usedInst] = false;
                                }
                            }
                        }
                    }
                }
            }
            sideEffect.clear();
        }

        // 遍历所有use，如果没有被覆盖，那么就是无用变量
        for (auto& bb :func->getBasicBlocks()) {
            for (auto& inst : bb->_instructions) {
                if (isUseless[inst]) {
                    inst->setDeleted(true);
                    hasChanged = true;
                    //                    std::cout << "del ";
                    //                    if (auto store = dynamic_pointer_cast<StoreInst>(inst)) {
                    //                        std::cout << "store " << store->getFrom()->getName()
                    //                        << "->"
                    //                                  << store->getTo()->getName() << std::endl;
                    //                    } else
                    //                        std::cout << inst->getName() << std::endl;
                }
            }
            // 真删除
            bb->_instructions.remove_if([](const SPInst& inst) { return inst->isDeleted(); });
            // 结果：
            //            std::cout << bb->_instructions.size() << std::endl;
        }





    }


}
}   // namespace MiddleIR::Optimizer
