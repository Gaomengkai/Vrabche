//
// Created by gaome on 2023/8/3.
//

#ifndef VRABCHE_IROPTCP_H
#define VRABCHE_IROPTCP_H
#include <variant>

#include "IROptimizerBase.h"
namespace MiddleIR::Optimizer
{

class UNDEF
{
};
class NAC
{
};
using FakeConst = std::variant<UNDEF, NAC, shared_ptr<R5IRValConst>>;

// Const Store and Load Replacement
class IROptCP : public IROptimizerBase
{
public:
    explicit IROptCP(const shared_ptr<MiddleIRAST>& irast);
    ~IROptCP() override = default;
    void run() override;

private:
    template<class T>
    using SP = shared_ptr<T>;
    void        For1Func(const shared_ptr<MiddleIRFuncDef>& func);
    static void ExecuteCurBB(
        std::unordered_map<shared_ptr<AllocaInst>, FakeConst>& map,
        const shared_ptr<MiddleIRBasicBlock>&                  bb
    );
    static void printIt(
        std::unordered_map<SP<MiddleIRBasicBlock>, std::unordered_map<SP<AllocaInst>, FakeConst>>&
            mapEachBBValStatus
    );
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTCP_H
