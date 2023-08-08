//
// Created by gaome on 2023/8/8.
//

#ifndef VRABCHE_IROPTCSE_H
#define VRABCHE_IROPTCSE_H
#include "IROptimizerBase.h"
#include "MiddleIRInst.h"
namespace MiddleIR::Optimizer
{
template<typename T>
using SP = shared_ptr<T>;

class IROptCSE : public IROptimizerBase
{
public:
    explicit IROptCSE(const shared_ptr<MiddleIRAST>& irast);
    ~IROptCSE() override = default;
    void        run() override;
    static bool runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb);
};

struct IMathTriple {
    IMathInst::IMathOp _op;
    SP<MiddleIRVal>    _lhs;
    SP<MiddleIRVal>    _rhs;

    struct Hash {
        size_t operator()(const IMathTriple& triple) const
        {
            auto   hash1 = static_cast<size_t>(triple._op) << 60;
            size_t hash2, hash3;
            if (auto constVal = DPC(R5IRValConstInt, triple._lhs)) {
                hash2 = constVal->getValue();
            } else {
                hash2 = reinterpret_cast<size_t>(triple._lhs.get());
            }
            if (auto constVal = DPC(R5IRValConstInt, triple._rhs)) {
                hash3 = constVal->getValue();
            } else {
                hash3 = reinterpret_cast<size_t>(triple._rhs.get());
            }
            return hash1 ^ hash2 ^ (hash3 << 32);
        }
    };

    struct Equal {
        static bool baseEQ(const SP<MiddleIRVal>& lhs, const SP<MiddleIRVal>& rhs)
        {
            if (auto constVal = DPC(R5IRValConstInt, lhs)) {
                if (auto constVal2 = DPC(R5IRValConstInt, rhs)) {
                    return constVal->getValue() == constVal2->getValue();
                } else {
                    return false;
                }
            } else {
                return lhs == rhs;
            }
        }
        bool operator()(const IMathTriple& lhs, const IMathTriple& rhs) const
        {
            if (lhs._op != rhs._op) return false;
            if (lhs._op == IMathInst::IMathOp::ADD || lhs._op == IMathInst::IMathOp::MUL) {
                return baseEQ(lhs._lhs, rhs._lhs) && baseEQ(lhs._rhs, rhs._rhs) ||
                       baseEQ(lhs._lhs, rhs._rhs) && baseEQ(lhs._rhs, rhs._lhs);
            } else {
                return baseEQ(lhs._lhs, rhs._lhs) && baseEQ(lhs._rhs, rhs._rhs);
            }
        }
    };
};

}   // namespace MiddleIR::Optimizer

#endif   // VRABCHE_IROPTCSE_H
