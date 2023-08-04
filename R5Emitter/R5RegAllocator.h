//
// Created by gaome on 2023/7/26.
//

#ifndef IRBACKENDR5_R5REGALLOCATOR_H
#define IRBACKENDR5_R5REGALLOCATOR_H
#include <list>
#include <set>
#include "R5Def.h"
#include "R5AsmStrangeFake.h"
#include "R5TaichiMap.h"
#include "R5Yang.h"
#include "MiddleIRFuncDef.h"

using MiddleIR::MiddleIRFuncDef;
using fu = std::unordered_map<string, std::set<R5Emitter::YangReg>>;
namespace R5Emitter
{
class R5RegAllocator
{
public:
    // 从基本块名字、基本块代码、太极图引用构造一个寄存器分配器
    R5RegAllocator(
        const std::vector<string>&                        bbNames_,
        const std::vector<std::vector<R5AsmStrangeFake>>& bbCodes_,
        R5TaichiMap&                                      taichiMap_,
        const fu&                                         fu_,
        const std::shared_ptr<MiddleIRFuncDef>&           thisFunc_
    );

    // 为所有基本块分配寄存器
    void doAllocate();
    // 指定一个基本块，为其分配寄存器
    void doAllocate(int bbIndex);
    // 获取分配结果
    const std::vector<std::vector<R5AsmStrangeFake>>& getAllocatedCodes();
    // 获取使用过的寄存器

protected:
    // 太极图引用。用于记录、分配栈空间。
    // 太极图是在函数层面的。
    R5TaichiMap& taichiMap;
    const std::shared_ptr<MiddleIRFuncDef>&           thisFunc;

    // 所有基本块的名字的拷贝
    std::vector<string> bbNames;
    // 所有基本块的代码的拷贝
    std::vector<std::vector<R5AsmStrangeFake>> bbCodes;

    // 分配结果
    std::vector<std::vector<R5AsmStrangeFake>> allocatedCodes;

    // 所有使用过的寄存器
    std::set<YangReg> totalUsedRegs;

public:
    [[nodiscard]] const std::set<YangReg>& getTotalUsedRegs() const;

protected:
    // 用于获取call指令用到哪些寄存器
    const fu& _fu;

    // 获取那个函数的寄存器使用情况
    std::set<YangReg> getUsedRegs(string funcName);
    std::unordered_map<string, YangReg> buildArgRegMap();
    std::unordered_map<string, int64_t> buildExtArgRegMap();
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5REGALLOCATOR_H
