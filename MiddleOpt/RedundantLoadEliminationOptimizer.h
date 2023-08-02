//
// Created by gaome on 2023/7/19.
//

#ifndef IRBACKENDR5_REDUNDANTLOADELIMINATIONOPTIMIZER_H
#define IRBACKENDR5_REDUNDANTLOADELIMINATIONOPTIMIZER_H
#include <set>
#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{


class RedundantLoadEliminationOptimizer : public IROptimizerBase
{
public:
    [[deprecated("This optimizer has bugs, please don't use it!")]]
    explicit RedundantLoadEliminationOptimizer(const shared_ptr<MiddleIRAST>& irast_)
        : IROptimizerBase(irast_)
    {
    }
    void run() override;
};

}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_REDUNDANTLOADELIMINATIONOPTIMIZER_H
