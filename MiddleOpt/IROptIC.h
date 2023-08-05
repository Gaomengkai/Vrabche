//
// Created by gaome on 2023/8/5.
//

#ifndef VRABCHE_IROPTIC_H
#define VRABCHE_IROPTIC_H
#include "IROptimizerBase.h"

namespace MiddleIR::Optimizer
{

class IROptIC : public IROptimizerBase
{
public:
    explicit IROptIC(const shared_ptr<MiddleIRAST>& irast);
    ~IROptIC() override = default;
    void run() override;
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTIC_H
