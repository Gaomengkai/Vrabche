//
// Created by gaome on 2023/7/21.
//

#include "R5FakeSeihai.h"
#include "R5Yin.h"
#include "R5Yang.h"
#include "R5Ru.h"
#include "R5Lai.h"
#include "R5Lai64.h"
#include "R5RegAllocator.h"
#include "R5Utils.h"

#define SP std::shared_ptr
namespace R5Emitter
{

/// 从IR的虚拟寄存器生成一个MIR的虚拟寄存器
/// \param v 名字
/// \param yinType 类型（Float/Int/Pointer）
/// \return 太极
static inline shared_ptr<R5Taichi> V(const string& v, YinType yinType)
{
    return make_shared<R5Yin>(v, yinType);
}

/// 检查一个立即数在s/l指令中是否可以直接使用
/// \param p
/// \return
static inline bool couldLoadWithRegImm(int64_t p)
{
    return -2048 <= p && p <= 2047;
}

/// 生成一个标签
/// \param l 标签名字
/// \return 太极
static inline shared_ptr<R5Taichi> L(const string& l)
{
    return make_shared<R5Ru>(l);
}

/// 生成一个立即数(32位)
/// \param v 数
/// \return 太极
static inline shared_ptr<R5Taichi> N(int v)
{
    return make_shared<R5Lai>(v);
}

/// 生成一个物理寄存器(Float/Long)
/// \param r r0/r1/r2...
/// \return 太极
static inline shared_ptr<R5Taichi> R(YangReg r)
{
    return make_shared<R5Yang>(r);
}


/// 生成一个立即数(64位)
/// \param v 数
/// \return 太极
static inline shared_ptr<R5Taichi> P(uint64_t v)
{
    return make_shared<R5Lai64>(v);
}

/// 生成一个基本块对应的标签名字
/// \param funcName 函数名字
/// \param bbName 基本块名字
/// \return 生成结果
static inline string BN(const string& funcName, const string& bbName)
{
    string pureFuncName = funcName.substr(1);
    return ".LBB_" + pureFuncName + "_" + bbName;
}

/// 生成一个新的虚拟寄存器
/// \return 寄存器的名字
inline string R5FakeSeihai::E()
{
    return "%t" + std::to_string(extTempVarNum++);
}

/// 从IR的函数定义构造一个假圣杯
/// \param funcDef IR函数定义
R5FakeSeihai::R5FakeSeihai(
    const std::shared_ptr<MiddleIRFuncDef>& funcDef, const std::shared_ptr<MiddleIRAST>& irast
)
    : thisFunc(funcDef)
    , ast(irast)
    , taichiMap(true)   // 注意，从此修改为反转的太极图！保留空间为16字节，分别存放ra和fp。
{
}

void R5FakeSeihai::emitStream(std::ostream& os)
{
    if (!isEmitFinished) emitFakeSeihai();
    const static char TAB      = '\t';
    const static char ENDL     = '\n';
    auto              removeAt = [&](const string& s) {
        if (s[0] == '@') return s.substr(1);
        return s;
    };
    // function declaration
    os << TAB << ".text" << ENDL;
    os << TAB << ".align 2" << ENDL;
    os << TAB << ".global " << removeAt(thisFunc->getName()) << ENDL;
    os << TAB << ".type " << removeAt(thisFunc->getName()) << ", @function" << ENDL;
    os << removeAt(thisFunc->getName()) << ":" << ENDL;
    // 生成函数头，包括保存ra和fp的指令。包括保存使用到的callee-save寄存器。(need TaichiMap)
    vector<R5AsmStrangeFake>            fh;   // function header.
    vector<R5AsmStrangeFake>            ft;   // function end.
    std::unordered_map<string, YangReg> funcUsedReg;
    //    for (auto reg : totalUsedReg) {
    //        funcUsedReg["#FH_" + R5Yang::toString(reg)] = reg;
    //        taichiMap.allocate("#FH_" + R5Yang::toString(reg), 8);
    //    }

    int64_t stackSize = taichiMap.getMaxSize() + 16;
    // 腾出额外的空间用来保存Callee-save寄存器
    stackSize += (int64_t)totalUsedReg.size() * 8;
    // stackSize 16bytes aligned
    if (stackSize % 16 != 0) stackSize += 16 - stackSize % 16;

    int64_t availableCalleeSavedRegStartOffset = -stackSize;

    // Function Header
    int64_t sSize = stackSize;
    // allocate stack space
    while (sSize >= 2040) {
        sSize -= 2040;
        fh.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N(-2040)}));
    }
    if (sSize > 0) { fh.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N(-sSize)})); }
    // save ra and fp
    accessStackWithTmp(fh, SD, R(ra), stackSize - 8, sp, t1);
    accessStackWithTmp(fh, SD, R(s0), stackSize - 16, sp, t1);
    // new s0
    sSize = stackSize;
    fh.emplace_back(R5AsmStrangeFake(ADDI, {R(s0), R(sp), N((int)(sSize % 2040LL))}));
    while (sSize >= 2040) {
        sSize -= 2040;
        fh.emplace_back(R5AsmStrangeFake(ADDI, {R(s0), R(s0), N(2040)}));
    }
    // save callee-save registers
    int j = 0;
    for (auto reg : totalUsedReg) {
        if (reg == ra || reg == s0) continue;
        auto offset = availableCalleeSavedRegStartOffset + 8 * j;
        if(R5Yang::isFloatReg(reg))
            accessStackWithTmp(fh, FSW, R(reg), offset, s0, t1);
        else
            accessStackWithTmp(fh, SD, R(reg), offset, s0, t1);
        j++;
    }


    // Function Tail
    // restore callee-save registers
    j = 0;
    for (auto reg : totalUsedReg) {
        if (reg == ra || reg == s0) continue;
        auto offset = availableCalleeSavedRegStartOffset + 8 * j;
        if(R5Yang::isFloatReg(reg))
            accessStackWithTmp(fh, FLW, R(reg), offset, s0, t1);
        else
            accessStackWithTmp(fh, LD, R(reg), offset, s0, t1);
        j++;
    }
    // reload ra, s0
    accessStackWithTmp(ft, LD, R(s0), stackSize - 16, sp, t1);   // reload s0
    accessStackWithTmp(ft, LD, R(ra), stackSize - 8, sp, t1);    // reload ra
    // restore sp
    sSize = stackSize;
    ft.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N((int)(sSize % 2040LL))}));
    while (sSize >= 2040) {
        sSize -= 2040;
        ft.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N(2040)}));
    }
    // jr ra
    ft.emplace_back(R5AsmStrangeFake(RET, {}));

    // emit function header
    for (auto& i : fh) { os << TAB << i.toString() << ENDL; }
    // emit function body
    for (auto i = 0; i < bbNames.size(); ++i) {
        os << bbNames[i] << ":" << ENDL;
        for (auto& a : allocatedCodes[i]) { os << TAB << a.toString(true) << ENDL; }
    }
    // emit function tail
    os << funcRetLabel() << ":" << ENDL;
    for (auto& i : ft) { os << TAB << i.toString() << ENDL; }
    // emit .LCxxx(.rodata)
    if (!constMem.empty()) os << ".section .rodata" << ENDL;
    for (auto [name, value] : constMem) {
        os << name << ":" << ENDL;
        os << TAB << ".word " << value << ENDL;
    }
    os << ENDL;
}
/// 虚假的圣杯，虚假的汇编。
void R5FakeSeihai::emitFakeSeihai()
{
    if (isEmitFinished) return;
    isEmitFinished = true;
    this->bbNames.clear();
    this->extTempVarNum = 0;
    this->blockStrangeFake.clear();
    this->totalUsedReg.clear();
    using fu = std::unordered_map<string, std::set<YangReg>>;
    fu funcUsedReg;
    // 遍历所有函数声明和函数调用。
    for (auto& decl : ast->funcDecls) {
        funcUsedReg[decl->getName()] = funcCallUsedReg(decl->getName(), ast);
    }
    for (auto& def : ast->funcDefs) {
        funcUsedReg[def->getName()] = funcCallUsedReg(def->getName(), ast);
    }
    // 差个@memset
    funcUsedReg["@memset"] = {a0, a1, a2};
    LOGW("FuncName: " << thisFunc->getName());
    for (const auto& bb : thisFunc->getBasicBlocks()) {
        emitBB(bb);   // bbName and bb itself will be added Into blockStrangeFake in this func.
        LOGW(bbNames.back());
        for (auto& i : blockStrangeFake.back()) { LOGD(i.toString(true)); }
    }

    // 函数级别的寄存器分配
    R5RegAllocator regAllocator(bbNames, blockStrangeFake, taichiMap, funcUsedReg);
    allocatedCodes       = regAllocator.getAllocatedCodes();
    auto totalUsedRegRes = regAllocator.getTotalUsedRegs();
    // remove NOT Callee-save regs
    for (auto& reg : totalUsedRegRes) {
        if (R5Yang::isCalleeSave(reg)) { totalUsedReg.insert(reg); }
    }

    // 处理返回语句。我的方法是新建立一个funcRetLabel()标签(基本块)，
    // 然后在每个函数的最后一条指令之后插入一条J指令，跳转到。
}
static inline void S(shared_ptr<R5Taichi>& a, shared_ptr<R5Taichi>& b)
{
    swap(a, b);
}
#pragma clang diagnostic push
#pragma ide diagnostic   ignored "modernize-use-emplace"

