//
// Created by gaome on 2023/7/23.
//

#include "R5Lai64.h"

namespace R5Emitter
{
string R5Lai64::toString() const
{
    return std::to_string(value);
}
bool R5Lai64::operator==(const R5Taichi& rhs) const
{
    return R5Taichi::operator==(rhs) && value == dynamic_cast<const R5Lai64&>(rhs).value;
}
bool R5Lai64::operator!=(const R5Taichi& rhs) const
{
    return R5Taichi::operator!=(rhs) || value != dynamic_cast<const R5Lai64&>(rhs).value;
}
string R5Lai64::toString(bool b) const
{
    return toString();
}

}   // namespace R5Emitter