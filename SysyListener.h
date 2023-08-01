
// Generated from Sysy.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "SysyParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SysyParser.
 */
class SysyListener : public antlr4::tree::ParseTreeListener
{
public:
    virtual void enterCompUnit(SysyParser::CompUnitContext* ctx) = 0;

    virtual void exitCompUnit(SysyParser::CompUnitContext* ctx) = 0;

    virtual void enterCompUnitItem(SysyParser::CompUnitItemContext* ctx) = 0;

    virtual void exitCompUnitItem(SysyParser::CompUnitItemContext* ctx) = 0;

    virtual void enterDecl(SysyParser::DeclContext* ctx) = 0;

    virtual void exitDecl(SysyParser::DeclContext* ctx) = 0;

    virtual void enterConstDecl(SysyParser::ConstDeclContext* ctx) = 0;

    virtual void exitConstDecl(SysyParser::ConstDeclContext* ctx) = 0;

    virtual void enterInt(SysyParser::IntContext* ctx) = 0;

    virtual void exitInt(SysyParser::IntContext* ctx) = 0;

    virtual void enterFloat(SysyParser::FloatContext* ctx) = 0;

    virtual void exitFloat(SysyParser::FloatContext* ctx) = 0;

    virtual void enterConstDef(SysyParser::ConstDefContext* ctx) = 0;

    virtual void exitConstDef(SysyParser::ConstDefContext* ctx) = 0;

    virtual void enterVarDecl(SysyParser::VarDeclContext* ctx) = 0;

    virtual void exitVarDecl(SysyParser::VarDeclContext* ctx) = 0;

    virtual void enterVarDef(SysyParser::VarDefContext* ctx) = 0;

    virtual void exitVarDef(SysyParser::VarDefContext* ctx) = 0;

    virtual void enterInit(SysyParser::InitContext* ctx) = 0;

    virtual void exitInit(SysyParser::InitContext* ctx) = 0;

    virtual void enterInitList(SysyParser::InitListContext* ctx) = 0;

    virtual void exitInitList(SysyParser::InitListContext* ctx) = 0;

    virtual void enterFuncDef(SysyParser::FuncDefContext* ctx) = 0;

    virtual void exitFuncDef(SysyParser::FuncDefContext* ctx) = 0;

    virtual void enterFuncType_(SysyParser::FuncType_Context* ctx) = 0;

    virtual void exitFuncType_(SysyParser::FuncType_Context* ctx) = 0;

    virtual void enterVoid(SysyParser::VoidContext* ctx) = 0;

    virtual void exitVoid(SysyParser::VoidContext* ctx) = 0;

    virtual void enterFuncFParams(SysyParser::FuncFParamsContext* ctx) = 0;

    virtual void exitFuncFParams(SysyParser::FuncFParamsContext* ctx) = 0;

    virtual void enterScalarParam(SysyParser::ScalarParamContext* ctx) = 0;

    virtual void exitScalarParam(SysyParser::ScalarParamContext* ctx) = 0;

    virtual void enterArrayParam(SysyParser::ArrayParamContext* ctx) = 0;

    virtual void exitArrayParam(SysyParser::ArrayParamContext* ctx) = 0;

    virtual void enterBlock(SysyParser::BlockContext* ctx) = 0;

    virtual void exitBlock(SysyParser::BlockContext* ctx) = 0;

    virtual void enterBlockItem(SysyParser::BlockItemContext* ctx) = 0;

    virtual void exitBlockItem(SysyParser::BlockItemContext* ctx) = 0;

    virtual void enterAssign(SysyParser::AssignContext* ctx) = 0;

    virtual void exitAssign(SysyParser::AssignContext* ctx) = 0;

    virtual void enterExprStmt(SysyParser::ExprStmtContext* ctx) = 0;

    virtual void exitExprStmt(SysyParser::ExprStmtContext* ctx) = 0;

    virtual void enterBlockStmt(SysyParser::BlockStmtContext* ctx) = 0;

    virtual void exitBlockStmt(SysyParser::BlockStmtContext* ctx) = 0;

    virtual void enterIfElse(SysyParser::IfElseContext* ctx) = 0;

    virtual void exitIfElse(SysyParser::IfElseContext* ctx) = 0;

    virtual void enterWhile(SysyParser::WhileContext* ctx) = 0;

    virtual void exitWhile(SysyParser::WhileContext* ctx) = 0;

    virtual void enterBreak(SysyParser::BreakContext* ctx) = 0;

    virtual void exitBreak(SysyParser::BreakContext* ctx) = 0;

    virtual void enterContinue(SysyParser::ContinueContext* ctx) = 0;

    virtual void exitContinue(SysyParser::ContinueContext* ctx) = 0;

    virtual void enterReturn(SysyParser::ReturnContext* ctx) = 0;

    virtual void exitReturn(SysyParser::ReturnContext* ctx) = 0;

    virtual void enterExp(SysyParser::ExpContext* ctx) = 0;

    virtual void exitExp(SysyParser::ExpContext* ctx) = 0;

    virtual void enterCond(SysyParser::CondContext* ctx) = 0;

    virtual void exitCond(SysyParser::CondContext* ctx) = 0;

    virtual void enterLVal(SysyParser::LValContext* ctx) = 0;

    virtual void exitLVal(SysyParser::LValContext* ctx) = 0;

    virtual void enterPrimaryExp_(SysyParser::PrimaryExp_Context* ctx) = 0;

    virtual void exitPrimaryExp_(SysyParser::PrimaryExp_Context* ctx) = 0;

    virtual void enterLValExpr(SysyParser::LValExprContext* ctx) = 0;

    virtual void exitLValExpr(SysyParser::LValExprContext* ctx) = 0;

