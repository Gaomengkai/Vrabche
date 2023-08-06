//
// Created by gaome on 2023/8/5.
//

#ifndef VRABCHE_IROPTIC_H
#define VRABCHE_IROPTIC_H
#include "IROptimizerBase.h"
#include "MiddleIRType.h"
#include <map>
#include <memory>
#include <queue>



namespace MiddleIR::Optimizer
{

using SPInst = shared_ptr<MiddleIRInst>;
using SPVal  = shared_ptr<MiddleIRVal>;
using SPType = shared_ptr<MiddleIRType>;
class IMathWithConst
{
public:
    explicit IMathWithConst(const shared_ptr<IMathInst>& inst) {
        _op = inst->getIMathOp();
        if (inst->getOpVal1()->isConst()) {
            _val00.first = inst->getOpVal1();
            _val00.second = 1;
            _val01.first = IR_INT_CONST(0);
            _val01.second = 0;
        }
        else {
            auto op1 = dynamic_pointer_cast<IMathInst>(inst->getOpVal1());
            _val00.first = op1->getOpVal1();
            _val00.second = _val00.first->isConst()? dynamic_pointer_cast<R5IRValConstInt>(_val00.first)->getValue() : 1 ;
            _val01.first = op1->getOpVal2();
            _val01.second = _val01.first->isConst()? dynamic_pointer_cast<R5IRValConstInt>(_val01.first)->getValue() : 1;
            _opSon = op1->getIMathOp();
        }
        if (inst->getOpVal2()->isConst()) {
            _val10.first = inst->getOpVal2();
            _val10.second = 1;
            _val11.first = IR_INT_CONST(0);
            _val11.second = 0;
        }
        else {
            auto op2 = dynamic_pointer_cast<IMathInst>(inst->getOpVal2());
            _val10.first = op2->getOpVal1();
            _val10.second = _val10.first->isConst()? dynamic_pointer_cast<R5IRValConstInt>(_val10.first)->getValue() : 1 ;
            _val11.first = op2->getOpVal2();
            _val11.second = _val11.first->isConst()? dynamic_pointer_cast<R5IRValConstInt>(_val11.first)->getValue() : 1;
            _opSon = op2->getIMathOp();
        }
    };
    bool couldCombine() {
        bool strangeFake = (_val00.first->isConst() + _val01.first->isConst() + _val10.first->isConst() + _val11.first->isConst() == 3) && (_op == _opSon);
        if (strangeFake) LOGW("could combine, now combine");
        else LOGW("not strange fake");
        return strangeFake;
    }
    std::pair<SPVal, SPVal> combine() {
        SPVal lval;
        SPVal rval = IR_INT_CONST(0);
        if (_op == IMathInst::IMathOp::ADD) {
            if (_val00.first->isConst()) {
                rval = IR_INT_CONST(_val00.second + std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
            }
            else {
                lval = _val00.first;
            }
            if (_val01.first->isConst()) {
                rval = IR_INT_CONST(_val01.second + std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
            }
            else {
                lval = _val01.first;
            }
            if (_val10.first->isConst()) {
                rval = IR_INT_CONST(_val10.second + std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
            }
            else {
                lval = _val10.first;
            }
            if (_val11.first->isConst()) {
                rval = IR_INT_CONST(_val11.second + std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
            }
            else {
                lval = _val11.first;
            }
        }
        if (_op == IMathInst::IMathOp::SUB) {
            if (!_val00.first->isConst()) {
                lval = _val00.first;
                rval = IR_INT_CONST(_val01.second + _val10.second + _val11.second + std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
            }
            if (!_val01.first->isConst()) {
                rval = _val01.first;
                lval = IR_INT_CONST(_val00.second + _val10.second + _val11.second + std::dynamic_pointer_cast<R5IRValConstInt>(lval)->getValue());
            }
            if (!_val10.first->isConst()) {
                rval = _val10.first;
                lval = IR_INT_CONST(_val00.second + _val01.second + _val11.second + std::dynamic_pointer_cast<R5IRValConstInt>(lval)->getValue());
            }
            if (!_val11.first->isConst()) {
                rval = _val11.first;
                lval = IR_INT_CONST(_val00.second + _val01.second + _val10.second + std::dynamic_pointer_cast<R5IRValConstInt>(lval)->getValue());
            }
        }
        if (_op == IMathInst::IMathOp::MUL) {
            rval = IR_INT_CONST(1);
            if (_val00.first->isConst()) {
                if (!std::dynamic_pointer_cast<R5IRValConstInt>(_val00.first)->isZero()) {
                    rval = IR_INT_CONST(_val00.second * std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
                }

            }
            else {
                lval = _val00.first;
            }
            if (_val01.first->isConst()) {
                if (!std::dynamic_pointer_cast<R5IRValConstInt>(_val01.first)->isZero()) {
                    rval = IR_INT_CONST(_val01.second * std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
                }
            }
            else {
                lval = _val01.first;
            }
            if (_val10.first->isConst()) {
                if (!std::dynamic_pointer_cast<R5IRValConstInt>(_val10.first)->isZero()) {
                    rval = IR_INT_CONST(_val10.second * std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
                }
            }
            else {
                lval = _val10.first;
            }
            if (_val11.first->isConst()) {
                if (!std::dynamic_pointer_cast<R5IRValConstInt>(_val11.first)->isZero()) {
                    rval = IR_INT_CONST(_val11.second * std::dynamic_pointer_cast<R5IRValConstInt>(rval)->getValue());
                }
            }
            else {
                lval = _val11.first;
            }
        }
        if (_op == IMathInst::IMathOp::SDIV) {
            if (!_val00.first->isConst()) {
                lval = _val00.first;
                rval = IR_INT_CONST((_val01.second == 0? 1:_val01.second) * (_val10.second == 0 ? 1:_val10.second) * (_val11.second == 0 ? 1 : _val11.second));
            }
            if (!_val01.first->isConst())  {
                rval = _val01.first;
                lval = IR_INT_CONST(_val00.second / (_val10.second==0?1:_val10.second)/(_val11.second==0?1:_val11.second));
            }
            if (!_val10.first->isConst()) {
                rval = _val10.first;
                lval = IR_INT_CONST(_val00.second / (_val01.second==0?1:_val01.second)/(_val11.second==0?1:_val11.second));
            }
            if (!_val11.first->isConst()) {
                rval = _val11.first;
                lval = IR_INT_CONST(_val00.second / (_val01.second==0?1:_val01.second)/(_val10.second==0?1:_val10.second));
            }
        }
        return std::make_pair(lval, rval);

    }
    virtual ~IMathWithConst() = default;
protected:
    std::pair<SPVal , int> _val00;
    std::pair<SPVal , int> _val01;
    std::pair<SPVal , int> _val10;
    std::pair<SPVal , int> _val11;
    IMathInst::IMathOp _op;
    IMathInst::IMathOp _opSon;
};





class IROptIC : public IROptimizerBase
{
public:
    explicit IROptIC(const shared_ptr<MiddleIRAST>& irast);
    ~IROptIC() override = default;
    void run() override;
};

}   // namespace MiddleIR::Optimizer


#endif   // VRABCHE_IROPTIC_H
