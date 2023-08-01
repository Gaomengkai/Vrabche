//
// Created by gao on 6/26/23.
//

#include "IRSen.h"
#include "IRUtils.h"
#include "IRLogger.h"
#include "IRGlobal.h"


namespace IRCtrl
{

string ConstSen::toString()
{
    return {};
}


string GlobalValDeclSen::toString()
{
    stringstream ss;
    ss << "@" << this->val->name << " = ";
    if (IRCtrl::IR_SWITCH_ENABLE_DSO_LOCAL) { ss << "dso_local "; }
    if (this->val->isConst)
        ss << "constant";
    else
        ss << "global";
    // constant float 0x4041475CE0000000
    switch (this->val->type) {
    case IRValType::Func: break;   // Unreachable
    case IRValType::Int: ss << " i32 " << this->val->toString(); break;
    case IRValType::Float: ss << " float " << this->val->toString(); break;
    case IRValType::Arr: {
        auto x = std::dynamic_pointer_cast<CArr>(this->val);
        if (x) {
            if (x->containedType == IRValType::Float) {
                ss << " " << this->val->toString();
            } else {
                ss << " " << this->val->toString();
            }
        } else {
            auto y = std::dynamic_pointer_cast<VArr>(this->val);
            ss << " " << this->val->toString();
        }

    } break;
    case IRValType::Void: break;
    case IRValType::Unknown: break;
    case IRValType::Pointer: break;
    case IRValType::FloatArr: break;
    case IRValType::IntArr: break;
    }
    return ss.str();
}

IROp IRSen::getOp() const
{
    return _op;
}

string LocalSen::toString()
{
    return {};
}

string AllocaSen::toString()
{
    // 之所以这里没有使用%百分号，是因为我需要统一名称。名称在之前生成对象时保证%或@
    return m_lv + " = alloca " + irType->toString();
}

string ReturnSen::toString()
{
    return "ret " + this->irType->toString() + " " + this->m_lv;
}

string LoadSen::toString()
{
    return _label + " = load " + this->irType->toString() + ", " + makePointer(irType)->toString() +
           " " + this->sourceName;
}

string StoreSen::toString()
{
    stringstream ss;
    ss << "store " << irType->toString() << " " << sourceName << ", ";
    ss << makePointer(irType)->toString() << " " << _label;
    return ss.str();
}

/// %v16 = sitofp i32 5 to float
/// \return
string SiToFpSen::toString()
{
    return _label + " = sitofp " + _retType->toString() + " " + sourceName + " to float";
}
string FpToSiSen::toString()
{
    return _label + " = fptosi " + _retType->toString() + " " + sourceName + " to i32";
}
string BiSen::toString()
{
    return _label + " = " + opToStr(this->getOp()) + " " + _retType->toString() + " " + v1 + ", " +
           v2;
}
string opToStr(IROp op_)
{

    switch (op_) {

    case IROp::ADD: return "add";
    case IROp::SUB: return "sub";
    case IROp::MUL: return "mul";
    case IROp::SDIV: return "sdiv";
    case IROp::SREM: return "srem";
    case IROp::UDIV: break;
    case IROp::UREM: break;
    case IROp::FADD: return "fadd";
    case IROp::FSUB: return "fsub";
    case IROp::FMUL: return "fmul";
    case IROp::FDIV: return "fdiv";
    case IROp::FNEG: break;
    case IROp::SHL: break;
    case IROp::LSHR: break;
    case IROp::ASHR: break;
    case IROp::AND: break;
    case IROp::OR: break;
    case IROp::XOR: break;
    case IROp::ALLOCA: return "alloca";
    case IROp::LOAD: break;
    case IROp::STORE: break;
    case IROp::GETELEMENTPTR: break;
    case IROp::RET: break;
    case IROp::BR: break;
    case IROp::CALL: break;
    case IROp::ZEXT: return "zext";
    case IROp::SITOFP: return "sitofp";
    case IROp::FPTOSI: return "fptosi";
    case IROp::BITCAST: break;
    case IROp::ICMP: break;
    case IROp::FCMP: break;
    case IROp::PHI: break;
    case IROp::UNKNOWN: break;
    }
    return "<<!!! IROP NOT IMPL !!!>>";
}
bool isTerminal(const IRSen& sen)
{
    return sen.getOp() == IROp::RET || sen.getOp() == IROp::BR;
}

/// getelementptr <TYPE>, <TYPE>* <POINTER>, i32 <OFFSET>, ...
// getelementptr [10 x [3 x float]], [10 x [3 x float]]* %v5, i32 0, i32 0, i32 0
/// \return
string GepSen::toString()
{
    stringstream ss;
    if (!dimensionality_reduction) {
        /* getelementptr i32*, i32** %1002, i32 0, i32 2 */
        ss << _label << " = "
           << "getelementptr " << t->toString() << ", " << t->toString() << "* " << sourceName;
        ss << ", i32 0";
        for (auto x : offset) { ss << ", i32 " << x; }
        for (const auto& xy : offset_str) { ss << ", i32 " << xy; }
    } else {
        //   %v4 = getelementptr i32, i32* %v3, i32 2
        auto tp = DPC(ArrayType, t);
        // cut *
        auto no_star = tp->toString().substr(0, tp->toString().size() - 1);
        ss << _label << " = "
           << "getelementptr " << no_star << ", " << tp->toString() << " " << sourceName;
        for (auto x : offset) { ss << ", i32 " << x; }
        for (const auto& xy : offset_str) { ss << ", i32 " << xy; }
    }

    return ss.str();
}
void GepSen::setRetType()
{
    if (t->type == IRValType::Arr) {
        // get inner type
        auto tp        = DPC(ArrayType, t);
        this->_retType = makeType(tp->innerType);
    } else {
        // pass
    }
}
string Memset::toString()
{
    /*
     *  %v6 = bitcast [10 x [3 x float]]* %v5 to i32*
        call void @llvm.memset.p0.i32(i32* %v6, i8 0, i32 120, i1 false)
     */
    stringstream ss;
    ss << _label << " = bitcast " << this->pt->toString() << " " << sourceName << " to i32*\n";
    ss << "    call void @llvm.memset.p0.i32(i32* " << _label << ", i8 " << int(x) << ", i32 "
       << bytes << ", i1 false)";
    return ss.str();
}
string CallSen::toString()
{
    /*
     *
        _label   = std::move(outLabel_);
        _retType = makeType(retType_);
        _op      = IROp::CALL;

        string toString() override;
        protected:
        string funcName;
        IRValType retType;
        vector<SPType> argTypes;
        vector<string> argNames;
     */
    stringstream ss;

    //   %v6 = call i32 @foo2(i32* %v5)
    if (_retType->type != IRValType::Void) { ss << _label << " = "; }
    ss << "call ";
    if (IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC) { ss << "arm_aapcs_vfpcc "; }
    ss << _retType->toString() << " @" << funcName << "(";
    for (int i = 0; i < argTypes.size(); i++) {
        ss << argTypes[i]->toString() << " " << argNames[i];
        if (i != argTypes.size() - 1) { ss << ", "; }
    }
    ss << ")";
    return ss.str();
}
string BrSen::toString()
{
    stringstream ss;

    if(brType == BrType::COND){
        ss << "br i1 " << cond << ", label %" << trueLabel << ", label %" << falseLabel;
    }else if(brType == BrType::UNCOND){
        ss << "br label %" << trueLabel;
    }
    return ss.str();
}

/// <result> = icmp eq i32 4, 5  ; yields i1 true
/// \return A i32 comparison string, which has a label representing the result(i1)
string IcmpSen::toString()
{
    stringstream ss;
    ss<<_label<<" = icmp "<< Utils::icmpOpToStr(cond) <<" i32 "<<op1<<", "<<op2;
    return ss.str();
}
string FcmpSen::toString()
{
    stringstream ss;
    ss<<_label<<" = fcmp "<< Utils::fcmpOpToStr(cond) <<" float "<<op1<<", "<<op2;
    return ss.str();
}

///   %v7 = zext i1 %v6 to i32
/// \return Just as you expect
string ZextSen::toString()
{
    if(from!=IRValType::Bool) {
        RUNTIME_ERROR("ZextSen::toString() from type is not i1");
    }
    stringstream ss;
    ss<<_label<<" = zext i1 "<<sourceName<<" to i32";
    return ss.str();
}
}   // namespace IRCtrl
