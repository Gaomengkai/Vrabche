#include "SysyVisitor.h"
#include "IRBuilder.h"
#include "IRLogger.h"
#include "IRUtils.h"
#include "IRExceptions.h"
#include "IRGlobalSwitch.h"
#include "IRCondAndIterController.h"
#include "IRGlobal.h"

namespace IRCtrl
{
// Init builder and layer controller
std::shared_ptr<IRCtrl::IRBuilder> g_builder =
    std::make_shared<IRCtrl::IRBuilder>(IRCtrl::IRBuilder());
std::shared_ptr<IRCtrl::IRLayerController> g_lc =
    std::make_shared<IRCtrl::IRLayerController>(IRCtrl::IRLayerController());
std::shared_ptr<IRCtrl::IRGlobalSwitch> g_sw =
    std::make_shared<IRCtrl::IRGlobalSwitch>(IRCtrl::IRGlobalSwitch());
std::shared_ptr<IRCtrl::IRCondAndIterController> g_bbc =
    std::make_shared<IRCtrl::IRCondAndIterController>(IRCtrl::IRCondAndIterController());

// tool functions for IRVisitor
/// from a std::any val to get last value.
/// \param aVal
/// \return IRValType and string
std::tuple<IRValType, string> getLastValue(std::any aVal)
{
    if (aVal.type() == typeid(std::shared_ptr<CVal>)) {
        auto irval = ACS(CVal, aVal);
        return {irval->type, irval->toString()};
    } else if (aVal.type() == typeid(int) && std::any_cast<int>(aVal) == 0x7de6543d) {
        return {IRValType::Unknown, ""};
    } else {
        auto& lastSen = g_builder->getLastSen();
        return {lastSen->_retType->type, lastSen->_label};
    }
}

/// A wrapper of getLastValue(std::any aVal), only check lastSen.
/// \return
std::tuple<IRValType, string> getLastValue() {
    auto& lastSen = g_builder->getLastSen();
    return {lastSen->_retType->type, lastSen->_label};
}
}   // namespace IRCtrl

using namespace IRCtrl;
using IRCtrl::g_builder;
using IRCtrl::g_lc;
using IRCtrl::g_sw;
#define IR_IS_CONST g_sw->isConst.get()

// ---end tool functions

/// compUnit: compUnitItem* EOF;
/// \param context
/// \return
std::any IRVisitor::visitCompUnit(SysyParser::CompUnitContext* context)
{
    LOGD("Enter CompUnit");



    for (auto& x : context->compUnitItem()) { x->accept(this); }

    LOGD("Exit CompUnit\nWell done.");
    return 0;
}

/// compUnitItem: decl | funcDef;
/// \param context
/// \return
std::any IRVisitor::visitCompUnitItem(SysyParser::CompUnitItemContext* context)
{
    if (context->decl() != nullptr) {
        context->decl()->accept(this);
    } else if (context->funcDef() != nullptr) {
        context->funcDef()->accept(this);
    }
    return 0;
}


/// decl: constDecl | varDecl;
/// \param context
/// \return
std::any IRVisitor::visitDecl(SysyParser::DeclContext* context)
{
    if (context->constDecl() != nullptr) {
        context->constDecl()->accept(this);
    } else if (context->varDecl() != nullptr) {
        context->varDecl()->accept(this);
    }
    return 0;
}

/// constDecl: Const bType constDef (Comma constDef)* Semicolon;
/// \param context
/// \return
std::any IRVisitor::visitConstDecl(SysyParser::ConstDeclContext* context)
{
    // Set this layer to const.
    g_sw->isConst.dive();
    g_sw->isConst.set(true);
    context->bType()->accept(this);   // this will change curBType;
    for (auto& x : context->constDef()) { x->accept(this); }
    g_sw->isConst.ascend();           // resume
    return 0;
}

/// bType: Int # int | Float # float;
/// \param context
/// \return
std::any IRVisitor::visitInt(SysyParser::IntContext* context)
{
    curBType = VT_INT;
    return curBType;
}

/// bType: Int # int | Float # float;
/// \param context
/// \return
std::any IRVisitor::visitFloat(SysyParser::FloatContext* context)
{
    curBType = VT_FLOAT;
    return curBType;
}

/// constDef: Ident (Lbracket exp Rbracket)* Assign initVal;
/// constDecl: Const bType constDef (Comma constDef)* Semicolon;
/// \param context
/// \return
std::any IRVisitor::visitConstDef(SysyParser::ConstDefContext* context)
{
    //    LOGD("Enter VisitConstDef");
    auto p      = context->parent;
    auto parent = dynamic_cast<SysyParser::ConstDeclContext*>(p);
    if (parent != nullptr) {
        auto              bType = parent->bType();
        IRCtrl::IRValType type;
        if (dynamic_cast<SysyParser::FloatContext*>(bType)) {
            type = VT_FLOAT;
        } else {
            type = VT_INT;
        }
        auto idName = string(context->Ident()->getText());

        auto initVal = context->initVal();

        // not array
        if (context->exp().empty()) {
            // single val
            // initVal:
            //	init	 # init
            auto init_ = dynamic_cast<SysyParser::InitContext*>(initVal);

            // Single value(not array) shouldn't have initList rather than init
            if (init_ == nullptr) throw std::runtime_error("Fuck!");

            auto number_any_val = init_->accept(this);   // Accept
            auto number_val     = std::any_cast<std::shared_ptr<CVal>>(number_any_val);
            auto int_val        = std::dynamic_pointer_cast<IntCVal>(number_val);
            auto float_val      = std::dynamic_pointer_cast<FloatCVal>(number_val);
            if (type == VT_INT) {
                // Int
                int num = (int_val != nullptr) ? int_val->iVal : (int)float_val->fVal;
                //                LOGD(num);
                // Judge if in Global
                if (g_lc->isInGlobal()) {
                    // global const int
                    auto thisIntConstVal = std::make_shared<IntCVal>(idName, num);
                    g_lc->push(thisIntConstVal);
                    g_builder->getProgram()->addGlobalConst(thisIntConstVal);
                } else {
                    // local const int
                    string funcName = g_builder->getFunction()->name;
                    //                    string  = funcName + "." + idName;
                    auto localConstIdName = Utils::localConstName(funcName, idName);
                    // Can we init like this way???

                    auto thisIntConstVal = std::make_shared<IntCVal>(localConstIdName, num);
                    thisIntConstVal->id="@"+localConstIdName;
                    g_lc->push(idName,thisIntConstVal);
                    g_builder->getProgram()->addGlobalConst(thisIntConstVal);
                }
            } else {
                // Float
                float num;
                num = (float_val != nullptr) ? float_val->fVal : (float)int_val->iVal;
                //                LOGD(num);
                // const float in global?
                if (g_lc->isInGlobal()) {
                    // const float global
                    auto thisFloatConstVal = make_shared<FloatCVal>(idName, num);
                    g_lc->push(thisFloatConstVal);
                    g_builder->getProgram()->addGlobalConst(thisFloatConstVal);
                } else {
                    // local const int
                    string funcName         = g_builder->getFunction()->name;
                    auto   localConstIdName = Utils::localConstName(funcName, idName);
                    // Can we init like this way???
                    auto thisFloatConstVal = std::make_shared<FloatCVal>(localConstIdName, num);
                    thisFloatConstVal->id="@"+localConstIdName;
                    g_lc->push(idName, thisFloatConstVal); // just put it in local variable layer.
                    g_builder->getProgram()->addGlobalConst(thisFloatConstVal);
                }
            }


        } else {
            // array cosnt val list

            // Array 1 : deal with shape
            std::deque<size_t> shape;
            for (auto& e : context->exp()) {
                auto   a           = e->accept(this);
                auto   number_val  = std::any_cast<std::shared_ptr<CVal>>(a);
                auto   int_val     = std::dynamic_pointer_cast<IntCVal>(number_val);
                auto   float_val   = std::dynamic_pointer_cast<FloatCVal>(number_val);
                size_t thisDimSize = (int_val != nullptr) ? int_val->iVal : (size_t)float_val->fVal;
                shape.emplace_back(thisDimSize);
            }

            // Array 2 : deal with init data
            auto iList_a     = context->initVal()->accept(this);
            auto iList       = any_cast<shared_ptr<InitListVal>>(iList_a);
            iList->contained = type;
            if (g_lc->isInGlobal()) {
                shared_ptr<CArr> thisArr;
                thisArr       = Utils::buildAnCArrFromInitList(iList, shape);
                thisArr->name = idName;
                g_lc->push(thisArr);
                g_builder->getProgram()->addGlobalConst(thisArr);
            } else {
                shared_ptr<CArr> thisArr;
                string           funcName          = g_builder->getFunction()->name;
                auto             thisArrGlobalName = Utils::localConstName(funcName, idName);
                thisArr                            = Utils::buildAnCArrFromInitList(iList, shape);
                thisArr->name                      = thisArrGlobalName;
                thisArr->id                        = "@"+thisArrGlobalName;
                g_lc->push(idName,thisArr);
                g_builder->getProgram()->addGlobalConst(thisArr);
            }
        }
    }
    //    LOGD("Exit  VisitConstDef");
    return 0;
}

