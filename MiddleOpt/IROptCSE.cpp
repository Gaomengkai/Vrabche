//
// Created by gaome on 2023/8/8.
//

#include "IROptCSE.h"
using std::unordered_map;
namespace MiddleIR::Optimizer
{
IROptCSE::IROptCSE(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptCSE::run()
{
    hasChanged = false;
    for (auto f : _irast->funcDefs) {
        for (auto b : f->getBasicBlocks()) { hasChanged |= runOnBB(b); }
    }
}

bool IROptCSE::runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    bool changed = false;
    unordered_map<IMathTriple, SP<MiddleIRVal>, IMathTriple::Hash, IMathTriple::Equal> calculated;
    unordered_map<SP<MiddleIRVal>, SP<MiddleIRVal>>                                    replaceMap;
    for (auto& i : bb->getInstructions()) {
        if (auto mathInst = DPC(IMathInst, i)) {
            IMathTriple triple{mathInst->iMathOp, mathInst->getOpVal1(), mathInst->getOpVal2()};
            if (calculated.count(triple)) {
                replaceMap[mathInst] = calculated[triple];
            } else {
                calculated[triple] = mathInst;
            }
        }
    }
    for (auto& i : bb->getInstructions()) {
        for (auto& u : i->getUseList()) {
            auto iMathVal = DPC(IMathInst, *u);
            if (replaceMap.count(iMathVal)) {
                *u      = replaceMap[*u];
                changed = true;
            }
        }
    }
    for (auto& u : bb->getTerminator()->getUseList()) {
        auto iMathVal = DPC(IMathInst, *u);
        if (replaceMap.count(iMathVal)) {
            *u      = replaceMap[*u];
            changed = true;
        }
    }
    return changed;
}
}   // namespace MiddleIR::Optimizer