//
// Created by gao on 6/29/23.
//

#ifndef SYSYLEX_IRTYPES_H
#define SYSYLEX_IRTYPES_H
#include <memory>
#include <any>
#include <utility>
#include <vector>
#include <stack>
#include <sstream>
using std::any_cast;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::stack;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

#define MS make_shared
#define MU make_unique

#define ACS(_ST, _TARG) std::any_cast<shared_ptr<_ST>>((_TARG))
#define DPC(_ST, _TARG) std::dynamic_pointer_cast<_ST>((_TARG))

#define VT_INT IRCtrl::IRValType::Int
#define VT_FLOAT IRCtrl::IRValType::Float

namespace IRCtrl
{

enum class IRValType {
    Unknown,
    Func,
    Int,
    Float,
    Arr,
    Void,
    Pointer,
    FloatArr,   // compatibility
    IntArr,     // compatibility
    Bool,
};

enum class IRValOp { Add, Sub, Mul, Div, Rem };

enum class ICMPOp {EQ, NE, UGT, UGE, ULT, ULE, SGT, SGE, SLT, SLE};

/*
 * false: always yields false, regardless of operands.
oeq: yields true if both operands are not a QNAN and op1 is equal to op2.
ogt: yields true if both operands are not a QNAN and op1 is greater than op2.
oge: yields true if both operands are not a QNAN and op1 is greater than or equal to op2.
olt: yields true if both operands are not a QNAN and op1 is less than op2.
ole: yields true if both operands are not a QNAN and op1 is less than or equal to op2.
one: yields true if both operands are not a QNAN and op1 is not equal to op2.
ord: yields true if both operands are not a QNAN.
ueq: yields true if either operand is a QNAN or op1 is equal to op2.
ugt: yields true if either operand is a QNAN or op1 is greater than op2.
uge: yields true if either operand is a QNAN or op1 is greater than or equal to op2.
ult: yields true if either operand is a QNAN or op1 is less than op2.
ule: yields true if either operand is a QNAN or op1 is less than or equal to op2.
une: yields true if either operand is a QNAN or op1 is not equal to op2.
uno: yields true if either operand is a QNAN.
true: always yields true, regardless of operands.
 */
enum class FCMPOp { False, OEQ, OGT, OGE, OLT, OLE, ONE, ORD, UEQ, UGT, UGE, ULT, ULE, UNE, UNO, True };

class IPrintable
{
public:
    virtual string toString() = 0;
};

/// Used for Functions FParams, Defines
class IRType : public IPrintable
{
public:
    IRValType type = IRValType::Unknown;
    explicit IRType(IRValType t)
        : type(t)
    {
    }
    bool operator==(const IRValType& _t) const { return type == _t; }
    bool operator!=(const IRValType& _t) const { return type != _t; }
    string toString() override { return {}; }
};
using SPType = shared_ptr<IRType>;
using UPType = unique_ptr<IRType>;

class IntType : public IRType
{
public:
    IntType()
        : IRType(IRValType::Int)
    {
    }
    string toString() override;
};

class BoolType : public IRType
{
public:
    BoolType()
        : IRType(IRValType::Bool)
    {
    }
    string toString() override;
};

class FloatType : public IRType
{
public:
    FloatType()
        : IRType(IRValType::Float)
    {
    }
    string toString() override;
};

class ArrayType : public IRType
{
public:
    explicit ArrayType(const IRValType& inner, vector<size_t> shape)
        : IRType(IRValType::Arr)
        , innerType(inner)
        , innerShape(std::move(shape))
    {
    }
    IRValType      innerType;
    vector<size_t> innerShape;
    string         toString() override;
};
class FuncType : public IRType
{
public:
    explicit FuncType(IRValType retT, const vector<SPType>& paramsT)
        : IRType(IRValType::Func)
        , retType(retT)
    {
        for (auto& x : paramsT) paramsType.emplace_back(x);
    }
    IRValType      retType;
    vector<SPType> paramsType;
    string         toString() override;
};
class VoidType : public IRType
{
public:
    VoidType()
        : IRType(IRValType::Void)
    {
    }
    string toString() override;
};
class PointerType : public IRType
{
public:
    explicit PointerType(SPType target)
        : IRType(IRValType::Pointer)
        , targetType(std::move(target))
    {
    }

    SPType targetType;
    [[nodiscard]] const SPType& getTargetType() const;

    string toString() override;
};

/// make an IRType from IRValType. Must check nullptr.
/// \param _t IRValType
/// \return `nullptr` or target type.
SPType makeType(IRValType _t);

SPType makePointer(const SPType& _t, size_t stars);

SPType makePointer(const SPType& _t);

}   // namespace IRCtrl

#endif   // SYSYLEX_IRTYPES_H