void R5FakeSeihai::emitBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    // 全部装填，包括终结符！
    std::list<SP<MiddleIRInst>> instructions = bb->_instructions;
    instructions.emplace_back(bb->getTerminator());

    vector<R5AsmStrangeFake> sf;
    auto                     it1 = instructions.begin();
    auto                     it2 = instructions.begin();
    it2++;
    auto moveNext = [&]() {
        it1++;
        it2++;
    };
    for (; it1 != instructions.end(); moveNext()) {
        auto inst1 = *it1;
        auto inst2 = inst1;
        if (it2 != instructions.end()) inst2 = *it2;
        if (inst1->isAllocaInst()) handleAllocaInst(inst1);
        // Int Math
        else if (inst1->isIMathInst())
            handleIMathInst(sf, inst1);
        // Float Math
        else if (inst1->isFMathInst())
            handleFMathInst(sf, inst1);
        // Load
        else if (inst1->isLoadInst())
            handleLoadInst(sf, inst1);
        // Store
        else if (inst1->isStoreInst())
            handleStoreInst(sf, inst1);
        // ICmp
        // #pragma region ICMP
        else if (inst1->isICmpInst()) {
            if (inst2->isBrInst()) {
                // 比较且跳转。
                auto cmpInst = std::dynamic_pointer_cast<ICmpInst>(inst1);
                auto brInst  = std::dynamic_pointer_cast<BrInst>(inst2);
                if (brInst->getCond() != cmpInst) {
                    LOGW("他妈的这两个指令不匹配! 回退到《非ICMP+跳转》格式");
                    // TODO 不用goto实现。
                    goto LabelCmpNotJump;
                }
                if (brInst->getIfFalse() == nullptr) {
                    // 直接插入一条跳转指令,不管比较结果如何，都跳转到ifTrue
                    sf.emplace_back(
                        R5AsmStrangeFake(J, {L(BN(thisFunc->getName(), brInst->getIfTrueLabel()))})
                    );
                } else {
                    auto                 cmpOp = cmpInst->getICmpOp();
                    auto                 op1   = cmpInst->getOpVal1();
                    auto                 op2   = cmpInst->getOpVal2();
                    shared_ptr<R5Taichi> taichi1;
                    shared_ptr<R5Taichi> taichi2;
                    // 将0的交换至taichi2. 然后即可解决。
                    if (op1->isConst()) {
                        // 立即数 不能直接比较。需要先装载到寄存器里。
                        int op1Val = std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue();
                        if (op1Val == 0)
                            taichi1 = R(zero);
                        else {
                            auto tmp = V(E(), Int);
                            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(op1Val)}));
                            taichi1 = tmp;
                        }
                    } else {
                        // 变量
                        taichi1 = V(op1->getName(), Int);
                    }
                    if (op2->isConst()) {
                        int op2Val = std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue();
                        if (op2Val == 0)
                            taichi2 = R(zero);
                        else {
                            auto tmp = V(E(), Int);
                            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(op2Val)}));
                            taichi2 = tmp;
                        }
                    } else {
                        taichi2 = V(op2->getName(), Int);
                    }
                    FakeOPs fop;
                    switch (cmpOp) {
                    case ICmpInst::EQ: fop = BEQ; break;
                    case ICmpInst::NE: fop = BNE; break;
                    case ICmpInst::SGT: fop = BGT; break;
                    case ICmpInst::SGE: fop = BGE; break;
                    case ICmpInst::SLT: fop = BLT; break;
                    case ICmpInst::SLE: fop = BLE; break;
                    case ICmpInst::UGE: fop = BGEU; break;
                    case ICmpInst::UGT: fop = BGTU; break;
                    case ICmpInst::ULE: fop = BLEU; break;
                    case ICmpInst::ULT: fop = BLTU; break;
                    }
                    // 比较完了，接下来是跳转
                    // 跳转的目标是什么？是标签。
                    string ifTrueLabel  = brInst->getIfTrueLabel();
                    ifTrueLabel         = BN(thisFunc->getName(), ifTrueLabel);
                    string ifFalseLabel = brInst->getIfFalseLabel();
                    ifFalseLabel        = BN(thisFunc->getName(), ifFalseLabel);
                    // 并非为了圣杯──也非为其他任何事物，而是为贯彻他们自身的信念。
                    sf.emplace_back(R5AsmStrangeFake(fop, {taichi1, taichi2, L(ifTrueLabel)}));
                    sf.emplace_back(R5AsmStrangeFake(J, {L(ifFalseLabel)}));
                    moveNext();
                }
            } else {
                // 比较 但是没有跳转指令、
            LabelCmpNotJump:
                handleICmpNoBr(sf, inst1);
            }
        }
        // #pragma endregion ICMP
        //  fptosi/ sitofp. But, Zext/Sext were not implemented.
        else if (inst1->isConvertInst())
            handleCvtInst(sf, inst1);
        else if (inst1->isGetElementPtrInst())
            handleGEPInst(sf, inst1);
        else if (inst1->isBitCastInst())
            handleBitcastInst(sf, inst1);
        else if (inst1->isFCmpInst())
            handleFCmpInst(sf, inst1);
        else if (inst1->isBrInst())
            handleBrInst(sf, inst1, thisFunc->getName());
        else if (inst1->isCallInst())
            handleCallInst(sf, inst1);
        else if (inst1->isReturnInst())
            handleRetInst(sf, inst1);
        else {
            // not implemented
            RUNTIME_ERROR("他妈的不支持的指令类型, 传了什么东西进来❤受不了了");
        }
    }
    // push sf into...
    string bbName = BN(thisFunc->getName(), bb->getName());
    blockStrangeFake.emplace_back(std::move(sf));
    bbNames.emplace_back(bbName);
}
void R5FakeSeihai::handleRetInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // 整数挪到a0，浮点数挪到fa0,然后跳转到.LRET_<funcname>
    auto retInst = std::dynamic_pointer_cast<ReturnInst>(inst1);
    auto retType = retInst->getAtomRetType();
    if (retType == MiddleIRType::FLOAT) {
        // 先判断是不是立即数。
        auto fVal = retInst->getOpVal();
        if (fVal->isConst()) {
            auto cf   = std::dynamic_pointer_cast<R5IRValConstFloat>(fVal);
            auto c    = L(C(cf->getWord()));
            auto addr = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LLA, {addr, c}));
            sf.emplace_back(R5AsmStrangeFake(FLW, {R(fa0), P(0), addr}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(FMV_S, {R(fa0), V(fVal->getName(), Float)}));
        }
    } else if (retType == MiddleIRType::INT) {
        auto iVal = retInst->getOpVal();
        if (iVal->isConst()) {
            auto ci = std::dynamic_pointer_cast<R5IRValConstInt>(iVal);
            sf.emplace_back(R5AsmStrangeFake(LI, {R(a0), N(ci->getValue())}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(MV, {R(a0), V(iVal->getName(), Int)}));
        }
    } else if (retType == MiddleIRType::VOID) {
        // do nothing
    } else {
        RUNTIME_ERROR("他妈的不支持的返回值类型, 传了什么东西进来❤受不了了");
    }
    sf.emplace_back(R5AsmStrangeFake(J, {L(funcRetLabel())}));
}
void R5FakeSeihai::handleCallInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto callInst = std::dynamic_pointer_cast<CallInst>(inst1);
    bool useReg;
    int  fRegRes = 8, iRegRes = 8;   // fa0-7, a0-7
    for (const auto& arg : callInst->getArgs()) {
        if (arg->getType()->isFloat()) {
            fRegRes -= 1;
        } else if (arg->getType()->isPointer() || arg->getType()->isInt()) {
            iRegRes -= 1;
        }
    }
    useReg = fRegRes >= 0 && iRegRes >= 0;
    // 特判。如果是@llvm.memset.p0.i32(i32*, i8, i32, i1), 那么应该调用的是memset
    if (callInst->getFunc()->getName() == "@llvm.memset.p0.i32") {
        // a0-2: dst, val, len. val肯定是0. dst是指针，len是整数。
        auto dstTaichi = V(callInst->getArgs()[0]->getName(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(MV, {R(a0), dstTaichi}));
        sf.emplace_back(R5AsmStrangeFake(MV, {R(a1), R(zero)}));
        int len = std::dynamic_pointer_cast<R5IRValConstInt>(callInst->getArgs()[2])->getValue();
        sf.emplace_back(R5AsmStrangeFake(LI, {R(a2), N(len)}));
        sf.emplace_back(R5AsmStrangeFake(CALL, {L("@memset")}));
        return;
    }
    YangReg fReg    = fa0;
    YangReg iReg    = a0;
    int     fArgNum = 8 - fRegRes;   // 浮点参数个数
    int     iArgNum = 8 - iRegRes;   // 整数参数个数
    // 需要额外的栈空间大小（单位：字节）
    int sSizeByte = ((fArgNum > 8 ? fArgNum - 8 : 0) + (iArgNum > 8 ? iArgNum - 8 : 0)) * 8;
    // 不行。我应该先进行实参的标号。
    int argNums[callInst->getArgs().size()];
    int ino = 0;
    int fno = 0;
    for (size_t i = 0; i < callInst->getArgs().size(); i++) {
        if (callInst->getArgs()[i]->getType()->isFloat()) {
            argNums[i] = fno++;
        } else {
            argNums[i] = ino++;
        }
    }
    // 此时，argNums[i]表示第i个参数在具体类型中的序号。比如参数列表是int,int,float,float,int
    // 则argNums[0]=0, argNums[1]=1, argNums[2]=0, argNums[3]=1, argNums[4]=2
    // 压栈操作
    if (sSizeByte > 0) {
        if (couldLoadWithRegImm(sSizeByte)) {
            sf.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N(-sSizeByte)}));
        } else {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(-sSizeByte)}));
            sf.emplace_back(R5AsmStrangeFake(ADD, {R(sp), R(sp), tmp}));
        }
    }
    int64_t curStackOffset = 0;

    for (int j = 0; j < callInst->getArgs().size(); j++) {
        const auto& arg = callInst->getArgs()[j];
        if (arg->getType()->isFloat()) {
            if (arg->isConst()) {
                // 立即数 先存到内存里，然后再加载到寄存器里。
                auto cf   = std::dynamic_pointer_cast<R5IRValConstFloat>(arg);
                auto c    = L(C(cf->getWord()));
                auto addr = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LLA, {addr, c}));
                if (argNums[j] < 8)
                    sf.emplace_back(R5AsmStrangeFake(FLW, {R(fReg), P(0), addr}));
                else {
                    // 压栈
                    auto tmp = V(E(), Pointer);
                    sf.emplace_back(R5AsmStrangeFake(LW, {tmp, addr}));
                    accessStack(sf, SW, tmp, curStackOffset, sp);
                    curStackOffset += 8;
                }
            } else {
                if (argNums[j] < 8)
                    sf.emplace_back(R5AsmStrangeFake(FMV_S, {R(fReg), V(arg->getName(), Float)}));
                else {
                    // 压栈
                    accessStack(sf, FSW, V(arg->getName(), Float), curStackOffset, sp);
                    curStackOffset += 8;
                }
            }
            fReg = (fReg <= fa7) ? (YangReg)((int)fReg + 1) : fa7;
        } else if (arg->getType()->isPointer() || arg->getType()->isInt()) {
            if (arg->isConst()) {
                // pointer不可能是立即数。
                auto intVal = std::dynamic_pointer_cast<R5IRValConstInt>(arg);
                IR_ASSERT(intVal != nullptr, "他妈的Pointer不可能是立即数啊❤受不了了");
                if (argNums[j] < 8)
                    sf.emplace_back(R5AsmStrangeFake(LI, {R(iReg), N(intVal->getValue())}));
                else {
                    // 压栈
                    auto tmp = V(E(), Int);
                    sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(intVal->getValue())}));
                    accessStack(sf, arg->getType()->isPointer() ? SD : SW, tmp, curStackOffset, sp);
                    curStackOffset += 8;
                }
            } else {
                if (argNums[j] < 8)
                    sf.emplace_back(R5AsmStrangeFake(MV, {R(iReg), V(arg->getName(), Pointer)}));
                else {
                    // 压栈
                    accessStack(
                        sf,
                        arg->getType()->isPointer() ? SD : SW,
                        V(arg->getName(), Pointer),
                        curStackOffset,
                        sp
                    );
                    curStackOffset += 8;
                }
            }
            iReg = (iReg <= a7) ? (YangReg)((int)iReg + 1) : a7;
        }
    }
    sf.emplace_back(R5AsmStrangeFake(CALL, {L(callInst->getFunc()->getName())}));
    if (callInst->getRetType() == MiddleIR::MiddleIRType::FLOAT) {
        sf.emplace_back(R5AsmStrangeFake(FMV_S, {V(callInst->getName(), Float), R(fa0)}));
    } else if (callInst->getRetType() == MiddleIR::MiddleIRType::INT) {
        sf.emplace_back(R5AsmStrangeFake(MV, {V(callInst->getName(), Int), R(a0)}));
    }
    // 恢复sp
    if (sSizeByte > 0) {
        if (couldLoadWithRegImm(sSizeByte)) {
            sf.emplace_back(R5AsmStrangeFake(ADDI, {R(sp), R(sp), N(sSizeByte)}));
        } else {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(sSizeByte)}));
            sf.emplace_back(R5AsmStrangeFake(ADD, {R(sp), R(sp), tmp}));
        }
    }
}
void R5FakeSeihai::handleGEPInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto gep   = std::dynamic_pointer_cast<GetElementPtrInst>(inst1);
    auto type1 = gep->getType1();
    auto from  = gep->getFrom();

    std::shared_ptr<R5Taichi> base;
    auto                      to = V(gep->getName(), Pointer);
    if (from->getName()[0] == '%') {
        if (queryInStackSpace(from->getName())) {
            // on stack
            int64_t o = queryStackSpace(from->getName());
            base      = V(E(), Pointer);
            if (couldLoadWithRegImm(o))
                sf.emplace_back(R5AsmStrangeFake(ADDI, {base, R(s0), P(o)}));
            else {
                auto tmp = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp, P(o)}));
                sf.emplace_back(R5AsmStrangeFake(ADD, {base, R(s0), tmp}));
            }
        } else {
            base = V(from->getName(), Pointer);
        }
    } else {
        // 是标签
        auto t = L(from->getName());
        base   = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {base, t}));
    }
    // 此时，base存储的是基地址。

    // a GEP instruction like this:
    // %v1 = getelementptr [3 x [4 x i32]], [3 x [4 x i32]]* %v0, i32 0, i32 0, i32 %v0
    // type1 is [3 x [4 x i32]]
    // type1 may be ArrayType or just a Int/Float.❤
    int64_t                   offset   = 0;
    bool                      immSoFar = true;
    std::shared_ptr<R5Taichi> tmp;
    for (const auto& idx : gep->getIndex()) {
        int64_t curShapeSizeBytes = 0;
        if (auto aType1 = std::dynamic_pointer_cast<ArrayType>(type1)) {
            curShapeSizeBytes = (int64_t)aType1->getSizeBytes();
            type1             = aType1->getElementType();
        } else {
            curShapeSizeBytes = 4;
        }
        if (idx->isConst()) {
            if (immSoFar) {
                // 前面的都是立即数，乘以类型大小。
                offset +=
                    std::dynamic_pointer_cast<R5IRValConstInt>(idx)->getValue() * curShapeSizeBytes;
            } else {
                // 前面的不是立即数，那就先乘以类型大小，然后再加上立即数。
                // tmp2=idx*curShapeSizeBytes; tmp1=tmp2+offset;
                uint64_t tmp2 =
                    std::dynamic_pointer_cast<R5IRValConstInt>(idx)->getValue() * curShapeSizeBytes;
                auto tmp3 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp3, P(tmp2)}));
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp, tmp3}));
            }
        } else {
            if (immSoFar) {
                immSoFar = false;
                // 把之前的结果先存到寄存器中，然后再加上这个变量*类型大小。
                // tmp1=tmp+offset; tmp2=tmp1+idx*curShapeSizeBytes;
                const std::shared_ptr<R5Taichi>& tmp2 = V(E(), Pointer);
                // li
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp2, P(curShapeSizeBytes)}));
                sf.emplace_back(R5AsmStrangeFake(MUL, {tmp2, V(idx->getName(), Int), tmp2}));
                // li offset
                auto tmp4 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp4, P(offset)}));
                // add
                tmp = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp4, tmp4, tmp2}));
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp4, base}));
            } else {
                // tmp1=tmp+offset; tmp2=tmp1+idx*curShapeSizeBytes;
                const std::shared_ptr<R5Taichi>& tmp2 = V(E(), Pointer);
                // li
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp2, P(curShapeSizeBytes)}));
                // mul
                const std::shared_ptr<R5Taichi>& tmp3 = V(E(), Pointer);
                sf.emplace_back(R5AsmStrangeFake(MUL, {tmp3, V(idx->getName(), Pointer), tmp2}));
                // add
                sf.emplace_back(R5AsmStrangeFake(ADD, {tmp, tmp, tmp3}));
            }
        }
    }
    if (immSoFar) {
        // 还有待处理的立即数。
        if(couldLoadWithRegImm(offset))
            sf.emplace_back(R5AsmStrangeFake(ADDI, {to, base, P(offset)}));
        else {
            auto t = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LI, {t, P(offset)}));
            sf.emplace_back(R5AsmStrangeFake(ADD, {to, base, t}));
        }
    } else {
        sf.emplace_back(R5AsmStrangeFake(MV, {to, tmp}));
    }
}
void R5FakeSeihai::handleBrInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1, const string& funcName
)
{
    auto brInst = std::dynamic_pointer_cast<BrInst>(inst1);
    if (brInst->getIfFalse() == nullptr) {
        // 直接插入一条跳转指令,不管比较结果如何，都跳转到ifTrue
        string ifTrueLabel = BN(funcName, brInst->getIfTrueLabel());
        sf.emplace_back(R5AsmStrangeFake(J, {L(ifTrueLabel)}));
    } else {
        // 有两个分支，那就是ifTrue和ifFalse
        // 先进行BNE, 然后J
        auto   cond         = brInst->getCond();
        auto   condName     = cond->getName();
        string ifTrueLabel  = BN(funcName, brInst->getIfTrueLabel());
        string ifFalseLabel = BN(funcName, brInst->getIfFalseLabel());
        sf.emplace_back(R5AsmStrangeFake(BNEZ, {V(condName, Int), L(ifTrueLabel)}));
        sf.emplace_back(R5AsmStrangeFake(J, {L(ifFalseLabel)}));
    }
}
void R5FakeSeihai::handleFCmpInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto fcmp = std::dynamic_pointer_cast<FCmpInst>(inst1);
    auto fOp  = fcmp->getFCmpOp();
    auto op1  = fcmp->getOpVal1();
    auto op2  = fcmp->getOpVal2();
    // 两个操作数都是立即数 则直接比较。然后返回
    if (op1->isConst() && op2->isConst()) {
        auto op1Num = std::dynamic_pointer_cast<R5IRValConstFloat>(op1)->getValue();
        auto op2Num = std::dynamic_pointer_cast<R5IRValConstFloat>(op2)->getValue();
        bool result;
        switch (fOp) {
        case FCmpInst::FCmpOp::FALSE: result = false; break;
        case FCmpInst::FCmpOp::TRUE: result = true; break;
        case FCmpInst::FCmpOp::OEQ:
        case FCmpInst::FCmpOp::UEQ: result = op1Num == op2Num; break;
        case FCmpInst::FCmpOp::OGE:
        case FCmpInst::FCmpOp::UGE: result = op1Num >= op2Num; break;
        case FCmpInst::FCmpOp::OGT:
        case FCmpInst::FCmpOp::UGT: result = op1Num > op2Num; break;
        case FCmpInst::FCmpOp::OLE:
        case FCmpInst::FCmpOp::ULE: result = op1Num <= op2Num; break;
        case FCmpInst::FCmpOp::OLT:
        case FCmpInst::FCmpOp::ULT: result = op1Num < op2Num; break;
        case FCmpInst::FCmpOp::UNE:
        case FCmpInst::FCmpOp::UNO: result = op1Num != op2Num; break;
        }
        if (result) {
            sf.emplace_back(R5AsmStrangeFake(LI, {V(fcmp->getName(), Int), N(1)}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(MV, {V(fcmp->getName(), Int), R(zero)}));
        }
        return;
    }
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    taichi1 = V(op1->getName(), Float);
    taichi2 = V(op2->getName(), Float);
    // 加载数
    if (op1->isConst()) {
        taichi1     = V(E(), Float);
        auto op1Num = std::dynamic_pointer_cast<R5IRValConstFloat>(op1)->getWord();
        auto tmp    = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(C(op1Num))}));
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi1, P(0), tmp}));
    }
    if (op2->isConst()) {
        taichi2     = V(E(), Float);
        auto op2Num = std::dynamic_pointer_cast<R5IRValConstFloat>(op2)->getWord();
        auto tmp    = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(C(op2Num))}));
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi2, P(0), tmp}));
    }


    switch (fOp) {

    case FCmpInst::FCmpOp::FALSE: {
        sf.emplace_back(R5AsmStrangeFake(MV, {V(fcmp->getName(), Int), R(zero)}));
    } break;
    case FCmpInst::FCmpOp::OEQ:
    case FCmpInst::FCmpOp::UEQ: {
        sf.emplace_back(R5AsmStrangeFake(FEQ_S, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::OGE:
    case FCmpInst::FCmpOp::UGE: {
        sf.emplace_back(R5AsmStrangeFake(FLE_S, {V(fcmp->getName(), Int), taichi2, taichi1}));
    } break;
    case FCmpInst::FCmpOp::OGT:
    case FCmpInst::FCmpOp::UGT: {
        sf.emplace_back(R5AsmStrangeFake(FLT_S, {V(fcmp->getName(), Int), taichi2, taichi1}));
    } break;
    case FCmpInst::FCmpOp::OLE:
    case FCmpInst::FCmpOp::ULE: {
        sf.emplace_back(R5AsmStrangeFake(FLE_S, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::OLT:
    case FCmpInst::FCmpOp::ULT: {
        sf.emplace_back(R5AsmStrangeFake(FLT_S, {V(fcmp->getName(), Int), taichi1, taichi2}));
    } break;
    case FCmpInst::FCmpOp::TRUE: {
        sf.emplace_back(R5AsmStrangeFake(LI, {V(fcmp->getName(), Int), N(1)}));
    } break;
    case FCmpInst::FCmpOp::UNO:
    case FCmpInst::FCmpOp::UNE: {
        auto tmp = V(E(), Int);
        sf.emplace_back(R5AsmStrangeFake(FEQ_S, {tmp, taichi1, taichi2}));
        sf.emplace_back(R5AsmStrangeFake(NOT, {V(fcmp->getName(), Int), tmp}));
    } break;
    }
}
void R5FakeSeihai::handleBitcastInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto bitCast = std::dynamic_pointer_cast<BitCastInst>(inst1);
    auto from    = bitCast->getFrom()->getName();
    auto to      = bitCast->getName();
    // 直接mv 错误的。需要判断类型。
    if (queryInStackSpace(from)) {
        // on stack
        int64_t o = queryStackSpace(from);
        if (couldLoadWithRegImm(o))
            sf.emplace_back(R5AsmStrangeFake(ADDI, {V(to, Pointer), R(s0), P(o)}));
        else {
            auto tmp = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, P(o)}));
            sf.emplace_back(R5AsmStrangeFake(ADD, {V(to, Pointer), R(s0), tmp}));
        }
    } else {
        sf.emplace_back(R5AsmStrangeFake(MV, {V(to, Pointer), V(from, Pointer)}));
    }
}
void R5FakeSeihai::handleCvtInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto convertInst = std::dynamic_pointer_cast<ConvertInst>(inst1);
    auto cvtOp       = convertInst->getConvertOp();
    //  SITOFP, FPTOSI 现在只需要实现这两个。
    if (cvtOp == ConvertInst::SITOFP) {
        // 老样子，还是得单独处理立即数。
        if (convertInst->getFrom()->isConst()) {
            // 整数转浮点数，立即数有点捉急。整数需要先li然后FCVT_S_W
            auto tmp = V(E(), Int);
            int  number =
                std::dynamic_pointer_cast<R5IRValConstInt>(convertInst->getFrom())->getValue();
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(number)}));
            sf.emplace_back(R5AsmStrangeFake(FCVT_S_W, {V(convertInst->getName(), Float), tmp}));
        } else {
            // 变量，直接FCVT_S_W
            sf.emplace_back(R5AsmStrangeFake(
                FCVT_S_W,
                {V(convertInst->getName(), Float), V(convertInst->getFrom()->getName(), Int)}
            ));
        }
    } else if (cvtOp == ConvertInst::FPTOSI) {
        if (convertInst->getFrom()->isConst()) {
            // 浮点他妈直接读出来，然后直接li进去就行了。
            float number =
                std::dynamic_pointer_cast<R5IRValConstFloat>(convertInst->getFrom())->getValue();
            sf.emplace_back(R5AsmStrangeFake(LI, {V(convertInst->getName(), Int), N((int)number)}));
        } else {
            // 变量，直接FCVT_W_S
            sf.emplace_back(R5AsmStrangeFake(
                FCVT_W_S,
                {V(convertInst->getName(), Int), V(convertInst->getFrom()->getName(), Float)}
            ));
        }
    } else if (cvtOp == MiddleIR::ConvertInst::ZEXT) {
        // 老样子，还是得单独处理立即数。
        if (convertInst->getFrom()->isConst()) {
            auto tmp = V(E(), Int);
            int  number =
                std::dynamic_pointer_cast<R5IRValConstInt>(convertInst->getFrom())->getValue();
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(number)}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(
                MV, {V(convertInst->getName(), Int), V(convertInst->getFrom()->getName(), Int)}
            ));
        }
    } else {
        // not implemented
        RUNTIME_ERROR("他妈的不支持的Convert类型, 传了什么东西进来❤受不了了");
    }
}
void R5FakeSeihai::handleICmpNoBr(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // 预期指令: SLT SLTI SLTU SLTIU.
    // 如果带等号的，比较之后取反
    auto cmpInst = std::dynamic_pointer_cast<ICmpInst>(inst1);
    auto cmpOp   = cmpInst->getICmpOp();
    auto op1     = cmpInst->getOpVal1();
    auto op2     = cmpInst->getOpVal2();
    // 特殊情况：两个操作数都是立即数
    if (op1->isConst() && op2->isConst()) {
        int  op1Val = std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue();
        int  op2Val = std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue();
        bool result;
        switch (cmpOp) {
        case ICmpInst::EQ: result = op1Val == op2Val; break;
        case ICmpInst::NE: result = op1Val != op2Val; break;
        case ICmpInst::SGT: result = op1Val > op2Val; break;
        case ICmpInst::SGE: result = op1Val >= op2Val; break;
        case ICmpInst::SLT: result = op1Val < op2Val; break;
        case ICmpInst::SLE: result = op1Val <= op2Val; break;
        case ICmpInst::UGE: result = op1Val >= op2Val; break;   // Not supported.
        case ICmpInst::UGT: result = op1Val > op2Val; break;    // Not supported.
        case ICmpInst::ULE: result = op1Val <= op2Val; break;   // Not supported.
        case ICmpInst::ULT: result = op1Val < op2Val; break;    // Not supported.
        }
        // 立即数比较结果，直接写入寄存器
        sf.emplace_back(R5AsmStrangeFake(LI, {V(cmpInst->getName(), Int), N((int)result)}));
    }
    // 两个寄存器
    else if (!(op1->isConst()) && (!op2->isConst())) {
        // 两个操作数都是变量
        // 两个操作数都是变量，那就直接比较就行了。
        shared_ptr<R5Taichi> taichi1 = V(op1->getName(), Int);
        shared_ptr<R5Taichi> taichi2 = V(op2->getName(), Int);
        // 小于号，直接使用SLT
        if (cmpOp == ICmpInst::SLT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi1, taichi2}));
        }
        // 大于号，反过来SLT
        else if (cmpOp == ICmpInst::SGT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi2, taichi1}));
        }
        // 大于等于号，先比较，再取反（强制SSA）
        else if (cmpOp == ICmpInst::SGE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 小于等于号，先反过来比较，再取反
        else if (cmpOp == ICmpInst::SLE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi2, taichi1}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 等于号，先减法，再SNEZ
        else if (cmpOp == ICmpInst::EQ) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SEQZ, {V(cmpInst->getName(), Int), tmp}));
        }
        // 不等于
        else if (cmpOp == ICmpInst::NE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SNEZ, {V(cmpInst->getName(), Int), tmp}));
        } else {
            RUNTIME_ERROR("他妈的不支持的ICMP类型, 传了什么东西进来❤受不了了");
        }
    }
    // 一个寄存器，一个立即数
    else {
        if (op1->isConst()) {
            // 立即数应该在后边
            swap(op1, op2);
        }
        // op1是寄存器，op2是立即数
        shared_ptr<R5Taichi> taichi1   = V(op1->getName(), Int);
        auto                 intValue2 = std::dynamic_pointer_cast<R5IRValConstInt>(op2);
        int                  op2Val    = intValue2->getValue();
        // 总之op2Val需要保存在一个寄存器里。
        shared_ptr<R5Taichi> taichi2;
        if (op2Val == 0) {
            taichi2 = R(zero);
        } else {
            taichi2 = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {taichi2, N(op2Val)}));
        }
        // 小于号，直接使用SLT
        if (cmpOp == ICmpInst::SLT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi1, taichi2}));
        }
        // 大于号，反过来SLT
        else if (cmpOp == ICmpInst::SGT) {
            sf.emplace_back(R5AsmStrangeFake(SLT, {V(cmpInst->getName(), Int), taichi2, taichi1}));
        }
        // 大于等于号，先比较，再取反（强制SSA）
        else if (cmpOp == ICmpInst::SGE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 小于等于号，先反过来比较，再取反
        else if (cmpOp == ICmpInst::SLE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SLT, {tmp, taichi2, taichi1}));
            sf.emplace_back(R5AsmStrangeFake(NOT, {V(cmpInst->getName(), Int), tmp}));
        }
        // 等于号，先减法，再SNEZ
        else if (cmpOp == ICmpInst::EQ) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SEQZ, {V(cmpInst->getName(), Int), tmp}));
        }
        // 不等于
        else if (cmpOp == MiddleIR::ICmpInst::NE) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(SUBW, {tmp, taichi1, taichi2}));
            sf.emplace_back(R5AsmStrangeFake(SNEZ, {V(cmpInst->getName(), Int), tmp}));
        } else {
            RUNTIME_ERROR("他妈的不支持的ICMP类型, 传了什么东西进来❤受不了了");
        }
    }
}

