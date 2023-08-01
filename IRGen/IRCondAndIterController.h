//
// Created by gao on 7/1/23.
//

#ifndef SYSYLEX_IRCONDANDITERCONTROLLER_H
#define SYSYLEX_IRCONDANDITERCONTROLLER_H
#include "IRBasicBlock.h"
#include "IRTypes.h"
namespace IRCtrl
{

using SPBB = shared_ptr<IRBasicBlock>;

struct IRBBLayer
{
    SPBB   condBB;
    SPBB   trueBB;
    SPBB   falseBB;
    SPBB   afterBB;
    size_t curLayerNum;
    enum LayerType
    {
        While,
        If,
        Or,
        And
    } type;
};

/// This class intends to deal with BRANCH and ITERATION
class IRCondAndIterController
{
public:
    IRCondAndIterController();
    void pushIf(SPBB trueBB_, SPBB ifFalseBB_, SPBB ifAfterBB_, size_t curLayerNum_);
    void pushWhile(SPBB trueBB_, SPBB whileCondBB_, SPBB whileBreakBB_, size_t curLayerNum_);
    void pushOr(SPBB falseBB_);
    void pushAnd(SPBB trueBB_);
    void pop();
    SPBB queryIfTrueBB();
    SPBB queryIfFalseBB();
    SPBB queryIfAfterBB();
    SPBB queryWhileBreakBB();
    SPBB queryWhileCondBB();
    SPBB queryWhileTrueBB();
    size_t queryWhileCurLayerNum();

    SPBB queryTrueBB();
    SPBB queryFalseBB();

protected:
    vector<shared_ptr<IRBBLayer>> _layers;
};

}   // namespace IRCtrl

#endif   // SYSYLEX_IRCONDANDITERCONTROLLER_H
