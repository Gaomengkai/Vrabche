//
// Created by gaome on 2023/8/8.
//

#include "IROptA2M.h"
#include <unordered_map>
#include <unordered_set>
using std::pair;
using std::unordered_map;
using std::unordered_set;
namespace MiddleIR::Optimizer
{
template<typename T>
using SP = shared_ptr<T>;
IROptA2M::IROptA2M(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptA2M::run()
{
    hasChanged = false;
    for (const auto& f : _irast->funcDefs) {
        for (const auto& b : f->getBasicBlocks()) { hasChanged |= runOnBB(b); }
    }
}
bool IROptA2M::runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    bool                        changed = false;
    decltype(bb->_instructions) newInsts;

    using Poseidon = pair<SP<MiddleIRVal>, int>;   // 值，重复加的次数
    unordered_map<SP<MiddleIRVal>, Poseidon> calculated;
    unordered_set<SP<MiddleIRVal>>           atomVal;

    for (auto& i : bb->getInstructions()) {
        // if assign ( not store or anonymous call )
        if (i->isStoreInst()) {
            newInsts.push_back(i);
            continue;
        }
        if (auto callInst = DPC(CallInst, i)) {
            if (callInst->getName().empty()) {
                newInsts.push_back(i);
                continue;
            }
        }
        // if math inst
        if (auto iMathInst = DPC(IMathInst, i);
            iMathInst != nullptr && iMathInst->iMathOp == IMathInst::IMathOp::ADD) {
            // const folding are not applied here.
            // here just handles a VReg + another VReg
            auto v1     = iMathInst->getOpVal1();
            auto v2     = iMathInst->getOpVal2();
            int  repeat = 1;
            if (v1 == v2) {
                if (calculated.count(v1)) {
                    repeat                = calculated[v1].second * 2;
                    calculated[iMathInst] = Poseidon{v1, repeat};
                } else {
                    calculated[iMathInst] = Poseidon{v1, 2};
                    repeat                = 2;
                }
                // repeat smaller than 8, we need not to use MUL instead of ADD
                if (repeat < 8) {
                    newInsts.push_back(i);
                    continue;
                } else {
                    iMathInst->iMathOp = IMathInst::IMathOp::MUL;
                    auto ul            = iMathInst->getUseList();
                    *ul[0]             = v1;
                    *ul[1]             = IR_INT_CONST(repeat);
                    changed            = true;
                    newInsts.push_back(i);
                }
            } else {
                if (calculated.count(v1) && calculated.count(v2)) {
                    auto v1c = calculated[v1];
                    auto v2c = calculated[v2];
                    if (v1c.first == v2c.first) {
                        repeat                = v1c.second + v2c.second;
                        calculated[iMathInst] = Poseidon{v1c.first, repeat};
                    } else {
                        repeat                = 1;
                        calculated[iMathInst] = Poseidon{iMathInst, 1};
                    }
                    if (repeat < 8) {
                        newInsts.push_back(i);
                    } else {
                        iMathInst->iMathOp = IMathInst::IMathOp::MUL;
                        auto ul            = iMathInst->getUseList();
                        *ul[0]             = v1c.first;
                        *ul[1]             = IR_INT_CONST(repeat);
                        changed            = true;
                        newInsts.push_back(i);
                    }
                } else {
                    repeat                = 1;
                    calculated[iMathInst] = Poseidon{iMathInst, 1};
                    newInsts.push_back(i);
                }
            }
        } else {
            atomVal.insert(i);
            calculated[i] = Poseidon{i, 1};
            newInsts.push_back(i);
        }
    }
    bb->_instructions.erase(bb->_instructions.begin(), bb->_instructions.end());
    bb->_instructions = newInsts;
    return changed;
}
}   // namespace MiddleIR::Optimizer