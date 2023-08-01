//
// Created by gaome on 2023/7/27.
//

#ifndef IRBACKENDR5_R5UTILS_H
#define IRBACKENDR5_R5UTILS_H

#include "R5FakeSeihai.h"
#include "ArrayHelper.h"
#include "MiddleIRVal.h"
#include "R5IREmitter.h"
#include <utility>
namespace R5Emitter
{
std::set<R5Emitter::YangReg>
funcCallUsedReg(string funcName, const std::shared_ptr<MiddleIRAST>& irast);
}
#endif   // IRBACKENDR5_R5UTILS_H