/// varDecl: bType varDef (Comma varDef)* Semicolon;
/// \param context
/// \return
std::any IRVisitor::visitVarDecl(SysyParser::VarDeclContext* context)
{
    // FINAL
    // Although we are dealing with a VAR decl, but it's initVal is const.
    // so here we set isConst to TRUE.

    this->curBType = dynamic_cast<SysyParser::FloatContext*>(context->bType()) ? VT_FLOAT : VT_INT;
    for (auto& v : context->varDef()) { v->accept(this); }
    return 0;
}

std::any GlobalVarDef(SysyParser::VarDefContext* context, IRVisitor* this_)
{
    // vars type
    IRCtrl::IRValType type = this_->curBType;
    // idName
    string idName = context->Ident()->getText();
    LOGD("Enter VisitVarDef, id == " << idName);

    // Only in Global, the initList can be initialized as const numbers.
    g_sw->isConst.dive(true);

    if (context->exp().empty()) {

        // float/int a (= ?)*
        // get the init val if exists
        float fInit = 0;
        int   iInit = 0;
        // only not array, not lVal can be initialized by this_ way.
        // but how can we know is that a lVal?
        // use try...
        if (context->initVal() != nullptr && context->exp().empty()) {
            g_sw->isConst.dive(true);
            auto initVal  = std::any_cast<shared_ptr<CVal>>(context->initVal()->accept(this_));
            auto fValInit = std::dynamic_pointer_cast<FloatCVal>(initVal);
            auto iValInit = std::dynamic_pointer_cast<IntCVal>(initVal);
            if (fValInit != nullptr) {
                fInit = fValInit->fVal;
                iInit = (int)fInit;
            } else {
                iInit = iValInit->iVal;
                fInit = (float)iInit;
            }
            g_sw->isConst.ascend();
        }

        // make an object and push it into LayerController and Builder
        if (type == VT_FLOAT) {
            auto vVal = make_shared<FloatVal>(idName);
            if (context->initVal() != nullptr) {
                // Global float has initialized
                vVal->fVal    = fInit;
                vVal->hasInit = true;
            }
            g_lc->push(vVal);
            g_builder->getProgram()->addGlobalVar(vVal);
        } else {
            auto vVal = make_shared<IntVal>(idName);
            if (context->initVal() != nullptr) {
                // Global int has initialized
                vVal->iVal    = iInit;
                vVal->hasInit = true;
            }
            g_lc->push(vVal);
            g_builder->getProgram()->addGlobalVar(vVal);
        }
    } else {

        // Array             // float/int a[][][][] (= ?)?

        // Array 1 : deal with shape
        std::deque<size_t> shape;
        for (auto& e : context->exp()) {
            auto   a           = e->accept(this_);
            auto   number_val  = std::any_cast<std::shared_ptr<CVal>>(a);
            auto   int_val     = std::dynamic_pointer_cast<IntCVal>(number_val);
            auto   float_val   = std::dynamic_pointer_cast<FloatCVal>(number_val);
            size_t thisDimSize = (int_val != nullptr) ? int_val->iVal : (size_t)float_val->fVal;
            shape.emplace_back(thisDimSize);
        }

        // Array 2 : deal with init data
        shared_ptr<InitListVal> iList;
        if (context->initVal() == nullptr) {
            // has no initVal. just return a non-initialized VArr. just so.
            auto emptyIList = make_shared<InitListVal>();
            iList           = emptyIList;
        } else {
            auto iList_a = context->initVal()->accept(this_);
            iList        = any_cast<shared_ptr<InitListVal>>(iList_a);
        }
        iList->contained = this_->curBType;
        auto thisArr     = Utils::buildAnVArrFromInitList(iList, shape);
        thisArr->name    = idName;
        thisArr->advancedType =
            make_shared<ArrayType>(this_->curBType, vector<size_t>(shape.begin(), shape.end()));
        g_lc->push(thisArr);
        g_builder->getProgram()->addGlobalVar(thisArr);
    }

    g_sw->isConst.ascend();
    return 0;
}

