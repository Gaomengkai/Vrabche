//
// Created by gaome on 2023/7/28.
//

#include "R5RegDispatcher.h"
#include <set>
#include <map>
namespace R5Emitter
{

// 优先级顺序，整数：a4-a7, a0-a3, t0-t6, s0-s11, fs0-fs11
// 浮点：fa4-fa7, fa0-fa3, ft0-ft6, fs0-fs11
std::map<YangReg, int> regPri{
    {a4, 0},   {a5, 1},   {a6, 2},   {a7, 3},   {a2, 4},   {a3, 5},   {a0, 6},
    {a1, 7},   {t0, 8},   {t1, 9},   {t2, 10},  {t3, 11},  {t4, 12},  {t5, 13},
    {t6, 14},  {s1, 16},  {s2, 17},  {s3, 18},  {s4, 19},  {s5, 20},  {s6, 21},
    {s7, 22},  {s8, 23},  {fa4, 25}, {fa5, 26}, {fa6, 27}, {fa7, 28}, {fa2, 29}, {fa3, 30}, {fa0, 31},
    {fa1, 32}, {ft0, 33}, {ft1, 34}, {ft2, 35}, {ft3, 36}, {ft4, 37}, {ft5, 38}, {ft6, 39},
    {fs0, 40}, {fs1, 41}, {fs2, 42}, {fs3, 43}, {fs4, 44}, {fs5, 45}, {fs6, 46}, {fs7, 47},
    {fs8, 48},
};

void R5RegDispatcher::insertReg(std::set<RPri>& regs, YangReg r)
{
    regs.insert({r, regPri[r]});
}
R5RegDispatcher::R5RegDispatcher(R5TaichiMap& taichiMap_, const LifespanMap& lsMap_)
    : taichiMap(taichiMap_), lsMap(lsMap_)
{
    for (auto [k, _] : regPri) {
        if (isFloat(k))
            insertReg(freeFRegs, k);
        else
            insertReg(freeIRegs, k);
    }
}
void R5RegDispatcher::releaseIV(const string& vName)
{
    YangReg r = queryReg(vName);
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        freeIRegs.insert({r, regPri[r]});
        var2Reg.erase(vName);
        reg2Var.erase(r);
    } else {
        auto q = taichiMap.query(preTaichi(vName));
        if(q!=-1) {
            taichiMap.release(preTaichi(vName));
        }
    }
}
void R5RegDispatcher::releaseFV(const string& vName)
{
    YangReg r = queryReg((vName));
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        freeFRegs.insert({r, regPri[r]});
        var2Reg.erase((vName));
        reg2Var.erase(r);
    } else {
        auto q = taichiMap.query(preTaichi(vName));
        if(q!=-1) {
            taichiMap.release(preTaichi(vName));
        }
    }
}
void R5RegDispatcher::releaseV(const string& vName)
{
    YangReg r = queryReg((vName));
    if (r != InvalidReg) {
        nowUsedRegs.erase(r);
        if (isFloat(r))
            freeFRegs.insert({r, regPri[r]});
        else
            freeIRegs.insert({r, regPri[r]});
        var2Reg.erase((vName));
        reg2Var.erase(r);
    } else {
        auto q = taichiMap.query(preTaichi(vName));
        if(q!=-1) {
            taichiMap.release(preTaichi(vName));
        }
    }
}
void R5RegDispatcher::releaseIR(YangReg r)
{
    return releaseR(r);
}
void R5RegDispatcher::releaseFR(YangReg r)
{
    return releaseR(r);
}
void R5RegDispatcher::releaseR(YangReg r)
{
    auto& freeRegs = isFloat(r) ? freeFRegs : freeIRegs;
    if (r == InvalidReg) return;
    nowUsedRegs.erase(r);
    freeRegs.insert({r, regPri[r]});
    var2Reg.erase(reg2Var[r]);
    reg2Var.erase(r);
}
YangReg R5RegDispatcher::allocateV(const string& vName, bool isFloat) {
    auto& freeRegs = isFloat ? freeFRegs : freeIRegs;
    YangReg r = queryReg(vName);
    if (r != InvalidReg) return r;
    // 不剩了❤一滴都不剩了
    if (freeRegs.empty()) {
        // allocate stack here.
        allocateStack(vName, 8);
        return InvalidReg;
    }
    std::set<YangReg> tempRemove;
    const auto& vLS = lsMap.at(vName);
    while(!freeRegs.empty()) {
        auto reg = (*freeRegs.begin()).reg;
        freeRegs.erase(freeRegs.begin());
        if(lsMap.find(R5Yang::toString(reg))!=lsMap.end()){
            // the reg was pre-allocated. we need to check if it is still alive.
            const auto& regLS = lsMap.at(R5Yang::toString(reg));
            if(regLS^vLS) {
                tempRemove.insert(reg);
                // 冲突
                continue;
            }
        }
        // 恢复拿走的
        for(auto& rtt:tempRemove) {
            freeRegs.insert({rtt, regPri[rtt]});
        }
        nowUsedRegs.insert(reg);
        totalUsedRegs.insert(reg);
        reg2Var[reg]   = vName;
        var2Reg[vName] = reg;
        return reg;
    }
    // 恢复拿走的
    for(auto& rtt:tempRemove) {
        freeRegs.insert({rtt, regPri[rtt]});
    }
    // 很遗憾，没有找到合适的寄存器
    allocateStack(vName, 8);
    return InvalidReg;
}
YangReg R5RegDispatcher::allocateIV(const string& vName)
{
    return allocateV(vName, false);
}
YangReg R5RegDispatcher::allocateFV(const string& vName)
{
    return allocateV(vName, true);
}
YangReg R5RegDispatcher::allocateIR(YangReg r)
{
    return allocateR(r);
}
YangReg R5RegDispatcher::allocateFR(YangReg r)
{
    return allocateR(r);
}
YangReg R5RegDispatcher::allocateR(YangReg r)
{
    std::set<RPri>& freeRegs = isFloat(r) ? freeFRegs : freeIRegs;
    if (r == InvalidReg) return r;
    if (freeRegs.empty()) {
        // allocate stack here.
        return InvalidReg;
    }
    // freeFRegs.erase(freeFRegs.begin()); not works.
    freeRegs.erase({r, regPri[r]});
    nowUsedRegs.insert(r);
    totalUsedRegs.insert(r);
    return r;
}
int64_t R5RegDispatcher::queryStackOffset(const string& vName)
{
    return taichiMap.query(preTaichi(vName));
}
int64_t R5RegDispatcher::allocateStack(const string& vName, int64_t sz)
{
    return taichiMap.allocate(preTaichi(vName), sz);
}
YangReg R5RegDispatcher::queryReg(const string& vName)
{
    if (var2Reg.find(vName) != var2Reg.end())
        return var2Reg[vName];
    else
        return InvalidReg;
}
std::set<YangReg> R5RegDispatcher::getNowUsedRegs()
{
    return nowUsedRegs;
}
YangReg R5RegDispatcher::getReservedIReg(int index)
{
    if(index<1) index=1;
    if(index>3) index=3;
    return (YangReg)(s9+index-1);
}

YangReg R5RegDispatcher::getReservedFReg(int index)
{
    if(index<1) index=1;
    if(index>3) index=3;
    return (YangReg)(fs9+index-1);
}

bool R5RegDispatcher::isFloat(YangReg r)
{
    return R5Yang::isFloatReg(r);
}
bool R5RegDispatcher::isInt(YangReg r)
{
    return R5Yang::isIntReg(r);
}
string R5RegDispatcher::preTaichi(const string& vName)
{
    return "!" + vName;
}
const std::set<YangReg>& R5RegDispatcher::getTotalUsedRegs() const
{
    return totalUsedRegs;
}
}   // namespace R5Emitter