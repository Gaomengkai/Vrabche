//
// Created by gaome on 2023/8/20.
//

#ifndef VRABCHE_R5OPT_H
#define VRABCHE_R5OPT_H
#include <vector>
#include "R5AsmStrangeFake.h"

namespace R5Emitter::Opt
{

class R5Opt
{
public:
    static void runOnBB(std::vector<R5AsmStrangeFake>& b);
    static void delAdd0(vector<R5AsmStrangeFake>& b);
};

} // namespace R5Emitter::Opt


#endif   // VRABCHE_R5OPT_H
