//
// Created by Merky Gao on 2023/7/12.
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

std::any IRVisitor::visitUnaryExp_(SysyParser::UnaryExp_Context* context)
{
    // FINAL
    return context->primaryExp()->accept(this);
}
/// unaryExp:
/// 	| Add unaryExp	                # unaryAdd
/// \param context
/// \return
std::any IRVisitor::visitUnaryAdd(SysyParser::UnaryAddContext* context)
{
    // Const decl, we should pass the value as a true value
    auto accept = context->unaryExp()->accept(this);
    if (g_sw->isCVal) {
        auto n = std::any_cast<std::shared_ptr<CVal>>(accept);
        g_sw->isCVal = true;
        return (n);
    } else {
        string zero = g_builder->getLastSen()->_retType->type == VT_INT ? "0" : "0x0";
        g_builder->addAdd(
            g_builder->getLastSen()->_retType, zero, g_builder->getLastLabel()
        );
        g_sw->isCVal = false;
    }
    return 0;
}

/// 	| Sub unaryExp						# unarySub
/// \param context
/// \return
std::any IRVisitor::visitUnarySub(SysyParser::UnarySubContext* context)
{
    // Const decl, we should pass the value as a true value
    auto accept = context->unaryExp()->accept(this);
    if (g_sw->isCVal) {
        auto n = std::any_cast<std::shared_ptr<CVal>>(accept);
        n->unary();
        g_sw->isCVal = true;
        return (n);
    } else {
        string zero = g_builder->getLastSen()->_retType->type == VT_INT ? "0" : "0x0";
        g_builder->addSub(
            g_builder->getLastSen()->_retType, zero, g_builder->getLastLabel()
        );
        g_sw->isCVal = false;
    }
    return 0;
}
/// unaryExp:
///	| Not unaryExp						# not;
/// \param context
/// \return
std::any IRVisitor::visitNot(SysyParser::NotContext* context)
{
    auto accept = context->unaryExp()->accept(this);
    if (g_sw->isCVal) {
        auto n = std::any_cast<std::shared_ptr<CVal>>(accept);
        n->notOp();
        g_sw->isCVal = true;
        return (n);
    } else {
        /*
         *  %v6 = icmp eq i32 %v5, 0
         *  %v7 = zext i1 %v6 to i32
         */
        auto [t, s] = getLastValue(accept);
        string newLabel = g_builder->getNewLabel();
        if(t==IRCtrl::IRValType::Float) {
            auto fcmp = MU<FcmpSen>(newLabel, FCMPOp::UEQ, s, "0x0");
            g_builder->addSen(std::move(fcmp));
        } else if(t==IRCtrl::IRValType::Int) {
            auto icmp = MU<IcmpSen>(newLabel, ICMPOp::EQ, s, "0");
            g_builder->addSen(std::move(icmp));
        } else {
            RUNTIME_ERROR("Not operation on non-int/float value");
        }
        auto zext = MU<ZextSen>(g_builder->getNewLabel(), newLabel, IRValType::Bool);
        g_builder->addSen(std::move(zext));
        g_sw->isCVal = false;
    }
    return 0;
}
/// mulExp Div unaryExp	# div
/// \param context
/// \return
std::any IRVisitor::visitDiv(SysyParser::DivContext* context)
{
    if (g_sw->isConst.get()) {
        // addExp と mulExp IntORFloatCVal returnする
        auto lav = context->mulExp()->accept(this);
        auto rav = context->unaryExp()->accept(this);
        auto lv  = std::any_cast<std::shared_ptr<CVal>>(lav);
        auto rv  = std::any_cast<std::shared_ptr<CVal>>(rav);

        auto res     = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Div);
        g_sw->isCVal = true;
        return res;
    } else {
        bool isCVal[2];
        auto lav      = context->mulExp()->accept(this);
        isCVal[0]     = g_sw->isCVal.get();
        auto [lt, ls] = getLastValue(lav);

        auto rav      = context->unaryExp()->accept(this);
        isCVal[1]     = g_sw->isCVal.get();
        auto [rt, rs] = getLastValue(rav);

        if (isCVal[0] && isCVal[1]) {
            // 按照const的写法，直接算出来。
            auto lv  = ACS(CVal, lav);
            auto rv  = ACS(CVal, rav);
            auto res = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Div);
            g_sw->isCVal.set(true);
            return res;
        }
        // not all const.......Let's gen some sentences.
        else {
            // 他妈的。我们这里不能只看左边是啥就是啥类型。草他妈的。
            // 坑死老子了。我草。
            // shit.
            // 我们这里要看左右两边的类型，如果左边是int，右边是float，那么我们要把右边转成int。
            // 以前是这么干的。现在环境变了。草。如果两边有其中一边是他妈浮点，那么就得把另一边转换成浮点。
            // 我说的怎么他妈的第95个测试点过不了
            auto arithmeticType = lt;
            if (lt == VT_INT && rt == VT_FLOAT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, ls);
                ls             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            } else if (lt == VT_FLOAT && rt == VT_INT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, rs);
                rs             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            }
            g_builder->addDiv(makeType(arithmeticType), ls, rs);
            g_sw->isCVal = false;
        }
    }

    return 0;
}

