//
// Created by gaome on 2023/7/20.
//

#include "R5Yang.h"

namespace R5Emitter
{
string R5Yang::toString() const
{
    return toString(reg);
}
bool R5Yang::operator==(const R5Taichi& rhs) const
{
    return R5Taichi::operator==(rhs) && reg == dynamic_cast<const R5Yang&>(rhs).reg;
}
bool R5Yang::operator!=(const R5Taichi& rhs) const
{
    return R5Taichi::operator!=(rhs) || reg != dynamic_cast<const R5Yang&>(rhs).reg;
}
string R5Yang::toString(YangReg reg)
{

    switch (reg) {
    case zero: return "zero";
    case ra: return "ra";
    case sp: return "sp";
    case gp: return "gp";
    case tp: return "tp";
    case t0: return "t0";
    case t1: return "t1";
    case t2: return "t2";
    case t3: return "t3";
    case t4: return "t4";
    case t5: return "t5";
    case t6: return "t6";
    case a0: return "a0";
    case a1: return "a1";
    case a2: return "a2";
    case a3: return "a3";
    case a4: return "a4";
    case a5: return "a5";
    case a6: return "a6";
    case a7: return "a7";
    case s0: return "s0";
    case s1: return "s1";
    case s2: return "s2";
    case s3: return "s3";
    case s4: return "s4";
    case s5: return "s5";
    case s6: return "s6";
    case s7: return "s7";
    case s8: return "s8";
    case s9: return "s9";
    case s10: return "s10";
    case s11: return "s11";
    case ft0: return "ft0";
    case ft1: return "ft1";
    case ft2: return "ft2";
    case ft3: return "ft3";
    case ft4: return "ft4";
    case ft5: return "ft5";
    case ft6: return "ft6";
    case ft7: return "ft7";
    case ft8: return "ft8";
    case ft9: return "ft9";
    case ft10: return "ft10";
    case ft11: return "ft11";
    case fa0: return "fa0";
    case fa1: return "fa1";
    case fa2: return "fa2";
    case fa3: return "fa3";
    case fa4: return "fa4";
    case fa5: return "fa5";
    case fa6: return "fa6";
    case fa7: return "fa7";
    case fs0: return "fs0";
    case fs1: return "fs1";
    case fs2: return "fs2";
    case fs3: return "fs3";
    case fs4: return "fs4";
    case fs5: return "fs5";
    case fs6: return "fs6";
    case fs7: return "fs7";
    case fs8: return "fs8";
    case fs9: return "fs9";
    case fs10: return "fs10";
    case fs11: return "fs11";
    case YangRegCount: return "YangRegCount";
    }
    return "Unknown";
}
string R5Yang::toString(bool onEmitting) const
{
    return toString();
}
YangReg YangRegs[YangRegCount] = {
    zero,                 // 零寄存器属金，金性刚硬，坚不可摧
    ra,   sp,  gp,  tp,   // 栈帧和全局指针属土，土性厚重，沉稳沉着
    t0,   t1,  t2,  t3,  t4,  t5,  t6,        // t寄存器属木，木性刚健，生长繁茂
    a0,   a1,  a2,  a3,  a4,  a5,  a6,  a7,   // a寄存器属火，火性炎热，烧灼燃烧
    s0,   s1,  s2,  s3,  s4,  s5,  s6,  s7,  s8,  s9,  s10,  s11,   // s寄存器属水，水性柔润，滋润滋养
    ft0,  ft1, ft2, ft3, ft4, ft5, ft6, ft7, ft8, ft9, ft10, ft11, fa0, fa1, fa2,  fa3,
    fa4,  fa5, fa6, fa7, fs0, fs1, fs2, fs3, fs4, fs5, fs6,  fs7,  fs8, fs9, fs10, fs11,
};
}   // namespace R5Emitter