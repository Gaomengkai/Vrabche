//
// Created by gao on 6/30/23.
//

#include "IRProgram.h"
namespace IRCtrl
{

void IRProgram::addGlobalVar(const shared_ptr<VVal>& v)
{
    this->_global_var.emplace_back(v);
}
void IRProgram::addGlobalConst(const shared_ptr<CVal>& v)
{
    this->_global_const.emplace_back(v);
}
void IRProgram::addFunction(const shared_ptr<IRFunction>& v)
{
    this->_funcs.emplace_back(v);
}
const vector<shared_ptr<VVal>>& IRProgram::getGlobalVar() const
{
    return _global_var;
}
const vector<shared_ptr<CVal>>& IRProgram::getGlobalConst() const
{
    return _global_const;
}
const vector<shared_ptr<IRFunction>>& IRProgram::getFuncs() const
{
    return _funcs;
}
}   // namespace IRCtrl