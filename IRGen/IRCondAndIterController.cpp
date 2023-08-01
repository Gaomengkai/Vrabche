//
// Created by gao on 7/1/23.
//

#include "IRCondAndIterController.h"
#include "IRLogger.h"

#include <utility>

namespace IRCtrl
{

IRCondAndIterController::IRCondAndIterController() = default;
void IRCondAndIterController::pushIf(
    SPBB trueBB_, SPBB ifFalseBB_, SPBB ifAfterBB_, size_t curLayerNum_
)
{
    auto newLayer = make_shared<IRBBLayer>();
    newLayer->trueBB = std::move(trueBB_);
    newLayer->falseBB     = std::move(ifFalseBB_);
    newLayer->afterBB     = std::move(ifAfterBB_);
    newLayer->curLayerNum = curLayerNum_;
    newLayer->type = IRBBLayer::If;
    _layers.push_back(newLayer);
}
void IRCondAndIterController::pushWhile(
    SPBB trueBB_, SPBB whileCondBB_, SPBB whileBreakBB_, size_t curLayerNum_
)
{
    auto newLayer = make_shared<IRBBLayer>();
    newLayer->trueBB = std::move(trueBB_);
    newLayer->condBB       = std::move(whileCondBB_);
    newLayer->afterBB = std::move(whileBreakBB_);
    newLayer->falseBB = newLayer->afterBB;
    newLayer->curLayerNum = curLayerNum_;
    newLayer->type = IRBBLayer::While;
    _layers.push_back(newLayer);
}
void IRCondAndIterController::pop() {
    _layers.pop_back();
}
SPBB IRCondAndIterController::queryIfTrueBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::If) {
            return (*it)->trueBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryIfTrueBB: no if layer");
    return nullptr;
}
SPBB IRCondAndIterController::queryIfFalseBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::If) {
            return (*it)->falseBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryIfFalseBB: no if layer");
    return nullptr;
}
SPBB IRCondAndIterController::queryIfAfterBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::If) {
            return (*it)->afterBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryIfAfterBB: no if layer");
    return nullptr;
}

SPBB IRCondAndIterController::queryWhileCondBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::While) {
            return (*it)->condBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryWhileCondBB: no while layer");
    return nullptr;
}
SPBB IRCondAndIterController::queryWhileTrueBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::While) {
            return (*it)->trueBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryWhileTrueBB: no while layer");
    return nullptr;
}
size_t IRCondAndIterController::queryWhileCurLayerNum()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::While) {
            return (*it)->curLayerNum;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryWhileCurLayerNum: no while layer");
    return -1;
}
SPBB IRCondAndIterController::queryTrueBB()
{
    if(_layers.empty()) {
        RUNTIME_ERROR("IRCondAndIterController::queryTrueBB: no layer");
    }
    for(auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if((*it)->trueBB!= nullptr) {
            return (*it)->trueBB;
        }
    }
    RUNTIME_ERROR("IRCondAndIterController::queryTrueBB: no trueBB");
}
SPBB IRCondAndIterController::queryFalseBB()
{
    if(_layers.empty()) {
        RUNTIME_ERROR("IRCondAndIterController::queryFalseBB: no layer");
    }
    for(auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if((*it)->falseBB!= nullptr) {
            return (*it)->falseBB;
        }
    }
    RUNTIME_ERROR("IRCondAndIterController::queryFalseBB: no falseBB");
}
SPBB IRCondAndIterController::queryWhileBreakBB()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); it++) {
        if ((*it)->type == IRBBLayer::While) {
            return (*it)->falseBB;
        }
    }
    throw std::runtime_error("IRCondAndIterController::queryWhileCurLayerNum: no while layer");
    return nullptr;
}
void IRCondAndIterController::pushOr(SPBB falseBB_) {
    auto newLayer = make_shared<IRBBLayer>();
    newLayer->falseBB = std::move(falseBB_);
    newLayer->type = IRBBLayer::Or;
    _layers.push_back(newLayer);
}
void IRCondAndIterController::pushAnd(SPBB trueBB_) {
    auto newLayer = make_shared<IRBBLayer>();
    newLayer->trueBB = std::move(trueBB_);
    newLayer->type = IRBBLayer::And;
    _layers.push_back(newLayer);
}
}   // namespace IRCtrl