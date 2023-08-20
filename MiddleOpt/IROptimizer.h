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
#include "IROptRSE.h"
#include "IROptGV2C.h"
#include "IROptCSE.h"

#include "MiddleIRPrinter.h"
#include "IROptInline.h"
#include "IROptA2M.h"

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
        OPT_INLINE                       = 0x40,
        NONE_OPTIMIZATION                = 0x80,
        OPT_RLE                          = 0x100,
        INSTRUCTION_COMBINE              = 0x200,
        OPT_CAFP                         = 0x400,
        OPT_CP                           = 0x800,
        OPT_DCE2                         = 0x1000,
        OPT_IC                           = 0x2000,
        OPT_RSE                          = 0x4000,
        OPT_GV2C                         = 0x8000,
        OPT_CSE                          = 0x10000,
        OPT_A2M                          = 0x20000,
        ALL                              = (uint64_t)-1
    } enabledOpt           = O0;
    virtual ~IROptimizer() = default;
    explicit IROptimizer(const shared_ptr<MiddleIRAST>& irast_, ENABLED_OPT enabledOpt_ = O0)
        : _irast(irast_)
        , enabledOpt(enabledOpt_)
    {
        if (OPT_GV2C & enabledOpt) { _optimizers.push_back(new IROptGV2C(irast_)); }
        if (OPT_RLE & enabledOpt) { _optimizers.push_back(new IROptRLE(irast_)); }
        if (OPT_DCE1 & enabledOpt) { _optimizers.push_back(new IROptDCE1(irast_)); }
        if (OPT_CAFP & enabledOpt) { _optimizers.push_back(new IROptCAFP(irast_)); }
        if (OPT_CP & enabledOpt) { _optimizers.push_back(new IROptCP(irast_)); }
        if (OPT_DCE2 & enabledOpt) { _optimizers.push_back(new IROptDCE2(irast_)); }
        if (OPT_IC & enabledOpt) { _optimizers.push_back(new IROptIC(irast_)); }
        if (OPT_RSE & enabledOpt) { _optimizers.push_back(new IROptRSE(irast_)); }
        if (OPT_CSE & enabledOpt) { _optimizers.push_back(new IROptCSE(irast_)); }
        if (OPT_A2M & enabledOpt) { _optimizers.push_back(new IROptA2M(irast_)); }
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
        if (OPT_INLINE & enabledOpt) {
            auto inLine = new IROptInline(_irast);
            inLine->run();
        }
        int tcnt = 1;
        do {
            hasChanged = false;
            for (auto i = 0; i < _optimizers.size(); i++) {
                int pause = 1;
                // if (i == pause) {
                //     auto before = std::ofstream("../testsrc/"+std::to_string(tcnt)+"before.txt");
                //     for (const auto& f : _irast->funcDefs) {
                //         before << "FUNC " << f->getName() << std::endl;
                //         for (auto& b : f->getBasicBlocks()) { before << printBB(b) << std::endl;
                //         }
                //     }
                //     before.close();
                // }
                auto& optimizer = _optimizers[i];
                optimizer->run();
                LOGW("Opt " << i << "done. Has changed: " << optimizer->hasChanged);
                hasChanged |= optimizer->hasChanged;
                // if (i == pause) {
                //     auto after  = std::ofstream("../testsrc/"+std::to_string(tcnt)+"after.txt");
                //     for (const auto& f : _irast->funcDefs) {
                //         after << "FUNC " << f->getName() << std::endl;
                //         for (auto& b : f->getBasicBlocks()) { after << printBB(b) << std::endl; }
                //     }
                //     after.close();
                // }
            }
            tcnt++;
        } while (hasChanged);
        // auto after = std::ofstream("../testsrc/allafter.txt");
        // for (const auto& f : _irast->funcDefs) {
        //     after << "FUNC " << f->getName() << std::endl;
        //     for (auto& b : f->getBasicBlocks()) { after << printBB(b) << std::endl; }
        // }
        // after.close();
    }

protected:
    shared_ptr<MiddleIRAST>  _irast;
    vector<IROptimizerBase*> _optimizers;
};
}   // namespace MiddleIR::Optimizer

#endif   // IRBACKENDR5_IROPTIMIZER_H
