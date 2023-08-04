//
// Created by gaome on 2023/7/19.
//

#include "IROptRLE.h"
#include "IROptCF.h"
namespace MiddleIR::Optimizer
{
template<typename T>
using SP = shared_ptr<T>;
void IROptRLE::run()
{
    hasChanged = false;
    for (auto& func : _irast->funcDefs) {
        for (auto& bb : func->getBasicBlocks()) {
            std::unordered_map<SP<AllocaInst>, SP<MiddleIRVal>>            map1;
            std::unordered_map<SP<AllocaInst>, std::list<SP<MiddleIRVal>>> map2;
            std::unordered_map<SP<MiddleIRVal>, SP<MiddleIRVal>>           map3;
            for (auto& i : bb->_instructions) {
                if (auto loadInst = DPC(LoadInst, i)) {
                    auto from = loadInst->getFrom();
                    if (auto fromAlloca = DPC(AllocaInst, from)) {
                        if (auto it1 = map1.find(fromAlloca); it1 != map1.end()) {
                            map2[fromAlloca].push_back(loadInst);
                            map3[loadInst] = it1->second;
                            i->setDeleted();
                        } else {
                            map1[fromAlloca] = loadInst;
                        }
                    }
                } else {
                    // replace
                    for (auto& u : i->getUseList()) {
                        if (auto it3 = map3.find(*u); it3 != map3.end()) {
                            i->tryReplaceUse(*u, it3->second);
                        }
                    }
                    if (auto storeInst = DPC(StoreInst, i)) {
                        auto from = storeInst->getFrom();
                        if (from->getName().size() > 5 && from->getName().substr(0, 5) == "%arg_") {
                            continue;
                        }
                        auto to = storeInst->getTo();
                        if (auto toAlloca = DPC(AllocaInst, to)) {
                            if (auto it1 = map1.find(toAlloca); it1 != map1.end()) {
                                for (const auto& k1 : map2[toAlloca]) { map3.erase(k1); }
                                map2.erase(toAlloca);
                            }
                            map1[toAlloca] = from;
                        }
                    }
                }
            }
            // handle the terminator inst(ret...)
            for (auto& u : bb->getTerminator()->getUseList()) {
                if (auto it3 = map3.find(*u); it3 != map3.end()) {
                    bb->getTerminator()->tryReplaceUse(*u, it3->second);
                }
            }
            // delete
            for (auto it = bb->_instructions.begin(); it != bb->_instructions.end();) {
                if ((*it)->isDeleted()) {
                    hasChanged = true;
                    it         = bb->_instructions.erase(it);
                } else {
                    ++it;
                }
            }
            // CF
            hasChanged |= IROptCF::ConstFold(bb);
            // end
        }
    }
    LOGW("RLE Done");
}

}   // namespace MiddleIR::Optimizer