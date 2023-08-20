//
// Created by gaome on 2023/8/2.
//

#include "IROptInline.h"
#include "MiddleIRPrinter.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using std::unordered_map;
using std::unordered_set;

namespace MiddleIR::Optimizer
{
IROptInline::IROptInline(shared_ptr<MiddleIR::MiddleIRAST> irast)
    : IROptimizerBase(std::move(irast))
{
}
using SPFDecl = shared_ptr<MiddleIRFuncDecl>;

bool isOuterCall(const SPFDecl& f)
{
    if (dynamic_pointer_cast<MiddleIRFuncDef>(f)) return false;
    return true;
}

shared_ptr<MiddleIRInst> copyInst(const shared_ptr<MiddleIRInst>& i)
{
    switch (i->_instType) {
    case MiddleIRInst::AllocaInst: return make_shared<AllocaInst>(*SPC(AllocaInst, i));
    case MiddleIRInst::ReturnInst: return make_shared<ReturnInst>(*SPC(ReturnInst, i));
    case MiddleIRInst::BrInst: return make_shared<BrInst>(*SPC(BrInst, i));
    case MiddleIRInst::IMathInst: return make_shared<IMathInst>(*SPC(IMathInst, i));
    case MiddleIRInst::FMathInst: return make_shared<FMathInst>(*SPC(FMathInst, i));
    case MiddleIRInst::ICmpInst: return make_shared<ICmpInst>(*SPC(ICmpInst, i));
    case MiddleIRInst::FCmpInst: return make_shared<FCmpInst>(*SPC(FCmpInst, i));
    case MiddleIRInst::LoadInst: return make_shared<LoadInst>(*SPC(LoadInst, i));
    case MiddleIRInst::StoreInst: return make_shared<StoreInst>(*SPC(StoreInst, i));
    case MiddleIRInst::BitCastInst: return make_shared<BitCastInst>(*SPC(BitCastInst, i));
    case MiddleIRInst::GetElementPtrInst:
        return make_shared<GetElementPtrInst>(*SPC(GetElementPtrInst, i));
    case MiddleIRInst::ConvertInst: return make_shared<ConvertInst>(*SPC(ConvertInst, i));
    case MiddleIRInst::CallInst: return make_shared<CallInst>(*SPC(CallInst, i));
    }
    return nullptr;
}

void IROptInline::run()
{
    hasChanged = false;
    unordered_set<SPFDef> canInlineFuncs;
    do {
        canInlineFuncs.clear();
        // 检查哪些函数已经可以inline（先找没有call的函数）
        // 构建调用关系图
        unordered_map<SPFDef, unordered_set<SPFDecl>> callGraph;
        for (auto& f : _irast->funcDefs) {
            unordered_set<SPFDecl> callees;
            for (auto& b : f->getBasicBlocks()) {
                for (auto& i : b->_instructions) {
                    if (auto callInst = dynamic_pointer_cast<CallInst>(i)) {
                        callees.insert(callInst->getFunc());
                    }
                }
            }
            callGraph[f] = callees;
        }
        // 这里仅仅Inline一些简单函数（只有一个基本块，没有递归调用）
        // 筛选出可以inline的函数
        for (auto& f : _irast->funcDefs) {
            // not main
            if (f->getName() == "@main") continue;
            // single block
            if (f->getBasicBlocks().size() != 1) continue;
            // no recursive call
            bool canInline = true;
            for (const auto& callee : callGraph[f]) {
                if ((!isOuterCall(callee)) || callee == f) {
                    canInline = false;
                    break;
                }
            }
            if (canInline) canInlineFuncs.insert(f);
        }
        // inline
        for (auto& f : canInlineFuncs) {
            inlineSimpleFunc(f);
            // remove f
            for (auto fit = _irast->funcDefs.begin(); fit != _irast->funcDefs.end(); fit++) {
                if (*fit == f) {
                    _irast->funcDefs.erase(fit);
                    break;
                }
            }
            std::cout << "Inline ing function: " << f->getName() << std::endl;
            break;   // inline one func at a time
        }
    } while (!canInlineFuncs.empty());
}

string IROptInline::newName()
{
    string idx = std::to_string(_iid);
    _iid += 1;
    return "%k" + idx;
}
void IROptInline::inlineSimpleFunc(const SPFDef& toInlineF)
{
    hasChanged = true;
    std::unordered_set<SP<AllocaInst>> allocaInsts;
    unordered_set<SP<AllocaInst>>      argAlloca;
    std::list<SP<MiddleIRInst>>        oriInst;
    SP<ReturnInst>                     oriRetInst;
    for (const auto& b : toInlineF->getBasicBlocks()) {
        for (const auto& i : b->getInstructions()) {
            if (auto allocaInst = dynamic_pointer_cast<AllocaInst>(i)) {
                allocaInsts.insert(allocaInst);
            }
            if (auto storeInst = DPC(StoreInst, i)) {
                if (auto toAlloca = DPC(AllocaInst, storeInst->getTo());
                    storeInst->getFrom()->getName().size() > 5 &&
                    storeInst->getFrom()->getName().substr(0, 5) == "%arg_") {
                    argAlloca.insert(toAlloca);
                }
            }
            oriInst.push_back(i);
        }
        oriRetInst = DPC(ReturnInst, b->getTerminator());
    }
    for (const auto& f : _irast->funcDefs) {
        LOGW("func: " << f->getName());
        for (auto b : f->getBasicBlocks()) {
            bool needContinue;
            do {
                needContinue = false;
                for (auto iit = b->_instructions.begin(); iit != b->_instructions.end(); iit++) {
                    auto i = *iit;
                    if (auto callInst = DPC(CallInst, i)) {
                        if (callInst->getFunc()->getName() != toInlineF->getName()) continue;
                        hasChanged = true;
                        // do here to replace.
                        // make a copy
                        std::list<SP<MiddleIRInst>>                       newInst;
                        unordered_map<SP<MiddleIRInst>, SP<MiddleIRInst>> old2new;
                        unordered_map<SP<MiddleIRInst>, SP<MiddleIRInst>> new2old;
                        for (const auto& oi : oriInst) {
                            auto c = copyInst(oi);
                            newInst.push_back(c);
                            old2new[oi] = c;
                            new2old[c]  = oi;
                        }
                        // make an arg map
                        // ATTENTION bare pointer
                        vector<SP<MiddleIRVal>*> argMap(callInst->getArgs().size());
                        auto                     callArgs = callInst->getArgs();
                        for (auto& ni : newInst) {
                            for (auto& u : ni->getUseList()) {
                                auto uname = (*u)->getName();
                                if (uname.size() > 5 && uname.substr(0, 5) == "%arg_") {
                                    auto argIdx = stoi(uname.substr(5));
                                    ni->tryReplaceUse(*u, callArgs[argIdx]);
                                    //                                argMap[argIdx] = u;
                                }
                            }
                        }

                        // rename new inst
                        for (auto& ni : newInst) {
                            if (!ni->getName().empty()) { ni->setName(newName()); }
                        }

                        // rebuild use list
                        for (const auto& ni : newInst) {
                            for (auto nu : ni->getUseList()) {
                                auto useInst = DPC(MiddleIRInst, *nu);
                                if (old2new.find(useInst) != old2new.end()) {
                                    *nu = old2new[useInst];
                                    //                                ni->tryReplaceUse(*nu,
                                    //                                old2new[useInst]);
                                }
                            }
                        }

                        // handle ret(by a batch of replace)
                        auto retVal = oriRetInst->getOpVal();
                        if (retVal != nullptr) {
                            // replace
                            auto newVal = retVal;
                            if (auto retValInst = DPC(MiddleIRInst, retVal)) {
                                newVal = old2new[retValInst];
                            }
                            // replace call's return with newVal;
                            auto anotherIt = iit;
                            for (anotherIt++; anotherIt != b->_instructions.end(); anotherIt++) {
                                auto anotherI = *anotherIt;
                                for (auto nu : anotherI->getUseList()) {
                                    if (*nu == callInst) { *nu = newVal; }
                                }
                            }
                            auto ter = b->getTerminator();
                            for (auto nu : ter->getUseList()) {
                                if (*nu == callInst) { *nu = newVal; }
                            }
                        }


                        // move "ALLOCA" to another list.
                        std::list<SP<MiddleIRInst>> newAllocaInsts;
                        for (auto it = newInst.begin(); it != newInst.end();) {
                            if (auto allocaInst = DPC(AllocaInst, *it)) {
                                newAllocaInsts.push_back(*it);
                                it = newInst.erase(it);
                            } else {
                                it++;
                            }
                        }

                        // erase callInst
                        iit = b->_instructions.erase(iit);
                        // start inline (insert newInst into
                        b->_instructions.insert(iit, newInst.begin(), newInst.end());
                        // add ALLOCA
                        auto entry = f->getBasicBlock("LEntry");
                        entry->_instructions.insert(
                            entry->_instructions.begin(),
                            newAllocaInsts.begin(),
                            newAllocaInsts.end()
                        );
                        needContinue = true;
                        break;
                    }
                }
            } while (needContinue);
        }
    }
}
}   // namespace MiddleIR::Optimizer
