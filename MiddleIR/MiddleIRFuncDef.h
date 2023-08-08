//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_MIDDLEIRFUNCDEF_H
#define IRBACKENDR5_MIDDLEIRFUNCDEF_H

#include "R5Def.h"
#include "MiddleIRVal.h"
#include "MiddleIRBasicBlock.h"
#include "MiddleIRFuncDecl.h"
#include "MiddleIRBrInst.h"
#include <unordered_map>
namespace MiddleIR
{

class MiddleIRFuncDef : public MiddleIRFuncDecl
{
private:
    std::vector<std::shared_ptr<MiddleIRBasicBlock>>                     _basicBlocks;
    std::unordered_map<std::string, std::shared_ptr<MiddleIRBasicBlock>> _basicBlockMap;
    std::unordered_map<std::string, std::shared_ptr<MiddleIRVal>>        _valMap;

public:
    MiddleIRFuncDef(
        SPType                                           type_,
        std::string                                      name_,
        std::vector<SPType>                              params_types_,
        std::vector<std::string>                         params_names_,
        std::vector<std::shared_ptr<MiddleIRBasicBlock>> basicBlocks_
    )
        : MiddleIRFuncDecl(
              std::move(type_), std::move(name_), std::move(params_types_), std::move(params_names_)
          )
        , _basicBlocks(std::move(basicBlocks_))
    {
        for (int i = 0; i < _params_names.size(); i++) {
            addVal(
                _params_names[i], std::make_shared<MiddleIRVal>(_params_types[i], _params_names[i])
            );
        }
    }
    void addBasicBlock(const std::shared_ptr<MiddleIRBasicBlock>& basicBlock_)
    {
        _basicBlocks.emplace_back(basicBlock_);
        _basicBlockMap[basicBlock_->getName()] = basicBlock_;
    }
    [[nodiscard]] const std::vector<std::shared_ptr<MiddleIRBasicBlock>>& getBasicBlocks() const
    {
        return _basicBlocks;
    }
    void setBasicBlocks(const std::vector<std::shared_ptr<MiddleIRBasicBlock>>& basicBlocks_)
    {
        _basicBlocks = basicBlocks_;
    }
    void addVal(const std::string& name_, const std::shared_ptr<MiddleIRVal>& val_)
    {
        _valMap[name_] = val_;
    }
    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<MiddleIRVal>>& getValMap(
    ) const
    {
        return _valMap;
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRBasicBlock>& getBasicBlock(const std::string& name_
    ) const
    {
        return _basicBlockMap.at(name_);
    }
    [[nodiscard]] const std::shared_ptr<MiddleIRVal>& getVal(const std::string& name_) const
    {
        return _valMap.at(name_);
    }
    void buildBBPrevNext()
    {
        for (const auto& bb : this->_basicBlocks) {
            auto ter = bb->getTerminator();
            if (ter->isBrInst()) {
                auto brInst = std::dynamic_pointer_cast<BrInst>(ter);
                brInst->getIfTrue()->addPrev(bb);
                bb->addNext(brInst->getIfTrue());
                if (brInst->getIfFalse()) {
                    brInst->getIfFalse()->addPrev(bb);
                    bb->addNext(brInst->getIfFalse());
                }
            }
        }
    }
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRFUNCDEF_H
