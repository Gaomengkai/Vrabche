//
// Created by gaome on 2023/7/13.
//

#include "GenIRAST.h"
#include "R5Logger.h"
#include "MiddleIRBrInst.h"

#define R5IRVISITOR_VISITING_DEBUG

namespace MiddleIR
{
std::any GenIRAST::visitCompilationUnit(LLVMIRParser::CompilationUnitContext* context)
{
    // ALL entrypoint.
    // just visit children
    visitChildren(context);

    // do post-processing
    // 1. set funcDef  prev/next BB
    for (auto& func : m_irast.funcDefs) { func->buildBBPrevNext(); }

    return nullptr;
}
std::any GenIRAST::visitTopLevelEntity(LLVMIRParser::TopLevelEntityContext* context)
{
    // just visit children
    return visitChildren(context);
}
std::any GenIRAST::visitGlobalDecl(LLVMIRParser::GlobalDeclContext* context)
{
    RUNTIME_ERROR("GlobalDecl is not supported yet!");
}
/// globalDef:
///	GlobalIdent '='  immutable type constant;
/// \param context
/// \return
std::any GenIRAST::visitGlobalDef(LLVMIRParser::GlobalDefContext* context)
{
    // name
    string globalName = context->GlobalIdent()->getText();
    // global/const
    auto imm     = std::any_cast<string>(context->immutable()->accept(this));
    bool isConst = imm == "const";
    // type
    context->type()->accept(this);
    auto globalType = lastType;
    // val
    context->constant()->accept(this);
    auto globalVal = std::move(lastVal);
    if (globalVal->getType()->type == MiddleIRType::ZEROINITIALIZER && globalType->isArray()) {
        globalVal = make_shared<R5IRArray>(globalType, vector<shared_ptr<MiddleIRVal>>());
    }

    // settings for global var/const
    globalVal->setName(globalName);
    globalVal->setConst(isConst);

    if (isConst) {
        m_irast.globalConsts.emplace_back(globalVal);
    } else {
        m_irast.globalVars.emplace_back(globalVal);
    }
    return 0;
}

///
/// \param context
/// \return std::any which is string
std::any GenIRAST::visitImmutable(LLVMIRParser::ImmutableContext* context)
{
    return context->getText();
}
std::any GenIRAST::visitFuncDecl(LLVMIRParser::FuncDeclContext* context)
{
    auto   funcHeader = context->funcHeader();
    SPType funcRetType;
    funcHeader->type()->accept(this);
    funcRetType             = lastType;
    string         funcName = funcHeader->GlobalIdent()->getText();
    vector<SPType> funcParamsTypes;
    vector<string> funcParamsNames;
    /**
     * param: type LocalIdent?;
     */
    for (auto param : funcHeader->params()->param()) {
        param->type()->accept(this);
        funcParamsTypes.push_back(lastType);
        if (param->LocalIdent() == nullptr) {
            funcParamsNames.emplace_back("");
        } else {
            funcParamsNames.push_back(param->LocalIdent()->getText());
        }
    }
    auto funcDecl =
        make_shared<MiddleIRFuncDecl>(funcRetType, funcName, funcParamsTypes, funcParamsNames);
    m_irast.funcDecls.push_back(funcDecl);
    return 0;
}
/// funcDef:
///	'define' funcHeader funcBody;//函数定义
/// \param context
/// \return
std::any GenIRAST::visitFuncDef(LLVMIRParser::FuncDefContext* context)
{
    auto   funcHeader = context->funcHeader();
    SPType funcRetType;
    funcHeader->type()->accept(this);
    funcRetType             = lastType;
    string         funcName = funcHeader->GlobalIdent()->getText();
    vector<SPType> funcParamsTypes;
    vector<string> funcParamsNames;
    /**
     * param: type LocalIdent?;
     */
    for (auto param : funcHeader->params()->param()) {
        param->type()->accept(this);
        funcParamsTypes.push_back(lastType);
        if (param->LocalIdent() == nullptr) {
            funcParamsNames.emplace_back("");
        } else {
            funcParamsNames.push_back(param->LocalIdent()->getText());
        }
    }
    auto irFuncDef = make_shared<MiddleIRFuncDef>(
        funcRetType,
        funcName,
        funcParamsTypes,
        funcParamsNames,
        vector<shared_ptr<MiddleIRBasicBlock>>()
    );

    thisFunc = irFuncDef;

    m_irast.funcDefs.push_back(irFuncDef);

    auto funcBody = context->funcBody();
    for (auto bb : funcBody->basicBlock()) {
        bb->accept(this);
        auto b = std::move(lastBB);
        irFuncDef->addBasicBlock(std::move(b));
    }

    // link brInst to basicBlock
    for (const auto& bb : irFuncDef->getBasicBlocks()) {
        if (bb->getTerminator()->isBrInst()) {
            auto brInst = dynamic_pointer_cast<BrInst>(bb->getTerminator());
            auto toTrue = brInst->getIfTrueLabel();
            auto spBB   = irFuncDef->getBasicBlock(toTrue);
            IR_ASSERT(spBB != nullptr, "br target " << toTrue << " not found");
            brInst->setIfTrue(spBB);
            if (brInst->_brType == BrInst::CondBr) {
                auto toFalse = brInst->getIfFalseLabel();
                auto spBB2   = irFuncDef->getBasicBlock(toFalse);
                IR_ASSERT(spBB2 != nullptr, "br target " << toFalse << " not found");
                brInst->setIfFalse(spBB2);
            }
        }
    }

    return 0;
}
[[deprecated]] std::any GenIRAST::visitFuncHeader(LLVMIRParser::FuncHeaderContext* context)
{
    // No need. FuncHeader need to be handled in visitFuncDecl and visitFuncDef
    return nullptr;
}
[[deprecated]] std::any GenIRAST::visitFuncBody(LLVMIRParser::FuncBodyContext* context)
{
    // no need. FuncBody need to be handled in visitFuncDef
    return nullptr;
}
std::any GenIRAST::visitBasicBlock(LLVMIRParser::BasicBlockContext* context)
{
    auto labelName = context->LabelIdent()->getText();
    // cut the last ":"
    labelName = labelName.substr(0, labelName.size() - 1);
    auto ubb  = std::make_unique<MiddleIRBasicBlock>(labelName);
    for (auto inst : context->instruction()) {
        inst->accept(this);
        auto i = std::move(lastInst);
        ubb->addInstruction(i);
    }
    context->terminator()->accept(this);
    IR_ASSERT(lastInst->isTerminatorInst(), "Terminator expected");
    auto term = std::move(lastInst);
    ubb->setTerminator(std::move(term));
    lastBB = std::move(ubb);
    return 0;
}
std::any GenIRAST::visitInstruction(LLVMIRParser::InstructionContext* context)
{
    // handle all instruction here and store instruction into lastInst.
    // instructions will be add into basicBlock in visitBasicBlock

    string instVarName;
    if (context->localDefInst() != nullptr) {
        instVarName = context->localDefInst()->LocalIdent()->getText();
        context->localDefInst()->valueInstruction()->accept(this);
        lastInst->setName(instVarName);
        thisFunc->addVal(instVarName, lastInst);
    } else if (context->valueInstruction() != nullptr) {
        context->valueInstruction()->accept(this);
    } else {
        context->storeInst()->accept(this);
    }
    return 0;
}
std::any GenIRAST::visitTerminator(LLVMIRParser::TerminatorContext* context)
{
    // just visit Children.
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitLocalDefInst(LLVMIRParser::LocalDefInstContext* context)
{
    // no need. LocalDefInst handled in visitInstruction
    return visitChildren(context);
}
std::any GenIRAST::visitAddInst(LLVMIRParser::AddInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::ADD, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFaddInst(LLVMIRParser::FaddInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<FMathInst>(FMathInst::FMathOp::FADD, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitSubInst(LLVMIRParser::SubInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::SUB, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFsubInst(LLVMIRParser::FsubInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<FMathInst>(FMathInst::FMathOp::FSUB, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitMulInst(LLVMIRParser::MulInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::MUL, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFmulInst(LLVMIRParser::FmulInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<FMathInst>(FMathInst::FMathOp::FMUL, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitUdivInst(LLVMIRParser::UdivInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::UDIV, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitSdivInst(LLVMIRParser::SdivInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::SDIV, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFdivInst(LLVMIRParser::FdivInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<FMathInst>(FMathInst::FMathOp::FDIV, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitUremInst(LLVMIRParser::UremInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::UREM, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitSremInst(LLVMIRParser::SremInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<IMathInst>(IMathInst::IMathOp::SREM, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFremInst(LLVMIRParser::FremInstContext* context)
{
    context->concreteType()->accept(this);
    auto type = std::move(lastType);
    context->value(0)->accept(this);
    auto v1 = std::move(lastVal);
    context->value(1)->accept(this);
    auto v2   = std::move(lastVal);
    auto inst = std::make_unique<FMathInst>(FMathInst::FMathOp::FREM, type, v1, v2);
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitMathInstruction_(LLVMIRParser::MathInstruction_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitAllocaInst_(LLVMIRParser::AllocaInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitLoadInst_(LLVMIRParser::LoadInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitGEPInst_(LLVMIRParser::GEPInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitZExtInst_(LLVMIRParser::ZExtInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitSExtInst_(LLVMIRParser::SExtInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitSiToFpInst_(LLVMIRParser::SiToFpInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitFpToSiInst_(LLVMIRParser::FpToSiInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitBitCastInst_(LLVMIRParser::BitCastInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitICmpInst_(LLVMIRParser::ICmpInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitFCmpInst_(LLVMIRParser::FCmpInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
std::any GenIRAST::visitCallInst_(LLVMIRParser::CallInst_Context* context)
{
    // handled in children
    return visitChildren(context);
}
/// 	'store' concreteType value ',' concreteType value;
/// \param context
/// \return
std::any GenIRAST::visitStoreInst(LLVMIRParser::StoreInstContext* context)
{
    context->concreteType(0)->accept(this);
    auto typeFrom = lastType;
    context->value(0)->accept(this);
    auto valueFrom = std::move(lastVal);
    context->concreteType(1)->accept(this);
    auto typeTo = lastType;
    context->value(1)->accept(this);
    auto valueTo = std::move(lastVal);
    IR_ASSERT(*(DPC(PointerType, typeTo)->getElementType()) == *typeFrom, "Pointer type not match");
    lastInst = MU<StoreInst>(std::move(valueFrom), std::move(valueTo));
    return 0;
}
std::any GenIRAST::visitAllocaInst(LLVMIRParser::AllocaInstContext* context)
{
    context->type()->accept(this);
    lastInst = MU<AllocaInst>("", lastType);
    return 0;
}
/// 	'load' type ',' concreteType value;
/// \param context
/// \return
std::any GenIRAST::visitLoadInst(LLVMIRParser::LoadInstContext* context)
{
    context->type()->accept(this);
    auto type = lastType;
    context->concreteType()->accept(this);
    auto concreteType = lastType;
    context->value()->accept(this);
    auto value = std::move(lastVal);
    IR_ASSERT(DPC(PointerType, concreteType) != nullptr, "Not a pointer type");
    IR_ASSERT(
        *(DPC(PointerType, concreteType)->getElementType()) == *type, "Pointer type not match"
    );
    lastInst = MU<LoadInst>(std::move(value), type);
    return 0;
}
std::any GenIRAST::visitGetElementPtrInst(LLVMIRParser::GetElementPtrInstContext* context)
{
    // 'getelementptr'  type ',' concreteType value (',' concreteType value)*;
    //   %v4 = getelementptr [3 x i32], [3 x i32]* %v3, i32 114, i32 1

    // [3 x i32]
    context->type()->accept(this);
    auto type = lastType;

    // [3 x i32]* %v3
    context->concreteType(0)->accept(this);
    auto fromType = lastType;
    context->value(0)->accept(this);
    auto fromVal = std::move(lastVal);

    // i32 114, i32 1, ...
    auto pointers = std::vector<shared_ptr<MiddleIRVal>>();
    for (auto i = 1; i < context->value().size(); i++) {
        context->value(i)->accept(this);
        auto val = std::move(lastVal);
        // 这里不一定非得是const，还有可能是其他的val。比如%v3
        pointers.emplace_back(val);
    }

    // GetElementPtrInst(SPType type1, SPType fromType, shared_ptr<MiddleIRVal> from, vector<int>
    // index)
    auto inst = MU<GetElementPtrInst>(type, fromType, std::move(fromVal), std::move(pointers));
    lastInst  = std::move(inst);
    return 0;
}
std::any GenIRAST::visitBitCastInst(LLVMIRParser::BitCastInstContext* context)
{
    // 'bitcast' concreteType value 'to' type;
    context->concreteType()->accept(this);
    auto typeFrom = lastType;
    context->value()->accept(this);
    auto valueFrom = std::move(lastVal);
    context->type()->accept(this);
    auto typeTo = lastType;
    auto inst   = std::make_unique<BitCastInst>(typeFrom, std::move(valueFrom), typeTo);
    lastInst    = std::move(inst);
    return 0;
}
std::any GenIRAST::visitZExtInst(LLVMIRParser::ZExtInstContext* context)
{
    // concreteType value 'to' type;
    context->concreteType()->accept(this);
    auto typeFrom = lastType;
    context->value()->accept(this);
    auto valueFrom = std::move(lastVal);
    context->type()->accept(this);
    auto typeTo = lastType;
    auto inst   = std::make_unique<ConvertInst>(
        ConvertInst::ConvertOp::ZEXT, typeFrom, std::move(valueFrom), typeTo
    );
    lastInst = std::move(inst);
    return 0;
}
std::any GenIRAST::visitSExtInst(LLVMIRParser::SExtInstContext* context)
{
    context->concreteType()->accept(this);
    auto typeFrom = lastType;
    context->value()->accept(this);
    auto valueFrom = std::move(lastVal);
    context->type()->accept(this);
    auto typeTo = lastType;
    auto inst   = std::make_unique<ConvertInst>(
        ConvertInst::ConvertOp::SEXT, typeFrom, std::move(valueFrom), typeTo
    );
    lastInst = std::move(inst);
    return 0;
}
std::any GenIRAST::visitSiToFpInst(LLVMIRParser::SiToFpInstContext* context)
{
    context->concreteType()->accept(this);
    auto typeFrom = lastType;
    context->value()->accept(this);
    auto valueFrom = std::move(lastVal);
    context->type()->accept(this);
    auto typeTo = lastType;
    auto inst   = std::make_unique<ConvertInst>(
        ConvertInst::ConvertOp::SITOFP, typeFrom, std::move(valueFrom), typeTo
    );
    lastInst = std::move(inst);
    return 0;
}
std::any GenIRAST::visitFpToSiInst(LLVMIRParser::FpToSiInstContext* context)
{
    context->concreteType()->accept(this);
    auto typeFrom = lastType;
    context->value()->accept(this);
    auto valueFrom = std::move(lastVal);
    context->type()->accept(this);
    auto typeTo = lastType;
    auto inst   = std::make_unique<ConvertInst>(
        ConvertInst::ConvertOp::FPTOSI, typeFrom, std::move(valueFrom), typeTo
    );
    lastInst = std::move(inst);
    return 0;
}
std::any GenIRAST::visitICmpInst(LLVMIRParser::ICmpInstContext* context)
{
    // iCmpInst:
    //	'icmp' iPred concreteType value ',' value;
    auto iPred  = context->iPred()->getText();
    auto iCmpOp = ICmpInst::fromString(iPred);
    context->concreteType()->accept(this);
    auto type = lastType;
    context->value(0)->accept(this);
    auto value0 = std::move(lastVal);
    context->value(1)->accept(this);
    auto value1 = std::move(lastVal);
    lastInst    = MU<ICmpInst>(iCmpOp, type, std::move(value0), std::move(value1));
    return 0;
}
std::any GenIRAST::visitFCmpInst(LLVMIRParser::FCmpInstContext* context)
{
    // fCmpInst:
    //	'fcmp' fPred concreteType value ',' value;
    auto fPred  = context->fPred()->getText();
    auto fCmpOp = FCmpInst::fromString(fPred);
    context->concreteType()->accept(this);
    auto type = lastType;
    context->value(0)->accept(this);
    auto value0 = std::move(lastVal);
    context->value(1)->accept(this);
    auto value1 = std::move(lastVal);
    lastInst    = MU<FCmpInst>(fCmpOp, type, std::move(value0), std::move(value1));
    return 0;
}
std::any GenIRAST::visitCallInst(LLVMIRParser::CallInstContext* context)
{
    // callInst:
    //	'call' type value '(' args ')'
    // args: arg+
    // arg: concreteType value
    context->type()->accept(this);
    auto type = lastType;
    context->value()->accept(this);
    auto func_val = std::move(lastVal);
    IR_ASSERT(func_val->getType()->isFunction(), "callInst: value is not a function");
    auto                                       func = DPC(MiddleIRFuncDecl, func_val);
    auto                                       args = context->args();
    std::vector<std::shared_ptr<MiddleIRType>> argTypes;
    std::vector<std::shared_ptr<MiddleIRVal>>  argValues;
    for (auto arg : args->arg()) {
        arg->concreteType()->accept(this);
        argTypes.emplace_back(lastType);
        arg->value()->accept(this);
        argValues.emplace_back(std::move(lastVal));
    }
    lastInst = MU<CallInst>(func, std::move(argValues), func->getRetType());
    return 0;
}
std::any GenIRAST::visitRetTerm(LLVMIRParser::RetTermContext* context)
{
    // not ret void
    if (context->concreteType() != nullptr) {
        context->concreteType()->accept(this);
        auto retType = lastType;
        context->value()->accept(this);
        auto retValue = std::move(lastVal);
        auto retInst  = make_unique<ReturnInst>(retType, std::move(retValue));
        lastInst      = std::move(retInst);
    }
    // ret void
    else {
        auto retType = make_shared<VoidType>();
        auto retInst = make_unique<ReturnInst>(retType, nullptr);
        lastInst     = std::move(retInst);
    }
    return 0;
}
std::any GenIRAST::visitBrTerm(LLVMIRParser::BrTermContext* context)
{
    auto to = context->label()->LocalIdent()->getText();
    // cut the first "%"
    to       = to.substr(1);
    auto br  = make_unique<BrInst>(BrInst::UnCondBr, nullptr, to, "");
    lastInst = std::move(br);
    return 0;
}
std::any GenIRAST::visitCondBrTerm(LLVMIRParser::CondBrTermContext* context)
{
    IR_ASSERT(context->label().size() == 2, "CondBrTermContext should have 2 labels");
    auto toTrue  = context->label()[0]->LocalIdent()->getText();
    auto toFalse = context->label()[1]->LocalIdent()->getText();
    // cut the first "%"
    toTrue  = toTrue.substr(1);
    toFalse = toFalse.substr(1);
    context->value()->accept(this);
    IR_ASSERT(*lastVal->getType() == *spBoolType, "CondBrTermContext should have a bool value");
    auto cond = std::move(lastVal);
    auto br   = make_unique<BrInst>(BrInst::CondBr, cond, toTrue, toFalse);
    lastInst  = std::move(br);
    return 0;
}
std::any GenIRAST::visitFloatType(LLVMIRParser::FloatTypeContext* context)
{
    auto floatType = std::make_shared<FloatType>();
    lastType       = floatType;
    return floatType;
}
std::any GenIRAST::visitConcreteType(LLVMIRParser::ConcreteTypeContext* context)
{
    // Just visit the children
    return visitChildren(context);
}
std::any GenIRAST::visitValue(LLVMIRParser::ValueContext* context)
{
    if (context->constant()) {
        context->constant()->accept(this);
        return 0;
    }
    if (context->LocalIdent()) {
        auto name = context->LocalIdent()->getText();
        // only for BasicBlock, we need to cut the "%" in the front
        // but here we don't need to cut
        lastVal = thisFunc->getVal(name);
        return 0;
    }
    if (context->GlobalIdent()) {
        auto name = context->GlobalIdent()->getText();
        auto id   = getAST().findVal(name);
        lastVal   = std::move(id);
        return 0;
    }
    RUNTIME_ERROR("Unknown value type");
    return visitChildren(context);   // unreachable
}
std::any GenIRAST::visitConstant(LLVMIRParser::ConstantContext* context)
{
    // just visit the children
    return visitChildren(context);
}
std::any GenIRAST::visitBoolConst(LLVMIRParser::BoolConstContext* context)
{
    auto boolString = context->getText();
    bool boolVal    = boolString == "true";
    auto boolConst  = IR_BOOL_CONST(boolVal);
    lastVal         = std::move(boolConst);
    return 0;
}
std::any GenIRAST::visitIntConst(LLVMIRParser::IntConstContext* context)
{
    auto intString = context->IntLit()->getText();
    int  base      = 10;
    if (intString[0] == '0' && (intString[1] == 'x' || intString[1] == 'X')) {
        base      = 16;
        intString = intString.substr(2);
    }
    int  num    = std::stoi(intString, nullptr, base);
    auto intVal = IR_INT_CONST(num);
    lastVal     = std::move(intVal);
    return 0;
}
std::any GenIRAST::visitFloatConst(LLVMIRParser::FloatConstContext* context)
{
    string floatString = context->FloatLit()->getText();
    // starts with 0x
    if (floatString.length() > 2 && floatString[0] == '0' &&
        (floatString[1] == 'x' || floatString[1] == 'X')) {
        floatString       = floatString.substr(2);
        uint64_t num      = std::stoull(floatString, nullptr, 16);
        auto     floatVal = IR_FLOAT_CONST(num);
        lastVal           = std::move(floatVal);
    } else {
        double num      = std::stod(context->FloatLit()->getText());
        auto   floatVal = IR_FLOAT_CONST(num);
        lastVal         = std::move(floatVal);
    }
    return 0;
}
std::any GenIRAST::visitArrayConst(LLVMIRParser::ArrayConstContext* context)
{
    size_t                                    size = context->constant().size();
    std::vector<std::shared_ptr<MiddleIRVal>> values;
    context->concreteType(0)->accept(this);
    auto elemType = lastType;
    // attention: this TYPE is the elemType of ONE element. DO NOT use this elemType to represent
    // the array
    for (size_t i = 0; i < size; i++) {
        context->concreteType(i)->accept(this);
        IR_ASSERT(*lastType == *elemType, "ArrayConst should have the same elemType");
        context->constant(i)->accept(this);
        values.push_back(std::move(lastVal));
    }
    // guess the elemType of the array
    auto arrayType = make_shared<ArrayType>(size, elemType);
    lastVal        = std::make_shared<R5IRArray>(arrayType, std::move(values));
    return 0;
}
std::any GenIRAST::visitType(LLVMIRParser::TypeContext* context)
{
    auto typeText = context->getText();
    if (typeText == "void") {
        auto voidType = std::make_shared<VoidType>();
        lastType      = voidType;
        IR_ASSERT(dynamic_pointer_cast<VoidType>(lastType) != nullptr, "Dynamic cast failed");
        return voidType;
    } else if (typeText == "float") {
        auto floatType = std::make_shared<FloatType>();
        lastType       = floatType;
        return floatType;
    } else if (typeText.back() == '*') {
        context->type()->accept(this);
        auto ptrType = std::make_shared<PointerType>(lastType);
        lastType     = ptrType;
        return ptrType;
    } else {
        visitChildren(context);
        return lastType;
    }
}
std::any GenIRAST::visitIntType(LLVMIRParser::IntTypeContext* context)
{
    string type     = context->getText();
    int    bitWidth = 0;
    if (type == "i32") {
        bitWidth = 32;
    } else if (type == "i1") {
        bitWidth = 1;
    } else if (type == "i16") {
        bitWidth = 16;
    } else if (type == "i8") {
        bitWidth = 8;
    } else if (type == "i64") {
        bitWidth = 64;
    } else if (type == "i128") {
        bitWidth = 128;
    } else {
        RUNTIME_ERROR("Unknown int type: %s" << type);
    }
    auto intType = std::make_shared<IntType>(bitWidth);
    lastType     = intType;
    return intType;
}
std::any GenIRAST::visitPointerType(LLVMIRParser::PointerTypeContext* context)
{
    context->type()->accept(this);
    auto ptrType = std::make_shared<PointerType>(lastType);
    lastType     = ptrType;
    return ptrType;
}
std::any GenIRAST::visitLabelType(LLVMIRParser::LabelTypeContext* context)
{
    lastType = std::make_shared<LabelType>();
    return lastType;
}
std::any GenIRAST::visitArrayType(LLVMIRParser::ArrayTypeContext* context)
{
    size_t size = std::stoi(context->IntLit()->getText());
    context->type()->accept(this);
    auto arrayType = std::make_shared<ArrayType>(size, std::move(lastType));
    lastType       = std::move(arrayType);
    return 0;
}
[[deprecated]] std::any GenIRAST::visitNamedType(LLVMIRParser::NamedTypeContext* context)
{
    // [[deprecated]]
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitParams(LLVMIRParser::ParamsContext* context)
{
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitParam(LLVMIRParser::ParamContext* context)
{
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitLabel(LLVMIRParser::LabelContext* context)
{
    // handled in visitBrTerm and visitCondBrTerm
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitIPred(LLVMIRParser::IPredContext* context)
{
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitFPred(LLVMIRParser::FPredContext* context)
{
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitArgs(LLVMIRParser::ArgsContext* context)
{
    return visitChildren(context);
}
[[deprecated]] std::any GenIRAST::visitArg(LLVMIRParser::ArgContext* context)
{
    return visitChildren(context);
}
std::any GenIRAST::visitZeroInitializerConst(LLVMIRParser::ZeroInitializerConstContext* context)
{
    lastVal = std::make_shared<R5IRZeroInitializerVal>();
    return 0;
}

const MiddleIRAST& GenIRAST::getAST() const
{
    return m_irast;
}
}   // namespace MiddleIR

#undef R5IRVISITOR_VISITING_DEBUG