//
// Created by gaome on 2023/8/4.
//

#include "IROptCF.h"
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>

template<class T>
using SP = shared_ptr<T>;

namespace MiddleIR::Optimizer
{

void IROptCF::ConstFold(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    std::map<SP<MiddleIRVal>, SP<MiddleIRVal>> mapConstReplace;
    do {
        mapConstReplace.clear();
        for (const auto& i : bb->_instructions) {
            if (i->isDeleted()) { continue; }
            if (auto binOpInst = DPC(IMathInst, i)) {
                auto lhs      = binOpInst->getOpVal1();
                auto rhs      = binOpInst->getOpVal2();
                auto lhsConst = DPC(R5IRValConstInt, lhs);
                auto rhsConst = DPC(R5IRValConstInt, rhs);
                if (lhsConst == nullptr || rhsConst == nullptr) { continue; }
                auto lhsVal = lhsConst->getValue();
                auto rhsVal = rhsConst->getValue();
                int  resVal;
                switch (binOpInst->iMathOp) {
                case IMathInst::IMathOp::ADD: resVal = lhsVal + rhsVal; break;
                case IMathInst::IMathOp::SUB: resVal = lhsVal - rhsVal; break;
                case IMathInst::IMathOp::MUL: resVal = lhsVal * rhsVal; break;
                case IMathInst::IMathOp::SDIV:
                case IMathInst::IMathOp::UDIV: resVal = lhsVal / rhsVal; break;
                case IMathInst::IMathOp::SREM:
                case IMathInst::IMathOp::UREM: resVal = lhsVal % rhsVal; break;
                }
                auto resConst              = std::make_shared<R5IRValConstInt>(resVal);
                mapConstReplace[binOpInst] = resConst;
                i->setDeleted();
            } else if (auto fMathInst = DPC(FMathInst, i)) {
                auto lhs      = fMathInst->getOpVal1();
                auto rhs      = fMathInst->getOpVal2();
                auto lhsConst = DPC(R5IRValConstFloat, lhs);
                auto rhsConst = DPC(R5IRValConstFloat, rhs);
                if (lhsConst == nullptr || rhsConst == nullptr) { continue; }
                auto  lhsVal = lhsConst->getValue();
                auto  rhsVal = rhsConst->getValue();
                float resVal;
                switch (fMathInst->fMathOp) {
                case FMathInst::FADD: resVal = lhsVal + rhsVal; break;
                case FMathInst::FSUB: resVal = lhsVal - rhsVal; break;
                case FMathInst::FMUL: resVal = lhsVal * rhsVal; break;
                case FMathInst::FDIV: resVal = lhsVal / rhsVal; break;
                case FMathInst::FREM: resVal = 0; break;
                }
                auto resConst              = std::make_shared<R5IRValConstFloat>(resVal);
                mapConstReplace[fMathInst] = resConst;
                i->setDeleted();
            }
        }
        // replace
        for (const auto& i : bb->_instructions) {
            for (auto& u : i->getUseList()) {
                if (mapConstReplace.find(*u) != mapConstReplace.end()) {
                    i->tryReplaceUse(*u, mapConstReplace[*u]);
                }
            }
        }
        auto ter = bb->getTerminator();
        for (auto& u : ter->getUseList()) {
            if (mapConstReplace.find(*u) != mapConstReplace.end()) {
                ter->tryReplaceUse(*u, mapConstReplace[*u]);
            }
        }
    } while (!mapConstReplace.empty());
    for (auto it1 = bb->_instructions.begin(); it1 != bb->_instructions.end();) {
        if ((*it1)->isDeleted()) {
            it1 = bb->_instructions.erase(it1);
        } else {
            ++it1;
        }
    }
}
}   // namespace MiddleIR::Optimizer