/// varDef: Ident (Lbracket exp Rbracket)* (Assign initVal)?;
/// \param context
/// \return
std::any IRVisitor::visitVarDef(SysyParser::VarDefContext* context)
{

    // var's type
    IRCtrl::IRValType type = this->curBType;
    // idName
    string idName = context->Ident()->getText();
    LOGD("Enter VisitVarDef, id == " << idName);

    if (g_lc->isInGlobal()) {
        return GlobalVarDef(context, this);
    } else {
        LOGD("Local Var name == " << idName << ",  type = " << Utils::valTypeToStr(type));
        const string& newLabelS = g_builder->getNewLabel();
        // local single:
        if (context->exp().empty()) {
            // local float/int a (= ?)*
            auto sen = make_unique<AllocaSen>(newLabelS, makeType(type));
            g_builder->addSen(std::move(sen));

            // make a object and push it into LayerController and Builder
            if (type == VT_FLOAT) {
                auto vVal = make_shared<LocalFloat>(newLabelS, idName);
                g_lc->push(vVal);
            } else {
                auto vVal = make_shared<LocalInt>(newLabelS, idName);
                g_lc->push(vVal);
            }

            // All the code below is about init the val.
            // get the init val if exists

            // only not array, not lVal can be initialized by this way.
            // but how can we know is that a lVal?
            // use try...
            if (context->initVal() != nullptr) {
                // initVal may be lVal exp or pure number(CVal)
                shared_ptr<CVal> initVal;
                g_sw->isConst.dive(false);
                auto anyResult = context->initVal()->accept(this);
                g_sw->isConst.ascend();
                if (g_sw->isCVal) {
                    initVal                  = ACS(CVal, anyResult);
                    auto [pos, iInit, fInit] = Utils::parseCVal(initVal);
                    string actualValS;
                    if (type == VT_FLOAT) {
                        actualValS = Utils::floatTo64BitStr(fInit);
                    } else {
                        actualValS = std::to_string(iInit);
                    }
                    auto storeSen = MU<StoreSen>(newLabelS, makeType(type), actualValS);
                    g_builder->addSen(std::move(storeSen));
                } else {
                    auto [t,s] = getLastValue(anyResult);
                    auto lastLabel = s;
                    g_builder->checkTypeAndCast(makeType(t), makeType(type), lastLabel);
                    lastLabel = g_builder->getLastLabel();
                    auto storeSen = MU<StoreSen>(newLabelS, makeType(type), lastLabel);
                    g_builder->addSen(std::move(storeSen));
                }
            }

        } else {
            /*
             *   _                 _     _                      _                    _
                | |   ___  __ __ _| |   /_\  _ _ _ _   _ _  ___| |_   __ ___ _ _  __| |_
                | |__/ _ \/ _/ _` | |  / _ \| '_| '_| | ' \/ _ \  _| / _/ _ \ ' \(_-<  _|
                |____\___/\__\__,_|_| /_/ \_\_| |_|   |_||_\___/\__| \__\___/_||_/__/\__|
             */

            // Array 1 : deal with shape
            g_sw->isConst.dive(true);
            std::deque<size_t> shape;
            for (auto& e : context->exp()) {
                auto a                      = e->accept(this);
                auto number_val             = std::any_cast<std::shared_ptr<CVal>>(a);
                auto [position, iVal, fVal] = Utils::parseCVal(number_val);
                size_t thisDimSize          = iVal;
                shape.emplace_back(thisDimSize);
            }
            g_sw->isConst.ascend();

            // Alloca inserted.
            auto arrType =
                make_shared<ArrayType>(curBType, std::vector<size_t>(shape.begin(), shape.end()));
            auto allocaSen = make_unique<AllocaSen>(newLabelS, arrType);
            g_builder->addSen(std::move(allocaSen));

            // local Array 2 : deal with init data
            // attention: we needn't initialize the actual val into that VArr.
            // but we need to init the val
            shared_ptr<InitListVal> iList;
            iList                 = make_shared<InitListVal>();
            iList->contained      = this->curBType;
            auto thisArr          = Utils::buildAnVArrFromInitList(iList, shape);
            thisArr->advancedType = arrType;
            thisArr->name         = idName;
            thisArr->id           = newLabelS;
            g_lc->push(thisArr);

            // local Array 3: load data by visiting init list.
            if (context->initVal()) {
                size_t szArr = 4;   // i32 is 4
                for (auto x : shape) { szArr *= x; }
                // whether init or not, first do memset.
                auto memSet = MU<Memset>(g_builder->getNewLabel(), newLabelS, makePointer(arrType), 0, szArr
                );
                g_builder->addSen(std::move(memSet));

                // pass the shape to the init list
                // attention: this will pass to visitInitList. because there's no single value after
                // an array.
                /**
                 * std::vector<size_t> curShape;
                 * std::vector<size_t> curArrayPos;
                 * size_t curArrayDim;
                 * string curArrId;
                 * shared_ptr<IRCtrl::IRType> curArrType;
                 * */
                this->curShape = vector<size_t>(shape.begin(), shape.end());
                this->curArrayPos.clear();
                this->curArrayPos.resize(curShape.size(), 0);
                curArrayDim = 0;
                curArrId    = newLabelS;
                curArrType  = arrType;
                context->initVal()->accept(this);   // check visitInitList
                // finally add into lc. already inserted before. nothing to do here.
            }
        }
    }

    LOGD("Exit VisitVarDef");
    return 0;
}

std::any IRVisitor::visitInit(SysyParser::InitContext* context)
{
    // FINAL
    return context->exp()->accept(this);
}

/// According to shape, add N to cur.
/// \param shape [2][3]
/// \param cur [1][2]
/// \param N
/// \param startsAt
/// \param reset
void ArrayPosPlusN(
    const vector<size_t>& shape, vector<size_t>& cur, size_t N, int startsAt = -1, bool reset = true
)
{
    if (startsAt == -1) startsAt = shape.size() - 1;
    for (int i = startsAt; i >= 0; --i) {   // ATTENTION!!!!!!!!
        cur[i] += N;
        if (cur[i] < shape[i]) { break; }
        N = cur[i] / shape[i];
        cur[i] %= shape[i];
    }
    if (reset) {
        for (int i = startsAt + 1; i < shape.size(); ++i) { cur[i] = 0; }
    }
}

/// initVal: {{},1, 2, {}, {5}}
/// Lbrace (initVal (Comma initVal)*)? Rbrace	# initList;
/// \param context
/// \return 0
std::any IRVisitor::visitInitList(SysyParser::InitListContext* context)
{
    if (IR_IS_CONST) {
        auto ril = make_shared<InitListVal>();
        for (auto& x : context->initVal()) {
            auto accept = x->accept(this);   // ACCEPT
            try {
                auto il = ACS(InitListVal, accept);
                ril->initList.emplace_back(il);
                ril->which.emplace_back(IRCtrl::InitListVal::INITLIST);
            } catch (const std::bad_any_cast&) {
                auto cv = any_cast<shared_ptr<CVal>>(accept);
                ril->cVal.emplace_back(cv);
                ril->which.emplace_back(IRCtrl::InitListVal::CVAL);
            }
        }
        return ril;
    }
    // Not Const init. may need read from other variables.
    else {
        // int e[4][5]={{1,2,3,4,5},{},3};
        auto arrInnerType = curBType;
        for (auto& init : context->initVal()) {
            int thisDimBefore = curArrayPos[curArrayDim];
            // $accept
            curArrayDim++;
            const std::any& accept = init->accept(this);
            curArrayDim--;
            // #accept
            auto [type, lastId] = getLastValue(accept);
            if (type == IRCtrl::IRValType::Unknown) {
                // this branch is InitList.
                if (curArrayPos[curArrayDim] == thisDimBefore) {
                    ArrayPosPlusN(curShape, curArrayPos, 1, curArrayDim);
                }
            } else {
                // it was a Val no matter it is const
                if (type == VT_INT && arrInnerType == VT_FLOAT) {
                    // convert Int to Float.
                    g_builder->checkTypeAndCast(type, arrInnerType, lastId);
                    lastId = g_builder->getLastLabel();
                } else if (type == VT_FLOAT && arrInnerType == VT_INT) {
                    // convert Float to Int.
                    g_builder->checkTypeAndCast(type, arrInnerType, lastId);
                    lastId = g_builder->getLastLabel();
                }
                // get element ptr and store.
                auto gepLabel = g_builder->getNewLabel();
                auto gep      = MU<GepSen>(gepLabel, curArrType, curArrId, curArrayPos);
                g_builder->addSen(std::move(gep));
                auto st = MU<StoreSen>(gepLabel, makeType(arrInnerType), lastId);
                g_builder->addSen(std::move(st));

                ArrayPosPlusN(curShape, curArrayPos, 1);
            }
        }
        return 0x7de6543d;
    }
    return 0x7de6543d;
}

