
// Generated from LLVMIR.g4 by ANTLR 4.13.0


#include "LLVMIRListener.h"
#include "LLVMIRVisitor.h"

#include "LLVMIRParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace
{

struct LLVMIRParserStaticData final {
    LLVMIRParserStaticData(
        std::vector<std::string> ruleNames,
        std::vector<std::string> literalNames,
        std::vector<std::string> symbolicNames
    )
        : ruleNames(std::move(ruleNames))
        , literalNames(std::move(literalNames))
        , symbolicNames(std::move(symbolicNames))
        , vocabulary(this->literalNames, this->symbolicNames)
    {
    }

    LLVMIRParserStaticData(const LLVMIRParserStaticData&)            = delete;
    LLVMIRParserStaticData(LLVMIRParserStaticData&&)                 = delete;
    LLVMIRParserStaticData& operator=(const LLVMIRParserStaticData&) = delete;
    LLVMIRParserStaticData& operator=(LLVMIRParserStaticData&&)      = delete;

    std::vector<antlr4::dfa::DFA>       decisionToDFA;
    antlr4::atn::PredictionContextCache sharedContextCache;
    const std::vector<std::string>      ruleNames;
    const std::vector<std::string>      literalNames;
    const std::vector<std::string>      symbolicNames;
    const antlr4::dfa::Vocabulary       vocabulary;
    antlr4::atn::SerializedATNView      serializedATN;
    std::unique_ptr<antlr4::atn::ATN>   atn;
};

::antlr4::internal::OnceFlag llvmirParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
    LLVMIRParserStaticData* llvmirParserStaticData = nullptr;

void llvmirParserInitialize()
{
#if ANTLR4_USE_THREAD_LOCAL_CACHE
    if (llvmirParserStaticData != nullptr) { return; }
#else
    assert(llvmirParserStaticData == nullptr);
#endif
    auto staticData = std::make_unique<LLVMIRParserStaticData>(
        std::vector<std::string>{
            "compilationUnit",
            "topLevelEntity",
            "globalDecl",
            "globalDef",
            "immutable",
            "funcDecl",
            "funcDef",
            "funcHeader",
            "funcBody",
            "basicBlock",
            "instruction",
            "terminator",
            "localDefInst",
            "mathInstruction",
            "valueInstruction",
            "storeInst",
            "allocaInst",
            "loadInst",
            "getElementPtrInst",
            "bitCastInst",
            "zExtInst",
            "sExtInst",
            "siToFpInst",
            "fpToSiInst",
            "iCmpInst",
            "fCmpInst",
            "callInst",
            "retTerm",
            "brTerm",
            "condBrTerm",
            "floatType",
            "concreteType",
            "value",
            "constant",
            "boolConst",
            "intConst",
            "floatConst",
            "arrayConst",
            "type",
            "intType",
            "pointerType",
            "labelType",
            "arrayType",
            "namedType",
            "params",
            "param",
            "label",
            "iPred",
            "args",
            "arg",
            "zeroInitializerConst",
            "fPred"},
        std::vector<std::string>{
            "",
            "'='",
            "'constant'",
            "'global'",
            "'declare'",
            "'define'",
            "'('",
            "')'",
            "'{'",
            "'}'",
            "'add'",
            "','",
            "'fadd'",
            "'sub'",
            "'fsub'",
            "'mul'",
            "'fmul'",
            "'udiv'",
            "'sdiv'",
            "'fdiv'",
            "'urem'",
            "'srem'",
            "'frem'",
            "'store'",
            "'alloca'",
            "'load'",
            "'getelementptr'",
            "'bitcast'",
            "'to'",
            "'zext'",
            "'sext'",
            "'sitofp'",
            "'fptosi'",
            "'icmp'",
            "'fcmp'",
            "'call'",
            "'ret'",
            "'void'",
            "'br'",
            "'float'",
            "'true'",
            "'false'",
            "'['",
            "']'",
            "'*'",
            "'label'",
            "'x'",
            "'eq'",
            "'ne'",
            "'sge'",
            "'sgt'",
            "'sle'",
            "'slt'",
            "'uge'",
            "'ugt'",
            "'ule'",
            "'ult'",
            "'zeroinitializer'",
            "'oeq'",
            "'oge'",
            "'ogt'",
            "'ole'",
            "'olt'",
            "'one'",
            "'ord'",
            "'ueq'",
            "'une'",
            "'uno'"},
        std::vector<std::string>{"",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "",           "",
                                 "Comment",    "WhiteSpace",
                                 "IntLit",     "FloatLit",
                                 "StringLit",  "GlobalIdent",
                                 "LocalIdent", "LabelIdent",
                                 "IntType"}
    );
    static const int32_t serializedATNSegment[] = {
        4,   1,   76,  487, 2,   0,   7,   0,   2,   1,   7,   1,   2,   2,   7,   2,   2,   3,
        7,   3,   2,   4,   7,   4,   2,   5,   7,   5,   2,   6,   7,   6,   2,   7,   7,   7,
        2,   8,   7,   8,   2,   9,   7,   9,   2,   10,  7,   10,  2,   11,  7,   11,  2,   12,
        7,   12,  2,   13,  7,   13,  2,   14,  7,   14,  2,   15,  7,   15,  2,   16,  7,   16,
        2,   17,  7,   17,  2,   18,  7,   18,  2,   19,  7,   19,  2,   20,  7,   20,  2,   21,
        7,   21,  2,   22,  7,   22,  2,   23,  7,   23,  2,   24,  7,   24,  2,   25,  7,   25,
        2,   26,  7,   26,  2,   27,  7,   27,  2,   28,  7,   28,  2,   29,  7,   29,  2,   30,
        7,   30,  2,   31,  7,   31,  2,   32,  7,   32,  2,   33,  7,   33,  2,   34,  7,   34,
        2,   35,  7,   35,  2,   36,  7,   36,  2,   37,  7,   37,  2,   38,  7,   38,  2,   39,
        7,   39,  2,   40,  7,   40,  2,   41,  7,   41,  2,   42,  7,   42,  2,   43,  7,   43,
        2,   44,  7,   44,  2,   45,  7,   45,  2,   46,  7,   46,  2,   47,  7,   47,  2,   48,
        7,   48,  2,   49,  7,   49,  2,   50,  7,   50,  2,   51,  7,   51,  1,   0,   5,   0,
        106, 8,   0,   10,  0,   12,  0,   109, 9,   0,   1,   0,   1,   0,   1,   1,   1,   1,
        1,   1,   1,   1,   3,   1,   117, 8,   1,   1,   2,   1,   2,   1,   2,   1,   2,   1,
        2,   1,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   3,   1,   4,   1,   4,   1,
        5,   1,   5,   1,   5,   1,   6,   1,   6,   1,   6,   1,   6,   1,   7,   1,   7,   1,
        7,   1,   7,   1,   7,   1,   7,   1,   8,   1,   8,   4,   8,   147, 8,   8,   11,  8,
        12,  8,   148, 1,   8,   1,   8,   1,   9,   3,   9,   154, 8,   9,   1,   9,   5,   9,
        157, 8,   9,   10,  9,   12,  9,   160, 9,   9,   1,   9,   1,   9,   1,   10,  1,   10,
        1,   10,  3,   10,  167, 8,   10,  1,   11,  1,   11,  1,   11,  3,   11,  172, 8,   11,
        1,   12,  1,   12,  1,   12,  1,   12,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,  1,   13,
        1,   13,  1,   13,  1,   13,  1,   13,  3,   13,  250, 8,   13,  1,   14,  1,   14,  1,
        14,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,  1,   14,  1,
        14,  3,   14,  264, 8,   14,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,
        1,   15,  1,   16,  1,   16,  1,   16,  1,   16,  1,   16,  1,   16,  3,   16,  279, 8,
        16,  1,   17,  1,   17,  1,   17,  1,   17,  1,   17,  1,   17,  1,   18,  1,   18,  1,
        18,  1,   18,  1,   18,  1,   18,  1,   18,  1,   18,  1,   18,  5,   18,  296, 8,   18,
        10,  18,  12,  18,  299, 9,   18,  1,   19,  1,   19,  1,   19,  1,   19,  1,   19,  1,
        19,  1,   20,  1,   20,  1,   20,  1,   20,  1,   20,  1,   20,  1,   21,  1,   21,  1,
        21,  1,   21,  1,   21,  1,   21,  1,   22,  1,   22,  1,   22,  1,   22,  1,   22,  1,
        22,  1,   23,  1,   23,  1,   23,  1,   23,  1,   23,  1,   23,  1,   24,  1,   24,  1,
        24,  1,   24,  1,   24,  1,   24,  1,   24,  1,   25,  1,   25,  1,   25,  1,   25,  1,
        25,  1,   25,  1,   25,  1,   26,  1,   26,  1,   26,  1,   26,  1,   26,  1,   26,  1,
        26,  1,   27,  1,   27,  1,   27,  1,   27,  1,   27,  1,   27,  3,   27,  358, 8,   27,
        1,   28,  1,   28,  1,   28,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,
        1,   29,  1,   29,  1,   30,  1,   30,  1,   31,  1,   31,  1,   31,  1,   31,  1,   31,
        1,   31,  3,   31,  379, 8,   31,  1,   32,  1,   32,  1,   32,  3,   32,  384, 8,   32,
        1,   33,  1,   33,  1,   33,  1,   33,  1,   33,  3,   33,  391, 8,   33,  1,   34,  1,
        34,  1,   35,  1,   35,  1,   36,  1,   36,  1,   37,  1,   37,  1,   37,  1,   37,  1,
        37,  1,   37,  1,   37,  5,   37,  406, 8,   37,  10,  37,  12,  37,  409, 9,   37,  3,
        37,  411, 8,   37,  1,   37,  1,   37,  1,   38,  1,   38,  1,   38,  1,   38,  1,   38,
        1,   38,  1,   38,  3,   38,  422, 8,   38,  1,   38,  1,   38,  1,   38,  1,   38,  1,
        38,  1,   38,  1,   38,  5,   38,  431, 8,   38,  10,  38,  12,  38,  434, 9,   38,  1,
        39,  1,   39,  1,   40,  1,   40,  1,   40,  1,   41,  1,   41,  1,   42,  1,   42,  1,
        42,  1,   42,  1,   42,  1,   42,  1,   43,  1,   43,  1,   44,  1,   44,  1,   44,  5,
        44,  454, 8,   44,  10,  44,  12,  44,  457, 9,   44,  3,   44,  459, 8,   44,  1,   45,
        1,   45,  3,   45,  463, 8,   45,  1,   46,  1,   46,  1,   46,  1,   47,  1,   47,  1,
        48,  1,   48,  1,   48,  5,   48,  473, 8,   48,  10,  48,  12,  48,  476, 9,   48,  3,
        48,  478, 8,   48,  1,   49,  1,   49,  1,   49,  1,   50,  1,   50,  1,   51,  1,   51,
        1,   51,  0,   1,   76,  52,  0,   2,   4,   6,   8,   10,  12,  14,  16,  18,  20,  22,
        24,  26,  28,  30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,  52,  54,  56,  58,
        60,  62,  64,  66,  68,  70,  72,  74,  76,  78,  80,  82,  84,  86,  88,  90,  92,  94,
        96,  98,  100, 102, 0,   4,   1,   0,   2,   3,   1,   0,   40,  41,  1,   0,   47,  56,
        3,   0,   40,  41,  53,  56,  58,  67,  495, 0,   107, 1,   0,   0,   0,   2,   116, 1,
        0,   0,   0,   4,   118, 1,   0,   0,   0,   6,   123, 1,   0,   0,   0,   8,   129, 1,
        0,   0,   0,   10,  131, 1,   0,   0,   0,   12,  134, 1,   0,   0,   0,   14,  138, 1,
        0,   0,   0,   16,  144, 1,   0,   0,   0,   18,  153, 1,   0,   0,   0,   20,  166, 1,
        0,   0,   0,   22,  171, 1,   0,   0,   0,   24,  173, 1,   0,   0,   0,   26,  249, 1,
        0,   0,   0,   28,  263, 1,   0,   0,   0,   30,  265, 1,   0,   0,   0,   32,  272, 1,
        0,   0,   0,   34,  280, 1,   0,   0,   0,   36,  286, 1,   0,   0,   0,   38,  300, 1,
        0,   0,   0,   40,  306, 1,   0,   0,   0,   42,  312, 1,   0,   0,   0,   44,  318, 1,
        0,   0,   0,   46,  324, 1,   0,   0,   0,   48,  330, 1,   0,   0,   0,   50,  337, 1,
        0,   0,   0,   52,  344, 1,   0,   0,   0,   54,  357, 1,   0,   0,   0,   56,  359, 1,
        0,   0,   0,   58,  362, 1,   0,   0,   0,   60,  370, 1,   0,   0,   0,   62,  378, 1,
        0,   0,   0,   64,  383, 1,   0,   0,   0,   66,  390, 1,   0,   0,   0,   68,  392, 1,
        0,   0,   0,   70,  394, 1,   0,   0,   0,   72,  396, 1,   0,   0,   0,   74,  398, 1,
        0,   0,   0,   76,  421, 1,   0,   0,   0,   78,  435, 1,   0,   0,   0,   80,  437, 1,
        0,   0,   0,   82,  440, 1,   0,   0,   0,   84,  442, 1,   0,   0,   0,   86,  448, 1,
        0,   0,   0,   88,  458, 1,   0,   0,   0,   90,  460, 1,   0,   0,   0,   92,  464, 1,
        0,   0,   0,   94,  467, 1,   0,   0,   0,   96,  477, 1,   0,   0,   0,   98,  479, 1,
        0,   0,   0,   100, 482, 1,   0,   0,   0,   102, 484, 1,   0,   0,   0,   104, 106, 3,
        2,   1,   0,   105, 104, 1,   0,   0,   0,   106, 109, 1,   0,   0,   0,   107, 105, 1,
        0,   0,   0,   107, 108, 1,   0,   0,   0,   108, 110, 1,   0,   0,   0,   109, 107, 1,
        0,   0,   0,   110, 111, 5,   0,   0,   1,   111, 1,   1,   0,   0,   0,   112, 117, 3,
        4,   2,   0,   113, 117, 3,   6,   3,   0,   114, 117, 3,   10,  5,   0,   115, 117, 3,
        12,  6,   0,   116, 112, 1,   0,   0,   0,   116, 113, 1,   0,   0,   0,   116, 114, 1,
        0,   0,   0,   116, 115, 1,   0,   0,   0,   117, 3,   1,   0,   0,   0,   118, 119, 5,
        73,  0,   0,   119, 120, 5,   1,   0,   0,   120, 121, 3,   8,   4,   0,   121, 122, 3,
        76,  38,  0,   122, 5,   1,   0,   0,   0,   123, 124, 5,   73,  0,   0,   124, 125, 5,
        1,   0,   0,   125, 126, 3,   8,   4,   0,   126, 127, 3,   76,  38,  0,   127, 128, 3,
        66,  33,  0,   128, 7,   1,   0,   0,   0,   129, 130, 7,   0,   0,   0,   130, 9,   1,
        0,   0,   0,   131, 132, 5,   4,   0,   0,   132, 133, 3,   14,  7,   0,   133, 11,  1,
        0,   0,   0,   134, 135, 5,   5,   0,   0,   135, 136, 3,   14,  7,   0,   136, 137, 3,
        16,  8,   0,   137, 13,  1,   0,   0,   0,   138, 139, 3,   76,  38,  0,   139, 140, 5,
        73,  0,   0,   140, 141, 5,   6,   0,   0,   141, 142, 3,   88,  44,  0,   142, 143, 5,
        7,   0,   0,   143, 15,  1,   0,   0,   0,   144, 146, 5,   8,   0,   0,   145, 147, 3,
        18,  9,   0,   146, 145, 1,   0,   0,   0,   147, 148, 1,   0,   0,   0,   148, 146, 1,
        0,   0,   0,   148, 149, 1,   0,   0,   0,   149, 150, 1,   0,   0,   0,   150, 151, 5,
        9,   0,   0,   151, 17,  1,   0,   0,   0,   152, 154, 5,   75,  0,   0,   153, 152, 1,
        0,   0,   0,   153, 154, 1,   0,   0,   0,   154, 158, 1,   0,   0,   0,   155, 157, 3,
        20,  10,  0,   156, 155, 1,   0,   0,   0,   157, 160, 1,   0,   0,   0,   158, 156, 1,
        0,   0,   0,   158, 159, 1,   0,   0,   0,   159, 161, 1,   0,   0,   0,   160, 158, 1,
        0,   0,   0,   161, 162, 3,   22,  11,  0,   162, 19,  1,   0,   0,   0,   163, 167, 3,
        24,  12,  0,   164, 167, 3,   28,  14,  0,   165, 167, 3,   30,  15,  0,   166, 163, 1,
        0,   0,   0,   166, 164, 1,   0,   0,   0,   166, 165, 1,   0,   0,   0,   167, 21,  1,
        0,   0,   0,   168, 172, 3,   54,  27,  0,   169, 172, 3,   56,  28,  0,   170, 172, 3,
        58,  29,  0,   171, 168, 1,   0,   0,   0,   171, 169, 1,   0,   0,   0,   171, 170, 1,
        0,   0,   0,   172, 23,  1,   0,   0,   0,   173, 174, 5,   74,  0,   0,   174, 175, 5,
        1,   0,   0,   175, 176, 3,   28,  14,  0,   176, 25,  1,   0,   0,   0,   177, 178, 5,
        10,  0,   0,   178, 179, 3,   62,  31,  0,   179, 180, 3,   64,  32,  0,   180, 181, 5,
        11,  0,   0,   181, 182, 3,   64,  32,  0,   182, 250, 1,   0,   0,   0,   183, 184, 5,
        12,  0,   0,   184, 185, 3,   62,  31,  0,   185, 186, 3,   64,  32,  0,   186, 187, 5,
        11,  0,   0,   187, 188, 3,   64,  32,  0,   188, 250, 1,   0,   0,   0,   189, 190, 5,
        13,  0,   0,   190, 191, 3,   62,  31,  0,   191, 192, 3,   64,  32,  0,   192, 193, 5,
        11,  0,   0,   193, 194, 3,   64,  32,  0,   194, 250, 1,   0,   0,   0,   195, 196, 5,
        14,  0,   0,   196, 197, 3,   62,  31,  0,   197, 198, 3,   64,  32,  0,   198, 199, 5,
        11,  0,   0,   199, 200, 3,   64,  32,  0,   200, 250, 1,   0,   0,   0,   201, 202, 5,
        15,  0,   0,   202, 203, 3,   62,  31,  0,   203, 204, 3,   64,  32,  0,   204, 205, 5,
        11,  0,   0,   205, 206, 3,   64,  32,  0,   206, 250, 1,   0,   0,   0,   207, 208, 5,
        16,  0,   0,   208, 209, 3,   62,  31,  0,   209, 210, 3,   64,  32,  0,   210, 211, 5,
        11,  0,   0,   211, 212, 3,   64,  32,  0,   212, 250, 1,   0,   0,   0,   213, 214, 5,
        17,  0,   0,   214, 215, 3,   62,  31,  0,   215, 216, 3,   64,  32,  0,   216, 217, 5,
        11,  0,   0,   217, 218, 3,   64,  32,  0,   218, 250, 1,   0,   0,   0,   219, 220, 5,
        18,  0,   0,   220, 221, 3,   62,  31,  0,   221, 222, 3,   64,  32,  0,   222, 223, 5,
        11,  0,   0,   223, 224, 3,   64,  32,  0,   224, 250, 1,   0,   0,   0,   225, 226, 5,
        19,  0,   0,   226, 227, 3,   62,  31,  0,   227, 228, 3,   64,  32,  0,   228, 229, 5,
        11,  0,   0,   229, 230, 3,   64,  32,  0,   230, 250, 1,   0,   0,   0,   231, 232, 5,
        20,  0,   0,   232, 233, 3,   62,  31,  0,   233, 234, 3,   64,  32,  0,   234, 235, 5,
        11,  0,   0,   235, 236, 3,   64,  32,  0,   236, 250, 1,   0,   0,   0,   237, 238, 5,
        21,  0,   0,   238, 239, 3,   62,  31,  0,   239, 240, 3,   64,  32,  0,   240, 241, 5,
        11,  0,   0,   241, 242, 3,   64,  32,  0,   242, 250, 1,   0,   0,   0,   243, 244, 5,
        22,  0,   0,   244, 245, 3,   62,  31,  0,   245, 246, 3,   64,  32,  0,   246, 247, 5,
        11,  0,   0,   247, 248, 3,   64,  32,  0,   248, 250, 1,   0,   0,   0,   249, 177, 1,
        0,   0,   0,   249, 183, 1,   0,   0,   0,   249, 189, 1,   0,   0,   0,   249, 195, 1,
        0,   0,   0,   249, 201, 1,   0,   0,   0,   249, 207, 1,   0,   0,   0,   249, 213, 1,
        0,   0,   0,   249, 219, 1,   0,   0,   0,   249, 225, 1,   0,   0,   0,   249, 231, 1,
        0,   0,   0,   249, 237, 1,   0,   0,   0,   249, 243, 1,   0,   0,   0,   250, 27,  1,
        0,   0,   0,   251, 264, 3,   26,  13,  0,   252, 264, 3,   32,  16,  0,   253, 264, 3,
        34,  17,  0,   254, 264, 3,   36,  18,  0,   255, 264, 3,   40,  20,  0,   256, 264, 3,
        42,  21,  0,   257, 264, 3,   44,  22,  0,   258, 264, 3,   46,  23,  0,   259, 264, 3,
        38,  19,  0,   260, 264, 3,   48,  24,  0,   261, 264, 3,   50,  25,  0,   262, 264, 3,
        52,  26,  0,   263, 251, 1,   0,   0,   0,   263, 252, 1,   0,   0,   0,   263, 253, 1,
        0,   0,   0,   263, 254, 1,   0,   0,   0,   263, 255, 1,   0,   0,   0,   263, 256, 1,
        0,   0,   0,   263, 257, 1,   0,   0,   0,   263, 258, 1,   0,   0,   0,   263, 259, 1,
        0,   0,   0,   263, 260, 1,   0,   0,   0,   263, 261, 1,   0,   0,   0,   263, 262, 1,
        0,   0,   0,   264, 29,  1,   0,   0,   0,   265, 266, 5,   23,  0,   0,   266, 267, 3,
        62,  31,  0,   267, 268, 3,   64,  32,  0,   268, 269, 5,   11,  0,   0,   269, 270, 3,
        62,  31,  0,   270, 271, 3,   64,  32,  0,   271, 31,  1,   0,   0,   0,   272, 273, 5,
        24,  0,   0,   273, 278, 3,   76,  38,  0,   274, 275, 5,   11,  0,   0,   275, 276, 3,
        62,  31,  0,   276, 277, 3,   64,  32,  0,   277, 279, 1,   0,   0,   0,   278, 274, 1,
        0,   0,   0,   278, 279, 1,   0,   0,   0,   279, 33,  1,   0,   0,   0,   280, 281, 5,
        25,  0,   0,   281, 282, 3,   76,  38,  0,   282, 283, 5,   11,  0,   0,   283, 284, 3,
        62,  31,  0,   284, 285, 3,   64,  32,  0,   285, 35,  1,   0,   0,   0,   286, 287, 5,
        26,  0,   0,   287, 288, 3,   76,  38,  0,   288, 289, 5,   11,  0,   0,   289, 290, 3,
        62,  31,  0,   290, 297, 3,   64,  32,  0,   291, 292, 5,   11,  0,   0,   292, 293, 3,
        62,  31,  0,   293, 294, 3,   64,  32,  0,   294, 296, 1,   0,   0,   0,   295, 291, 1,
        0,   0,   0,   296, 299, 1,   0,   0,   0,   297, 295, 1,   0,   0,   0,   297, 298, 1,
        0,   0,   0,   298, 37,  1,   0,   0,   0,   299, 297, 1,   0,   0,   0,   300, 301, 5,
        27,  0,   0,   301, 302, 3,   62,  31,  0,   302, 303, 3,   64,  32,  0,   303, 304, 5,
        28,  0,   0,   304, 305, 3,   76,  38,  0,   305, 39,  1,   0,   0,   0,   306, 307, 5,
        29,  0,   0,   307, 308, 3,   62,  31,  0,   308, 309, 3,   64,  32,  0,   309, 310, 5,
        28,  0,   0,   310, 311, 3,   76,  38,  0,   311, 41,  1,   0,   0,   0,   312, 313, 5,
        30,  0,   0,   313, 314, 3,   62,  31,  0,   314, 315, 3,   64,  32,  0,   315, 316, 5,
        28,  0,   0,   316, 317, 3,   76,  38,  0,   317, 43,  1,   0,   0,   0,   318, 319, 5,
        31,  0,   0,   319, 320, 3,   62,  31,  0,   320, 321, 3,   64,  32,  0,   321, 322, 5,
        28,  0,   0,   322, 323, 3,   76,  38,  0,   323, 45,  1,   0,   0,   0,   324, 325, 5,
        32,  0,   0,   325, 326, 3,   62,  31,  0,   326, 327, 3,   64,  32,  0,   327, 328, 5,
        28,  0,   0,   328, 329, 3,   76,  38,  0,   329, 47,  1,   0,   0,   0,   330, 331, 5,
        33,  0,   0,   331, 332, 3,   94,  47,  0,   332, 333, 3,   62,  31,  0,   333, 334, 3,
        64,  32,  0,   334, 335, 5,   11,  0,   0,   335, 336, 3,   64,  32,  0,   336, 49,  1,
        0,   0,   0,   337, 338, 5,   34,  0,   0,   338, 339, 3,   102, 51,  0,   339, 340, 3,
        62,  31,  0,   340, 341, 3,   64,  32,  0,   341, 342, 5,   11,  0,   0,   342, 343, 3,
        64,  32,  0,   343, 51,  1,   0,   0,   0,   344, 345, 5,   35,  0,   0,   345, 346, 3,
        76,  38,  0,   346, 347, 3,   64,  32,  0,   347, 348, 5,   6,   0,   0,   348, 349, 3,
        96,  48,  0,   349, 350, 5,   7,   0,   0,   350, 53,  1,   0,   0,   0,   351, 352, 5,
        36,  0,   0,   352, 358, 5,   37,  0,   0,   353, 354, 5,   36,  0,   0,   354, 355, 3,
        62,  31,  0,   355, 356, 3,   64,  32,  0,   356, 358, 1,   0,   0,   0,   357, 351, 1,
        0,   0,   0,   357, 353, 1,   0,   0,   0,   358, 55,  1,   0,   0,   0,   359, 360, 5,
        38,  0,   0,   360, 361, 3,   92,  46,  0,   361, 57,  1,   0,   0,   0,   362, 363, 5,
        38,  0,   0,   363, 364, 5,   76,  0,   0,   364, 365, 3,   64,  32,  0,   365, 366, 5,
        11,  0,   0,   366, 367, 3,   92,  46,  0,   367, 368, 5,   11,  0,   0,   368, 369, 3,
        92,  46,  0,   369, 59,  1,   0,   0,   0,   370, 371, 5,   39,  0,   0,   371, 61,  1,
        0,   0,   0,   372, 379, 3,   78,  39,  0,   373, 379, 3,   60,  30,  0,   374, 379, 3,
        80,  40,  0,   375, 379, 3,   82,  41,  0,   376, 379, 3,   84,  42,  0,   377, 379, 3,
        86,  43,  0,   378, 372, 1,   0,   0,   0,   378, 373, 1,   0,   0,   0,   378, 374, 1,
        0,   0,   0,   378, 375, 1,   0,   0,   0,   378, 376, 1,   0,   0,   0,   378, 377, 1,
        0,   0,   0,   379, 63,  1,   0,   0,   0,   380, 384, 3,   66,  33,  0,   381, 384, 5,
        74,  0,   0,   382, 384, 5,   73,  0,   0,   383, 380, 1,   0,   0,   0,   383, 381, 1,
        0,   0,   0,   383, 382, 1,   0,   0,   0,   384, 65,  1,   0,   0,   0,   385, 391, 3,
        68,  34,  0,   386, 391, 3,   70,  35,  0,   387, 391, 3,   72,  36,  0,   388, 391, 3,
        74,  37,  0,   389, 391, 3,   100, 50,  0,   390, 385, 1,   0,   0,   0,   390, 386, 1,
        0,   0,   0,   390, 387, 1,   0,   0,   0,   390, 388, 1,   0,   0,   0,   390, 389, 1,
        0,   0,   0,   391, 67,  1,   0,   0,   0,   392, 393, 7,   1,   0,   0,   393, 69,  1,
        0,   0,   0,   394, 395, 5,   70,  0,   0,   395, 71,  1,   0,   0,   0,   396, 397, 5,
        71,  0,   0,   397, 73,  1,   0,   0,   0,   398, 410, 5,   42,  0,   0,   399, 400, 3,
        62,  31,  0,   400, 407, 3,   66,  33,  0,   401, 402, 5,   11,  0,   0,   402, 403, 3,
        62,  31,  0,   403, 404, 3,   66,  33,  0,   404, 406, 1,   0,   0,   0,   405, 401, 1,
        0,   0,   0,   406, 409, 1,   0,   0,   0,   407, 405, 1,   0,   0,   0,   407, 408, 1,
        0,   0,   0,   408, 411, 1,   0,   0,   0,   409, 407, 1,   0,   0,   0,   410, 399, 1,
        0,   0,   0,   410, 411, 1,   0,   0,   0,   411, 412, 1,   0,   0,   0,   412, 413, 5,
        43,  0,   0,   413, 75,  1,   0,   0,   0,   414, 415, 6,   38,  -1,  0,   415, 422, 5,
        37,  0,   0,   416, 422, 3,   78,  39,  0,   417, 422, 5,   39,  0,   0,   418, 422, 3,
        82,  41,  0,   419, 422, 3,   84,  42,  0,   420, 422, 3,   86,  43,  0,   421, 414, 1,
        0,   0,   0,   421, 416, 1,   0,   0,   0,   421, 417, 1,   0,   0,   0,   421, 418, 1,
        0,   0,   0,   421, 419, 1,   0,   0,   0,   421, 420, 1,   0,   0,   0,   422, 432, 1,
        0,   0,   0,   423, 424, 10,  7,   0,   0,   424, 425, 5,   6,   0,   0,   425, 426, 3,
        88,  44,  0,   426, 427, 5,   7,   0,   0,   427, 431, 1,   0,   0,   0,   428, 429, 10,
        2,   0,   0,   429, 431, 5,   44,  0,   0,   430, 423, 1,   0,   0,   0,   430, 428, 1,
        0,   0,   0,   431, 434, 1,   0,   0,   0,   432, 430, 1,   0,   0,   0,   432, 433, 1,
        0,   0,   0,   433, 77,  1,   0,   0,   0,   434, 432, 1,   0,   0,   0,   435, 436, 5,
        76,  0,   0,   436, 79,  1,   0,   0,   0,   437, 438, 3,   76,  38,  0,   438, 439, 5,
        44,  0,   0,   439, 81,  1,   0,   0,   0,   440, 441, 5,   45,  0,   0,   441, 83,  1,
        0,   0,   0,   442, 443, 5,   42,  0,   0,   443, 444, 5,   70,  0,   0,   444, 445, 5,
        46,  0,   0,   445, 446, 3,   76,  38,  0,   446, 447, 5,   43,  0,   0,   447, 85,  1,
        0,   0,   0,   448, 449, 5,   74,  0,   0,   449, 87,  1,   0,   0,   0,   450, 455, 3,
        90,  45,  0,   451, 452, 5,   11,  0,   0,   452, 454, 3,   90,  45,  0,   453, 451, 1,
        0,   0,   0,   454, 457, 1,   0,   0,   0,   455, 453, 1,   0,   0,   0,   455, 456, 1,
        0,   0,   0,   456, 459, 1,   0,   0,   0,   457, 455, 1,   0,   0,   0,   458, 450, 1,
        0,   0,   0,   458, 459, 1,   0,   0,   0,   459, 89,  1,   0,   0,   0,   460, 462, 3,
        76,  38,  0,   461, 463, 5,   74,  0,   0,   462, 461, 1,   0,   0,   0,   462, 463, 1,
        0,   0,   0,   463, 91,  1,   0,   0,   0,   464, 465, 5,   45,  0,   0,   465, 466, 5,
        74,  0,   0,   466, 93,  1,   0,   0,   0,   467, 468, 7,   2,   0,   0,   468, 95,  1,
        0,   0,   0,   469, 474, 3,   98,  49,  0,   470, 471, 5,   11,  0,   0,   471, 473, 3,
        98,  49,  0,   472, 470, 1,   0,   0,   0,   473, 476, 1,   0,   0,   0,   474, 472, 1,
        0,   0,   0,   474, 475, 1,   0,   0,   0,   475, 478, 1,   0,   0,   0,   476, 474, 1,
        0,   0,   0,   477, 469, 1,   0,   0,   0,   477, 478, 1,   0,   0,   0,   478, 97,  1,
        0,   0,   0,   479, 480, 3,   62,  31,  0,   480, 481, 3,   64,  32,  0,   481, 99,  1,
        0,   0,   0,   482, 483, 5,   57,  0,   0,   483, 101, 1,   0,   0,   0,   484, 485, 7,
        3,   0,   0,   485, 103, 1,   0,   0,   0,   25,  107, 116, 148, 153, 158, 166, 171, 249,
        263, 278, 297, 357, 378, 383, 390, 407, 410, 421, 430, 432, 455, 458, 462, 474, 477};
    staticData->serializedATN = antlr4::atn::SerializedATNView(
        serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0])
    );

    antlr4::atn::ATNDeserializer deserializer;
    staticData->atn = deserializer.deserialize(staticData->serializedATN);

    const size_t count = staticData->atn->getNumberOfDecisions();
    staticData->decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++) {
        staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
    }
    llvmirParserStaticData = staticData.release();
}

}   // namespace

