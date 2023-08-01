//
// Created by gao on 6/29/23.
//

#ifndef SYSYLEX_IRGLOBALSWITCH_H
#define SYSYLEX_IRGLOBALSWITCH_H

#include <stack>
#include <utility>

namespace IRCtrl
{

template<typename T>
class IRSwitch
{
public:
    virtual void dive()   = 0;
    virtual void ascend() = 0;

    virtual IRSwitch& operator=(T x) = 0;

    virtual void set(T) = 0;

    virtual T get() = 0;
};

class IRBoolSwitch : public IRSwitch<bool>
{
public:
    IRBoolSwitch& operator=(bool x) override
    {
        set(x);
        return *this;
    }

public:
    explicit IRBoolSwitch(string name)
        : _name(std::move(name)){
              //        LOGD("Constructed IRBoolSwitch");
          };

    explicit IRBoolSwitch(bool init)
        : _cur(init)
    {
    }

    void dive() override
    {
        if (_name == "isConst") {
            //            LOGD("CONST DIVE " << _stack.size() << _name);
        }
        _stack.push(_cur);
        if (_name == "isConst") {
            //            LOGD("CONST DIVE" << _stack.size());
        }
    }

    void dive(bool x)
    {
        dive();
        _cur = x;
    }

    void set(bool t) override { _cur = t; }

    void ascend() override
    {
        _cur = _stack.top();
        _stack.pop();
        if (_name == "isConst") {
            //            LOGD("CONST ascend" << _stack.size() << _name);
        }
    }

    bool get() override { return _cur; }

    explicit operator bool() const { return _cur; }

private:
    std::stack<bool> _stack;
    bool             _cur = false;
    string           _name;
};

class IRGlobalSwitch
{
public:
    IRBoolSwitch isConst;
    IRBoolSwitch isInFunc;
    IRBoolSwitch needLoad;
    IRBoolSwitch isCVal;
    IRBoolSwitch needLLValLoad;
    IRBoolSwitch isBool;
    IRBoolSwitch inIf;
    IRBoolSwitch inWhile;
    IRBoolSwitch isNewFunc;

    IRGlobalSwitch()
        : isConst(std::string("isConst"))
        , isInFunc(std::string("inFUnc"))
        , needLoad(std::string("needLoad"))
        , isCVal(std::string("isCVal"))
        , needLLValLoad(std::string("needLLValLoad"))
    , isBool(std::string("isBool"))
    , inIf(std::string("inIf"))
    , inWhile(std::string("inWhile"))
    , isNewFunc(std::string("isNewFunc"))
    {
    }
};
}   // namespace IRCtrl

#endif   // SYSYLEX_IRGLOBALSWITCH_H
