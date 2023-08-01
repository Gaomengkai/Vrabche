//
// Created by gaome on 2023/7/11.
//
#include "SysyVisitor.h"
#include "IRBuilder.h"
#include "IRLogger.h"
#include "IRUtils.h"
#include "IRExceptions.h"
#include "IRGlobalSwitch.h"
#include "IRCondAndIterController.h"
#include "IRGlobal.h"

using namespace IRCtrl;
using IRCtrl::g_builder;
using IRCtrl::g_lc;
using IRCtrl::g_sw;
using IRCtrl::g_bbc;


/// stmt:
/// 	| If Lparen cond Rparen stmt (Else stmt)?	# ifElse
/// \param context
/// \return
std::any IRVisitor::visitIfElse(SysyParser::IfElseContext* context)
{
    // status
    g_sw->inIf.dive(true);

    // First we need to create 3 BBs
    SPBB trueBB = g_builder->createBB();
    SPBB falseBB;
    SPBB afterBB = g_builder->createBB();

    // check if there is else
    if(context->Else() != nullptr)
    {
        falseBB = g_builder->createBB();
    } else {
        falseBB = afterBB;
    }

    // push to BBC
    g_bbc->pushIf(trueBB, falseBB, afterBB, g_lc->getCurLayerNum());

    // 1. add COND sen
    context->cond()->accept(this);
    g_sw->isBool=false; // reset
    auto [lt, ls] = getLastValue();
    auto lastCond = ls;

    // 2. add BR
    auto condBrSen = MU<BrSen>(lastCond, trueBB->getLabel(), falseBB->getLabel());
    g_builder->addSen(std::move(condBrSen));

    // 3. move to TrueBB
    g_builder->moveToBB(trueBB);

    // 4. accept true stmt
    g_sw->inIf.dive(false);
    context->stmt()[0]->accept(this);
    g_sw->inIf.ascend();

    // 5. add BR
    auto trueBrSen = MU<BrSen>(afterBB->getLabel());
    g_builder->addSen(std::move(trueBrSen));

    // 6-8 if there is else
    if (context->Else() != nullptr) {
        // 6. move to FalseBB
        g_builder->moveToBB(falseBB);

        // 7. accept false stmt
        g_sw->inIf.dive(false);
        if(context->stmt().size() == 2)
            context->stmt()[1]->accept(this);
        g_sw->inIf.ascend();

        // 8. add BR
        auto falseBrSen = MU<BrSen>(afterBB->getLabel());
        g_builder->addSen(std::move(falseBrSen));
    }

    // 9. move to AfterBB
    g_builder->moveToBB(afterBB);

    // 10. status
    g_sw->inIf.ascend();
    g_bbc->pop();
    return 0;
}


/// stmt:
/// | While Lparen cond Rparen stmt				# while
/// \param context
/// \return
std::any IRVisitor::visitWhile(SysyParser::WhileContext* context)
{
    /**
     * Created by zzzcola 2023/7/12
     */
    // status
    g_sw->inWhile.dive(true);

    SPBB condBB = g_builder->createBB();
    SPBB bodyBB = g_builder->createBB();
    SPBB afterBB = g_builder->createBB();

    // push to BBC
    // inverted
    g_bbc->pushWhile(bodyBB,condBB , afterBB, g_lc->getCurLayerNum());

    // 1. add BR to CondBB
    auto brToCondSen = MU<BrSen>(condBB->getLabel());
    g_builder->addSen(std::move(brToCondSen));

    // 2. add COND sen
    g_builder->moveToBB(condBB);
    context->cond()->accept(this);
    g_sw->isBool = false; // reset
    auto [lt, ls] = getLastValue();
    auto lastCond = ls;

//    // 3. move to CondBB
//    g_builder->moveToBB(condBB);


    // 4. add BR
    auto condBrSen = MU<BrSen>(lastCond, bodyBB->getLabel(), afterBB->getLabel());
    g_builder->addSen(std::move(condBrSen));

    // 5. move to BodyBB
    g_builder->moveToBB(bodyBB);

    // 6. accept body stmt
    g_sw->inWhile.dive(false);
    context->stmt()->accept(this);
    g_sw->inWhile.ascend();

    // 7. add BR to CondBB
    auto brToCondSen2 = MU<BrSen>(condBB->getLabel());
    g_builder->addSen(std::move(brToCondSen2));

    // 8. move to AfterBB
    g_builder->moveToBB(afterBB);

    // 9. status
    g_sw->inWhile.ascend();
    g_bbc->pop(); // pop
    return 0;
}


/// stmt:
/// \param context
/// \return
std::any IRVisitor::visitBreak(SysyParser::BreakContext* context)
{
    auto whileAfter = g_bbc->queryWhileBreakBB()->getLabel();
    auto br = MU<BrSen>(whileAfter);
    g_builder->addSen(std::move(br));
    return 0;
}


/// stmt:
/// \param context
/// \return
std::any IRVisitor::visitContinue(SysyParser::ContinueContext* context)
{
    auto whileCondition = g_bbc->queryWhileCondBB()->getLabel();
    auto br = MU<BrSen>(whileCondition);
    g_builder->addSen(std::move(br));
    return 0;
}