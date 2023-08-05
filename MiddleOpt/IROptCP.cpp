//
// Created by gaome on 2023/8/3.
//

#include "IROptCP.h"
#include "IROptCF.h"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <queue>
#include <variant>
#include <set>
#include "IROptCF.h"
using std::list;
using std::map;
using std::pair;
using std::queue;
using std::unordered_map;
using std::variant;

template<class T>
using SP = shared_ptr<T>;
namespace MiddleIR::Optimizer
{
IROptCP::IROptCP(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptCP::run()
{
    hasChanged = false;
    for (const auto& f : _irast->funcDefs) { For1Func(f); }
}

using FakeConst     = variant<UNDEF, NAC, SP<R5IRValConst>>;
const int UNDEF_IDX = 0, NAC_IDX = 1, C_IDX = 2;

inline static bool ValConstEQ(const SP<R5IRValConst>& lhs, const SP<R5IRValConst>& rhs)
{
    // check type
    if (lhs->getType()->type != rhs->getType()->type) return false;
    // check value
    if (lhs->getType()->type == MiddleIRType::INT) {
        auto l = std::dynamic_pointer_cast<R5IRValConstInt>(lhs);
        auto r = std::dynamic_pointer_cast<R5IRValConstInt>(rhs);
        return l->getWord() == r->getWord();
    } else if (lhs->getType()->type == MiddleIRType::FLOAT) {
        auto l = DPC(R5IRValConstFloat, lhs);
        auto r = DPC(R5IRValConstFloat, rhs);
        return l->getWord() == r->getWord();
    } else
        return false;
}

/// v2 merge into v1
/// \param v1
/// \param v2
/// \return 是否发生了变化
bool merge(
    unordered_map<SP<AllocaInst>, FakeConst>& v1, const unordered_map<SP<AllocaInst>, FakeConst>& v2
)
{
    // 结果放在v1里
    // 1 NAC @ UNDEF = NAC
    // 2 NAC @ NAC = NAC
    // 3 NAC @ C = NAC
    // 4 UNDEF @ UNDEF = UNDEF
    // 5 UNDEF @ C = C
    // 5.5 UNDEF @ NAC = NAC
    // 6 C @ C = C
    // 7 C1 @ C2 = NAC (C1 != C2)
    // 8 C @ UNDEF = C
    // 9 C @ NAC = NAC
    bool changed = false;
    for (const auto& [k, rhs] : v2) {
        if (v1.find(k) == v1.end()) {
            v1[k]   = rhs;   // Rule 0
            changed = true;
        } else {
            auto& lhs = v1[k];
            if (lhs.index() == UNDEF_IDX) {
                changed |= (rhs.index() != UNDEF_IDX);
                lhs = rhs;   // Rule 4, 5
            } else if (lhs.index() == C_IDX && rhs.index() == C_IDX) {
                // Rule 6, 7
                if (!ValConstEQ(std::get<C_IDX>(lhs), std::get<C_IDX>(rhs))) {
                    lhs     = NAC();   // Rule 7
                    changed = true;
                }
                // do nothing for Rule 6
            } else if (lhs.index() == C_IDX && rhs.index() == UNDEF_IDX) {
                // Rule 8 do nothing
            } else {
                changed |= (lhs.index() != NAC_IDX);
                lhs = NAC();   // Rule 1, 2, 3
            }
        }
    }
    return changed;
}

// 不同按newOne为准
FakeConst MergeOne(FakeConst oldOne, FakeConst newOne)
{
    if (oldOne.index() == UNDEF_IDX) {
        return newOne;
    } else if (oldOne.index() == C_IDX && newOne.index() == C_IDX) {
        if (ValConstEQ(std::get<C_IDX>(oldOne), std::get<C_IDX>(newOne))) {
            return oldOne;
        } else {
            return newOne;
        }
    } else {
        return NAC();
    }
}

void IROptCP::For1Func(const shared_ptr<MiddleIRFuncDef>& func)
{
    // 基本块多于30，不优化
    if (func->getBasicBlocks().size() > 30) return;
    // 常量传播是半格。只对alloca的单变量进行考虑，不考虑数组。
    // 1. 初始化: 找出所有的单变量alloca，将其初始化为undef
    std::set<SP<AllocaInst>> setAlloca;
    for (const auto& b : func->getBasicBlocks()) {
        // Only in LEntry can you find alloca.
        if (b->getName() == "LEntry") {
            for (const auto& i : b->_instructions) {
                if (auto allocaInst = DPC(AllocaInst, i)) { setAlloca.insert(allocaInst); }
            }
            break;
        }
    }
    unordered_map<SP<MiddleIRBasicBlock>, unordered_map<SP<AllocaInst>, FakeConst>>
        mapEachBBValStatus;
    for (const auto& b : func->getBasicBlocks()) {
        unordered_map<SP<AllocaInst>, FakeConst> mapAllocaToVal;
        for (auto& a : setAlloca) { mapAllocaToVal[a] = UNDEF(); }
        mapEachBBValStatus[b] = mapAllocaToVal;
    }
    // 2. from LEntry BFS.
    bool                             changed;
    std::set<SP<MiddleIRBasicBlock>> visited;
    auto                             lEntryBB = func->getBasicBlock("LEntry");
    do {
        changed = false;
        queue<SP<MiddleIRBasicBlock>> q;
        for (auto& b : func->getBasicBlocks()) q.push(b);
        while (!q.empty()) {
            auto bb = q.front();
            q.pop();
            if (bb->getName() == "L4" && func->getName() == "@main") { int a = 1; }
            visited.insert(bb);
            auto& mapAllocaToVal = mapEachBBValStatus[bb];
            // 计算当前基本块的值状态。
            auto t = mapAllocaToVal;
            ExecuteCurBB(mapAllocaToVal, bb);
            LOGW("After Calc:" << bb->getName());
            printIt(mapEachBBValStatus);

            // 遍历后继。
            for (auto& s : bb->getNext()) {
                bool jb = false;
                jb |= merge(mapEachBBValStatus[s], mapAllocaToVal);
                LOGW("Merged " << s->getName() << " from " << bb->getName() << " changed=" << jb);
                changed |= jb;
                if (jb) { q.push(s); }
                //                if (visited.find(s) != visited.end()) { continue; }
                //                printIt(mapEachBBValStatus);
                //                q.push(s);
            }
        }
        //        printIt(mapEachBBValStatus);
    } while (changed);
    //    printIt(mapEachBBValStatus);
    // 3. 构建predecessor表
    unordered_map<SP<MiddleIRBasicBlock>, std::set<SP<MiddleIRBasicBlock>>> mapPredecessor;
    for (const auto& b : func->getBasicBlocks()) {
        for (const auto& s : b->getNext()) { mapPredecessor[s].insert(b); }
    }
    // 4.
    // 一些值在一个基本块中是不变的，他们可以直接替换，当且仅当这个基本块的所有前驱都是这个值，即：
    // 合并之后，这个值在这个基本块中是不变的。（非UNDEF和NAC）
    for (const auto& b : func->getBasicBlocks()) {
        unordered_map<SP<AllocaInst>, FakeConst> mapReplaceReady;
        for (const auto& a : setAlloca) { mapReplaceReady[a] = UNDEF(); }
        for (const auto& p : mapPredecessor[b]) { merge(mapReplaceReady, mapEachBBValStatus[p]); }
        merge(mapReplaceReady, mapEachBBValStatus[b]);
        // 可以提取出不是UNDEF和NAC的值。
        unordered_map<SP<AllocaInst>, SP<R5IRValConst>> mapAllocaToValConst;
        for (const auto& [a, v] : mapReplaceReady) {
            if (v.index() == C_IDX) { mapAllocaToValConst[a] = std::get<C_IDX>(v); }
        }
        unordered_map<SP<LoadInst>, SP<R5IRValConst>> mapLoadToValConst;
        for (const auto& i : b->_instructions) {
            if (auto loadInst = DPC(LoadInst, i)) {
                if (auto allocaFrom = DPC(AllocaInst, loadInst->getFrom())) {
                    if (mapAllocaToValConst.find(allocaFrom) != mapAllocaToValConst.end()) {
                        mapLoadToValConst[loadInst] = mapAllocaToValConst[allocaFrom];
                    }
                }
            }
        }
        // 替换。

        for (auto& i : b->_instructions) {
            for (auto u : i->getUseList()) {
                if (auto loadInst = DPC(LoadInst, *u)) {
                    if (mapLoadToValConst.find(loadInst) != mapLoadToValConst.end()) {
                        i->tryReplaceUse(loadInst, mapLoadToValConst[loadInst]);
                        hasChanged = true;
                    }
                }
            }
        }
        auto i = b->getTerminator();
        for (auto u : i->getUseList()) {
            if (auto loadInst = DPC(LoadInst, *u)) {
                if (mapLoadToValConst.find(loadInst) != mapLoadToValConst.end()) {
                    i->tryReplaceUse(loadInst, mapLoadToValConst[loadInst]);
                    hasChanged = true;
                }
            }
        }
        hasChanged |= IROptCF::ConstFold(b);
    }
    LOGW("CP Done.");
}
void IROptCP::printIt(
    unordered_map<SP<MiddleIRBasicBlock>, std::unordered_map<SP<AllocaInst>, FakeConst>>&
        mapEachBBValStatus
)
{
    for (auto [bb, mapAllocaToVal] : mapEachBBValStatus) {
        std::cout << bb->getName() << ": ";
        for (auto [allocaInst, val] : mapAllocaToVal) {
            std::cout << allocaInst->getName() << " ";
            if (val.index() == NAC_IDX) {
                std::cout << "NAC, ";
            } else if (val.index() == UNDEF_IDX) {
                std::cout << "UNDEF, ";
            } else {
                auto c = std::get<C_IDX>(val);
                if (c->getType()->type == MiddleIRType::INT) {
                    std::cout << std::dynamic_pointer_cast<R5IRValConstInt>(c)->getValue() << ", ";
                } else if (c->getType()->type == MiddleIRType::FLOAT) {
                    std::cout << std::dynamic_pointer_cast<R5IRValConstFloat>(c)->getValue()
                              << ", ";
                } else {
                    std::cout << "???, ";
                }
            }
        }
        std::cout << std::endl;
    }
}

///
/// \param v1
/// \param v2
/// \return 值，是否需要计算
inline std::tuple<FakeConst, bool> Ohayouguzaimasu(FakeConst& v1, FakeConst& v2)
{
    if (v1.index() == NAC_IDX) { return {NAC(), false}; }
    if (v2.index() == NAC_IDX) { return {NAC(), false}; }
    if (v1.index() == UNDEF_IDX) { return {UNDEF(), false}; }
    if (v2.index() == UNDEF_IDX) { return {UNDEF(), false}; }
    // now all C.
    return {v1, true};
}
static void
EmulateCalc(shared_ptr<MiddleIRInst>& i, unordered_map<SP<MiddleIRVal>, FakeConst>& valConstMap)
{
    if (auto iMath = DPC(IMathInst, i)) {
        auto v1       = iMath->getOpVal1();
        auto v2       = iMath->getOpVal2();
        auto v1FConst = valConstMap[v1];
        auto v2FConst = valConstMap[v2];
        if (v1->isConst()) v1FConst = DPC(R5IRValConst, v1);
        if (v2->isConst()) v2FConst = DPC(R5IRValConst, v2);
        auto [aNew, v1NeedCalc] = Ohayouguzaimasu(v1FConst, v2FConst);
        if (!v1NeedCalc) {
            valConstMap[iMath] = aNew;
            return;
        } else {
            auto v1c = DPC(R5IRValConstInt, std::get<C_IDX>(v1FConst))->getValue();
            auto v2c = DPC(R5IRValConstInt, std::get<C_IDX>(v2FConst))->getValue();
            int  res;
            switch (iMath->iMathOp) {
            case IMathInst::IMathOp::ADD: res = v1c + v2c; break;
            case IMathInst::IMathOp::SUB: res = v1c - v2c; break;
            case IMathInst::IMathOp::MUL: res = v1c * v2c; break;
            case IMathInst::IMathOp::UDIV:
            case IMathInst::IMathOp::SDIV: res = v1c / v2c; break;
            case IMathInst::IMathOp::UREM:
            case IMathInst::IMathOp::SREM: res = v1c % v2c; break;
            }
            valConstMap[iMath] = IR_INT_CONST(res);
        }
    }
    //
    else if (auto fMath = DPC(FMathInst, i)) {
        auto v1       = fMath->getOpVal1();
        auto v2       = fMath->getOpVal2();
        auto v1FConst = valConstMap[v1];
        auto v2FConst = valConstMap[v2];
        if (v1->isConst()) v1FConst = DPC(R5IRValConst, v1);
        if (v2->isConst()) v2FConst = DPC(R5IRValConst, v2);
        auto [constNew, needCalc] = Ohayouguzaimasu(v1FConst, v2FConst);
        if (!needCalc) {
            valConstMap[fMath] = constNew;
            return;
        } else {
            auto  v1c = DPC(R5IRValConstFloat, std::get<C_IDX>(v1FConst))->getValue();
            auto  v2c = DPC(R5IRValConstFloat, std::get<C_IDX>(v2FConst))->getValue();
            float res;
            switch (fMath->fMathOp) {
            case FMathInst::FMathOp::FADD: res = v1c + v2c; break;
            case FMathInst::FMathOp::FSUB: res = v1c - v2c; break;
            case FMathInst::FMathOp::FMUL: res = v1c * v2c; break;
            case FMathInst::FMathOp::FDIV: res = v1c / v2c; break;
            case FMathInst::FREM: res = 0; break;
            }
            valConstMap[fMath] = IR_FLOAT_CONST(res);
        }
    }
    //
    else if (auto icmp = DPC(ICmpInst, i)) {
        auto v1       = icmp->getOpVal1();
        auto v2       = icmp->getOpVal2();
        auto v1FConst = valConstMap[v1];
        auto v2FConst = valConstMap[v2];
        if (v1->isConst()) v1FConst = DPC(R5IRValConst, v1);
        if (v2->isConst()) v2FConst = DPC(R5IRValConst, v2);
        auto [v1ConstNew, v1NeedCalc] = Ohayouguzaimasu(v1FConst, v2FConst);
        if (!v1NeedCalc) {
            valConstMap[icmp] = v1ConstNew;
            return;
        } else {
            auto v1c = DPC(R5IRValConstInt, std::get<C_IDX>(v1FConst))->getValue();
            auto v2c = DPC(R5IRValConstInt, std::get<C_IDX>(v2FConst))->getValue();
            bool res;
            switch (icmp->iCmpOp) {
            case ICmpInst::EQ: res = v1c == v2c; break;
            case ICmpInst::NE: res = v1c != v2c; break;
            case ICmpInst::UGT:
            case ICmpInst::SGT: res = v1c > v2c; break;
            case ICmpInst::UGE:
            case ICmpInst::SGE: res = v1c >= v2c; break;
            case ICmpInst::ULT:
            case ICmpInst::SLT: res = v1c < v2c; break;
            case ICmpInst::ULE:
            case ICmpInst::SLE: res = v1c <= v2c; break;
            }
            valConstMap[icmp] = IR_BOOL_CONST(res);
        }
    }
    //
    else if (auto fcmp = DPC(FCmpInst, i)) {
        auto v1       = fcmp->getOpVal1();
        auto v2       = fcmp->getOpVal2();
        auto v1FConst = valConstMap[v1];
        auto v2FConst = valConstMap[v2];
        if (v1->isConst()) v1FConst = DPC(R5IRValConst, v1);
        if (v2->isConst()) v2FConst = DPC(R5IRValConst, v2);
        auto [v1ConstNew, v1NeedCalc] = Ohayouguzaimasu(v1FConst, v2FConst);
        if (!v1NeedCalc) {
            valConstMap[fcmp] = v1ConstNew;
            return;
        } else {
            auto v1c = DPC(R5IRValConstFloat, std::get<C_IDX>(v1FConst))->getValue();
            auto v2c = DPC(R5IRValConstFloat, std::get<C_IDX>(v2FConst))->getValue();
            bool res;
            switch (fcmp->fCmpOp) {
            case FCmpInst::FCmpOp::OEQ: res = v1c == v2c; break;
            case FCmpInst::FCmpOp::OGT: res = v1c > v2c; break;
            case FCmpInst::FCmpOp::OGE: res = v1c >= v2c; break;
            case FCmpInst::FCmpOp::OLT: res = v1c < v2c; break;
            case FCmpInst::FCmpOp::OLE: res = v1c <= v2c; break;
            case FCmpInst::FCmpOp::UEQ: res = v1c == v2c; break;
            case FCmpInst::FCmpOp::UNE: res = v1c != v2c; break;
            case FCmpInst::FCmpOp::UGT: res = v1c > v2c; break;
            case FCmpInst::FCmpOp::UGE: res = v1c >= v2c; break;
            case FCmpInst::FCmpOp::ULT: res = v1c < v2c; break;
            case FCmpInst::FCmpOp::ULE: res = v1c <= v2c; break;
            case FCmpInst::FCmpOp::FALSE: res = false; break;
            case FCmpInst::FCmpOp::TRUE: res = true; break;
            case FCmpInst::FCmpOp::UNO: res = false; break;
            }
            valConstMap[fcmp] = IR_BOOL_CONST(res);
        }
    }
    //
    else if (auto cv = DPC(ConvertInst, i)) {
        auto v1       = cv->getFrom();
        auto v1FConst = valConstMap[v1];
        if (v1->isConst()) v1FConst = DPC(R5IRValConst, v1);
        if (v1FConst.index() == C_IDX) {
            auto v1ci = DPC(R5IRValConstInt, std::get<C_IDX>(v1FConst));
            auto v1cf = DPC(R5IRValConstFloat, std::get<C_IDX>(v1FConst));
            auto v1cb = DPC(R5IRValConstI1, std::get<C_IDX>(v1FConst));
            if (v1ci == nullptr && v1cf == nullptr) v1ci = IR_INT_CONST((int)v1cb->getValue());
            switch (cv->getConvertOp()) {
            case ConvertInst::ConvertOp::ZEXT:
            case ConvertInst::ConvertOp::SEXT:
                valConstMap[cv] = IR_INT_CONST(v1ci->getValue());
                break;
            case ConvertInst::ConvertOp::FPTOUI:
            case ConvertInst::ConvertOp::FPTOSI:
                valConstMap[cv] = IR_INT_CONST(v1cf->getValue());
                break;
            case ConvertInst::ConvertOp::UITOFP:
            case ConvertInst::ConvertOp::SITOFP:
                valConstMap[cv] = IR_FLOAT_CONST((float)v1ci->getValue());
                break;
            case ConvertInst::TRUNC: break;
            }
        }
    }
    //
    else {
        valConstMap[i] = NAC();
    }
}
void IROptCP::ExecuteCurBB(
    unordered_map<SP<AllocaInst>, FakeConst>& map, const shared_ptr<MiddleIRBasicBlock>& bb
)
{
    unordered_map<SP<MiddleIRVal>, FakeConst> valConstMap;
    std::unordered_set<SP<AllocaInst>>        allocaVis;
    for (auto& i : bb->_instructions) {
        if (i->isLoadInst()) {
            auto loadInst   = DPC(LoadInst, i);
            auto allocaInst = DPC(AllocaInst, loadInst->getFrom());
            if (allocaInst == nullptr) continue;
            valConstMap[loadInst] = map[allocaInst];
        } else if (i->isStoreInst()) {
            auto store    = DPC(StoreInst, i);
            auto from     = store->getFrom();
            auto to       = store->getTo();
            auto toAlloca = DPC(AllocaInst, to);
            if (toAlloca == nullptr) continue;
            if (auto constFrom = DPC(R5IRValConst, from)) {
                // 如果toAlloca来自上一级，则不同要给NAC，否则不同按后来者为准。
                //                if (allocaVis.find(toAlloca) == allocaVis.end()) {
                //                    // 还未访问过
                //                    allocaVis.insert(toAlloca);
                //                    // 如果这个constFrom和之前的不同，则给NAC
                //                    // 1. before is NAC then give NAC;
                //                    // 2. before is UNDEF, then give the constFrom;
                //                    // 3. before is Const, then compare the value. if different,
                //                    give NAC; else give
                //                    //    constFrom;
                //                    if (map[toAlloca].index() == C_IDX &&
                //                        !ValConstEQ(std::get<C_IDX>(map[toAlloca]), constFrom)) {
                //                        map[toAlloca] = NAC();
                //                    } else {
                //                        map[toAlloca] = MergeOne(map[toAlloca], constFrom);
                //                    }
                //                } else {
                map[toAlloca] = MergeOne(map[toAlloca], constFrom);
                //                }
            } else {
                if (auto it = valConstMap.find(from); it != valConstMap.end()) {
                    // 同上
                    //                    if (allocaVis.find(toAlloca) == allocaVis.end()) {
                    //                        allocaVis.insert(toAlloca);
                    //                        if (map[toAlloca].index() == C_IDX &&
                    //                        it->second.index() == C_IDX &&
                    //                            !ValConstEQ(
                    //                                std::get<C_IDX>(map[toAlloca]),
                    //                                std::get<C_IDX>(it->second)
                    //                            )) {
                    //                            map[toAlloca] = NAC();
                    //                        } else {
                    //                            map[toAlloca] = MergeOne(map[toAlloca],
                    //                            it->second);
                    //                        }
                    //                    } else {
                    map[toAlloca] = MergeOne(map[toAlloca], it->second);
                    //                    }
                }
            }
        } else {
            EmulateCalc(i, valConstMap);
        }
    }
}



}   // namespace MiddleIR::Optimizer
