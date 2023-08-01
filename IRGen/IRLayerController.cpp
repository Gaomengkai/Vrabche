//
// Created by gao on 6/28/23.
//

#include "IRLayerController.h"
#include "IRLogger.h"
#include "IRUtils.h"
#include <iostream>
#include <cassert>

namespace IRCtrl
{
[[maybe_unused]] bool IRCtrl::IRLayerController::isInGlobal() const
{
    return this->_layers.size() <= 1;
}


IRCtrl::IRLayerController::IRLayerController()
{
    dive();
}


void IRCtrl::IRLayerController::dive()
{
    IRLayer layer;
    this->_layers.emplace_back(layer);
}


void IRCtrl::IRLayerController::ascend()
{
    this->_layers.pop_back();
}

///
/// \param val
/// \return
std::shared_ptr<IRCtrl::IRVal>
IRCtrl::IRLayerController::query(const std::shared_ptr<IRVal>& val, bool recursively)
{
    return query(val->name, recursively);
}

///
/// \param symbol_name
/// \return
std::shared_ptr<IRCtrl::IRVal>
IRCtrl::IRLayerController::query(const std::string& symbol_name, bool recursively)
{
    CHECK_LAYER_EMPTY;
    for (auto it = this->_layers.rbegin(); it != this->_layers.rend(); it++) {
        auto sy = it->symbols.find(symbol_name);
        if (sy != it->symbols.end()) { return sy->second; }
        if (!recursively) break;
    }
    return nullptr;
}


void IRCtrl::IRLayerController::push(const std::shared_ptr<IRVal>& val)
{
    this->_layers[_layers.size() - 1].symbols.insert(std::make_pair(val->name, val));
}


std::shared_ptr<IRVal> IRLayerController::queryLocal(const string& symbol_name, bool recursively)
{
    for (auto i = _layers.size() - 1; i > 0; i--) {
        auto sy = _layers[i].symbols.find(symbol_name);
        if (sy != _layers[i].symbols.end()) { return sy->second; }
        if (!recursively) break;
    }
    return nullptr;
}
void IRLayerController::pushGlobal(const shared_ptr<IRVal>& val)
{
    if (_layers.empty()) {
        LOGE("ERROR no layers!");
        return;
    }
    _layers.front().symbols[val->name] = val;
}
std::shared_ptr<IRVal>
IRLayerController::queryLocalConst(const string& symbol_name, const string& functionName)
{
    string idName = Utils::localConstName(functionName, symbol_name);
    if (_layers.empty())
        return nullptr;
    else {
        auto sy = _layers.front().symbols.find(idName);
        if (sy == _layers.front().symbols.end())
            return nullptr;
        else
            return sy->second;
    }
}
size_t IRLayerController::getCurLayerNum()
{
    assert(!_layers.empty());
    return _layers.size()-1;
}
void IRLayerController::push(const string& name, const shared_ptr<IRVal>& val) {
    this->_layers[_layers.size() - 1].symbols.insert(std::make_pair(name, val));
}


}   // namespace IRCtrl