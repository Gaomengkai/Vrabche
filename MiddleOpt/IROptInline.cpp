//
// Created by gaome on 2023/8/2.
//

#include "IROptInline.h"

#include <utility>


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
    do {
        for (auto& f : _irast->funcDefs) {
            bool canInline = true;
            for (auto& b : f->getBasicBlocks()) {
                for (auto& i : b->_instructions) {
                    if (auto callInst = dynamic_pointer_cast<CallInst>(i)) {
                        if (!isOuterCall(callInst->getFunc())||callInst->getName()=="@main") {
                            canInline = false;
                            break;
                        }
                    }
                }
            }
            if (canInline) {
                toInlineFunc = f;
                break;
            }
        }
        if (toInlineFunc != nullptr) { inlineFunc(toInlineFunc); }
    } while (toInlineFunc != nullptr);
    // inline
}
void IROptInline::inlineFunc(const SPFDef& f) {}
}   // namespace MiddleIR::Optimizer
