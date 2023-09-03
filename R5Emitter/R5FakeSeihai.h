//
// Created by gaome on 2023/7/21.
//

#ifndef IRBACKENDR5_R5FAKESEIHAI_H
#define IRBACKENDR5_R5FAKESEIHAI_H

#include <list>
#include "MiddleIRInst.h"
#include "R5AsmStrangeFake.h"
#include "MiddleIRFuncDef.h"
#include "R5TaichiMap.h"
#include "MiddleIRAST.h"
#include <variant>
using std::variant;
using namespace MiddleIR;

namespace R5Emitter
{
// 一个函数级别的虚拟IR和寄存器分配器。
class R5FakeSeihai
{
public:
    explicit R5FakeSeihai(
        const std::shared_ptr<MiddleIRFuncDef>& funcDef, const std::shared_ptr<MiddleIRAST>& irast
    );
    void emitFakeSeihai();
    void emitStream(std::ostream& os);

    std::vector<string>                        bbNames;   // 基本块名字(optimized)
    std::vector<vector<R5AsmStrangeFake>>      blockStrangeFake;
    std::vector<std::vector<R5AsmStrangeFake>> allocatedCodes;

private:
    int extTempVarNum    = 0;   // 额外的虚拟寄存器
    int extTempMemVarNum = 0;   // 额外的内存常量区

    bool isEmitFinished = false;

    // 新建虚拟寄存器
    inline string E();

    // 新建内存常量区
    template<class T>
    inline string C(T v);

    // 内存常量区表
    std::unordered_map<string, uint32_t> constMem;

    // 太极图 表示alloca和spill中相对于s0的正偏移。
    R5TaichiMap taichiMap; //这里只是 声明 。它会被初始化为R5TaichiMap(true)
    // 一般的太极图我们不能满足了！我们需要新的太极图！
    // 分配一个栈空间。单位字节。按4字节对齐。
    void allocateStackSpace(const string& name, int64_t size);
    // 查询太极图中的偏移量。是s0的负偏移。
    int64_t queryStackSpace(const string& name);
    // 太极图中真的有吗？如有！
    bool queryInStackSpace(const string& name);

    // 函数返回标签
    string funcRetLabel();
    // 函数入口标签
    string funcEntryLabel();
    // 函数第一个基本块标签
    string funcFirstBBLabel();

    // 函数在栈上的参数区大小
    int funcStackArgCount = 0;
    // 函数的整数参数计数
    int funcIntArgCount = 0;
    // 函数的浮点参数计数
    int funcFloatArgCount = 0;

    const std::shared_ptr<MiddleIRFuncDef>& thisFunc;
    const std::shared_ptr<MiddleIRAST>&     ast;

    // 0807重构：用于去除没用的参数store操作
    using RegOrStack = variant<YangReg, int64_t>;
    std::vector<RegOrStack> argRegOrStack;
    void                    initArgRegOrStack();

    void emitBB(const std::shared_ptr<MiddleIRBasicBlock>& bb);

    // Inst Handler
    void handleIMathInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleFMathInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleAllocaInst(const shared_ptr<MiddleIRInst>& inst1);
    void handleLoadInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleStoreInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleArgStoreInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleICmpNoBr(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleCvtInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleBitcastInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleFCmpInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    static void handleBrInst(
        vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1, const string& funcName
    );
    void handleGEPInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleCallInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);
    void handleRetInst(vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1);

    // 为了方便，这个函数用来l/s一个寄存器+偏移量的内存地址.
    void accessStack(
        vector<R5AsmStrangeFake>&   sf,
        FakeOPs                     op,
        const shared_ptr<R5Taichi>& op1,
        int64_t                     offset,
        YangReg                     st
    );
    std::set<YangReg> totalUsedReg;   // Only saved Callee-Saved Regs
    static void              accessStackWithTmp(
                     vector<R5AsmStrangeFake>&   sf,
                     FakeOPs                     op,
                     const shared_ptr<R5Taichi>& op1,
                     int64_t                     offset,
                     YangReg                     st,
                     YangReg                     tmp
                 );
    R5AsmStrangeFake quickMulInm(
        vector<R5AsmStrangeFake>& sf,
        shared_ptr<R5Taichi>      lv,
        shared_ptr<R5Taichi>      rv,
        int64_t                   inm,
        bool                      is64
    );
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5FAKESEIHAI_H
