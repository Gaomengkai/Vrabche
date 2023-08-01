//
// Created by gaome on 2023/7/19.
//

#ifndef IRBACKENDR5_IROPTDCE1_H
#define IRBACKENDR5_IROPTDCE1_H

#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

class IROptDCE1 : public IROptimizerBase
{
public:
    explicit IROptDCE1(shared_ptr<MiddleIRAST> irast)
        : IROptimizerBase(std::move(irast)){};
    void run() override;
};

}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_IROPTDCE1_H
