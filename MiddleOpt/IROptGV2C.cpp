//
// Created by gaome on 2023/8/6.
//

#include "IROptGV2C.h"
#include <unordered_set>

using std::unordered_map;
using std::unordered_set;

namespace MiddleIR::Optimizer
{
IROptGV2C::IROptGV2C(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptGV2C::run()
{
    // 全局变量，没被改过的直接替换成常量
    unordered_set<shared_ptr<R5IRValConst>> globalVars;
    for (auto& gv : _irast->globalVars) {
        if (gv->getType()->isArray()) continue;
        globalVars.insert(std::static_pointer_cast<R5IRValConst>(gv));
    }
    hasChanged = false;
    // one pass.
    for (auto& f : _irast->funcDefs) {
        for (auto& b : f->getBasicBlocks()) {
            for (auto& i : b->_instructions) {
                if (auto storeInst = dynamic_pointer_cast<StoreInst>(i)) {
                    if (auto p = DPC(R5IRValConst, storeInst->getTo())) {
                        if (globalVars.find(p) != globalVars.end()) { globalVars.erase(p); }
                    }
                }
            }
        }
    }
    // 新建一些常量
    unordered_map<shared_ptr<R5IRValConst>, shared_ptr<R5IRValConst>> globalConsts;
    for (auto& gv : globalVars) {
        if (auto iC = DPC(R5IRValConstInt, gv)) {
            globalConsts[gv] = (make_shared<R5IRValConstInt>(iC->getValue()));
        } else if (auto fC = DPC(R5IRValConstFloat, gv)) {
            globalConsts[gv] = (make_shared<R5IRValConstFloat>(fC->getValue()));
        } else if (auto bC = DPC(R5IRValConstI1, gv)) {
            globalConsts[gv] = (make_shared<R5IRValConstI1>(bC->getValue()));
        }
    }

    // replace map
    unordered_map<shared_ptr<LoadInst>, shared_ptr<R5IRValConst>> replaceMap;
    for (auto& f : _irast->funcDefs) {
        for (auto& b : f->getBasicBlocks()) {
            for (auto& i : b->_instructions) {
                if (auto loadInst = dynamic_pointer_cast<LoadInst>(i)) {
                    auto from = DPC(R5IRValConst, loadInst->getFrom());
                    if (from == nullptr) continue;
                    if (globalConsts.find(from) != globalConsts.end()) {
                        replaceMap[loadInst] = globalConsts[from];
                    }
                }
            }
        }
    }

    // true replace
    for (auto& f : _irast->funcDefs) {
        for (auto& b : f->getBasicBlocks()) {
            for (auto& i : b->_instructions) {
                for (auto& u : i->getUseList()) {
                    if (auto p = DPC(LoadInst, *u)) {
                        if (replaceMap.find(p) != replaceMap.end()) {
                            i->tryReplaceUse(*u, replaceMap[p]);
                            hasChanged = true;
                        }
                    }
                }
            }
        }
    }
}
}   // namespace MiddleIR::Optimizer