/// funcDef: funcType Ident Lparen funcFParams? Rparen block;
/// \param context
/// \return
std::any IRVisitor::visitFuncDef(SysyParser::FuncDefContext* context)
{
    context->funcType()->accept(this);   // this operation will change this->curBType

    // Func name
    string idName = context->Ident()->getText();
    LOGD("Enter FuncDef, name==" << idName);
    // Only for log
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
    switch (this->curBType) {
    case IRValType::Int: LOGD("Int Func"); break;
    case IRValType::Float: LOGD("Float Func"); break;
    case IRValType::Void: LOGD("Void Func"); break;
    }
#pragma clang diagnostic pop
    auto retType = this->curBType;

    // IRFunction signature
    // IRFunction fps
    vector<SPFPVar> fps;
    if (context->funcFParams()) {
        auto fp = std::any_cast<vector<SPFPVar>>(context->funcFParams()->accept(this));
        fps     = fp;
    }
    vector<SPType> fpTypes;
    fpTypes.reserve(fps.size());
    for (auto& p : fps) { fpTypes.emplace_back(p->fpType); }
    FuncType funcType(retType, fpTypes);
    // ↑↑↑↑↑↑ funcType here.

    // To build a function var, we need its name, FPTypes, and its returns.
    // In a function, we need to store its instructions.
    // And instructions were stored in BasicBlocks.

    // Another question: do we need to analyze the relationship between BasicBlocks?
    // I don't know yet.

    // So I just...

    // Forgive me.

    // Here we add a function to the builder. At the end of HERE function,
    g_builder->createFunction(funcType, idName);
    // after that, the function was stored in g_builder->thisFunction

    // Func Block
    g_sw->isInFunc.dive(true);
    g_lc->dive();
    // operating on args.
    //   %v9 = alloca i32
    //  store i32 %arg_0, i32* %v9
    for (int l = 0; l < fpTypes.size(); l++) {
        // alloca
        auto allocaSen = make_unique<AllocaSen>(g_builder->getNewLabel(), fpTypes[l]);
        g_builder->addSen(std::move(allocaSen));
        // store
        auto storeSen = MU<StoreSen>(g_builder->getLastLabel(), fpTypes[l], "%arg_" + std::to_string(l)
        );
        g_builder->addSen(std::move(storeSen));
        auto& fpVar = fps[l];
        fpVar->id   = g_builder->getLastLabel();   // reallocate id
        LOGD("FPVAR name=" << fpVar->name << ", id=" << fpVar->id);
        g_lc->push(fpVar);
    }
    // visit its block
    g_sw->isNewFunc=true;
    context->block()->accept(this);
    g_sw->isNewFunc=false;
    // check void function has ret sen?
    if (funcType.retType == IRCtrl::IRValType::Void) {
        for (auto& bb : g_builder->getFunction()->bbs) {
            if (!bb->hasTerminalSen()) {
                auto retSen = MU<ReturnSen>("", makeType(IRCtrl::IRValType::Void));
                bb->add(std::move(retSen));
            }
        }
    }
    g_lc->ascend();
    g_sw->isInFunc.ascend();

    // now we finished a function.
    g_builder->finishFunction();
    LOGD("Exit  FuncDef");
    return 0;
}

/// changes: this->curBType
/// \param context
/// \return this->curBType;
std::any IRVisitor::visitFuncType_(SysyParser::FuncType_Context* context)
{
    // FINAL
    if (dynamic_cast<SysyParser::FloatContext*>(context->bType())) {
        this->curBType = VT_FLOAT;
    } else {
        this->curBType = VT_INT;
    }
    return this->curBType;
}

/// changes: this->curBType
/// \param context
/// \return Void
std::any IRVisitor::visitVoid(SysyParser::VoidContext* context)
{
    // FINAL
    this->curBType = IRCtrl::IRValType::Void;
    return IRCtrl::IRValType::Void;
}

/// funcFParams: funcFParam (Comma funcFParam)*;
///
/// funcFParam:
///	bType Ident													# scalarParam
///	| bType Ident Lbracket Rbracket (Lbracket exp Rbracket)*	# arrayParam;
/// \param context
/// \return vector<SPFPVar> t;
std::any IRVisitor::visitFuncFParams(SysyParser::FuncFParamsContext* context)
{
    vector<SPFPVar> t;
    int             argN = 0;
    for (auto& x : context->funcFParam()) {
        auto v = std::any_cast<SPFPVar>(x->accept(this));
        v->id  = "arg_" + std::to_string(argN++);
        t.emplace_back(v);
    }
    return t;
}

/// funcFParam:
//	bType Ident													# scalarParam
//	| bType Ident Lbracket Rbracket (Lbracket exp Rbracket)*	# arrayParam;
/// \param context
/// \return
std::any IRVisitor::visitScalarParam(SysyParser::ScalarParamContext* context)
{
    context->bType()->accept(this);   // this will change cur->bType
    SPType fParam;
    switch (this->curBType) {
    case IRValType::Int: {
        fParam = make_shared<IntType>();
    } break;
    case IRValType::Float: {
        fParam = make_shared<FloatType>();
    } break;
    default: break;
    }
    SPFPVar fp = make_shared<FPVar>("", context->Ident()->getText());
    //    fp->fpType = fParam;
    fp->setFpType(fParam);
    return fp;
}

/// funcFParam:
/// 	| bType Ident Lbracket Rbracket (Lbracket exp Rbracket)*	# arrayParam;
/// \param context
/// \return
std::any IRVisitor::visitArrayParam(SysyParser::ArrayParamContext* context)
{
    context->bType()->accept(this);   // this will change cur->bType
    SPType fParam;

    // deal with shape
    vector<size_t> shape;
    shape.emplace_back(0);
    g_sw->isConst.dive(true);
    for (auto& e : context->exp()) {
        auto   a           = e->accept(this);
        auto   number_val  = std::any_cast<std::shared_ptr<CVal>>(a);
        auto   int_val     = std::dynamic_pointer_cast<IntCVal>(number_val);
        auto   float_val   = std::dynamic_pointer_cast<FloatCVal>(number_val);
        size_t thisDimSize = (int_val != nullptr) ? int_val->iVal : (size_t)float_val->fVal;
        shape.emplace_back(thisDimSize);
    }
    g_sw->isConst.ascend();

    fParam     = make_shared<ArrayType>(curBType, shape);
    SPFPVar fp = make_shared<FPVar>("", context->Ident()->getText());
    //    fp->fpType = fParam;
    fp->setFpType(fParam);
    return fp;


    // ATTENTION: I didn't make a
}

/// block: Lbrace blockItem* Rbrace;
/// \param context
/// \return
std::any IRVisitor::visitBlock(SysyParser::BlockContext* context)
{
    bool hereNewFunc = false;
    if(g_sw->isNewFunc) {
        hereNewFunc=true;
        g_sw->isNewFunc.dive(false);
    } else{
        g_lc->dive();
    }
    // In a Function.
    for (auto& x : context->blockItem()) { x->accept(this); }
    if(!hereNewFunc) {g_lc->ascend();}
    return 0;
}

/// blockItem: decl | stmt;
/// \param context
/// \return
std::any IRVisitor::visitBlockItem(SysyParser::BlockItemContext* context)
{
    // FINAL
    if (context->decl())
        return context->decl()->accept(this);
    else if (context->stmt())
        return context->stmt()->accept(this);
    return 0;
}



