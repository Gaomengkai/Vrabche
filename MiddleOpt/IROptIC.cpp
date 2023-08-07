//
// Created by gaome on 2023/8/5.
//

#include "IROptIC.h"


using std::queue;

namespace MiddleIR::Optimizer
{

IROptIC::IROptIC(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptIC::run()
{
    /// 指令合并。比如v1=addi v2, 1; v3=addi v1, 1; 可以合并成v1=addi v2, 1; v3=addi v2, 2;
    /// 后续如果没有使用v1的话，可以删除v1=addi v2, 1（删除由DCE2完成）
    hasChanged = false;   // 如果发生改动，hasChanged置为true
    //需要我干的应该只有算数优化和比较优化
    //其他的gls应该都写了

    //先找出所有有关常数加减运算的算术指令
    for (auto &func: _irast->funcDefs) {

        queue<SPInst> iMath;
        for (auto &bb : func->getBasicBlocks()) {
            for (auto &inst :bb->_instructions) {
                //加入队列的条件是：是算术指令，且有一个操作数是常数，另一个操作数也是算术指令
                //整形和浮点型中间隔了一个sext指令，所以不会出现浮点数和整数的运算，不考虑浮点
                if (inst->isIMathInst()) {
                    auto i = dynamic_pointer_cast<IMathInst>(inst);
                    if ((i->getOpVal1()->isConst() && dynamic_pointer_cast<IMathInst>(i->getOpVal2())) ||(i->getOpVal2()->isConst() && dynamic_pointer_cast<IMathInst>(i->getOpVal1())) )
                        iMath.push(inst);
                }
            }
        }

        //然后对每个算术指令单独进行优化
        while (!iMath.empty()) {
            auto inst = dynamic_pointer_cast<IMathInst>(iMath.front());
            iMath.pop();
            IMathWithConst i(inst);
            if (i.couldCombine()) {
                std::pair<SPVal, SPVal> p = i.combine();
                if (p.first!=nullptr) {
                    inst->tryReplaceUse(inst->getOpVal1(), p.first);
                    hasChanged = true;
                }
                if (p.second!=nullptr) {
                    inst->tryReplaceUse(inst->getOpVal2(), p.second);
                    hasChanged = true;
                }
                if ((inst->getOpVal1()->isConst() && dynamic_pointer_cast<IMathInst>(inst->getOpVal2())) ||(inst->getOpVal2()->isConst() && dynamic_pointer_cast<IMathInst>(inst->getOpVal1()))){
                    iMath.push(inst);
                }
            }
        }


    }


}
}   // namespace MiddleIR::Optimizer