LLVMIRParser::LLVMIRParser(TokenStream* input)
    : LLVMIRParser(input, antlr4::atn::ParserATNSimulatorOptions())
{
}

LLVMIRParser::LLVMIRParser(
    TokenStream* input, const antlr4::atn::ParserATNSimulatorOptions& options
)
    : Parser(input)
{
    LLVMIRParser::initialize();
    _interpreter = new atn::ParserATNSimulator(
        this,
        *llvmirParserStaticData->atn,
        llvmirParserStaticData->decisionToDFA,
        llvmirParserStaticData->sharedContextCache,
        options
    );
}

LLVMIRParser::~LLVMIRParser()
{
    delete _interpreter;
}

const atn::ATN& LLVMIRParser::getATN() const
{
    return *llvmirParserStaticData->atn;
}

std::string LLVMIRParser::getGrammarFileName() const
{
    return "LLVMIR.g4";
}

const std::vector<std::string>& LLVMIRParser::getRuleNames() const
{
    return llvmirParserStaticData->ruleNames;
}

const dfa::Vocabulary& LLVMIRParser::getVocabulary() const
{
    return llvmirParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LLVMIRParser::getSerializedATN() const
{
    return llvmirParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext
//------------------------------------------------------------------

LLVMIRParser::CompilationUnitContext::CompilationUnitContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::CompilationUnitContext::EOF()
{
    return getToken(LLVMIRParser::EOF, 0);
}

std::vector<LLVMIRParser::TopLevelEntityContext*>
LLVMIRParser::CompilationUnitContext::topLevelEntity()
{
    return getRuleContexts<LLVMIRParser::TopLevelEntityContext>();
}

LLVMIRParser::TopLevelEntityContext* LLVMIRParser::CompilationUnitContext::topLevelEntity(size_t i)
{
    return getRuleContext<LLVMIRParser::TopLevelEntityContext>(i);
}


size_t LLVMIRParser::CompilationUnitContext::getRuleIndex() const
{
    return LLVMIRParser::RuleCompilationUnit;
}

void LLVMIRParser::CompilationUnitContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCompilationUnit(this);
}

void LLVMIRParser::CompilationUnitContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCompilationUnit(this);
}


