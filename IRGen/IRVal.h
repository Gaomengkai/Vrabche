//
// Created by gao on 6/29/23.
//

#ifndef SYSYLEX_IRVAL_H
#define SYSYLEX_IRVAL_H

#include <string>
#include <utility>
#include <vector>
#include "IRTypes.h"

namespace IRCtrl
{

class IRVal : public IPrintable
{
public:
    std::string   name;
    const string& getName() const;
    void          setName(const string& name);
    const string& getId() const;
    void          setId(const string& id);
    std::string   id;
    IRValType     type;
    SPType        advancedType;   // Only function and array has advancedType

    IRVal()
        : name(std::string(""))
        , type(IRValType::Unknown)
    {
    }

    IRVal(const std::string& name1, IRValType type1)
        : name(std::string(name1))
        , id(string(name1))
        , type(type1)
    {
    }

    explicit IRVal(const std::string& name1)
        : name(std::string(name1))
        , id(string(name1))
        , type(IRValType::Unknown)
    {
    }

    [[nodiscard]] SPType getTrueAdvType() const;
};

class NumberVal : public IRVal
{
public:
    bool isGlobal;
    bool isConst;

    virtual void unary() {}
    virtual void notOp() {}

    explicit NumberVal(const std::string& name1)
        : isConst(false)
        , isGlobal(false)
        , IRVal(name1)
    {
    }
};


/**
 * Const Value, including const int and const float.
 */
class CVal : public NumberVal
{
public:
    explicit CVal(const std::string& name1)
        : NumberVal(name1)
    {
        isConst = true;
    }
};

class IntCVal : public CVal
{
public:
    int iVal{};
    explicit IntCVal(const std::string& name1)
        : CVal(name1)
    {

        type = IRValType::Int;
    }

    IntCVal(const std::string& name1, int val)
        : CVal(name1)
    //        : CVal(name1, val)
    {
        name = name1;
        iVal = val;
        type = IRValType::Int;
    }

    void   unary() override;
    string toString() override;
    void   notOp() override;
};



class FloatCVal : public CVal
{
public:
    float fVal = .0f;
    explicit FloatCVal(const std::string& name1)
        : CVal(name1)
    {
        type = IRValType::Float;
        fVal = 0;
    }

    FloatCVal(const std::string& name1, float val)
        : CVal(name1)
    {
        type = IRValType::Float;
        fVal = val;
    }

    void   unary() override;
    string toString() override;
    void   notOp() override;
};

class InitListVal : public IRVal
{
public:
    enum { INITLIST, CVAL };
    vector<shared_ptr<InitListVal>> initList;
    vector<shared_ptr<CVal>>        cVal;
    vector<decltype(CVAL)>          which;
    IRValType                       contained = IRValType::Unknown;
    string                          toString() override;
    [[nodiscard]] bool              empty() const;
    [[nodiscard]] size_t            dim() const;
};

class CArr : public CVal
{
public:
    enum { CARR, CVAL, ZERO };
    explicit CArr(const string& name1, IRValType contained)
        : CVal(name1)
        , containedType(contained)
    {
        isConst = true;
        type    = IRValType::Arr;
    }
    ~CArr() = default;

    string           toString() override;
    shared_ptr<CVal> access(const vector<int>& indices);

    std::deque<size_t>       _shape;
    bool                     isZero = false;
    vector<shared_ptr<CArr>> _childArrs;
    vector<shared_ptr<CVal>> _childVals;
    vector<decltype(CARR)>   witch;
    IRValType                containedType = IRValType::Float;
    [[maybe_unused]] string shapeString() const;

    static string shapeString(IRValType containedType_, const std::deque<size_t>& shape_);
};

/// No need to init "type" in this constructor.
/// This var will filled by its inherits classes
class VVal : public NumberVal
{
public:
    explicit VVal(const string& name1)
        : NumberVal(name1)
    {
        isConst = false;
    }
    bool hasInit = false;
};

class IntVal : public VVal
{
public:
    int iVal{};
    explicit IntVal(const string& name1)
        : VVal(name1)
    {
        type = IRValType::Int;
    }
    IntVal(const string& name1, int val)
        : IntVal(name1)
    {
        iVal = val;
        type = IRValType::Int;
    }

    string toString() override;
};
class FloatVal : public VVal
{
public:
    float fVal{};
    explicit FloatVal(const string& name1)
        : VVal(name1)
    {
        type = IRValType::Float;
    }
    FloatVal(const string& name1, float val)
        : FloatVal(name1)
    {
        fVal = val;
        type = IRValType::Float;
    }
    string toString() override;
};

class VArr : public VVal
{
public:
    enum { VARR, CVAL, ZERO };
    explicit VArr(const string& name1, IRValType contained)
        : VVal(name1)
        , containedType(contained)
    {
        isConst = false;
        type    = IRValType::Arr;
    }
    explicit VArr(const CArr& fromCArr)
        : VVal(fromCArr.name)
    {
        name = fromCArr.name;
        id = fromCArr.id;
        type = IRValType::Arr;
        containedType = fromCArr.containedType;
        _shape = fromCArr._shape;
        isZero = fromCArr.isZero;
        _childVals = fromCArr._childVals;
        for(const auto& child : fromCArr._childArrs)
        {
            if(child!=nullptr)
            _childArrs.emplace_back(make_shared<VArr>(*child));
            else
                _childArrs.emplace_back(nullptr);
        }
        for(const auto& child : fromCArr.witch)
        {
            witch.emplace_back((decltype(VARR))child);
        }
    }

    string toString() override;

    std::deque<size_t>       _shape;
    bool                     isZero = false;
    vector<decltype(VARR)>   witch;
    vector<shared_ptr<VArr>> _childArrs;
    vector<shared_ptr<CVal>> _childVals;
    IRValType                containedType = IRValType::Float;

protected:
    virtual string shapeString();
};

// in-function vars. not global.
class LocalVar : public IRVal
{
public:
    explicit LocalVar(string _id) { id = std::move(_id); }
};
using SPLocalVar = shared_ptr<LocalVar>;

class LocalInt : public LocalVar
{
public:
    explicit LocalInt(const string& _id)
        : LocalVar(_id)
    {
        type = IRValType::Int;
    }
    LocalInt(const string& _id, const string& _name)
        : LocalVar(_id)
    {
        type = IRValType::Int;
        name = _name;
    }
    string toString() override;
};

class LocalBool : public LocalInt
{
    int iVal{};

    explicit LocalBool(const string& _id)
        : LocalInt(_id)
    {
        type = IRValType::Bool;
    }

    LocalBool(const string& _id, const string& _name)
        : LocalInt(_id)
    {
        type = IRValType::Bool;
        name = _name;
    }

    string toString() override;
};

class LocalFloat : public LocalVar
{
public:
    explicit LocalFloat(const string& _id)
        : LocalVar(_id)
    {
        type = IRValType::Float;
    }
    LocalFloat(const string& _id, const string& _name)
        : LocalVar(_id)
    {
        type = IRValType::Float;
        name = _name;
    }
    string toString() override;
};

/// the var of a function's params
class FPVar : public LocalVar
{
public:
    explicit FPVar(const string& id, const string& name1)
        : LocalVar(id)
    {
        name = name1;
    }
    string toString() override;
    SPType fpType;

    [[nodiscard]] const SPType& getFpType() const;

    void setFpType(const SPType& fpType_);
};
using SPFPVar = shared_ptr<FPVar>;


}   // namespace IRCtrl
#endif   // SYSYLEX_IRVAL_H
