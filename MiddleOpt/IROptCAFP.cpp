//
// Created by gaome on 2023/8/3.
//

#include "IROptCAFP.h"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
using std::list;
using std::map;
using std::pair;
using std::unordered_map;

namespace MiddleIR::Optimizer
{
IROptCAFP::IROptCAFP(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
inline static bool
R5IRValConstEq(const shared_ptr<R5IRValConst>& v1, const shared_ptr<R5IRValConst>& v2)
{
    if (v1->getType() != v2->getType()) { return false; }
    if (auto floatConst1 = dynamic_pointer_cast<R5IRValConstFloat>(v1)) {
        auto floatConst2 = dynamic_pointer_cast<R5IRValConstFloat>(v2);
        return floatConst1->getWord() == floatConst2->getWord();
    }
    if (auto intConst1 = dynamic_pointer_cast<R5IRValConstInt>(v1)) {
        auto intConst2 = dynamic_pointer_cast<R5IRValConstInt>(v2);
        return intConst1->getWord() == intConst2->getWord();
    }
    if (auto boolConst1 = dynamic_pointer_cast<R5IRValConstI1>(v1)) {
        auto boolConst2 = dynamic_pointer_cast<R5IRValConstI1>(v2);
        return boolConst1->getWord() == boolConst2->getWord();
    }
    RUNTIME_ERROR("Unknown R5IRValConst type");
}
void IROptCAFP::run()
{
    if (powerOff) {
        hasChanged = false;
        return;
    }
    unordered_map<string, vector<shared_ptr<R5IRValConst>>> mapFnNameToConstArgs;
    std::unordered_set<string>                              setFnNameIgnored;
    for (const auto& f : _irast->funcDefs) {
        for (const auto& b : f->getBasicBlocks()) {
            for (const auto& i : b->_instructions) {
                if (auto callInst = dynamic_pointer_cast<CallInst>(i)) {
                    if (callInst->getFunc()->getName() == "@main" ||
                        setFnNameIgnored.find(callInst->getFunc()->getName()) !=
                            setFnNameIgnored.end()) {
                        continue;
                    }
                    if (mapFnNameToConstArgs.find(callInst->getFunc()->getName()) !=
                        mapFnNameToConstArgs.end()) {
                        auto callFuncArgs = callInst->getArgs();
                        auto mas          = mapFnNameToConstArgs[callInst->getFunc()->getName()];
                        int  j            = 0;
                        for (const auto& v : mas) {
                            if (auto cArg = dynamic_pointer_cast<R5IRValConst>(callFuncArgs[j])) {
                                if (!R5IRValConstEq(v, cArg)) {
                                    setFnNameIgnored.insert(callInst->getFunc()->getName());
                                    goto next_inst;
                                } else {
                                    j++;
                                    continue;
                                }
                            } else {
                                setFnNameIgnored.insert(callInst->getFunc()->getName());
                                goto next_inst;
                            }
                        }
                        // all args are const and equal
                    } else {
                        // first time
                        if (!DPC(MiddleIRFuncDef, callInst->getFunc())) {
                            setFnNameIgnored.insert(callInst->getFunc()->getName());
                            goto next_inst;
                        }
                        auto listConstArgs = vector<shared_ptr<R5IRValConst>>();
                        for (const auto& arg : callInst->getArgs()) {
                            if (auto cArg = dynamic_pointer_cast<R5IRValConst>(arg)) {
                                listConstArgs.push_back(cArg);
                            } else {
                                setFnNameIgnored.insert(callInst->getFunc()->getName());
                                goto next_inst;
                            }
                        }
                        mapFnNameToConstArgs[callInst->getFunc()->getName()] = listConstArgs;
                    }
                }
            next_inst:
                continue;
            }
        }
    }
    // replace.
    for (const auto& [funcName, args] : mapFnNameToConstArgs) {
        if (setFnNameIgnored.find(funcName) != setFnNameIgnored.end()) { continue; }
        auto fd = DPC(MiddleIRFuncDef, _irast->findVal(funcName));
        for (const auto& b : fd->getBasicBlocks()) {
            if (b->getName() != "LEntry") continue;
            for (auto& i : b->_instructions) {
                if (!i->isStoreInst()) continue;
                auto storeInst = DPC(StoreInst, i);
                auto fromName  = storeInst->getFrom()->getName();
                if (fromName.size() < 6 && fromName.substr(0, 5) != "%arg_") continue;
                auto argNum   = stoi(fromName.substr(5));
                auto arg      = args[argNum];
                auto newStore = make_shared<StoreInst>(arg, storeInst->getTo());
                i             = newStore;
            }
        }
    }
    hasChanged = true;
    powerOff   = true;
    // end
    LOGW("CAFP done");
}
}   // namespace MiddleIR::Optimizer
