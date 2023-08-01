//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5YANG_H
#define IRBACKENDR5_R5YANG_H

#include "R5Taichi.h"
namespace R5Emitter
{

// ☰, ☱, ☲, ☳
// ䷗䷚䷂䷩䷲䷔䷐䷘䷣䷕䷾䷤䷶䷝䷰䷌䷒䷨䷻䷼䷵䷥䷹䷉䷊䷙䷄䷈䷡䷍䷪䷀
// 阳，乾，天，刚，健，父，君，君子，圣人，圣贤，圣人之道，
// 于编译器后端，于刚，于健，于父，于君，于物理寄存器
// clang-format off
// 五种寄存器对应五行
enum YangReg { zero,                                     // 零寄存器属金，金性刚硬，坚不可摧
        ra, sp, gp, tp,                                  // 栈帧和全局指针属土，土性厚重，沉稳沉着
        t0, t1, t2, t3, t4, t5, t6,                      // t寄存器属木，木性刚健，生长繁茂
        a0, a1, a2, a3, a4, a5, a6, a7,                  // a寄存器属火，火性炎热，烧灼燃烧
        s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11,// s寄存器属水，水性柔润，滋润滋养
        ft0, ft1, ft2, ft3, ft4, ft5, ft6, ft7, ft8, ft9, ft10, ft11,
        fa0, fa1, fa2, fa3, fa4, fa5, fa6, fa7,
        fs0, fs1, fs2, fs3, fs4, fs5, fs6, fs7, fs8, fs9, fs10, fs11,
        YangRegCount, InvalidReg = -1
} ;

extern YangReg YangRegs[YangRegCount];
// clang-format on

class R5Yang : public R5Taichi
{
public:
    [[nodiscard]] string toString() const override;
    static string        toString(YangReg reg);
    static inline bool   isFloatReg(YangReg r) { return r >= ft0 && r <= fs11; }
    static inline bool   isIntReg(YangReg r) { return r >= zero && r <= s11; }

public:
    YangReg reg;
    bool    operator==(const R5Taichi& rhs) const override;
    bool    operator!=(const R5Taichi& rhs) const override;

    static inline bool isCallerSave(size_t reg)
    {
        return (reg >= t0 && reg <= t6) || (reg >= a0 && reg <= a7) ||
               (reg >= ft0 && reg <= ft11) || (reg >= fa0 && reg <= fa7);
    }
    static inline bool isCalleeSave(size_t reg)
    {
        return (reg >= s0 && reg <= s11) || (reg >= fs0 && reg <= fs11);
    }

    [[nodiscard]] inline bool isCallerSave() const { return isCallerSave(reg); }
    [[nodiscard]] inline bool isCalleeSave() const { return isCalleeSave(reg); }
    explicit R5Yang(YangReg reg_)
        : R5Taichi(Yang)
        , reg(reg_)
    {
    }
    string toString(bool onEmitting) const override;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5YANG_H
