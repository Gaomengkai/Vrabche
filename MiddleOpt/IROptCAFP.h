//
// Created by gaome on 2023/8/3.
//

#ifndef VRABCHE_IROPTCAFP_H
#define VRABCHE_IROPTCAFP_H
#include "IROptimizerBase.h"
namespace MiddleIR
{
namespace Optimizer
{

// const args function propagation
class IROptCAFP:public IROptimizerBase
{
public:
    explicit IROptCAFP(const shared_ptr<MiddleIRAST>& irast);
    void run() override;
    ~IROptCAFP() override = default;
};

}   // namespace Optimizer
}   // namespace MiddleIR

#endif   // VRABCHE_IROPTCAFP_H
