//
// Created by gaome on 2023/7/13.
//

#include "MiddleIRInst.h"

namespace MiddleIR
{
[[maybe_unused]] bool MiddleIRInst::tryReplaceUse(
    const std::shared_ptr<MiddleIRVal>& oldVal, const std::shared_ptr<MiddleIRVal>& newVal
)
{
    bool replaced = false;
    for (auto& use : _useList) {
        if (*use == oldVal) {
            *use     = newVal;
            replaced = true;
            break;
        }
    }
    return replaced;
}
bool MiddleIRInst::isDeleted() const
{
    return _deleted;
}
void MiddleIRInst::setDeleted(bool deleted)
{
    _deleted = deleted;
}
}   // namespace MiddleIR