std::any LLVMIRParser::CompilationUnitContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitCompilationUnit(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::CompilationUnitContext* LLVMIRParser::compilationUnit()
{
    CompilationUnitContext* _localctx =
        _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
    enterRule(_localctx, 0, LLVMIRParser::RuleCompilationUnit);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(107);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == LLVMIRParser::T__3

               || _la == LLVMIRParser::T__4 || _la == LLVMIRParser::GlobalIdent) {
            setState(104);
            topLevelEntity();
            setState(109);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(110);
        match(LLVMIRParser::EOF);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TopLevelEntityContext
//------------------------------------------------------------------

LLVMIRParser::TopLevelEntityContext::TopLevelEntityContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::GlobalDeclContext* LLVMIRParser::TopLevelEntityContext::globalDecl()
{
    return getRuleContext<LLVMIRParser::GlobalDeclContext>(0);
}

LLVMIRParser::GlobalDefContext* LLVMIRParser::TopLevelEntityContext::globalDef()
{
    return getRuleContext<LLVMIRParser::GlobalDefContext>(0);
}

LLVMIRParser::FuncDeclContext* LLVMIRParser::TopLevelEntityContext::funcDecl()
{
    return getRuleContext<LLVMIRParser::FuncDeclContext>(0);
}

LLVMIRParser::FuncDefContext* LLVMIRParser::TopLevelEntityContext::funcDef()
{
    return getRuleContext<LLVMIRParser::FuncDefContext>(0);
}


size_t LLVMIRParser::TopLevelEntityContext::getRuleIndex() const
{
    return LLVMIRParser::RuleTopLevelEntity;
}

void LLVMIRParser::TopLevelEntityContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterTopLevelEntity(this);
}

void LLVMIRParser::TopLevelEntityContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitTopLevelEntity(this);
}


std::any LLVMIRParser::TopLevelEntityContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitTopLevelEntity(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::TopLevelEntityContext* LLVMIRParser::topLevelEntity()
{
    TopLevelEntityContext* _localctx =
        _tracker.createInstance<TopLevelEntityContext>(_ctx, getState());
    enterRule(_localctx, 2, LLVMIRParser::RuleTopLevelEntity);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(116);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
            enterOuterAlt(_localctx, 1);
            setState(112);
            globalDecl();
            break;
        }

        case 2: {
            enterOuterAlt(_localctx, 2);
            setState(113);
            globalDef();
            break;
        }

        case 3: {
            enterOuterAlt(_localctx, 3);
            setState(114);
            funcDecl();
            break;
        }

        case 4: {
            enterOuterAlt(_localctx, 4);
            setState(115);
            funcDef();
            break;
        }

        default: break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- GlobalDeclContext
//------------------------------------------------------------------

LLVMIRParser::GlobalDeclContext::GlobalDeclContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::GlobalDeclContext::GlobalIdent()
{
    return getToken(LLVMIRParser::GlobalIdent, 0);
}

LLVMIRParser::ImmutableContext* LLVMIRParser::GlobalDeclContext::immutable()
{
    return getRuleContext<LLVMIRParser::ImmutableContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::GlobalDeclContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::GlobalDeclContext::getRuleIndex() const
{
    return LLVMIRParser::RuleGlobalDecl;
}

void LLVMIRParser::GlobalDeclContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGlobalDecl(this);
}

void LLVMIRParser::GlobalDeclContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGlobalDecl(this);
}


std::any LLVMIRParser::GlobalDeclContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitGlobalDecl(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::GlobalDeclContext* LLVMIRParser::globalDecl()
{
    GlobalDeclContext* _localctx = _tracker.createInstance<GlobalDeclContext>(_ctx, getState());
    enterRule(_localctx, 4, LLVMIRParser::RuleGlobalDecl);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(118);
        match(LLVMIRParser::GlobalIdent);
        setState(119);
        match(LLVMIRParser::T__0);
        setState(120);
        immutable();
        setState(121);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- GlobalDefContext
//------------------------------------------------------------------

LLVMIRParser::GlobalDefContext::GlobalDefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::GlobalDefContext::GlobalIdent()
{
    return getToken(LLVMIRParser::GlobalIdent, 0);
}

LLVMIRParser::ImmutableContext* LLVMIRParser::GlobalDefContext::immutable()
{
    return getRuleContext<LLVMIRParser::ImmutableContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::GlobalDefContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

LLVMIRParser::ConstantContext* LLVMIRParser::GlobalDefContext::constant()
{
    return getRuleContext<LLVMIRParser::ConstantContext>(0);
}


size_t LLVMIRParser::GlobalDefContext::getRuleIndex() const
{
    return LLVMIRParser::RuleGlobalDef;
}

void LLVMIRParser::GlobalDefContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGlobalDef(this);
}

void LLVMIRParser::GlobalDefContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGlobalDef(this);
}


std::any LLVMIRParser::GlobalDefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitGlobalDef(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::GlobalDefContext* LLVMIRParser::globalDef()
{
    GlobalDefContext* _localctx = _tracker.createInstance<GlobalDefContext>(_ctx, getState());
    enterRule(_localctx, 6, LLVMIRParser::RuleGlobalDef);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(123);
        match(LLVMIRParser::GlobalIdent);
        setState(124);
        match(LLVMIRParser::T__0);
        setState(125);
        immutable();
        setState(126);
        type(0);
        setState(127);
        constant();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ImmutableContext
//------------------------------------------------------------------

LLVMIRParser::ImmutableContext::ImmutableContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::ImmutableContext::getRuleIndex() const
{
    return LLVMIRParser::RuleImmutable;
}

void LLVMIRParser::ImmutableContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterImmutable(this);
}

void LLVMIRParser::ImmutableContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitImmutable(this);
}


std::any LLVMIRParser::ImmutableContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitImmutable(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ImmutableContext* LLVMIRParser::immutable()
{
    ImmutableContext* _localctx = _tracker.createInstance<ImmutableContext>(_ctx, getState());
    enterRule(_localctx, 8, LLVMIRParser::RuleImmutable);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(129);
        _la = _input->LA(1);
        if (!(_la == LLVMIRParser::T__1

              || _la == LLVMIRParser::T__2)) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncDeclContext
//------------------------------------------------------------------

LLVMIRParser::FuncDeclContext::FuncDeclContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::FuncHeaderContext* LLVMIRParser::FuncDeclContext::funcHeader()
{
    return getRuleContext<LLVMIRParser::FuncHeaderContext>(0);
}


size_t LLVMIRParser::FuncDeclContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFuncDecl;
}

void LLVMIRParser::FuncDeclContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncDecl(this);
}

void LLVMIRParser::FuncDeclContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncDecl(this);
}


