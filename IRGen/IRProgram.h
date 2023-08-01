//
// Created by gao on 6/30/23.
//

#ifndef SYSYLEX_IRPROGRAM_H
#define SYSYLEX_IRPROGRAM_H

#include <iostream>
#include "IRTypes.h"
#include "IRVal.h"
#include "IRFunction.h"

namespace IRCtrl
{
/**
 * This IS a IRProgram file, a builder can build a true file from this Program.
 */
class IRProgram
{
private:
public:
    [[nodiscard]] const vector<shared_ptr<VVal>>&       getGlobalVar() const;
    [[nodiscard]] const vector<shared_ptr<CVal>>&       getGlobalConst() const;
    [[nodiscard]] const vector<shared_ptr<IRFunction>>& getFuncs() const;

private:
    vector<shared_ptr<VVal>>       _global_var;
    vector<shared_ptr<CVal>>       _global_const;
    vector<shared_ptr<IRFunction>> _funcs;

public:
    void addGlobalVar(const shared_ptr<VVal>& v);
    void addGlobalConst(const shared_ptr<CVal>& v);
    void addFunction(const shared_ptr<IRFunction>& v);
};
}   // namespace IRCtrl



#endif   // SYSYLEX_IRPROGRAM_H
