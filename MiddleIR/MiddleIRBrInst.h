//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_MIDDLEIRBRINST_H
#define IRBACKENDR5_MIDDLEIRBRINST_H

#include <utility>

#include "MiddleIRInst.h"
#include "MiddleIRVal.h"
#include "MiddleIRBasicBlock.h"
namespace MiddleIR
{
class BrInst : public MiddleIR::MiddleIRInst
{
public:
    enum BrType { UnCondBr, CondBr } _brType;

private:
    std::shared_ptr<MiddleIRVal> _cond;

private:
    std::shared_ptr<MiddleIRBasicBlock> _ifTrue;
    std::shared_ptr<MiddleIRBasicBlock> _ifFalse;

public:
    [[nodiscard]] const string& getIfTrueLabel() const { return _ifTrueLabel; }
    [[nodiscard]] const string& getIfFalseLabel() const { return _ifFalseLabel; }

private:
    string _ifTrueLabel;
    string _ifFalseLabel;

public:
    BrInst(
        BrType                                     brType_,
        std::shared_ptr<MiddleIRVal>               cond_,
        const std::shared_ptr<MiddleIRBasicBlock>& ifTrue_,
        const std::shared_ptr<MiddleIRBasicBlock>& ifFalse_
    )
        : MiddleIRInst(MiddleIRInst::InstType::BrInst, spVoidType)
        , _brType(brType_)
        , _cond(std::move(cond_))
        , _ifTrue(ifTrue_)
        , _ifFalse(ifFalse_)
    {
    }
    BrInst(
        BrType                       brType_,
        std::shared_ptr<MiddleIRVal> cond_,
        string                       ifTrueLabel_,
        string                       ifFalseLabel_
    )
        : MiddleIRInst(MiddleIRInst::InstType::BrInst, spVoidType)
        , _brType(brType_)
        , _cond(std::move(cond_))
        , _ifTrueLabel(std::move(ifTrueLabel_))
        , _ifFalseLabel(std::move(ifFalseLabel_))
    {
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>&        getCond() const { return _cond; }
    [[nodiscard]] const std::shared_ptr<MiddleIRBasicBlock>& getIfTrue() const { return _ifTrue; }
    [[nodiscard]] const std::shared_ptr<MiddleIRBasicBlock>& getIfFalse() const { return _ifFalse; }
    void setIfTrue(const shared_ptr<MiddleIRBasicBlock>& ifTrue) { _ifTrue = ifTrue; }
    void setIfFalse(const shared_ptr<MiddleIRBasicBlock>& ifFalse) { _ifFalse = ifFalse; }
};
}   // namespace MiddleIR
#endif   // IRBACKENDR5_MIDDLEIRBRINST_H
