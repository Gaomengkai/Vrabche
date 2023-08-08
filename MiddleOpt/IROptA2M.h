//
// Created by gaome on 2023/8/8.
//

#ifndef VRABCHE_IROPTA2M_H
#define VRABCHE_IROPTA2M_H
#include "IROptimizerBase.h"
namespace MiddleIR
{
namespace Optimizer
{

class IROptA2M : public IROptimizerBase
{
public:
    explicit IROptA2M(const shared_ptr<MiddleIRAST>& irast);
    ~IROptA2M() override = default;
    void run() override;
    bool runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb);
};

}   // namespace Optimizer
}   // namespace MiddleIR

#endif   // VRABCHE_IROPTA2M_H
