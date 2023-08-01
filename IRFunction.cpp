//
// Created by gao on 7/1/23.
//

#include "IRFunction.h"
#include "IRUtils.h"
#include "IRLogger.h"
#include "IRGlobal.h"
namespace IRCtrl
{
string IRFunction::toString()
{
    /*
     * vector<SPLocalVar> alloca;
        vector<SPBasicBlock> bbs;
        SPBasicBlock curBB;
        FuncType _type;
     */
    string arm_tag;
    if (IRCtrl::IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC) arm_tag = "arm_aapcs_vfpcc ";
    if (onlyDecl) {
        // declare void @putarray(i32, i32*)
        stringstream ss;
        string       retTypeStr = Utils::valTypeToStr(this->_type.retType);
        // declare i32 @funcName(
        ss << "declare ";
        if (IRCtrl::IR_SWITCH_ENABLE_DSO_LOCAL) ss << "dso_local ";
        ss << arm_tag << retTypeStr << " @" << this->name << "(";
        // i32, i32*
        size_t labelNum = 0;
        for (auto& t : this->_type.paramsType) {
            ss << t->toString() << ", ";
            labelNum += 1;
        }
        // cut the last ","
        if (labelNum != 0) {
            string s = ss.str();
            if (!s.empty()) {
                s.pop_back();
                s.pop_back();
            }
            ss.str("");
            ss << s;
        }
        ss << ")";
        return ss.str();
    }

    stringstream ss;
    string       retTypeStr = Utils::valTypeToStr(this->_type.retType);
    // define i32 @funcName(
    ss << "define ";
    if (IRCtrl::IR_SWITCH_ENABLE_DSO_LOCAL) ss << "dso_local ";
    ss << arm_tag << retTypeStr << " @" << this->name << "(";
    // i32 %arg_0, [59 x i32]* %arg_1,
    size_t labelNum = 0;
    for (auto& t : this->_type.paramsType) {
        ss << t->toString() << " %arg_" << labelNum << ", ";
        labelNum += 1;
    }

    // del the last ","
    if (labelNum != 0) {
        string s = ss.str();
        if (!s.empty()) {
            s.pop_back();
            s.pop_back();
        }
        ss.str("");
        ss << s;
    }

    //    string s = ss.str();
    //    s=s.substr(0,s.size()-2);
    //    ss.clear();
    ss << ") {\n";

    vector<unique_ptr<LocalSen>> allocas;
    vector<unique_ptr<LocalSen>> notAllocas;
    // when generate code, we must put all the alloca at the beginning of the function.
    // it is LEntry block.
    // first, we gather all the alloca.
    for(auto& b : bbs) {
        for(auto& s : b->instructions) {
            if(s->getOp()==IROp::ALLOCA) {
                allocas.push_back(std::move(s));
            }
        }
    }
    // 2. find LEntry block.
    for(auto& b : bbs) {
        if(b->name=="LEntry") {
            // 3. insert all the alloca to LEntry block.
            for(auto t=allocas.rbegin();t!=allocas.rend();t++) {
                b->instructions.insert(b->instructions.begin(), std::move(*t));
            }
            break;
        }
    }
    for (auto& b : bbs) {
        if(b->instructions.empty()) {
            // add return.
            switch(this->_type.retType) {
            case IRValType::Int:
                b->add(MU<ReturnSen>("0", makeType(IRValType::Int)));
                break;
            case IRValType::Float:
                b->add(MU<ReturnSen>("0x0", makeType(IRValType::Float)));
                break;
            case IRValType::Void:
                b->add(MU<ReturnSen>("", makeType(IRValType::Void)));
                break;

            // unreachable cases.
            case IRValType::Pointer:
            case IRValType::FloatArr:
            case IRValType::IntArr:
            case IRValType::Bool:
            case IRValType::Func:
            case IRValType::Arr:
            case IRValType::Unknown:
                RUNTIME_ERROR("Unreachable cases.");
            }
        }
        ss << b->name << ":\n";
        for (auto& s : b->instructions) {
            if(s== nullptr) continue ;
            ss << "    " << s->toString() << "\n";
            if(isTerminal(*s)) break ;
        }
    }
    ss << "}\n";
    return ss.str();
}
size_t IRFunction::getParamsNum() const
{
    return _type.paramsType.size();
}

}   // namespace IRCtrl