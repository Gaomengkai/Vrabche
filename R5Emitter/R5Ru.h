//
// Created by gaome on 2023/7/21.
//

#ifndef IRBACKENDR5_R5RU_H
#define IRBACKENDR5_R5RU_H

#include <utility>

#include "R5Taichi.h"

namespace R5Emitter
{

class R5Ru : public R5Taichi
{
public:
    bool operator==(const R5Taichi& rhs) const override;
    bool operator!=(const R5Taichi& rhs) const override;

public:
    explicit R5Ru(string labelName_)
        : R5Taichi(Ru)
        , labelName(std::move(labelName_))
    {
    }
    [[nodiscard]] string toString() const override;
    string               toString(bool b) const override;
    string               labelName;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5RU_H
