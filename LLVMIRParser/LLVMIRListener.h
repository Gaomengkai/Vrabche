
// Generated from LLVMIR.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "LLVMIRParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LLVMIRParser.
 */
class LLVMIRListener : public antlr4::tree::ParseTreeListener
{
public:
    virtual void enterCompilationUnit(LLVMIRParser::CompilationUnitContext* ctx) = 0;
    virtual void exitCompilationUnit(LLVMIRParser::CompilationUnitContext* ctx)  = 0;

    virtual void enterTopLevelEntity(LLVMIRParser::TopLevelEntityContext* ctx) = 0;
    virtual void exitTopLevelEntity(LLVMIRParser::TopLevelEntityContext* ctx)  = 0;

    virtual void enterGlobalDecl(LLVMIRParser::GlobalDeclContext* ctx) = 0;
    virtual void exitGlobalDecl(LLVMIRParser::GlobalDeclContext* ctx)  = 0;

    virtual void enterGlobalDef(LLVMIRParser::GlobalDefContext* ctx) = 0;
    virtual void exitGlobalDef(LLVMIRParser::GlobalDefContext* ctx)  = 0;

    virtual void enterImmutable(LLVMIRParser::ImmutableContext* ctx) = 0;
    virtual void exitImmutable(LLVMIRParser::ImmutableContext* ctx)  = 0;

    virtual void enterFuncDecl(LLVMIRParser::FuncDeclContext* ctx) = 0;
    virtual void exitFuncDecl(LLVMIRParser::FuncDeclContext* ctx)  = 0;

    virtual void enterFuncDef(LLVMIRParser::FuncDefContext* ctx) = 0;
    virtual void exitFuncDef(LLVMIRParser::FuncDefContext* ctx)  = 0;

    virtual void enterFuncHeader(LLVMIRParser::FuncHeaderContext* ctx) = 0;
    virtual void exitFuncHeader(LLVMIRParser::FuncHeaderContext* ctx)  = 0;

    virtual void enterFuncBody(LLVMIRParser::FuncBodyContext* ctx) = 0;
    virtual void exitFuncBody(LLVMIRParser::FuncBodyContext* ctx)  = 0;

    virtual void enterBasicBlock(LLVMIRParser::BasicBlockContext* ctx) = 0;
    virtual void exitBasicBlock(LLVMIRParser::BasicBlockContext* ctx)  = 0;

    virtual void enterInstruction(LLVMIRParser::InstructionContext* ctx) = 0;
    virtual void exitInstruction(LLVMIRParser::InstructionContext* ctx)  = 0;

    virtual void enterTerminator(LLVMIRParser::TerminatorContext* ctx) = 0;
    virtual void exitTerminator(LLVMIRParser::TerminatorContext* ctx)  = 0;

    virtual void enterLocalDefInst(LLVMIRParser::LocalDefInstContext* ctx) = 0;
    virtual void exitLocalDefInst(LLVMIRParser::LocalDefInstContext* ctx)  = 0;

    virtual void enterAddInst(LLVMIRParser::AddInstContext* ctx) = 0;
    virtual void exitAddInst(LLVMIRParser::AddInstContext* ctx)  = 0;

    virtual void enterFaddInst(LLVMIRParser::FaddInstContext* ctx) = 0;
    virtual void exitFaddInst(LLVMIRParser::FaddInstContext* ctx)  = 0;

    virtual void enterSubInst(LLVMIRParser::SubInstContext* ctx) = 0;
    virtual void exitSubInst(LLVMIRParser::SubInstContext* ctx)  = 0;

    virtual void enterFsubInst(LLVMIRParser::FsubInstContext* ctx) = 0;
    virtual void exitFsubInst(LLVMIRParser::FsubInstContext* ctx)  = 0;

    virtual void enterMulInst(LLVMIRParser::MulInstContext* ctx) = 0;
    virtual void exitMulInst(LLVMIRParser::MulInstContext* ctx)  = 0;

    virtual void enterFmulInst(LLVMIRParser::FmulInstContext* ctx) = 0;
    virtual void exitFmulInst(LLVMIRParser::FmulInstContext* ctx)  = 0;

    virtual void enterUdivInst(LLVMIRParser::UdivInstContext* ctx) = 0;
    virtual void exitUdivInst(LLVMIRParser::UdivInstContext* ctx)  = 0;

    virtual void enterSdivInst(LLVMIRParser::SdivInstContext* ctx) = 0;
    virtual void exitSdivInst(LLVMIRParser::SdivInstContext* ctx)  = 0;

    virtual void enterFdivInst(LLVMIRParser::FdivInstContext* ctx) = 0;
    virtual void exitFdivInst(LLVMIRParser::FdivInstContext* ctx)  = 0;

    virtual void enterUremInst(LLVMIRParser::UremInstContext* ctx) = 0;
    virtual void exitUremInst(LLVMIRParser::UremInstContext* ctx)  = 0;

