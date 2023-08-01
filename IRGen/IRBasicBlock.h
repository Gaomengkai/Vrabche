//
// Created by gao on 6/30/23.
//

#ifndef SYSYLEX_IRBASICBLOCK_H
#define SYSYLEX_IRBASICBLOCK_H

#include <utility>

#include "IRTypes.h"
#include "IRSen.h"


namespace IRCtrl
{
class IRBasicBlock
{
public:
    string             name;
    vector<UPLocalSen> instructions;
    IRBasicBlock*      parent = nullptr;
    explicit IRBasicBlock(string name1)
        : name(std::move(name1))
    {
    }
    explicit IRBasicBlock(string name1, IRBasicBlock* _parent)
        : name(std::move(name1))
        , parent(_parent)
    {
    }
    void add(UPLocalSen sen);
    string getLabel() const;

    bool hasTerminalSen();
};

using SPBasicBlock = std::shared_ptr<IRBasicBlock>;
}   // namespace IRCtrl



#endif   // SYSYLEX_IRBASICBLOCK_H
