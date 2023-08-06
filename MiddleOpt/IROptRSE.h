//
// Created by gaome on 2023/8/6.
//

#ifndef VRABCHE_IROPTRSE_H
#define VRABCHE_IROPTRSE_H
#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

class IROptRSE : public IROptimizerBase
{
public:
    explicit IROptRSE(const shared_ptr<MiddleIRAST>& irast);
    ~IROptRSE() override = default;
    void run() override;
    void For1BB(const shared_ptr<MiddleIRBasicBlock>& b);
};

}   // namespace MiddleIR::Optimizer

#endif   // VRABCHE_IROPTRSE_H
