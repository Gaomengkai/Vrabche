//
// Created by gao on 6/29/23.
//

#ifndef SYSYLEX_IRUTILS_H
#define SYSYLEX_IRUTILS_H

#include <string>
#include <stdexcept>
#include <memory>
#include "IRVal.h"
#include "IRSen.h"

namespace IRCtrl
{
class Utils
{
public:
    static int parseInteger(const std::string& str);

    static int tryParseInteger(const std::string& str);

    static std::shared_ptr<CVal>
    constBiCalc(const std::shared_ptr<CVal>& a, const std::shared_ptr<CVal>& b, IRValOp op);

    static std::shared_ptr<CArr>
    buildAnCArrFromInitList(const shared_ptr<InitListVal>& iList, const std::deque<size_t>& shape);

    static std::shared_ptr<VArr>
    buildAnVArrFromInitList(const shared_ptr<InitListVal>& iList, const std::deque<size_t>& shape);

    static string valTypeToStr(IRValType _t);
    static string icmpOpToStr(ICMPOp _op);
    static string fcmpOpToStr(FCMPOp _op);

    static string floatTo64BitStr(float x);

    static string localConstName(const string& functionName, const string& idName);

    /// parse a CVal to it's oringle like. first position is:
    /// 0=INVALID, 1=INT, 2=FLOAT
    /// \param cVal
    /// \return
    static std::tuple<size_t, int, float> parseCVal(const shared_ptr<CVal>& cVal);




private:
    template<class T1, class T2>
    static T1 T1OP(T1 v1, T2 v2, IRValOp op);

    template<class T1, class T2>
    T2 static T2OP(T1 v1, T2 v2, IRValOp op);

    template<class T1, class T2>
    static float FLOP(T1 v1, T2 v2, IRValOp op);

};

}   // namespace IRCtrl

#endif   // SYSYLEX_IRUTILS_H
