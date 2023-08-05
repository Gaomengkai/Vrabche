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
    for (const auto& f : _irast->funcDefs) { For1Func(f); }
}

class UNDEF
{
};
class NAC
{
};

using FakeConst = variant<UNDEF, NAC, SP<R5IRValConst>>;

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
    // 6 C @ C = C
    // 7 C1 @ C2 = NAC (C1 != C2)
    bool      changed   = false;
    const int UNDEF_IDX = 0, NAC_IDX = 1, C_IDX = 2;
    for (const auto& [k, v] : v2) {
        if (v1.find(k) == v1.end()) {
            v1[k]   = v;   // Rule 0
            changed = true;
        } else {
            if (v1[k].index() == UNDEF_IDX) {
                changed = v.index() != UNDEF_IDX;
                v1[k]   = v;   // Rule 4, 5
            } else if (v1[k].index() == C_IDX && v.index() == C_IDX) {
                // Rule 6, 7
                if (!ValConstEQ(std::get<C_IDX>(v1[k]), std::get<C_IDX>(v))) {
                    v1[k]   = NAC();   // Rule 7
                    changed = true;
                }
            } else {
                v1[k]   = NAC();   // Rule 1, 2, 3
                changed = v.index() != NAC_IDX;
            }
        }
    }
    return changed;
}

void IROptCP::For1Func(const shared_ptr<MiddleIRFuncDef>& func)
{
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
    bool                             changed = false;
    std::set<SP<MiddleIRBasicBlock>> visited;
    auto                             lEntryBB = func->getBasicBlock("LEntry");
    do {
        changed = false;
        queue<SP<MiddleIRBasicBlock>> q;
        q.push(lEntryBB);
        while (!q.empty()) {
            auto bb = q.front();
            q.pop();
            visited.insert(bb);
            auto& mapAllocaToVal = mapEachBBValStatus[bb];
            // 遍历store即可。
            for (auto& i : bb->_instructions) {
                if (auto storeInst = DPC(StoreInst, i)) {
                    auto allocaTo = DPC(AllocaInst, storeInst->getTo());
                    if (allocaTo == nullptr) continue;
                    auto val = storeInst->getFrom();
                    if (auto constVal = DPC(R5IRValConst, val)) {
                        if (auto c = std::get_if<SP<R5IRValConst>>(&mapAllocaToVal[allocaTo]);
                            c == nullptr || *c != constVal) {
                            changed                  = true;
                            mapAllocaToVal[allocaTo] = constVal;
                        }
                    } else {
                        if (std::get_if<NAC>(&mapAllocaToVal[allocaTo]) == nullptr) {
                            changed                  = true;
                            mapAllocaToVal[allocaTo] = NAC();
                        }
                    }
                }
            }
            // 遍历后继。
            for (auto& s : bb->getNext()) {
                if (visited.find(s) != visited.end()) { continue; }
                // m[B'] ∧= m'
                //  if m[B'] change then
                //      change = true
                //  end
            }
        }
    } while (changed);
    // 3. 没想好。
}

[[deprecated("Use For1Func instead.")]] void
IROptCP::OptForOneFunction(const shared_ptr<MiddleIRFuncDef>& func)
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

        std::map<SP<AllocaInst>, SP<R5IRValConst>>    mapAllocaToConst;
        std::queue<pair<SP<MiddleIRBasicBlock>, int>> q;
        std::set<SP<MiddleIRBasicBlock>>              setVisited;
        // 1st pass: add all CS
        for (const auto& p : b->getPrev()) { q.emplace(p, 0); }
        while (!q.empty()) {
            auto [bb, d] = q.front();
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
            for (const auto& p : bb->getPrev()) { q.emplace(p, d + 1); }
        }
        // 2nd pass: erase common store
        std::queue<SP<MiddleIRBasicBlock>> q2;
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
        IROptCF::ConstFold(b);
    }
}

}   // namespace MiddleIR::Optimizer
