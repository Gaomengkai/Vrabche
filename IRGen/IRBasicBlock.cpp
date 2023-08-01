//
// Created by gao on 6/30/23.
//

#include "IRBasicBlock.h"
namespace IRCtrl
{


void IRBasicBlock::add(UPLocalSen sen)
{
    this->instructions.emplace_back(std::move(sen));
}

bool IRBasicBlock::hasTerminalSen()
{
    if (this->instructions.empty()) return false;
    auto& tt = instructions.back();
    if (tt->getOp() == IROp::RET || tt->getOp() == IROp::BR) { return true; }
    return false;
}
string IRBasicBlock::getLabel() const
{
    return name;
}
}   // namespace IRCtrl