std::any LLVMIRParser::FuncDeclContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFuncDecl(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FuncDeclContext* LLVMIRParser::funcDecl()
{
    FuncDeclContext* _localctx = _tracker.createInstance<FuncDeclContext>(_ctx, getState());
    enterRule(_localctx, 10, LLVMIRParser::RuleFuncDecl);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(131);
        match(LLVMIRParser::T__3);
        setState(132);
        funcHeader();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncDefContext
//------------------------------------------------------------------

LLVMIRParser::FuncDefContext::FuncDefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::FuncHeaderContext* LLVMIRParser::FuncDefContext::funcHeader()
{
    return getRuleContext<LLVMIRParser::FuncHeaderContext>(0);
}

LLVMIRParser::FuncBodyContext* LLVMIRParser::FuncDefContext::funcBody()
{
    return getRuleContext<LLVMIRParser::FuncBodyContext>(0);
}


size_t LLVMIRParser::FuncDefContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFuncDef;
}

void LLVMIRParser::FuncDefContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncDef(this);
}

void LLVMIRParser::FuncDefContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncDef(this);
}


std::any LLVMIRParser::FuncDefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFuncDef(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FuncDefContext* LLVMIRParser::funcDef()
{
    FuncDefContext* _localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
    enterRule(_localctx, 12, LLVMIRParser::RuleFuncDef);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(134);
        match(LLVMIRParser::T__4);
        setState(135);
        funcHeader();
        setState(136);
        funcBody();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncHeaderContext
//------------------------------------------------------------------

LLVMIRParser::FuncHeaderContext::FuncHeaderContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::FuncHeaderContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

tree::TerminalNode* LLVMIRParser::FuncHeaderContext::GlobalIdent()
{
    return getToken(LLVMIRParser::GlobalIdent, 0);
}

LLVMIRParser::ParamsContext* LLVMIRParser::FuncHeaderContext::params()
{
    return getRuleContext<LLVMIRParser::ParamsContext>(0);
}


size_t LLVMIRParser::FuncHeaderContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFuncHeader;
}

void LLVMIRParser::FuncHeaderContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncHeader(this);
}

void LLVMIRParser::FuncHeaderContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncHeader(this);
}


std::any LLVMIRParser::FuncHeaderContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFuncHeader(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FuncHeaderContext* LLVMIRParser::funcHeader()
{
    FuncHeaderContext* _localctx = _tracker.createInstance<FuncHeaderContext>(_ctx, getState());
    enterRule(_localctx, 14, LLVMIRParser::RuleFuncHeader);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(138);
        type(0);
        setState(139);
        match(LLVMIRParser::GlobalIdent);
        setState(140);
        match(LLVMIRParser::T__5);
        setState(141);
        params();
        setState(142);
        match(LLVMIRParser::T__6);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncBodyContext
//------------------------------------------------------------------

LLVMIRParser::FuncBodyContext::FuncBodyContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<LLVMIRParser::BasicBlockContext*> LLVMIRParser::FuncBodyContext::basicBlock()
{
    return getRuleContexts<LLVMIRParser::BasicBlockContext>();
}

LLVMIRParser::BasicBlockContext* LLVMIRParser::FuncBodyContext::basicBlock(size_t i)
{
    return getRuleContext<LLVMIRParser::BasicBlockContext>(i);
}


size_t LLVMIRParser::FuncBodyContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFuncBody;
}

void LLVMIRParser::FuncBodyContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncBody(this);
}

void LLVMIRParser::FuncBodyContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncBody(this);
}


std::any LLVMIRParser::FuncBodyContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFuncBody(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FuncBodyContext* LLVMIRParser::funcBody()
{
    FuncBodyContext* _localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
    enterRule(_localctx, 16, LLVMIRParser::RuleFuncBody);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(144);
        match(LLVMIRParser::T__7);
        setState(146);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(145);
            basicBlock();
            setState(148);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 412048421888) != 0) ||
                 _la == LLVMIRParser::LocalIdent

                 || _la == LLVMIRParser::LabelIdent);
        setState(150);
        match(LLVMIRParser::T__8);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BasicBlockContext
//------------------------------------------------------------------

LLVMIRParser::BasicBlockContext::BasicBlockContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TerminatorContext* LLVMIRParser::BasicBlockContext::terminator()
{
    return getRuleContext<LLVMIRParser::TerminatorContext>(0);
}

tree::TerminalNode* LLVMIRParser::BasicBlockContext::LabelIdent()
{
    return getToken(LLVMIRParser::LabelIdent, 0);
}

std::vector<LLVMIRParser::InstructionContext*> LLVMIRParser::BasicBlockContext::instruction()
{
    return getRuleContexts<LLVMIRParser::InstructionContext>();
}

LLVMIRParser::InstructionContext* LLVMIRParser::BasicBlockContext::instruction(size_t i)
{
    return getRuleContext<LLVMIRParser::InstructionContext>(i);
}


size_t LLVMIRParser::BasicBlockContext::getRuleIndex() const
{
    return LLVMIRParser::RuleBasicBlock;
}

void LLVMIRParser::BasicBlockContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBasicBlock(this);
}

void LLVMIRParser::BasicBlockContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBasicBlock(this);
}


std::any LLVMIRParser::BasicBlockContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitBasicBlock(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::BasicBlockContext* LLVMIRParser::basicBlock()
{
    BasicBlockContext* _localctx = _tracker.createInstance<BasicBlockContext>(_ctx, getState());
    enterRule(_localctx, 18, LLVMIRParser::RuleBasicBlock);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(153);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LLVMIRParser::LabelIdent) {
            setState(152);
            match(LLVMIRParser::LabelIdent);
        }
        setState(158);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 68451038208) != 0) ||
               _la == LLVMIRParser::LocalIdent) {
            setState(155);
            instruction();
            setState(160);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(161);
        terminator();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- InstructionContext
//------------------------------------------------------------------

LLVMIRParser::InstructionContext::InstructionContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::LocalDefInstContext* LLVMIRParser::InstructionContext::localDefInst()
{
    return getRuleContext<LLVMIRParser::LocalDefInstContext>(0);
}

LLVMIRParser::ValueInstructionContext* LLVMIRParser::InstructionContext::valueInstruction()
{
    return getRuleContext<LLVMIRParser::ValueInstructionContext>(0);
}

LLVMIRParser::StoreInstContext* LLVMIRParser::InstructionContext::storeInst()
{
    return getRuleContext<LLVMIRParser::StoreInstContext>(0);
}


size_t LLVMIRParser::InstructionContext::getRuleIndex() const
{
    return LLVMIRParser::RuleInstruction;
}

void LLVMIRParser::InstructionContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterInstruction(this);
}

void LLVMIRParser::InstructionContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitInstruction(this);
}


std::any LLVMIRParser::InstructionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitInstruction(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::InstructionContext* LLVMIRParser::instruction()
{
    InstructionContext* _localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
    enterRule(_localctx, 20, LLVMIRParser::RuleInstruction);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(166);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::LocalIdent: {
            enterOuterAlt(_localctx, 1);
            setState(163);
            localDefInst();
            break;
        }

        case LLVMIRParser::T__9:
        case LLVMIRParser::T__11:
        case LLVMIRParser::T__12:
        case LLVMIRParser::T__13:
        case LLVMIRParser::T__14:
        case LLVMIRParser::T__15:
        case LLVMIRParser::T__16:
        case LLVMIRParser::T__17:
        case LLVMIRParser::T__18:
        case LLVMIRParser::T__19:
        case LLVMIRParser::T__20:
        case LLVMIRParser::T__21:
        case LLVMIRParser::T__23:
        case LLVMIRParser::T__24:
        case LLVMIRParser::T__25:
        case LLVMIRParser::T__26:
        case LLVMIRParser::T__28:
        case LLVMIRParser::T__29:
        case LLVMIRParser::T__30:
        case LLVMIRParser::T__31:
        case LLVMIRParser::T__32:
        case LLVMIRParser::T__33:
        case LLVMIRParser::T__34: {
            enterOuterAlt(_localctx, 2);
            setState(164);
            valueInstruction();
            break;
        }

        case LLVMIRParser::T__22: {
            enterOuterAlt(_localctx, 3);
            setState(165);
            storeInst();
            break;
        }

        default: throw NoViableAltException(this);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TerminatorContext
//------------------------------------------------------------------

LLVMIRParser::TerminatorContext::TerminatorContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::RetTermContext* LLVMIRParser::TerminatorContext::retTerm()
{
    return getRuleContext<LLVMIRParser::RetTermContext>(0);
}

LLVMIRParser::BrTermContext* LLVMIRParser::TerminatorContext::brTerm()
{
    return getRuleContext<LLVMIRParser::BrTermContext>(0);
}

LLVMIRParser::CondBrTermContext* LLVMIRParser::TerminatorContext::condBrTerm()
{
    return getRuleContext<LLVMIRParser::CondBrTermContext>(0);
}


size_t LLVMIRParser::TerminatorContext::getRuleIndex() const
{
    return LLVMIRParser::RuleTerminator;
}

void LLVMIRParser::TerminatorContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterTerminator(this);
}

void LLVMIRParser::TerminatorContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitTerminator(this);
}


std::any LLVMIRParser::TerminatorContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitTerminator(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::TerminatorContext* LLVMIRParser::terminator()
{
    TerminatorContext* _localctx = _tracker.createInstance<TerminatorContext>(_ctx, getState());
    enterRule(_localctx, 22, LLVMIRParser::RuleTerminator);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(171);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
            enterOuterAlt(_localctx, 1);
            setState(168);
            retTerm();
            break;
        }

        case 2: {
            enterOuterAlt(_localctx, 2);
            setState(169);
            brTerm();
            break;
        }

        case 3: {
            enterOuterAlt(_localctx, 3);
            setState(170);
            condBrTerm();
            break;
        }

        default: break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LocalDefInstContext
//------------------------------------------------------------------

LLVMIRParser::LocalDefInstContext::LocalDefInstContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::LocalDefInstContext::LocalIdent()
{
    return getToken(LLVMIRParser::LocalIdent, 0);
}

LLVMIRParser::ValueInstructionContext* LLVMIRParser::LocalDefInstContext::valueInstruction()
{
    return getRuleContext<LLVMIRParser::ValueInstructionContext>(0);
}


size_t LLVMIRParser::LocalDefInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleLocalDefInst;
}

void LLVMIRParser::LocalDefInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLocalDefInst(this);
}

void LLVMIRParser::LocalDefInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLocalDefInst(this);
}


std::any LLVMIRParser::LocalDefInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitLocalDefInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::LocalDefInstContext* LLVMIRParser::localDefInst()
{
    LocalDefInstContext* _localctx = _tracker.createInstance<LocalDefInstContext>(_ctx, getState());
    enterRule(_localctx, 24, LLVMIRParser::RuleLocalDefInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(173);
        match(LLVMIRParser::LocalIdent);
        setState(174);
        match(LLVMIRParser::T__0);
        setState(175);
        valueInstruction();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- MathInstructionContext
//------------------------------------------------------------------

LLVMIRParser::MathInstructionContext::MathInstructionContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::MathInstructionContext::getRuleIndex() const
{
    return LLVMIRParser::RuleMathInstruction;
}

void LLVMIRParser::MathInstructionContext::copyFrom(MathInstructionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- SdivInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::SdivInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::SdivInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::SdivInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::SdivInstContext::SdivInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::SdivInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSdivInst(this);
}
void LLVMIRParser::SdivInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSdivInst(this);
}

std::any LLVMIRParser::SdivInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSdivInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FremInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FremInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FremInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FremInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::FremInstContext::FremInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FremInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFremInst(this);
}
void LLVMIRParser::FremInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFremInst(this);
}

std::any LLVMIRParser::FremInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFremInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AddInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::AddInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::AddInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::AddInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::AddInstContext::AddInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::AddInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAddInst(this);
}
void LLVMIRParser::AddInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAddInst(this);
}

std::any LLVMIRParser::AddInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitAddInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FsubInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FsubInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FsubInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FsubInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::FsubInstContext::FsubInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FsubInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFsubInst(this);
}
void LLVMIRParser::FsubInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFsubInst(this);
}

std::any LLVMIRParser::FsubInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFsubInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FdivInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FdivInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FdivInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FdivInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::FdivInstContext::FdivInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FdivInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFdivInst(this);
}
void LLVMIRParser::FdivInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFdivInst(this);
}

std::any LLVMIRParser::FdivInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFdivInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SremInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::SremInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::SremInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::SremInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::SremInstContext::SremInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::SremInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSremInst(this);
}
void LLVMIRParser::SremInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSremInst(this);
}

std::any LLVMIRParser::SremInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSremInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UdivInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::UdivInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::UdivInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::UdivInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::UdivInstContext::UdivInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::UdivInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterUdivInst(this);
}
void LLVMIRParser::UdivInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitUdivInst(this);
}

std::any LLVMIRParser::UdivInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitUdivInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UremInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::UremInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::UremInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::UremInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::UremInstContext::UremInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::UremInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterUremInst(this);
}
void LLVMIRParser::UremInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitUremInst(this);
}

std::any LLVMIRParser::UremInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitUremInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- MulInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::MulInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::MulInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::MulInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::MulInstContext::MulInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::MulInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterMulInst(this);
}
void LLVMIRParser::MulInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitMulInst(this);
}

std::any LLVMIRParser::MulInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitMulInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FaddInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FaddInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FaddInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FaddInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::FaddInstContext::FaddInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FaddInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFaddInst(this);
}
void LLVMIRParser::FaddInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFaddInst(this);
}

std::any LLVMIRParser::FaddInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFaddInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SubInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::SubInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::SubInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::SubInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::SubInstContext::SubInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::SubInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSubInst(this);
}
void LLVMIRParser::SubInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSubInst(this);
}

std::any LLVMIRParser::SubInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSubInst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FmulInstContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FmulInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FmulInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FmulInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}

LLVMIRParser::FmulInstContext::FmulInstContext(MathInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FmulInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFmulInst(this);
}
void LLVMIRParser::FmulInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFmulInst(this);
}

