//
// Created by gaome on 2023/8/5.
//

#include "IROptIC.h"


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
}
}   // namespace MiddleIR::Optimizer
