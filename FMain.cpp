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

std::string optimizationLevel;

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
    auto     irAST       = visitor->getAST();
    auto     SPCopiedAST = make_shared<MiddleIRAST>(irAST);
    uint64_t opt;
    if (!optimizationLevel.empty()) {
        opt = IROptimizer::ALL;
    } else
        opt = IROptimizer::O0;
    if (optimizationLevel == "-Otest") { opt = IROptimizer::ALL ^ IROptimizer::OPT_CP; }
    IROptimizer optimizer(SPCopiedAST, static_cast<IROptimizer::ENABLED_OPT>(opt));
    optimizer.run();

    // Emitter
    auto emitter = new R5Emitter::R5IREmitter(SPCopiedAST);
    emitter->build(out);
}

void frontEnd(std::istream& in, std::ostream& out, const string& filename = "")
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
void welcome()
{
    auto s = R"(                                                          
                                      ,                   
`7MM"""Yp,                     ,dMMMP'                    
  MM    Yb                    dP                          
  MM    dP `7MMpdMAo.  ,6"Yb. M,dW"Wb.`7MMF'`7MMF'.gP"Ya  
  MM"""bg.   MM   `Wb 8)   MM MW'   `Wb MM    MM ,M'   Yb 
  MM    `Y   MM    M8  ,pm9MM MM     M8 ``=.='MM 8M"""""" 
  MM    ,9   MM   ,AP 8M   MM YA.   ,A9       MM YM.    , 
.JMMmmmd9    MMbmmd'  `Moo9^Yo.`Ybmd9'      .JMML.`Mbmmd' 
             MM                                           
           .JMML.                                         )";
    cout << s << endl;
}

void help(const string& filename = "./compiler")
{
    cout << "Usage: " << filename << " [options] <input file>" << endl;
    cout << "Options:" << endl;
    cout << "  -o <output file>  Specify output filename" << endl;
    cout << "  -O0               Disable optimization" << endl;
    cout << "  -O1               Enable optimization level 1" << endl;
    cout << "  -O2               Enable optimization level 2" << endl;
    cout << "  -S                Emit LLVM-IR instead of RISC-V assembly" << endl;
    cout << "  -arm              Enable ARM AAPCS-VFPCC calling convention" << endl;
    cout << "  -dso              Enable DSO local" << endl;
    cout << "  -debug            Enable debug log" << endl;
    cout << "  -save-llvm <file> Save LLVM-IR to file" << endl;
    cout << "  -h, --help        Show this help message" << endl;
    exit(0);
}

int main(int argc, const char** argv)
{
    std::string  inputFileName;
    std::string  outputFileName;
    stringstream irStream;
    std::string  llvmIRFileName;
    bool         emitLLVMIR = false;
    g_log_level             = MiddleIR::LOG_LEVEL_WARNING;
    welcome();
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
        } else if (arg == "-O2" || arg == "-O1" || arg == "-O0" || arg == "-Otest") {
            optimizationLevel = arg;
        } else if (arg == "-S") {
            // do nothing
        } else if (arg == "-arm") {
            IRCtrl::IR_SWITCH_ENABLE_ARM_AAPCS_VFPCC = true;
        } else if (arg == "-dso") {
            IRCtrl::IR_SWITCH_ENABLE_DSO_LOCAL = true;
        } else if (arg == "-debug") {
            g_log_level = MiddleIR::LOG_LEVEL_DEBUG;
        } else if (arg == "-save-llvm") {
            if (i + 1 < argc) {
                llvmIRFileName = argv[i + 1];
                emitLLVMIR     = true;
                ++i;
            } else {
                LOGE("No LLVM-IR output filename" << std::endl);
                return 1;
            }
        } else if (arg == "-h" || arg == "--help") {
            help(argv[0]);
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
    if (emitLLVMIR) {
        std::ofstream llvmIROutputStream;
        llvmIROutputStream.open(llvmIRFileName, std::ios::out);
        if (!llvmIROutputStream) {
            LOGE("no such llvmIROutputStream" << endl);
            return 1;
        }
        llvmIROutputStream << irStream.str();
        llvmIROutputStream.close();
    }
    // -------------------------后端--------------------------------

    RISC_V_Backend(irStream, outputStream);

    // ------------------后端输出到outputStream----------------------
    cout << "Well done." << endl;
    outputStream.close();
    return 0;
}