// 这个函数特殊。因为他要处理函数参数列表。
void R5FakeSeihai::handleStoreInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto storeInst = std::dynamic_pointer_cast<StoreInst>(inst1);
    auto from      = storeInst->getFrom();
    // 短路处理from事arg的情况。
    if (from->getName().substr(0, 5) == "%arg_") {
        handleArgStoreInst(sf, storeInst);
        return;
    }
    auto    to      = storeInst->getTo();
    bool    isFloat = from->getType()->isFloat();
    FakeOPs op      = isFloat ? FSW : SW;
    // 草，好像有bug。要是存储的是个指针，就不能用FSW/SW，就得用SD
    if (from->getType()->isPointer()) { op = SD; }
    shared_ptr<R5Taichi> rs;
    shared_ptr<R5Taichi> rt;
    // 先检查rt是全局还是栈
    auto name     = to->getName();
    bool onStack  = queryInStackSpace(name);
    bool isGlobal = name[0] == '@';
    if (onStack) {
        // 栈
        uint64_t offset = queryStackSpace(to->getName());
        rt              = P(offset);
        onStack         = true;
    } else if (isGlobal) {
        // 全局
        rt      = L(to->getName());
        onStack = false;
    } else {
        // GetElementPtrInst的结果
        rt = V(to->getName(), Pointer);
    }
    // 是不是立即数
    if (from->isConst()) {
        // 立即数有点捉急。因为他妈的，立即数不能直接存到内存里。
        if (isFloat) {
            string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(from)->getWord());
            auto   tmp       = V(E(), Pointer);
            sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
            rs = V(E(), Float);
            sf.emplace_back(R5AsmStrangeFake(FLW, {rs, P(0), tmp}));
        } else {
            auto tmp = V(E(), Int);
            // li
            sf.emplace_back(R5AsmStrangeFake(
                LI, {tmp, N(std::dynamic_pointer_cast<R5IRValConstInt>(from)->getValue())}
            ));
            rs = tmp;
        }
        // 此时立即数已经在rs里了。
    } else {
        // 变量
        rs = V(from->getName(), isFloat ? Float : Int);
    }
    if (onStack) {
        int64_t of = (dynamic_pointer_cast<R5Lai64>(rt))->value;
        accessStack(sf, op, rs, of, s0);
    } else if (isGlobal) {
        // lla+fsw/sw，此时rt是个label
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, rt}));
        sf.emplace_back(R5AsmStrangeFake(op, {rs, P(0), tmp}));
    } else {
        // GetElementPtrInst的结果
        sf.emplace_back(R5AsmStrangeFake(op, {rs, P(0), rt}));
    }
}