/// mulExp Mod unaryExp	# mod;
/// \param context
/// \return
std::any IRVisitor::visitMod(SysyParser::ModContext* context)
{
    if (g_sw->isConst.get()) {
        // addExp と mulExp IntORFloatCVal returnする
        auto lav = context->mulExp()->accept(this);
        auto rav = context->unaryExp()->accept(this);
        auto lv  = std::any_cast<std::shared_ptr<CVal>>(lav);
        auto rv  = std::any_cast<std::shared_ptr<CVal>>(rav);

        auto res     = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Rem);
        g_sw->isCVal = true;
        return res;
    } else {
        bool isCVal[2];
        auto lav      = context->mulExp()->accept(this);
        isCVal[0]     = g_sw->isCVal.get();
        auto [lt, ls] = getLastValue(lav);

        auto rav      = context->unaryExp()->accept(this);
        isCVal[1]     = g_sw->isCVal.get();
        auto [rt, rs] = getLastValue(rav);

        if (isCVal[0] && isCVal[1]) {
            // 按照const的写法，直接算出来。
            auto lv  = ACS(CVal, lav);
            auto rv  = ACS(CVal, rav);
            auto res = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Rem);
            g_sw->isCVal.set(true);
            return res;
        }
        // not all const.......Let's gen some sentences.
        else {
            g_builder->addRem(makeType(lt), ls, rs);
        }
        g_sw->isCVal = false;
    }

    return 0;
}

/// mulExp Mul unaryExp	# mul
/// \param context
/// \return
std::any IRVisitor::visitMul(SysyParser::MulContext* context)
{
    if (g_sw->isConst.get()) {
        // addExp と mulExp IntORFloatCVal returnする
        auto lav = context->mulExp()->accept(this);
        auto rav = context->unaryExp()->accept(this);
        auto lv  = std::any_cast<std::shared_ptr<CVal>>(lav);
        auto rv  = std::any_cast<std::shared_ptr<CVal>>(rav);

        auto res     = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Mul);
        g_sw->isCVal = true;
        return res;
    } else {
        bool isCVal[2];
        auto lav      = context->mulExp()->accept(this);
        isCVal[0]     = g_sw->isCVal.get();
        auto [lt, ls] = getLastValue(lav);

        auto rav      = context->unaryExp()->accept(this);
        isCVal[1]     = g_sw->isCVal.get();
        auto [rt, rs] = getLastValue(rav);

        if (isCVal[0] && isCVal[1]) {
            // 按照const的写法，直接算出来。
            auto lv  = ACS(CVal, lav);
            auto rv  = ACS(CVal, rav);
            auto res = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Mul);
            g_sw->isCVal.set(true);
            return res;
        }
        // not all const.......Let's gen some sentences.
        else {
            auto arithmeticType = lt;
            if (lt == VT_INT && rt == VT_FLOAT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, ls);
                ls             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            } else if (lt == VT_FLOAT && rt == VT_INT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, rs);
                rs             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            }
            g_builder->addMul(makeType(arithmeticType), ls, rs);
        }
        g_sw->isCVal = false;
    }
    return 0;
}


