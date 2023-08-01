//
// Created by gao on 6/29/23.
//

#include "IRUtils.h"
#include "IRLogger.h"

namespace IRCtrl
{
int IRCtrl::Utils::parseInteger(const std::string& str)
{
    if (str.empty()) { throw std::invalid_argument("Empty string"); }

    size_t startPos = 0;
    int    base     = 10;

    if (str.size() > 2 && (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X")) {
        startPos = 2;
        base     = 16;
    } else if (str[0] == '0') {
        startPos = 1;
        base     = 8;
    }

    try {
        size_t pos = 0;
        int    num = std::stoi(str.substr(startPos), &pos, base);

        // Check Invalid Chars
        if (pos != str.size() - startPos) {
            throw std::invalid_argument("Invalid characters in the string");
        }

        return num;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Failed to parse the integer");
    }
}

int Utils::tryParseInteger(const std::string& str)
{
    int a = 0;
    try {
        a = parseInteger(str);
    } catch (const std::invalid_argument& e) {
        float f = std::strtof(str.c_str(), nullptr);
        a       = (int)f;
    }
    return a;
}


/// Do a calc between 2 literal/const number
/// \param a
/// \param b
/// \param op
/// \return
std::shared_ptr<CVal>
Utils::constBiCalc(const std::shared_ptr<CVal>& a, const std::shared_ptr<CVal>& b, IRValOp op)
{
    auto af         = std::dynamic_pointer_cast<FloatCVal>(a);
    auto ai         = std::dynamic_pointer_cast<IntCVal>(a);
    auto bf         = std::dynamic_pointer_cast<FloatCVal>(b);
    auto bi         = std::dynamic_pointer_cast<IntCVal>(b);
    bool isResFloat = false;
    isResFloat      = (af != nullptr) || (bf != nullptr);
    if (isResFloat) {
        auto  res = std::make_shared<FloatCVal>("");
        float _a, _b;
        if (af != nullptr)
            _a = af->fVal;
        else
            _a = (float)ai->iVal;
        if (bf != nullptr)
            _b = bf->fVal;
        else
            _b = (float)bi->iVal;
        res->fVal = FLOP(_a, _b, op);
        return res;
    } else {
        int _a, _b;
        _a        = ai->iVal;
        _b        = bi->iVal;
        auto res  = std::make_shared<IntCVal>("");
        res->iVal = T1OP(_a, _b, op);
        return res;
    }
}

/// Get access to a CArr
/// \param arr_
/// \param pos
/// \param shape
/// \return a l-value ref of CVal. use auto& to receive the return
inline shared_ptr<CVal>& getValInACArrRef(
    const shared_ptr<CArr>& arr_, const std::deque<size_t>& pos, const std::deque<size_t>& shape
)
{
    shared_ptr<CArr> arr = arr_;
    auto subArrShape     = shape;
    // init for first to last-1 dim. because last-1 is CVal not CArr.
    for (auto p = 0; p < pos.size() - 1; p++) {
        // init
        if (arr->_childArrs.empty()) {
            arr->_shape = subArrShape;
            for (auto i = 0; i < arr->_shape.front(); i++) {
                arr->witch.emplace_back(CArr::ZERO);
                arr->_childVals.emplace_back(nullptr);
                arr->_childArrs.emplace_back(nullptr);
            }
        }
        arr->isZero = false;
        // insert
        if (arr->_childArrs[pos[p]] == nullptr) {
            arr->_childArrs[pos[p]] = make_shared<CArr>("", arr->containedType);
        }
        arr->witch[pos[p]] = CArr::CARR;
        arr                = arr->_childArrs[pos[p]];   // attention
        subArrShape.pop_front();
    }
    // last layer (CVal)
    if (arr->_childArrs.empty()) {
        arr->_shape = subArrShape;
        for (auto i = 0; i < arr->_shape.back(); i++) {
            arr->witch.emplace_back(CArr::ZERO);
            arr->_childVals.emplace_back(nullptr);
            arr->_childArrs.emplace_back(nullptr);
        }
    }
    arr->isZero = false;
    if (arr->_childVals[pos.back()] == nullptr) {
        if (arr->containedType == IRValType::Int) {
            arr->_childVals[pos.back()] = make_shared<IntCVal>("");
        } else if (arr->containedType == IRValType::Float) {
            arr->_childVals[pos.back()] = make_shared<FloatCVal>("");
        }
    }
    arr->witch[pos.back()] = CArr::CVAL;
    return arr->_childVals[pos.back()];
}


/// According to shape, add N to cur.
/// \param shape [2][3]
/// \param cur [1][2]
/// \param N
/// \param startsAt
/// \param reset
void ArrayPosPlusN(
    const std::deque<size_t>& shape,
    std::deque<size_t>&       cur,
    size_t                    N,
    int                       startsAt = -1,
    bool                      reset    = true
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
shared_ptr<CVal> makeSureType(IRValType ty_, const shared_ptr<CVal>& val)
{
    if (val->type == ty_) {
        return val;
    } else {
        if (ty_ == IRValType::Int) {
            auto res  = make_shared<IntCVal>("");
            res->iVal = DPC(FloatCVal, val)->fVal;
            return res;
        } else if (ty_ == IRValType::Float) {
            auto res  = make_shared<FloatCVal>("");
            res->fVal = DPC(IntCVal, val)->iVal;
            return res;
        }
    }
    return nullptr;
}
struct CArrGenerator {
    std::shared_ptr<CArr>          arr;
    std::deque<size_t>             cur;
    std::deque<size_t>             shape;
    std::vector<size_t>            curShape;
    std::vector<size_t>            curArrayPos;
    const shared_ptr<InitListVal>& iList;
    size_t                         curArrayDim;

    CArrGenerator(
        const std::shared_ptr<CArr>&   arr_,
        const std::deque<size_t>&      shape_,
        const shared_ptr<InitListVal>& iList_
    )
        : arr(arr_)
        , cur(shape_.size(), 0)
        , shape(shape_)
        , iList(iList_)
        , curArrayDim(0)
    {
    }
    void gen() { gen(iList, cur, 0); }
    void gen(const shared_ptr<InitListVal>& val, std::deque<size_t> pos, size_t d)
    {
        auto pVal = 0, pArr = 0;
        for (auto i = 0; i < val->which.size(); i++) {
            if (val->which[i] == InitListVal::CVAL) {
                auto& c = getValInACArrRef(arr, pos, shape);
                //                c= val->cVal [pVal++];
                c = makeSureType(arr->containedType, val->cVal[pVal++]);
                ArrayPosPlusN(shape, pos, 1);
            } else {
                auto  before = pos[d];
                auto& il     = val->initList[pArr++];
                gen(il, pos, d + 1);
                if (before == pos[d]) ArrayPosPlusN(shape, pos, 1, d);
            }
        }
    }
};
/// Build a completely CArr from AST
/// \param iList
/// \return
std::shared_ptr<CArr> Utils::buildAnCArrFromInitList(
    const shared_ptr<InitListVal>& iList, const std::deque<size_t>& shape
)
{
    auto rr    = make_shared<CArr>("", iList->contained);
    rr->_shape = shape;
    rr->isZero = true;
    auto g     = CArrGenerator(rr, shape, iList);
    g.gen();
    rr->advancedType = MS<ArrayType>(rr->containedType, vector<size_t>(shape.begin(), shape.end()));
    return g.arr;
}
std::shared_ptr<VArr> Utils::buildAnVArrFromInitList(
    const shared_ptr<InitListVal>& iList, const std::deque<size_t>& shape
)
{
    auto c = buildAnCArrFromInitList(iList, shape);
    auto r = make_shared<VArr>(*c);
    return r;
}
string Utils::valTypeToStr(IRValType _t)
{
    switch (_t) {

    case IRValType::Func: return "function";
    case IRValType::Int: return "i32";
    case IRValType::Float: return "float";
    case IRValType::Arr: return "";
    case IRValType::Void: return "void";
    case IRValType::Pointer:
    case IRValType::FloatArr:
    case IRValType::IntArr: return "";
    case IRValType::Bool: return "i1";
    case IRValType::Unknown: return "ERROR";
    }
    RUNTIME_ERROR("Unknown IRValType"<<(int)_t);
}

string Utils::floatTo64BitStr(float x)
{
    stringstream ss;
    //    ss<<"0x"<<std::hex<<reinterpret_cast<uint32_t>(this->fVal);
    // Method above was not allowed
    // In LLVM-IR, a float is 64 bit.
    double thisValue = x;
    ss << "0x" << std::hex << *(uint64_t*)(&thisValue);
    return ss.str();
}

std::tuple<size_t, int, float> Utils::parseCVal(const shared_ptr<CVal>& cVal)
{
    float  fInit    = 0;
    int    iInit    = 0;
    size_t position = 0;
    auto   fValInit = std::dynamic_pointer_cast<FloatCVal>(cVal);
    auto   iValInit = std::dynamic_pointer_cast<IntCVal>(cVal);
    if (fValInit != nullptr) {
        fInit    = fValInit->fVal;
        iInit    = (int)fInit;
        position = 1;
    } else if (iValInit != nullptr) {
        iInit    = iValInit->iVal;
        fInit    = (float)iInit;
        position = 2;
    }

    return {position, iInit, fInit};
}
string Utils::localConstName(const string& functionName, const string& idName)
{
    static int id = 0;
    return "__const."+std::to_string(id++)+"." + functionName + "." + idName;
}

/// \brief Get string representation of a icmp operator
/// \param _op
/// \return Just as you expected
string Utils::icmpOpToStr(ICMPOp _op)
{
    // enum class ICMPOp {EQ, NE, UGT, UGE, ULT, ULE, SGT, SGE, SLT, SLE};
    switch (_op) {
        case ICMPOp::EQ: return "eq";
        case ICMPOp::NE: return "ne";
        case ICMPOp::UGT: return "ugt";
        case ICMPOp::UGE: return "uge";
        case ICMPOp::ULT: return "ult";
        case ICMPOp::ULE: return "ule";
        case ICMPOp::SGT: return "sgt";
        case ICMPOp::SGE: return "sge";
        case ICMPOp::SLT: return "slt";
        case ICMPOp::SLE: return "sle";
    }
    throw std::runtime_error("Unknown icmp operator");
}

/// enum class FCMPOp { False, OEQ, OGT, OGE, OLT, OLE, ONE, ORD, UEQ, UGT, UGE, ULT, ULE, UNE, UNO, True };
/// \param _op
/// \return Just as you expected
string Utils::fcmpOpToStr(FCMPOp _op)
{
    switch (_op) {
        case FCMPOp::False: return "false";
        case FCMPOp::OEQ: return "oeq";
        case FCMPOp::OGT: return "ogt";
        case FCMPOp::OGE: return "oge";
        case FCMPOp::OLT: return "olt";
        case FCMPOp::OLE: return "ole";
        case FCMPOp::ONE: return "one";
        case FCMPOp::ORD: return "ord";
        case FCMPOp::UEQ: return "ueq";
        case FCMPOp::UGT: return "ugt";
        case FCMPOp::UGE: return "uge";
        case FCMPOp::ULT: return "ult";
        case FCMPOp::ULE: return "ule";
        case FCMPOp::UNE: return "une";
        case FCMPOp::UNO: return "uno";
        case FCMPOp::True: return "true";
    }
    RUNTIME_ERROR("Unknown fcmp operator"<<(int)_op);
}


template<class T1, class T2>
T1 Utils::T1OP(T1 v1, T2 v2, IRValOp op)
{
    switch (op) {
    case IRValOp::Add: return (T1)v1 + v2;
    case IRValOp::Sub: return (T1)v1 - v2;
    case IRValOp::Mul: return (T1)v1 * v2;
    case IRValOp::Div: return (T1)v1 / v2;
    case IRValOp::Rem: return (T1)v1 % v2;
    }
    return 0;
}
template<class T1, class T2>
T2 Utils::T2OP(T1 v1, T2 v2, IRValOp op)
{
    switch (op) {
    case IRValOp::Add: return (T2)v1 + v2;
    case IRValOp::Sub: return (T2)v1 - v2;
    case IRValOp::Mul: return (T2)v1 * v2;
    case IRValOp::Div: return (T2)v1 / v2;
    case IRValOp::Rem: return (T2)v1 % v2;
    }
    return 0;
}
template<class T1, class T2>
float Utils::FLOP(T1 v1, T2 v2, IRValOp op)
{
    switch (op) {
    case IRValOp::Add: return (float)v1 + v2;
    case IRValOp::Sub: return (float)v1 - v2;
    case IRValOp::Mul: return (float)v1 * v2;
    case IRValOp::Div: return (float)v1 / v2;
    case IRValOp::Rem: throw std::invalid_argument("float cannot %");
    }
    return 0;
}
}   // namespace IRCtrl