    virtual void enterDecIntConst(SysyParser::DecIntConstContext* ctx) = 0;

    virtual void exitDecIntConst(SysyParser::DecIntConstContext* ctx) = 0;

    virtual void enterOctIntConst(SysyParser::OctIntConstContext* ctx) = 0;

    virtual void exitOctIntConst(SysyParser::OctIntConstContext* ctx) = 0;

    virtual void enterHexIntConst(SysyParser::HexIntConstContext* ctx) = 0;

    virtual void exitHexIntConst(SysyParser::HexIntConstContext* ctx) = 0;

    virtual void enterDecFloatConst(SysyParser::DecFloatConstContext* ctx) = 0;

    virtual void exitDecFloatConst(SysyParser::DecFloatConstContext* ctx) = 0;

    virtual void enterHexFloatConst(SysyParser::HexFloatConstContext* ctx) = 0;

    virtual void exitHexFloatConst(SysyParser::HexFloatConstContext* ctx) = 0;

    virtual void enterNumber(SysyParser::NumberContext* ctx) = 0;

    virtual void exitNumber(SysyParser::NumberContext* ctx) = 0;

    virtual void enterUnaryExp_(SysyParser::UnaryExp_Context* ctx) = 0;

    virtual void exitUnaryExp_(SysyParser::UnaryExp_Context* ctx) = 0;

    virtual void enterCall(SysyParser::CallContext* ctx) = 0;

    virtual void exitCall(SysyParser::CallContext* ctx) = 0;

    virtual void enterUnaryAdd(SysyParser::UnaryAddContext* ctx) = 0;

    virtual void exitUnaryAdd(SysyParser::UnaryAddContext* ctx) = 0;

    virtual void enterUnarySub(SysyParser::UnarySubContext* ctx) = 0;

    virtual void exitUnarySub(SysyParser::UnarySubContext* ctx) = 0;

    virtual void enterNot(SysyParser::NotContext* ctx) = 0;

    virtual void exitNot(SysyParser::NotContext* ctx) = 0;

    virtual void enterStringConst(SysyParser::StringConstContext* ctx) = 0;

    virtual void exitStringConst(SysyParser::StringConstContext* ctx) = 0;

    virtual void enterFuncRParam(SysyParser::FuncRParamContext* ctx) = 0;

    virtual void exitFuncRParam(SysyParser::FuncRParamContext* ctx) = 0;

    virtual void enterFuncRParams(SysyParser::FuncRParamsContext* ctx) = 0;

    virtual void exitFuncRParams(SysyParser::FuncRParamsContext* ctx) = 0;

    virtual void enterDiv(SysyParser::DivContext* ctx) = 0;

    virtual void exitDiv(SysyParser::DivContext* ctx) = 0;

    virtual void enterMod(SysyParser::ModContext* ctx) = 0;

    virtual void exitMod(SysyParser::ModContext* ctx) = 0;

    virtual void enterMul(SysyParser::MulContext* ctx) = 0;

    virtual void exitMul(SysyParser::MulContext* ctx) = 0;

    virtual void enterMulExp_(SysyParser::MulExp_Context* ctx) = 0;

    virtual void exitMulExp_(SysyParser::MulExp_Context* ctx) = 0;

    virtual void enterAddExp_(SysyParser::AddExp_Context* ctx) = 0;

    virtual void exitAddExp_(SysyParser::AddExp_Context* ctx) = 0;

    virtual void enterAdd(SysyParser::AddContext* ctx) = 0;

    virtual void exitAdd(SysyParser::AddContext* ctx) = 0;

    virtual void enterSub(SysyParser::SubContext* ctx) = 0;

    virtual void exitSub(SysyParser::SubContext* ctx) = 0;

    virtual void enterGeq(SysyParser::GeqContext* ctx) = 0;

    virtual void exitGeq(SysyParser::GeqContext* ctx) = 0;

    virtual void enterLt(SysyParser::LtContext* ctx) = 0;

    virtual void exitLt(SysyParser::LtContext* ctx) = 0;

    virtual void enterRelExp_(SysyParser::RelExp_Context* ctx) = 0;

    virtual void exitRelExp_(SysyParser::RelExp_Context* ctx) = 0;

    virtual void enterLeq(SysyParser::LeqContext* ctx) = 0;

    virtual void exitLeq(SysyParser::LeqContext* ctx) = 0;

    virtual void enterGt(SysyParser::GtContext* ctx) = 0;

    virtual void exitGt(SysyParser::GtContext* ctx) = 0;

    virtual void enterNeq(SysyParser::NeqContext* ctx) = 0;

    virtual void exitNeq(SysyParser::NeqContext* ctx) = 0;

    virtual void enterEq(SysyParser::EqContext* ctx) = 0;

    virtual void exitEq(SysyParser::EqContext* ctx) = 0;

    virtual void enterEqExp_(SysyParser::EqExp_Context* ctx) = 0;

    virtual void exitEqExp_(SysyParser::EqExp_Context* ctx) = 0;

    virtual void enterLAndExp_(SysyParser::LAndExp_Context* ctx) = 0;

    virtual void exitLAndExp_(SysyParser::LAndExp_Context* ctx) = 0;

    virtual void enterAnd(SysyParser::AndContext* ctx) = 0;

    virtual void exitAnd(SysyParser::AndContext* ctx) = 0;

    virtual void enterOr(SysyParser::OrContext* ctx) = 0;

    virtual void exitOr(SysyParser::OrContext* ctx) = 0;

    virtual void enterLOrExp_(SysyParser::LOrExp_Context* ctx) = 0;

    virtual void exitLOrExp_(SysyParser::LOrExp_Context* ctx) = 0;
};
