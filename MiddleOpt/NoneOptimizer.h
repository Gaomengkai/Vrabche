//
// Created by gaome on 2023/7/19.
//

#ifndef IRBACKENDR5_NONEOPTIMIZER_H
#define IRBACKENDR5_NONEOPTIMIZER_H

#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

class NoneOptimizer : public IROptimizerBase
{
public:
    explicit NoneOptimizer(shared_ptr<MiddleIRAST> irast)
        : IROptimizerBase(std::move(irast)){};
    void run() override;
};

}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_NONEOPTIMIZER_H
