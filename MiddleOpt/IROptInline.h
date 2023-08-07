//
// Created by gaome on 2023/8/2.
//

#ifndef VRABCHE_IROPTINLINE_H
#define VRABCHE_IROPTINLINE_H
#include "IROptimizerBase.h"

namespace MiddleIR::Optimizer
{
using SPFDef = shared_ptr<MiddleIRFuncDef>;
template<class T>
using SP = shared_ptr<T>;
class IROptInline : IROptimizerBase
{
public:
    explicit IROptInline(shared_ptr<MiddleIR::MiddleIRAST> irast);
    ~IROptInline() override = default;
    void run() override;
    void inlineSimpleFunc(const SPFDef& toInlineF);

private:
    int         _iid = 0;
    std::string newName();
};

} // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTINLINE_H
