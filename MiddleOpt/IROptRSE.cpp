//
// Created by gaome on 2023/8/6.
//

#include "IROptRSE.h"
#include <unordered_set>
namespace MiddleIR::Optimizer
{
IROptRSE::IROptRSE(const shared_ptr<MiddleIRAST>& irast)
    : IROptimizerBase(irast)
{
}
void IROptRSE::run()
{
    hasChanged = false;
    for (auto& func : _irast->funcDefs) {
        for (auto& bb : func->getBasicBlocks()) { For1BB(bb); }
    }
}
void IROptRSE::For1BB(const shared_ptr<MiddleIRBasicBlock>& b)
{
    // 删除一个基本块中的冗余load语句

    // 一个store语句是可以删除的，当且仅当：
    // 1. 假设这个store语句的目的地是%a，那么在这个store语句之后，没有任何一条语句使用%a,
    //    直到出现下一个store至%a的语句。而且，这个下一条store语句的目的地也是%a。

    // 算法：维护一个map: Dst -> SP<StoreInst>，表示目的地为Dst的最近一次store语句。
    // 再维护一个set: SP<StoreInst>，表示要删除的store语句。
    // 遍历BB中的每一条语句，如果是store语句：
    // 1. 如果map中已经有了这个目的地，那么就把map中的这个目的地对应的store语句加入set。
    // 然后把这个store语句加入map。
    // 2. 如果map中没有这个目的地，那么就把这个store语句加入map。
    // 如果是load语句：
    // 1. 如果map中没有这个目的地，那么忽略。
    // 2. 如果map中有这个目的地，那么从map中删除这个目的地。
    std::unordered_map<shared_ptr<MiddleIRVal>, shared_ptr<StoreInst>> map1;
    std::unordered_set<shared_ptr<StoreInst>>                          set1;

    for (auto& i : b->_instructions) {
        if (auto storeInst = DPC(StoreInst, i)) {
            auto from     = storeInst->getFrom();
            auto fromName = from->getName();
            if (fromName.size() > 5 && fromName.substr(0, 5) == "%arg_") { continue; }
            auto dst = storeInst->getTo();
            if (map1.find(dst) != map1.end()) { set1.insert(map1[dst]); }
            map1[dst] = storeInst;
        } else if (auto loadInst = DPC(LoadInst, i)) {
            auto dst = loadInst->getFrom();
            map1.erase(dst);
        }
    }

    for (auto it = b->_instructions.begin(); it != b->_instructions.end();) {
        if (set1.find(DPC(StoreInst, *it)) != set1.end()) {
            it         = b->_instructions.erase(it);
            hasChanged = true;
        } else {
            it++;
        }
    }
}

}   // namespace MiddleIR::Optimizer