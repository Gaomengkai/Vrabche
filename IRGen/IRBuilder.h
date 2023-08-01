//
// Created by gao on 6/26/23.
//

#ifndef SYSYLEX_IRBUILDER_H
#define SYSYLEX_IRBUILDER_H


#include <cstdio>
#include <string>
#include <vector>
#include "IRLayerController.h"
#include "SysyParser.h"
#include "IRVal.h"
#include "IRProgram.h"


namespace IRCtrl
{
class IRBuilder
{
public:
    IRBuilder();

    explicit IRBuilder(const std::string& filename);
    void setFilename(const std::string& filename);

    // function
    void createFunction(IRCtrl::FuncType& type1, const string& name1);
    void finishFunction();
    // builder
    void        build(std::ostream& os);
    std::string build();
    SPBB addBB(const std::string& name);
    SPBB createBB();
    void        addSen(unique_ptr<LocalSen> sen);

    // label and sen getter
    int                                         getNewLabelInt();
    [[nodiscard]] int                           getLastLabelInt() const;
    string                                      getNewLabel();
    [[nodiscard]] string                        getLastLabel() const;
    [[nodiscard]] const unique_ptr<LocalSen>&   getLastSen() const;
    [[nodiscard]] const shared_ptr<IRFunction>& getFunction() const;
    shared_ptr<IRFunction>                      getFunction(const string& funcName);

    // bb
    int getNewBBLabelInt();
    string getNewBBLabel();
    void   moveToBB(SPBB bb);

    // tools
    void checkTypeAndCast(const SPType& from, const SPType& to, const string& from_name);
    /// Do a cast if type not eq or do nothing
    /// \param from source type
    /// \param to target type
    /// \param from_name source name
    void checkTypeAndCast(IRValType from, IRValType to, const string& from_name);


    // AddInstuctions into the builder.
    const unique_ptr<LocalSen>& addAdd(const SPType& t_, const string& v1, const string& v2);
    const unique_ptr<LocalSen>& addSub(const SPType& t_, const string& v1, const string& v2);
    const unique_ptr<LocalSen>& addMul(const SPType& t_, const string& v1, const string& v2);
    const unique_ptr<LocalSen>& addDiv(const SPType& t_, const string& v1, const string& v2);
    const unique_ptr<LocalSen>& addRem(const SPType& t_, const string& v1, const string& v2);

private:
    // Here stmts only means other stmt(other than function, var, const)
    std::vector<std::string>    _stmts;
    std::string                 _filename;
    int                         _label = -1;
    int _bb_label = 0; // starts at 0
    std::shared_ptr<IRProgram>  program;
    std::shared_ptr<IRFunction> thisFunction;
    const std::string localVarPrefix = "%v";
    const string bbPrefix = "L";

public:
    [[nodiscard]] const shared_ptr<IRProgram>& getProgram() const;


private:
    void _as(const std::string& s);
};
}   // namespace IRCtrl


#endif   // SYSYLEX_IRBUILDER_H