/// stmt:
///	lVal Assign exp Semicolon					# assign
/// \param context
/// \return
std::any IRVisitor::visitAssign(SysyParser::AssignContext* context)
{
    if (g_sw->isInFunc.get()) {
        // 这里左值有可能是一个数组，所以要先计算出数组的地址，然后再赋值
        g_sw->needLLValLoad.dive(true);
        g_sw->needLoad.dive(true);
        auto lVal_a = context->lVal()->accept(this);
        g_sw->needLLValLoad.ascend();
        g_sw->needLoad.ascend();
        SPType type;
        string target;
        // passed by IRVal
        if (lVal_a.type() == typeid(shared_ptr<IRVal>)) {
            auto lVal     = ACS(IRVal, lVal_a);
            auto localVar = DPC(LocalVar, lVal);
            if (localVar != nullptr)
                target = localVar->id;
            else
                target = "@" + lVal->name;
            LOGD("assign target = " << target);
            type = makeType(lVal->type);
        }
        // passed by lastSen
        else {
            IRValType t;
            tie(t, target) = getLastValue(lVal_a);
            type           = makeType(t);
        }

        g_sw->needLoad.dive(true);
        auto exp_a = context->exp()->accept(this);
        g_sw->needLoad.ascend();

        auto [rt, rs] = getLastValue(exp_a);
        if (type->type == VT_INT && rt == VT_FLOAT) {
            g_builder->checkTypeAndCast(VT_FLOAT, VT_INT, rs);
            rs = g_builder->getLastLabel();
        } else if (type->type == VT_FLOAT && rt == VT_INT) {
            g_builder->checkTypeAndCast(VT_INT, VT_FLOAT, rs);
            rs = g_builder->getLastLabel();
        }
        auto s = MU<StoreSen>(target, type, rs);
        g_builder->addSen(std::move(s));
    }
    return 0;
}

/// 	| exp? Semicolon							# exprStmt
/// \param context
/// \return
std::any IRVisitor::visitExprStmt(SysyParser::ExprStmtContext* context)
{
    if (context->exp() != nullptr) { return context->exp()->accept(this); }
    return 0x11451419;
}

/// stmt:
//	| block										# blockStmt
/// \param context
/// \return
std::any IRVisitor::visitBlockStmt(SysyParser::BlockStmtContext* context)
{
    return context->block()->accept(this);
}



/// stmt:
///	| Return exp? Semicolon						# return;
/// \param context
/// \return
std::any IRVisitor::visitReturn(SysyParser::ReturnContext* context)
{
    if (context->exp() == nullptr) {
        g_builder->addSen(MU<ReturnSen>("", makeType(IRCtrl::IRValType::Void)));
    } else {
        auto r           = context->exp()->accept(this);
        auto funcRetType = makeType(g_builder->getFunction()->_type.retType);
        if (g_sw->isCVal.get()) {
            auto   cv = ACS(CVal, r);
            size_t pos;
            int    iVal;
            float  fVal;
            std::tie(pos, iVal, fVal) = Utils::parseCVal(cv);
            if (pos > 0) {   // valid return number.
                if (g_builder->getFunction()->_type.retType == VT_INT) {
                    auto retInt = MU<ReturnSen>(std::to_string(iVal), funcRetType);
                    g_builder->addSen(std::move(retInt));
                } else {
                    auto retFl = MU<ReturnSen>(Utils::floatTo64BitStr(fVal), funcRetType);
                    g_builder->addSen(std::move(retFl));
                }
            }
        }
        // LVal expression branch
        else {
            // it must inserted a sen into builder.
            auto& lastSen  = g_builder->getLastSen();
            auto  lastName = g_builder->getLastLabel();
            g_builder->checkTypeAndCast(lastSen->_retType, funcRetType, lastName);
            auto ret = MU<ReturnSen>(g_builder->getLastLabel(), funcRetType);
            g_builder->addSen(std::move(ret));
        }
    }
    return 0;
}

/// If the result is CVal, it will return. Otherwise it doesn't return anything.
/// Instead, this function will add a sen into current function.
/// \param context
/// \return shared_ptr<CVal> or nothing.
std::any IRVisitor::visitExp(SysyParser::ExpContext* context)
{
    // FINAL.
    auto a = context->addExp()->accept(this);

    try {
        ACS(CVal, a);
        g_sw->isCVal.set(true);
        return a;
    } catch (const std::bad_any_cast&) {
        g_sw->isCVal.set(false);
        return 0;
    }
}



