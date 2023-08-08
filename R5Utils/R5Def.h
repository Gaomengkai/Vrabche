//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5DEF_H
#define IRBACKENDR5_R5DEF_H

#include <memory>
#include <any>
#include <utility>
#include <vector>
#include <stack>
#include <sstream>
using std::any_cast;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::stack;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::vector;

#define MS make_shared
#define MU make_unique

#define ACS(_ST, _TARG) std::any_cast<shared_ptr<_ST>>((_TARG))
#define DPC(_ST, _TARG) std::dynamic_pointer_cast<_ST>((_TARG))
#define SPC(_ST, _TARG) std::static_pointer_cast<_ST>((_TARG))

#endif   // IRBACKENDR5_R5DEF_H
