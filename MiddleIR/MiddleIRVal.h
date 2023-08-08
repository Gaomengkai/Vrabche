//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_MIDDLEIRVAL_H
#define IRBACKENDR5_MIDDLEIRVAL_H

#include <utility>
#include <ostream>

#include "MiddleIRType.h"
namespace MiddleIR
{

class MiddleIRVal
{
public:
    MiddleIRVal()          = default;
    virtual ~MiddleIRVal() = default;

protected:
    SPType _type;
    string _name;
    bool   _const = false;

public:
    [[nodiscard]] bool isConst() const { return _const; }
    void               setConst(bool const_) { _const = const_; }

public:
    explicit MiddleIRVal(SPType type)
        : _type(std::move(type))
    {
    }
    MiddleIRVal(SPType type, string name)
        : _type(std::move(type))
        , _name(std::move(name))
    {
    }
    [[nodiscard]] virtual const SPType& getType() const { return _type; }
    [[nodiscard]] shared_ptr<ArrayType> getArrayType() const
    {
        return dynamic_pointer_cast<ArrayType>(_type);
    }
    void                                setType(const SPType& type) { _type = type; }
    [[nodiscard]] virtual const string& getName() const { return _name; }
    void                                setName(const string& name) { _name = name; }
};

class R5IRValConst : public MiddleIRVal
{
public:
    explicit R5IRValConst(SPType type_)
        : MiddleIRVal(std::move(type_))
    {
        setConst(true);
    }
};

class R5IRValConstInt : public R5IRValConst
{
public:
    explicit R5IRValConstInt(int value_)
        : R5IRValConst(spIntType32)
        , _value(value_)
    {
    }
    [[nodiscard]] bool needLUI() const { return _value > 0x7fff || _value < -0x8000; }
    [[nodiscard]] bool isZero() const { return _value == 0; }
    [[nodiscard]] bool inBss() const { return isZero(); }
    [[nodiscard]] int  getWord() const { return _value; }

protected:
    int _value;

public:
    [[nodiscard]] int getValue() const { return _value; }
};
#define IR_INT_CONST(_VAL) std::make_shared<R5IRValConstInt>(_VAL)

// 注意，在前端生成的代码中，根本不会出现一个bool单独的东西，比如true,false
class R5IRValConstI1 : public R5IRValConst
{
public:
    explicit R5IRValConstI1(int value_)
        : R5IRValConst(spBoolType)
        , _value(value_)
    {
    }
    [[nodiscard]] bool needLUI() const { return false; }
    [[nodiscard]] bool isZero() const { return _value == 0; }
    [[nodiscard]] bool inBss() const { return isZero(); }
    [[nodiscard]] int  getWord() const { return _value; }

protected:
    int _value;

public:
    [[nodiscard]] int getValue() const { return _value; }
};
#define IR_BOOL_CONST(_VAL) std::make_shared<R5IRValConstI1>(_VAL)

class R5IRValConstFloat : public R5IRValConst
{
public:
    explicit R5IRValConstFloat(float value_)
        : R5IRValConst(spFloatType)
        , _value(value_)
    {
    }
    explicit R5IRValConstFloat(uint64_t value_)
        : R5IRValConst(spFloatType)
        , _value((float)*reinterpret_cast<double*>(&value_))
    {
    }
    explicit R5IRValConstFloat(double value_)
        : R5IRValConst(spFloatType)
        , _value((float)value_)
    {
    }
    bool     isZero() const { return _value == 0; }
    bool     inBss() const { return isZero(); }
    uint32_t getWord() const { return *(uint32_t*)&_value; }

protected:
    float _value;

public:
    [[nodiscard]] float getValue() const { return _value; }
};
#define IR_FLOAT_CONST(_VAL) std::make_shared<R5IRValConstFloat>(_VAL)

class R5IRArray : public MiddleIRVal
{
public:
    R5IRArray(SPType type_, vector<shared_ptr<MiddleIRVal>> elements_)
        : MiddleIRVal(std::move(type_))
        , _elements(std::move(elements_))
    {
        IR_ASSERT(_type->type == MiddleIRType::ARRAY, "R5IRArray::R5IRArray: type must be ARRAY");
        if (empty()) return;
        IR_ASSERT(
            _elements.size() == dynamic_cast<ArrayType*>(_type.get())->getSize(),
            "R5IRArray::R5IRArray: size not match"
        );
    }
    [[nodiscard]] inline bool empty() const { return _elements.empty(); }
    inline size_t             getSizeBytes() const
    {
        auto arrayType = dynamic_pointer_cast<ArrayType>(_type);
        return arrayType->getSizeBytes();
    }


    vector<shared_ptr<MiddleIRVal>> _elements;
};

class R5IRZeroInitializerVal : public MiddleIRVal
{
public:
    explicit R5IRZeroInitializerVal()
        : MiddleIRVal(spZeroInitializerType)
    {
    }
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRVAL_H