std::any LLVMIRParser::FmulInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFmulInst(this);
    else
        return visitor->visitChildren(this);
}
LLVMIRParser::MathInstructionContext* LLVMIRParser::mathInstruction()
{
    MathInstructionContext* _localctx =
        _tracker.createInstance<MathInstructionContext>(_ctx, getState());
    enterRule(_localctx, 26, LLVMIRParser::RuleMathInstruction);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(249);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::T__9: {
            _localctx = _tracker.createInstance<LLVMIRParser::AddInstContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(177);
            match(LLVMIRParser::T__9);
            setState(178);
            concreteType();
            setState(179);
            value();
            setState(180);
            match(LLVMIRParser::T__10);
            setState(181);
            value();
            break;
        }

        case LLVMIRParser::T__11: {
            _localctx = _tracker.createInstance<LLVMIRParser::FaddInstContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(183);
            match(LLVMIRParser::T__11);
            setState(184);
            concreteType();
            setState(185);
            value();
            setState(186);
            match(LLVMIRParser::T__10);
            setState(187);
            value();
            break;
        }

        case LLVMIRParser::T__12: {
            _localctx = _tracker.createInstance<LLVMIRParser::SubInstContext>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(189);
            match(LLVMIRParser::T__12);
            setState(190);
            concreteType();
            setState(191);
            value();
            setState(192);
            match(LLVMIRParser::T__10);
            setState(193);
            value();
            break;
        }

        case LLVMIRParser::T__13: {
            _localctx = _tracker.createInstance<LLVMIRParser::FsubInstContext>(_localctx);
            enterOuterAlt(_localctx, 4);
            setState(195);
            match(LLVMIRParser::T__13);
            setState(196);
            concreteType();
            setState(197);
            value();
            setState(198);
            match(LLVMIRParser::T__10);
            setState(199);
            value();
            break;
        }

        case LLVMIRParser::T__14: {
            _localctx = _tracker.createInstance<LLVMIRParser::MulInstContext>(_localctx);
            enterOuterAlt(_localctx, 5);
            setState(201);
            match(LLVMIRParser::T__14);
            setState(202);
            concreteType();
            setState(203);
            value();
            setState(204);
            match(LLVMIRParser::T__10);
            setState(205);
            value();
            break;
        }

        case LLVMIRParser::T__15: {
            _localctx = _tracker.createInstance<LLVMIRParser::FmulInstContext>(_localctx);
            enterOuterAlt(_localctx, 6);
            setState(207);
            match(LLVMIRParser::T__15);
            setState(208);
            concreteType();
            setState(209);
            value();
            setState(210);
            match(LLVMIRParser::T__10);
            setState(211);
            value();
            break;
        }

        case LLVMIRParser::T__16: {
            _localctx = _tracker.createInstance<LLVMIRParser::UdivInstContext>(_localctx);
            enterOuterAlt(_localctx, 7);
            setState(213);
            match(LLVMIRParser::T__16);
            setState(214);
            concreteType();
            setState(215);
            value();
            setState(216);
            match(LLVMIRParser::T__10);
            setState(217);
            value();
            break;
        }

        case LLVMIRParser::T__17: {
            _localctx = _tracker.createInstance<LLVMIRParser::SdivInstContext>(_localctx);
            enterOuterAlt(_localctx, 8);
            setState(219);
            match(LLVMIRParser::T__17);
            setState(220);
            concreteType();
            setState(221);
            value();
            setState(222);
            match(LLVMIRParser::T__10);
            setState(223);
            value();
            break;
        }

        case LLVMIRParser::T__18: {
            _localctx = _tracker.createInstance<LLVMIRParser::FdivInstContext>(_localctx);
            enterOuterAlt(_localctx, 9);
            setState(225);
            match(LLVMIRParser::T__18);
            setState(226);
            concreteType();
            setState(227);
            value();
            setState(228);
            match(LLVMIRParser::T__10);
            setState(229);
            value();
            break;
        }

        case LLVMIRParser::T__19: {
            _localctx = _tracker.createInstance<LLVMIRParser::UremInstContext>(_localctx);
            enterOuterAlt(_localctx, 10);
            setState(231);
            match(LLVMIRParser::T__19);
            setState(232);
            concreteType();
            setState(233);
            value();
            setState(234);
            match(LLVMIRParser::T__10);
            setState(235);
            value();
            break;
        }

        case LLVMIRParser::T__20: {
            _localctx = _tracker.createInstance<LLVMIRParser::SremInstContext>(_localctx);
            enterOuterAlt(_localctx, 11);
            setState(237);
            match(LLVMIRParser::T__20);
            setState(238);
            concreteType();
            setState(239);
            value();
            setState(240);
            match(LLVMIRParser::T__10);
            setState(241);
            value();
            break;
        }

        case LLVMIRParser::T__21: {
            _localctx = _tracker.createInstance<LLVMIRParser::FremInstContext>(_localctx);
            enterOuterAlt(_localctx, 12);
            setState(243);
            match(LLVMIRParser::T__21);
            setState(244);
            concreteType();
            setState(245);
            value();
            setState(246);
            match(LLVMIRParser::T__10);
            setState(247);
            value();
            break;
        }

        default: throw NoViableAltException(this);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ValueInstructionContext
//------------------------------------------------------------------

LLVMIRParser::ValueInstructionContext::ValueInstructionContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::ValueInstructionContext::getRuleIndex() const
{
    return LLVMIRParser::RuleValueInstruction;
}

void LLVMIRParser::ValueInstructionContext::copyFrom(ValueInstructionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- MathInstruction_Context
//------------------------------------------------------------------

LLVMIRParser::MathInstructionContext* LLVMIRParser::MathInstruction_Context::mathInstruction()
{
    return getRuleContext<LLVMIRParser::MathInstructionContext>(0);
}

LLVMIRParser::MathInstruction_Context::MathInstruction_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::MathInstruction_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterMathInstruction_(this);
}
void LLVMIRParser::MathInstruction_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitMathInstruction_(this);
}

std::any LLVMIRParser::MathInstruction_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitMathInstruction_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AllocaInst_Context
//------------------------------------------------------------------

LLVMIRParser::AllocaInstContext* LLVMIRParser::AllocaInst_Context::allocaInst()
{
    return getRuleContext<LLVMIRParser::AllocaInstContext>(0);
}

LLVMIRParser::AllocaInst_Context::AllocaInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::AllocaInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAllocaInst_(this);
}
void LLVMIRParser::AllocaInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAllocaInst_(this);
}

std::any LLVMIRParser::AllocaInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitAllocaInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ICmpInst_Context
//------------------------------------------------------------------

LLVMIRParser::ICmpInstContext* LLVMIRParser::ICmpInst_Context::iCmpInst()
{
    return getRuleContext<LLVMIRParser::ICmpInstContext>(0);
}

LLVMIRParser::ICmpInst_Context::ICmpInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::ICmpInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterICmpInst_(this);
}
void LLVMIRParser::ICmpInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitICmpInst_(this);
}

std::any LLVMIRParser::ICmpInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitICmpInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SiToFpInst_Context
//------------------------------------------------------------------

LLVMIRParser::SiToFpInstContext* LLVMIRParser::SiToFpInst_Context::siToFpInst()
{
    return getRuleContext<LLVMIRParser::SiToFpInstContext>(0);
}

LLVMIRParser::SiToFpInst_Context::SiToFpInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::SiToFpInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSiToFpInst_(this);
}
void LLVMIRParser::SiToFpInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSiToFpInst_(this);
}

std::any LLVMIRParser::SiToFpInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSiToFpInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- BitCastInst_Context
//------------------------------------------------------------------

LLVMIRParser::BitCastInstContext* LLVMIRParser::BitCastInst_Context::bitCastInst()
{
    return getRuleContext<LLVMIRParser::BitCastInstContext>(0);
}

LLVMIRParser::BitCastInst_Context::BitCastInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::BitCastInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBitCastInst_(this);
}
void LLVMIRParser::BitCastInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBitCastInst_(this);
}

std::any LLVMIRParser::BitCastInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitBitCastInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ZExtInst_Context
//------------------------------------------------------------------

LLVMIRParser::ZExtInstContext* LLVMIRParser::ZExtInst_Context::zExtInst()
{
    return getRuleContext<LLVMIRParser::ZExtInstContext>(0);
}

LLVMIRParser::ZExtInst_Context::ZExtInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::ZExtInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterZExtInst_(this);
}
void LLVMIRParser::ZExtInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitZExtInst_(this);
}

std::any LLVMIRParser::ZExtInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitZExtInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- CallInst_Context
//------------------------------------------------------------------

LLVMIRParser::CallInstContext* LLVMIRParser::CallInst_Context::callInst()
{
    return getRuleContext<LLVMIRParser::CallInstContext>(0);
}

LLVMIRParser::CallInst_Context::CallInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::CallInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCallInst_(this);
}
void LLVMIRParser::CallInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCallInst_(this);
}

std::any LLVMIRParser::CallInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitCallInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FCmpInst_Context
//------------------------------------------------------------------

LLVMIRParser::FCmpInstContext* LLVMIRParser::FCmpInst_Context::fCmpInst()
{
    return getRuleContext<LLVMIRParser::FCmpInstContext>(0);
}

LLVMIRParser::FCmpInst_Context::FCmpInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FCmpInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFCmpInst_(this);
}
void LLVMIRParser::FCmpInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFCmpInst_(this);
}

std::any LLVMIRParser::FCmpInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFCmpInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LoadInst_Context
//------------------------------------------------------------------

LLVMIRParser::LoadInstContext* LLVMIRParser::LoadInst_Context::loadInst()
{
    return getRuleContext<LLVMIRParser::LoadInstContext>(0);
}

LLVMIRParser::LoadInst_Context::LoadInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::LoadInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLoadInst_(this);
}
void LLVMIRParser::LoadInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLoadInst_(this);
}

std::any LLVMIRParser::LoadInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitLoadInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- GEPInst_Context
//------------------------------------------------------------------

LLVMIRParser::GetElementPtrInstContext* LLVMIRParser::GEPInst_Context::getElementPtrInst()
{
    return getRuleContext<LLVMIRParser::GetElementPtrInstContext>(0);
}

LLVMIRParser::GEPInst_Context::GEPInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::GEPInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGEPInst_(this);
}
void LLVMIRParser::GEPInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGEPInst_(this);
}

std::any LLVMIRParser::GEPInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitGEPInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FpToSiInst_Context
//------------------------------------------------------------------

LLVMIRParser::FpToSiInstContext* LLVMIRParser::FpToSiInst_Context::fpToSiInst()
{
    return getRuleContext<LLVMIRParser::FpToSiInstContext>(0);
}

LLVMIRParser::FpToSiInst_Context::FpToSiInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::FpToSiInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFpToSiInst_(this);
}
void LLVMIRParser::FpToSiInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFpToSiInst_(this);
}

std::any LLVMIRParser::FpToSiInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFpToSiInst_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SExtInst_Context
//------------------------------------------------------------------

LLVMIRParser::SExtInstContext* LLVMIRParser::SExtInst_Context::sExtInst()
{
    return getRuleContext<LLVMIRParser::SExtInstContext>(0);
}

LLVMIRParser::SExtInst_Context::SExtInst_Context(ValueInstructionContext* ctx)
{
    copyFrom(ctx);
}

void LLVMIRParser::SExtInst_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSExtInst_(this);
}
void LLVMIRParser::SExtInst_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSExtInst_(this);
}

std::any LLVMIRParser::SExtInst_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSExtInst_(this);
    else
        return visitor->visitChildren(this);
}
LLVMIRParser::ValueInstructionContext* LLVMIRParser::valueInstruction()
{
    ValueInstructionContext* _localctx =
        _tracker.createInstance<ValueInstructionContext>(_ctx, getState());
    enterRule(_localctx, 28, LLVMIRParser::RuleValueInstruction);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(263);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::T__9:
        case LLVMIRParser::T__11:
        case LLVMIRParser::T__12:
        case LLVMIRParser::T__13:
        case LLVMIRParser::T__14:
        case LLVMIRParser::T__15:
        case LLVMIRParser::T__16:
        case LLVMIRParser::T__17:
        case LLVMIRParser::T__18:
        case LLVMIRParser::T__19:
        case LLVMIRParser::T__20:
        case LLVMIRParser::T__21: {
            _localctx = _tracker.createInstance<LLVMIRParser::MathInstruction_Context>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(251);
            mathInstruction();
            break;
        }

        case LLVMIRParser::T__23: {
            _localctx = _tracker.createInstance<LLVMIRParser::AllocaInst_Context>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(252);
            allocaInst();
            break;
        }

        case LLVMIRParser::T__24: {
            _localctx = _tracker.createInstance<LLVMIRParser::LoadInst_Context>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(253);
            loadInst();
            break;
        }

        case LLVMIRParser::T__25: {
            _localctx = _tracker.createInstance<LLVMIRParser::GEPInst_Context>(_localctx);
            enterOuterAlt(_localctx, 4);
            setState(254);
            getElementPtrInst();
            break;
        }

        case LLVMIRParser::T__28: {
            _localctx = _tracker.createInstance<LLVMIRParser::ZExtInst_Context>(_localctx);
            enterOuterAlt(_localctx, 5);
            setState(255);
            zExtInst();
            break;
        }

        case LLVMIRParser::T__29: {
            _localctx = _tracker.createInstance<LLVMIRParser::SExtInst_Context>(_localctx);
            enterOuterAlt(_localctx, 6);
            setState(256);
            sExtInst();
            break;
        }

        case LLVMIRParser::T__30: {
            _localctx = _tracker.createInstance<LLVMIRParser::SiToFpInst_Context>(_localctx);
            enterOuterAlt(_localctx, 7);
            setState(257);
            siToFpInst();
            break;
        }

        case LLVMIRParser::T__31: {
            _localctx = _tracker.createInstance<LLVMIRParser::FpToSiInst_Context>(_localctx);
            enterOuterAlt(_localctx, 8);
            setState(258);
            fpToSiInst();
            break;
        }

        case LLVMIRParser::T__26: {
            _localctx = _tracker.createInstance<LLVMIRParser::BitCastInst_Context>(_localctx);
            enterOuterAlt(_localctx, 9);
            setState(259);
            bitCastInst();
            break;
        }

        case LLVMIRParser::T__32: {
            _localctx = _tracker.createInstance<LLVMIRParser::ICmpInst_Context>(_localctx);
            enterOuterAlt(_localctx, 10);
            setState(260);
            iCmpInst();
            break;
        }

        case LLVMIRParser::T__33: {
            _localctx = _tracker.createInstance<LLVMIRParser::FCmpInst_Context>(_localctx);
            enterOuterAlt(_localctx, 11);
            setState(261);
            fCmpInst();
            break;
        }

        case LLVMIRParser::T__34: {
            _localctx = _tracker.createInstance<LLVMIRParser::CallInst_Context>(_localctx);
            enterOuterAlt(_localctx, 12);
            setState(262);
            callInst();
            break;
        }

        default: throw NoViableAltException(this);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StoreInstContext
//------------------------------------------------------------------

LLVMIRParser::StoreInstContext::StoreInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<LLVMIRParser::ConcreteTypeContext*> LLVMIRParser::StoreInstContext::concreteType()
{
    return getRuleContexts<LLVMIRParser::ConcreteTypeContext>();
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::StoreInstContext::concreteType(size_t i)
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(i);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::StoreInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::StoreInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}


size_t LLVMIRParser::StoreInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleStoreInst;
}