/// addExp:
///	| addExp Add mulExp	# add
///  \param context
///  \return
std::any IRVisitor::visitAdd(SysyParser::AddContext* context)
{
    if (g_sw->isConst.get()) {
        // addExp と mulExp IntORFloatCVal returnする
        auto lav = context->addExp()->accept(this);
        auto rav = context->mulExp()->accept(this);
        auto lv  = ACS(CVal, lav);
        auto rv  = ACS(CVal, rav);

        auto res     = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Add);
        g_sw->isCVal = true;
        return res;
    } else {

        bool isCVal[2];
        auto lav      = context->addExp()->accept(this);
        isCVal[0]     = g_sw->isCVal.get();
        auto [lt, ls] = getLastValue(lav);

        auto rav      = context->mulExp()->accept(this);
        isCVal[1]     = g_sw->isCVal.get();
        auto [rt, rs] = getLastValue(rav);

        if (isCVal[0] && isCVal[1]) {
            // 按照const的写法，直接算出来。
            auto lv  = ACS(CVal, lav);
            auto rv  = ACS(CVal, rav);
            auto res = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Add);
            g_sw->isCVal.set(true);
            return res;
        }
        // not all const.......Let's gen some sentences.
        else {
            auto arithmeticType = lt;
            if (lt == VT_INT && rt == VT_FLOAT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, ls);
                ls             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            } else if (lt == VT_FLOAT && rt == VT_INT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, rs);
                rs             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            }
            g_builder->addAdd(makeType(arithmeticType), ls, rs);
            g_sw->isCVal = false;
        }
    }
    return 0;
}

/// 	| addExp Sub mulExp	# sub;
/// \param context
/// \return
std::any IRVisitor::visitSub(SysyParser::SubContext* context)
{
    if (g_sw->isConst.get()) {
        // addExp と mulExp IntORFloatCVal returnする
        auto lav     = context->addExp()->accept(this);
        auto rav     = context->mulExp()->accept(this);
        auto lv      = ACS(CVal, lav);
        auto rv      = ACS(CVal, rav);
        auto res     = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Sub);
        g_sw->isCVal = true;
        return res;
    } else {

        bool isCVal[2];
        auto lav      = context->addExp()->accept(this);
        isCVal[0]     = g_sw->isCVal.get();
        auto [lt, ls] = getLastValue(lav);

        auto rav      = context->mulExp()->accept(this);
        isCVal[1]     = g_sw->isCVal.get();
        auto [rt, rs] = getLastValue(rav);

        if (isCVal[0] && isCVal[1]) {
            // 按照const的写法，直接算出来。
            auto lv  = ACS(CVal, lav);
            auto rv  = ACS(CVal, rav);
            auto res = Utils::constBiCalc(lv, rv, IRCtrl::IRValOp::Sub);
            g_sw->isCVal.set(true);
            return res;
        }
        // not all const.......Let's gen some sentences.
        else {
            auto arithmeticType = lt;
            if (lt == VT_INT && rt == VT_FLOAT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, ls);
                ls             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            } else if (lt == VT_FLOAT && rt == VT_INT) {
                g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, rs);
                rs             = g_builder->getLastLabel();
                arithmeticType = VT_FLOAT;
            }
            g_builder->addSub(makeType(arithmeticType), ls, rs);
            g_sw->isCVal = false;
        }
    }
    return 0;
}
