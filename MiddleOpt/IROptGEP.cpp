//
// Created by 17269 on 2023/8/20.
//

#include "IROptGEP.h"
MiddleIR::Optimizer::IROptGEP::IROptGEP(const shared_ptr<MiddleIRAST>& irast)  : IROptimizerBase(irast) {

}
void MiddleIR::Optimizer::IROptGEP::run()
{
    hasChanged = false;
    for (const auto& f : _irast->funcDefs) {
        for (const auto& b : f->getBasicBlocks()) { hasChanged |= runOnBB(b); }
    }
}
bool MiddleIR::Optimizer::IROptGEP::runOnBB(const shared_ptr<MiddleIRBasicBlock>& bb)
{
    bool                        changed = false;
    decltype(bb->_instructions) newInsts;
    for (auto inst : bb->getInstructions()){
        if (!inst->isGetElementPtrInst()) {
            newInsts.push_back(inst);
            continue;
        }
        else {
            //把%v91 = getelementptr [500 x i32], [500 x i32]* %v90, i32 %v88, i32 %v89
            //改成%g1 = %v88 * 500
            //%g2 = %g1 + %v89
            //%g3 = %g2 * 4
            //%g4 = bitcast [500 x i32]* %v90 to i32*
            //%v91 = getelementptr i32, i32* %g4, i32 %g3
            auto i = DPC(GetElementPtrInst, inst);
            if (i->getIndex().size() <= 1) {
                IR_ASSERT(i->getIndex().size() == 1, "getElementPtrInst's index size must be greater than 1");
                newInsts.push_back(inst);
                continue;
            }
            else {
                changed = true;
                auto added = i->getIndex()[i->getIndex().size() - 1];

                auto prototype = i->getType1();
                auto type1 = i->getType1();
                auto from  = i->getFrom();


                for (int j = 0; j < i->getIndex().size() - 1; j++) {
                    int64_t curShapeSizeBytes = 0;
                    if (auto aType1 = std::dynamic_pointer_cast<ArrayType>(type1)) {
                        curShapeSizeBytes = (int64_t)aType1->getSizeBytes();
                        type1             = aType1->getElementType();
                    } else {
                        curShapeSizeBytes = 4;
                    }
                    //先算出偏移量
                    auto mul_ = make_shared<IMathInst>(IMathInst::IMathOp::MUL, make_shared<IntType>(32), i->getIndex()[j], IR_INT_CONST(curShapeSizeBytes));
                    mul_->setName(G());
                    newInsts.push_back(mul_);

                    //再加到added上
                    auto add_ = make_shared<IMathInst>(IMathInst::IMathOp::ADD, make_shared<IntType>(32), mul_, added);
                    add_->setName(G());
                    newInsts.push_back(add_);
                    added = add_;
                }

                while (type1->isArray()) {
                    type1 = std::dynamic_pointer_cast<ArrayType>(type1)->getElementType();
                }

                //接下来bitcast
                auto bitcast_ = make_shared<BitCastInst>(prototype, from, makePointer(type1));
                bitcast_->setName(G());
                newInsts.push_back(bitcast_);

                //最后getelementptr
                i->_index.erase(i->_index.begin(), i->_index.end());
                i->_index.push_back(added);
                i->_type1 = type1;
                i->_from = bitcast_;
                i->_fromType = makePointer(type1);
                i->_useList.erase(i->_useList.begin(), i->_useList.end());
                i->_useList.emplace_back(&i->_from);
                i->_useList.emplace_back(&i->_index[0]);
                newInsts.push_back(i);
            }

        }
    }
    bb->_instructions.erase(bb->_instructions.begin(), bb->_instructions.end());
    bb->_instructions = newInsts;
    return changed;
}
