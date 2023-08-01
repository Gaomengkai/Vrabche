
// Generated from LLVMIR.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"




class LLVMIRParser : public antlr4::Parser
{
public:
    enum {
        T__0        = 1,
        T__1        = 2,
        T__2        = 3,
        T__3        = 4,
        T__4        = 5,
        T__5        = 6,
        T__6        = 7,
        T__7        = 8,
        T__8        = 9,
        T__9        = 10,
        T__10       = 11,
        T__11       = 12,
        T__12       = 13,
        T__13       = 14,
        T__14       = 15,
        T__15       = 16,
        T__16       = 17,
        T__17       = 18,
        T__18       = 19,
        T__19       = 20,
        T__20       = 21,
        T__21       = 22,
        T__22       = 23,
        T__23       = 24,
        T__24       = 25,
        T__25       = 26,
        T__26       = 27,
        T__27       = 28,
        T__28       = 29,
        T__29       = 30,
        T__30       = 31,
        T__31       = 32,
        T__32       = 33,
        T__33       = 34,
        T__34       = 35,
        T__35       = 36,
        T__36       = 37,
        T__37       = 38,
        T__38       = 39,
        T__39       = 40,
        T__40       = 41,
        T__41       = 42,
        T__42       = 43,
        T__43       = 44,
        T__44       = 45,
        T__45       = 46,
        T__46       = 47,
        T__47       = 48,
        T__48       = 49,
        T__49       = 50,
        T__50       = 51,
        T__51       = 52,
        T__52       = 53,
        T__53       = 54,
        T__54       = 55,
        T__55       = 56,
        T__56       = 57,
        T__57       = 58,
        T__58       = 59,
        T__59       = 60,
        T__60       = 61,
        T__61       = 62,
        T__62       = 63,
        T__63       = 64,
        T__64       = 65,
        T__65       = 66,
        T__66       = 67,
        Comment     = 68,
        WhiteSpace  = 69,
        IntLit      = 70,
        FloatLit    = 71,
        StringLit   = 72,
        GlobalIdent = 73,
        LocalIdent  = 74,
        LabelIdent  = 75,
        IntType     = 76
    };

    enum {
        RuleCompilationUnit      = 0,
        RuleTopLevelEntity       = 1,
        RuleGlobalDecl           = 2,
        RuleGlobalDef            = 3,
        RuleImmutable            = 4,
        RuleFuncDecl             = 5,
        RuleFuncDef              = 6,
        RuleFuncHeader           = 7,
        RuleFuncBody             = 8,
        RuleBasicBlock           = 9,
        RuleInstruction          = 10,
        RuleTerminator           = 11,
        RuleLocalDefInst         = 12,
        RuleMathInstruction      = 13,
        RuleValueInstruction     = 14,
        RuleStoreInst            = 15,
        RuleAllocaInst           = 16,
        RuleLoadInst             = 17,
        RuleGetElementPtrInst    = 18,
        RuleBitCastInst          = 19,
        RuleZExtInst             = 20,
        RuleSExtInst             = 21,
        RuleSiToFpInst           = 22,
        RuleFpToSiInst           = 23,
        RuleICmpInst             = 24,
        RuleFCmpInst             = 25,
        RuleCallInst             = 26,
        RuleRetTerm              = 27,
        RuleBrTerm               = 28,
        RuleCondBrTerm           = 29,
        RuleFloatType            = 30,
        RuleConcreteType         = 31,
        RuleValue                = 32,
        RuleConstant             = 33,
        RuleBoolConst            = 34,
        RuleIntConst             = 35,
        RuleFloatConst           = 36,
        RuleArrayConst           = 37,
        RuleType                 = 38,
        RuleIntType              = 39,
        RulePointerType          = 40,
        RuleLabelType            = 41,
        RuleArrayType            = 42,
        RuleNamedType            = 43,
        RuleParams               = 44,
        RuleParam                = 45,
        RuleLabel                = 46,
        RuleIPred                = 47,
        RuleArgs                 = 48,
        RuleArg                  = 49,
        RuleZeroInitializerConst = 50,
        RuleFPred                = 51
    };

    explicit LLVMIRParser(antlr4::TokenStream* input);

    LLVMIRParser(antlr4::TokenStream* input, const antlr4::atn::ParserATNSimulatorOptions& options);

    ~LLVMIRParser() override;