/// lVal: Ident (Lbracket exp Rbracket)*;
/// \param context
/// \return
std::any IRVisitor::visitLVal(SysyParser::LValContext* context)
{
    if (g_sw->isConst.get()) {
        // Const, we need to actually calc the true value
        // First of all, we must check if the val is array.

        string idName = context->Ident()->getText();
        if (context->exp().empty()) {
            // 1. query local const first.
            shared_ptr<IRVal> t = g_lc->queryLocal(idName);
            if (t == nullptr) {
                // 2. query global.
//                if(g_sw->isInFunc)
//                    t = g_lc->queryLocalConst(idName, g_builder->getFunction()->name);
                if (t == nullptr) t = g_lc->query(idName);
                assert(t != nullptr);
            }
            g_sw->isCVal = true;
            return DPC(CVal, t);
        } else {
            // 3. deal with const array
            std::vector<int> indices;
            for (auto& e : context->exp()) {
                auto c              = e->accept(this);
                auto [_1, iVal, _2] = Utils::parseCVal(ACS(CVal, c));
                indices.emplace_back(iVal);
            }
            shared_ptr<IRVal> t = g_lc->queryLocal(idName);
            if (t == nullptr) {
                // 2. query global.
//                if(g_sw->isInFunc)
//                    t = g_lc->queryLocalConst(idName, g_builder->getFunction()->name);
                if (t == nullptr) t = g_lc->query(idName);
                assert(t != nullptr);
            }
            auto cv      = DPC(CArr, t);
            auto cVal    = cv->access(indices);
            g_sw->isCVal = true;
            return cVal;
        }
    } else {
        // Non const, we need generate some code to store the result.
        string idName = context->Ident()->getText();
        LOGD("lVal idName=" << idName);
        string            sourceId;
        bool              isLocal = true;
        shared_ptr<IRVal> t       = g_lc->queryLocal(idName);
        if (t == nullptr) {
            // query global.
//            if(g_sw->isInFunc)
//                t = g_lc->queryLocalConst(idName, g_builder->getFunction()->name);
            if (t == nullptr) t = g_lc->query(idName);
            IR_ASSERT(t != nullptr, "lVal: " << idName << " not found.");
            isLocal  = false;
            sourceId = "@" + t->name;
        } else {
            sourceId = t->id;
        }
        // if is array, need to get the element.
        if (g_sw->needLoad.get()) {
            g_sw->isCVal = false;
            // (1) on arrays.
            auto                vArr  = DPC(VArr, t);
            auto                cArr  = DPC(CArr, t);
            auto                fpVar = DPC(FPVar, t);
            std::vector<size_t> shape;
            std::vector<string> shape_string;
            bool                constShape = true;

            // Array 1 : deal with shape
            for (auto& e : context->exp()) {
                g_sw->needLLValLoad.dive(false);
                auto a = e->accept(this);
                g_sw->needLLValLoad.ascend();
                if (!g_sw->isCVal.get()) {
                    constShape = false;
                    shape_string.emplace_back(g_builder->getLastLabel());
                } else {
                    auto [_1, i, _2]   = Utils::parseCVal(ACS(CVal, a));
                    size_t thisDimSize = i;
                    shape.emplace_back(thisDimSize);
                    shape_string.emplace_back(std::to_string(thisDimSize));
                }
            }
            // the shape really match a terminal element on an array???
            // In sysylex, "const int[]" won't be passed by function args. so we needn't deal
            // with that in-ordinary thing.
            if (constShape) {
                // varr or carr
                if (vArr || cArr || (fpVar && fpVar->type == IRCtrl::IRValType::Arr)) {
                    if (cArr) {
                        // no need to check if you noob are accessing a const string.
                        vector<int> shape_(shape.begin(), shape.end());
                        g_sw->isCVal = true;
                        return cArr->access(shape_);
                    } else if (vArr) {
                        g_sw->isCVal = false;
                        // is terminal?
                        if (vArr->_shape.size() == shape.size()) {
                            // local varr / global varr (the same way.)
                            // get element ptr
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                vArr->getTrueAdvType(),
                                sourceId,
                                shape
                            );
                            gepSen->_retType = makeType(vArr->containedType);
                            g_builder->addSen(std::move(gepSen));
                            if (g_sw->needLLValLoad) return 2;
                            auto gepLabel = g_builder->getLastLabel();
                            // load from ptr
                            auto loadSen = MU<LoadSen>(
                                g_builder->getNewLabel(),
                                makeType(vArr->containedType),
                                gepLabel
                            );
                            g_builder->addSen(std::move(loadSen));
                            return 0;
                        }
                        // not the terminal node. No way to assign here.
                        else {
                            g_sw->isCVal = false;
                            if (shape.empty()) {
                                auto gepSen = MU<GepSen>(
                                    g_builder->getNewLabel(),
                                    vArr->getTrueAdvType(),
                                    sourceId,
                                    std::vector<size_t>{0}
                                );
                                gepSen->_retType = makeType(vArr->containedType);
                                auto gepLabel    = g_builder->getLastLabel();
                                g_builder->addSen(std::move(gepSen));
                                g_sw->isCVal = false;
                                return 0;
                            }
                            // get element ptr
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                vArr->getTrueAdvType(),
                                sourceId,
                                shape
                            );
                            gepSen->_retType = makeType(vArr->containedType);
                            auto gepLabel    = g_builder->getLastLabel();
                            g_builder->addSen(std::move(gepSen));

                            auto newArrTypeTmp =
                                MS<ArrayType>(*DPC(ArrayType, vArr->getTrueAdvType()));
                            auto n2 = std::deque<int>(
                                newArrTypeTmp->innerShape.begin(), newArrTypeTmp->innerShape.end()
                            );
                            for (auto i = 0; i < shape.size(); i++) n2.pop_front();
                            newArrTypeTmp->innerShape = vector<size_t>(n2.begin(), n2.end());

                            auto gepSen2 = MU<GepSen>(
                                g_builder->getNewLabel(),
                                newArrTypeTmp,
                                gepLabel,
                                vector<size_t>{0}
                            );
                            gepSen2->_retType = makeType(vArr->containedType);
                            auto gepLabel2    = g_builder->getLastLabel();
                            g_builder->addSen(std::move(gepSen2));

                            g_sw->isCVal = false;
                            return 0;
                        }
                    }   // on fpvar array.
                    else if (fpVar && fpVar->type == IRCtrl::IRValType::Arr) {
                        auto fpArrType = DPC(ArrayType, fpVar->fpType);
                        // terminal node, directly to the ass.
                        if (fpArrType->innerShape.size() == shape.size()) {
                            g_sw->isCVal = false;
                            // 2 steps load like this
                            /*
                             *  %v3 = load [2 x i32]*, [2 x i32]** %v1
                                %v4 = getelementptr [2 x i32], [2 x i32]* %v3, i32 4, i32 1
                                %v5 = load i32, i32* %v4
                             */
                            auto loadSen1 =
                                MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id);
                            g_builder->addSen(std::move(loadSen1));
                            auto s1Label = g_builder->getLastLabel();

                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(), fpArrType, s1Label, shape, true
                            );
                            g_builder->addSen(std::move(gepSen));
                            auto s2Label = g_builder->getLastLabel();

                            if (g_sw->needLLValLoad) return 2;

                            auto loadSen = MU<LoadSen>(g_builder->getNewLabel(), g_builder->getLastSen()->_retType, s2Label
                            );
                            g_builder->addSen(std::move(loadSen));
                            return 0;
                        }
                        // not the terminal... fuck!!!!!
                        else {
                            // 0. no shape requested, just load and return.
                            if (shape.empty()) {
                                auto loadSen1 = MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id
                                );
                                g_builder->addSen(std::move(loadSen1));
                                g_sw->isCVal = false;
                                return 0;
                            }

                            // 1. the same way load from alloca.
                            // %v3 = load [8 x i32]*, [8 x i32]** %v1
                            auto loadSen1 =
                                MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id);
                            g_builder->addSen(std::move(loadSen1));
                            auto s1Label = g_builder->getLastLabel();

                            // 2. gep the var but not completely.
                            // %v4 = getelementptr [8 x i32], [8 x i32]* %v3, i32 1
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(), fpArrType, s1Label, shape, true
                            );
                            g_builder->addSen(std::move(gepSen));
                            auto s2Label = g_builder->getLastLabel();

                            // 3. another gep, but pass 0,0
                            // %v5 = getelementptr [8 x i32], [8 x i32]* %v4, i32 0, i32 0
                            auto gepSen2 = MU<GepSen>(
                                g_builder->getNewLabel(),
                                fpArrType,
                                s2Label,
                                vector<size_t>({0, 0}),
                                true
                            );
                            g_builder->addSen(std::move(gepSen2));
                            auto s3Label = g_builder->getLastLabel();

                            g_sw->isCVal = false;
                            return 0;
                        }
                    }
                }
                // else on single variable.
                else {
                    if (g_sw->needLLValLoad) {
                        g_sw->isCVal = false;
                        return t;
                    }
                    unique_ptr<LocalSen> s = MU<LoadSen>(g_builder->getNewLabel(), t->getTrueAdvType(), sourceId
                    );
                    g_builder->addSen(std::move(s));
                }
            }
            // need load shape info from memory.
            else {
                // shape is not a const...
                // varr or carr
                if (vArr || cArr || (fpVar && fpVar->type == IRCtrl::IRValType::Arr)) {
                    if (cArr) {
                        // local varr / global varr (the same way.)
                        // get element ptr
                        auto gepSen = MU<GepSen>(
                            g_builder->getNewLabel(),
                            cArr->getTrueAdvType(),
                            sourceId,
                            shape_string
                        );
                        gepSen->_retType = makeType(cArr->containedType);
                        auto gepLabel    = g_builder->getLastLabel();
                        // load from ptr
                        auto loadSen = MU<LoadSen>(
                            g_builder->getNewLabel(),
                            makeType(cArr->containedType),
                            gepLabel
                        );
                        g_builder->addSen(std::move(gepSen));
                        g_builder->addSen(std::move(loadSen));
                        g_sw->isCVal = false;
                        return 0;
                    } else if (vArr) {
                        g_sw->isCVal = false;
                        // check terminal?
                        if (vArr->_shape.size() == shape_string.size()) {
                            // local varr / global varr (the same way.)
                            // get element ptr
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                vArr->getTrueAdvType(),
                                sourceId,
                                shape_string
                            );
                            gepSen->_retType = makeType(vArr->containedType);
                            g_builder->addSen(std::move(gepSen));
                            if (g_sw->needLLValLoad) return 2;
                            auto gepLabel = g_builder->getLastLabel();
                            // load from ptr
                            auto loadSen = MU<LoadSen>(
                                g_builder->getNewLabel(),
                                makeType(vArr->containedType),
                                gepLabel
                            );
                            g_builder->addSen(std::move(loadSen));
                            g_sw->isCVal = false;
                            return 0;
                        }
                        // not the terminal node.
                        else {
                            if (shape_string.empty()) {
                                auto gepSen = MU<GepSen>(
                                    g_builder->getNewLabel(),
                                    vArr->getTrueAdvType(),
                                    sourceId,
                                    std::vector<size_t>{0}
                                );
                                gepSen->_retType = makeType(vArr->containedType);
                                auto gepLabel    = g_builder->getLastLabel();
                                g_builder->addSen(std::move(gepSen));
                                g_sw->isCVal = false;
                                return 0;
                            }
                            // get element ptr
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                vArr->getTrueAdvType(),
                                sourceId,
                                shape_string
                            );
                            gepSen->_retType = makeType(vArr->containedType);
                            auto gepLabel    = g_builder->getLastLabel();
                            g_builder->addSen(std::move(gepSen));

                            auto newArrTypeTmp =
                                MS<ArrayType>(*DPC(ArrayType, vArr->getTrueAdvType()));
                            auto n2 = std::deque<int>(
                                newArrTypeTmp->innerShape.begin(), newArrTypeTmp->innerShape.end()
                            );
                            for (int i = 0; i < shape_string.size(); i++) n2.pop_front();
                            newArrTypeTmp->innerShape = vector<size_t>(n2.begin(), n2.end());

                            auto gepSen2 = MU<GepSen>(
                                g_builder->getNewLabel(),
                                newArrTypeTmp,
                                gepLabel,
                                vector<size_t>{0}
                            );
                            gepSen2->_retType = makeType(vArr->containedType);
                            auto gepLabel2    = g_builder->getLastLabel();
                            g_builder->addSen(std::move(gepSen2));

                            g_sw->isCVal = false;
                            return 0;
                        }
                    }   // on fpvar array.
                    else if (fpVar && fpVar->type == IRCtrl::IRValType::Arr) {
                        auto fpArrType = DPC(ArrayType, fpVar->fpType);
                        // terminal node, directly to the ass.
                        if (fpArrType->innerShape.size() == shape_string.size()) {
                            // 2 steps load like this
                            /*
                             *  %v3 = load [2 x i32]*, [2 x i32]** %v1
                                %v4 = getelementptr [2 x i32], [2 x i32]* %v3, i32 4, i32 1
                                %v5 = load i32, i32* %v4
                             */
                            auto loadSen1 =
                                MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id);
                            g_builder->addSen(std::move(loadSen1));
                            auto s1Label = g_builder->getLastLabel();

                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                fpArrType,
                                s1Label,
                                shape_string,
                                true
                            );
                            g_builder->addSen(std::move(gepSen));
                            auto s2Label = g_builder->getLastLabel();

                            if (g_sw->needLLValLoad) return 2;

                            auto loadSen = MU<LoadSen>(g_builder->getNewLabel(), g_builder->getLastSen()->_retType, s2Label
                            );
                            g_builder->addSen(std::move(loadSen));
                            g_sw->isCVal = false;
                            return 0;
                        }
                        // not the terminal... fuck!!!!!
                        else {
                            // 0. no shape requested, just load and return.
                            if (shape_string.empty()) {
                                auto loadSen1 = MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id
                                );
                                g_builder->addSen(std::move(loadSen1));
                                g_sw->isCVal = false;
                                return 0;
                            }

                            // 1. the same way load from alloca.
                            // %v3 = load [8 x i32]*, [8 x i32]** %v1
                            auto loadSen1 =
                                MU<LoadSen>(g_builder->getNewLabel(), fpArrType, fpVar->id);
                            g_builder->addSen(std::move(loadSen1));
                            auto s1Label = g_builder->getLastLabel();

                            // 2. gep the var but not completely.
                            // %v4 = getelementptr [8 x i32], [8 x i32]* %v3, i32 1
                            auto gepSen = MU<GepSen>(
                                g_builder->getNewLabel(),
                                fpArrType,
                                s1Label,
                                shape_string,
                                true
                            );
                            g_builder->addSen(std::move(gepSen));
                            auto s2Label = g_builder->getLastLabel();

                            // 3. another gep, but pass 0,0
                            // %v5 = getelementptr [8 x i32], [8 x i32]* %v4, i32 0, i32 0
                            auto gepSen2 = MU<GepSen>(
                                g_builder->getNewLabel(),
                                fpArrType,
                                s2Label,
                                vector<size_t>({0, 0}),
                                true
                            );
                            g_builder->addSen(std::move(gepSen2));
                            auto s3Label = g_builder->getLastLabel();

                            g_sw->isCVal = false;
                            return 0;
                        }
                    }
                }
                // else on single variable.
                else {
                    unique_ptr<LocalSen> s = MU<LoadSen>(g_builder->getNewLabel(), t->getTrueAdvType(), sourceId
                    );
                    g_builder->addSen(std::move(s));
                }
            }
        }
        return 0;
    }
    return 0;
}

