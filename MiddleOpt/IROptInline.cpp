//
// Created by gaome on 2023/8/2.
//

#include "IROptInline.h"

#include <utility>


namespace MiddleIR::Optimizer
{
void IROptInline::run() {}
IROptInline::IROptInline(shared_ptr<MiddleIR::MiddleIRAST> irast)
    : IROptimizerBase(std::move(irast))
{
}
} // namespace MiddleIR::Optimizer