    virtual void enterSremInst(LLVMIRParser::SremInstContext* ctx) = 0;
    virtual void exitSremInst(LLVMIRParser::SremInstContext* ctx)  = 0;

    virtual void enterFremInst(LLVMIRParser::FremInstContext* ctx) = 0;
    virtual void exitFremInst(LLVMIRParser::FremInstContext* ctx)  = 0;

    virtual void enterMathInstruction_(LLVMIRParser::MathInstruction_Context* ctx) = 0;
    virtual void exitMathInstruction_(LLVMIRParser::MathInstruction_Context* ctx)  = 0;

    virtual void enterAllocaInst_(LLVMIRParser::AllocaInst_Context* ctx) = 0;
    virtual void exitAllocaInst_(LLVMIRParser::AllocaInst_Context* ctx)  = 0;

    virtual void enterLoadInst_(LLVMIRParser::LoadInst_Context* ctx) = 0;
    virtual void exitLoadInst_(LLVMIRParser::LoadInst_Context* ctx)  = 0;

    virtual void enterGEPInst_(LLVMIRParser::GEPInst_Context* ctx) = 0;
    virtual void exitGEPInst_(LLVMIRParser::GEPInst_Context* ctx)  = 0;

    virtual void enterZExtInst_(LLVMIRParser::ZExtInst_Context* ctx) = 0;
    virtual void exitZExtInst_(LLVMIRParser::ZExtInst_Context* ctx)  = 0;

    virtual void enterSExtInst_(LLVMIRParser::SExtInst_Context* ctx) = 0;
    virtual void exitSExtInst_(LLVMIRParser::SExtInst_Context* ctx)  = 0;

    virtual void enterSiToFpInst_(LLVMIRParser::SiToFpInst_Context* ctx) = 0;
    virtual void exitSiToFpInst_(LLVMIRParser::SiToFpInst_Context* ctx)  = 0;

    virtual void enterFpToSiInst_(LLVMIRParser::FpToSiInst_Context* ctx) = 0;
    virtual void exitFpToSiInst_(LLVMIRParser::FpToSiInst_Context* ctx)  = 0;

    virtual void enterBitCastInst_(LLVMIRParser::BitCastInst_Context* ctx) = 0;
    virtual void exitBitCastInst_(LLVMIRParser::BitCastInst_Context* ctx)  = 0;

    virtual void enterICmpInst_(LLVMIRParser::ICmpInst_Context* ctx) = 0;
    virtual void exitICmpInst_(LLVMIRParser::ICmpInst_Context* ctx)  = 0;

    virtual void enterFCmpInst_(LLVMIRParser::FCmpInst_Context* ctx) = 0;
    virtual void exitFCmpInst_(LLVMIRParser::FCmpInst_Context* ctx)  = 0;

    virtual void enterCallInst_(LLVMIRParser::CallInst_Context* ctx) = 0;
    virtual void exitCallInst_(LLVMIRParser::CallInst_Context* ctx)  = 0;

    virtual void enterStoreInst(LLVMIRParser::StoreInstContext* ctx) = 0;
    virtual void exitStoreInst(LLVMIRParser::StoreInstContext* ctx)  = 0;

    virtual void enterAllocaInst(LLVMIRParser::AllocaInstContext* ctx) = 0;
    virtual void exitAllocaInst(LLVMIRParser::AllocaInstContext* ctx)  = 0;

    virtual void enterLoadInst(LLVMIRParser::LoadInstContext* ctx) = 0;
    virtual void exitLoadInst(LLVMIRParser::LoadInstContext* ctx)  = 0;

