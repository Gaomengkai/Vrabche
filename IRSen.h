//
// Created by gao on 6/26/23.
//

#ifndef SYSYLEX_IRSEN_H
#define SYSYLEX_IRSEN_H

#include <string>
#include <utility>
#include "IRTypes.h"
#include "IRVal.h"

namespace IRCtrl
{
enum class IROp {
    // INT
    ADD = 100,
    SUB,
    MUL,
    SDIV,
    SREM,
    UDIV,
    UREM,
    // FLOAT
    FADD,
    FSUB,
    FMUL,
    FDIV,
    FNEG,
    // LOGICAL
    SHL,
    LSHR,
    ASHR,
    AND,
    OR,
    XOR,
    // MEM
    ALLOCA,
    LOAD,
    STORE,
    GETELEMENTPTR,
    // CONTROL
    RET,
    BR,
    CALL,
    // CONVERT INT <-> FLOAT AND EXPAND
    ZEXT,
    SITOFP,
    FPTOSI,
    BITCAST,
    // COMPARE
    ICMP,
    FCMP,

    // MISC
    PHI = 200,

    // DONTMIND
    UNKNOWN = 114514
};

class IRSen
{
public:
    IRSen() = default;
    explicit IRSen(string name)
        : name(std::move(name))
    {
    }
    std::string         name;
    virtual std::string toString() = 0;

protected:
    IROp _op = IROp::UNKNOWN;

public:
    [[nodiscard]] IROp getOp() const;
};

class ConstSen : public IRSen
{
public:
    std::string toString() override;
};

/// Global Val: Including i32/float global single/array. Excluding func def.
class GlobalValDeclSen : public IRSen
{
public:
    shared_ptr<NumberVal> val;
    GlobalValDeclSen(const std::string& name, const shared_ptr<NumberVal>& val)
        : IRSen(name)
        , val(val)
    {
    }
    string toString() override;
};

class LocalSen : public IRSen
{

public:
    string toString() override;

    shared_ptr<IRType> _retType = makeType(IRValType::Void);
    string             _label;   // -> %3 <- = addi %2, 1
};
using UPLocalSen = unique_ptr<LocalSen>;
using SPLocalSen = shared_ptr<LocalSen>;

class AllocaSen : public LocalSen
{
public:
    AllocaSen(string lv, SPType irType1)
        : irType(std::move(irType1))
        , m_lv(std::move((lv)))
    {
        _op      = IROp::ALLOCA;
        _retType = makePointer(irType);
    }

protected:
    SPType irType;
    string m_lv;

public:
    string toString() override;
};

class ReturnSen : public LocalSen
{
public:
    ReturnSen(string lv, SPType irType1)
        : irType(std::move(irType1))
        , m_lv(std::move((lv)))
    {
        _op = IROp::RET;
    }

protected:
    SPType irType;
    string m_lv;

public:
    string toString() override;
};

class LoadSen : public LocalSen
{
public:
    LoadSen(string retLabel, SPType ty, string sourceName_)
        : sourceName(std::move(sourceName_))
        , irType(std::move(ty))
    {
        _label   = std::move(retLabel);
        _retType = irType;
        _op      = IROp::LOAD;
    }

    string toString() override;

protected:
    SPType irType;
    string sourceName;
};

class StoreSen : public LocalSen
{
public:
    StoreSen(string targetLabel, SPType ty, string sourceName_)
        : sourceName(std::move(sourceName_))
        , irType(std::move(ty))
    {
        _label = std::move(targetLabel);
        _op    = IROp::STORE;
    }

    string toString() override;

protected:
    SPType irType;
    string sourceName;
};

/// %v16 = sitofp i32 5 to float
class SiToFpSen : public LocalSen
{
public:
    SiToFpSen(string retLabel, SPType ty, string sourceName_)
        : sourceName(std::move(sourceName_))
    {
        _label   = std::move(retLabel);
        _retType = std::move(ty);
        _op      = IROp::SITOFP;
    }

    string toString() override;

protected:
    string sourceName;
};

class FpToSiSen : public LocalSen
{
public:
    FpToSiSen(string retLabel, SPType ty, string sourceName_)
        : sourceName(std::move(sourceName_))
    {
        _label   = std::move(retLabel);
        _retType = std::move(ty);
        _op      = IROp::FPTOSI;
    }

    string toString() override;

protected:
    string sourceName;
};

class BiSen : public LocalSen
{
public:
    BiSen(string outLabel, IROp op_, string v1_, SPType ty, string v2_)
        : v1(std::move(v1_))
        , v2(std::move(v2_))
    {
        _label   = std::move(outLabel);
        _retType = std::move(ty);
        _op      = op_;
    }

