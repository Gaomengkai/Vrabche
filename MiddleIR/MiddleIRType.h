//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_MIDDLEIRTYPE_H
#define IRBACKENDR5_MIDDLEIRTYPE_H
#include <utility>
#include "R5Logger.h"
#include "R5Def.h"
namespace MiddleIR
{

class MiddleIRType
{
public:
    enum IRType {
        UNKNOWN,
        INT,
        FLOAT,
        VOID,
        ARRAY,
        POINTER,
        FUNCTION,
        LABEL,
        ZEROINITIALIZER
    } type;
    explicit MiddleIRType(IRType type_)
        : type(type_)
    {
    }
    virtual ~MiddleIRType() = default;
    virtual bool operator==(const MiddleIRType& rhs) const
    {
        RUNTIME_ERROR("MiddleIRType::operator== not implemented");
    }
    [[nodiscard]] inline bool isInt() const { return type == INT; }
    [[nodiscard]] inline bool isFloat() const { return type == FLOAT; }
    [[nodiscard]] inline bool isVoid() const { return type == VOID; }
    [[nodiscard]] inline bool isArray() const { return type == ARRAY; }
    [[nodiscard]] inline bool isPointer() const { return type == POINTER; }
    [[nodiscard]] inline bool isFunction() const { return type == FUNCTION; }
    [[nodiscard]] inline bool isLabel() const { return type == LABEL; }
    [[nodiscard]] inline bool isZeroInitializer() const { return type == ZEROINITIALIZER; }
};
using SPType = std::shared_ptr<MiddleIRType>;

class IntType : public MiddleIRType
{
public:
    int bitWidth = 32;

public:
    IntType()
        : MiddleIRType(INT)
    {
    }
    explicit IntType(int bitWidth_)
        : MiddleIRType(INT)
        , bitWidth(bitWidth_)
    {
    }
    bool operator==(const MiddleIRType& rhs) const override
    {
        if (rhs.type == INT) { return bitWidth == dynamic_cast<const IntType&>(rhs).bitWidth; }
        return false;
    }
};

class FloatType : public MiddleIRType
{
public:
    FloatType()
        : MiddleIRType(FLOAT)
    {
    }
    bool operator==(const MiddleIRType& rhs) const override { return rhs.type == FLOAT; }
};

class VoidType : public MiddleIRType
{
public:
    VoidType()
        : MiddleIRType(VOID)
    {
    }
    bool operator==(const MiddleIRType& rhs) const override { return rhs.type == VOID; }
};

class ArrayType : public MiddleIRType
{
private:
    int    _size;
    SPType _elementType;
    IRType _atomElemType = UNKNOWN;

public:
    ArrayType(int size_, SPType elementType_)
        : MiddleIRType(ARRAY)
        , _size(size_)
        , _elementType(std::move(elementType_))
    {
    }
    bool operator==(const MiddleIRType& rhs) const override
    {
        if (rhs.type == ARRAY) {
            return _size == dynamic_cast<const ArrayType&>(rhs).getSize() &&
                   *_elementType == *dynamic_cast<const ArrayType&>(rhs).getElementType();
        }
        return false;
    }

public:
    [[nodiscard]] int           getSize() const { return _size; }
    void                        setSize(int size_) { ArrayType::_size = size_; }
    [[nodiscard]] const SPType& getElementType() const { return _elementType; }
    void setElementType(const SPType& elementType_) { ArrayType::_elementType = elementType_; }

public:
    [[nodiscard]] size_t getSizeBytes() const
    {
        if (_elementType->isInt()) {
            return _size * dynamic_cast<IntType*>(_elementType.get())->bitWidth / 8;
        } else if (_elementType->isFloat()) {
            return _size * 4;
        } else if (_elementType->isArray()) {
            return _size * dynamic_cast<ArrayType*>(_elementType.get())->getSizeBytes();
        } else {
            RUNTIME_ERROR("ArrayType::getSizeBytes not implemented");
        }
    }
    IRType getAtomElemType()
    {
        if (_atomElemType == UNKNOWN) {
            if (_elementType->isInt()) {
                _atomElemType = INT;
            } else if (_elementType->isFloat()) {
                _atomElemType = FLOAT;
            } else if (_elementType->isArray()) {
                _atomElemType = dynamic_cast<ArrayType*>(_elementType.get())->getAtomElemType();
            } else {
                RUNTIME_ERROR("ArrayType::getAtomElemType not implemented");
            }
        }
        return _atomElemType;
    }
};

class PointerType : public MiddleIRType
{
private:
    SPType _elementType;

public:
    explicit PointerType(SPType elementType_)
        : MiddleIRType(POINTER)
        , _elementType(std::move(elementType_))
    {
    }
    [[nodiscard]] const SPType& getElementType() const { return _elementType; }
    void setElementType(const SPType& elementType_) { PointerType::_elementType = elementType_; }
    bool operator==(const MiddleIRType& rhs) const override
    {
        if (rhs.type == POINTER) {
            return *_elementType == *dynamic_cast<const PointerType&>(rhs).getElementType();
        }
        return false;
    }
};

class LabelType : public MiddleIRType
{
public:
    LabelType()
        : MiddleIRType(LABEL)
    {
    }
    bool operator==(const MiddleIRType& rhs) const override { return rhs.type == LABEL; }
};

class ZeroInitializerType : public MiddleIRType
{
public:
    ZeroInitializerType()
        : MiddleIRType(ZEROINITIALIZER)
    {
    }
    bool operator==(const MiddleIRType& rhs) const override { return rhs.type == ZEROINITIALIZER; }
};

unique_ptr<MiddleIRType>        makePointer(const SPType& elementType_);
extern shared_ptr<MiddleIRType> spVoidType;
extern shared_ptr<MiddleIRType> spIntType32;
extern shared_ptr<MiddleIRType> spBoolType;
extern shared_ptr<MiddleIRType> spFloatType;
extern shared_ptr<MiddleIRType> spLabelType;
extern shared_ptr<MiddleIRType> spZeroInitializerType;
}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRTYPE_H