void R5FakeSeihai::handleArgStoreInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto storeInst  = dynamic_pointer_cast<StoreInst>(inst1);
    auto valType    = storeInst->getFrom()->getType()->type;
    auto fromName   = storeInst->getFrom()->getName();
    auto toName     = storeInst->getTo()->getName();
    auto destOffset = queryStackSpace(toName);
    if (valType == MiddleIR::MiddleIRType::INT || valType == MiddleIR::MiddleIRType::POINTER) {
        const auto saveInst = valType == MiddleIR::MiddleIRType::POINTER ? SD : SW;
        const auto loadInst = valType == MiddleIR::MiddleIRType::POINTER ? LD : LW;
        if (funcIntArgCount < 8) {
            // 将a0+funcIntArgCount
            accessStack(sf, saveInst, R((YangReg)(a0 + funcIntArgCount)), destOffset, s0);
        } else {
            // 来吧，**栈
            // 我们通过s0寻址
            int64_t argOffs0 = funcStackArgCount * 8;
            auto    tmp      = V(E(), Pointer);
            accessStack(sf, loadInst, tmp, argOffs0, s0);
            accessStack(sf, saveInst, tmp, destOffset, s0);
            funcStackArgCount++;
        }
        funcIntArgCount++;
    } else if (valType == MiddleIR::MiddleIRType::FLOAT) {
        if (funcFloatArgCount < 8) {
            accessStack(sf, FSW, R((YangReg)(fa0 + funcFloatArgCount)), destOffset, s0);
        } else {
            int64_t argOffs0 = funcStackArgCount * 8;
            auto    tmp      = V(E(), Pointer);
            accessStack(sf, LW, tmp, argOffs0, s0);
            accessStack(sf, SW, tmp, destOffset, s0);
            funcStackArgCount++;
        }
        funcFloatArgCount++;
    }
}
void R5FakeSeihai::handleLoadInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto                 loadInst = std::dynamic_pointer_cast<LoadInst>(inst1);
    bool                 isFloat  = loadInst->getType()->isFloat();
    FakeOPs              op       = isFloat ? FLW : LW;
    shared_ptr<R5Taichi> rd       = V(loadInst->getName(), isFloat ? Float : Int);
    // 等会，如果需要加载的是个指针，那就不能用FLW/LW，得用LD
    if (loadInst->getType()->isPointer()) { op = LD; }
    // 我草，load可能从栈里读，也可能从全局变量里读。这该如何是好？
    string rsName = loadInst->getOpVal()->getName();
    // 他妈的，如果是全局变量，那就是@开头的，如果是栈变量，那就是%开头的
    // 草，应该没别的情况了吧？
    // 有！ 还可能是GetElementPtrInst的结果！
    bool isGlobal = rsName[0] == '@';
    bool onStack  = queryInStackSpace(rsName);
    if (isGlobal) {
        // 全局变量 草，这个时候，rsName是一个label
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(rsName)}));
        sf.emplace_back(R5AsmStrangeFake(op, {rd, P(0), tmp}));
    } else if (onStack) {
        // 栈变量
        int64_t offset = queryStackSpace(rsName);
        accessStack(sf, op, rd, offset, s0);
    } else {
        // GetElementPtrInst的结果
        sf.emplace_back(R5AsmStrangeFake(op, {rd, P(0), V(rsName, Pointer)}));
    }
}
void R5FakeSeihai::handleAllocaInst(const shared_ptr<MiddleIRInst>& inst1)
{
    // 更新太极图，把虚拟寄存器和栈地址绑定
    auto    allocaInst = std::dynamic_pointer_cast<AllocaInst>(inst1);
    auto    innerType  = dynamic_pointer_cast<PointerType>(inst1->getType())->getElementType();
    auto    name       = allocaInst->getName();
    int64_t size;
    if (innerType->isFloat() || innerType->isInt())
        size = 4;
    else if (innerType->isPointer())
        size = 8;
    else if (innerType->isArray()) {
        const auto& arrayTypeI = innerType;
        auto        arrayType  = std::dynamic_pointer_cast<ArrayType>(arrayTypeI);
        size                   = (int64_t)arrayType->getSizeBytes();
    } else
        RUNTIME_ERROR("他妈的不支持的alloca类型, 传了什么东西进来❤受不了了");
    allocateStackSpace(name, size);
}
void R5FakeSeihai::handleFMathInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    auto                 fMath = std::dynamic_pointer_cast<FMathInst>(inst1);
    auto                 fOp   = fMath->getFMathOp();
    auto                 op1   = fMath->getOpVal1();
    auto                 op2   = fMath->getOpVal2();
    auto                 rd    = V(fMath->getName(), Float);
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    // check if op1 or op2 is const. if const, we need to LI it first and move it to a float
    // register
    if (op1->isConst()) {
        // 先需要把立即数装载到整数寄存器里。之后再转换成浮点数寄存器
        // 太蠢了。gcc的做法是把立即数装载到内存里，然后再从内存里装载到浮点数寄存器里
        string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(op1)->getWord());
        // LLA and FLW
        auto tmp = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
        taichi1 = V(E(), Float);
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi1, P(0), tmp}));
    } else {
        taichi1 = V(op1->getName(), Float);
    }
    if (op2->isConst()) {
        string newCLabel = C(std::dynamic_pointer_cast<R5IRValConstFloat>(op2)->getWord());
        auto   tmp       = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LLA, {tmp, L(newCLabel)}));
        taichi2 = V(E(), Float);
        sf.emplace_back(R5AsmStrangeFake(FLW, {taichi2, P(0), tmp}));
    } else {
        taichi2 = V(op2->getName(), Float);
    }
    // 现在可以保证两个太极都是浮点寄存器
    switch (fOp) {
    case FMathInst::FADD: {
        sf.emplace_back(R5AsmStrangeFake(FADD_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FSUB: {
        sf.emplace_back(R5AsmStrangeFake(FSUB_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FMUL: {
        sf.emplace_back(R5AsmStrangeFake(FMUL_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FDIV: {
        sf.emplace_back(R5AsmStrangeFake(FDIV_S, {rd, taichi1, taichi2}));
    } break;
    case FMathInst::FREM: RUNTIME_ERROR("他妈的没有浮点数取余");
    }
}
void R5FakeSeihai::handleIMathInst(
    vector<R5AsmStrangeFake>& sf, const shared_ptr<MiddleIRInst>& inst1
)
{
    // only INT, float will be handled later in isFMathInst()
    auto                 math    = std::dynamic_pointer_cast<IMathInst>(inst1);
    auto                 iMathOp = math->getIMathOp();
    shared_ptr<R5Taichi> taichi1;
    shared_ptr<R5Taichi> taichi2;
    shared_ptr<R5Taichi> rd;
    auto                 op1 = math->getOpVal1();
    if (op1->isConst())
        taichi1 = N(std::dynamic_pointer_cast<R5IRValConstInt>(op1)->getValue());   // const LAI
    else
        taichi1 = V(op1->getName(), Int);   // var YIN
    auto op2 = math->getOpVal2();
    if (op2->isConst())
        taichi2 = N(std::dynamic_pointer_cast<R5IRValConstInt>(op2)->getValue());
    else
        taichi2 = V(op2->getName(), Int);
    bool isI =
        (taichi1->isLai() || taichi2->isLai()
        );   // 这里从前端中就已经确定不可能是两个立即数相运算。
    rd = V(math->getName(), Int);
    FakeOPs op;
    switch (iMathOp) {
        // todo
        // 如果他妈的是立即数，并且还是需要LUI那种，就不能直接使用ADDI等指令了。交给@ZZZCOLA处理。
        // 留言：注意使用严格的SSA，不要出现同一个寄存器被多次写入的情况。

    case IMathInst::IMathOp::ADD: {
        if (taichi1->isLai()) S(taichi1, taichi2);
        if (taichi2->isLai()) {
            int num = dynamic_pointer_cast<R5Lai>(taichi2)->value;
            if (!couldLoadWithRegImm(num)) {
                auto tmp = V(E(), Int);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(num)}));
                sf.emplace_back(R5AsmStrangeFake(ADDW, {rd, taichi1, tmp}));
            } else {
                sf.emplace_back(R5AsmStrangeFake(ADDIW, {rd, taichi1, N(num)}));
            }
        } else {
            sf.emplace_back(R5AsmStrangeFake(ADDW, {rd, taichi1, taichi2}));
        }
    } break;

    case IMathInst::IMathOp::SUB: {
        if (isI) {
            bool needNeg = false;
            if (taichi1->isLai()) {
                needNeg = true;
                S(taichi1, taichi2);
            }
            dynamic_pointer_cast<R5Lai>(taichi2)->negative();
            int num = dynamic_pointer_cast<R5Lai>(taichi2)->value;
            if (!couldLoadWithRegImm(num)) {
                auto tmp = V(E(), Int);
                sf.emplace_back(R5AsmStrangeFake(LI, {tmp, N(num)}));
                sf.emplace_back(R5AsmStrangeFake(ADDW, {rd, taichi1, tmp}));
            } else {
                sf.emplace_back(R5AsmStrangeFake(ADDIW, {rd, taichi1, N(num)}));
            }
            if (needNeg) sf.emplace_back(R5AsmStrangeFake(NEGW, {rd, rd}));
        } else {
            sf.emplace_back(R5AsmStrangeFake(SUBW, {rd, taichi1, taichi2}));
        }
    } break;

    case IMathInst::IMathOp::MUL: {
        // 乘法要求两个操作数都是寄存器
        // 不是的话，就要先把立即数装载到寄存器里
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(MULW, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::SDIV: {
        // 除法要求两个操作数都是寄存器
        // 不是的话，就要先把立即数装载到寄存器里
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(DIVW, {rd, taichi1, taichi2}));
    } break;

    case IMathInst::IMathOp::SREM: {
        // 同上。
        if (taichi1->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi1}));
            taichi1 = tmp;
        }
        if (taichi2->isLai()) {
            auto tmp = V(E(), Int);
            sf.emplace_back(R5AsmStrangeFake(LI, {tmp, taichi2}));
            taichi2 = tmp;
        }
        sf.emplace_back(R5AsmStrangeFake(REMW, {rd, taichi1, taichi2}));
    } break;
    case IMathInst::IMathOp::UDIV:
    case IMathInst::IMathOp::UREM: RUNTIME_ERROR("他妈的没有无符号除法和取余");
    }
}

/// 在栈上为name分配size字节大小的空间
/// \param name 虚拟寄存器的名字
/// \param size 要分配的大小
void R5FakeSeihai::allocateStackSpace(const string& name, int64_t size)
{
    taichiMap.allocate(name, size);
}
int64_t R5FakeSeihai::queryStackSpace(const string& name)
{
    return taichiMap.query(name);
}
/// 查询一个虚拟寄存器是不是alloca在栈上
/// \param name 虚拟寄存器的名字
/// \return 在栈上返回true，否则返回false
bool R5FakeSeihai::queryInStackSpace(const string& name)
{
    return taichiMap.query(name) != -1;
}
/// 生成函数的返回标签名字
/// \return 如你所愿
string R5FakeSeihai::funcRetLabel()
{
    return ".LRET_" + thisFunc->getName().substr(1);
}

string R5FakeSeihai::funcEntryLabel()
{
    return ".LENT" + thisFunc->getName().substr(1);
}
string R5FakeSeihai::funcFirstBBLabel()
{
    return BN(thisFunc->getName(), "LEntry");
}
// OP dst, imm, reg
void R5FakeSeihai::accessStack(
    vector<R5AsmStrangeFake>&   sf,
    FakeOPs                     op,
    const shared_ptr<R5Taichi>& op1,
    int64_t                     offset,
    YangReg                     st
)
{
    if (couldLoadWithRegImm(offset)) {
        // 可以用SW
        sf.emplace_back(R5AsmStrangeFake(op, {op1, P(offset), R(st)}));
    } else {
        // 先LI，再SW
        auto tmp0 = V(E(), Pointer);
        sf.emplace_back(R5AsmStrangeFake(LI, {tmp0, P(offset)}));
        sf.emplace_back(R5AsmStrangeFake(ADD, {tmp0, tmp0, R(st)}));
        sf.emplace_back(R5AsmStrangeFake(op, {op1, P(0), tmp0}));
    }
}

void R5FakeSeihai::accessStackWithTmp(
    vector<R5AsmStrangeFake>&   sf,
    FakeOPs                     op,
    const shared_ptr<R5Taichi>& op1,
    int64_t                     offset,
    YangReg                     st,
    YangReg                     tmp
)
{
    if (couldLoadWithRegImm(offset)) {
        // 可以用SW
        sf.emplace_back(R5AsmStrangeFake(op, {op1, P(offset), R(st)}));
    } else {
        // 先LI，再SW
        sf.emplace_back(R5AsmStrangeFake(LI, {R(tmp), P(offset)}));
        sf.emplace_back(R5AsmStrangeFake(ADD, {R(tmp), R(tmp), R(st)}));
        sf.emplace_back(R5AsmStrangeFake(op, {op1, P(0), R(tmp)}));
    }
}


/// 生成一个内存中常亮的标签，存储常量值，并且返回这个标签的名字
/// \tparam T Int/Float
/// \param v 数
/// \return 标签名字
template<class T>
string R5FakeSeihai::C(T v)
{
    uint32_t word = *(uint32_t*)&v;
    string   labelName =
        ".LC_" + thisFunc->getName().substr(1) + "_" + std::to_string(extTempMemVarNum++);
    constMem[labelName] = word;
    return labelName;
}

#pragma clang diagnostic pop


}   // namespace R5Emitter
#undef SP