    string toString() override;

protected:
    string v1, v2;
};

class GepSen : public LocalSen
{
public:
    GepSen(string outLabel_, SPType t_, string source_, vector<size_t> offset_)
        : t(std::move(t_)),sourceName(std::move(source_))
        , offset(std::move(offset_))
    {
        _label=std::move(outLabel_);setRetType();
    }
    GepSen(string outLabel_, SPType t_, string source_, vector<size_t> offset_, bool dr)
        : t(std::move(t_)),sourceName(std::move(source_))
        , offset(std::move(offset_)), dimensionality_reduction(dr)
    {
        _label=std::move(outLabel_);setRetType();
    }
    GepSen(string outLabel_, SPType t_, string source_, vector<string> offset_str_, bool dr=false)
        : t(std::move(t_)),sourceName(std::move(source_))
        , offset_str(std::move(offset_str_)), dimensionality_reduction(dr)
    {
        _label=std::move(outLabel_);setRetType();
    }
    string toString() override;

protected:
    SPType      t;
    vector<size_t> offset;
    vector<string> offset_str;
    string sourceName;
    bool dimensionality_reduction = false;
    void setRetType();
};

// declare void @llvm.memset.p0.i32(ptr, i8, i32, i1)
class Memset: public LocalSen {
public:
    Memset(string retLabel_, string sourceLabel, shared_ptr<IRType> pt_, unsigned char x_, int bytes_):
    pt(std::move(pt_)),sourceName(std::move(sourceLabel)),
        x(x_), bytes(bytes_){_label=std::move(retLabel_);}
protected:
    shared_ptr<IRType> pt;
    unsigned char x;
    int bytes;
    string sourceName;

public:
    string toString() override;
};

//   %v13 = call i32 @foo3([8 x [8 x i32]]* %v12)
//   %v6 = call i32 @foo2(i32* %v5)
//   %v3 = call i32 @foo1(i32 %v2)
class CallSen : public LocalSen
{
public:
    CallSen(string outLabel_, string funcName_, IRValType retType_, vector<SPType> argTypes,
            vector<string> argNames)
        : funcName(std::move(funcName_))
        , retType(retType_)
        , argTypes(std::move(argTypes))
        , argNames(std::move(argNames))
    {
        _label   = std::move(outLabel_);
        _retType = makeType(retType_);
        _op      = IROp::CALL;
    }

    string toString() override;
protected:
    string funcName;
    IRValType retType;
    vector<SPType> argTypes;
    vector<string> argNames;
};

// br i1 %v3, label %5, label %6
// br label %7
class BrSen : public LocalSen
{
public:
    BrSen(string cond_, string trueLabel_, string falseLabel_)
        : cond(std::move(cond_))
        , trueLabel(std::move(trueLabel_))
        , falseLabel(std::move(falseLabel_))
    {
        _op = IROp::BR;
        brType=BrType::COND;
    }

    BrSen(string trueLabel_)
        : trueLabel(std::move(trueLabel_))
    {
        _op = IROp::BR;
        brType=BrType::UNCOND;
    }
protected:
    string cond, trueLabel, falseLabel;

    // br type: conditional or unconditional
    enum class BrType
    {
        COND,
        UNCOND
    } brType;

public:
    string toString() override;
};

// https://llvm.org/docs/LangRef.html#icmp-instruction
// <result> = icmp <cond> <ty> <op1>, <op2>   ; yields i1 or <N x i1>:result
class IcmpSen : public LocalSen
{
public:
    IcmpSen(string outLabel_, ICMPOp cond_, string op1_, string op2_)
        : cond(cond_), op1(std::move(op1_)), op2(std::move(op2_))
    {
        _label   = std::move(outLabel_);
        _op      = IROp::ICMP;
        _retType = makeType(IRValType::Bool);
    }

protected:
    string op1, op2;
    ICMPOp cond;

public:
    string toString() override;
};

class FcmpSen : public LocalSen
{
public:
    FcmpSen(string outLabel_, FCMPOp cond_, string op1_, string op2_)
        : cond(cond_), op1(std::move(op1_)), op2(std::move(op2_))
    {
        _label   = std::move(outLabel_);
        _op      = IROp::FCMP;
        _retType = makeType(IRValType::Bool);
    }

protected:
    string op1, op2;
    FCMPOp cond;

public:
    string toString() override;
};

class ZextSen : public LocalSen
{
public:
    ZextSen(string outLabel_, string source_, IRValType from_)
        : sourceName(std::move(source_)), from(from_)
    {
        _label   = std::move(outLabel_);
        _op      = IROp::ZEXT;
        _retType = makeType(IRValType::Int);
    }

protected:
    string sourceName;
    IRValType from;

public:
    string toString() override;
};

// tool functions:
static string opToStr(IROp op_);
bool isTerminal(const IRSen& sen);
}   // namespace IRCtrl


#endif   // SYSYLEX_IRSEN_H
