//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_MIDDLEIRAST_H
#define IRBACKENDR5_MIDDLEIRAST_H
#include "R5Def.h"
#include "MiddleIRFuncDef.h"
namespace MiddleIR
{

struct MiddleIRAST {
    virtual ~MiddleIRAST() = default;
    std::vector<std::shared_ptr<MiddleIRFuncDef>>  funcDefs;
    std::vector<std::shared_ptr<MiddleIRFuncDecl>> funcDecls;
    std::vector<std::shared_ptr<MiddleIRVal>>      globalVars;
    std::vector<std::shared_ptr<MiddleIRVal>>      globalConsts;
    [[nodiscard]] shared_ptr<MiddleIRVal>          findVal(const std::string& name) const
    {
        for (const auto& funcDef : funcDefs) {
            if (funcDef->getName() == name) { return funcDef; }
        }
        for (const auto& funcDecl : funcDecls) {
            if (funcDecl->getName() == name) { return funcDecl; }
        }
        for (const auto& globalVar : globalVars) {
            if (globalVar->getName() == name) { return globalVar; }
        }
        for (const auto& globalConst : globalConsts) {
            if (globalConst->getName() == name) { return globalConst; }
        }
        RUNTIME_ERROR("Cannot find val named " + name);
        return nullptr;
    }
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRAST_H
