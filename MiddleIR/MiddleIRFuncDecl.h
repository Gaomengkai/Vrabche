//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_MIDDLEIRFUNCDECL_H
#define IRBACKENDR5_MIDDLEIRFUNCDECL_H
#include <utility>

#include "MiddleIRType.h"
#include "R5Def.h"
#include "MiddleIRVal.h"
namespace MiddleIR
{

class MiddleIRFuncDecl : public MiddleIRVal
{
protected:
    SPType              _retType;
    std::vector<SPType> _params_types;

public:
    [[nodiscard]] const vector<SPType>& getParamsTypes() const { return _params_types; }

protected:
    std::vector<std::string> _params_names;

public:
    MiddleIRFuncDecl(
        SPType                   type_,
        std::string              name_,
        std::vector<SPType>      params_types_,
        std::vector<std::string> params_names_
    )
        : MiddleIRVal(make_shared<MiddleIRType>(MiddleIRType::FUNCTION))
        , _retType(std::move(type_))
        , _params_types(std::move(params_types_))
        , _params_names(std::move(params_names_))
    {
        _name = std::move(name_);
        IR_ASSERT(
            _params_types.size() == _params_names.size(),
            "params_types.size() != params_names.size()"
        );
    }
    [[nodiscard]] const SPType& getRetType() const { return _retType; }
};

}   // namespace MiddleIR

#endif   // IRBACKENDR5_MIDDLEIRFUNCDECL_H
