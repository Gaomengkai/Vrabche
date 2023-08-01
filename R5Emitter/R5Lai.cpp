//
// Created by gaome on 2023/7/21.
//

#include "R5Lai.h"

namespace R5Emitter
{
string R5Lai::toString() const
{
    return std::to_string(value);
}
void R5Lai::negative()
{
    value = -value;
}
bool R5Lai::operator==(const R5Taichi& rhs) const
{
    return R5Taichi::operator==(rhs) && value == dynamic_cast<const R5Lai&>(rhs).value;
}
bool R5Lai::operator!=(const R5Taichi& rhs) const
{
    return R5Taichi::operator!=(rhs) || value != dynamic_cast<const R5Lai&>(rhs).value;
}
string R5Lai::toString(bool b) const
{
    return toString();
}
}   // namespace R5Emitter