//
// Created by gaome on 2023/7/20.
//

#ifndef IRBACKENDR5_R5FUNCTION_H
#define IRBACKENDR5_R5FUNCTION_H

#include <unordered_map>
#include <list>
#include "R5Def.h"
#include "R5Taichi.h"
#include "R5AsmStrangeFake.h"

namespace R5Emitter
{

struct R5Function {
    size_t                                    stackSize;
    std::list<R5AsmStrangeFake>               asmList;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5FUNCTION_H