    std::string getGrammarFileName() const override;

    const antlr4::atn::ATN& getATN() const override;

    const std::vector<std::string>& getRuleNames() const override;

    const antlr4::dfa::Vocabulary& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;


    class CompilationUnitContext;
    class TopLevelEntityContext;
    class GlobalDeclContext;
    class GlobalDefContext;
    class ImmutableContext;
    class FuncDeclContext;
    class FuncDefContext;
    class FuncHeaderContext;
    class FuncBodyContext;
    class BasicBlockContext;
    class InstructionContext;
    class TerminatorContext;
    class LocalDefInstContext;
    class MathInstructionContext;
    class ValueInstructionContext;
    class StoreInstContext;
    class AllocaInstContext;
    class LoadInstContext;
    class GetElementPtrInstContext;
    class BitCastInstContext;
    class ZExtInstContext;
    class SExtInstContext;
    class SiToFpInstContext;
    class FpToSiInstContext;
    class ICmpInstContext;
    class FCmpInstContext;
    class CallInstContext;
    class RetTermContext;
    class BrTermContext;
    class CondBrTermContext;
    class FloatTypeContext;
    class ConcreteTypeContext;
    class ValueContext;
    class ConstantContext;
    class BoolConstContext;
    class IntConstContext;
    class FloatConstContext;
    class ArrayConstContext;
    class TypeContext;
    class IntTypeContext;
    class PointerTypeContext;
    class LabelTypeContext;
    class ArrayTypeContext;
    class NamedTypeContext;
    class ParamsContext;
    class ParamContext;
    class LabelContext;
    class IPredContext;
    class ArgsContext;
    class ArgContext;
    class ZeroInitializerConstContext;
    class FPredContext;

