//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_GENIRAST_H
#define IRBACKENDR5_GENIRAST_H
#include <antlr4-common.h>
#include "LLVMIRVisitor.h"
#include "MiddleIRAST.h"
namespace MiddleIR
{

class GenIRAST : public LLVMIRVisitor
{
public:
    std::any visitCompilationUnit(LLVMIRParser::CompilationUnitContext* context) override;
    std::any visitTopLevelEntity(LLVMIRParser::TopLevelEntityContext* context) override;
    std::any visitGlobalDecl(LLVMIRParser::GlobalDeclContext* context) override;
    std::any visitGlobalDef(LLVMIRParser::GlobalDefContext* context) override;
    std::any visitImmutable(LLVMIRParser::ImmutableContext* context) override;
    /// funcDecl:
    ///	'declare' funcHeader;//函数声明
    /// \param context
    /// \return
    std::any visitFuncDecl(LLVMIRParser::FuncDeclContext* context) override;
    /// funcDef:
    ///	'define' funcHeader funcBody;
    /// \param context
    /// \return
    std::any visitFuncDef(LLVMIRParser::FuncDefContext* context) override;
    /// funcHeader:
    ///     type GlobalIdent
    ///		'(' params ')';
    /// \param context
    /// \return
    std::any visitFuncHeader(LLVMIRParser::FuncHeaderContext* context) override;
    /// funcBody: '{' basicBlock+ '}';
    /// \param context
    /// \return
    std::any visitFuncBody(LLVMIRParser::FuncBodyContext* context) override;


    /// basicBlock:
    ///	LabelIdent? instruction* terminator;
    /// \param context
    /// \return
    std::any visitBasicBlock(LLVMIRParser::BasicBlockContext* context) override;
    /// instruction:
    ///	localDefInst
    ///	| valueInstruction
    ///	| storeInst;
    /// \param context
    /// \return
    std::any visitInstruction(LLVMIRParser::InstructionContext* context) override;
    /// terminator:
    ///	retTerm
    ///	| brTerm
    ///	| condBrTerm;
    /// \param context
    /// \return
    std::any visitTerminator(LLVMIRParser::TerminatorContext* context) override;
    std::any visitLocalDefInst(LLVMIRParser::LocalDefInstContext* context) override;
    std::any visitAddInst(LLVMIRParser::AddInstContext* context) override;
    std::any visitFaddInst(LLVMIRParser::FaddInstContext* context) override;
    std::any visitSubInst(LLVMIRParser::SubInstContext* context) override;
    std::any visitFsubInst(LLVMIRParser::FsubInstContext* context) override;
    std::any visitMulInst(LLVMIRParser::MulInstContext* context) override;
    std::any visitFmulInst(LLVMIRParser::FmulInstContext* context) override;
    std::any visitUdivInst(LLVMIRParser::UdivInstContext* context) override;
    std::any visitSdivInst(LLVMIRParser::SdivInstContext* context) override;
    std::any visitFdivInst(LLVMIRParser::FdivInstContext* context) override;
    std::any visitUremInst(LLVMIRParser::UremInstContext* context) override;
    std::any visitSremInst(LLVMIRParser::SremInstContext* context) override;
    std::any visitFremInst(LLVMIRParser::FremInstContext* context) override;
    std::any visitMathInstruction_(LLVMIRParser::MathInstruction_Context* context) override;
    std::any visitAllocaInst_(LLVMIRParser::AllocaInst_Context* context) override;
    std::any visitLoadInst_(LLVMIRParser::LoadInst_Context* context) override;
    std::any visitGEPInst_(LLVMIRParser::GEPInst_Context* context) override;
    std::any visitZExtInst_(LLVMIRParser::ZExtInst_Context* context) override;
    std::any visitSExtInst_(LLVMIRParser::SExtInst_Context* context) override;
    std::any visitSiToFpInst_(LLVMIRParser::SiToFpInst_Context* context) override;
    std::any visitFpToSiInst_(LLVMIRParser::FpToSiInst_Context* context) override;
    std::any visitBitCastInst_(LLVMIRParser::BitCastInst_Context* context) override;
    std::any visitICmpInst_(LLVMIRParser::ICmpInst_Context* context) override;
    std::any visitFCmpInst_(LLVMIRParser::FCmpInst_Context* context) override;
    std::any visitCallInst_(LLVMIRParser::CallInst_Context* context) override;
    /// 	'store'concreteType value ',' concreteType value;
    /// \param context
    /// \return
    std::any visitStoreInst(LLVMIRParser::StoreInstContext* context) override;
    std::any visitAllocaInst(LLVMIRParser::AllocaInstContext* context) override;
    std::any visitLoadInst(LLVMIRParser::LoadInstContext* context) override;
    std::any visitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext* context) override;
    /// bitCastInst:
    ///	'bitcast' concreteType value 'to' type;
    /// \param context
    /// \return
    std::any visitBitCastInst(LLVMIRParser::BitCastInstContext* context) override;
    std::any visitZExtInst(LLVMIRParser::ZExtInstContext* context) override;
    std::any visitSExtInst(LLVMIRParser::SExtInstContext* context) override;
    std::any visitSiToFpInst(LLVMIRParser::SiToFpInstContext* context) override;
    std::any visitFpToSiInst(LLVMIRParser::FpToSiInstContext* context) override;
    std::any visitICmpInst(LLVMIRParser::ICmpInstContext* context) override;
    std::any visitFCmpInst(LLVMIRParser::FCmpInstContext* context) override;
    std::any visitCallInst(LLVMIRParser::CallInstContext* context) override;
    /// retTerm:
    ///	'ret' 'void'
    ///	|'ret' concreteType value;
    /// \param context
    /// \return
    std::any visitRetTerm(LLVMIRParser::RetTermContext* context) override;
    std::any visitBrTerm(LLVMIRParser::BrTermContext* context) override;
    std::any visitCondBrTerm(LLVMIRParser::CondBrTermContext* context) override;
    std::any visitFloatType(LLVMIRParser::FloatTypeContext* context) override;

