//
// Created by gao on 6/26/23.
//

#include "IRBuilder.h"
#include "SysyParser.h"
#include "IRLogger.h"
#include <utility>
#include <ostream>
#include <sstream>
namespace IRCtrl
{

IRCtrl::IRBuilder::IRBuilder()
{
    program = make_shared<IRProgram>();

    // declare i32 @getint()
    auto type_i32_void   = MS<FuncType>(IRValType::Int, vector<SPType>{});
    auto type_float_void = MS<FuncType>(IRValType::Float, vector<SPType>{});
    auto type_void_i32   = MS<FuncType>(IRValType::Void, vector<SPType>{makeType(IRValType::Int)});
    auto type_void_float =
        MS<FuncType>(IRValType::Void, vector<SPType>{makeType(IRValType::Float)});
    auto type_i32_i32_star =
        MS<FuncType>(IRValType::Int, vector<SPType>{makePointer(makeType(IRValType::Int))});
    auto type_i32_float_star =
        MS<FuncType>(IRValType::Int, vector<SPType>{makePointer(makeType(IRValType::Float))});
    auto type_void_i32_i32_star = MS<FuncType>(
        IRValType::Void,
        vector<SPType>{makeType(IRValType::Int), makePointer(makeType(IRValType::Int))}
    );
    auto type_void_i32_float_star = MS<FuncType>(
        IRValType::Void,
        vector<SPType>{makeType(IRValType::Int), makePointer(makeType(IRValType::Float))}
    );

    // declare i32 @getint()
    auto func_getint = MS<IRFunction>(type_i32_void, "getint", true);
    // declare float @getfloat()
    auto func_getfloat = MS<IRFunction>(type_float_void, "getfloat", true);
    // declare i32 @getch()
    auto func_getch = MS<IRFunction>(type_i32_void, "getch", true);
    // declare i32 @getarray(i32*)
    auto func_getarray = MS<IRFunction>(type_i32_i32_star, "getarray", true);
    // declare i32 @getfarray(float*)
    auto func_getfarray = MS<IRFunction>(type_i32_float_star, "getfarray", true);
    // declare void @putint(i32)
    auto func_putint = MS<IRFunction>(type_void_i32, "putint", true);
    // declare void @putfloat(float)
    auto func_putfloat = MS<IRFunction>(type_void_float, "putfloat", true);
    // declare void @putch(i32)
    auto func_putch = MS<IRFunction>(type_void_i32, "putch", true);
    // declare void @putarray(i32, i32*)
    auto func_putarray = MS<IRFunction>(type_void_i32_i32_star, "putarray", true);
    // declare void @putfarray(i32, float*)
    auto func_putfarray = MS<IRFunction>(type_void_i32_float_star, "putfarray", true);
    // declare void @_sysy_starttime(i32)
    auto func_sysy_starttime = MS<IRFunction>(type_void_i32, "_sysy_starttime", true);
    // declare void @_sysy_stoptime(i32)
    auto func_sysy_stoptime = MS<IRFunction>(type_void_i32, "_sysy_stoptime", true);

    // add into functions
    program->addFunction(func_getint);
    program->addFunction(func_getfloat);
    program->addFunction(func_getch);
    program->addFunction(func_getarray);
    program->addFunction(func_getfarray);
    program->addFunction(func_putint);
    program->addFunction(func_putfloat);
    program->addFunction(func_putch);
    program->addFunction(func_putarray);
    program->addFunction(func_putfarray);
    program->addFunction(func_sysy_starttime);
    program->addFunction(func_sysy_stoptime);
}


void IRCtrl::IRBuilder::build(std::ostream& os)
{
    os << build();
}

std::string IRCtrl::IRBuilder::build()
{
    std::stringstream ss;

    // Other Info about file
    ss << "; Filename = " << this->_filename << "\n";
    ss << "declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)\n";
    for (auto& one : _stmts) {
        ss << one;
        ss << '\n';
    }

    // Main Code
    // Global const
    for (auto& c : this->program->getGlobalConst()) {
        GlobalValDeclSen declSen(c->name, c);
        ss << declSen.toString() << "\n";
    }

    // Global Variables
    for (auto& c : this->program->getGlobalVar()) {
        GlobalValDeclSen declSen(c->name, c);
        ss << declSen.toString() << "\n";
    }

    // Functions
    for (auto& f : this->program->getFuncs()) { ss << f->toString() << "\n"; }

    return ss.str();
}

IRCtrl::IRBuilder::IRBuilder(const std::string& filename)
    : IRBuilder()
{
    _filename = filename;
    _as("source_filename = \"" + _filename + "\"");
}

void IRCtrl::IRBuilder::_as(const std::string& s)
{
    _stmts.emplace_back(s);
}


int IRCtrl::IRBuilder::getNewLabelInt()
{
    _label += 1;
    return _label;
}



void IRCtrl::IRBuilder::setFilename(const std::string& filename)
{
    this->_filename = filename;
}
void IRCtrl::IRBuilder::createFunction(IRCtrl::FuncType& type1, const string& name1)
{
    this->thisFunction = make_shared<IRFunction>(type1, name1);
    _label             = -1;
    _bb_label= 0;
}
void IRCtrl::IRBuilder::finishFunction()
{
    assert(this->thisFunction != nullptr);
    this->program->addFunction(thisFunction);
    this->thisFunction = nullptr;
}
const shared_ptr<IRCtrl::IRProgram>& IRCtrl::IRBuilder::getProgram() const
{
    return program;
}
const shared_ptr<IRFunction>& IRCtrl::IRBuilder::getFunction() const
{
    return thisFunction;
}
void IRBuilder::addSen(unique_ptr<LocalSen> sen)
{
    this->thisFunction->curBB->add(std::move(sen));
}

string IRBuilder::getNewLabel()
{
    return localVarPrefix + std::to_string(this->getNewLabelInt());
}

int IRBuilder::getLastLabelInt() const
{
    return this->_label;
}

/// contains "%"
/// \return
string IRBuilder::getLastLabel() const
{
    return localVarPrefix + std::to_string(getLastLabelInt());
}

const unique_ptr<LocalSen>& IRBuilder::getLastSen() const
{
    return getFunction()->curBB->instructions.back();
}
void IRBuilder::checkTypeAndCast(const SPType& from, const SPType& to, const string& from_name)
{
    checkTypeAndCast(from->type,to->type, from_name);
}
const unique_ptr<LocalSen>& IRBuilder::addAdd(const SPType& t_, const string& v1, const string& v2)
{
    unique_ptr<BiSen> s;
    if (t_->type == IRValType::Float) {
        s           = MU<BiSen>(getNewLabel(), IROp::FADD, v1, t_, v2);
        s->_retType = makeType(IRValType::Float);
    } else {
        s           = MU<BiSen>(getNewLabel(), IROp::ADD, v1, t_, v2);
        s->_retType = makeType(IRValType::Int);
    }
    addSen(std::move(s));
    return getLastSen();
}
const unique_ptr<LocalSen>& IRBuilder::addSub(const SPType& t_, const string& v1, const string& v2)
{
    unique_ptr<BiSen> s;
    if (t_->type == IRValType::Float) {
        s           = MU<BiSen>(getNewLabel(), IROp::FSUB, v1, t_, v2);
        s->_retType = makeType(IRValType::Float);
    } else {
        s           = MU<BiSen>(getNewLabel(), IROp::SUB, v1, t_, v2);
        s->_retType = makeType(IRValType::Int);
    }
    addSen(std::move(s));
    return getLastSen();
}
void IRBuilder::checkTypeAndCast(IRValType from, IRValType to, const string& from_name)
{
    if (from == to) { return; }
    if (from == IRValType::Float && to == IRValType::Int) {
        auto sen =
            MU<FpToSiSen>(this->getNewLabel(), makeType(IRValType::Float), from_name);
        this->addSen(std::move(sen));
    } else if (from == IRValType::Int && to == IRValType::Float) {
        auto sen = MU<SiToFpSen>(this->getNewLabel(), makeType(IRValType::Int), from_name);
        this->addSen(std::move(sen));
    }else if(from==IRValType::Bool&&to==IRValType::Int){
        auto sen = MU<ZextSen>(this->getNewLabel(), from_name, IRValType::Bool);
        this->addSen(std::move(sen));
    } else {
        RUNTIME_ERROR("!!! Cannot Check Type Not in FLOAT and INT !!!");
    }
}
shared_ptr<IRFunction> IRBuilder::getFunction(const string& funcName)
{
    for (auto& f : this->program->getFuncs()) {
        if (f->name == funcName) { return f; }
    }
    if(this->thisFunction!= nullptr && this->thisFunction->name == funcName){
        return this->thisFunction;
    }
    LOGE("Cannot find function " + funcName);
    throw std::runtime_error("Cannot find function " + funcName);
    return nullptr;
}
const unique_ptr<LocalSen>& IRBuilder::addMul(const SPType& t_, const string& v1, const string& v2)
{
    unique_ptr<BiSen> s;
    if (t_->type == IRValType::Float) {
        s           = MU<BiSen>(getNewLabel(), IROp::FMUL, v1, t_, v2);
        s->_retType = makeType(IRValType::Float);
    } else {
        s           = MU<BiSen>(getNewLabel(), IROp::MUL, v1, t_, v2);
        s->_retType = makeType(IRValType::Int);
    }
    addSen(std::move(s));
    return getLastSen();
}
const unique_ptr<LocalSen>& IRBuilder::addDiv(const SPType& t_, const string& v1, const string& v2)
{
    unique_ptr<BiSen> s;
    if (t_->type == IRValType::Float) {
        s           = MU<BiSen>(getNewLabel(), IROp::FDIV, v1, t_, v2);
        s->_retType = makeType(IRValType::Float);
    } else {
        s           = MU<BiSen>(getNewLabel(), IROp::SDIV, v1, t_, v2);
        s->_retType = makeType(IRValType::Int);
    }
    addSen(std::move(s));
    return getLastSen();
}
const unique_ptr<LocalSen>& IRBuilder::addRem(const SPType& t_, const string& v1, const string& v2)
{
    // MUST BE INT
    unique_ptr<BiSen> s;
    s           = MU<BiSen>(getNewLabel(), IROp::SREM, v1, t_, v2);
    s->_retType = makeType(IRValType::Int);
    addSen(std::move(s));
    return getLastSen();
}
SPBB IRBuilder::addBB(const string& name)
{
    if (this->thisFunction == nullptr) {
        throw std::runtime_error("Cannot add BB without function");
    }
    auto bb = MS<IRBasicBlock>(name);
    this->thisFunction->bbs.emplace_back(bb);
    return bb;
}
SPBB IRBuilder::createBB()
{
    auto bbName = getNewBBLabel();
    return addBB(bbName);
}
int  IRBuilder::getNewBBLabelInt()
{
    _bb_label+=1;
    return _bb_label;
}
string IRBuilder::getNewBBLabel()
{
    return bbPrefix+std::to_string(getNewBBLabelInt());
}
void IRBuilder::moveToBB(SPBB bb) {
    this->thisFunction->curBB = std::move(bb);
}

}   // namespace IRCtrl