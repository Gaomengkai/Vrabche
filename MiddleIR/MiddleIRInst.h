//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_MIDDLEIRINST_H
#define IRBACKENDR5_MIDDLEIRINST_H

#include <utility>
#include <set>

#include "MiddleIRType.h"
#include "MiddleIRVal.h"
#include "MiddleIRFuncDecl.h"
namespace MiddleIR
{

class MiddleIRInst : public MiddleIRVal
{
public:
    enum InstType {
        AllocaInst,
        ReturnInst,
        BrInst,
        IMathInst,
        FMathInst,
        ICmpInst,
        FCmpInst,
        LoadInst,
        StoreInst,
        BitCastInst,
        GetElementPtrInst,
        ConvertInst,
        CallInst
    } _instType;
    explicit MiddleIRInst(InstType instType_, SPType retType_)
        : _instType(instType_)
        , MiddleIRVal(std::move(retType_))
    {
    }
    inline static bool isAllocaInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::AllocaInst;
    }
    inline static bool isReturnInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::ReturnInst;
    }
    inline static bool isBrInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::BrInst;
    }
    inline static bool isTerminatorInst(const MiddleIRInst& inst)
    {
        return isReturnInst(inst) || isBrInst(inst);
    }
    inline static bool isIMathInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::IMathInst;
    }
    inline static bool isFMathInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::FMathInst;
    }
    inline static bool isMathInst(const MiddleIRInst& inst)
    {
        return isIMathInst(inst) || isFMathInst(inst);
    }
    inline static bool isLoadInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::LoadInst;
    }
    inline static bool isStoreInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::StoreInst;
    }
    inline static bool isBitCastInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::BitCastInst;
    }
    inline static bool isGetElementPtrInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::GetElementPtrInst;
    }
    inline static bool isICmpInst(const MiddleIRInst& inst)
    {
        return inst._instType == InstType::ICmpInst;
    }

    // object method
    [[nodiscard]] inline bool isAllocaInst() const { return _instType == InstType::AllocaInst; }
    [[nodiscard]] inline bool isReturnInst() const { return _instType == InstType::ReturnInst; }
    [[nodiscard]] inline bool isBrInst() const { return _instType == InstType::BrInst; }
    [[nodiscard]] inline bool isTerminatorInst() const { return isReturnInst() || isBrInst(); }
    [[nodiscard]] inline bool isIMathInst() const { return _instType == InstType::IMathInst; }
    [[nodiscard]] inline bool isFMathInst() const { return _instType == InstType::FMathInst; }
    [[nodiscard]] inline bool isMathInst() const { return isIMathInst() || isFMathInst(); }
    [[nodiscard]] inline bool isLoadInst() const { return _instType == InstType::LoadInst; }
    [[nodiscard]] inline bool isStoreInst() const { return _instType == InstType::StoreInst; }
    [[nodiscard]] inline bool isBitCastInst() const { return _instType == InstType::BitCastInst; }
    [[nodiscard]] inline bool isICmpInst() const { return _instType == InstType::ICmpInst; }
    [[nodiscard]] inline bool isFCmpInst() const { return _instType == InstType::FCmpInst; }
    [[nodiscard]] inline bool isConvertInst() const { return _instType == InstType::ConvertInst; }
    [[nodiscard]] inline bool isCallInst() const { return _instType == InstType::CallInst; }
    [[nodiscard]] inline bool isGetElementPtrInst() const
    {
        return _instType == InstType::GetElementPtrInst;
    }
    [[nodiscard]] InstType getInstType() const { return _instType; }

    // virtual destructor
    ~MiddleIRInst() override = default;

    // use
    bool tryReplaceUse(
        const std::shared_ptr<MiddleIRVal>& oldVal, const std::shared_ptr<MiddleIRVal>& newVal
    );
    [[nodiscard]] std::vector<shared_ptr<MiddleIRVal>*> getUseList() const { return _useList; }


protected:
    std::vector<shared_ptr<MiddleIRVal>*> _useList;
    bool                                  _deleted = false;

public:
    [[nodiscard]] bool isDeleted() const;
    void               setDeleted(bool deleted);

private:
    bool   mustAddFirst  = false;
    size_t lastRemovePos = -1;
};

class AllocaInst : public MiddleIRInst
{
private:
public:
    AllocaInst(std::string name_, const SPType& type_)
        : MiddleIRInst(InstType::AllocaInst, std::move(makePointer(type_)))
    {
        _name = std::move(name_);
    }
};