/// primaryExp:
//	Lparen exp Rparen	# primaryExp_       <-----------
//	| lVal				# lValExpr
//	| number			# primaryExp_       <-----------
/// ATTENTION: THIS RULE HAS 2: exp and number!!!!!!!!
/// \param context
/// \return
std::any IRVisitor::visitPrimaryExp_(SysyParser::PrimaryExp_Context* context)
{
    if (context->exp()) {
        return context->exp()->accept(this);
    } else {
        return context->number()->accept(this);
    }
    return 0;
}
/// primaryExp:
//	Lparen exp Rparen	# primaryExp_
//	| lVal				# lValExpr      <-----------
/// \param context
/// \return
std::any IRVisitor::visitLValExpr(SysyParser::LValExprContext* context)
{
    if (IR_IS_CONST) {
        // if const, this func must return exact CVal
        return context->lVal()->accept(this);
    }
    // If in function:
    // Need Load, Not Const.
    if (g_sw->isInFunc.get()) {
        g_sw->needLoad.dive(true);
        g_sw->isConst.dive(false);
        auto ret = context->lVal()->accept(this);
        g_sw->isConst.ascend();
        g_sw->needLoad.ascend();
        g_sw->isCVal = false;
        return ret;
    } else {
        return context->lVal()->accept(this);
    }
}