    class CompilationUnitContext : public antlr4::ParserRuleContext
    {
    public:
        CompilationUnitContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                      getRuleIndex() const override;
        antlr4::tree::TerminalNode*         EOF();
        std::vector<TopLevelEntityContext*> topLevelEntity();
        TopLevelEntityContext*              topLevelEntity(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    CompilationUnitContext* compilationUnit();

    class TopLevelEntityContext : public antlr4::ParserRuleContext
    {
    public:
        TopLevelEntityContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        GlobalDeclContext* globalDecl();
        GlobalDefContext*  globalDef();
        FuncDeclContext*   funcDecl();
        FuncDefContext*    funcDef();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TopLevelEntityContext* topLevelEntity();

    class GlobalDeclContext : public antlr4::ParserRuleContext
    {
    public:
        GlobalDeclContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* GlobalIdent();
        ImmutableContext*           immutable();
        TypeContext*                type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    GlobalDeclContext* globalDecl();

    class GlobalDefContext : public antlr4::ParserRuleContext
    {
    public:
        GlobalDefContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* GlobalIdent();
        ImmutableContext*           immutable();
        TypeContext*                type();
        ConstantContext*            constant();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    GlobalDefContext* globalDef();

    class ImmutableContext : public antlr4::ParserRuleContext
    {
    public:
        ImmutableContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ImmutableContext* immutable();

    class FuncDeclContext : public antlr4::ParserRuleContext
    {
    public:
        FuncDeclContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        FuncHeaderContext* funcHeader();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FuncDeclContext* funcDecl();

    class FuncDefContext : public antlr4::ParserRuleContext
    {
    public:
        FuncDefContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        FuncHeaderContext* funcHeader();
        FuncBodyContext*   funcBody();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FuncDefContext* funcDef();

    class FuncHeaderContext : public antlr4::ParserRuleContext
    {
    public:
        FuncHeaderContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        TypeContext*                type();
        antlr4::tree::TerminalNode* GlobalIdent();
        ParamsContext*              params();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FuncHeaderContext* funcHeader();

    class FuncBodyContext : public antlr4::ParserRuleContext
    {
    public:
        FuncBodyContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                  getRuleIndex() const override;
        std::vector<BasicBlockContext*> basicBlock();
        BasicBlockContext*              basicBlock(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FuncBodyContext* funcBody();

    class BasicBlockContext : public antlr4::ParserRuleContext
    {
    public:
        BasicBlockContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                   getRuleIndex() const override;
        TerminatorContext*               terminator();
        antlr4::tree::TerminalNode*      LabelIdent();
        std::vector<InstructionContext*> instruction();
        InstructionContext*              instruction(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BasicBlockContext* basicBlock();

    class InstructionContext : public antlr4::ParserRuleContext
    {
    public:
        InstructionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t           getRuleIndex() const override;
        LocalDefInstContext*     localDefInst();
        ValueInstructionContext* valueInstruction();
        StoreInstContext*        storeInst();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    InstructionContext* instruction();

    class TerminatorContext : public antlr4::ParserRuleContext
    {
    public:
        TerminatorContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        RetTermContext*    retTerm();
        BrTermContext*     brTerm();
        CondBrTermContext* condBrTerm();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TerminatorContext* terminator();

    class LocalDefInstContext : public antlr4::ParserRuleContext
    {
    public:
        LocalDefInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* LocalIdent();
        ValueInstructionContext*    valueInstruction();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LocalDefInstContext* localDefInst();

    class MathInstructionContext : public antlr4::ParserRuleContext
    {
    public:
        MathInstructionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        MathInstructionContext() = default;
        void copyFrom(MathInstructionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class SdivInstContext : public MathInstructionContext
    {
    public:
        SdivInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FremInstContext : public MathInstructionContext
    {
    public:
        FremInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AddInstContext : public MathInstructionContext
    {
    public:
        AddInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FsubInstContext : public MathInstructionContext
    {
    public:
        FsubInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FdivInstContext : public MathInstructionContext
    {
    public:
        FdivInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SremInstContext : public MathInstructionContext
    {
    public:
        SremInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class UdivInstContext : public MathInstructionContext
    {
    public:
        UdivInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class UremInstContext : public MathInstructionContext
    {
    public:
        UremInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class MulInstContext : public MathInstructionContext
    {
    public:
        MulInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FaddInstContext : public MathInstructionContext
    {
    public:
        FaddInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SubInstContext : public MathInstructionContext
    {
    public:
        SubInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FmulInstContext : public MathInstructionContext
    {
    public:
        FmulInstContext(MathInstructionContext* ctx);

        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);
        virtual void               enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void               exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    MathInstructionContext* mathInstruction();

    class ValueInstructionContext : public antlr4::ParserRuleContext
    {
    public:
        ValueInstructionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        ValueInstructionContext() = default;
        void copyFrom(ValueInstructionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class MathInstruction_Context : public ValueInstructionContext
    {
    public:
        MathInstruction_Context(ValueInstructionContext* ctx);

        MathInstructionContext* mathInstruction();
        virtual void            enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void            exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AllocaInst_Context : public ValueInstructionContext
    {
    public:
        AllocaInst_Context(ValueInstructionContext* ctx);

        AllocaInstContext* allocaInst();
        virtual void       enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void       exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ICmpInst_Context : public ValueInstructionContext
    {
    public:
        ICmpInst_Context(ValueInstructionContext* ctx);

        ICmpInstContext* iCmpInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SiToFpInst_Context : public ValueInstructionContext
    {
    public:
        SiToFpInst_Context(ValueInstructionContext* ctx);

        SiToFpInstContext* siToFpInst();
        virtual void       enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void       exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class BitCastInst_Context : public ValueInstructionContext
    {
    public:
        BitCastInst_Context(ValueInstructionContext* ctx);

        BitCastInstContext* bitCastInst();
        virtual void        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ZExtInst_Context : public ValueInstructionContext
    {
    public:
        ZExtInst_Context(ValueInstructionContext* ctx);

        ZExtInstContext* zExtInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class CallInst_Context : public ValueInstructionContext
    {
    public:
        CallInst_Context(ValueInstructionContext* ctx);

        CallInstContext* callInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FCmpInst_Context : public ValueInstructionContext
    {
    public:
        FCmpInst_Context(ValueInstructionContext* ctx);

        FCmpInstContext* fCmpInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LoadInst_Context : public ValueInstructionContext
    {
    public:
        LoadInst_Context(ValueInstructionContext* ctx);

        LoadInstContext* loadInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class GEPInst_Context : public ValueInstructionContext
    {
    public:
        GEPInst_Context(ValueInstructionContext* ctx);

        GetElementPtrInstContext* getElementPtrInst();
        virtual void              enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void              exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FpToSiInst_Context : public ValueInstructionContext
    {
    public:
        FpToSiInst_Context(ValueInstructionContext* ctx);

        FpToSiInstContext* fpToSiInst();
        virtual void       enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void       exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SExtInst_Context : public ValueInstructionContext
    {
    public:
        SExtInst_Context(ValueInstructionContext* ctx);

        SExtInstContext* sExtInst();
        virtual void     enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void     exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ValueInstructionContext* valueInstruction();

    class StoreInstContext : public antlr4::ParserRuleContext
    {
    public:
        StoreInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                    getRuleIndex() const override;
        std::vector<ConcreteTypeContext*> concreteType();
        ConcreteTypeContext*              concreteType(size_t i);
        std::vector<ValueContext*>        value();
        ValueContext*                     value(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StoreInstContext* storeInst();

    class AllocaInstContext : public antlr4::ParserRuleContext
    {
    public:
        AllocaInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        TypeContext*         type();
        ConcreteTypeContext* concreteType();
        ValueContext*        value();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AllocaInstContext* allocaInst();

    class LoadInstContext : public antlr4::ParserRuleContext
    {
    public:
        LoadInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        TypeContext*         type();
        ConcreteTypeContext* concreteType();
        ValueContext*        value();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LoadInstContext* loadInst();

    class GetElementPtrInstContext : public antlr4::ParserRuleContext
    {
    public:
        GetElementPtrInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                    getRuleIndex() const override;
        TypeContext*                      type();
        std::vector<ConcreteTypeContext*> concreteType();
        ConcreteTypeContext*              concreteType(size_t i);
        std::vector<ValueContext*>        value();
        ValueContext*                     value(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    GetElementPtrInstContext* getElementPtrInst();

    class BitCastInstContext : public antlr4::ParserRuleContext
    {
    public:
        BitCastInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();
        TypeContext*         type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BitCastInstContext* bitCastInst();

    class ZExtInstContext : public antlr4::ParserRuleContext
    {
    public:
        ZExtInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();
        TypeContext*         type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ZExtInstContext* zExtInst();

    class SExtInstContext : public antlr4::ParserRuleContext
    {
    public:
        SExtInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();
        TypeContext*         type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SExtInstContext* sExtInst();

    class SiToFpInstContext : public antlr4::ParserRuleContext
    {
    public:
        SiToFpInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();
        TypeContext*         type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SiToFpInstContext* siToFpInst();

    class FpToSiInstContext : public antlr4::ParserRuleContext
    {
    public:
        FpToSiInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();
        TypeContext*         type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FpToSiInstContext* fpToSiInst();

    class ICmpInstContext : public antlr4::ParserRuleContext
    {
    public:
        ICmpInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        IPredContext*              iPred();
        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ICmpInstContext* iCmpInst();

    class FCmpInstContext : public antlr4::ParserRuleContext
    {
    public:
        FCmpInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        FPredContext*              fPred();
        ConcreteTypeContext*       concreteType();
        std::vector<ValueContext*> value();
        ValueContext*              value(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FCmpInstContext* fCmpInst();

    class CallInstContext : public antlr4::ParserRuleContext
    {
    public:
        CallInstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        TypeContext*   type();
        ValueContext*  value();
        ArgsContext*   args();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    CallInstContext* callInst();

    class RetTermContext : public antlr4::ParserRuleContext
    {
    public:
        RetTermContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    RetTermContext* retTerm();

    class BrTermContext : public antlr4::ParserRuleContext
    {
    public:
        BrTermContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        LabelContext*  label();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BrTermContext* brTerm();

    class CondBrTermContext : public antlr4::ParserRuleContext
    {
    public:
        CondBrTermContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IntType();
        ValueContext*               value();
        std::vector<LabelContext*>  label();
        LabelContext*               label(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    CondBrTermContext* condBrTerm();

    class FloatTypeContext : public antlr4::ParserRuleContext
    {
    public:
        FloatTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FloatTypeContext* floatType();

    class ConcreteTypeContext : public antlr4::ParserRuleContext
    {
    public:
        ConcreteTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t      getRuleIndex() const override;
        IntTypeContext*     intType();
        FloatTypeContext*   floatType();
        PointerTypeContext* pointerType();
        LabelTypeContext*   labelType();
        ArrayTypeContext*   arrayType();
        NamedTypeContext*   namedType();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ConcreteTypeContext* concreteType();

    class ValueContext : public antlr4::ParserRuleContext
    {
    public:
        ValueContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        ConstantContext*            constant();
        antlr4::tree::TerminalNode* LocalIdent();
        antlr4::tree::TerminalNode* GlobalIdent();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ValueContext* value();

    class ConstantContext : public antlr4::ParserRuleContext
    {
    public:
        ConstantContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t               getRuleIndex() const override;
        BoolConstContext*            boolConst();
        IntConstContext*             intConst();
        FloatConstContext*           floatConst();
        ArrayConstContext*           arrayConst();
        ZeroInitializerConstContext* zeroInitializerConst();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ConstantContext* constant();

    class BoolConstContext : public antlr4::ParserRuleContext
    {
    public:
        BoolConstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BoolConstContext* boolConst();

    class IntConstContext : public antlr4::ParserRuleContext
    {
    public:
        IntConstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IntLit();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IntConstContext* intConst();

    class FloatConstContext : public antlr4::ParserRuleContext
    {
    public:
        FloatConstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* FloatLit();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FloatConstContext* floatConst();

    class ArrayConstContext : public antlr4::ParserRuleContext
    {
    public:
        ArrayConstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                    getRuleIndex() const override;
        std::vector<ConcreteTypeContext*> concreteType();
        ConcreteTypeContext*              concreteType(size_t i);
        std::vector<ConstantContext*>     constant();
        ConstantContext*                  constant(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArrayConstContext* arrayConst();

    class TypeContext : public antlr4::ParserRuleContext
    {
    public:
        TypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t    getRuleIndex() const override;
        IntTypeContext*   intType();
        LabelTypeContext* labelType();
        ArrayTypeContext* arrayType();
        NamedTypeContext* namedType();
        TypeContext*      type();
        ParamsContext*    params();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TypeContext* type();
    TypeContext* type(int precedence);
    class IntTypeContext : public antlr4::ParserRuleContext
    {
    public:
        IntTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IntType();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IntTypeContext* intType();

    class PointerTypeContext : public antlr4::ParserRuleContext
    {
    public:
        PointerTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        TypeContext*   type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    PointerTypeContext* pointerType();

    class LabelTypeContext : public antlr4::ParserRuleContext
    {
    public:
        LabelTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LabelTypeContext* labelType();

    class ArrayTypeContext : public antlr4::ParserRuleContext
    {
    public:
        ArrayTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IntLit();
        TypeContext*                type();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArrayTypeContext* arrayType();

    class NamedTypeContext : public antlr4::ParserRuleContext
    {
    public:
        NamedTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* LocalIdent();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    NamedTypeContext* namedType();

    class ParamsContext : public antlr4::ParserRuleContext
    {
    public:
        ParamsContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        std::vector<ParamContext*> param();
        ParamContext*              param(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParamsContext* params();

    class ParamContext : public antlr4::ParserRuleContext
    {
    public:
        ParamContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        TypeContext*                type();
        antlr4::tree::TerminalNode* LocalIdent();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParamContext* param();

    class LabelContext : public antlr4::ParserRuleContext
    {
    public:
        LabelContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* LocalIdent();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LabelContext* label();

    class IPredContext : public antlr4::ParserRuleContext
    {
    public:
        IPredContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IPredContext* iPred();

    class ArgsContext : public antlr4::ParserRuleContext
    {
    public:
        ArgsContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t           getRuleIndex() const override;
        std::vector<ArgContext*> arg();
        ArgContext*              arg(size_t i);

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArgsContext* args();

    class ArgContext : public antlr4::ParserRuleContext
    {
    public:
        ArgContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        ConcreteTypeContext* concreteType();
        ValueContext*        value();

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArgContext* arg();

    class ZeroInitializerConstContext : public antlr4::ParserRuleContext
    {
    public:
        ZeroInitializerConstContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ZeroInitializerConstContext* zeroInitializerConst();

    class FPredContext : public antlr4::ParserRuleContext
    {
    public:
        FPredContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FPredContext* fPred();


    bool sempred(antlr4::RuleContext* _localctx, size_t ruleIndex, size_t predicateIndex) override;

    bool typeSempred(TypeContext* _localctx, size_t predicateIndex);

    // By default the static state used to implement the parser is lazily initialized during the
    // first call to the constructor. You can call this function if you wish to initialize the
    // static state ahead of time.
    static void initialize();

private:
};
