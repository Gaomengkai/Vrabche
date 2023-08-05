//
// Created by gaome on 2023/8/3.
//

#ifndef VRABCHE_IROPTCP_H
#define VRABCHE_IROPTCP_H


#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

// Const Store and Load Replacement
class IROptCP : public IROptimizerBase
{
public:
    explicit IROptCP(const shared_ptr<MiddleIRAST>& irast);
    ~IROptCP() override = default;
    void run() override;

private:
    [[deprecated("Use For1Func instead.")]] static void OptForOneFunction(const shared_ptr<MiddleIRFuncDef>& func);
    static void For1Func(const shared_ptr<MiddleIRFuncDef>& func);
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTCP_H
