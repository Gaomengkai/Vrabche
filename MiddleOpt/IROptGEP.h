//
// Created by 17269 on 2023/8/20.
//

#ifndef VRABCHE_IROPTGEP_H
#define VRABCHE_IROPTGEP_H
#include "IROptimizerBase.h"
#include "MiddleIRType.h"
#include <map>
#include <memory>
#include <queue>
#define DPC(_ST, _TARG) std::dynamic_pointer_cast<_ST>((_TARG))
namespace MiddleIR::Optimizer{
    template<typename T>
    using SP = shared_ptr<T>;



    class IROptGEP : public IROptimizerBase
    {
    public:
        explicit IROptGEP(const shared_ptr<MiddleIRAST>& irast);
        ~IROptGEP() override = default;
        void        run() override;
        bool runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb);
        inline string G(){
            return "%g" + std::to_string(TempVarNum++);
        }
    protected:
        int TempVarNum = 0;
    };


}




#endif   // VRABCHE_IROPTGEP_H
