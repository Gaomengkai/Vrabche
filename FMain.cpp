/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

//
//  main.cpp
//  antlr4-cpp-demo
//
//  Created by Mike Lischke on 13.03.16.
//

#include <fstream>
#include <iostream>
#include <ostream>

#include "SysyLexer.h"
#include "SysyParser.h"
#include "SysyVisitor.h"
#include "antlr4-runtime.h"
#include "tree/ParseTree.h"
#include "IRLogger.h"
#include "IRGlobal.h"
#include "LLVMIRLexer.h"
#include "LLVMIRParser.h"
#include "LLVMIRVisitor.h"
#include "antlr4-runtime.h"
#include "tree/AbstractParseTreeVisitor.h"
#include "tree/ParseTree.h"

#include "R5Logger.h"
#include "IROptimizer.h"
#include "R5IREmitter.h"
#include "GenIRAST.h"
using namespace antlrcpp;
using namespace antlr4;
using std::cout;
using std::endl;
using tree::ErrorNode;
using tree::ParseTree;
using tree::TerminalNode;

using namespace MiddleIR;
using MiddleIR::Optimizer::IROptimizer;

void RISC_V_Backend(std::istream& in, std::ostream& out)
{
    // parse IR AST
    ANTLRInputStream  input(in);
    LLVMIRLexer       lexer(&input);
    CommonTokenStream tokens(&lexer);
    LLVMIRParser      parser(&tokens);
    tree::ParseTree*  tree    = parser.compilationUnit();
    auto              visitor = new MiddleIR::GenIRAST;
    tree->accept(visitor);

    // Optimizer
    auto        irAST       = visitor->getAST();
    auto        SPCopiedAST = make_shared<MiddleIRAST>(irAST);
    uint64_t    opt         = IROptimizer::NONE_OPTIMIZATION;
    IROptimizer optimizer(SPCopiedAST, static_cast<IROptimizer::ENABLED_OPT>(opt));
    optimizer.run();

    // Emitter
    auto emitter = new R5Emitter::R5IREmitter(SPCopiedAST);
    emitter->build(out);
}

void frontEnd(std::istream& in, std::ostream& out, string filename = "")
{
    ANTLRInputStream  f_input(in);
    SysyLexer         f_lexer(&f_input);
    CommonTokenStream f_tokens(&f_lexer);

    SysyParser                   f_parser(&f_tokens);
    SysyParser::CompUnitContext* f_tree = f_parser.compUnit();

    auto irVisitor = IRVisitor();
    f_tree->accept(&irVisitor);

    IRCtrl::g_builder->setFilename(filename);
    IRCtrl::g_builder->build(out);
}

int main(int argc, const char** argv)
{
    std::string  inputFileName;
    std::string  outputFileName;
    std::string  optimizationLevel;
    stringstream irStream;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-o") {
            if (i + 1 < argc) {
                outputFileName = argv[i + 1];
                ++i;
            } else {
                std::cerr << "No output filename" << std::endl;
                return 1;
            }
        } else if (arg == "-O2" || arg == "-O1" || arg == "-O0") {
            optimizationLevel = arg;
        } else if (arg == "-S") {
            // do nothing
        } else if (arg == "-arm") {
            IRCtrl::IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC = true;
        } else if (arg == "-dso") {
            IRCtrl::IR_SWITCH_ENABLE_DSO_LOCAL = true;
        } else {
            inputFileName = arg;
        }
    }
    if (!inputFileName.empty()) { LOGD("f_input: " << inputFileName); }

    // 处理缺省参数
    if (inputFileName.empty()) { inputFileName = "../testsrc/1.c"; }
    if (outputFileName.empty()) { outputFileName = "../testsrc/1.txt"; }
    std::ifstream inputStream;
    std::ofstream outputStream;

    auto sourceFileName = inputFileName;

    outputStream.open(outputFileName, std::ios::out);
    inputStream.open(sourceFileName, std::ios::in);
    if (!inputStream) {
        cout << "no such inputStream" << endl;
        return 0;
    }
    LOGD("File Fine." << inputFileName);
    // ----------------------命令行参数解析结束-----------------------

    // -------------------------前端--------------------------------
    frontEnd(inputStream, irStream, inputFileName);

    // ---------------前端结果输出到了irStream中----------------------

    // -------------------------后端--------------------------------

    RISC_V_Backend(irStream, outputStream);

    // ------------------后端输出到outputStream----------------------

    outputStream.close();
    return 0;
}