void LLVMIRParser::StoreInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterStoreInst(this);
}

void LLVMIRParser::StoreInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitStoreInst(this);
}


std::any LLVMIRParser::StoreInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitStoreInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::StoreInstContext* LLVMIRParser::storeInst()
{
    StoreInstContext* _localctx = _tracker.createInstance<StoreInstContext>(_ctx, getState());
    enterRule(_localctx, 30, LLVMIRParser::RuleStoreInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(265);
        match(LLVMIRParser::T__22);
        setState(266);
        concreteType();
        setState(267);
        value();
        setState(268);
        match(LLVMIRParser::T__10);
        setState(269);
        concreteType();
        setState(270);
        value();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AllocaInstContext
//------------------------------------------------------------------

LLVMIRParser::AllocaInstContext::AllocaInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::AllocaInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::AllocaInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::AllocaInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}


size_t LLVMIRParser::AllocaInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleAllocaInst;
}

void LLVMIRParser::AllocaInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAllocaInst(this);
}

void LLVMIRParser::AllocaInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAllocaInst(this);
}


std::any LLVMIRParser::AllocaInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitAllocaInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::AllocaInstContext* LLVMIRParser::allocaInst()
{
    AllocaInstContext* _localctx = _tracker.createInstance<AllocaInstContext>(_ctx, getState());
    enterRule(_localctx, 32, LLVMIRParser::RuleAllocaInst);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(272);
        match(LLVMIRParser::T__23);
        setState(273);
        type(0);
        setState(278);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LLVMIRParser::T__10) {
            setState(274);
            match(LLVMIRParser::T__10);
            setState(275);
            concreteType();
            setState(276);
            value();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LoadInstContext
//------------------------------------------------------------------

LLVMIRParser::LoadInstContext::LoadInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::LoadInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::LoadInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::LoadInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}


size_t LLVMIRParser::LoadInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleLoadInst;
}

void LLVMIRParser::LoadInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLoadInst(this);
}

void LLVMIRParser::LoadInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLoadInst(this);
}


std::any LLVMIRParser::LoadInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitLoadInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::LoadInstContext* LLVMIRParser::loadInst()
{
    LoadInstContext* _localctx = _tracker.createInstance<LoadInstContext>(_ctx, getState());
    enterRule(_localctx, 34, LLVMIRParser::RuleLoadInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(280);
        match(LLVMIRParser::T__24);
        setState(281);
        type(0);
        setState(282);
        match(LLVMIRParser::T__10);
        setState(283);
        concreteType();
        setState(284);
        value();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- GetElementPtrInstContext
//------------------------------------------------------------------

LLVMIRParser::GetElementPtrInstContext::GetElementPtrInstContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::GetElementPtrInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

std::vector<LLVMIRParser::ConcreteTypeContext*>
LLVMIRParser::GetElementPtrInstContext::concreteType()
{
    return getRuleContexts<LLVMIRParser::ConcreteTypeContext>();
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::GetElementPtrInstContext::concreteType(size_t i)
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(i);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::GetElementPtrInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::GetElementPtrInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}


size_t LLVMIRParser::GetElementPtrInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleGetElementPtrInst;
}

void LLVMIRParser::GetElementPtrInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGetElementPtrInst(this);
}

void LLVMIRParser::GetElementPtrInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGetElementPtrInst(this);
}


std::any LLVMIRParser::GetElementPtrInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitGetElementPtrInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::GetElementPtrInstContext* LLVMIRParser::getElementPtrInst()
{
    GetElementPtrInstContext* _localctx =
        _tracker.createInstance<GetElementPtrInstContext>(_ctx, getState());
    enterRule(_localctx, 36, LLVMIRParser::RuleGetElementPtrInst);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(286);
        match(LLVMIRParser::T__25);
        setState(287);
        type(0);
        setState(288);
        match(LLVMIRParser::T__10);
        setState(289);
        concreteType();
        setState(290);
        value();
        setState(297);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == LLVMIRParser::T__10) {
            setState(291);
            match(LLVMIRParser::T__10);
            setState(292);
            concreteType();
            setState(293);
            value();
            setState(299);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BitCastInstContext
//------------------------------------------------------------------

LLVMIRParser::BitCastInstContext::BitCastInstContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::BitCastInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::BitCastInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::BitCastInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::BitCastInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleBitCastInst;
}

void LLVMIRParser::BitCastInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBitCastInst(this);
}

void LLVMIRParser::BitCastInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBitCastInst(this);
}


std::any LLVMIRParser::BitCastInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitBitCastInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::BitCastInstContext* LLVMIRParser::bitCastInst()
{
    BitCastInstContext* _localctx = _tracker.createInstance<BitCastInstContext>(_ctx, getState());
    enterRule(_localctx, 38, LLVMIRParser::RuleBitCastInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(300);
        match(LLVMIRParser::T__26);
        setState(301);
        concreteType();
        setState(302);
        value();
        setState(303);
        match(LLVMIRParser::T__27);
        setState(304);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ZExtInstContext
//------------------------------------------------------------------

LLVMIRParser::ZExtInstContext::ZExtInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::ZExtInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::ZExtInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::ZExtInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::ZExtInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleZExtInst;
}

void LLVMIRParser::ZExtInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterZExtInst(this);
}

void LLVMIRParser::ZExtInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitZExtInst(this);
}


std::any LLVMIRParser::ZExtInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitZExtInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ZExtInstContext* LLVMIRParser::zExtInst()
{
    ZExtInstContext* _localctx = _tracker.createInstance<ZExtInstContext>(_ctx, getState());
    enterRule(_localctx, 40, LLVMIRParser::RuleZExtInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(306);
        match(LLVMIRParser::T__28);
        setState(307);
        concreteType();
        setState(308);
        value();
        setState(309);
        match(LLVMIRParser::T__27);
        setState(310);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SExtInstContext
//------------------------------------------------------------------

LLVMIRParser::SExtInstContext::SExtInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::SExtInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::SExtInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::SExtInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::SExtInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleSExtInst;
}

void LLVMIRParser::SExtInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSExtInst(this);
}

void LLVMIRParser::SExtInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSExtInst(this);
}


std::any LLVMIRParser::SExtInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSExtInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::SExtInstContext* LLVMIRParser::sExtInst()
{
    SExtInstContext* _localctx = _tracker.createInstance<SExtInstContext>(_ctx, getState());
    enterRule(_localctx, 42, LLVMIRParser::RuleSExtInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(312);
        match(LLVMIRParser::T__29);
        setState(313);
        concreteType();
        setState(314);
        value();
        setState(315);
        match(LLVMIRParser::T__27);
        setState(316);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SiToFpInstContext
//------------------------------------------------------------------

LLVMIRParser::SiToFpInstContext::SiToFpInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::SiToFpInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::SiToFpInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::SiToFpInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::SiToFpInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleSiToFpInst;
}

void LLVMIRParser::SiToFpInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSiToFpInst(this);
}

void LLVMIRParser::SiToFpInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSiToFpInst(this);
}


std::any LLVMIRParser::SiToFpInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitSiToFpInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::SiToFpInstContext* LLVMIRParser::siToFpInst()
{
    SiToFpInstContext* _localctx = _tracker.createInstance<SiToFpInstContext>(_ctx, getState());
    enterRule(_localctx, 44, LLVMIRParser::RuleSiToFpInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(318);
        match(LLVMIRParser::T__30);
        setState(319);
        concreteType();
        setState(320);
        value();
        setState(321);
        match(LLVMIRParser::T__27);
        setState(322);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FpToSiInstContext
//------------------------------------------------------------------

LLVMIRParser::FpToSiInstContext::FpToSiInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FpToSiInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::FpToSiInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::FpToSiInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::FpToSiInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFpToSiInst;
}

void LLVMIRParser::FpToSiInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFpToSiInst(this);
}

void LLVMIRParser::FpToSiInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFpToSiInst(this);
}


std::any LLVMIRParser::FpToSiInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFpToSiInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FpToSiInstContext* LLVMIRParser::fpToSiInst()
{
    FpToSiInstContext* _localctx = _tracker.createInstance<FpToSiInstContext>(_ctx, getState());
    enterRule(_localctx, 46, LLVMIRParser::RuleFpToSiInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(324);
        match(LLVMIRParser::T__31);
        setState(325);
        concreteType();
        setState(326);
        value();
        setState(327);
        match(LLVMIRParser::T__27);
        setState(328);
        type(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ICmpInstContext
//------------------------------------------------------------------

LLVMIRParser::ICmpInstContext::ICmpInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::IPredContext* LLVMIRParser::ICmpInstContext::iPred()
{
    return getRuleContext<LLVMIRParser::IPredContext>(0);
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::ICmpInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::ICmpInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::ICmpInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}


size_t LLVMIRParser::ICmpInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleICmpInst;
}

void LLVMIRParser::ICmpInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterICmpInst(this);
}

void LLVMIRParser::ICmpInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitICmpInst(this);
}


std::any LLVMIRParser::ICmpInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitICmpInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ICmpInstContext* LLVMIRParser::iCmpInst()
{
    ICmpInstContext* _localctx = _tracker.createInstance<ICmpInstContext>(_ctx, getState());
    enterRule(_localctx, 48, LLVMIRParser::RuleICmpInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(330);
        match(LLVMIRParser::T__32);
        setState(331);
        iPred();
        setState(332);
        concreteType();
        setState(333);
        value();
        setState(334);
        match(LLVMIRParser::T__10);
        setState(335);
        value();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FCmpInstContext
//------------------------------------------------------------------

LLVMIRParser::FCmpInstContext::FCmpInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::FPredContext* LLVMIRParser::FCmpInstContext::fPred()
{
    return getRuleContext<LLVMIRParser::FPredContext>(0);
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::FCmpInstContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

std::vector<LLVMIRParser::ValueContext*> LLVMIRParser::FCmpInstContext::value()
{
    return getRuleContexts<LLVMIRParser::ValueContext>();
}

LLVMIRParser::ValueContext* LLVMIRParser::FCmpInstContext::value(size_t i)
{
    return getRuleContext<LLVMIRParser::ValueContext>(i);
}


size_t LLVMIRParser::FCmpInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFCmpInst;
}

void LLVMIRParser::FCmpInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFCmpInst(this);
}

void LLVMIRParser::FCmpInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFCmpInst(this);
}


std::any LLVMIRParser::FCmpInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFCmpInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FCmpInstContext* LLVMIRParser::fCmpInst()
{
    FCmpInstContext* _localctx = _tracker.createInstance<FCmpInstContext>(_ctx, getState());
    enterRule(_localctx, 50, LLVMIRParser::RuleFCmpInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(337);
        match(LLVMIRParser::T__33);
        setState(338);
        fPred();
        setState(339);
        concreteType();
        setState(340);
        value();
        setState(341);
        match(LLVMIRParser::T__10);
        setState(342);
        value();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- CallInstContext
//------------------------------------------------------------------

LLVMIRParser::CallInstContext::CallInstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::CallInstContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::CallInstContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

LLVMIRParser::ArgsContext* LLVMIRParser::CallInstContext::args()
{
    return getRuleContext<LLVMIRParser::ArgsContext>(0);
}


size_t LLVMIRParser::CallInstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleCallInst;
}

void LLVMIRParser::CallInstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCallInst(this);
}

void LLVMIRParser::CallInstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCallInst(this);
}


std::any LLVMIRParser::CallInstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitCallInst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::CallInstContext* LLVMIRParser::callInst()
{
    CallInstContext* _localctx = _tracker.createInstance<CallInstContext>(_ctx, getState());
    enterRule(_localctx, 52, LLVMIRParser::RuleCallInst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(344);
        match(LLVMIRParser::T__34);
        setState(345);
        type(0);
        setState(346);
        value();
        setState(347);
        match(LLVMIRParser::T__5);
        setState(348);
        args();
        setState(349);
        match(LLVMIRParser::T__6);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- RetTermContext
//------------------------------------------------------------------

LLVMIRParser::RetTermContext::RetTermContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::RetTermContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::RetTermContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}


size_t LLVMIRParser::RetTermContext::getRuleIndex() const
{
    return LLVMIRParser::RuleRetTerm;
}

void LLVMIRParser::RetTermContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterRetTerm(this);
}

void LLVMIRParser::RetTermContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitRetTerm(this);
}


std::any LLVMIRParser::RetTermContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitRetTerm(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::RetTermContext* LLVMIRParser::retTerm()
{
    RetTermContext* _localctx = _tracker.createInstance<RetTermContext>(_ctx, getState());
    enterRule(_localctx, 54, LLVMIRParser::RuleRetTerm);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(357);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
        case 1: {
            enterOuterAlt(_localctx, 1);
            setState(351);
            match(LLVMIRParser::T__35);
            setState(352);
            match(LLVMIRParser::T__36);
            break;
        }

        case 2: {
            enterOuterAlt(_localctx, 2);
            setState(353);
            match(LLVMIRParser::T__35);
            setState(354);
            concreteType();
            setState(355);
            value();
            break;
        }

        default: break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BrTermContext ------------------------------------------------------------------

LLVMIRParser::BrTermContext::BrTermContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::LabelContext* LLVMIRParser::BrTermContext::label()
{
    return getRuleContext<LLVMIRParser::LabelContext>(0);
}


size_t LLVMIRParser::BrTermContext::getRuleIndex() const
{
    return LLVMIRParser::RuleBrTerm;
}

void LLVMIRParser::BrTermContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBrTerm(this);
}

void LLVMIRParser::BrTermContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBrTerm(this);
}


