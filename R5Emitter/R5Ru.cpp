//
// Created by gaome on 2023/7/21.
//

#include "R5Ru.h"

namespace R5Emitter
{
string R5Ru::toString() const
{
    return labelName;
}
bool R5Ru::operator==(const R5Taichi& rhs) const
{
    return R5Taichi::operator==(rhs) && labelName == dynamic_cast<const R5Ru&>(rhs).labelName;
}
bool R5Ru::operator!=(const R5Taichi& rhs) const
{
    return R5Taichi::operator!=(rhs) || labelName != dynamic_cast<const R5Ru&>(rhs).labelName;
}
string R5Ru::toString(bool b) const
{
    // b is removing first "@"
    if (b && labelName[0] == '@') return labelName.substr(1);
    return labelName;
}
}   // namespace R5Emitter