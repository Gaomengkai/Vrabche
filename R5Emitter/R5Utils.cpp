//
// Created by gaome on 2023/7/27.
//
#include "R5Utils.h"
namespace R5Emitter
{
std::set<R5Emitter::YangReg>
funcCallUsedReg(string funcName, const std::shared_ptr<MiddleIRAST>& irast)
{
    // if not starts with "@" , then add "@"
    if (funcName[0] != '@') { funcName = "@" + funcName; }
    if (funcName == "@memset") return {a0, a1, a2};
    const std::shared_ptr<MiddleIRFuncDecl>& funcDecl =
        std::dynamic_pointer_cast<MiddleIRFuncDecl>(irast->findVal(funcName));
    if (!funcDecl) { RUNTIME_ERROR("Cannot find function named " << funcName); }
    std::set<YangReg> usedReg;
    int               intRegUsed   = 0;
    int               floatRegUsed = 0;
    for (auto& ty : funcDecl->getParamsTypes()) {
        if (ty->isPointer() || ty->isInt()) {
            intRegUsed++;
        } else if (ty->isFloat()) {
            floatRegUsed++;
        }
    }
    intRegUsed   = std::min(intRegUsed, 8);
    floatRegUsed = std::min(floatRegUsed, 8);
    for (int i = 0; i < intRegUsed; i++) { usedReg.insert((YangReg)(i + a0)); }
    for (int i = 0; i < floatRegUsed; i++) { usedReg.insert((YangReg)(i + fa0)); }
    return usedReg;
}
}   // namespace R5Emitter