/// A Const literal number
/// \param context
/// \return std::shared_ptr<CVal>
std::any IRVisitor::visitNumber(SysyParser::NumberContext* context)
{
    std::string num;
    g_sw->isCVal.set(true);
    if (context->intConst()) {
        auto x                        = context->intConst()->accept(this);
        num                           = std::any_cast<std::string>(x);
        int                   trueNum = Utils::tryParseInteger(num);
        std::shared_ptr<CVal> n       = std::make_shared<IntCVal>("", trueNum);
        n->isConst                    = g_sw->isConst.get();
        n->isGlobal                   = g_lc->isInGlobal();
        return n;
    } else {
        auto x = context->floatConst()->accept(this);
        num    = std::any_cast<std::string>(x);
        float trueNum;
        trueNum                 = std::strtof(num.c_str(), nullptr);
        std::shared_ptr<CVal> n = std::make_shared<FloatCVal>("", trueNum);
        n->isConst              = g_sw->isConst.get();
        n->isGlobal             = g_lc->isInGlobal();
        return n;
    }
}

/// **宏，老子需要特殊处理，还得搁着自行展开。
/// \param context
void IRVisitor::visitSysyTimerFunc(SysyParser::CallContext* context)
{
    auto lineno = context->getStart()->getLine();
    auto idName = context->Ident()->getText();
    if (idName == "starttime") {
        idName = "_sysy_starttime";
    } else {
        idName = "_sysy_stoptime";
    }
    vector<string> argNames{std::to_string(lineno)};
    auto           func = g_builder->getFunction(idName);
    // 这我**的都写完了，都万事大吉了，还想让老子改这*屎山？
    // 纯纯的**。
    string outLabel = func->_type.retType == IRValType::Void ? "" : g_builder->getNewLabel();
    auto   call =
        MU<CallSen>(outLabel, idName, func->_type.retType, func->_type.paramsType, argNames);
    g_builder->addSen(std::move(call));
    g_sw->isCVal = false;
}

/// Ident Lparen funcRParams? Rparen	# call
/// \param context
/// \return
std::any IRVisitor::visitCall(SysyParser::CallContext* context)
{
    string idName = context->Ident()->getText();
    // 对于starttime()和stoptime()两个**宏，老子需要特殊处理，还得搁着自行展开。
    // 赛事组就不能先把代码里的此等东西自行替换了？纯你妈**。**！
    if (idName == "starttime" || idName == "stoptime") {
        visitSysyTimerFunc(context);
        return 0;
    }
    auto func = g_builder->getFunction(idName);
    if (func == nullptr) { throw std::runtime_error("Function " + idName + " not found!"); }
    size_t nParams = 0;
    if (context->funcRParams() != nullptr) {
        nParams = context->funcRParams()->funcRParam().size();
    }
    // check params num
    if (func->getParamsNum() != nParams) {
        throw std::runtime_error("Function " + idName + " params num not match!");
    }
    size_t         pFuncParam = 0;
    vector<string> argNames;

    if (context->funcRParams() != nullptr) {
        for (auto fp : context->funcRParams()->funcRParam()) {
            //     ↓↓↓↓↓↓↓↓↓↓↓ ACCEPT ↓↓↓↓↓↓↓↓↓↓↓
            auto any_param = fp->exp()->accept(this);
            //     ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
            if (g_sw->isCVal) {
                auto argType = func->_type.paramsType[pFuncParam++];
                if (*argType != IRValType::Int && *argType != IRValType::Float) {
                    throw std::runtime_error("Function " + idName + " params type not match!");
                }
                auto cVal              = ACS(CVal, any_param);
                auto [pos, iVal, fVal] = Utils::parseCVal(cVal);
                if (*argType == IRValType::Int) {
                    argNames.emplace_back(std::to_string(iVal));
                } else if (*argType == IRValType::Float) {
                    argNames.emplace_back(Utils::floatTo64BitStr(fVal));
                }
            }
            // none cVal
            else {
                auto argType = func->_type.paramsType[pFuncParam++];   // IRType
                // two-way: array or not
                if (argType->type == IRValType::Arr) {
                    // no need to check type, just pass the value in argNames
                    // TODO: check array type
                    auto&  lastSen      = g_builder->getLastSen();
                    string lastSenLabel = lastSen->_label;
                    argNames.emplace_back(lastSenLabel);
                } else {
                    // need check type and do conversion
                    // last sentence must be LOAD, so we can get the type
                    auto&  lastSen      = g_builder->getLastSen();
                    string lastSenLabel = lastSen->_label;
                    if (*argType == IRValType::Int && *lastSen->_retType == IRValType::Float) {
                        // do conversion
                        g_builder->checkTypeAndCast(IRValType::Float, IRValType::Int, lastSenLabel);
                        lastSenLabel = g_builder->getLastLabel();
                    } else if (*argType == IRValType::Float && *lastSen->_retType == IRValType::Int) {
                        // do conversion
                        g_builder->checkTypeAndCast(IRValType::Int, IRValType::Float, lastSenLabel);
                        lastSenLabel = g_builder->getLastLabel();
                    }
                    // pass value.
                    argNames.emplace_back(lastSenLabel);
                }
            }
        }
    }
    //(string outLabel_, string funcName_, IRValType retType_, vector<SPType> argTypes,
    //            vector<string> argNames)
    string outLabel =
        func->_type.retType == IRValType::Void ? "" : g_builder->getNewLabel();
    auto call =
        MU<CallSen>(outLabel, idName, func->_type.retType, func->_type.paramsType, argNames);
    g_builder->addSen(std::move(call));
    g_sw->isCVal = false;
    return 0;
}


/// Ignored function
/// \param context
/// \return
std::any IRVisitor::visitStringConst(SysyParser::StringConstContext* context)
{
    return 0;
}

/// funcRParam: exp | stringConst;
/// \param context
/// \return exp.accept
std::any IRVisitor::visitFuncRParam(SysyParser::FuncRParamContext* context)
{
    // Here stringConst was ignored.
    // FINAL
    return context->exp()->accept(this);
}

/// funcRParams: funcRParam (Comma funcRParam)*;
//  note: funcRParam: exp
/// \param context
/// \return
std::any IRVisitor::visitFuncRParams(SysyParser::FuncRParamsContext* context)
{
    for (auto r : context->funcRParam()) { r->accept(this); }
    return 0;
}


std::any IRVisitor::visitDecIntConst(SysyParser::DecIntConstContext* context)
{
    // FINAL
    return context->DecIntConst()->getText();
}

std::any IRVisitor::visitOctIntConst(SysyParser::OctIntConstContext* context)
{
    // FINAL
    return context->OctIntConst()->getText();
}

std::any IRVisitor::visitHexIntConst(SysyParser::HexIntConstContext* context)
{
    // FINAL
    return context->HexIntConst()->getText();
}

std::any IRVisitor::visitDecFloatConst(SysyParser::DecFloatConstContext* context)
{
    // FINAL
    return context->DecFloatConst()->getText();
}

std::any IRVisitor::visitHexFloatConst(SysyParser::HexFloatConstContext* context)
{
    // FINAL
    return context->HexFloatConst()->getText();
}

// mulExp:
//	unaryExp				# mulExp_
std::any IRVisitor::visitMulExp_(SysyParser::MulExp_Context* context)
{
    // FINAL
    return context->unaryExp()->accept(this);
}

/// addExp:
///	mulExp				# addExp_
/// \param context
/// \return Returns what mulExp returns
std::any IRVisitor::visitAddExp_(SysyParser::AddExp_Context* context)
{
    // Actually it is mulExp
    // FINAL
    return context->mulExp()->accept(this);
}
