//
// Created by gaome on 2023/7/26.
//

#include "R5RegAllocator.h"
#include "R5RegDispatcher.h"
#include "R5Lai64.h"
#include "R5Logger.h"

#include <utility>
#include <iostream>
#include <algorithm>
#include "Phoenix.h"

namespace R5Emitter
{
/// 检查一个立即数在s/l指令中是否可以直接使用
/// \param p
/// \return
static inline bool couldLoadWithRegImm(int64_t p)
{
    return -2048 <= p && p <= 2047;
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
// dst和tmpReg不冲突，可以使用同一个寄存器
static inline void accessStackWithTmp(
    std::vector<R5AsmStrangeFake>& codeDest,
    FakeOPs                        op,
    YangReg                        dst,
    int64_t                        offset,
    YangReg                        baseReg,
    YangReg                        tmpReg
)
{
    if (couldLoadWithRegImm(offset)) {
        codeDest.emplace_back(R5AsmStrangeFake(op, {R(dst), P(offset), R(baseReg)}));
    } else {
        codeDest.emplace_back(R5AsmStrangeFake(LI, {R(tmpReg), P(offset)}));
        codeDest.emplace_back(R5AsmStrangeFake(ADD, {R(tmpReg),R(tmpReg), R(baseReg)}));
        codeDest.emplace_back(R5AsmStrangeFake(op, {R(dst), P(0), R(tmpReg)}));
    }
}
R5RegAllocator::R5RegAllocator(
    const std::vector<string>&                        bbNames_,
    const std::vector<std::vector<R5AsmStrangeFake>>& bbCodes_,
    R5TaichiMap&                                      taichiMap_,
    const fu&                                         fu_
)
    : taichiMap(taichiMap_)
    , _fu(fu_)
{
    bbNames = std::vector<string>(bbNames_.begin(), bbNames_.end());
    bbCodes = std::vector<std::vector<R5AsmStrangeFake>>(bbCodes_.begin(), bbCodes_.end());
    // 初始化分配结果
    allocatedCodes = std::vector<std::vector<R5AsmStrangeFake>>(bbCodes.size());

    // 开始分配
    doAllocate();
}
void R5RegAllocator::doAllocate()
{
    for (int i = 0; i < bbCodes.size(); i++) { doAllocate(i); }
}




void R5RegAllocator::doAllocate(int bbIndex)
{
    auto& bb   = bbCodes[bbIndex];
    auto& dest = allocatedCodes[bbIndex];
    // 构建每个寄存器的lifespan。（unordered_map)
    LifespanMap lifespan;

    // 预处理结束。

    // 打印替换结果。
    //    for (int i = 0; i < bb.size(); i++) {
    //        std::cout << i << ":\t" << bb[i].toString() << std::endl;
    //    }
    // 倒序扫描基本块，构建lifespan
    for (int j = (int)bb.size() - 1; j >= 0; --j) {
        auto inst = bb[j];
        auto def  = inst.getDefReg();
        auto use  = inst.getUsedRegs();
        // 构建lifespan
        // 一Call而万物死
        if (inst.fakeOP == CALL) {
            // 而如果a0,fa0被用到，那么涅槃重生。
            if (lifespan.find("a0") != lifespan.end()) {
                if (lifespan["a0"].isDead(j)) lifespan["a0"].birth(j);
            }
            if (lifespan.find("fa0") != lifespan.end()) {
                if (lifespan["fa0"].isDead(j)) lifespan["fa0"].birth(j);
            }
            // 死哪些？我们可以知道。
            auto dead = getUsedRegs(inst.operands[0]->toString());
            for (auto t : dead) {
                // 无论如何，都要死
                lifespan[R5Yang::toString(t)].death(j);
            }
        }
        // 应该先生而后死，所以先处理生存。
        // 想想mv a0,a0这种情况，
        // 生
        if (def) {
            string name;
            if (auto d = dynamic_pointer_cast<R5Yang>(def)) name = d->toString();
            if (auto d2 = dynamic_pointer_cast<R5Yin>(def)) name = d2->toString();
            if (!name.empty()) lifespan[name].birth(j);
        }
        // 死
        for (const auto& r1 : use) {
            string name;
            if (auto ur = dynamic_pointer_cast<R5Yang>(r1)) name = ur->toString();
            if (auto ur2 = dynamic_pointer_cast<R5Yin>(r1)) name = ur2->toString();
            if (!name.empty()) lifespan[name].death(j);
        }
    }
    // 在lifespan 中 去除zero, sp, ra, s0
    lifespan.erase("zero");
    lifespan.erase("sp");
    lifespan.erase("ra");
    lifespan.erase("s0");
    // 修正所有-1开始的lifespan，改为0开始。
    for (auto& [name, ls] : lifespan) {
        for (auto& [birth, death] : ls.ls) {
            if (birth == -1) birth = 0;
        }
    }
    // 修正所有-1结束的lifespan，改为bb.size()-1结束。
    for (auto& [name, ls] : lifespan) {
        for (auto& [birth, death] : ls.ls) {
            if (death == -1) death = (int)bb.size() - 1;
        }
    }
    // 合并相邻的生死段。(1,2)(2,3) -> (1,3) 但是(1,3)(4,5)不合并。（有可能有问题，感觉上）
    // 并且反转。
    for (auto& [name, ls] : lifespan) {
        auto& l = ls.ls;
        l.reverse();
        // 这么搞还不如直接弄个新list。
        auto newL = std::list<std::pair<int, int>>();
        for (auto it = l.begin(); it != l.end(); it++) {
            auto [birth, death] = *it;
            if (newL.empty()) {
                newL.emplace_back(birth, death);
                continue;
            }
            auto [birthLast, deathLast] = newL.back();
            if (birth == deathLast) {
                newL.pop_back();
                newL.emplace_back(birthLast, death);
            } else {
                newL.emplace_back(birth, death);
            }
        }
        ls.ls = newL;
    }
    // 打印结果。
    // for (auto& [name, ls] : lifespan) {
    //     std::cout << name << ": ";
    //     for (auto& [birth, death] : ls.ls) { std::cout << "(" << birth << "," << death << ") "; }
    //     std::cout << std::endl;
    // }

    // 构建结束。
    // 数据还算比较密集，可以使用一个数组来记录每一位置的指令对应的寄存器分配和释放情况。
    auto regInStream  = new shared_ptr<R5Taichi>[bb.size()];
    auto regOutStream = new shared_ptr<R5Taichi>[bb.size()][4];

    // 初始化
    for (int j = 0; j < bb.size(); j++) {
        int   k             = 0;
        auto& outStreamHere = regOutStream[j];
        for (auto& r : bb[j].getUsedRegs()) {
            auto name = r->toString();
            if (lifespan.find(name) != lifespan.end()) {
                if (lifespan[name].isNowDying(j)) { outStreamHere[k++] = r; }
            }
        }
        if (bb[j].getDefReg()) {
            auto name = bb[j].getDefReg()->toString();
            if (lifespan.find(name) != lifespan.end()) {
                if (lifespan[name].isNowBearing(j)) { regInStream[j] = bb[j].getDefReg(); }
            }
        }
    }

    /// 开始分配

    std::set<YangReg> needSaveRegs;      // = allocated - argUsed. 读取完成后必须清空。
    int               needSaveRegHashAllocate = 0;
    int               needSaveRegHashRelease  = 0;

    int callFutureInst = -1;   // call的善后处理。用完置-1

    // 分配器
    auto dispatcher = R5RegDispatcher(taichiMap, lifespan);
    for (int i = 0; i < bb.size(); i++) {

        auto& inst = bb[i];
        // call的spill的reload处理。
        if (i == callFutureInst) {
            callFutureInst = -1;
            for (auto r : needSaveRegs) {
                if (!R5Yang::isCallerSave(r)) continue;
                auto    rStr = R5Yang::toString(r) + "!" + std::to_string(needSaveRegHashRelease++);
                int64_t off     = taichiMap.query(rStr);   // 固定8.
                auto    isFloat = R5Yang::isFloatReg(r);
                accessStackWithTmp(
                    dest, isFloat ? FLW : LD, r, off, s0, dispatcher.getReservedIReg(0)
                );
                taichiMap.release(rStr);
            }
            needSaveRegs.clear();
        }
        // CALL的spill的save处理。
        if (inst.fakeOP == CALL) {
            // call需要特殊处理。这里需要计算出是否需要保存寄存器。如果需要保存，那么就要保存。
            auto              funcName         = inst.operands[0]->toString();
            std::set<YangReg> argsUsedRegs     = _fu.at(funcName);
            std::set<YangReg> nowAllocatedRegs = dispatcher.getNowUsedRegs();
            needSaveRegs.clear();
            // 补集
            std::set_difference(
                nowAllocatedRegs.begin(),
                nowAllocatedRegs.end(),
                argsUsedRegs.begin(),
                argsUsedRegs.end(),
                std::inserter(needSaveRegs, needSaveRegs.begin())
            );

            // woc call后边还有 一条类似addi sp,sp,16
            // 他妈的。如果直接用sp寻址，sp还变化了。就有一些问题。
            // 20230728 大改由s0寻址。保存直接用太极图就行、、、
            for (auto r : needSaveRegs) {
                if (!R5Yang::isCallerSave(r)) continue;
                auto rStr   = R5Yang::toString(r) + "!" + std::to_string(needSaveRegHashAllocate++);
                int64_t off     = taichiMap.allocate(rStr, 8);   // 固定8.
                auto    isFloat = R5Yang::isFloatReg(r);
                accessStackWithTmp(
                    dest, isFloat ? FSW : SD, r, off, s0, dispatcher.getReservedIReg(0)
                );
            }
            dest.push_back(inst);
            // 如果下一条指令是类似于mv %v1,a0或者fmv.s %v1,fa0此类。先将其放入dest中。
            auto instNext = bb[i + 1];
            callFutureInst = i + 1;
            if (instNext.fakeOP == MV || instNext.fakeOP == FMV_S) {
                auto reg = instNext.operands[1];
                if (auto r = dynamic_pointer_cast<R5Yang>(reg)) {
                    if (r->reg == fa0 || r->reg == a0) { callFutureInst = i + 2; }
                }
            }

            continue;
        }


        int spillLoadCount = 0; // 从内存中读取的次数。
        int spillSaveCount = 0; // 写入内存的次数。
        // 第一次替换。将即将流入历史长河的寄存器替换为实体寄存器。
        for (auto j = 0; j < inst.opNum; j++) {
            auto& r = inst.operands[j];   // <---------- 一会我们要替换的寄存器。
            // 仅仅替换USE, 所以DEF&UNUSED要跳过。
            if(inst.defUse[j]==R5AsmStrangeFake::DEF||inst.defUse[j]==R5AsmStrangeFake::UNUSED) continue;
            if (auto vr = dynamic_pointer_cast<R5Yin>(r)) {
                auto name = vr->toString();
                // 他很幸运。能够分配在寄存器中。
                if (auto allocatedReg = dispatcher.queryReg(name); allocatedReg != InvalidReg) {
                    r = make_shared<R5Yang>(allocatedReg);
                }
                // 不幸，被spill到内存中。太可惜了。
                if (int64_t offset = dispatcher.queryStackOffset(name); offset != -1) {
                    // 通过加载指令，将内存中的值加载到寄存器中。
                    spillLoadCount+=1;
                    auto reservedR1 = vr->isFloat() ? dispatcher.getReservedFReg(spillLoadCount)
                                                    : dispatcher.getReservedIReg(spillLoadCount);
                    auto tmpReg     = dispatcher.getReservedIReg(spillLoadCount);
                    if (vr->isFloat()) {
                        accessStackWithTmp(dest, FLW, reservedR1, offset, s0, tmpReg);
                    } else if (vr->isInt()) {
                        accessStackWithTmp(dest, LW, reservedR1, offset, s0, tmpReg);
                    } else {
                        accessStackWithTmp(dest, LD, reservedR1, offset, s0, tmpReg);
                    }
                    r = make_shared<R5Yang>(reservedR1);
                }
            }
        }
        auto in  = regInStream[i];
        auto out = regOutStream[i];
        // in是开始使用这个寄存器，out是他妈的释放。
        // out 要他妈的注意总共就4个，不要超过4个。
        // 注意，先释放，再分配。
        for (auto jj = 0; jj < 4; jj++) {
            auto outJ = out[jj];   // 需要释放的寄存器
            if (outJ == nullptr) continue;
            //            LOGD("Release " << outJ->toString() << " in " << i << "th inst");
            if (auto outYang = dynamic_pointer_cast<R5Yang>(outJ)) {
                dispatcher.releaseR(outYang->reg);
            } else if (auto outYin = dynamic_pointer_cast<R5Yin>(outJ)) {
                dispatcher.releaseV(outYin->toString());
            }
        }
        // 分配
        if (in != nullptr) {
            //            LOGD("Allocate " << in->toString() << " in " << i << "th inst");
            if (auto inYang = dynamic_pointer_cast<R5Yang>(in)) {
                // 这里分配了物理寄存器。
                dispatcher.allocateR(inYang->reg);
                // 物理寄存器不可能出现spill, 要不就是你脑子抽了。
                // 也不需要对应关系说是。
            } else if (auto inYin = dynamic_pointer_cast<R5Yin>(in)) {
                if (inYin->isFloat()) {
                    // 分配一个物理寄存器（浮点）
                    auto reg = dispatcher.allocateFV(inYin->toString());
                    // 只说一遍，栈上的不需要记录。
                    if (reg == InvalidReg) {
                        auto offset = dispatcher.queryStackOffset(inYin->toString());
                        IR_ASSERT(offset != -1, "offset should not be -1");
                    }
                    // 再说一遍，已经分配的也不需要记录。
                } else {
                    auto reg = dispatcher.allocateIV(inYin->toString());
                    if (reg == InvalidReg) {
                        auto offset = dispatcher.queryStackOffset(inYin->toString());
                        IR_ASSERT(offset != -1, "offset should not be -1");
                    }
                }
            }
        }
        // 第二次替换
        std::vector<R5AsmStrangeFake> spillWriteBackFutureInst;
        for (auto j = 0; j < inst.opNum; j++) {
            auto& r = inst.operands[j];   // <---------- 一会我们要替换的寄存器。
            // 仅替换def.所以use&unused要跳过。
            if(inst.defUse[j]==R5AsmStrangeFake::USE||inst.defUse[j]==R5AsmStrangeFake::UNUSED) continue;
            if (auto vr = dynamic_pointer_cast<R5Yin>(r)) {
                auto name = vr->toString();
                // 他很幸运。能够分配在寄存器中。
                if (auto allocatedReg = dispatcher.queryReg(name); allocatedReg != InvalidReg) {
                    r = make_shared<R5Yang>(allocatedReg);
                }
                // 我们需要知道他出现在use还是def中。def需要store，use需要load。
                // 不幸，被spill到内存中。太可惜了。
                if (int64_t offset = dispatcher.queryStackOffset(name); offset != -1) {
                    // 通过加载指令，将内存中的值加载到寄存器中。
                    spillSaveCount+=1;
                    auto reservedR2 = vr->isFloat() ? dispatcher.getReservedFReg(spillSaveCount)
                                                    : dispatcher.getReservedIReg(spillSaveCount);
                    auto tmpReg     = dispatcher.getReservedIReg(spillSaveCount);
                    if (vr->isFloat()) {
                        accessStackWithTmp(spillWriteBackFutureInst, FSW, reservedR2, offset, s0, tmpReg);
                    } else if (vr->isInt()) {
                        accessStackWithTmp(spillWriteBackFutureInst, SW, reservedR2, offset, s0, tmpReg);
                    } else {
                        accessStackWithTmp(spillWriteBackFutureInst, SD, reservedR2, offset, s0, tmpReg);
                    }
                    r = make_shared<R5Yang>(reservedR2);
                }
            }
        }
        // 将结果写入dest数组。

        dest.push_back(inst);
        for (auto& t : spillWriteBackFutureInst) { dest.push_back(t); }
    }


    // ∪
    auto t = dispatcher.getTotalUsedRegs();
    totalUsedRegs.merge(t);
    delete[] regInStream;
    delete[] regOutStream;
}
std::set<YangReg> R5RegAllocator::getUsedRegs(string funcName)
{
    // if not starts with "@" , then add "@"
    if (funcName[0] != '@') { funcName = "@" + funcName; }
    if (funcName == "@memset") return {a0, a1, a2};
    return _fu.at(funcName);
}
const std::vector<std::vector<R5AsmStrangeFake>>& R5RegAllocator::getAllocatedCodes()
{
    return allocatedCodes;
}
const std::set<YangReg>& R5RegAllocator::getTotalUsedRegs() const
{
    return totalUsedRegs;
}

}   // namespace R5Emitter