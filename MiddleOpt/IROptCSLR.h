//
// Created by gaome on 2023/8/3.
//

#ifndef VRABCHE_IROPTCSLR_H
#define VRABCHE_IROPTCSLR_H


#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

// Const Store and Load Replacement
class IROptCSLR : public IROptimizerBase
{
public:
    explicit IROptCSLR(const shared_ptr<MiddleIRAST>& irast);
    ~IROptCSLR() override = default;
    void run() override;

private:
    static void OptForOneFunction(const shared_ptr<MiddleIRFuncDef>& func);
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTCSLR_H
