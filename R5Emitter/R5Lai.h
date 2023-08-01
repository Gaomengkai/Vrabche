//
// Created by gaome on 2023/7/21.
//

#ifndef IRBACKENDR5_R5LAI_H
#define IRBACKENDR5_R5LAI_H

#include "R5Taichi.h"
namespace R5Emitter
{

// 立即数（没有废话，只能是整数）
class R5Lai : public R5Taichi
{
public:
    explicit R5Lai(int value_)
        : R5Taichi(Lai)
        , value(value_)
    {
    }
    bool operator==(const R5Taichi& rhs) const override;
    bool operator!=(const R5Taichi& rhs) const override;
    // 负号操作
    void                 negative();
    [[nodiscard]] string toString() const override;
    string               toString(bool b) const override;
    int                  value;
};


}   // namespace R5Emitter

#endif   // IRBACKENDR5_R5LAI_H
