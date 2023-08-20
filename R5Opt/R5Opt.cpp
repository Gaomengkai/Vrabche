//
// Created by gaome on 2023/8/20.
//

#include <list>
#include "R5Opt.h"
#include "R5Lai.h"
#include "R5Lai64.h"


namespace R5Emitter::Opt
{
void R5Opt::runOnBB(vector<R5AsmStrangeFake>& b)
{
    // wtf?
    R5Opt::delAdd0(b);
}
void R5Opt::delAdd0(vector<R5AsmStrangeFake>& b)
{
    std::list<R5AsmStrangeFake> k;
    for (auto& c : b) {
        if (c.fakeOP != ADDI && c.fakeOP != ADDIW && c.fakeOP != MV) {
            k.push_back(c);
            continue;
        }
        if (std::static_pointer_cast<R5Yang>(c.operands[0])->reg !=
            std::static_pointer_cast<R5Yang>(c.operands[1])->reg) {
            k.push_back(c);
            continue;
        }
        if (c.fakeOP == MV) { continue; }
        if ((!c.operands[2]->isLai()) && (!c.operands[2]->isLai64())) {
            k.push_back(c);
            continue;
        }
        auto i = DPC(R5Lai, c.operands[2]);
        auto p = DPC(R5Lai64, c.operands[2]);
        if (i && i->value == 0) { continue; }
        if (p && p->value == 0) { continue; }
        k.push_back(c);
    }
    b = std::vector<R5AsmStrangeFake>(k.begin(), k.end());
}
}   // namespace R5Emitter::Opt
