//
// Created by gaome on 2023/7/13.
//

#include "MiddleIRType.h"

namespace MiddleIR
{
VoidType                 voidType;
IntType                  intType32(32);
IntType                  boolType(1);
FloatType                floatType;
LabelType                labelType;
shared_ptr<MiddleIRType> spVoidType            = std::make_shared<VoidType>(voidType);
shared_ptr<MiddleIRType> spIntType32           = std::make_shared<IntType>(intType32);
shared_ptr<MiddleIRType> spBoolType            = std::make_shared<IntType>(boolType);
shared_ptr<MiddleIRType> spFloatType           = std::make_shared<FloatType>(floatType);
shared_ptr<MiddleIRType> spLabelType           = std::make_shared<LabelType>(labelType);
shared_ptr<MiddleIRType> spZeroInitializerType = std::make_shared<ZeroInitializerType>();
unique_ptr<MiddleIRType> makePointer(const SPType& elementType_)
{
    return std::make_unique<PointerType>(elementType_);
}
}   // namespace MiddleIR