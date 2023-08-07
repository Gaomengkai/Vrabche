//
// Created by gaome on 2023/8/6.
//

#ifndef VRABCHE_MIDDLEIRPRINTER_H
#define VRABCHE_MIDDLEIRPRINTER_H
#include "MiddleIRInst.h"
#include "MiddleIRVal.h"
#include "MiddleIRType.h"
#include <string>
using std::string;
namespace MiddleIR
{
inline string printConst(shared_ptr<R5IRValConst> c)
{
    if (auto iVal = dynamic_pointer_cast<R5IRValConstInt>(c)) {
        return std::to_string(iVal->getValue());
    } else if (auto fVal = dynamic_pointer_cast<R5IRValConstFloat>(c)) {
        return std::to_string(fVal->getValue());
    } else if (auto bVal = dynamic_pointer_cast<R5IRValConstI1>(c)) {
        return bVal->getValue() ? "true" : "false";
    }
    return "UNKNOWN CONST";
}
inline string printInst(const shared_ptr<MiddleIRInst>& sharedPtr)
{
    string instName;
    switch (sharedPtr->_instType) {
    case MiddleIRInst::AllocaInst: instName = "ALLOCA"; break;
    case MiddleIRInst::ReturnInst: instName = "RETURN"; break;
    case MiddleIRInst::BrInst: instName = "BR"; break;
    case MiddleIRInst::IMathInst: instName = "IMATH"; break;
    case MiddleIRInst::FMathInst: instName = "FMATH"; break;
    case MiddleIRInst::ICmpInst: instName = "ICMP"; break;
    case MiddleIRInst::FCmpInst: instName = "FCMP"; break;
    case MiddleIRInst::LoadInst: instName = "LOAD"; break;
    case MiddleIRInst::StoreInst: instName = "STORE"; break;
    case MiddleIRInst::BitCastInst: instName = "BITCAST"; break;
    case MiddleIRInst::GetElementPtrInst: instName = "GETELEMENTPTR"; break;
    case MiddleIRInst::ConvertInst: instName = "CONVERT"; break;
    case MiddleIRInst::CallInst: instName = "CALL"; break;
    }
    string instRet = sharedPtr->getName();
    string instArgs;
    for (auto u : sharedPtr->getUseList()) {
        if ((*u)->isConst()) {
            instArgs += printConst(dynamic_pointer_cast<R5IRValConst>(*u));
        } else {
            instArgs += (*u)->getName();
        }
        instArgs += ", ";
    }
    if (!instRet.empty()) { return instRet + " = " + instName + " " + instArgs; }
    return instName + " " + instArgs;
}
inline string print(const shared_ptr<MiddleIR::MiddleIRVal>& val)
{
    if (auto inst = dynamic_pointer_cast<MiddleIR::MiddleIRInst>(val)) {
        return printInst(inst);
    } else if (val->isConst()) {
        return printConst(dynamic_pointer_cast<R5IRValConst>(val));
    } else {
        return val->getName();
    }
}
inline string printBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    string bbName = bb->getName();
    string bbInsts;
    for (auto inst : bb->_instructions) { bbInsts += printInst(inst) + "\n"; }
    return bbName + ":\n" + bbInsts;
}
}   // namespace MiddleIR


#endif   // VRABCHE_MIDDLEIRPRINTER_H