std::any LLVMIRParser::BrTermContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitBrTerm(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::BrTermContext* LLVMIRParser::brTerm()
{
    BrTermContext* _localctx = _tracker.createInstance<BrTermContext>(_ctx, getState());
    enterRule(_localctx, 56, LLVMIRParser::RuleBrTerm);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(359);
        match(LLVMIRParser::T__37);
        setState(360);
        label();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- CondBrTermContext
//------------------------------------------------------------------

LLVMIRParser::CondBrTermContext::CondBrTermContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::CondBrTermContext::IntType()
{
    return getToken(LLVMIRParser::IntType, 0);
}

LLVMIRParser::ValueContext* LLVMIRParser::CondBrTermContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}

std::vector<LLVMIRParser::LabelContext*> LLVMIRParser::CondBrTermContext::label()
{
    return getRuleContexts<LLVMIRParser::LabelContext>();
}

LLVMIRParser::LabelContext* LLVMIRParser::CondBrTermContext::label(size_t i)
{
    return getRuleContext<LLVMIRParser::LabelContext>(i);
}


size_t LLVMIRParser::CondBrTermContext::getRuleIndex() const
{
    return LLVMIRParser::RuleCondBrTerm;
}

void LLVMIRParser::CondBrTermContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCondBrTerm(this);
}

void LLVMIRParser::CondBrTermContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCondBrTerm(this);
}


std::any LLVMIRParser::CondBrTermContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitCondBrTerm(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::CondBrTermContext* LLVMIRParser::condBrTerm()
{
    CondBrTermContext* _localctx = _tracker.createInstance<CondBrTermContext>(_ctx, getState());
    enterRule(_localctx, 58, LLVMIRParser::RuleCondBrTerm);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(362);
        match(LLVMIRParser::T__37);
        setState(363);
        match(LLVMIRParser::IntType);
        setState(364);
        value();
        setState(365);
        match(LLVMIRParser::T__10);
        setState(366);
        label();
        setState(367);
        match(LLVMIRParser::T__10);
        setState(368);
        label();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FloatTypeContext
//------------------------------------------------------------------

LLVMIRParser::FloatTypeContext::FloatTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::FloatTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFloatType;
}

void LLVMIRParser::FloatTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFloatType(this);
}

void LLVMIRParser::FloatTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFloatType(this);
}


std::any LLVMIRParser::FloatTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFloatType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FloatTypeContext* LLVMIRParser::floatType()
{
    FloatTypeContext* _localctx = _tracker.createInstance<FloatTypeContext>(_ctx, getState());
    enterRule(_localctx, 60, LLVMIRParser::RuleFloatType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(370);
        match(LLVMIRParser::T__38);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ConcreteTypeContext
//------------------------------------------------------------------

LLVMIRParser::ConcreteTypeContext::ConcreteTypeContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::IntTypeContext* LLVMIRParser::ConcreteTypeContext::intType()
{
    return getRuleContext<LLVMIRParser::IntTypeContext>(0);
}

LLVMIRParser::FloatTypeContext* LLVMIRParser::ConcreteTypeContext::floatType()
{
    return getRuleContext<LLVMIRParser::FloatTypeContext>(0);
}

LLVMIRParser::PointerTypeContext* LLVMIRParser::ConcreteTypeContext::pointerType()
{
    return getRuleContext<LLVMIRParser::PointerTypeContext>(0);
}

LLVMIRParser::LabelTypeContext* LLVMIRParser::ConcreteTypeContext::labelType()
{
    return getRuleContext<LLVMIRParser::LabelTypeContext>(0);
}

LLVMIRParser::ArrayTypeContext* LLVMIRParser::ConcreteTypeContext::arrayType()
{
    return getRuleContext<LLVMIRParser::ArrayTypeContext>(0);
}

LLVMIRParser::NamedTypeContext* LLVMIRParser::ConcreteTypeContext::namedType()
{
    return getRuleContext<LLVMIRParser::NamedTypeContext>(0);
}


size_t LLVMIRParser::ConcreteTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleConcreteType;
}

void LLVMIRParser::ConcreteTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterConcreteType(this);
}

void LLVMIRParser::ConcreteTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitConcreteType(this);
}


std::any LLVMIRParser::ConcreteTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitConcreteType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::concreteType()
{
    ConcreteTypeContext* _localctx = _tracker.createInstance<ConcreteTypeContext>(_ctx, getState());
    enterRule(_localctx, 62, LLVMIRParser::RuleConcreteType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(378);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
            enterOuterAlt(_localctx, 1);
            setState(372);
            intType();
            break;
        }

        case 2: {
            enterOuterAlt(_localctx, 2);
            setState(373);
            floatType();
            break;
        }

        case 3: {
            enterOuterAlt(_localctx, 3);
            setState(374);
            pointerType();
            break;
        }

        case 4: {
            enterOuterAlt(_localctx, 4);
            setState(375);
            labelType();
            break;
        }

        case 5: {
            enterOuterAlt(_localctx, 5);
            setState(376);
            arrayType();
            break;
        }

        case 6: {
            enterOuterAlt(_localctx, 6);
            setState(377);
            namedType();
            break;
        }

        default: break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

LLVMIRParser::ValueContext::ValueContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConstantContext* LLVMIRParser::ValueContext::constant()
{
    return getRuleContext<LLVMIRParser::ConstantContext>(0);
}

tree::TerminalNode* LLVMIRParser::ValueContext::LocalIdent()
{
    return getToken(LLVMIRParser::LocalIdent, 0);
}

tree::TerminalNode* LLVMIRParser::ValueContext::GlobalIdent()
{
    return getToken(LLVMIRParser::GlobalIdent, 0);
}


size_t LLVMIRParser::ValueContext::getRuleIndex() const
{
    return LLVMIRParser::RuleValue;
}

void LLVMIRParser::ValueContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterValue(this);
}

void LLVMIRParser::ValueContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitValue(this);
}


std::any LLVMIRParser::ValueContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitValue(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ValueContext* LLVMIRParser::value()
{
    ValueContext* _localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
    enterRule(_localctx, 64, LLVMIRParser::RuleValue);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(383);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::T__39:
        case LLVMIRParser::T__40:
        case LLVMIRParser::T__41:
        case LLVMIRParser::T__56:
        case LLVMIRParser::IntLit:
        case LLVMIRParser::FloatLit: {
            enterOuterAlt(_localctx, 1);
            setState(380);
            constant();
            break;
        }

        case LLVMIRParser::LocalIdent: {
            enterOuterAlt(_localctx, 2);
            setState(381);
            match(LLVMIRParser::LocalIdent);
            break;
        }

        case LLVMIRParser::GlobalIdent: {
            enterOuterAlt(_localctx, 3);
            setState(382);
            match(LLVMIRParser::GlobalIdent);
            break;
        }

        default: throw NoViableAltException(this);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ConstantContext
//------------------------------------------------------------------

LLVMIRParser::ConstantContext::ConstantContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::BoolConstContext* LLVMIRParser::ConstantContext::boolConst()
{
    return getRuleContext<LLVMIRParser::BoolConstContext>(0);
}

LLVMIRParser::IntConstContext* LLVMIRParser::ConstantContext::intConst()
{
    return getRuleContext<LLVMIRParser::IntConstContext>(0);
}

LLVMIRParser::FloatConstContext* LLVMIRParser::ConstantContext::floatConst()
{
    return getRuleContext<LLVMIRParser::FloatConstContext>(0);
}

LLVMIRParser::ArrayConstContext* LLVMIRParser::ConstantContext::arrayConst()
{
    return getRuleContext<LLVMIRParser::ArrayConstContext>(0);
}

LLVMIRParser::ZeroInitializerConstContext* LLVMIRParser::ConstantContext::zeroInitializerConst()
{
    return getRuleContext<LLVMIRParser::ZeroInitializerConstContext>(0);
}


size_t LLVMIRParser::ConstantContext::getRuleIndex() const
{
    return LLVMIRParser::RuleConstant;
}

void LLVMIRParser::ConstantContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterConstant(this);
}

void LLVMIRParser::ConstantContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitConstant(this);
}


std::any LLVMIRParser::ConstantContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitConstant(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ConstantContext* LLVMIRParser::constant()
{
    ConstantContext* _localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
    enterRule(_localctx, 66, LLVMIRParser::RuleConstant);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(390);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::T__39:
        case LLVMIRParser::T__40: {
            enterOuterAlt(_localctx, 1);
            setState(385);
            boolConst();
            break;
        }

        case LLVMIRParser::IntLit: {
            enterOuterAlt(_localctx, 2);
            setState(386);
            intConst();
            break;
        }

        case LLVMIRParser::FloatLit: {
            enterOuterAlt(_localctx, 3);
            setState(387);
            floatConst();
            break;
        }

        case LLVMIRParser::T__41: {
            enterOuterAlt(_localctx, 4);
            setState(388);
            arrayConst();
            break;
        }

        case LLVMIRParser::T__56: {
            enterOuterAlt(_localctx, 5);
            setState(389);
            zeroInitializerConst();
            break;
        }

        default: throw NoViableAltException(this);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BoolConstContext
//------------------------------------------------------------------

LLVMIRParser::BoolConstContext::BoolConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::BoolConstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleBoolConst;
}

void LLVMIRParser::BoolConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBoolConst(this);
}

void LLVMIRParser::BoolConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBoolConst(this);
}


std::any LLVMIRParser::BoolConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitBoolConst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::BoolConstContext* LLVMIRParser::boolConst()
{
    BoolConstContext* _localctx = _tracker.createInstance<BoolConstContext>(_ctx, getState());
    enterRule(_localctx, 68, LLVMIRParser::RuleBoolConst);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(392);
        _la = _input->LA(1);
        if (!(_la == LLVMIRParser::T__39

              || _la == LLVMIRParser::T__40)) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- IntConstContext
//------------------------------------------------------------------

LLVMIRParser::IntConstContext::IntConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::IntConstContext::IntLit()
{
    return getToken(LLVMIRParser::IntLit, 0);
}


size_t LLVMIRParser::IntConstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleIntConst;
}

void LLVMIRParser::IntConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterIntConst(this);
}

void LLVMIRParser::IntConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitIntConst(this);
}


std::any LLVMIRParser::IntConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitIntConst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::IntConstContext* LLVMIRParser::intConst()
{
    IntConstContext* _localctx = _tracker.createInstance<IntConstContext>(_ctx, getState());
    enterRule(_localctx, 70, LLVMIRParser::RuleIntConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(394);
        match(LLVMIRParser::IntLit);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FloatConstContext
//------------------------------------------------------------------

LLVMIRParser::FloatConstContext::FloatConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::FloatConstContext::FloatLit()
{
    return getToken(LLVMIRParser::FloatLit, 0);
}


size_t LLVMIRParser::FloatConstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFloatConst;
}

void LLVMIRParser::FloatConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFloatConst(this);
}

void LLVMIRParser::FloatConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFloatConst(this);
}


std::any LLVMIRParser::FloatConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFloatConst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FloatConstContext* LLVMIRParser::floatConst()
{
    FloatConstContext* _localctx = _tracker.createInstance<FloatConstContext>(_ctx, getState());
    enterRule(_localctx, 72, LLVMIRParser::RuleFloatConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(396);
        match(LLVMIRParser::FloatLit);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArrayConstContext
//------------------------------------------------------------------

LLVMIRParser::ArrayConstContext::ArrayConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<LLVMIRParser::ConcreteTypeContext*> LLVMIRParser::ArrayConstContext::concreteType()
{
    return getRuleContexts<LLVMIRParser::ConcreteTypeContext>();
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::ArrayConstContext::concreteType(size_t i)
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(i);
}

std::vector<LLVMIRParser::ConstantContext*> LLVMIRParser::ArrayConstContext::constant()
{
    return getRuleContexts<LLVMIRParser::ConstantContext>();
}

LLVMIRParser::ConstantContext* LLVMIRParser::ArrayConstContext::constant(size_t i)
{
    return getRuleContext<LLVMIRParser::ConstantContext>(i);
}


size_t LLVMIRParser::ArrayConstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleArrayConst;
}

void LLVMIRParser::ArrayConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterArrayConst(this);
}

void LLVMIRParser::ArrayConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitArrayConst(this);
}


std::any LLVMIRParser::ArrayConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitArrayConst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ArrayConstContext* LLVMIRParser::arrayConst()
{
    ArrayConstContext* _localctx = _tracker.createInstance<ArrayConstContext>(_ctx, getState());
    enterRule(_localctx, 74, LLVMIRParser::RuleArrayConst);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(398);
        match(LLVMIRParser::T__41);
        setState(410);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 37) & ~0x3fULL) == 0) && ((1ULL << (_la - 37)) & 687194767653) != 0)) {
            setState(399);
            concreteType();
            setState(400);
            constant();
            setState(407);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == LLVMIRParser::T__10) {
                setState(401);
                match(LLVMIRParser::T__10);
                setState(402);
                concreteType();
                setState(403);
                constant();
                setState(409);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
        setState(412);
        match(LLVMIRParser::T__42);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

LLVMIRParser::TypeContext::TypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::IntTypeContext* LLVMIRParser::TypeContext::intType()
{
    return getRuleContext<LLVMIRParser::IntTypeContext>(0);
}

LLVMIRParser::LabelTypeContext* LLVMIRParser::TypeContext::labelType()
{
    return getRuleContext<LLVMIRParser::LabelTypeContext>(0);
}

LLVMIRParser::ArrayTypeContext* LLVMIRParser::TypeContext::arrayType()
{
    return getRuleContext<LLVMIRParser::ArrayTypeContext>(0);
}

LLVMIRParser::NamedTypeContext* LLVMIRParser::TypeContext::namedType()
{
    return getRuleContext<LLVMIRParser::NamedTypeContext>(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::TypeContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

LLVMIRParser::ParamsContext* LLVMIRParser::TypeContext::params()
{
    return getRuleContext<LLVMIRParser::ParamsContext>(0);
}


size_t LLVMIRParser::TypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleType;
}

void LLVMIRParser::TypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterType(this);
}

void LLVMIRParser::TypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitType(this);
}


