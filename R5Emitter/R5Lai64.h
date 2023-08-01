//
// Created by gaome on 2023/7/23.
//

#ifndef IRBACKENDR5_R5LAI64_H
#define IRBACKENDR5_R5LAI64_H

#include "R5Taichi.h"
namespace R5Emitter
{

class R5Lai64 : public R5Taichi
{
public:
    bool operator==(const R5Taichi& rhs) const override;
    bool operator!=(const R5Taichi& rhs) const override;

public:
    explicit R5Lai64(int64_t value_)
        : R5Taichi(Lai64)
        , value(value_)
    {
    }
    [[nodiscard]] string toString() const override;
    [[nodiscard]] string toString(bool b) const override;
    int64_t              value;
};

}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5LAI64_H
