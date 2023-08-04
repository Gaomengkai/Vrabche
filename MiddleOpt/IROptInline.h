//
// Created by gaome on 2023/8/2.
//

#ifndef VRABCHE_IROPTINLINE_H
#define VRABCHE_IROPTINLINE_H
#include "IROptimizerBase.h"

namespace MiddleIR::Optimizer
{

class IROptInline : IROptimizerBase
{
public:
    explicit IROptInline(shared_ptr<MiddleIR::MiddleIRAST> irast);
    ~IROptInline() override = default;
    void run() override;
    void inlineFunc(const shared_ptr<MiddleIRFuncDef>& f);
};

} // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTINLINE_H
