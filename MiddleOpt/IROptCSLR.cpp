//
// Created by gaome on 2023/8/3.
//

#include "IROptCSLR.h"
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <queue>
using std::list;
using std::map;
using std::pair;
using std::unordered_map;

namespace MiddleIR::Optimizer
{
IROptCSLR::IROptCSLR(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptCSLR::run()
{
    for (const auto& f : _irast->funcDefs) { OptForOneFunction(f); }
}
template<class T>
using SP = shared_ptr<T>;
void IROptCSLR::OptForOneFunction(const shared_ptr<MiddleIRFuncDef>& func)
{
    bool optForThis = false;
    for (auto& b : func->getBasicBlocks()) {
        if (b->_instructions.size() > 1000) {
            optForThis = true;
            break;
        }
    }
    if (!optForThis) { return; }
    // 仅供外部的基本块使用。所以最后一个SC要覆盖前一个。
    map<SP<MiddleIRBasicBlock>, map<SP<MiddleIRVal>, SP<R5IRValConst>>> mapBBToMapConstToVar;
    map<SP<MiddleIRBasicBlock>, std::set<SP<AllocaInst>>>               commonStore;
    // CS
    for (auto& b : func->getBasicBlocks()) {
        map<SP<MiddleIRVal>, SP<R5IRValConst>> mapConstToVar;
        std::set<SP<AllocaInst>>               setCommonStore;
        for (auto& i : b->_instructions) {
            if (auto storeInst = dynamic_pointer_cast<StoreInst>(i)) {
                auto from = storeInst->getFrom();
                auto to   = storeInst->getTo();
                if (auto toAlloca = DPC(AllocaInst, to)) {
                    if (auto constVal = dynamic_pointer_cast<R5IRValConst>(from)) {
                        mapConstToVar[to] = constVal;
                        setCommonStore.erase(toAlloca);
                    } else {
                        mapConstToVar.erase(to);
                        setCommonStore.insert(toAlloca);
                    }
                }
            }
        }
        if (!mapConstToVar.empty()) { mapBBToMapConstToVar[b] = mapConstToVar; }
        if (!setCommonStore.empty()) { commonStore[b] = setCommonStore; }
    }
    if (mapBBToMapConstToVar.empty()) { return; }
    // Nugprte, Reepvtich.

    for (auto& b : func->getBasicBlocks()) {
        // 找出所有的only-load.
        std::set<SP<AllocaInst>> setOnlyLoad;
        std::set<SP<AllocaInst>> setDisabledLoad;
        for (const auto& i : b->_instructions) {
            if (auto loadInst = dynamic_pointer_cast<LoadInst>(i)) {
                auto from = loadInst->getFrom();
                if (auto allocaInst = DPC(AllocaInst, from)) {
                    if (setDisabledLoad.find(allocaInst) == setDisabledLoad.end()) {
                        setOnlyLoad.insert(allocaInst);
                    }
                }
            } else if (auto storeInst = dynamic_pointer_cast<StoreInst>(i)) {
                auto to = storeInst->getTo();
                if (auto toAlloca = DPC(AllocaInst, to)) {
                    setDisabledLoad.insert(toAlloca);
                    setOnlyLoad.erase(toAlloca);
                }
            }
        }

        std::map<SP<AllocaInst>, SP<R5IRValConst>> mapAllocaToConst;
        std::queue<pair<SP<MiddleIRBasicBlock>,int>>         q;
        std::set<SP<MiddleIRBasicBlock>>           setVisited;
        // 1st pass: add all CS
        for (const auto& p : b->getPrev()) { q.emplace(p,0); }
        while (!q.empty()) {
            auto [bb,d] = q.front();
            q.pop();
            if (setVisited.find(bb) != setVisited.end()) { continue; }
            setVisited.insert(bb);
            if (auto it1 = mapBBToMapConstToVar.find(bb); it1 != mapBBToMapConstToVar.end()) {
                for (auto& [alloca, constVal] : it1->second) {
                    if (auto allocaInst = DPC(AllocaInst, alloca);
                        allocaInst != nullptr &&
                        setOnlyLoad.find(allocaInst) != setOnlyLoad.end()) {
                        mapAllocaToConst[allocaInst] = constVal;
                        setOnlyLoad.erase(allocaInst);
                    }
                }
            }
            for (const auto& p : bb->getPrev()) { q.emplace(p,d+1); }
        }
        // 2nd pass: erase common store
        std::queue<SP<MiddleIRBasicBlock>>         q2;
        for (const auto& p : b->getPrev()) { q2.push(p); }
        setVisited.clear();
        while (!q2.empty()) {
            auto bb = q2.front();
            q2.pop();
            if (setVisited.find(bb) != setVisited.end()) { continue; }
            setVisited.insert(bb);
            if (auto it1 = commonStore.find(bb); it1 != commonStore.end()) {
                for (auto& alloca : it1->second) { mapAllocaToConst.erase(alloca); }
            }
            for (const auto& p : bb->getPrev()) { q2.push(p); }
        }
        // 3rd pass: build the replacement table.(loadInst -> const)
        std::unordered_map<SP<LoadInst>, SP<R5IRValConst>> mapLoad2Const;
        for (const auto& i : b->_instructions) {
            if (auto inst = DPC(LoadInst, i)) {
                if (auto allocaInst = DPC(AllocaInst, inst->getFrom())) {
                    if (auto it1 = mapAllocaToConst.find(allocaInst);
                        it1 != mapAllocaToConst.end()) {
                        auto constVal       = it1->second;
                        mapLoad2Const[inst] = constVal;
                    }
                }
            }
        }
        // 4th pass: replace
        for (const auto& i : b->_instructions) {
            if (auto inst = DPC(LoadInst, i)) {
                if (mapLoad2Const.find(inst) != mapLoad2Const.end()) { inst->setDeleted(); }
            } else {
                for (auto& u : i->getUseList()) {
                    if (auto loadInst = DPC(LoadInst, *u)) {
                        if (auto it1 = mapLoad2Const.find(loadInst); it1 != mapLoad2Const.end()) {
                            i->tryReplaceUse(loadInst, it1->second);
                            break;   // 一条指令替换一次就够了。
                        }
                    }
                }
            }
        }
        for (auto it1 = b->_instructions.begin(); it1 != b->_instructions.end();) {
            if ((*it1)->isDeleted()) {
                it1 = b->_instructions.erase(it1);
            } else {
                ++it1;
            }
        }
        // 5th pass: const fold
        std::map<SP<MiddleIRVal>, SP<MiddleIRVal>> mapConstReplace;
        do {
            mapConstReplace.clear();
            for (const auto& i : b->_instructions) {
                if (auto binOpInst = DPC(IMathInst, i)) {
                    auto lhs      = binOpInst->getOpVal1();
                    auto rhs      = binOpInst->getOpVal2();
                    auto lhsConst = DPC(R5IRValConstInt, lhs);
                    auto rhsConst = DPC(R5IRValConstInt, rhs);
                    if (lhsConst == nullptr || rhsConst == nullptr) { continue; }
                    auto lhsVal = lhsConst->getValue();
                    auto rhsVal = rhsConst->getValue();
                    int  resVal;
                    switch (binOpInst->iMathOp) {
                    case IMathInst::IMathOp::ADD: resVal = lhsVal + rhsVal; break;
                    case IMathInst::IMathOp::SUB: resVal = lhsVal - rhsVal; break;
                    case IMathInst::IMathOp::MUL: resVal = lhsVal * rhsVal; break;
                    case IMathInst::IMathOp::SDIV:
                    case IMathInst::IMathOp::UDIV: resVal = lhsVal / rhsVal; break;
                    case IMathInst::IMathOp::SREM:
                    case IMathInst::IMathOp::UREM: resVal = lhsVal % rhsVal; break;
                    }
                    auto resConst              = make_shared<R5IRValConstInt>(resVal);
                    mapConstReplace[binOpInst] = resConst;
                    i->setDeleted();
                } else if (auto fMathInst = DPC(FMathInst, i)) {
                    auto lhs      = fMathInst->getOpVal1();
                    auto rhs      = fMathInst->getOpVal2();
                    auto lhsConst = DPC(R5IRValConstFloat, lhs);
                    auto rhsConst = DPC(R5IRValConstFloat, rhs);
                    if (lhsConst == nullptr || rhsConst == nullptr) { continue; }
                    auto  lhsVal = lhsConst->getValue();
                    auto  rhsVal = rhsConst->getValue();
                    float resVal;
                    switch (fMathInst->fMathOp) {
                    case FMathInst::FMathOp::FADD: resVal = lhsVal + rhsVal; break;
                    case FMathInst::FMathOp::FSUB: resVal = lhsVal - rhsVal; break;
                    case FMathInst::FMathOp::FMUL: resVal = lhsVal * rhsVal; break;
                    case FMathInst::FMathOp::FDIV: resVal = lhsVal / rhsVal; break;
                    case FMathInst::FMathOp::FREM: resVal = 0; break;
                    }
                    auto resConst              = make_shared<R5IRValConstFloat>(resVal);
                    mapConstReplace[fMathInst] = resConst;
                    i->setDeleted();
                }
            }
            for (const auto& i : b->_instructions) {
                for (auto& u : i->getUseList()) {
                    if (mapConstReplace.find(*u) != mapConstReplace.end()) {
                        i->tryReplaceUse(*u, mapConstReplace[*u]);
                        break;
                    }
                }
            }
        } while (!mapConstReplace.empty());
        // 6th pass: truly delete deleted inst
        for (auto it1 = b->_instructions.begin(); it1 != b->_instructions.end();) {
            if ((*it1)->isDeleted()) {
                it1 = b->_instructions.erase(it1);
            } else {
                ++it1;
            }
        }
    }
}
}   // namespace MiddleIR::Optimizer
