//
// Created by gaome on 2023/7/10.
//

#include "SysyVisitor.h"
#include "IRBuilder.h"
#include "IRLogger.h"
#include "IRUtils.h"
#include "IRGlobalSwitch.h"
#include "IRGlobal.h"

using namespace IRCtrl;
using IRCtrl::g_builder;
using IRCtrl::g_lc;
using IRCtrl::g_sw;

std::tuple<IRValType, string> makeSureBool(IRValType t_, const std::string& s_)
{
    if(t_==IRCtrl::IRValType::Bool) {
        return {t_, s_};
    }
    else if(t_==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UNE, s_, "0x0000000000000000");
        g_builder->addSen(std::move(fcmp));
        return {IRValType::Bool, g_builder->getLastLabel()};
    } else if(t_==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::NE, s_, "0");
        g_builder->addSen(std::move(icmp));
        return {IRValType::Bool, g_builder->getLastLabel()};
    } else {
        RUNTIME_ERROR("Unknown type in cond");
    }
}

std::tuple<IRValType, string> ZExtOrNot(IRValType t_, const std::string& s_)
{
    if(t_!=IRCtrl::IRValType::Bool) {
        return {t_, s_};
    } else {
        auto zext = MU<ZextSen>(g_builder->getNewLabel(), s_, IRValType::Bool);
        g_builder->addSen(std::move(zext));
        return {IRValType::Int, g_builder->getLastLabel()};
    }
}

/// cond: lOrExp;
/// Here we must convert ALL types to bool(including CVal, Var, etc.)
/// \param context
/// \return
std::any IRVisitor::visitCond(SysyParser::CondContext* context)
{
    // check if the type is bool ( important )
    auto lOrExp = context->lOrExp()->accept(this);
    // 1. isBool. do nothing here. In "if", we will get last sentence.
    if (g_sw->isBool) {
        g_sw->isBool=false;
        return 0;
    }
    // 2. isCVal. just judge it NEQ 0?
    // 3. isVar. just judge it NEQ 0?
    auto [lt,ls] = getLastValue(lOrExp);
    makeSureBool(lt,ls);
//    if(lt==VT_FLOAT) {
//        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UNE, ls, "0x0000000000000000");
//        g_builder->addSen(std::move(fcmp));
//    } else if(lt==VT_INT) {
//        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::NE, ls, "0");
//        g_builder->addSen(std::move(icmp));
//    } else {
//        RUNTIME_ERROR("Unknown type in cond");
//    }
    return 0;
}


/// relExp:
///	| relExp Geq addExp	# geq;
/// \param context
/// \return
std::any IRVisitor::visitGeq(SysyParser::GeqContext* context)
{
    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->relExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->addExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UGE, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::SGE, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}

/// relExp:
//	| relExp Lt addExp	# lt
/// \param context
/// \return
std::any IRVisitor::visitLt(SysyParser::LtContext* context)
{
    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->relExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->addExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::ULT, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::SLT, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}

/// relExp:
//	addExp				# relExp_
/// \param context
/// \return
std::any IRVisitor::visitRelExp_(SysyParser::RelExp_Context* context)
{
    // FINAL
    return context->addExp()->accept(this);
}


/// | relExp Leq addExp	# leq
/// \param context
/// \return
std::any IRVisitor::visitLeq(SysyParser::LeqContext* context)
{
    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->relExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->addExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::ULE, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::SLE, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}


/// 	| relExp Gt addExp	# gt
/// \param context
/// \return
std::any IRVisitor::visitGt(SysyParser::GtContext* context)
{

    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->relExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->addExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UGT, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::SGT, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}


/// eqExp:
//	relExp				# eqExp_
//	| eqExp Eq relExp	# eq
//	| eqExp Neq relExp	# neq;
/// \param context
/// \return
std::any IRVisitor::visitNeq(SysyParser::NeqContext* context)
{
    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->eqExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->relExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UNE, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::NE, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}

