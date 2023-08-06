//
// Created by gaome on 2023/8/5.
//

#include "IROptDCE2.h"


namespace MiddleIR::Optimizer
{
IROptDCE2::IROptDCE2(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptDCE2::run()
{
    // 用于删除每个基本块中不可达的代码（非内存型）
    // 比如v5 = addi v3, 1
    // 后续没有使用v5的话，就可以删除这条语句
    hasChanged = false;   // 如果发生改动，hasChanged置为true
}
}   // namespace MiddleIR::Optimizer
