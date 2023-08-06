//
// Created by gaome on 2023/7/19.
//

#ifndef IRBACKENDR5_IROPTIMIZER_H
#define IRBACKENDR5_IROPTIMIZER_H

#include "IROptimizerBase.h"
#include "NoneOptimizer.h"
#include "IROptRLE.h"
#include "IROptDCE1.h"
#include "IROptDCE2.h"
#include "IROptCAFP.h"
#include "IROptCP.h"
#include "IROptIC.h"

namespace MiddleIR::Optimizer
{
class IROptimizer
{
public:
    enum ENABLED_OPT : uint64_t {
        O0                               = 0x0,
        CONSTANT_FOLDING                 = 0x1,
        CONSTANT_PROPAGATION             = 0x2,
        COPY_PROPAGATION                 = 0x4,
        OPT_DCE1                         = 0x8,
        COMMON_SUBEXPRESSION_ELIMINATION = 0x10,
        LOOP_OPTIMIZATION                = 0x20,
        FUNCTION_INLINE                  = 0x40,
        NONE_OPTIMIZATION                = 0x80,
        OPT_RLE                          = 0x100,
        INSTRUCTION_COMBINE              = 0x200,
        OPT_CAFP                         = 0x400,
        OPT_CP                           = 0x800,
        OPT_DCE2                         = 0x1000,
        OPT_IC                           = 0x2000,
        ALL                              = (uint64_t)-1
    } enabledOpt           = O0;
    virtual ~IROptimizer() = default;
    explicit IROptimizer(const shared_ptr<MiddleIRAST>& irast_, ENABLED_OPT enabledOpt_ = O0)
        : _irast(irast_)
        , enabledOpt(enabledOpt_)
    {
        if (OPT_RLE & enabledOpt) { _optimizers.push_back(new IROptRLE(irast_)); }
        if (OPT_DCE1 & enabledOpt) { _optimizers.push_back(new IROptDCE1(irast_)); }
        if (OPT_CAFP & enabledOpt) { _optimizers.push_back(new IROptCAFP(irast_)); }
        if (OPT_CP & enabledOpt) { _optimizers.push_back(new IROptCP(irast_)); }
        if (OPT_DCE2 & enabledOpt) { _optimizers.push_back(new IROptDCE2(irast_)); }
        if (OPT_IC & enabledOpt) { _optimizers.push_back(new IROptIC(irast_)); }
    }
    virtual void run()
    {
        bool hasChanged;
        do {
            hasChanged = false;
            for (auto i = 0; i < _optimizers.size(); i++) {
                auto& optimizer = _optimizers[i];
                optimizer->run();
                LOGW("Opt " << i << "done. Has changed: " << optimizer->hasChanged);
                hasChanged |= optimizer->hasChanged;
            }
        } while (hasChanged);
    }

protected:
    shared_ptr<MiddleIRAST>  _irast;
    vector<IROptimizerBase*> _optimizers;
};
}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_IROPTIMIZER_H
