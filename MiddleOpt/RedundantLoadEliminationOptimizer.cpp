//
// Created by gaome on 2023/7/19.
//

#include "RedundantLoadEliminationOptimizer.h"

namespace MiddleIR::Optimizer
{
void RedundantLoadEliminationOptimizer::run()
{
    decltype(g_log_level) old_level = g_log_level;
    g_log_level                      = LOG_LEVEL::LOG_LEVEL_DEBUG;
    for (auto& func : _irast->funcDefs) {
        LOGD("Enter Function "<<func->getName());
        for (auto& bb : func->getBasicBlocks()) {
            LOGD("Enter BasicBlock "<<bb->getName());
            // round 1: find first load from
            std::set<shared_ptr<MiddleIRVal>> loadFrom;
            std::unordered_map<shared_ptr<MiddleIRVal>, shared_ptr<MiddleIRInst>>
                fromFirstRepWithSecond;
            for (auto& inst : bb->_instructions) {
                if (inst->isLoadInst()) {
                    auto loadInst = dynamic_pointer_cast<LoadInst>(inst);
                    // not in loadFrom, means this is the first load after a store
                    if (loadFrom.find(loadInst->getFrom()) == loadFrom.end()) {
                        loadFrom.insert(loadInst->getFrom());
                        fromFirstRepWithSecond[loadInst->getFrom()] = loadInst;
                    }
                    // del this loadInst
                    else
                        inst->setDeleted(true);
                } else {
                    if (inst->isStoreInst()) {
                        auto storeInst = dynamic_pointer_cast<StoreInst>(inst);
                        if (loadFrom.find(storeInst->getTo()) != loadFrom.end()) {
                            loadFrom.erase(storeInst->getTo());
                        }
                    }
                    for (const auto& u : inst->getUseList()) {
                        // u must be a LOAD inst then we can optimize
                        auto loadInst = dynamic_pointer_cast<LoadInst>(*u);
                        if (!loadInst) continue;
                        if (loadFrom.find(loadInst->getFrom()) != loadFrom.end()) {
                            inst->tryReplaceUse(*u, fromFirstRepWithSecond[loadInst->getFrom()]);
                        }
                    }
                }
            }
            {
                // handle the terminator inst(ret...)
                auto inst = bb->getTerminator();
                for (const auto& u : inst->getUseList()) {
                    // u must be a LOAD inst then we can optimize
                    auto loadInst = dynamic_pointer_cast<LoadInst>(*u);
                    if (!loadInst) continue;
                    if (loadFrom.find(loadInst->getFrom()) != loadFrom.end()) {
                        inst->tryReplaceUse(*u, fromFirstRepWithSecond[loadInst->getFrom()]);
                    }
                }
            }
            // round 2: actually delete
            // cannot inplace delete, because it will change the size of vector
            // create another list
            decltype(bb->_instructions) newInstList;
            for (auto& inst : bb->_instructions) {
                if (!inst->isDeleted()) { newInstList.push_back(inst); }
                else {
                    std::cout << "delete inst: " << inst->getName() <<  std::endl;
                }
            }
            bb->_instructions = newInstList;
        }
    }
    g_log_level = old_level;
}

}   // namespace MiddleIR