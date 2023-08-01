//
// Created by gao on 6/29/23.
//

#include "IRVal.h"
#include "IRLogger.h"

#include <utility>
#include <ios>
#include <sstream>


namespace IRCtrl
{

void IntCVal::unary()
{
    this->iVal = -this->iVal;
}
string IntCVal::toString()
{
    return std::to_string(this->iVal);
}
void IntCVal::notOp()
{
    iVal = !iVal;
}

void FloatCVal::unary()
{
    this->fVal = -this->fVal;
}
string FloatCVal::toString()
{
    stringstream ss;
    //    ss<<"0x"<<std::hex<<reinterpret_cast<uint32_t>(this->fVal);
    // Method above was not allowed
    // In LLVM-IR, a float is 64 bit.
    double thisValue = this->fVal;
    ss << "0x" << std::hex << *(uint64_t*)(&thisValue);
    return ss.str();
}
void FloatCVal::notOp()
{
    fVal = !fVal;
}

string InitListVal::toString()
{
    return {};
}
bool InitListVal::empty() const
{
    return this->cVal.empty() && this->initList.empty();
}
size_t InitListVal::dim() const
{
    if (!cVal.empty()) return 1;
    if (initList.empty()) return 0;
    size_t maxDim = 0;
    for (auto& x : initList) { maxDim = std::max(maxDim, x->dim()); }
    return maxDim + 1;
}
string CArr::shapeString(IRValType containedType_, const std::deque<size_t>& shape_)
{
    stringstream ss;
    // returns like [3 x [3 x i32]]
    // a 3 dimensional array likes [5 x [3 x [3 x i32]]]
    // this->_shape = {3,3} (vector<size_t>)
    // element type is i32 or float
    string elementTypeString = (containedType_ == IRValType::Float) ? "float" : "i32";

    for (auto& x : shape_) { ss << "[" << x << " x "; }
    ss << elementTypeString;
    for (size_t _ = 0; _ < shape_.size(); _++) { ss << "]"; }
    return ss.str();
}
string fillZero(std::deque<size_t> sh, const shared_ptr<CVal>& cv, IRValType t)
{
    stringstream ss;
    string       elementTypeStr = t == IRValType::Float ? "float" : "i32";
    if (sh.empty()) {
        ss << elementTypeStr << " " << cv->toString();
        return ss.str();
    } else if (sh.size() == 1) {
        ss << CArr::shapeString(t, sh) << " ";
        ss << "[";
        ss << elementTypeStr << " " << cv->toString();
        for (auto i = 1; i < sh.front(); i++) { ss << ", " << elementTypeStr << " 0"; }
        ss << "]";
        return ss.str();
    } else {
        // multiple dims
        ss << CArr::shapeString(t, sh) << " ";
        auto curDim = sh.front();
        sh.pop_front();
        ss << fillZero(sh, cv, t);
        for (auto i = 1; i < curDim; i++) {
            ss << ", " << CArr::shapeString(t, sh) << " ";
            ss << "zeroinitializer";
        }
        sh.push_front(curDim);
        return ss.str();
    }
}
string CArr::toString()
{
    stringstream ss;
    string       elementTypeString = (this->containedType == IRValType::Float) ? "float" : "i32";
    // [3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] zeroinitializer, [3 x i32]
    // zeroinitializer]
    ss << shapeString(this->containedType, this->_shape);
    if (this->isZero) {
        ss << " zeroinitializer";
        return ss.str();
    }
    ss << " [";
    for (auto i = 0; i < witch.size(); i++) {
        auto ty = witch[i];
        if (ty == CARR) {
            // arr, recursive
            ss << _childArrs[i]->toString() << ", ";
        } else if (ty == ZERO) {
            // zero or zeroinitializer
            size_t front = _shape.front();
            _shape.pop_front();
            if (_shape.empty())
                ss << elementTypeString << " 0, ";
            else
                ss << shapeString(this->containedType, _shape) << " zeroinitializer, ";
            _shape.push_front(front);
        } else {
            // cval. output its value or init another array?
            size_t front = _shape.front();
            _shape.pop_front();
            ss << fillZero(_shape, _childVals[i], this->containedType) << ", ";
            _shape.push_front(front);
        }
    }
    // Here we have a problem: at the end of the string, there is a ", " which is not allowed.
    // So we need to remove it.
    string s = ss.str();
    s.pop_back();
    s.pop_back();
    s += "]";
    return s;
}

shared_ptr<CVal> CArr::access(const vector<int>& indices)
{
    auto* cur = this;
    for (int i : indices) {
        if (cur->witch[i] == ZERO) {
            if (this->containedType == IRValType::Int) {
                return make_shared<IntCVal>("", 0);
            } else {
                return make_shared<FloatCVal>("", 0);
            }
        } else if (cur->witch[i] == CARR) {
            cur = cur->_childArrs[i].get();
            continue;
        } else {   // CVAL
            auto cv = cur->_childVals[i];
            return cv;
        }
    }
    // you have not return yet.
    // wtf, u r accessing a incomplete arr shape. you must want to pass the pointer to another
    // function. so how should we do? return 0? no,no,no. we must store this state into a FLAG.
    // Someone who reach this flag, and she would plug-out this FLAG.

    // on the other way, one who want to access an array, she has to check shape had been matched.
    return nullptr;
}
[[maybe_unused]] string CArr::shapeString() const
{
    return shapeString(this->containedType, this->_shape);
}

string IntVal::toString()
{
    return std::to_string(this->iVal);
}
string FloatVal::toString()
{
    stringstream ss;
    //    ss<<"0x"<<std::hex<<reinterpret_cast<uint32_t>(this->fVal);
    // Method above was not allowed
    // In LLVM-IR, a float is 64 bit.
    double thisValue = this->fVal;
    ss << "0x" << std::hex << *(uint64_t*)(&thisValue);
    return ss.str();
}
string VArr::toString()
{
    stringstream ss;
    string       elementTypeString = (this->containedType == IRValType::Float) ? "float" : "i32";
    // [3 x [3 x i32]] [[3 x i32] [i32 1, i32 2, i32 3], [3 x i32] zeroinitializer, [3 x i32]
    // zeroinitializer]
    ss << CArr::shapeString(this->containedType, this->_shape);
    if (this->isZero) {
        ss << " zeroinitializer";
        return ss.str();
    }
    ss << " [";
    for (auto i = 0; i < witch.size(); i++) {
        auto ty = witch[i];
        if (ty == VARR) {
            // arr, recursive
            ss << _childArrs[i]->toString() << ", ";
        } else if (ty == ZERO) {
            // zero or zeroinitializer
            size_t front = _shape.front();
            _shape.pop_front();
            if (_shape.empty())
                ss << elementTypeString << " 0, ";
            else
                ss << CArr::shapeString(this->containedType, _shape) << " zeroinitializer, ";
            _shape.push_front(front);
        } else {
            // cval. output its value or init another array?
            size_t front = _shape.front();
            _shape.pop_front();
            ss << fillZero(_shape, _childVals[i], this->containedType) << ", ";
            _shape.push_front(front);
        }
    }
    // Here we have a problem: at the end of the string, there is a ", " which is not allowed.
    // So we need to remove it.
    string s = ss.str();
    if (s.substr(s.size() - 2) == ", ") {
        s.pop_back();
        s.pop_back();
    }
    s += "]";
    LOGD(s);
    return s;
}
string VArr::shapeString()
{
    return CArr::shapeString(this->containedType, this->_shape);
}
string FPVar::toString()
{
    stringstream ss;
    auto         pType = this->fpType->type;
    if (pType == IRValType::Float) {
        ss << "float";
    } else if (pType == IRValType::Int) {
        ss << "i32";
    } else if (pType == IRValType::Arr) {
        auto   fpArrType   = std::dynamic_pointer_cast<ArrayType>(this->fpType);
        string elemTypeStr = (fpArrType->innerType == IRValType::Float) ? "float" : "i32";
    } else {
        RUNTIME_ERROR("Unknown type");
    }
    return ss.str();
}

const SPType& FPVar::getFpType() const
{
    return fpType;
}

void FPVar::setFpType(const SPType& fpType_)
{
    advancedType  = fpType_;
    FPVar::fpType = fpType_;
    type          = fpType_->type;
}

string LocalInt::toString()
{
    return std::string();
}
string LocalFloat::toString()
{
    return std::string();
}

string LocalBool::toString()
{
    return LocalInt::toString();
}

SPType IRVal::getTrueAdvType() const
{
    if (this->advancedType != nullptr) {
        return this->advancedType;
    } else {
        return makeType(this->type);
    }
}
const string& IRVal::getName() const
{
    return name;
}
void IRVal::setName(const string& name)
{
    IRVal::name = name;
}
const string& IRVal::getId() const
{
    return id;
}
void IRVal::setId(const string& id)
{
    IRVal::id = id;
}
}   // namespace IRCtrl