    /// concreteType:
    ///	intType
    ///	| floatType
    ///	| pointerType
    ///	| labelType
    ///	| arrayType
    ///	| namedType;
    /// \param context
    /// \return
    std::any visitConcreteType(LLVMIRParser::ConcreteTypeContext* context) override;
    /// value:
    ///	constant
    ///	| LocalIdent
    ///	| GlobalIdent;
    /// \param context
    /// \return
    std::any visitValue(LLVMIRParser::ValueContext* context) override;
    /// constant:
    ///	boolConst
    ///	| intConst
    ///	| floatConst
    ///	| arrayConst
    ///	| zeroInitializerConst;
    /// \param context
    /// \return
    std::any visitConstant(LLVMIRParser::ConstantContext* context) override;
    /// [[deprecated]] boolConst: 'true' | 'false';
    /// \param context
    /// \return
    [[deprecated]] std::any visitBoolConst(LLVMIRParser::BoolConstContext* context) override;
    std::any                visitIntConst(LLVMIRParser::IntConstContext* context) override;
    /// floatConst: FloatLit;
    /// \param context
    /// \return
    std::any visitFloatConst(LLVMIRParser::FloatConstContext* context) override;
    /// arrayConst:
    ///	'[' (concreteType constant (',' concreteType constant)*)? ']';
    /// \param context
    /// \return
    std::any visitArrayConst(LLVMIRParser::ArrayConstContext* context) override;
    /// type:
    ///	'void'
    ///	| type '(' params ')'
    ///	| intType
    ///	| 'float'
    ///	| labelType
    ///	| arrayType
    ///	| type '*'
    ///	| namedType;
    /// \param context
    /// \return changed class var "lastType"
    std::any visitType(LLVMIRParser::TypeContext* context) override;
    /// IntType: 'i' DecimalDigit+;
    /// \param context
    /// \return make_shared IntType (bitWidth);
    std::any visitIntType(LLVMIRParser::IntTypeContext* context) override;
    /// pointerType:
    ///	type  '*' ;
    /// \param context
    /// \return
    std::any visitPointerType(LLVMIRParser::PointerTypeContext* context) override;
    /// labelType:
    ///	'label';
    /// \param context
    /// \return
    std::any visitLabelType(LLVMIRParser::LabelTypeContext* context) override;
    /// arrayType:
    ///	'[' IntLit 'x' type ']';
    /// \param context
    /// \return
    std::any visitArrayType(LLVMIRParser::ArrayTypeContext* context) override;
    /// (Not used.)
    /// \param context
    /// \return
    [[deprecated]] std::any visitNamedType(LLVMIRParser::NamedTypeContext* context) override;
    /// params: (param (',' param)*)?;
    /// \param context
    /// \return
    std::any visitParams(LLVMIRParser::ParamsContext* context) override;
    /// param: type LocalIdent?;
    /// \param context
    /// \return
    std::any visitParam(LLVMIRParser::ParamContext* context) override;
    /// label: 'label' LocalIdent;
    /// \param context
    /// \return
    std::any visitLabel(LLVMIRParser::LabelContext* context) override;
    /// Int MathInstruction_ op
    /// \param context
    /// \return
    std::any visitIPred(LLVMIRParser::IPredContext* context) override;
    /// args:
    ///	(arg (',' arg)*)?;
    /// \param context
    /// \return
    std::any visitArgs(LLVMIRParser::ArgsContext* context) override;
    /// arg: concreteType value;
    /// \param context
    /// \return
    std::any visitArg(LLVMIRParser::ArgContext* context) override;
    /// zeroInitializerConst: 'zeroinitializer';
    /// \param context
    /// \return
    std::any visitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext* context) override;
    /// Float MathInstruction_ op
    std::any visitFPred(LLVMIRParser::FPredContext* context) override;

private:
    MiddleIRAST m_irast;

    // in-class private variables for building AST
    SPType                         lastType;
    unique_ptr<MiddleIRBasicBlock> lastBB;
    shared_ptr<MiddleIRInst>       lastInst;
    shared_ptr<MiddleIRVal>        lastVal;
    shared_ptr<MiddleIRFuncDef>    thisFunc;

public:
    [[nodiscard]] const MiddleIRAST& getAST() const;
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_GENIRAST_H
