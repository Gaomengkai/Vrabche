
// Generated from LLVMIR.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "LLVMIRParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LLVMIRParser.
 */
class LLVMIRVisitor : public antlr4::tree::AbstractParseTreeVisitor
{
public:
    /**
     * Visit parse trees produced by LLVMIRParser.
     */
    virtual std::any visitCompilationUnit(LLVMIRParser::CompilationUnitContext* context) = 0;

    virtual std::any visitTopLevelEntity(LLVMIRParser::TopLevelEntityContext* context) = 0;

    virtual std::any visitGlobalDecl(LLVMIRParser::GlobalDeclContext* context) = 0;

    virtual std::any visitGlobalDef(LLVMIRParser::GlobalDefContext* context) = 0;

    virtual std::any visitImmutable(LLVMIRParser::ImmutableContext* context) = 0;

    virtual std::any visitFuncDecl(LLVMIRParser::FuncDeclContext* context) = 0;

    virtual std::any visitFuncDef(LLVMIRParser::FuncDefContext* context) = 0;

    virtual std::any visitFuncHeader(LLVMIRParser::FuncHeaderContext* context) = 0;

    virtual std::any visitFuncBody(LLVMIRParser::FuncBodyContext* context) = 0;

    virtual std::any visitBasicBlock(LLVMIRParser::BasicBlockContext* context) = 0;

    virtual std::any visitInstruction(LLVMIRParser::InstructionContext* context) = 0;

    virtual std::any visitTerminator(LLVMIRParser::TerminatorContext* context) = 0;

    virtual std::any visitLocalDefInst(LLVMIRParser::LocalDefInstContext* context) = 0;

    virtual std::any visitAddInst(LLVMIRParser::AddInstContext* context) = 0;

    virtual std::any visitFaddInst(LLVMIRParser::FaddInstContext* context) = 0;

    virtual std::any visitSubInst(LLVMIRParser::SubInstContext* context) = 0;

    virtual std::any visitFsubInst(LLVMIRParser::FsubInstContext* context) = 0;

    virtual std::any visitMulInst(LLVMIRParser::MulInstContext* context) = 0;

    virtual std::any visitFmulInst(LLVMIRParser::FmulInstContext* context) = 0;

    virtual std::any visitUdivInst(LLVMIRParser::UdivInstContext* context) = 0;

    virtual std::any visitSdivInst(LLVMIRParser::SdivInstContext* context) = 0;

    virtual std::any visitFdivInst(LLVMIRParser::FdivInstContext* context) = 0;

    virtual std::any visitUremInst(LLVMIRParser::UremInstContext* context) = 0;

    virtual std::any visitSremInst(LLVMIRParser::SremInstContext* context) = 0;

    virtual std::any visitFremInst(LLVMIRParser::FremInstContext* context) = 0;

    virtual std::any visitMathInstruction_(LLVMIRParser::MathInstruction_Context* context) = 0;

    virtual std::any visitAllocaInst_(LLVMIRParser::AllocaInst_Context* context) = 0;

    virtual std::any visitLoadInst_(LLVMIRParser::LoadInst_Context* context) = 0;

    virtual std::any visitGEPInst_(LLVMIRParser::GEPInst_Context* context) = 0;

    virtual std::any visitZExtInst_(LLVMIRParser::ZExtInst_Context* context) = 0;

    virtual std::any visitSExtInst_(LLVMIRParser::SExtInst_Context* context) = 0;

    virtual std::any visitSiToFpInst_(LLVMIRParser::SiToFpInst_Context* context) = 0;

    virtual std::any visitFpToSiInst_(LLVMIRParser::FpToSiInst_Context* context) = 0;

    virtual std::any visitBitCastInst_(LLVMIRParser::BitCastInst_Context* context) = 0;

    virtual std::any visitICmpInst_(LLVMIRParser::ICmpInst_Context* context) = 0;

    virtual std::any visitFCmpInst_(LLVMIRParser::FCmpInst_Context* context) = 0;

    virtual std::any visitCallInst_(LLVMIRParser::CallInst_Context* context) = 0;

    virtual std::any visitStoreInst(LLVMIRParser::StoreInstContext* context) = 0;

    virtual std::any visitAllocaInst(LLVMIRParser::AllocaInstContext* context) = 0;

    virtual std::any visitLoadInst(LLVMIRParser::LoadInstContext* context) = 0;

    virtual std::any visitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext* context) = 0;

    virtual std::any visitBitCastInst(LLVMIRParser::BitCastInstContext* context) = 0;

    virtual std::any visitZExtInst(LLVMIRParser::ZExtInstContext* context) = 0;

    virtual std::any visitSExtInst(LLVMIRParser::SExtInstContext* context) = 0;

    virtual std::any visitSiToFpInst(LLVMIRParser::SiToFpInstContext* context) = 0;

    virtual std::any visitFpToSiInst(LLVMIRParser::FpToSiInstContext* context) = 0;

    virtual std::any visitICmpInst(LLVMIRParser::ICmpInstContext* context) = 0;

    virtual std::any visitFCmpInst(LLVMIRParser::FCmpInstContext* context) = 0;

    virtual std::any visitCallInst(LLVMIRParser::CallInstContext* context) = 0;

    virtual std::any visitRetTerm(LLVMIRParser::RetTermContext* context) = 0;

    virtual std::any visitBrTerm(LLVMIRParser::BrTermContext* context) = 0;

    virtual std::any visitCondBrTerm(LLVMIRParser::CondBrTermContext* context) = 0;

    virtual std::any visitFloatType(LLVMIRParser::FloatTypeContext* context) = 0;

    virtual std::any visitConcreteType(LLVMIRParser::ConcreteTypeContext* context) = 0;

    virtual std::any visitValue(LLVMIRParser::ValueContext* context) = 0;

    virtual std::any visitConstant(LLVMIRParser::ConstantContext* context) = 0;

    virtual std::any visitBoolConst(LLVMIRParser::BoolConstContext* context) = 0;

    virtual std::any visitIntConst(LLVMIRParser::IntConstContext* context) = 0;

    virtual std::any visitFloatConst(LLVMIRParser::FloatConstContext* context) = 0;

    virtual std::any visitArrayConst(LLVMIRParser::ArrayConstContext* context) = 0;

    virtual std::any visitType(LLVMIRParser::TypeContext* context) = 0;

    virtual std::any visitIntType(LLVMIRParser::IntTypeContext* context) = 0;

    virtual std::any visitPointerType(LLVMIRParser::PointerTypeContext* context) = 0;

    virtual std::any visitLabelType(LLVMIRParser::LabelTypeContext* context) = 0;

    virtual std::any visitArrayType(LLVMIRParser::ArrayTypeContext* context) = 0;

    virtual std::any visitNamedType(LLVMIRParser::NamedTypeContext* context) = 0;

    virtual std::any visitParams(LLVMIRParser::ParamsContext* context) = 0;

    virtual std::any visitParam(LLVMIRParser::ParamContext* context) = 0;

    virtual std::any visitLabel(LLVMIRParser::LabelContext* context) = 0;

    virtual std::any visitIPred(LLVMIRParser::IPredContext* context) = 0;

    virtual std::any visitArgs(LLVMIRParser::ArgsContext* context) = 0;

    virtual std::any visitArg(LLVMIRParser::ArgContext* context) = 0;

    virtual std::any visitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext* context
    ) = 0;

    virtual std::any visitFPred(LLVMIRParser::FPredContext* context) = 0;
};