    virtual void enterGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext* ctx) = 0;
    virtual void exitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext* ctx)  = 0;

    virtual void enterBitCastInst(LLVMIRParser::BitCastInstContext* ctx) = 0;
    virtual void exitBitCastInst(LLVMIRParser::BitCastInstContext* ctx)  = 0;

    virtual void enterZExtInst(LLVMIRParser::ZExtInstContext* ctx) = 0;
    virtual void exitZExtInst(LLVMIRParser::ZExtInstContext* ctx)  = 0;

    virtual void enterSExtInst(LLVMIRParser::SExtInstContext* ctx) = 0;
    virtual void exitSExtInst(LLVMIRParser::SExtInstContext* ctx)  = 0;

    virtual void enterSiToFpInst(LLVMIRParser::SiToFpInstContext* ctx) = 0;
    virtual void exitSiToFpInst(LLVMIRParser::SiToFpInstContext* ctx)  = 0;

    virtual void enterFpToSiInst(LLVMIRParser::FpToSiInstContext* ctx) = 0;
    virtual void exitFpToSiInst(LLVMIRParser::FpToSiInstContext* ctx)  = 0;

    virtual void enterICmpInst(LLVMIRParser::ICmpInstContext* ctx) = 0;
    virtual void exitICmpInst(LLVMIRParser::ICmpInstContext* ctx)  = 0;

    virtual void enterFCmpInst(LLVMIRParser::FCmpInstContext* ctx) = 0;
    virtual void exitFCmpInst(LLVMIRParser::FCmpInstContext* ctx)  = 0;

    virtual void enterCallInst(LLVMIRParser::CallInstContext* ctx) = 0;
    virtual void exitCallInst(LLVMIRParser::CallInstContext* ctx)  = 0;

    virtual void enterRetTerm(LLVMIRParser::RetTermContext* ctx) = 0;
    virtual void exitRetTerm(LLVMIRParser::RetTermContext* ctx)  = 0;

    virtual void enterBrTerm(LLVMIRParser::BrTermContext* ctx) = 0;
    virtual void exitBrTerm(LLVMIRParser::BrTermContext* ctx)  = 0;

    virtual void enterCondBrTerm(LLVMIRParser::CondBrTermContext* ctx) = 0;
    virtual void exitCondBrTerm(LLVMIRParser::CondBrTermContext* ctx)  = 0;

    virtual void enterFloatType(LLVMIRParser::FloatTypeContext* ctx) = 0;
    virtual void exitFloatType(LLVMIRParser::FloatTypeContext* ctx)  = 0;

    virtual void enterConcreteType(LLVMIRParser::ConcreteTypeContext* ctx) = 0;
    virtual void exitConcreteType(LLVMIRParser::ConcreteTypeContext* ctx)  = 0;

    virtual void enterValue(LLVMIRParser::ValueContext* ctx) = 0;
    virtual void exitValue(LLVMIRParser::ValueContext* ctx)  = 0;

    virtual void enterConstant(LLVMIRParser::ConstantContext* ctx) = 0;
    virtual void exitConstant(LLVMIRParser::ConstantContext* ctx)  = 0;

    virtual void enterBoolConst(LLVMIRParser::BoolConstContext* ctx) = 0;
    virtual void exitBoolConst(LLVMIRParser::BoolConstContext* ctx)  = 0;

    virtual void enterIntConst(LLVMIRParser::IntConstContext* ctx) = 0;
    virtual void exitIntConst(LLVMIRParser::IntConstContext* ctx)  = 0;

    virtual void enterFloatConst(LLVMIRParser::FloatConstContext* ctx) = 0;
    virtual void exitFloatConst(LLVMIRParser::FloatConstContext* ctx)  = 0;

    virtual void enterArrayConst(LLVMIRParser::ArrayConstContext* ctx) = 0;
    virtual void exitArrayConst(LLVMIRParser::ArrayConstContext* ctx)  = 0;

    virtual void enterType(LLVMIRParser::TypeContext* ctx) = 0;
    virtual void exitType(LLVMIRParser::TypeContext* ctx)  = 0;

    virtual void enterIntType(LLVMIRParser::IntTypeContext* ctx) = 0;
    virtual void exitIntType(LLVMIRParser::IntTypeContext* ctx)  = 0;

    virtual void enterPointerType(LLVMIRParser::PointerTypeContext* ctx) = 0;
    virtual void exitPointerType(LLVMIRParser::PointerTypeContext* ctx)  = 0;

    virtual void enterLabelType(LLVMIRParser::LabelTypeContext* ctx) = 0;
    virtual void exitLabelType(LLVMIRParser::LabelTypeContext* ctx)  = 0;

    virtual void enterArrayType(LLVMIRParser::ArrayTypeContext* ctx) = 0;
    virtual void exitArrayType(LLVMIRParser::ArrayTypeContext* ctx)  = 0;

    virtual void enterNamedType(LLVMIRParser::NamedTypeContext* ctx) = 0;
    virtual void exitNamedType(LLVMIRParser::NamedTypeContext* ctx)  = 0;

    virtual void enterParams(LLVMIRParser::ParamsContext* ctx) = 0;
    virtual void exitParams(LLVMIRParser::ParamsContext* ctx)  = 0;

    virtual void enterParam(LLVMIRParser::ParamContext* ctx) = 0;
    virtual void exitParam(LLVMIRParser::ParamContext* ctx)  = 0;

    virtual void enterLabel(LLVMIRParser::LabelContext* ctx) = 0;
    virtual void exitLabel(LLVMIRParser::LabelContext* ctx)  = 0;

    virtual void enterIPred(LLVMIRParser::IPredContext* ctx) = 0;
    virtual void exitIPred(LLVMIRParser::IPredContext* ctx)  = 0;

    virtual void enterArgs(LLVMIRParser::ArgsContext* ctx) = 0;
    virtual void exitArgs(LLVMIRParser::ArgsContext* ctx)  = 0;

    virtual void enterArg(LLVMIRParser::ArgContext* ctx) = 0;
    virtual void exitArg(LLVMIRParser::ArgContext* ctx)  = 0;

    virtual void enterZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext* ctx) = 0;
    virtual void exitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext* ctx)  = 0;

    virtual void enterFPred(LLVMIRParser::FPredContext* ctx) = 0;
    virtual void exitFPred(LLVMIRParser::FPredContext* ctx)  = 0;
};