class ReturnInst : public MiddleIRInst
{
private:
    SPType                       _opType;
    std::shared_ptr<MiddleIRVal> _opVal;

public:
    ReturnInst(SPType opType_, std::shared_ptr<MiddleIRVal> opVal_)
        : MiddleIRInst(InstType::ReturnInst, opType_)
        , _opType(std::move(opType_))
        , _opVal(std::move(opVal_))
    {
        _useList.emplace_back(&_opVal);
    }
    [[nodiscard]] const SPType&                       getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal() const { return _opVal; }
    [[nodiscard]] MiddleIRType::IRType getAtomRetType() const { return _opType->type; }
};

class ICmpInst : public MiddleIRInst
{
public:
    enum ICmpOp { EQ, NE, SGT, SGE, SLT, SLE, UGE, UGT, ULE, ULT } iCmpOp;
    [[nodiscard]] ICmpOp getICmpOp() const { return iCmpOp; }
    ICmpInst(
        ICmpOp                       iMathOp_,
        SPType                       opType_,
        std::shared_ptr<MiddleIRVal> opVal1_,
        std::shared_ptr<MiddleIRVal> opVal2_
    )
        : MiddleIRInst(InstType::ICmpInst, spBoolType)
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , iCmpOp(iMathOp_)
    {
        _useList.emplace_back(&_opVal1);
        _useList.emplace_back(&_opVal2);
    }
    [[nodiscard]] const SPType&                       getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal2() const { return _opVal2; }
    static ICmpOp                                     fromString(const string& op_)
    {
        if (op_ == "eq") return ICmpOp::EQ;
        if (op_ == "ne") return ICmpOp::NE;
        if (op_ == "sgt") return ICmpOp::SGT;
        if (op_ == "sge") return ICmpOp::SGE;
        if (op_ == "slt") return ICmpOp::SLT;
        if (op_ == "sle") return ICmpOp::SLE;
        if (op_ == "uge") return ICmpOp::UGE;
        if (op_ == "ugt") return ICmpOp::UGT;
        if (op_ == "ule") return ICmpOp::ULE;
        if (op_ == "ult") return ICmpOp::ULT;
        IR_ASSERT(false, "invalid ICmpOp: " << op_);
    }

private:
    SPType                       _opType;
    std::shared_ptr<MiddleIRVal> _opVal1;
    std::shared_ptr<MiddleIRVal> _opVal2;
};

class FCmpInst : public MiddleIRInst
{
public:
    // clang-format off
    enum class FCmpOp { FALSE, OEQ, OGE, OGT, OLE, OLT, TRUE, UEQ, UGE, UGT, ULE, ULT, UNE, UNO} fCmpOp;
    // clang-format on
    FCmpInst(
        FCmpOp                       fMathOp_,
        SPType                       opType_,
        std::shared_ptr<MiddleIRVal> opVal1_,
        std::shared_ptr<MiddleIRVal> opVal2_
    )
        : MiddleIRInst(InstType::FCmpInst, spBoolType)
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , fCmpOp(fMathOp_)
    {
        _useList.emplace_back(&_opVal1);
        _useList.emplace_back(&_opVal2);
    }
    static FCmpOp fromString(const string& op_)
    {
        if (op_ == "false") return FCmpOp::FALSE;
        if (op_ == "oeq") return FCmpOp::OEQ;
        if (op_ == "oge") return FCmpOp::OGE;
        if (op_ == "ogt") return FCmpOp::OGT;
        if (op_ == "ole") return FCmpOp::OLE;
        if (op_ == "olt") return FCmpOp::OLT;
        if (op_ == "true") return FCmpOp::TRUE;
        if (op_ == "ueq") return FCmpOp::UEQ;
        if (op_ == "uge") return FCmpOp::UGE;
        if (op_ == "ugt") return FCmpOp::UGT;
        if (op_ == "ule") return FCmpOp::ULE;
        if (op_ == "ult") return FCmpOp::ULT;
        if (op_ == "une") return FCmpOp::UNE;
        if (op_ == "uno") return FCmpOp::UNO;
        IR_ASSERT(false, "invalid FCmpOp: " << op_);
    }

private:
    SPType                       _opType;
    std::shared_ptr<MiddleIRVal> _opVal1;
    std::shared_ptr<MiddleIRVal> _opVal2;

public:
    [[nodiscard]] const shared_ptr<MiddleIRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const shared_ptr<MiddleIRVal>& getOpVal2() const { return _opVal2; }
    [[nodiscard]] FCmpOp                         getFCmpOp() const { return fCmpOp; }
};

