//
// Created by gaome on 2023/8/2.
//

#include "IROptInline.h"

#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using std::unordered_map;
using std::unordered_set;

namespace MiddleIR::Optimizer
{
IROptInline::IROptInline(shared_ptr<MiddleIR::MiddleIRAST> irast)
    : IROptimizerBase(std::move(irast))
{
}
using SPFDecl = shared_ptr<MiddleIRFuncDecl>;
using SPFDef  = shared_ptr<MiddleIRFuncDef>;

bool isOuterCall(const SPFDecl& f)
{
    if (dynamic_pointer_cast<MiddleIRFuncDef>(f)) return false;
    return true;
}

void IROptInline::run()
{
    // 检查哪些函数已经可以inline（先找没有call的函数）
    shared_ptr<MiddleIRFuncDef> toInlineFunc;
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
    //
    //    do {
    //        for (auto& f : _irast->funcDefs) {
    //            bool canInline = true;
    //            if (f->getName() == "@main") continue;
    //            for (auto& b : f->getBasicBlocks()) {
    //                for (auto& i : b->_instructions) {
    //                    if (auto callInst = dynamic_pointer_cast<CallInst>(i)) {
    //                        if (!isOuterCall(callInst->getFunc())||callInst->getName()=="@main") {
    //                            canInline = false;
    //                            break;
    //                        }
    //                        // 如果是递归的话，也不能inline
    //                        if (callInst->getFunc()->getName() == f->getName()) {
    //                            canInline = false;
    //                            break;
    //                        }
    //                    }
    //                }
    //            }
    //            if (canInline) {
    //                toInlineFunc = f;
    //                break;
    //            }
    //        }
    //        if (toInlineFunc != nullptr) { inlineFunc(toInlineFunc); }
    //    } while (toInlineFunc != nullptr);
    // inline
}
void IROptInline::inlineFunc(const SPFDef& f) {}
}   // namespace MiddleIR::Optimizer
