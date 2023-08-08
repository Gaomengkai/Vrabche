//
// Created by gaome on 2023/7/14.
//

#ifndef IRBACKENDR5_MIDDLEIRBASICBLOCK_H
#define IRBACKENDR5_MIDDLEIRBASICBLOCK_H

#include "R5Def.h"
#include "MiddleIRInst.h"
#include "R5Logger.h"
#include <list>

namespace MiddleIR
{
class MiddleIRBasicBlock
{
private:
    std::string                              _name;
    std::set<shared_ptr<MiddleIRBasicBlock>> _next;
    std::set<shared_ptr<MiddleIRBasicBlock>> _prev;
    std::shared_ptr<MiddleIRInst>            _terminator;

public:
    std::list<std::shared_ptr<MiddleIRInst>> _instructions;
    [[nodiscard]] auto&                      getInstructions() const { return _instructions; }
    explicit MiddleIRBasicBlock(std::string name_)
        : _name(std::move(name_))
    {
    }
    void addInstruction(std::shared_ptr<MiddleIRInst> inst)
    {
        _instructions.emplace_back(std::move(inst));
    }
    void addNext(shared_ptr<MiddleIRBasicBlock> next_) { _next.insert(std::move(next_)); }
    void addPrev(shared_ptr<MiddleIRBasicBlock> prev_) { _prev.insert(std::move(prev_)); }
    void setTerminator(std::shared_ptr<MiddleIRInst> terminator_)
    {
        if (_terminator != nullptr)
            LOGW("MiddleIRBasicBlock::setTerminator: _terminator is not nullptr");
        if (!terminator_->isTerminatorInst())
            RUNTIME_ERROR("MiddleIRBasicBlock::setTerminator: terminator_ is not a terminator inst"
            );
        _terminator = std::move(terminator_);
    }
    [[nodiscard]] const std::set<shared_ptr<MiddleIRBasicBlock>>& getNext() const { return _next; }
    [[nodiscard]] const std::set<shared_ptr<MiddleIRBasicBlock>>& getPrev() const { return _prev; }
    [[nodiscard]] std::shared_ptr<MiddleIRInst> getTerminator() { return _terminator; }
    [[nodiscard]] const std::string&            getName() const { return _name; }
};
}   // namespace MiddleIR



#endif   // IRBACKENDR5_MIDDLEIRBASICBLOCK_H
