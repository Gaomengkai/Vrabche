//
// Created by gaome on 2023/7/28.
//

#ifndef IRBACKENDR5_R5REGDISPATCHER_H
#define IRBACKENDR5_R5REGDISPATCHER_H
#include "R5Yang.h"
#include "R5Yin.h"
#include "R5TaichiMap.h"
#include <set>
#include <map>
#include "Phoenix.h"
namespace R5Emitter
{

class R5RegDispatcher
{
public:
    explicit R5RegDispatcher(R5TaichiMap& taichiMap_, const LifespanMap& lsMap_);
    void    releaseIV(const string& vName);
    void    releaseFV(const string& vName);
    void    releaseV(const string& vName);
    void    releaseIR(YangReg r);
    void    releaseFR(YangReg r);
    void    releaseR(YangReg r);
    YangReg allocateIV(const string& vName);
    YangReg allocateFV(const string& vName);
    YangReg allocateIR(YangReg r);
    YangReg allocateFR(YangReg r);
    YangReg allocateR(YangReg r);
    YangReg allocateHard(const string& vName, YangReg r);
    void allocateHardOffset(const string& vName, int64_t offset);

    /// 查询变量在栈上的偏移
    /// \param vName
    /// \return 如果变量在栈上，返回偏移（相对于sp）；否则返回-1
    int64_t queryStackOffset(const string& vName);
    /// 查询已经分配的寄存器
    /// \param vName 虚拟寄存器名字
    /// \return 如果已经分配，返回寄存器；否则返回InvalidReg
    YangReg           queryReg(const string& vName);
    std::set<YangReg> getNowUsedRegs();
    static YangReg    getReservedIReg(int index);
    static YangReg    getReservedFReg(int index);

private:
    struct RPri {
        YangReg reg;
        int     pri;
        bool    operator<(const RPri& rhs) const { return pri < rhs.pri; }
        bool    operator==(const RPri& rhs) const { return reg == rhs.reg && pri == rhs.pri; }
        bool    operator!=(const RPri& rhs) const { return !(*this == rhs); }
    };
    // 太极图引用。用于记录、分配栈空间。
    // 太极图是在函数层面的。
    R5TaichiMap&      taichiMap;
    static bool       isFloat(YangReg r);
    static bool       isInt(YangReg r);
    static string     preTaichi(const string& vName);
    std::set<YangReg> totalUsedRegs;
    const LifespanMap& lsMap;

public:
    [[nodiscard]] const std::set<YangReg>& getTotalUsedRegs() const;

private:
    std::set<YangReg>         nowUsedRegs;
    std::set<RPri>            freeIRegs;
    std::set<RPri>            freeFRegs;
    std::map<YangReg, string> reg2Var;
    std::map<string, YangReg> var2Reg;
    std::unordered_map<string, int64_t> extArgStackOffset;
    static void               insertReg(std::set<RPri>& regs, YangReg r);
    int64_t                   allocateStack(const string& vName, int64_t sz);
    YangReg                   allocateV(const string& vName, bool isFloat);
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5REGDISPATCHER_H
