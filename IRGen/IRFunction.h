//
// Created by gao on 7/1/23.
//

#ifndef SYSYLEX_IRFUNCTION_H
#define SYSYLEX_IRFUNCTION_H
#include "IRTypes.h"
#include "IRVal.h"
#include "IRBasicBlock.h"
#include "IRCondAndIterController.h"
namespace IRCtrl
{

class IRFunction : public IRVal
{
public:
    vector<SPLocalVar>   alloca;
    vector<SPBasicBlock> bbs;
    SPBasicBlock         curBB;
    FuncType             _type;
    bool onlyDecl = false;

    IRFunction(FuncType& type1, const string& name1)
        : _type(std::move(type1))
    {
        curBB = make_shared<IRBasicBlock>("LEntry");
        bbs.push_back(curBB);
        name = name1;
        type = IRValType::Func;
    }

    IRFunction(const shared_ptr<FuncType>& type1, const string& name1, bool onlyDecl1)
        : _type(*type1), onlyDecl(onlyDecl1) {
        type=IRValType::Func;
        name=name1;
        if(!onlyDecl1) {
            curBB = MS<IRBasicBlock>("LEntry");
            bbs.push_back(curBB);
        }
    }

    [[nodiscard]] size_t getParamsNum() const;

public:
    string toString() override;
};

}   // namespace IRCtrl

#endif   // SYSYLEX_IRFUNCTION_H