/// eqExp:
//	| eqExp Eq relExp	# eq
/// \param context
/// \return
std::any IRVisitor::visitEq(SysyParser::EqContext* context)
{
    // 3<b<c is not allowed. so let's assume that there is only one < in the expression
    // that means, relExp is always a single addExp
    auto relExp = context->eqExp()->accept(this);
    auto [lt, ls]= getLastValue(relExp);
    tie(lt,ls)=ZExtOrNot(lt,ls);
    auto addExp = context->relExp()->accept(this);
    auto [rt, rs] = getLastValue(addExp);
    if(lt!=rt) {
        g_builder->checkTypeAndCast(rt,lt,rs);
        rs=g_builder->getLastLabel();
    }
    if(lt==VT_FLOAT) {
        auto fcmp = MU<FcmpSen>(g_builder->getNewLabel(),FCMPOp::UEQ, ls, rs);
        g_builder->addSen(std::move(fcmp));
    } else if(lt==VT_INT) {
        auto icmp = MU<IcmpSen>(g_builder->getNewLabel(),ICMPOp::EQ, ls, rs);
        g_builder->addSen(std::move(icmp));
    } else {
        RUNTIME_ERROR("Unknown type in lt");
    }

    g_sw->isBool= true;
    return 0;
}

/// eqExp:
//	relExp				# eqExp_
/// \param context
/// \return
std::any IRVisitor::visitEqExp_(SysyParser::EqExp_Context* context)
{
    // FINAL
    return context->relExp()->accept(this);
}

/// lAndExp: eqExp # lAndExp_
/// \param context
/// \return
std::any IRVisitor::visitLAndExp_(SysyParser::LAndExp_Context* context)
{
    // FINAL
    return context->eqExp()->accept(this);
}

/// lAndExp:
/// lAndExp And eqExp # and;
/// \param context
/// \return
std::any IRVisitor::visitAnd(SysyParser::AndContext* context)
{
    // 0. prepare
    auto trueBB = g_builder->createBB();
    g_bbc->pushAnd(trueBB);

    // 1. accept left.
    auto left = context->lAndExp()->accept(this);
    auto [lt,ls] = getLastValue(left);

    // 2. make sure last val is bool.
    tie(lt,ls) = makeSureBool(lt,ls);

    // 3. if left is false, jump to end.
    if((!g_sw->inIf)&&(!g_sw->inWhile)) RUNTIME_ERROR("And is not in if or while");

    // 4. br. if left is true, accept right. else, jump to end.
    auto br = MU<BrSen>(ls,g_bbc->queryTrueBB()->name,g_bbc->queryFalseBB()->name);
    g_builder->addSen(std::move(br));

    // 5. move to trueBB. and accept right.
    g_builder->moveToBB(trueBB);
    g_bbc->pop();

    auto accept =  context->eqExp()->accept(this);
    auto [rt,rs] = getLastValue(accept);
    makeSureBool(rt,rs);

    g_sw->isBool=true;

    return 0;
}


/// lOrExp:     | lOrExp Or lAndExp # or;
/// \param context
/// \return
std::any IRVisitor::visitOr(SysyParser::OrContext* context)
{
    // 0. prepare falseBB
    auto falseBB = g_builder->createBB();
    g_bbc->pushOr(falseBB);

    // 1. accept left.
    auto left = context->lOrExp()->accept(this);
    auto [lt,ls] = getLastValue(left);

    // 2. make sure last val is bool.
    tie(lt,ls) = makeSureBool(lt,ls);

    // 3. if left is false, jump to end.
    if((!g_sw->inIf)&&(!g_sw->inWhile)) RUNTIME_ERROR("And is not in if or while");

    // 4. br. if left is true, accept right. else, jump to end.
    auto br = MU<BrSen>(ls,g_bbc->queryTrueBB()->name, g_bbc->queryFalseBB()->name);
    g_builder->addSen(std::move(br));

    // 5. move to falseBB. and accept right.
    g_builder->moveToBB(falseBB);
    g_bbc->pop();

    auto accept = context->lAndExp()->accept(this);
    auto [rt,rs] = getLastValue(accept);
    makeSureBool(rt,rs);

    g_sw->isBool=true;

    return 0;
}

/// lOrExp: lAndExp # lOrExp_
/// \param context
/// \return
std::any IRVisitor::visitLOrExp_(SysyParser::LOrExp_Context* context)
{
    // FINAL
    return context->lAndExp()->accept(this);
}
