//
// Created by gaome on 2023/8/6.
//

#ifndef VRABCHE_IROPTGV2C_H
#define VRABCHE_IROPTGV2C_H


#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

class IROptGV2C : public IROptimizerBase
{
public:
    explicit IROptGV2C(const shared_ptr<MiddleIRAST>& irast);
    ~IROptGV2C() override = default;
    void run() override;
};

}   // namespace MiddleIR::Optimizer

#endif   // VRABCHE_IROPTGV2C_H
