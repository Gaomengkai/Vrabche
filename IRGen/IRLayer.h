//
// Created by gao on 6/28/23.
//

#ifndef SYSYLEX_IRLAYER_H
#define SYSYLEX_IRLAYER_H

#include "IRSen.h"
#include <vector>
#include <unordered_map>
#include <memory>

using std::unordered_map;
namespace IRCtrl
{
struct IRLayer {
    // using unordered_map instead of vector
    unordered_map<std::string, std::shared_ptr<IRVal>> symbols;
};
}   // namespace IRCtrl


#endif   // SYSYLEX_IRLAYER_H