std::any LLVMIRParser::TypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitType(this);
    else
        return visitor->visitChildren(this);
}


LLVMIRParser::TypeContext* LLVMIRParser::type()
{
    return type(0);
}

LLVMIRParser::TypeContext* LLVMIRParser::type(int precedence)
{
    ParserRuleContext*         parentContext = _ctx;
    size_t                     parentState   = getState();
    LLVMIRParser::TypeContext* _localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
    LLVMIRParser::TypeContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 76;
    enterRecursionRule(_localctx, 76, LLVMIRParser::RuleType, precedence);



#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        unrollRecursionContexts(parentContext);
    });
    try {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(421);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case LLVMIRParser::T__36: {
            setState(415);
            match(LLVMIRParser::T__36);
            break;
        }

        case LLVMIRParser::IntType: {
            setState(416);
            intType();
            break;
        }

        case LLVMIRParser::T__38: {
            setState(417);
            match(LLVMIRParser::T__38);
            break;
        }

        case LLVMIRParser::T__44: {
            setState(418);
            labelType();
            break;
        }

        case LLVMIRParser::T__41: {
            setState(419);
            arrayType();
            break;
        }

        case LLVMIRParser::LocalIdent: {
            setState(420);
            namedType();
            break;
        }

        default: throw NoViableAltException(this);
        }
        _ctx->stop = _input->LT(-1);
        setState(432);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(430);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)
                ) {
                case 1: {
                    _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
                    pushNewRecursionContext(_localctx, startState, RuleType);
                    setState(423);

                    if (!(precpred(_ctx, 7)))
                        throw FailedPredicateException(this, "precpred(_ctx, 7)");
                    setState(424);
                    match(LLVMIRParser::T__5);
                    setState(425);
                    params();
                    setState(426);
                    match(LLVMIRParser::T__6);
                    break;
                }

                case 2: {
                    _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
                    pushNewRecursionContext(_localctx, startState, RuleType);
                    setState(428);

                    if (!(precpred(_ctx, 2)))
                        throw FailedPredicateException(this, "precpred(_ctx, 2)");
                    setState(429);
                    match(LLVMIRParser::T__43);
                    break;
                }

                default: break;
                }
            }
            setState(434);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- IntTypeContext
//------------------------------------------------------------------

LLVMIRParser::IntTypeContext::IntTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::IntTypeContext::IntType()
{
    return getToken(LLVMIRParser::IntType, 0);
}


size_t LLVMIRParser::IntTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleIntType;
}

void LLVMIRParser::IntTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterIntType(this);
}

void LLVMIRParser::IntTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitIntType(this);
}


std::any LLVMIRParser::IntTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitIntType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::IntTypeContext* LLVMIRParser::intType()
{
    IntTypeContext* _localctx = _tracker.createInstance<IntTypeContext>(_ctx, getState());
    enterRule(_localctx, 78, LLVMIRParser::RuleIntType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(435);
        match(LLVMIRParser::IntType);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PointerTypeContext
//------------------------------------------------------------------

LLVMIRParser::PointerTypeContext::PointerTypeContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::PointerTypeContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::PointerTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RulePointerType;
}

void LLVMIRParser::PointerTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterPointerType(this);
}

void LLVMIRParser::PointerTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitPointerType(this);
}


std::any LLVMIRParser::PointerTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitPointerType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::PointerTypeContext* LLVMIRParser::pointerType()
{
    PointerTypeContext* _localctx = _tracker.createInstance<PointerTypeContext>(_ctx, getState());
    enterRule(_localctx, 80, LLVMIRParser::RulePointerType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(437);
        type(0);
        setState(438);
        match(LLVMIRParser::T__43);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LabelTypeContext
//------------------------------------------------------------------

LLVMIRParser::LabelTypeContext::LabelTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::LabelTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleLabelType;
}

void LLVMIRParser::LabelTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLabelType(this);
}

void LLVMIRParser::LabelTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLabelType(this);
}


std::any LLVMIRParser::LabelTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitLabelType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::LabelTypeContext* LLVMIRParser::labelType()
{
    LabelTypeContext* _localctx = _tracker.createInstance<LabelTypeContext>(_ctx, getState());
    enterRule(_localctx, 82, LLVMIRParser::RuleLabelType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(440);
        match(LLVMIRParser::T__44);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArrayTypeContext
//------------------------------------------------------------------

LLVMIRParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::ArrayTypeContext::IntLit()
{
    return getToken(LLVMIRParser::IntLit, 0);
}

LLVMIRParser::TypeContext* LLVMIRParser::ArrayTypeContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}


size_t LLVMIRParser::ArrayTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleArrayType;
}

void LLVMIRParser::ArrayTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterArrayType(this);
}

void LLVMIRParser::ArrayTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitArrayType(this);
}


std::any LLVMIRParser::ArrayTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitArrayType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ArrayTypeContext* LLVMIRParser::arrayType()
{
    ArrayTypeContext* _localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
    enterRule(_localctx, 84, LLVMIRParser::RuleArrayType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(442);
        match(LLVMIRParser::T__41);
        setState(443);
        match(LLVMIRParser::IntLit);
        setState(444);
        match(LLVMIRParser::T__45);
        setState(445);
        type(0);
        setState(446);
        match(LLVMIRParser::T__42);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- NamedTypeContext
//------------------------------------------------------------------

LLVMIRParser::NamedTypeContext::NamedTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::NamedTypeContext::LocalIdent()
{
    return getToken(LLVMIRParser::LocalIdent, 0);
}


size_t LLVMIRParser::NamedTypeContext::getRuleIndex() const
{
    return LLVMIRParser::RuleNamedType;
}

void LLVMIRParser::NamedTypeContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterNamedType(this);
}

void LLVMIRParser::NamedTypeContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitNamedType(this);
}


std::any LLVMIRParser::NamedTypeContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitNamedType(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::NamedTypeContext* LLVMIRParser::namedType()
{
    NamedTypeContext* _localctx = _tracker.createInstance<NamedTypeContext>(_ctx, getState());
    enterRule(_localctx, 86, LLVMIRParser::RuleNamedType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(448);
        match(LLVMIRParser::LocalIdent);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

LLVMIRParser::ParamsContext::ParamsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<LLVMIRParser::ParamContext*> LLVMIRParser::ParamsContext::param()
{
    return getRuleContexts<LLVMIRParser::ParamContext>();
}

LLVMIRParser::ParamContext* LLVMIRParser::ParamsContext::param(size_t i)
{
    return getRuleContext<LLVMIRParser::ParamContext>(i);
}


size_t LLVMIRParser::ParamsContext::getRuleIndex() const
{
    return LLVMIRParser::RuleParams;
}

void LLVMIRParser::ParamsContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterParams(this);
}

void LLVMIRParser::ParamsContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitParams(this);
}


std::any LLVMIRParser::ParamsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitParams(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ParamsContext* LLVMIRParser::params()
{
    ParamsContext* _localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
    enterRule(_localctx, 88, LLVMIRParser::RuleParams);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(458);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 37) & ~0x3fULL) == 0) && ((1ULL << (_la - 37)) & 687194767653) != 0)) {
            setState(450);
            param();
            setState(455);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == LLVMIRParser::T__10) {
                setState(451);
                match(LLVMIRParser::T__10);
                setState(452);
                param();
                setState(457);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

LLVMIRParser::ParamContext::ParamContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::TypeContext* LLVMIRParser::ParamContext::type()
{
    return getRuleContext<LLVMIRParser::TypeContext>(0);
}

tree::TerminalNode* LLVMIRParser::ParamContext::LocalIdent()
{
    return getToken(LLVMIRParser::LocalIdent, 0);
}


size_t LLVMIRParser::ParamContext::getRuleIndex() const
{
    return LLVMIRParser::RuleParam;
}

void LLVMIRParser::ParamContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterParam(this);
}

void LLVMIRParser::ParamContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitParam(this);
}


std::any LLVMIRParser::ParamContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitParam(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ParamContext* LLVMIRParser::param()
{
    ParamContext* _localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
    enterRule(_localctx, 90, LLVMIRParser::RuleParam);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(460);
        type(0);
        setState(462);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LLVMIRParser::LocalIdent) {
            setState(461);
            match(LLVMIRParser::LocalIdent);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LabelContext ------------------------------------------------------------------

LLVMIRParser::LabelContext::LabelContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* LLVMIRParser::LabelContext::LocalIdent()
{
    return getToken(LLVMIRParser::LocalIdent, 0);
}


size_t LLVMIRParser::LabelContext::getRuleIndex() const
{
    return LLVMIRParser::RuleLabel;
}

void LLVMIRParser::LabelContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLabel(this);
}

void LLVMIRParser::LabelContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLabel(this);
}


std::any LLVMIRParser::LabelContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitLabel(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::LabelContext* LLVMIRParser::label()
{
    LabelContext* _localctx = _tracker.createInstance<LabelContext>(_ctx, getState());
    enterRule(_localctx, 92, LLVMIRParser::RuleLabel);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(464);
        match(LLVMIRParser::T__44);
        setState(465);
        match(LLVMIRParser::LocalIdent);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- IPredContext ------------------------------------------------------------------

LLVMIRParser::IPredContext::IPredContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::IPredContext::getRuleIndex() const
{
    return LLVMIRParser::RuleIPred;
}

void LLVMIRParser::IPredContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterIPred(this);
}

void LLVMIRParser::IPredContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitIPred(this);
}


std::any LLVMIRParser::IPredContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitIPred(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::IPredContext* LLVMIRParser::iPred()
{
    IPredContext* _localctx = _tracker.createInstance<IPredContext>(_ctx, getState());
    enterRule(_localctx, 94, LLVMIRParser::RuleIPred);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(467);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 143974450587500544) != 0))) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

LLVMIRParser::ArgsContext::ArgsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<LLVMIRParser::ArgContext*> LLVMIRParser::ArgsContext::arg()
{
    return getRuleContexts<LLVMIRParser::ArgContext>();
}

LLVMIRParser::ArgContext* LLVMIRParser::ArgsContext::arg(size_t i)
{
    return getRuleContext<LLVMIRParser::ArgContext>(i);
}


size_t LLVMIRParser::ArgsContext::getRuleIndex() const
{
    return LLVMIRParser::RuleArgs;
}

void LLVMIRParser::ArgsContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterArgs(this);
}

void LLVMIRParser::ArgsContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitArgs(this);
}


std::any LLVMIRParser::ArgsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitArgs(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ArgsContext* LLVMIRParser::args()
{
    ArgsContext* _localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
    enterRule(_localctx, 96, LLVMIRParser::RuleArgs);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(477);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 37) & ~0x3fULL) == 0) && ((1ULL << (_la - 37)) & 687194767653) != 0)) {
            setState(469);
            arg();
            setState(474);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == LLVMIRParser::T__10) {
                setState(470);
                match(LLVMIRParser::T__10);
                setState(471);
                arg();
                setState(476);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

LLVMIRParser::ArgContext::ArgContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

LLVMIRParser::ConcreteTypeContext* LLVMIRParser::ArgContext::concreteType()
{
    return getRuleContext<LLVMIRParser::ConcreteTypeContext>(0);
}

LLVMIRParser::ValueContext* LLVMIRParser::ArgContext::value()
{
    return getRuleContext<LLVMIRParser::ValueContext>(0);
}


size_t LLVMIRParser::ArgContext::getRuleIndex() const
{
    return LLVMIRParser::RuleArg;
}

void LLVMIRParser::ArgContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterArg(this);
}

void LLVMIRParser::ArgContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitArg(this);
}


std::any LLVMIRParser::ArgContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitArg(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ArgContext* LLVMIRParser::arg()
{
    ArgContext* _localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
    enterRule(_localctx, 98, LLVMIRParser::RuleArg);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(479);
        concreteType();
        setState(480);
        value();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ZeroInitializerConstContext
//------------------------------------------------------------------

LLVMIRParser::ZeroInitializerConstContext::ZeroInitializerConstContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::ZeroInitializerConstContext::getRuleIndex() const
{
    return LLVMIRParser::RuleZeroInitializerConst;
}

void LLVMIRParser::ZeroInitializerConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterZeroInitializerConst(this);
}

void LLVMIRParser::ZeroInitializerConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitZeroInitializerConst(this);
}


std::any LLVMIRParser::ZeroInitializerConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitZeroInitializerConst(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::ZeroInitializerConstContext* LLVMIRParser::zeroInitializerConst()
{
    ZeroInitializerConstContext* _localctx =
        _tracker.createInstance<ZeroInitializerConstContext>(_ctx, getState());
    enterRule(_localctx, 100, LLVMIRParser::RuleZeroInitializerConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(482);
        match(LLVMIRParser::T__56);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FPredContext ------------------------------------------------------------------

LLVMIRParser::FPredContext::FPredContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t LLVMIRParser::FPredContext::getRuleIndex() const
{
    return LLVMIRParser::RuleFPred;
}

void LLVMIRParser::FPredContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFPred(this);
}

void LLVMIRParser::FPredContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<LLVMIRListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFPred(this);
}


std::any LLVMIRParser::FPredContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<LLVMIRVisitor*>(visitor))
        return parserVisitor->visitFPred(this);
    else
        return visitor->visitChildren(this);
}

LLVMIRParser::FPredContext* LLVMIRParser::fPred()
{
    FPredContext* _localctx = _tracker.createInstance<FPredContext>(_ctx, getState());
    enterRule(_localctx, 102, LLVMIRParser::RuleFPred);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(484);
        _la = _input->LA(1);
        if (!(((((_la - 40) & ~0x3fULL) == 0) && ((1ULL << (_la - 40)) & 268296195) != 0))) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

bool LLVMIRParser::sempred(RuleContext* context, size_t ruleIndex, size_t predicateIndex)
{
    switch (ruleIndex) {
    case 38: return typeSempred(antlrcpp::downCast<TypeContext*>(context), predicateIndex);

    default: break;
    }
    return true;
}

bool LLVMIRParser::typeSempred(TypeContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 2);

    default: break;
    }
    return true;
}

void LLVMIRParser::initialize()
{
#if ANTLR4_USE_THREAD_LOCAL_CACHE
    llvmirParserInitialize();
#else
    ::antlr4::internal::call_once(llvmirParserOnceFlag, llvmirParserInitialize);
#endif
}
