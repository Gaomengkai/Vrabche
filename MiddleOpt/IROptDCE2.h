//
// Created by gaome on 2023/8/5.
//

#ifndef VRABCHE_DCE2_H
#define VRABCHE_DCE2_H
#include "IROptimizerBase.h"

namespace MiddleIR::Optimizer
{

class IROptDCE2 : public IROptimizerBase
{
public:
    explicit IROptDCE2(const shared_ptr<MiddleIRAST>& irast);
    void run() override;
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_DCE2_H
