//
// Created by gaome on 2023/7/19.
//

#ifndef IRBACKENDR5_IROPTIMIZERBASE_H
#define IRBACKENDR5_IROPTIMIZERBASE_H

#include <utility>

#include "R5Def.h"
#include "MiddleIRAST.h"
namespace MiddleIR::Optimizer
{

class IROptimizerBase
{
public:
    virtual ~IROptimizerBase() = default;
    explicit IROptimizerBase(shared_ptr<MiddleIRAST> irast)
        : _irast(std::move(irast)){};
    virtual void run() = 0;
    bool         hasChanged = false;

protected:
    shared_ptr<MiddleIRAST> _irast;

public:
    [[nodiscard]] const shared_ptr<MiddleIRAST>& getIrast() const { return _irast; }
};

}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_IROPTIMIZERBASE_H
