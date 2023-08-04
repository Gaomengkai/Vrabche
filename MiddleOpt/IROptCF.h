//
// Created by gaome on 2023/8/4.
//

#ifndef VRABCHE_IROPTCF_H
#define VRABCHE_IROPTCF_H


#include "MiddleIRBasicBlock.h"
namespace MiddleIR::Optimizer
{

class IROptCF
{
public:
    static void ConstFold(const shared_ptr<MiddleIRBasicBlock>& bb);
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTCF_H
