//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5ASMSTRANGEFAKE_H
#define IRBACKENDR5_R5ASMSTRANGEFAKE_H
#include <forward_list>
#include "R5Def.h"
#include "R5Taichi.h"
#include "R5Yang.h"
#include "R5Yin.h"
namespace R5Emitter
{
// clang-format off
enum FakeOPs {
    FAKEOPS_BEGIN, NOP,
    // RV64I
    LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LW, SW, ADDIW, ADDW, SUBW, SLT, SLTU, LD, SD,
    NEG, SRAIW,
    // 64bit pointer
    ADD, SUB, SLL, SRL, SRA, AND, OR, XOR, SLLI, SRLI, SRAI, ANDI, ORI, XORI, ADDI,
    // RV64M
    MULW, DIVW, REMW, MUL, DIV, REM,
    // RV64F , convert
    FLW, FSW, FCVT_S_W, FCVT_W_S, FMV_X_S, FMV_S_X,
    // RV64F, Calculate
    FADD_S, FSUB_S, FMUL_S, FDIV_S, FSGNJ_S, FSGNJN_S, FSGNJX_S, FMIN_S, FMAX_S, FSQRT_S,
    FLT_S, FEQ_S, FLE_S,
    // RV64F(32F) move
    FMV_S,
    // RV64F, R4
    FMADD_S, FMSUB_S, FNMADD_S, FNMSUB_S,
    // Psuedo
    J, CALL, BGT, BLE, LI, LA, LLA, MV, RET, NOT, NEGW, SEQZ, SNEZ, SLTZ, SGTZ,
    BEQZ, BNEZ, BLEZ, BGEZ, BGTZ, BLTZ, BGTU, BLEU,

    FAKEOPS_END
};
// clang-format on

// 汇编，奇异赝品
struct R5AsmStrangeFake {
    // clang-format off
    enum OPType {
        I, R, R4, UJ, S, SB, U
    };
    // clang-format on

    static const int     R5_MAX_ARG_NUM = 4;
    FakeOPs              fakeOP         = FAKEOPS_BEGIN;
    int8_t               opNum          = 0;
    shared_ptr<R5Taichi> operands[R5_MAX_ARG_NUM]{};
    enum DefUse { DEF, USE, UNUSED };
    DefUse defUse[4] = {UNUSED, UNUSED, UNUSED, UNUSED};
    // 对于带括号的指令，括号外边的写前边。比如sd r2, 0(r3)。写成sd, {r2,0,r3}
    R5AsmStrangeFake(FakeOPs oPs, std::initializer_list<shared_ptr<R5Taichi>>&& operands_);

    static string                           FakeOPToString(FakeOPs op);
    string                                  toString();
    string                                  toString(bool onEmitting);
    std::forward_list<shared_ptr<R5Taichi>> getUsedRegs();
    shared_ptr<R5Taichi>                    getDefReg();
    ~R5AsmStrangeFake() = default;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5ASMSTRANGEFAKE_H