class LoadInst : public MiddleIRInst
{
public:
    LoadInst(const std::shared_ptr<MiddleIRVal>& from_, SPType type_)
        : MiddleIRInst(InstType::LoadInst, std::move(type_))
        , _from(from_)
    {
        _useList.emplace_back(&_from);
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal() const { return _from; }

protected:
    std::shared_ptr<MiddleIRVal> _from;

public:
    [[nodiscard]] const shared_ptr<MiddleIRVal>& getFrom() const { return _from; }
};

class StoreInst : public MiddleIRInst
{
public:
    StoreInst(shared_ptr<MiddleIRVal> from_, shared_ptr<MiddleIRVal> to_)
        : MiddleIRInst(InstType::StoreInst, spVoidType)
        , _from(std::move(from_))
        , _to(std::move(to_))
    {
        _useList.emplace_back(&_from);
        _useList.emplace_back(&_to);
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal1() const { return _from; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal2() const { return _to; }

protected:
    std::shared_ptr<MiddleIRVal> _from;
    std::shared_ptr<MiddleIRVal> _to;

public:
    [[nodiscard]] const shared_ptr<MiddleIRVal>& getTo() const { return _to; }
    [[nodiscard]] const shared_ptr<MiddleIRVal>& getFrom() const { return _from; }
};

class IMathInst : public MiddleIRInst
{
public:
    enum class IMathOp { ADD, SUB, MUL, SDIV, SREM, UDIV, UREM } iMathOp;
    [[nodiscard]] IMathOp getIMathOp() const { return iMathOp; }
    IMathInst(
        IMathOp                      iMathOp_,
        SPType                       opType_,
        std::shared_ptr<MiddleIRVal> opVal1_,
        std::shared_ptr<MiddleIRVal> opVal2_
    )
        : MiddleIRInst(InstType::IMathInst, std::move(opType_))
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , iMathOp(iMathOp_)
    {
        _useList.emplace_back(&_opVal1);
        _useList.emplace_back(&_opVal2);
    }
    [[nodiscard]] const SPType&                       getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal2() const { return _opVal2; }

protected:
    SPType                       _opType;
    std::shared_ptr<MiddleIRVal> _opVal1;
    std::shared_ptr<MiddleIRVal> _opVal2;
};
class FMathInst : public MiddleIRInst
{
public:
    enum FMathOp { FADD, FSUB, FMUL, FDIV, FREM } fMathOp;
    FMathOp getFMathOp() const { return fMathOp; }
    FMathInst(
        FMathOp                      fMathOp_,
        SPType                       opType_,
        std::shared_ptr<MiddleIRVal> opVal1_,
        std::shared_ptr<MiddleIRVal> opVal2_
    )
        : MiddleIRInst(InstType::FMathInst, std::move(opType_))
        , _opType(std::move(opType_))
        , _opVal1(std::move(opVal1_))
        , _opVal2(std::move(opVal2_))
        , fMathOp(fMathOp_)
    {
        _useList.emplace_back(&_opVal1);
        _useList.emplace_back(&_opVal2);
    }
    [[nodiscard]] const SPType&                       getOpType() const { return _opType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal1() const { return _opVal1; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getOpVal2() const { return _opVal2; }

protected:
    SPType                       _opType;
    std::shared_ptr<MiddleIRVal> _opVal1;
    std::shared_ptr<MiddleIRVal> _opVal2;
};

class BitCastInst : public MiddleIRInst
{
public:
    BitCastInst(SPType fromType_, std::shared_ptr<MiddleIRVal> from_, SPType toType_)
        : MiddleIRInst(InstType::BitCastInst, std::move(toType_))
        , _fromType(std::move(fromType_))
        , _toType(std::move(toType_))
        , _from(std::move(from_))
    {
        _useList.emplace_back(&_from);
    }
    [[nodiscard]] const SPType&                       getFromType() const { return _fromType; }
    [[nodiscard]] const SPType&                       getToType() const { return _toType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getFrom() const { return _from; }

protected:
    SPType                       _fromType;
    SPType                       _toType;
    std::shared_ptr<MiddleIRVal> _from;
};

class CallInst : public MiddleIRInst
{
public:
    CallInst(
        std::shared_ptr<MiddleIRFuncDecl>         func_,
        std::vector<std::shared_ptr<MiddleIRVal>> args_,
        SPType                                    retType_
    )
        : MiddleIRInst(InstType::CallInst, std::move(retType_))
        , _func(std::move(func_))
        , _args(std::move(args_))
    {
        for (auto& arg : _args) { _useList.emplace_back(&arg); }
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRFuncDecl>&         getFunc() const { return _func; }
    [[nodiscard]] const std::vector<std::shared_ptr<MiddleIRVal>>& getArgs() const { return _args; }
    [[nodiscard]] MiddleIRType::IRType getRetType() const { return _func->getRetType()->type; }

protected:
    std::shared_ptr<MiddleIRFuncDecl>         _func;
    std::vector<std::shared_ptr<MiddleIRVal>> _args;
};

class ConvertInst : public MiddleIRInst
{
    // 'zext' concreteType value 'to' type;
public:
    enum ConvertOp { ZEXT, SEXT, TRUNC, FPTOUI, FPTOSI, UITOFP, SITOFP } convertOp;
    [[nodiscard]] ConvertOp getConvertOp() const { return convertOp; }
    ConvertInst(ConvertOp op_, SPType fromType_, std::shared_ptr<MiddleIRVal> from_, SPType toType_)
        : MiddleIRInst(InstType::ConvertInst, std::move(toType_))
        , _fromType(std::move(fromType_))
        , _toType(std::move(toType_))
        , _from(std::move(from_))
        , convertOp(op_)
    {
        _useList.emplace_back(&_from);
    }
    [[nodiscard]] const SPType&                       getFromType() const { return _fromType; }
    [[nodiscard]] const SPType&                       getToType() const { return _toType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getFrom() const { return _from; }

protected:
    SPType                       _fromType;
    SPType                       _toType;
    std::shared_ptr<MiddleIRVal> _from;
};

// %v4 = getelementptr [3 x i32], [3 x i32]* %v3, i32 114, i32 1
class GetElementPtrInst : public MiddleIRInst
{
public:
    GetElementPtrInst(
        const SPType&                   type1,
        SPType                          fromType,
        shared_ptr<MiddleIRVal>         from,
        vector<shared_ptr<MiddleIRVal>> index
    )
        : MiddleIRInst(InstType::GetElementPtrInst, std::move(spVoidType))
        , _fromType(std::move(fromType))
        , _from(std::move(from))
        , _index(std::move(index))
        , _type1(type1)
    {
        // from must be a pointer.
        IR_ASSERT(_fromType->isPointer(), "GetElementPtrInst: from must be a pointer.");
        auto fromTypePtr = DPC(PointerType, _fromType);
        // from must be a pointer to type1
        IR_ASSERT(
            *fromTypePtr->getElementType() == *type1,
            "GetElementPtrInst: from must be a pointer to type1."
        );
        //   %v3 = getelementptr [114 x [3 x i32]], [114 x [3 x i32]]* %v1, i32 0, i32 0, i32 0
        //  %v4 = getelementptr [114 x [3 x i32]], [114 x [3 x i32]]* %v1, i32 0, i32 0
        // %v4 = getelementptr [3 x i32], [3 x i32]* %v3, i32 114, i32 1
        // %v5 = getelementptr i32, i32* v7, i32 1
        // in case 1, this instruction returns i32*
        // in case 2, it returns [3 x i32]*
        // in case 3, it returns i32*
        // in case 4, it returns i32*
        auto innerType = fromTypePtr->getElementType();
        for (int i = 1; i < _index.size(); ++i) {
            if (innerType->isArray()) {
                auto arrayType = DPC(ArrayType, innerType);
                innerType      = arrayType->getElementType();
            } else if (innerType->isPointer()) {
                auto ptrType = DPC(PointerType, innerType);
                innerType    = ptrType->getElementType();
            } else {
                IR_ASSERT(i == _index.size() - 1, "GetElementPtrInst: invalid index.");
            }
        }
        _type = makePointer(innerType);
        _useList.emplace_back(&_from);
        for (auto& i : _index) {
            if (!dynamic_pointer_cast<R5IRValConst>(i)) { _useList.emplace_back(&i); }
        }
    }
    [[nodiscard]] const SPType&                          getFromType() const { return _fromType; }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>&    getFrom() const { return _from; }
    [[nodiscard]] const vector<shared_ptr<MiddleIRVal>>& getIndex() const { return _index; }
    [[nodiscard]] const SPType&                          getType1() const { return _type1; }

protected:
    SPType                          _fromType;
    std::shared_ptr<MiddleIRVal>    _from;
    vector<shared_ptr<MiddleIRVal>> _index;
    SPType                          _type1;
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRINST_H
