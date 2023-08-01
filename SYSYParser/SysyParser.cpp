
// Generated from Sysy.g4 by ANTLR 4.13.0


#include "SysyListener.h"
#include "SysyVisitor.h"

#include "SysyParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace
{

struct SysyParserStaticData final {
    SysyParserStaticData(
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

    SysyParserStaticData(const SysyParserStaticData&) = delete;

    SysyParserStaticData(SysyParserStaticData&&) = delete;

    SysyParserStaticData& operator=(const SysyParserStaticData&) = delete;

    SysyParserStaticData& operator=(SysyParserStaticData&&) = delete;

    std::vector<antlr4::dfa::DFA>       decisionToDFA;
    antlr4::atn::PredictionContextCache sharedContextCache;
    const std::vector<std::string>      ruleNames;
    const std::vector<std::string>      literalNames;
    const std::vector<std::string>      symbolicNames;
    const antlr4::dfa::Vocabulary       vocabulary;
    antlr4::atn::SerializedATNView      serializedATN;
    std::unique_ptr<antlr4::atn::ATN>   atn;
};

::antlr4::internal::OnceFlag sysyParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
    SysyParserStaticData* sysyParserStaticData = nullptr;

void sysyParserInitialize()
{
#if ANTLR4_USE_THREAD_LOCAL_CACHE
    if (sysyParserStaticData != nullptr) { return; }
#else
    assert(sysyParserStaticData == nullptr);
#endif
    auto staticData = std::make_unique<SysyParserStaticData>(
        std::vector<std::string>{
            "compUnit",    "compUnitItem", "decl",        "constDecl",  "bType",    "constDef",
            "varDecl",     "varDef",       "initVal",     "funcDef",    "funcType", "funcFParams",
            "funcFParam",  "block",        "blockItem",   "stmt",       "exp",      "cond",
            "lVal",        "primaryExp",   "intConst",    "floatConst", "number",   "unaryExp",
            "stringConst", "funcRParam",   "funcRParams", "mulExp",     "addExp",   "relExp",
            "eqExp",       "lAndExp",      "lOrExp"},
        std::vector<std::string>{
            "",         "",       "",        "",     "",       "",        "",        "'int'",
            "'float'",  "'void'", "'const'", "'if'", "'else'", "'while'", "'break'", "'continue'",
            "'return'", "'='",    "'+'",     "'-'",  "'*'",    "'/'",     "'%'",     "'=='",
            "'!='",     "'<'",    "'>'",     "'<='", "'>='",   "'!'",     "'&&'",    "'||'",
            "','",      "';'",    "'('",     "')'",  "'['",    "']'",     "'{'",     "'}'"},
        std::vector<std::string>{
            "",
            "DecIntConst",
            "OctIntConst",
            "HexIntConst",
            "DecFloatConst",
            "HexFloatConst",
            "StringConst",
            "Int",
            "Float",
            "Void",
            "Const",
            "If",
            "Else",
            "While",
            "Break",
            "Continue",
            "Return",
            "Assign",
            "Add",
            "Sub",
            "Mul",
            "Div",
            "Mod",
            "Eq",
            "Neq",
            "Lt",
            "Gt",
            "Leq",
            "Geq",
            "Not",
            "And",
            "Or",
            "Comma",
            "Semicolon",
            "Lparen",
            "Rparen",
            "Lbracket",
            "Rbracket",
            "Lbrace",
            "Rbrace",
            "Ident",
            "Whitespace",
            "LineComment",
            "BlockComment"}
    );
    static const int32_t serializedATNSegment[] = {
        4,   1,   43,  391, 2,   0,   7,   0,   2,   1,   7,   1,   2,   2,   7,   2,   2,   3,
        7,   3,   2,   4,   7,   4,   2,   5,   7,   5,   2,   6,   7,   6,   2,   7,   7,   7,
        2,   8,   7,   8,   2,   9,   7,   9,   2,   10,  7,   10,  2,   11,  7,   11,  2,   12,
        7,   12,  2,   13,  7,   13,  2,   14,  7,   14,  2,   15,  7,   15,  2,   16,  7,   16,
        2,   17,  7,   17,  2,   18,  7,   18,  2,   19,  7,   19,  2,   20,  7,   20,  2,   21,
        7,   21,  2,   22,  7,   22,  2,   23,  7,   23,  2,   24,  7,   24,  2,   25,  7,   25,
        2,   26,  7,   26,  2,   27,  7,   27,  2,   28,  7,   28,  2,   29,  7,   29,  2,   30,
        7,   30,  2,   31,  7,   31,  2,   32,  7,   32,  1,   0,   5,   0,   68,  8,   0,   10,
        0,   12,  0,   71,  9,   0,   1,   0,   1,   0,   1,   1,   1,   1,   3,   1,   77,  8,
        1,   1,   2,   1,   2,   3,   2,   81,  8,   2,   1,   3,   1,   3,   1,   3,   1,   3,
        1,   3,   5,   3,   88,  8,   3,   10,  3,   12,  3,   91,  9,   3,   1,   3,   1,   3,
        1,   4,   1,   4,   3,   4,   97,  8,   4,   1,   5,   1,   5,   1,   5,   1,   5,   1,
        5,   5,   5,   104, 8,   5,   10,  5,   12,  5,   107, 9,   5,   1,   5,   1,   5,   1,
        5,   1,   6,   1,   6,   1,   6,   1,   6,   5,   6,   116, 8,   6,   10,  6,   12,  6,
        119, 9,   6,   1,   6,   1,   6,   1,   7,   1,   7,   1,   7,   1,   7,   1,   7,   5,
        7,   128, 8,   7,   10,  7,   12,  7,   131, 9,   7,   1,   7,   1,   7,   3,   7,   135,
        8,   7,   1,   8,   1,   8,   1,   8,   1,   8,   1,   8,   5,   8,   142, 8,   8,   10,
        8,   12,  8,   145, 9,   8,   3,   8,   147, 8,   8,   1,   8,   3,   8,   150, 8,   8,
        1,   9,   1,   9,   1,   9,   1,   9,   3,   9,   156, 8,   9,   1,   9,   1,   9,   1,
        9,   1,   10,  1,   10,  3,   10,  163, 8,   10,  1,   11,  1,   11,  1,   11,  5,   11,
        168, 8,   11,  10,  11,  12,  11,  171, 9,   11,  1,   12,  1,   12,  1,   12,  1,   12,
        1,   12,  1,   12,  1,   12,  1,   12,  1,   12,  1,   12,  1,   12,  5,   12,  184, 8,
        12,  10,  12,  12,  12,  187, 9,   12,  3,   12,  189, 8,   12,  1,   13,  1,   13,  5,
        13,  193, 8,   13,  10,  13,  12,  13,  196, 9,   13,  1,   13,  1,   13,  1,   14,  1,
        14,  3,   14,  202, 8,   14,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,
        3,   15,  210, 8,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,
        15,  1,   15,  1,   15,  3,   15,  221, 8,   15,  1,   15,  1,   15,  1,   15,  1,   15,
        1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  1,   15,  3,   15,
        235, 8,   15,  1,   15,  3,   15,  238, 8,   15,  1,   16,  1,   16,  1,   17,  1,   17,
        1,   18,  1,   18,  1,   18,  1,   18,  1,   18,  5,   18,  249, 8,   18,  10,  18,  12,
        18,  252, 9,   18,  1,   19,  1,   19,  1,   19,  1,   19,  1,   19,  1,   19,  3,   19,
        260, 8,   19,  1,   20,  1,   20,  1,   20,  3,   20,  265, 8,   20,  1,   21,  1,   21,
        3,   21,  269, 8,   21,  1,   22,  1,   22,  3,   22,  273, 8,   22,  1,   23,  1,   23,
        1,   23,  1,   23,  3,   23,  279, 8,   23,  1,   23,  1,   23,  1,   23,  1,   23,  1,
        23,  1,   23,  1,   23,  3,   23,  288, 8,   23,  1,   24,  1,   24,  1,   25,  1,   25,
        3,   25,  294, 8,   25,  1,   26,  1,   26,  1,   26,  5,   26,  299, 8,   26,  10,  26,
        12,  26,  302, 9,   26,  1,   27,  1,   27,  1,   27,  1,   27,  1,   27,  1,   27,  1,
        27,  1,   27,  1,   27,  1,   27,  1,   27,  1,   27,  5,   27,  316, 8,   27,  10,  27,
        12,  27,  319, 9,   27,  1,   28,  1,   28,  1,   28,  1,   28,  1,   28,  1,   28,  1,
        28,  1,   28,  1,   28,  5,   28,  330, 8,   28,  10,  28,  12,  28,  333, 9,   28,  1,
        29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  1,
        29,  1,   29,  1,   29,  1,   29,  1,   29,  1,   29,  5,   29,  350, 8,   29,  10,  29,
        12,  29,  353, 9,   29,  1,   30,  1,   30,  1,   30,  1,   30,  1,   30,  1,   30,  1,
        30,  1,   30,  1,   30,  5,   30,  364, 8,   30,  10,  30,  12,  30,  367, 9,   30,  1,
        31,  1,   31,  1,   31,  1,   31,  1,   31,  1,   31,  5,   31,  375, 8,   31,  10,  31,
        12,  31,  378, 9,   31,  1,   32,  1,   32,  1,   32,  1,   32,  1,   32,  1,   32,  5,
        32,  386, 8,   32,  10,  32,  12,  32,  389, 9,   32,  1,   32,  0,   6,   54,  56,  58,
        60,  62,  64,  33,  0,   2,   4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  26,
        28,  30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,  52,  54,  56,  58,  60,  62,
        64,  0,   0,   413, 0,   69,  1,   0,   0,   0,   2,   76,  1,   0,   0,   0,   4,   80,
        1,   0,   0,   0,   6,   82,  1,   0,   0,   0,   8,   96,  1,   0,   0,   0,   10,  98,
        1,   0,   0,   0,   12,  111, 1,   0,   0,   0,   14,  122, 1,   0,   0,   0,   16,  149,
        1,   0,   0,   0,   18,  151, 1,   0,   0,   0,   20,  162, 1,   0,   0,   0,   22,  164,
        1,   0,   0,   0,   24,  188, 1,   0,   0,   0,   26,  190, 1,   0,   0,   0,   28,  201,
        1,   0,   0,   0,   30,  237, 1,   0,   0,   0,   32,  239, 1,   0,   0,   0,   34,  241,
        1,   0,   0,   0,   36,  243, 1,   0,   0,   0,   38,  259, 1,   0,   0,   0,   40,  264,
        1,   0,   0,   0,   42,  268, 1,   0,   0,   0,   44,  272, 1,   0,   0,   0,   46,  287,
        1,   0,   0,   0,   48,  289, 1,   0,   0,   0,   50,  293, 1,   0,   0,   0,   52,  295,
        1,   0,   0,   0,   54,  303, 1,   0,   0,   0,   56,  320, 1,   0,   0,   0,   58,  334,
        1,   0,   0,   0,   60,  354, 1,   0,   0,   0,   62,  368, 1,   0,   0,   0,   64,  379,
        1,   0,   0,   0,   66,  68,  3,   2,   1,   0,   67,  66,  1,   0,   0,   0,   68,  71,
        1,   0,   0,   0,   69,  67,  1,   0,   0,   0,   69,  70,  1,   0,   0,   0,   70,  72,
        1,   0,   0,   0,   71,  69,  1,   0,   0,   0,   72,  73,  5,   0,   0,   1,   73,  1,
        1,   0,   0,   0,   74,  77,  3,   4,   2,   0,   75,  77,  3,   18,  9,   0,   76,  74,
        1,   0,   0,   0,   76,  75,  1,   0,   0,   0,   77,  3,   1,   0,   0,   0,   78,  81,
        3,   6,   3,   0,   79,  81,  3,   12,  6,   0,   80,  78,  1,   0,   0,   0,   80,  79,
        1,   0,   0,   0,   81,  5,   1,   0,   0,   0,   82,  83,  5,   10,  0,   0,   83,  84,
        3,   8,   4,   0,   84,  89,  3,   10,  5,   0,   85,  86,  5,   32,  0,   0,   86,  88,
        3,   10,  5,   0,   87,  85,  1,   0,   0,   0,   88,  91,  1,   0,   0,   0,   89,  87,
        1,   0,   0,   0,   89,  90,  1,   0,   0,   0,   90,  92,  1,   0,   0,   0,   91,  89,
        1,   0,   0,   0,   92,  93,  5,   33,  0,   0,   93,  7,   1,   0,   0,   0,   94,  97,
        5,   7,   0,   0,   95,  97,  5,   8,   0,   0,   96,  94,  1,   0,   0,   0,   96,  95,
        1,   0,   0,   0,   97,  9,   1,   0,   0,   0,   98,  105, 5,   40,  0,   0,   99,  100,
        5,   36,  0,   0,   100, 101, 3,   32,  16,  0,   101, 102, 5,   37,  0,   0,   102, 104,
        1,   0,   0,   0,   103, 99,  1,   0,   0,   0,   104, 107, 1,   0,   0,   0,   105, 103,
        1,   0,   0,   0,   105, 106, 1,   0,   0,   0,   106, 108, 1,   0,   0,   0,   107, 105,
        1,   0,   0,   0,   108, 109, 5,   17,  0,   0,   109, 110, 3,   16,  8,   0,   110, 11,
        1,   0,   0,   0,   111, 112, 3,   8,   4,   0,   112, 117, 3,   14,  7,   0,   113, 114,
        5,   32,  0,   0,   114, 116, 3,   14,  7,   0,   115, 113, 1,   0,   0,   0,   116, 119,
        1,   0,   0,   0,   117, 115, 1,   0,   0,   0,   117, 118, 1,   0,   0,   0,   118, 120,
        1,   0,   0,   0,   119, 117, 1,   0,   0,   0,   120, 121, 5,   33,  0,   0,   121, 13,
        1,   0,   0,   0,   122, 129, 5,   40,  0,   0,   123, 124, 5,   36,  0,   0,   124, 125,
        3,   32,  16,  0,   125, 126, 5,   37,  0,   0,   126, 128, 1,   0,   0,   0,   127, 123,
        1,   0,   0,   0,   128, 131, 1,   0,   0,   0,   129, 127, 1,   0,   0,   0,   129, 130,
        1,   0,   0,   0,   130, 134, 1,   0,   0,   0,   131, 129, 1,   0,   0,   0,   132, 133,
        5,   17,  0,   0,   133, 135, 3,   16,  8,   0,   134, 132, 1,   0,   0,   0,   134, 135,
        1,   0,   0,   0,   135, 15,  1,   0,   0,   0,   136, 150, 3,   32,  16,  0,   137, 146,
        5,   38,  0,   0,   138, 143, 3,   16,  8,   0,   139, 140, 5,   32,  0,   0,   140, 142,
        3,   16,  8,   0,   141, 139, 1,   0,   0,   0,   142, 145, 1,   0,   0,   0,   143, 141,
        1,   0,   0,   0,   143, 144, 1,   0,   0,   0,   144, 147, 1,   0,   0,   0,   145, 143,
        1,   0,   0,   0,   146, 138, 1,   0,   0,   0,   146, 147, 1,   0,   0,   0,   147, 148,
        1,   0,   0,   0,   148, 150, 5,   39,  0,   0,   149, 136, 1,   0,   0,   0,   149, 137,
        1,   0,   0,   0,   150, 17,  1,   0,   0,   0,   151, 152, 3,   20,  10,  0,   152, 153,
        5,   40,  0,   0,   153, 155, 5,   34,  0,   0,   154, 156, 3,   22,  11,  0,   155, 154,
        1,   0,   0,   0,   155, 156, 1,   0,   0,   0,   156, 157, 1,   0,   0,   0,   157, 158,
        5,   35,  0,   0,   158, 159, 3,   26,  13,  0,   159, 19,  1,   0,   0,   0,   160, 163,
        3,   8,   4,   0,   161, 163, 5,   9,   0,   0,   162, 160, 1,   0,   0,   0,   162, 161,
        1,   0,   0,   0,   163, 21,  1,   0,   0,   0,   164, 169, 3,   24,  12,  0,   165, 166,
        5,   32,  0,   0,   166, 168, 3,   24,  12,  0,   167, 165, 1,   0,   0,   0,   168, 171,
        1,   0,   0,   0,   169, 167, 1,   0,   0,   0,   169, 170, 1,   0,   0,   0,   170, 23,
        1,   0,   0,   0,   171, 169, 1,   0,   0,   0,   172, 173, 3,   8,   4,   0,   173, 174,
        5,   40,  0,   0,   174, 189, 1,   0,   0,   0,   175, 176, 3,   8,   4,   0,   176, 177,
        5,   40,  0,   0,   177, 178, 5,   36,  0,   0,   178, 185, 5,   37,  0,   0,   179, 180,
        5,   36,  0,   0,   180, 181, 3,   32,  16,  0,   181, 182, 5,   37,  0,   0,   182, 184,
        1,   0,   0,   0,   183, 179, 1,   0,   0,   0,   184, 187, 1,   0,   0,   0,   185, 183,
        1,   0,   0,   0,   185, 186, 1,   0,   0,   0,   186, 189, 1,   0,   0,   0,   187, 185,
        1,   0,   0,   0,   188, 172, 1,   0,   0,   0,   188, 175, 1,   0,   0,   0,   189, 25,
        1,   0,   0,   0,   190, 194, 5,   38,  0,   0,   191, 193, 3,   28,  14,  0,   192, 191,
        1,   0,   0,   0,   193, 196, 1,   0,   0,   0,   194, 192, 1,   0,   0,   0,   194, 195,
        1,   0,   0,   0,   195, 197, 1,   0,   0,   0,   196, 194, 1,   0,   0,   0,   197, 198,
        5,   39,  0,   0,   198, 27,  1,   0,   0,   0,   199, 202, 3,   4,   2,   0,   200, 202,
        3,   30,  15,  0,   201, 199, 1,   0,   0,   0,   201, 200, 1,   0,   0,   0,   202, 29,
        1,   0,   0,   0,   203, 204, 3,   36,  18,  0,   204, 205, 5,   17,  0,   0,   205, 206,
        3,   32,  16,  0,   206, 207, 5,   33,  0,   0,   207, 238, 1,   0,   0,   0,   208, 210,
        3,   32,  16,  0,   209, 208, 1,   0,   0,   0,   209, 210, 1,   0,   0,   0,   210, 211,
        1,   0,   0,   0,   211, 238, 5,   33,  0,   0,   212, 238, 3,   26,  13,  0,   213, 214,
        5,   11,  0,   0,   214, 215, 5,   34,  0,   0,   215, 216, 3,   34,  17,  0,   216, 217,
        5,   35,  0,   0,   217, 220, 3,   30,  15,  0,   218, 219, 5,   12,  0,   0,   219, 221,
        3,   30,  15,  0,   220, 218, 1,   0,   0,   0,   220, 221, 1,   0,   0,   0,   221, 238,
        1,   0,   0,   0,   222, 223, 5,   13,  0,   0,   223, 224, 5,   34,  0,   0,   224, 225,
        3,   34,  17,  0,   225, 226, 5,   35,  0,   0,   226, 227, 3,   30,  15,  0,   227, 238,
        1,   0,   0,   0,   228, 229, 5,   14,  0,   0,   229, 238, 5,   33,  0,   0,   230, 231,
        5,   15,  0,   0,   231, 238, 5,   33,  0,   0,   232, 234, 5,   16,  0,   0,   233, 235,
        3,   32,  16,  0,   234, 233, 1,   0,   0,   0,   234, 235, 1,   0,   0,   0,   235, 236,
        1,   0,   0,   0,   236, 238, 5,   33,  0,   0,   237, 203, 1,   0,   0,   0,   237, 209,
        1,   0,   0,   0,   237, 212, 1,   0,   0,   0,   237, 213, 1,   0,   0,   0,   237, 222,
        1,   0,   0,   0,   237, 228, 1,   0,   0,   0,   237, 230, 1,   0,   0,   0,   237, 232,
        1,   0,   0,   0,   238, 31,  1,   0,   0,   0,   239, 240, 3,   56,  28,  0,   240, 33,
        1,   0,   0,   0,   241, 242, 3,   64,  32,  0,   242, 35,  1,   0,   0,   0,   243, 250,
        5,   40,  0,   0,   244, 245, 5,   36,  0,   0,   245, 246, 3,   32,  16,  0,   246, 247,
        5,   37,  0,   0,   247, 249, 1,   0,   0,   0,   248, 244, 1,   0,   0,   0,   249, 252,
        1,   0,   0,   0,   250, 248, 1,   0,   0,   0,   250, 251, 1,   0,   0,   0,   251, 37,
        1,   0,   0,   0,   252, 250, 1,   0,   0,   0,   253, 254, 5,   34,  0,   0,   254, 255,
        3,   32,  16,  0,   255, 256, 5,   35,  0,   0,   256, 260, 1,   0,   0,   0,   257, 260,
        3,   36,  18,  0,   258, 260, 3,   44,  22,  0,   259, 253, 1,   0,   0,   0,   259, 257,
        1,   0,   0,   0,   259, 258, 1,   0,   0,   0,   260, 39,  1,   0,   0,   0,   261, 265,
        5,   1,   0,   0,   262, 265, 5,   2,   0,   0,   263, 265, 5,   3,   0,   0,   264, 261,
        1,   0,   0,   0,   264, 262, 1,   0,   0,   0,   264, 263, 1,   0,   0,   0,   265, 41,
        1,   0,   0,   0,   266, 269, 5,   4,   0,   0,   267, 269, 5,   5,   0,   0,   268, 266,
        1,   0,   0,   0,   268, 267, 1,   0,   0,   0,   269, 43,  1,   0,   0,   0,   270, 273,
        3,   40,  20,  0,   271, 273, 3,   42,  21,  0,   272, 270, 1,   0,   0,   0,   272, 271,
        1,   0,   0,   0,   273, 45,  1,   0,   0,   0,   274, 288, 3,   38,  19,  0,   275, 276,
        5,   40,  0,   0,   276, 278, 5,   34,  0,   0,   277, 279, 3,   52,  26,  0,   278, 277,
        1,   0,   0,   0,   278, 279, 1,   0,   0,   0,   279, 280, 1,   0,   0,   0,   280, 288,
        5,   35,  0,   0,   281, 282, 5,   18,  0,   0,   282, 288, 3,   46,  23,  0,   283, 284,
        5,   19,  0,   0,   284, 288, 3,   46,  23,  0,   285, 286, 5,   29,  0,   0,   286, 288,
        3,   46,  23,  0,   287, 274, 1,   0,   0,   0,   287, 275, 1,   0,   0,   0,   287, 281,
        1,   0,   0,   0,   287, 283, 1,   0,   0,   0,   287, 285, 1,   0,   0,   0,   288, 47,
        1,   0,   0,   0,   289, 290, 5,   6,   0,   0,   290, 49,  1,   0,   0,   0,   291, 294,
        3,   32,  16,  0,   292, 294, 3,   48,  24,  0,   293, 291, 1,   0,   0,   0,   293, 292,
        1,   0,   0,   0,   294, 51,  1,   0,   0,   0,   295, 300, 3,   50,  25,  0,   296, 297,
        5,   32,  0,   0,   297, 299, 3,   50,  25,  0,   298, 296, 1,   0,   0,   0,   299, 302,
        1,   0,   0,   0,   300, 298, 1,   0,   0,   0,   300, 301, 1,   0,   0,   0,   301, 53,
        1,   0,   0,   0,   302, 300, 1,   0,   0,   0,   303, 304, 6,   27,  -1,  0,   304, 305,
        3,   46,  23,  0,   305, 317, 1,   0,   0,   0,   306, 307, 10,  3,   0,   0,   307, 308,
        5,   20,  0,   0,   308, 316, 3,   46,  23,  0,   309, 310, 10,  2,   0,   0,   310, 311,
        5,   21,  0,   0,   311, 316, 3,   46,  23,  0,   312, 313, 10,  1,   0,   0,   313, 314,
        5,   22,  0,   0,   314, 316, 3,   46,  23,  0,   315, 306, 1,   0,   0,   0,   315, 309,
        1,   0,   0,   0,   315, 312, 1,   0,   0,   0,   316, 319, 1,   0,   0,   0,   317, 315,
        1,   0,   0,   0,   317, 318, 1,   0,   0,   0,   318, 55,  1,   0,   0,   0,   319, 317,
        1,   0,   0,   0,   320, 321, 6,   28,  -1,  0,   321, 322, 3,   54,  27,  0,   322, 331,
        1,   0,   0,   0,   323, 324, 10,  2,   0,   0,   324, 325, 5,   18,  0,   0,   325, 330,
        3,   54,  27,  0,   326, 327, 10,  1,   0,   0,   327, 328, 5,   19,  0,   0,   328, 330,
        3,   54,  27,  0,   329, 323, 1,   0,   0,   0,   329, 326, 1,   0,   0,   0,   330, 333,
        1,   0,   0,   0,   331, 329, 1,   0,   0,   0,   331, 332, 1,   0,   0,   0,   332, 57,
        1,   0,   0,   0,   333, 331, 1,   0,   0,   0,   334, 335, 6,   29,  -1,  0,   335, 336,
        3,   56,  28,  0,   336, 351, 1,   0,   0,   0,   337, 338, 10,  4,   0,   0,   338, 339,
        5,   25,  0,   0,   339, 350, 3,   56,  28,  0,   340, 341, 10,  3,   0,   0,   341, 342,
        5,   26,  0,   0,   342, 350, 3,   56,  28,  0,   343, 344, 10,  2,   0,   0,   344, 345,
        5,   27,  0,   0,   345, 350, 3,   56,  28,  0,   346, 347, 10,  1,   0,   0,   347, 348,
        5,   28,  0,   0,   348, 350, 3,   56,  28,  0,   349, 337, 1,   0,   0,   0,   349, 340,
        1,   0,   0,   0,   349, 343, 1,   0,   0,   0,   349, 346, 1,   0,   0,   0,   350, 353,
        1,   0,   0,   0,   351, 349, 1,   0,   0,   0,   351, 352, 1,   0,   0,   0,   352, 59,
        1,   0,   0,   0,   353, 351, 1,   0,   0,   0,   354, 355, 6,   30,  -1,  0,   355, 356,
        3,   58,  29,  0,   356, 365, 1,   0,   0,   0,   357, 358, 10,  2,   0,   0,   358, 359,
        5,   23,  0,   0,   359, 364, 3,   58,  29,  0,   360, 361, 10,  1,   0,   0,   361, 362,
        5,   24,  0,   0,   362, 364, 3,   58,  29,  0,   363, 357, 1,   0,   0,   0,   363, 360,
        1,   0,   0,   0,   364, 367, 1,   0,   0,   0,   365, 363, 1,   0,   0,   0,   365, 366,
        1,   0,   0,   0,   366, 61,  1,   0,   0,   0,   367, 365, 1,   0,   0,   0,   368, 369,
        6,   31,  -1,  0,   369, 370, 3,   60,  30,  0,   370, 376, 1,   0,   0,   0,   371, 372,
        10,  1,   0,   0,   372, 373, 5,   30,  0,   0,   373, 375, 3,   60,  30,  0,   374, 371,
        1,   0,   0,   0,   375, 378, 1,   0,   0,   0,   376, 374, 1,   0,   0,   0,   376, 377,
        1,   0,   0,   0,   377, 63,  1,   0,   0,   0,   378, 376, 1,   0,   0,   0,   379, 380,
        6,   32,  -1,  0,   380, 381, 3,   62,  31,  0,   381, 387, 1,   0,   0,   0,   382, 383,
        10,  1,   0,   0,   383, 384, 5,   31,  0,   0,   384, 386, 3,   62,  31,  0,   385, 382,
        1,   0,   0,   0,   386, 389, 1,   0,   0,   0,   387, 385, 1,   0,   0,   0,   387, 388,
        1,   0,   0,   0,   388, 65,  1,   0,   0,   0,   389, 387, 1,   0,   0,   0,   42,  69,
        76,  80,  89,  96,  105, 117, 129, 134, 143, 146, 149, 155, 162, 169, 185, 188, 194, 201,
        209, 220, 234, 237, 250, 259, 264, 268, 272, 278, 287, 293, 300, 315, 317, 329, 331, 349,
        351, 363, 365, 376, 387};
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
    sysyParserStaticData = staticData.release();
}

}   // namespace

SysyParser::SysyParser(TokenStream* input)
    : SysyParser(input, antlr4::atn::ParserATNSimulatorOptions())
{
}

SysyParser::SysyParser(TokenStream* input, const antlr4::atn::ParserATNSimulatorOptions& options)
    : Parser(input)
{
    SysyParser::initialize();
    _interpreter = new atn::ParserATNSimulator(
        this,
        *sysyParserStaticData->atn,
        sysyParserStaticData->decisionToDFA,
        sysyParserStaticData->sharedContextCache,
        options
    );
}

SysyParser::~SysyParser()
{
    delete _interpreter;
}

const atn::ATN& SysyParser::getATN() const
{
    return *sysyParserStaticData->atn;
}

std::string SysyParser::getGrammarFileName() const
{
    return "Sysy.g4";
}

const std::vector<std::string>& SysyParser::getRuleNames() const
{
    return sysyParserStaticData->ruleNames;
}

const dfa::Vocabulary& SysyParser::getVocabulary() const
{
    return sysyParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysyParser::getSerializedATN() const
{
    return sysyParserStaticData->serializedATN;
}


//----------------- CompUnitContext
//------------------------------------------------------------------

SysyParser::CompUnitContext::CompUnitContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::CompUnitContext::EOF()
{
    return getToken(SysyParser::EOF, 0);
}

std::vector<SysyParser::CompUnitItemContext*> SysyParser::CompUnitContext::compUnitItem()
{
    return getRuleContexts<SysyParser::CompUnitItemContext>();
}

SysyParser::CompUnitItemContext* SysyParser::CompUnitContext::compUnitItem(size_t i)
{
    return getRuleContext<SysyParser::CompUnitItemContext>(i);
}


size_t SysyParser::CompUnitContext::getRuleIndex() const
{
    return SysyParser::RuleCompUnit;
}

void SysyParser::CompUnitContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCompUnit(this);
}

void SysyParser::CompUnitContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCompUnit(this);
}


std::any SysyParser::CompUnitContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitCompUnit(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::CompUnitContext* SysyParser::compUnit()
{
    CompUnitContext* _localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
    enterRule(_localctx, 0, SysyParser::RuleCompUnit);
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
        setState(69);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1920) != 0)) {
            setState(66);
            compUnitItem();
            setState(71);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(72);
        match(SysyParser::EOF);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- CompUnitItemContext
//------------------------------------------------------------------

SysyParser::CompUnitItemContext::CompUnitItemContext(
    ParserRuleContext* parent, size_t invokingState
)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::DeclContext* SysyParser::CompUnitItemContext::decl()
{
    return getRuleContext<SysyParser::DeclContext>(0);
}

SysyParser::FuncDefContext* SysyParser::CompUnitItemContext::funcDef()
{
    return getRuleContext<SysyParser::FuncDefContext>(0);
}


size_t SysyParser::CompUnitItemContext::getRuleIndex() const
{
    return SysyParser::RuleCompUnitItem;
}

void SysyParser::CompUnitItemContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCompUnitItem(this);
}

void SysyParser::CompUnitItemContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCompUnitItem(this);
}


std::any SysyParser::CompUnitItemContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitCompUnitItem(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::CompUnitItemContext* SysyParser::compUnitItem()
{
    CompUnitItemContext* _localctx = _tracker.createInstance<CompUnitItemContext>(_ctx, getState());
    enterRule(_localctx, 2, SysyParser::RuleCompUnitItem);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(76);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
            enterOuterAlt(_localctx, 1);
            setState(74);
            decl();
            break;
        }

        case 2: {
            enterOuterAlt(_localctx, 2);
            setState(75);
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

//----------------- DeclContext ------------------------------------------------------------------

SysyParser::DeclContext::DeclContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::ConstDeclContext* SysyParser::DeclContext::constDecl()
{
    return getRuleContext<SysyParser::ConstDeclContext>(0);
}

SysyParser::VarDeclContext* SysyParser::DeclContext::varDecl()
{
    return getRuleContext<SysyParser::VarDeclContext>(0);
}


size_t SysyParser::DeclContext::getRuleIndex() const
{
    return SysyParser::RuleDecl;
}

void SysyParser::DeclContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterDecl(this);
}

void SysyParser::DeclContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitDecl(this);
}


std::any SysyParser::DeclContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitDecl(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::DeclContext* SysyParser::decl()
{
    DeclContext* _localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
    enterRule(_localctx, 4, SysyParser::RuleDecl);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(80);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::Const: {
            enterOuterAlt(_localctx, 1);
            setState(78);
            constDecl();
            break;
        }

        case SysyParser::Int:
        case SysyParser::Float: {
            enterOuterAlt(_localctx, 2);
            setState(79);
            varDecl();
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

//----------------- ConstDeclContext
//------------------------------------------------------------------

SysyParser::ConstDeclContext::ConstDeclContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::ConstDeclContext::Const()
{
    return getToken(SysyParser::Const, 0);
}

SysyParser::BTypeContext* SysyParser::ConstDeclContext::bType()
{
    return getRuleContext<SysyParser::BTypeContext>(0);
}

std::vector<SysyParser::ConstDefContext*> SysyParser::ConstDeclContext::constDef()
{
    return getRuleContexts<SysyParser::ConstDefContext>();
}

SysyParser::ConstDefContext* SysyParser::ConstDeclContext::constDef(size_t i)
{
    return getRuleContext<SysyParser::ConstDefContext>(i);
}

tree::TerminalNode* SysyParser::ConstDeclContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

std::vector<tree::TerminalNode*> SysyParser::ConstDeclContext::Comma()
{
    return getTokens(SysyParser::Comma);
}

tree::TerminalNode* SysyParser::ConstDeclContext::Comma(size_t i)
{
    return getToken(SysyParser::Comma, i);
}


size_t SysyParser::ConstDeclContext::getRuleIndex() const
{
    return SysyParser::RuleConstDecl;
}

void SysyParser::ConstDeclContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterConstDecl(this);
}

void SysyParser::ConstDeclContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitConstDecl(this);
}


std::any SysyParser::ConstDeclContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitConstDecl(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::ConstDeclContext* SysyParser::constDecl()
{
    ConstDeclContext* _localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
    enterRule(_localctx, 6, SysyParser::RuleConstDecl);
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
        setState(82);
        match(SysyParser::Const);
        setState(83);
        bType();
        setState(84);
        constDef();
        setState(89);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Comma) {
            setState(85);
            match(SysyParser::Comma);
            setState(86);
            constDef();
            setState(91);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(92);
        match(SysyParser::Semicolon);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

SysyParser::BTypeContext::BTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::BTypeContext::getRuleIndex() const
{
    return SysyParser::RuleBType;
}

void SysyParser::BTypeContext::copyFrom(BTypeContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::FloatContext::Float()
{
    return getToken(SysyParser::Float, 0);
}

SysyParser::FloatContext::FloatContext(BTypeContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::FloatContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFloat(this);
}

void SysyParser::FloatContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFloat(this);
}

std::any SysyParser::FloatContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFloat(this);
    else
        return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::IntContext::Int()
{
    return getToken(SysyParser::Int, 0);
}

SysyParser::IntContext::IntContext(BTypeContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::IntContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterInt(this);
}

void SysyParser::IntContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitInt(this);
}

std::any SysyParser::IntContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitInt(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::BTypeContext* SysyParser::bType()
{
    BTypeContext* _localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
    enterRule(_localctx, 8, SysyParser::RuleBType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(96);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::Int: {
            _localctx = _tracker.createInstance<SysyParser::IntContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(94);
            match(SysyParser::Int);
            break;
        }

        case SysyParser::Float: {
            _localctx = _tracker.createInstance<SysyParser::FloatContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(95);
            match(SysyParser::Float);
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

//----------------- ConstDefContext
//------------------------------------------------------------------

SysyParser::ConstDefContext::ConstDefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::ConstDefContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

tree::TerminalNode* SysyParser::ConstDefContext::Assign()
{
    return getToken(SysyParser::Assign, 0);
}

SysyParser::InitValContext* SysyParser::ConstDefContext::initVal()
{
    return getRuleContext<SysyParser::InitValContext>(0);
}

std::vector<tree::TerminalNode*> SysyParser::ConstDefContext::Lbracket()
{
    return getTokens(SysyParser::Lbracket);
}

tree::TerminalNode* SysyParser::ConstDefContext::Lbracket(size_t i)
{
    return getToken(SysyParser::Lbracket, i);
}

std::vector<SysyParser::ExpContext*> SysyParser::ConstDefContext::exp()
{
    return getRuleContexts<SysyParser::ExpContext>();
}

SysyParser::ExpContext* SysyParser::ConstDefContext::exp(size_t i)
{
    return getRuleContext<SysyParser::ExpContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::ConstDefContext::Rbracket()
{
    return getTokens(SysyParser::Rbracket);
}

tree::TerminalNode* SysyParser::ConstDefContext::Rbracket(size_t i)
{
    return getToken(SysyParser::Rbracket, i);
}


size_t SysyParser::ConstDefContext::getRuleIndex() const
{
    return SysyParser::RuleConstDef;
}

void SysyParser::ConstDefContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterConstDef(this);
}

void SysyParser::ConstDefContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitConstDef(this);
}


std::any SysyParser::ConstDefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitConstDef(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::ConstDefContext* SysyParser::constDef()
{
    ConstDefContext* _localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
    enterRule(_localctx, 10, SysyParser::RuleConstDef);
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
        setState(98);
        match(SysyParser::Ident);
        setState(105);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Lbracket) {
            setState(99);
            match(SysyParser::Lbracket);
            setState(100);
            exp();
            setState(101);
            match(SysyParser::Rbracket);
            setState(107);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(108);
        match(SysyParser::Assign);
        setState(109);
        initVal();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VarDeclContext
//------------------------------------------------------------------

SysyParser::VarDeclContext::VarDeclContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::BTypeContext* SysyParser::VarDeclContext::bType()
{
    return getRuleContext<SysyParser::BTypeContext>(0);
}

std::vector<SysyParser::VarDefContext*> SysyParser::VarDeclContext::varDef()
{
    return getRuleContexts<SysyParser::VarDefContext>();
}

SysyParser::VarDefContext* SysyParser::VarDeclContext::varDef(size_t i)
{
    return getRuleContext<SysyParser::VarDefContext>(i);
}

tree::TerminalNode* SysyParser::VarDeclContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

std::vector<tree::TerminalNode*> SysyParser::VarDeclContext::Comma()
{
    return getTokens(SysyParser::Comma);
}

tree::TerminalNode* SysyParser::VarDeclContext::Comma(size_t i)
{
    return getToken(SysyParser::Comma, i);
}


size_t SysyParser::VarDeclContext::getRuleIndex() const
{
    return SysyParser::RuleVarDecl;
}

void SysyParser::VarDeclContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterVarDecl(this);
}

void SysyParser::VarDeclContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitVarDecl(this);
}


std::any SysyParser::VarDeclContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitVarDecl(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::VarDeclContext* SysyParser::varDecl()
{
    VarDeclContext* _localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
    enterRule(_localctx, 12, SysyParser::RuleVarDecl);
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
        setState(111);
        bType();
        setState(112);
        varDef();
        setState(117);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Comma) {
            setState(113);
            match(SysyParser::Comma);
            setState(114);
            varDef();
            setState(119);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(120);
        match(SysyParser::Semicolon);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

SysyParser::VarDefContext::VarDefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::VarDefContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

std::vector<tree::TerminalNode*> SysyParser::VarDefContext::Lbracket()
{
    return getTokens(SysyParser::Lbracket);
}

tree::TerminalNode* SysyParser::VarDefContext::Lbracket(size_t i)
{
    return getToken(SysyParser::Lbracket, i);
}

std::vector<SysyParser::ExpContext*> SysyParser::VarDefContext::exp()
{
    return getRuleContexts<SysyParser::ExpContext>();
}

SysyParser::ExpContext* SysyParser::VarDefContext::exp(size_t i)
{
    return getRuleContext<SysyParser::ExpContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::VarDefContext::Rbracket()
{
    return getTokens(SysyParser::Rbracket);
}

tree::TerminalNode* SysyParser::VarDefContext::Rbracket(size_t i)
{
    return getToken(SysyParser::Rbracket, i);
}

tree::TerminalNode* SysyParser::VarDefContext::Assign()
{
    return getToken(SysyParser::Assign, 0);
}

SysyParser::InitValContext* SysyParser::VarDefContext::initVal()
{
    return getRuleContext<SysyParser::InitValContext>(0);
}


size_t SysyParser::VarDefContext::getRuleIndex() const
{
    return SysyParser::RuleVarDef;
}

void SysyParser::VarDefContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterVarDef(this);
}

void SysyParser::VarDefContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitVarDef(this);
}


std::any SysyParser::VarDefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitVarDef(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::VarDefContext* SysyParser::varDef()
{
    VarDefContext* _localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
    enterRule(_localctx, 14, SysyParser::RuleVarDef);
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
        setState(122);
        match(SysyParser::Ident);
        setState(129);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Lbracket) {
            setState(123);
            match(SysyParser::Lbracket);
            setState(124);
            exp();
            setState(125);
            match(SysyParser::Rbracket);
            setState(131);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(134);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SysyParser::Assign) {
            setState(132);
            match(SysyParser::Assign);
            setState(133);
            initVal();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- InitValContext
//------------------------------------------------------------------

SysyParser::InitValContext::InitValContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::InitValContext::getRuleIndex() const
{
    return SysyParser::RuleInitVal;
}

void SysyParser::InitValContext::copyFrom(InitValContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- InitContext ------------------------------------------------------------------

SysyParser::ExpContext* SysyParser::InitContext::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

SysyParser::InitContext::InitContext(InitValContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::InitContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterInit(this);
}

void SysyParser::InitContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitInit(this);
}

std::any SysyParser::InitContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitInit(this);
    else
        return visitor->visitChildren(this);
}
//----------------- InitListContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::InitListContext::Lbrace()
{
    return getToken(SysyParser::Lbrace, 0);
}

tree::TerminalNode* SysyParser::InitListContext::Rbrace()
{
    return getToken(SysyParser::Rbrace, 0);
}

std::vector<SysyParser::InitValContext*> SysyParser::InitListContext::initVal()
{
    return getRuleContexts<SysyParser::InitValContext>();
}

SysyParser::InitValContext* SysyParser::InitListContext::initVal(size_t i)
{
    return getRuleContext<SysyParser::InitValContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::InitListContext::Comma()
{
    return getTokens(SysyParser::Comma);
}

tree::TerminalNode* SysyParser::InitListContext::Comma(size_t i)
{
    return getToken(SysyParser::Comma, i);
}

SysyParser::InitListContext::InitListContext(InitValContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::InitListContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterInitList(this);
}

void SysyParser::InitListContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitInitList(this);
}

std::any SysyParser::InitListContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitInitList(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::InitValContext* SysyParser::initVal()
{
    InitValContext* _localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
    enterRule(_localctx, 16, SysyParser::RuleInitVal);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(149);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::DecIntConst:
        case SysyParser::OctIntConst:
        case SysyParser::HexIntConst:
        case SysyParser::DecFloatConst:
        case SysyParser::HexFloatConst:
        case SysyParser::Add:
        case SysyParser::Sub:
        case SysyParser::Not:
        case SysyParser::Lparen:
        case SysyParser::Ident: {
            _localctx = _tracker.createInstance<SysyParser::InitContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(136);
            exp();
            break;
        }

        case SysyParser::Lbrace: {
            _localctx = _tracker.createInstance<SysyParser::InitListContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(137);
            match(SysyParser::Lbrace);
            setState(146);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1392107061310) != 0)) {
                setState(138);
                initVal();
                setState(143);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (_la == SysyParser::Comma) {
                    setState(139);
                    match(SysyParser::Comma);
                    setState(140);
                    initVal();
                    setState(145);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
            }
            setState(148);
            match(SysyParser::Rbrace);
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

//----------------- FuncDefContext
//------------------------------------------------------------------

SysyParser::FuncDefContext::FuncDefContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::FuncTypeContext* SysyParser::FuncDefContext::funcType()
{
    return getRuleContext<SysyParser::FuncTypeContext>(0);
}

tree::TerminalNode* SysyParser::FuncDefContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

tree::TerminalNode* SysyParser::FuncDefContext::Lparen()
{
    return getToken(SysyParser::Lparen, 0);
}

tree::TerminalNode* SysyParser::FuncDefContext::Rparen()
{
    return getToken(SysyParser::Rparen, 0);
}

SysyParser::BlockContext* SysyParser::FuncDefContext::block()
{
    return getRuleContext<SysyParser::BlockContext>(0);
}

SysyParser::FuncFParamsContext* SysyParser::FuncDefContext::funcFParams()
{
    return getRuleContext<SysyParser::FuncFParamsContext>(0);
}


size_t SysyParser::FuncDefContext::getRuleIndex() const
{
    return SysyParser::RuleFuncDef;
}

void SysyParser::FuncDefContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncDef(this);
}

void SysyParser::FuncDefContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncDef(this);
}


std::any SysyParser::FuncDefContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFuncDef(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncDefContext* SysyParser::funcDef()
{
    FuncDefContext* _localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
    enterRule(_localctx, 18, SysyParser::RuleFuncDef);
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
        setState(151);
        funcType();
        setState(152);
        match(SysyParser::Ident);
        setState(153);
        match(SysyParser::Lparen);
        setState(155);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == SysyParser::Int

            || _la == SysyParser::Float) {
            setState(154);
            funcFParams();
        }
        setState(157);
        match(SysyParser::Rparen);
        setState(158);
        block();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncTypeContext
//------------------------------------------------------------------

SysyParser::FuncTypeContext::FuncTypeContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::FuncTypeContext::getRuleIndex() const
{
    return SysyParser::RuleFuncType;
}

void SysyParser::FuncTypeContext::copyFrom(FuncTypeContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncType_Context
//------------------------------------------------------------------

SysyParser::BTypeContext* SysyParser::FuncType_Context::bType()
{
    return getRuleContext<SysyParser::BTypeContext>(0);
}

SysyParser::FuncType_Context::FuncType_Context(FuncTypeContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::FuncType_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncType_(this);
}

void SysyParser::FuncType_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncType_(this);
}

std::any SysyParser::FuncType_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFuncType_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- VoidContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::VoidContext::Void()
{
    return getToken(SysyParser::Void, 0);
}

SysyParser::VoidContext::VoidContext(FuncTypeContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::VoidContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterVoid(this);
}

void SysyParser::VoidContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitVoid(this);
}

std::any SysyParser::VoidContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitVoid(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncTypeContext* SysyParser::funcType()
{
    FuncTypeContext* _localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
    enterRule(_localctx, 20, SysyParser::RuleFuncType);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(162);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::Int:
        case SysyParser::Float: {
            _localctx = _tracker.createInstance<SysyParser::FuncType_Context>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(160);
            bType();
            break;
        }

        case SysyParser::Void: {
            _localctx = _tracker.createInstance<SysyParser::VoidContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(161);
            match(SysyParser::Void);
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

//----------------- FuncFParamsContext
//------------------------------------------------------------------

SysyParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<SysyParser::FuncFParamContext*> SysyParser::FuncFParamsContext::funcFParam()
{
    return getRuleContexts<SysyParser::FuncFParamContext>();
}

SysyParser::FuncFParamContext* SysyParser::FuncFParamsContext::funcFParam(size_t i)
{
    return getRuleContext<SysyParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::FuncFParamsContext::Comma()
{
    return getTokens(SysyParser::Comma);
}

tree::TerminalNode* SysyParser::FuncFParamsContext::Comma(size_t i)
{
    return getToken(SysyParser::Comma, i);
}


size_t SysyParser::FuncFParamsContext::getRuleIndex() const
{
    return SysyParser::RuleFuncFParams;
}

void SysyParser::FuncFParamsContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncFParams(this);
}

void SysyParser::FuncFParamsContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncFParams(this);
}


std::any SysyParser::FuncFParamsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFuncFParams(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncFParamsContext* SysyParser::funcFParams()
{
    FuncFParamsContext* _localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
    enterRule(_localctx, 22, SysyParser::RuleFuncFParams);
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
        setState(164);
        funcFParam();
        setState(169);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Comma) {
            setState(165);
            match(SysyParser::Comma);
            setState(166);
            funcFParam();
            setState(171);
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

//----------------- FuncFParamContext
//------------------------------------------------------------------

SysyParser::FuncFParamContext::FuncFParamContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::FuncFParamContext::getRuleIndex() const
{
    return SysyParser::RuleFuncFParam;
}

void SysyParser::FuncFParamContext::copyFrom(FuncFParamContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- ScalarParamContext
//------------------------------------------------------------------

SysyParser::BTypeContext* SysyParser::ScalarParamContext::bType()
{
    return getRuleContext<SysyParser::BTypeContext>(0);
}

tree::TerminalNode* SysyParser::ScalarParamContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

SysyParser::ScalarParamContext::ScalarParamContext(FuncFParamContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ScalarParamContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterScalarParam(this);
}

void SysyParser::ScalarParamContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitScalarParam(this);
}

std::any SysyParser::ScalarParamContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitScalarParam(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ArrayParamContext
//------------------------------------------------------------------

SysyParser::BTypeContext* SysyParser::ArrayParamContext::bType()
{
    return getRuleContext<SysyParser::BTypeContext>(0);
}

tree::TerminalNode* SysyParser::ArrayParamContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

std::vector<tree::TerminalNode*> SysyParser::ArrayParamContext::Lbracket()
{
    return getTokens(SysyParser::Lbracket);
}

tree::TerminalNode* SysyParser::ArrayParamContext::Lbracket(size_t i)
{
    return getToken(SysyParser::Lbracket, i);
}

std::vector<tree::TerminalNode*> SysyParser::ArrayParamContext::Rbracket()
{
    return getTokens(SysyParser::Rbracket);
}

tree::TerminalNode* SysyParser::ArrayParamContext::Rbracket(size_t i)
{
    return getToken(SysyParser::Rbracket, i);
}

std::vector<SysyParser::ExpContext*> SysyParser::ArrayParamContext::exp()
{
    return getRuleContexts<SysyParser::ExpContext>();
}

SysyParser::ExpContext* SysyParser::ArrayParamContext::exp(size_t i)
{
    return getRuleContext<SysyParser::ExpContext>(i);
}

SysyParser::ArrayParamContext::ArrayParamContext(FuncFParamContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ArrayParamContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterArrayParam(this);
}

void SysyParser::ArrayParamContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitArrayParam(this);
}

std::any SysyParser::ArrayParamContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitArrayParam(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncFParamContext* SysyParser::funcFParam()
{
    FuncFParamContext* _localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
    enterRule(_localctx, 24, SysyParser::RuleFuncFParam);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(188);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
            _localctx = _tracker.createInstance<SysyParser::ScalarParamContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(172);
            bType();
            setState(173);
            match(SysyParser::Ident);
            break;
        }

        case 2: {
            _localctx = _tracker.createInstance<SysyParser::ArrayParamContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(175);
            bType();
            setState(176);
            match(SysyParser::Ident);
            setState(177);
            match(SysyParser::Lbracket);
            setState(178);
            match(SysyParser::Rbracket);
            setState(185);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == SysyParser::Lbracket) {
                setState(179);
                match(SysyParser::Lbracket);
                setState(180);
                exp();
                setState(181);
                match(SysyParser::Rbracket);
                setState(187);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
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

//----------------- BlockContext ------------------------------------------------------------------

SysyParser::BlockContext::BlockContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::BlockContext::Lbrace()
{
    return getToken(SysyParser::Lbrace, 0);
}

tree::TerminalNode* SysyParser::BlockContext::Rbrace()
{
    return getToken(SysyParser::Rbrace, 0);
}

std::vector<SysyParser::BlockItemContext*> SysyParser::BlockContext::blockItem()
{
    return getRuleContexts<SysyParser::BlockItemContext>();
}

SysyParser::BlockItemContext* SysyParser::BlockContext::blockItem(size_t i)
{
    return getRuleContext<SysyParser::BlockItemContext>(i);
}


size_t SysyParser::BlockContext::getRuleIndex() const
{
    return SysyParser::RuleBlock;
}

void SysyParser::BlockContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBlock(this);
}

void SysyParser::BlockContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBlock(this);
}


std::any SysyParser::BlockContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitBlock(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::BlockContext* SysyParser::block()
{
    BlockContext* _localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
    enterRule(_localctx, 26, SysyParser::RuleBlock);
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
        setState(190);
        match(SysyParser::Lbrace);
        setState(194);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1400697122238) != 0)) {
            setState(191);
            blockItem();
            setState(196);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(197);
        match(SysyParser::Rbrace);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BlockItemContext
//------------------------------------------------------------------

SysyParser::BlockItemContext::BlockItemContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::DeclContext* SysyParser::BlockItemContext::decl()
{
    return getRuleContext<SysyParser::DeclContext>(0);
}

SysyParser::StmtContext* SysyParser::BlockItemContext::stmt()
{
    return getRuleContext<SysyParser::StmtContext>(0);
}


size_t SysyParser::BlockItemContext::getRuleIndex() const
{
    return SysyParser::RuleBlockItem;
}

void SysyParser::BlockItemContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBlockItem(this);
}

void SysyParser::BlockItemContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBlockItem(this);
}


std::any SysyParser::BlockItemContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitBlockItem(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::BlockItemContext* SysyParser::blockItem()
{
    BlockItemContext* _localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
    enterRule(_localctx, 28, SysyParser::RuleBlockItem);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(201);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::Int:
        case SysyParser::Float:
        case SysyParser::Const: {
            enterOuterAlt(_localctx, 1);
            setState(199);
            decl();
            break;
        }

        case SysyParser::DecIntConst:
        case SysyParser::OctIntConst:
        case SysyParser::HexIntConst:
        case SysyParser::DecFloatConst:
        case SysyParser::HexFloatConst:
        case SysyParser::If:
        case SysyParser::While:
        case SysyParser::Break:
        case SysyParser::Continue:
        case SysyParser::Return:
        case SysyParser::Add:
        case SysyParser::Sub:
        case SysyParser::Not:
        case SysyParser::Semicolon:
        case SysyParser::Lparen:
        case SysyParser::Lbrace:
        case SysyParser::Ident: {
            enterOuterAlt(_localctx, 2);
            setState(200);
            stmt();
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

//----------------- StmtContext ------------------------------------------------------------------

SysyParser::StmtContext::StmtContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::StmtContext::getRuleIndex() const
{
    return SysyParser::RuleStmt;
}

void SysyParser::StmtContext::copyFrom(StmtContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprStmtContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::ExprStmtContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

SysyParser::ExpContext* SysyParser::ExprStmtContext::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

SysyParser::ExprStmtContext::ExprStmtContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ExprStmtContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterExprStmt(this);
}

void SysyParser::ExprStmtContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitExprStmt(this);
}

std::any SysyParser::ExprStmtContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitExprStmt(this);
    else
        return visitor->visitChildren(this);
}
//----------------- BlockStmtContext
//------------------------------------------------------------------

SysyParser::BlockContext* SysyParser::BlockStmtContext::block()
{
    return getRuleContext<SysyParser::BlockContext>(0);
}

SysyParser::BlockStmtContext::BlockStmtContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::BlockStmtContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBlockStmt(this);
}

void SysyParser::BlockStmtContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBlockStmt(this);
}

std::any SysyParser::BlockStmtContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitBlockStmt(this);
    else
        return visitor->visitChildren(this);
}
//----------------- BreakContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::BreakContext::Break()
{
    return getToken(SysyParser::Break, 0);
}

tree::TerminalNode* SysyParser::BreakContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

SysyParser::BreakContext::BreakContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::BreakContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterBreak(this);
}

void SysyParser::BreakContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitBreak(this);
}

std::any SysyParser::BreakContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitBreak(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ContinueContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::ContinueContext::Continue()
{
    return getToken(SysyParser::Continue, 0);
}

tree::TerminalNode* SysyParser::ContinueContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

SysyParser::ContinueContext::ContinueContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ContinueContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterContinue(this);
}

void SysyParser::ContinueContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitContinue(this);
}

std::any SysyParser::ContinueContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitContinue(this);
    else
        return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::WhileContext::While()
{
    return getToken(SysyParser::While, 0);
}

tree::TerminalNode* SysyParser::WhileContext::Lparen()
{
    return getToken(SysyParser::Lparen, 0);
}

SysyParser::CondContext* SysyParser::WhileContext::cond()
{
    return getRuleContext<SysyParser::CondContext>(0);
}

tree::TerminalNode* SysyParser::WhileContext::Rparen()
{
    return getToken(SysyParser::Rparen, 0);
}

SysyParser::StmtContext* SysyParser::WhileContext::stmt()
{
    return getRuleContext<SysyParser::StmtContext>(0);
}

SysyParser::WhileContext::WhileContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::WhileContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterWhile(this);
}

void SysyParser::WhileContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitWhile(this);
}

std::any SysyParser::WhileContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitWhile(this);
    else
        return visitor->visitChildren(this);
}
//----------------- IfElseContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::IfElseContext::If()
{
    return getToken(SysyParser::If, 0);
}

tree::TerminalNode* SysyParser::IfElseContext::Lparen()
{
    return getToken(SysyParser::Lparen, 0);
}

SysyParser::CondContext* SysyParser::IfElseContext::cond()
{
    return getRuleContext<SysyParser::CondContext>(0);
}

tree::TerminalNode* SysyParser::IfElseContext::Rparen()
{
    return getToken(SysyParser::Rparen, 0);
}

std::vector<SysyParser::StmtContext*> SysyParser::IfElseContext::stmt()
{
    return getRuleContexts<SysyParser::StmtContext>();
}

SysyParser::StmtContext* SysyParser::IfElseContext::stmt(size_t i)
{
    return getRuleContext<SysyParser::StmtContext>(i);
}

tree::TerminalNode* SysyParser::IfElseContext::Else()
{
    return getToken(SysyParser::Else, 0);
}

SysyParser::IfElseContext::IfElseContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::IfElseContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterIfElse(this);
}

void SysyParser::IfElseContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitIfElse(this);
}

std::any SysyParser::IfElseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitIfElse(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ReturnContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::ReturnContext::Return()
{
    return getToken(SysyParser::Return, 0);
}

tree::TerminalNode* SysyParser::ReturnContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

SysyParser::ExpContext* SysyParser::ReturnContext::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

SysyParser::ReturnContext::ReturnContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ReturnContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterReturn(this);
}

void SysyParser::ReturnContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitReturn(this);
}

std::any SysyParser::ReturnContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitReturn(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AssignContext ------------------------------------------------------------------

SysyParser::LValContext* SysyParser::AssignContext::lVal()
{
    return getRuleContext<SysyParser::LValContext>(0);
}

tree::TerminalNode* SysyParser::AssignContext::Assign()
{
    return getToken(SysyParser::Assign, 0);
}

SysyParser::ExpContext* SysyParser::AssignContext::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

tree::TerminalNode* SysyParser::AssignContext::Semicolon()
{
    return getToken(SysyParser::Semicolon, 0);
}

SysyParser::AssignContext::AssignContext(StmtContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::AssignContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAssign(this);
}

void SysyParser::AssignContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAssign(this);
}

std::any SysyParser::AssignContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitAssign(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::StmtContext* SysyParser::stmt()
{
    StmtContext* _localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
    enterRule(_localctx, 30, SysyParser::RuleStmt);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(237);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
        case 1: {
            _localctx = _tracker.createInstance<SysyParser::AssignContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(203);
            lVal();
            setState(204);
            match(SysyParser::Assign);
            setState(205);
            exp();
            setState(206);
            match(SysyParser::Semicolon);
            break;
        }

        case 2: {
            _localctx = _tracker.createInstance<SysyParser::ExprStmtContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(209);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1117229154366) != 0)) {
                setState(208);
                exp();
            }
            setState(211);
            match(SysyParser::Semicolon);
            break;
        }

        case 3: {
            _localctx = _tracker.createInstance<SysyParser::BlockStmtContext>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(212);
            block();
            break;
        }

        case 4: {
            _localctx = _tracker.createInstance<SysyParser::IfElseContext>(_localctx);
            enterOuterAlt(_localctx, 4);
            setState(213);
            match(SysyParser::If);
            setState(214);
            match(SysyParser::Lparen);
            setState(215);
            cond();
            setState(216);
            match(SysyParser::Rparen);
            setState(217);
            stmt();
            setState(220);
            _errHandler->sync(this);

            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
            case 1: {
                setState(218);
                match(SysyParser::Else);
                setState(219);
                stmt();
                break;
            }

            default: break;
            }
            break;
        }

        case 5: {
            _localctx = _tracker.createInstance<SysyParser::WhileContext>(_localctx);
            enterOuterAlt(_localctx, 5);
            setState(222);
            match(SysyParser::While);
            setState(223);
            match(SysyParser::Lparen);
            setState(224);
            cond();
            setState(225);
            match(SysyParser::Rparen);
            setState(226);
            stmt();
            break;
        }

        case 6: {
            _localctx = _tracker.createInstance<SysyParser::BreakContext>(_localctx);
            enterOuterAlt(_localctx, 6);
            setState(228);
            match(SysyParser::Break);
            setState(229);
            match(SysyParser::Semicolon);
            break;
        }

        case 7: {
            _localctx = _tracker.createInstance<SysyParser::ContinueContext>(_localctx);
            enterOuterAlt(_localctx, 7);
            setState(230);
            match(SysyParser::Continue);
            setState(231);
            match(SysyParser::Semicolon);
            break;
        }

        case 8: {
            _localctx = _tracker.createInstance<SysyParser::ReturnContext>(_localctx);
            enterOuterAlt(_localctx, 8);
            setState(232);
            match(SysyParser::Return);
            setState(234);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1117229154366) != 0)) {
                setState(233);
                exp();
            }
            setState(236);
            match(SysyParser::Semicolon);
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

//----------------- ExpContext ------------------------------------------------------------------

SysyParser::ExpContext::ExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::AddExpContext* SysyParser::ExpContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}


size_t SysyParser::ExpContext::getRuleIndex() const
{
    return SysyParser::RuleExp;
}

void SysyParser::ExpContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterExp(this);
}

void SysyParser::ExpContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitExp(this);
}


std::any SysyParser::ExpContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitExp(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::ExpContext* SysyParser::exp()
{
    ExpContext* _localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
    enterRule(_localctx, 32, SysyParser::RuleExp);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(239);
        addExp(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

SysyParser::CondContext::CondContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::LOrExpContext* SysyParser::CondContext::lOrExp()
{
    return getRuleContext<SysyParser::LOrExpContext>(0);
}


size_t SysyParser::CondContext::getRuleIndex() const
{
    return SysyParser::RuleCond;
}

void SysyParser::CondContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCond(this);
}

void SysyParser::CondContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCond(this);
}


std::any SysyParser::CondContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitCond(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::CondContext* SysyParser::cond()
{
    CondContext* _localctx = _tracker.createInstance<CondContext>(_ctx, getState());
    enterRule(_localctx, 34, SysyParser::RuleCond);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(241);
        lOrExp(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

SysyParser::LValContext::LValContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::LValContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

std::vector<tree::TerminalNode*> SysyParser::LValContext::Lbracket()
{
    return getTokens(SysyParser::Lbracket);
}

tree::TerminalNode* SysyParser::LValContext::Lbracket(size_t i)
{
    return getToken(SysyParser::Lbracket, i);
}

std::vector<SysyParser::ExpContext*> SysyParser::LValContext::exp()
{
    return getRuleContexts<SysyParser::ExpContext>();
}

SysyParser::ExpContext* SysyParser::LValContext::exp(size_t i)
{
    return getRuleContext<SysyParser::ExpContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::LValContext::Rbracket()
{
    return getTokens(SysyParser::Rbracket);
}

tree::TerminalNode* SysyParser::LValContext::Rbracket(size_t i)
{
    return getToken(SysyParser::Rbracket, i);
}


size_t SysyParser::LValContext::getRuleIndex() const
{
    return SysyParser::RuleLVal;
}

void SysyParser::LValContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLVal(this);
}

void SysyParser::LValContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLVal(this);
}


std::any SysyParser::LValContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLVal(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::LValContext* SysyParser::lVal()
{
    LValContext* _localctx = _tracker.createInstance<LValContext>(_ctx, getState());
    enterRule(_localctx, 36, SysyParser::RuleLVal);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(243);
        match(SysyParser::Ident);
        setState(250);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(244);
                match(SysyParser::Lbracket);
                setState(245);
                exp();
                setState(246);
                match(SysyParser::Rbracket);
            }
            setState(252);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PrimaryExpContext
//------------------------------------------------------------------

SysyParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::PrimaryExpContext::getRuleIndex() const
{
    return SysyParser::RulePrimaryExp;
}

void SysyParser::PrimaryExpContext::copyFrom(PrimaryExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- PrimaryExp_Context
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::PrimaryExp_Context::Lparen()
{
    return getToken(SysyParser::Lparen, 0);
}

SysyParser::ExpContext* SysyParser::PrimaryExp_Context::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

tree::TerminalNode* SysyParser::PrimaryExp_Context::Rparen()
{
    return getToken(SysyParser::Rparen, 0);
}

SysyParser::NumberContext* SysyParser::PrimaryExp_Context::number()
{
    return getRuleContext<SysyParser::NumberContext>(0);
}

SysyParser::PrimaryExp_Context::PrimaryExp_Context(PrimaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::PrimaryExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterPrimaryExp_(this);
}

void SysyParser::PrimaryExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitPrimaryExp_(this);
}

std::any SysyParser::PrimaryExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitPrimaryExp_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LValExprContext
//------------------------------------------------------------------

SysyParser::LValContext* SysyParser::LValExprContext::lVal()
{
    return getRuleContext<SysyParser::LValContext>(0);
}

SysyParser::LValExprContext::LValExprContext(PrimaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::LValExprContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLValExpr(this);
}

void SysyParser::LValExprContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLValExpr(this);
}

std::any SysyParser::LValExprContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLValExpr(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::PrimaryExpContext* SysyParser::primaryExp()
{
    PrimaryExpContext* _localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
    enterRule(_localctx, 38, SysyParser::RulePrimaryExp);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(259);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::Lparen: {
            _localctx = _tracker.createInstance<SysyParser::PrimaryExp_Context>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(253);
            match(SysyParser::Lparen);
            setState(254);
            exp();
            setState(255);
            match(SysyParser::Rparen);
            break;
        }

        case SysyParser::Ident: {
            _localctx = _tracker.createInstance<SysyParser::LValExprContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(257);
            lVal();
            break;
        }

        case SysyParser::DecIntConst:
        case SysyParser::OctIntConst:
        case SysyParser::HexIntConst:
        case SysyParser::DecFloatConst:
        case SysyParser::HexFloatConst: {
            _localctx = _tracker.createInstance<SysyParser::PrimaryExp_Context>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(258);
            number();
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

//----------------- IntConstContext
//------------------------------------------------------------------

SysyParser::IntConstContext::IntConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::IntConstContext::getRuleIndex() const
{
    return SysyParser::RuleIntConst;
}

void SysyParser::IntConstContext::copyFrom(IntConstContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- HexIntConstContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::HexIntConstContext::HexIntConst()
{
    return getToken(SysyParser::HexIntConst, 0);
}

SysyParser::HexIntConstContext::HexIntConstContext(IntConstContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::HexIntConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterHexIntConst(this);
}

void SysyParser::HexIntConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitHexIntConst(this);
}

std::any SysyParser::HexIntConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitHexIntConst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- DecIntConstContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::DecIntConstContext::DecIntConst()
{
    return getToken(SysyParser::DecIntConst, 0);
}

SysyParser::DecIntConstContext::DecIntConstContext(IntConstContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::DecIntConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterDecIntConst(this);
}

void SysyParser::DecIntConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitDecIntConst(this);
}

std::any SysyParser::DecIntConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitDecIntConst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- OctIntConstContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::OctIntConstContext::OctIntConst()
{
    return getToken(SysyParser::OctIntConst, 0);
}

SysyParser::OctIntConstContext::OctIntConstContext(IntConstContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::OctIntConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterOctIntConst(this);
}

void SysyParser::OctIntConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitOctIntConst(this);
}

std::any SysyParser::OctIntConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitOctIntConst(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::IntConstContext* SysyParser::intConst()
{
    IntConstContext* _localctx = _tracker.createInstance<IntConstContext>(_ctx, getState());
    enterRule(_localctx, 40, SysyParser::RuleIntConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(264);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::DecIntConst: {
            _localctx = _tracker.createInstance<SysyParser::DecIntConstContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(261);
            match(SysyParser::DecIntConst);
            break;
        }

        case SysyParser::OctIntConst: {
            _localctx = _tracker.createInstance<SysyParser::OctIntConstContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(262);
            match(SysyParser::OctIntConst);
            break;
        }

        case SysyParser::HexIntConst: {
            _localctx = _tracker.createInstance<SysyParser::HexIntConstContext>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(263);
            match(SysyParser::HexIntConst);
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

//----------------- FloatConstContext
//------------------------------------------------------------------

SysyParser::FloatConstContext::FloatConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::FloatConstContext::getRuleIndex() const
{
    return SysyParser::RuleFloatConst;
}

void SysyParser::FloatConstContext::copyFrom(FloatConstContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- DecFloatConstContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::DecFloatConstContext::DecFloatConst()
{
    return getToken(SysyParser::DecFloatConst, 0);
}

SysyParser::DecFloatConstContext::DecFloatConstContext(FloatConstContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::DecFloatConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterDecFloatConst(this);
}

void SysyParser::DecFloatConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitDecFloatConst(this);
}

std::any SysyParser::DecFloatConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitDecFloatConst(this);
    else
        return visitor->visitChildren(this);
}
//----------------- HexFloatConstContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::HexFloatConstContext::HexFloatConst()
{
    return getToken(SysyParser::HexFloatConst, 0);
}

SysyParser::HexFloatConstContext::HexFloatConstContext(FloatConstContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::HexFloatConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterHexFloatConst(this);
}

void SysyParser::HexFloatConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitHexFloatConst(this);
}

std::any SysyParser::HexFloatConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitHexFloatConst(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FloatConstContext* SysyParser::floatConst()
{
    FloatConstContext* _localctx = _tracker.createInstance<FloatConstContext>(_ctx, getState());
    enterRule(_localctx, 42, SysyParser::RuleFloatConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(268);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::DecFloatConst: {
            _localctx = _tracker.createInstance<SysyParser::DecFloatConstContext>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(266);
            match(SysyParser::DecFloatConst);
            break;
        }

        case SysyParser::HexFloatConst: {
            _localctx = _tracker.createInstance<SysyParser::HexFloatConstContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(267);
            match(SysyParser::HexFloatConst);
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

//----------------- NumberContext ------------------------------------------------------------------

SysyParser::NumberContext::NumberContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::IntConstContext* SysyParser::NumberContext::intConst()
{
    return getRuleContext<SysyParser::IntConstContext>(0);
}

SysyParser::FloatConstContext* SysyParser::NumberContext::floatConst()
{
    return getRuleContext<SysyParser::FloatConstContext>(0);
}


size_t SysyParser::NumberContext::getRuleIndex() const
{
    return SysyParser::RuleNumber;
}

void SysyParser::NumberContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterNumber(this);
}

void SysyParser::NumberContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitNumber(this);
}


std::any SysyParser::NumberContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitNumber(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::NumberContext* SysyParser::number()
{
    NumberContext* _localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
    enterRule(_localctx, 44, SysyParser::RuleNumber);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(272);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::DecIntConst:
        case SysyParser::OctIntConst:
        case SysyParser::HexIntConst: {
            enterOuterAlt(_localctx, 1);
            setState(270);
            intConst();
            break;
        }

        case SysyParser::DecFloatConst:
        case SysyParser::HexFloatConst: {
            enterOuterAlt(_localctx, 2);
            setState(271);
            floatConst();
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

//----------------- UnaryExpContext
//------------------------------------------------------------------

SysyParser::UnaryExpContext::UnaryExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::UnaryExpContext::getRuleIndex() const
{
    return SysyParser::RuleUnaryExp;
}

void SysyParser::UnaryExpContext::copyFrom(UnaryExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- CallContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::CallContext::Ident()
{
    return getToken(SysyParser::Ident, 0);
}

tree::TerminalNode* SysyParser::CallContext::Lparen()
{
    return getToken(SysyParser::Lparen, 0);
}

tree::TerminalNode* SysyParser::CallContext::Rparen()
{
    return getToken(SysyParser::Rparen, 0);
}

SysyParser::FuncRParamsContext* SysyParser::CallContext::funcRParams()
{
    return getRuleContext<SysyParser::FuncRParamsContext>(0);
}

SysyParser::CallContext::CallContext(UnaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::CallContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterCall(this);
}

void SysyParser::CallContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitCall(this);
}

std::any SysyParser::CallContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitCall(this);
    else
        return visitor->visitChildren(this);
}
//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* SysyParser::NotContext::Not()
{
    return getToken(SysyParser::Not, 0);
}

SysyParser::UnaryExpContext* SysyParser::NotContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::NotContext::NotContext(UnaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::NotContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterNot(this);
}

void SysyParser::NotContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitNot(this);
}

std::any SysyParser::NotContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitNot(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnaryExp_Context
//------------------------------------------------------------------

SysyParser::PrimaryExpContext* SysyParser::UnaryExp_Context::primaryExp()
{
    return getRuleContext<SysyParser::PrimaryExpContext>(0);
}

SysyParser::UnaryExp_Context::UnaryExp_Context(UnaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::UnaryExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterUnaryExp_(this);
}

void SysyParser::UnaryExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitUnaryExp_(this);
}

std::any SysyParser::UnaryExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitUnaryExp_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnaryAddContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::UnaryAddContext::Add()
{
    return getToken(SysyParser::Add, 0);
}

SysyParser::UnaryExpContext* SysyParser::UnaryAddContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::UnaryAddContext::UnaryAddContext(UnaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::UnaryAddContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterUnaryAdd(this);
}

void SysyParser::UnaryAddContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitUnaryAdd(this);
}

std::any SysyParser::UnaryAddContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitUnaryAdd(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnarySubContext
//------------------------------------------------------------------

tree::TerminalNode* SysyParser::UnarySubContext::Sub()
{
    return getToken(SysyParser::Sub, 0);
}

SysyParser::UnaryExpContext* SysyParser::UnarySubContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::UnarySubContext::UnarySubContext(UnaryExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::UnarySubContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterUnarySub(this);
}

void SysyParser::UnarySubContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitUnarySub(this);
}

std::any SysyParser::UnarySubContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitUnarySub(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::UnaryExpContext* SysyParser::unaryExp()
{
    UnaryExpContext* _localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
    enterRule(_localctx, 46, SysyParser::RuleUnaryExp);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(287);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
        case 1: {
            _localctx = _tracker.createInstance<SysyParser::UnaryExp_Context>(_localctx);
            enterOuterAlt(_localctx, 1);
            setState(274);
            primaryExp();
            break;
        }

        case 2: {
            _localctx = _tracker.createInstance<SysyParser::CallContext>(_localctx);
            enterOuterAlt(_localctx, 2);
            setState(275);
            match(SysyParser::Ident);
            setState(276);
            match(SysyParser::Lparen);
            setState(278);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & 1117229154430) != 0)) {
                setState(277);
                funcRParams();
            }
            setState(280);
            match(SysyParser::Rparen);
            break;
        }

        case 3: {
            _localctx = _tracker.createInstance<SysyParser::UnaryAddContext>(_localctx);
            enterOuterAlt(_localctx, 3);
            setState(281);
            match(SysyParser::Add);
            setState(282);
            unaryExp();
            break;
        }

        case 4: {
            _localctx = _tracker.createInstance<SysyParser::UnarySubContext>(_localctx);
            enterOuterAlt(_localctx, 4);
            setState(283);
            match(SysyParser::Sub);
            setState(284);
            unaryExp();
            break;
        }

        case 5: {
            _localctx = _tracker.createInstance<SysyParser::NotContext>(_localctx);
            enterOuterAlt(_localctx, 5);
            setState(285);
            match(SysyParser::Not);
            setState(286);
            unaryExp();
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

//----------------- StringConstContext
//------------------------------------------------------------------

SysyParser::StringConstContext::StringConstContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* SysyParser::StringConstContext::StringConst()
{
    return getToken(SysyParser::StringConst, 0);
}


size_t SysyParser::StringConstContext::getRuleIndex() const
{
    return SysyParser::RuleStringConst;
}

void SysyParser::StringConstContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterStringConst(this);
}

void SysyParser::StringConstContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitStringConst(this);
}


std::any SysyParser::StringConstContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitStringConst(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::StringConstContext* SysyParser::stringConst()
{
    StringConstContext* _localctx = _tracker.createInstance<StringConstContext>(_ctx, getState());
    enterRule(_localctx, 48, SysyParser::RuleStringConst);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(289);
        match(SysyParser::StringConst);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncRParamContext
//------------------------------------------------------------------

SysyParser::FuncRParamContext::FuncRParamContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

SysyParser::ExpContext* SysyParser::FuncRParamContext::exp()
{
    return getRuleContext<SysyParser::ExpContext>(0);
}

SysyParser::StringConstContext* SysyParser::FuncRParamContext::stringConst()
{
    return getRuleContext<SysyParser::StringConstContext>(0);
}


size_t SysyParser::FuncRParamContext::getRuleIndex() const
{
    return SysyParser::RuleFuncRParam;
}

void SysyParser::FuncRParamContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncRParam(this);
}

void SysyParser::FuncRParamContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncRParam(this);
}


std::any SysyParser::FuncRParamContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFuncRParam(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncRParamContext* SysyParser::funcRParam()
{
    FuncRParamContext* _localctx = _tracker.createInstance<FuncRParamContext>(_ctx, getState());
    enterRule(_localctx, 50, SysyParser::RuleFuncRParam);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(293);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
        case SysyParser::DecIntConst:
        case SysyParser::OctIntConst:
        case SysyParser::HexIntConst:
        case SysyParser::DecFloatConst:
        case SysyParser::HexFloatConst:
        case SysyParser::Add:
        case SysyParser::Sub:
        case SysyParser::Not:
        case SysyParser::Lparen:
        case SysyParser::Ident: {
            enterOuterAlt(_localctx, 1);
            setState(291);
            exp();
            break;
        }

        case SysyParser::StringConst: {
            enterOuterAlt(_localctx, 2);
            setState(292);
            stringConst();
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

//----------------- FuncRParamsContext
//------------------------------------------------------------------

SysyParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<SysyParser::FuncRParamContext*> SysyParser::FuncRParamsContext::funcRParam()
{
    return getRuleContexts<SysyParser::FuncRParamContext>();
}

SysyParser::FuncRParamContext* SysyParser::FuncRParamsContext::funcRParam(size_t i)
{
    return getRuleContext<SysyParser::FuncRParamContext>(i);
}

std::vector<tree::TerminalNode*> SysyParser::FuncRParamsContext::Comma()
{
    return getTokens(SysyParser::Comma);
}

tree::TerminalNode* SysyParser::FuncRParamsContext::Comma(size_t i)
{
    return getToken(SysyParser::Comma, i);
}


size_t SysyParser::FuncRParamsContext::getRuleIndex() const
{
    return SysyParser::RuleFuncRParams;
}

void SysyParser::FuncRParamsContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterFuncRParams(this);
}

void SysyParser::FuncRParamsContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitFuncRParams(this);
}


std::any SysyParser::FuncRParamsContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitFuncRParams(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::FuncRParamsContext* SysyParser::funcRParams()
{
    FuncRParamsContext* _localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
    enterRule(_localctx, 52, SysyParser::RuleFuncRParams);
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
        setState(295);
        funcRParam();
        setState(300);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SysyParser::Comma) {
            setState(296);
            match(SysyParser::Comma);
            setState(297);
            funcRParam();
            setState(302);
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

//----------------- MulExpContext ------------------------------------------------------------------

SysyParser::MulExpContext::MulExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::MulExpContext::getRuleIndex() const
{
    return SysyParser::RuleMulExp;
}

void SysyParser::MulExpContext::copyFrom(MulExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- DivContext ------------------------------------------------------------------

SysyParser::MulExpContext* SysyParser::DivContext::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

tree::TerminalNode* SysyParser::DivContext::Div()
{
    return getToken(SysyParser::Div, 0);
}

SysyParser::UnaryExpContext* SysyParser::DivContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::DivContext::DivContext(MulExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::DivContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterDiv(this);
}

void SysyParser::DivContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitDiv(this);
}

std::any SysyParser::DivContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitDiv(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ModContext ------------------------------------------------------------------

SysyParser::MulExpContext* SysyParser::ModContext::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

tree::TerminalNode* SysyParser::ModContext::Mod()
{
    return getToken(SysyParser::Mod, 0);
}

SysyParser::UnaryExpContext* SysyParser::ModContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::ModContext::ModContext(MulExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::ModContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterMod(this);
}

void SysyParser::ModContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitMod(this);
}

std::any SysyParser::ModContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitMod(this);
    else
        return visitor->visitChildren(this);
}
//----------------- MulContext ------------------------------------------------------------------

SysyParser::MulExpContext* SysyParser::MulContext::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

tree::TerminalNode* SysyParser::MulContext::Mul()
{
    return getToken(SysyParser::Mul, 0);
}

SysyParser::UnaryExpContext* SysyParser::MulContext::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::MulContext::MulContext(MulExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::MulContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterMul(this);
}

void SysyParser::MulContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitMul(this);
}

std::any SysyParser::MulContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitMul(this);
    else
        return visitor->visitChildren(this);
}
//----------------- MulExp_Context
//------------------------------------------------------------------

SysyParser::UnaryExpContext* SysyParser::MulExp_Context::unaryExp()
{
    return getRuleContext<SysyParser::UnaryExpContext>(0);
}

SysyParser::MulExp_Context::MulExp_Context(MulExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::MulExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterMulExp_(this);
}

void SysyParser::MulExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitMulExp_(this);
}

std::any SysyParser::MulExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitMulExp_(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::MulExpContext* SysyParser::mulExp()
{
    return mulExp(0);
}

SysyParser::MulExpContext* SysyParser::mulExp(int precedence)
{
    ParserRuleContext*         parentContext = _ctx;
    size_t                     parentState   = getState();
    SysyParser::MulExpContext* _localctx =
        _tracker.createInstance<MulExpContext>(_ctx, parentState);
    SysyParser::MulExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 54;
    enterRecursionRule(_localctx, 54, SysyParser::RuleMulExp, precedence);


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
        _localctx       = _tracker.createInstance<MulExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(304);
        unaryExp();
        _ctx->stop = _input->LT(-1);
        setState(317);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(315);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)
                ) {
                case 1: {
                    auto newContext = _tracker.createInstance<MulContext>(
                        _tracker.createInstance<MulExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleMulExp);
                    setState(306);

                    if (!(precpred(_ctx, 3)))
                        throw FailedPredicateException(this, "precpred(_ctx, 3)");
                    setState(307);
                    match(SysyParser::Mul);
                    setState(308);
                    unaryExp();
                    break;
                }

                case 2: {
                    auto newContext = _tracker.createInstance<DivContext>(
                        _tracker.createInstance<MulExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleMulExp);
                    setState(309);

                    if (!(precpred(_ctx, 2)))
                        throw FailedPredicateException(this, "precpred(_ctx, 2)");
                    setState(310);
                    match(SysyParser::Div);
                    setState(311);
                    unaryExp();
                    break;
                }

                case 3: {
                    auto newContext = _tracker.createInstance<ModContext>(
                        _tracker.createInstance<MulExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleMulExp);
                    setState(312);

                    if (!(precpred(_ctx, 1)))
                        throw FailedPredicateException(this, "precpred(_ctx, 1)");
                    setState(313);
                    match(SysyParser::Mod);
                    setState(314);
                    unaryExp();
                    break;
                }

                default: break;
                }
            }
            setState(319);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

SysyParser::AddExpContext::AddExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::AddExpContext::getRuleIndex() const
{
    return SysyParser::RuleAddExp;
}

void SysyParser::AddExpContext::copyFrom(AddExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- AddExp_Context
//------------------------------------------------------------------

SysyParser::MulExpContext* SysyParser::AddExp_Context::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

SysyParser::AddExp_Context::AddExp_Context(AddExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::AddExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAddExp_(this);
}

void SysyParser::AddExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAddExp_(this);
}

std::any SysyParser::AddExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitAddExp_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AddContext ------------------------------------------------------------------

SysyParser::AddExpContext* SysyParser::AddContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

tree::TerminalNode* SysyParser::AddContext::Add()
{
    return getToken(SysyParser::Add, 0);
}

SysyParser::MulExpContext* SysyParser::AddContext::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

SysyParser::AddContext::AddContext(AddExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::AddContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAdd(this);
}

void SysyParser::AddContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAdd(this);
}

std::any SysyParser::AddContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitAdd(this);
    else
        return visitor->visitChildren(this);
}
//----------------- SubContext ------------------------------------------------------------------

SysyParser::AddExpContext* SysyParser::SubContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

tree::TerminalNode* SysyParser::SubContext::Sub()
{
    return getToken(SysyParser::Sub, 0);
}

SysyParser::MulExpContext* SysyParser::SubContext::mulExp()
{
    return getRuleContext<SysyParser::MulExpContext>(0);
}

SysyParser::SubContext::SubContext(AddExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::SubContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterSub(this);
}

void SysyParser::SubContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitSub(this);
}

std::any SysyParser::SubContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitSub(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::AddExpContext* SysyParser::addExp()
{
    return addExp(0);
}

SysyParser::AddExpContext* SysyParser::addExp(int precedence)
{
    ParserRuleContext*         parentContext = _ctx;
    size_t                     parentState   = getState();
    SysyParser::AddExpContext* _localctx =
        _tracker.createInstance<AddExpContext>(_ctx, parentState);
    SysyParser::AddExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 56;
    enterRecursionRule(_localctx, 56, SysyParser::RuleAddExp, precedence);


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
        _localctx       = _tracker.createInstance<AddExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(321);
        mulExp(0);
        _ctx->stop = _input->LT(-1);
        setState(331);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(329);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)
                ) {
                case 1: {
                    auto newContext = _tracker.createInstance<AddContext>(
                        _tracker.createInstance<AddExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleAddExp);
                    setState(323);

                    if (!(precpred(_ctx, 2)))
                        throw FailedPredicateException(this, "precpred(_ctx, 2)");
                    setState(324);
                    match(SysyParser::Add);
                    setState(325);
                    mulExp(0);
                    break;
                }

                case 2: {
                    auto newContext = _tracker.createInstance<SubContext>(
                        _tracker.createInstance<AddExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleAddExp);
                    setState(326);

                    if (!(precpred(_ctx, 1)))
                        throw FailedPredicateException(this, "precpred(_ctx, 1)");
                    setState(327);
                    match(SysyParser::Sub);
                    setState(328);
                    mulExp(0);
                    break;
                }

                default: break;
                }
            }
            setState(333);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

SysyParser::RelExpContext::RelExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::RelExpContext::getRuleIndex() const
{
    return SysyParser::RuleRelExp;
}

void SysyParser::RelExpContext::copyFrom(RelExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- GeqContext ------------------------------------------------------------------

SysyParser::RelExpContext* SysyParser::GeqContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

tree::TerminalNode* SysyParser::GeqContext::Geq()
{
    return getToken(SysyParser::Geq, 0);
}

SysyParser::AddExpContext* SysyParser::GeqContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

SysyParser::GeqContext::GeqContext(RelExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::GeqContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGeq(this);
}

void SysyParser::GeqContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGeq(this);
}

std::any SysyParser::GeqContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitGeq(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LtContext ------------------------------------------------------------------

SysyParser::RelExpContext* SysyParser::LtContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

tree::TerminalNode* SysyParser::LtContext::Lt()
{
    return getToken(SysyParser::Lt, 0);
}

SysyParser::AddExpContext* SysyParser::LtContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

SysyParser::LtContext::LtContext(RelExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::LtContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLt(this);
}

void SysyParser::LtContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLt(this);
}

std::any SysyParser::LtContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLt(this);
    else
        return visitor->visitChildren(this);
}
//----------------- RelExp_Context
//------------------------------------------------------------------

SysyParser::AddExpContext* SysyParser::RelExp_Context::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

SysyParser::RelExp_Context::RelExp_Context(RelExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::RelExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterRelExp_(this);
}

void SysyParser::RelExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitRelExp_(this);
}

std::any SysyParser::RelExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitRelExp_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LeqContext ------------------------------------------------------------------

SysyParser::RelExpContext* SysyParser::LeqContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

tree::TerminalNode* SysyParser::LeqContext::Leq()
{
    return getToken(SysyParser::Leq, 0);
}

SysyParser::AddExpContext* SysyParser::LeqContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

SysyParser::LeqContext::LeqContext(RelExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::LeqContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLeq(this);
}

void SysyParser::LeqContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLeq(this);
}

std::any SysyParser::LeqContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLeq(this);
    else
        return visitor->visitChildren(this);
}
//----------------- GtContext ------------------------------------------------------------------

SysyParser::RelExpContext* SysyParser::GtContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

tree::TerminalNode* SysyParser::GtContext::Gt()
{
    return getToken(SysyParser::Gt, 0);
}

SysyParser::AddExpContext* SysyParser::GtContext::addExp()
{
    return getRuleContext<SysyParser::AddExpContext>(0);
}

SysyParser::GtContext::GtContext(RelExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::GtContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterGt(this);
}

void SysyParser::GtContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitGt(this);
}

std::any SysyParser::GtContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitGt(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::RelExpContext* SysyParser::relExp()
{
    return relExp(0);
}

SysyParser::RelExpContext* SysyParser::relExp(int precedence)
{
    ParserRuleContext*         parentContext = _ctx;
    size_t                     parentState   = getState();
    SysyParser::RelExpContext* _localctx =
        _tracker.createInstance<RelExpContext>(_ctx, parentState);
    SysyParser::RelExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 58;
    enterRecursionRule(_localctx, 58, SysyParser::RuleRelExp, precedence);


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
        _localctx       = _tracker.createInstance<RelExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(335);
        addExp(0);
        _ctx->stop = _input->LT(-1);
        setState(351);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(349);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)
                ) {
                case 1: {
                    auto newContext = _tracker.createInstance<LtContext>(
                        _tracker.createInstance<RelExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleRelExp);
                    setState(337);

                    if (!(precpred(_ctx, 4)))
                        throw FailedPredicateException(this, "precpred(_ctx, 4)");
                    setState(338);
                    match(SysyParser::Lt);
                    setState(339);
                    addExp(0);
                    break;
                }

                case 2: {
                    auto newContext = _tracker.createInstance<GtContext>(
                        _tracker.createInstance<RelExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleRelExp);
                    setState(340);

                    if (!(precpred(_ctx, 3)))
                        throw FailedPredicateException(this, "precpred(_ctx, 3)");
                    setState(341);
                    match(SysyParser::Gt);
                    setState(342);
                    addExp(0);
                    break;
                }

                case 3: {
                    auto newContext = _tracker.createInstance<LeqContext>(
                        _tracker.createInstance<RelExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleRelExp);
                    setState(343);

                    if (!(precpred(_ctx, 2)))
                        throw FailedPredicateException(this, "precpred(_ctx, 2)");
                    setState(344);
                    match(SysyParser::Leq);
                    setState(345);
                    addExp(0);
                    break;
                }

                case 4: {
                    auto newContext = _tracker.createInstance<GeqContext>(
                        _tracker.createInstance<RelExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleRelExp);
                    setState(346);

                    if (!(precpred(_ctx, 1)))
                        throw FailedPredicateException(this, "precpred(_ctx, 1)");
                    setState(347);
                    match(SysyParser::Geq);
                    setState(348);
                    addExp(0);
                    break;
                }

                default: break;
                }
            }
            setState(353);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

SysyParser::EqExpContext::EqExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::EqExpContext::getRuleIndex() const
{
    return SysyParser::RuleEqExp;
}

void SysyParser::EqExpContext::copyFrom(EqExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- NeqContext ------------------------------------------------------------------

SysyParser::EqExpContext* SysyParser::NeqContext::eqExp()
{
    return getRuleContext<SysyParser::EqExpContext>(0);
}

tree::TerminalNode* SysyParser::NeqContext::Neq()
{
    return getToken(SysyParser::Neq, 0);
}

SysyParser::RelExpContext* SysyParser::NeqContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

SysyParser::NeqContext::NeqContext(EqExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::NeqContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterNeq(this);
}

void SysyParser::NeqContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitNeq(this);
}

std::any SysyParser::NeqContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitNeq(this);
    else
        return visitor->visitChildren(this);
}
//----------------- EqContext ------------------------------------------------------------------

SysyParser::EqExpContext* SysyParser::EqContext::eqExp()
{
    return getRuleContext<SysyParser::EqExpContext>(0);
}

tree::TerminalNode* SysyParser::EqContext::Eq()
{
    return getToken(SysyParser::Eq, 0);
}

SysyParser::RelExpContext* SysyParser::EqContext::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

SysyParser::EqContext::EqContext(EqExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::EqContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterEq(this);
}

void SysyParser::EqContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitEq(this);
}

std::any SysyParser::EqContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitEq(this);
    else
        return visitor->visitChildren(this);
}
//----------------- EqExp_Context ------------------------------------------------------------------

SysyParser::RelExpContext* SysyParser::EqExp_Context::relExp()
{
    return getRuleContext<SysyParser::RelExpContext>(0);
}

SysyParser::EqExp_Context::EqExp_Context(EqExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::EqExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterEqExp_(this);
}

void SysyParser::EqExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitEqExp_(this);
}

std::any SysyParser::EqExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitEqExp_(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::EqExpContext* SysyParser::eqExp()
{
    return eqExp(0);
}

SysyParser::EqExpContext* SysyParser::eqExp(int precedence)
{
    ParserRuleContext*        parentContext = _ctx;
    size_t                    parentState   = getState();
    SysyParser::EqExpContext* _localctx = _tracker.createInstance<EqExpContext>(_ctx, parentState);
    SysyParser::EqExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 60;
    enterRecursionRule(_localctx, 60, SysyParser::RuleEqExp, precedence);


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
        _localctx       = _tracker.createInstance<EqExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(355);
        relExp(0);
        _ctx->stop = _input->LT(-1);
        setState(365);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                setState(363);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)
                ) {
                case 1: {
                    auto newContext = _tracker.createInstance<EqContext>(
                        _tracker.createInstance<EqExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleEqExp);
                    setState(357);

                    if (!(precpred(_ctx, 2)))
                        throw FailedPredicateException(this, "precpred(_ctx, 2)");
                    setState(358);
                    match(SysyParser::Eq);
                    setState(359);
                    relExp(0);
                    break;
                }

                case 2: {
                    auto newContext = _tracker.createInstance<NeqContext>(
                        _tracker.createInstance<EqExpContext>(parentContext, parentState)
                    );
                    _localctx = newContext;
                    pushNewRecursionContext(newContext, startState, RuleEqExp);
                    setState(360);

                    if (!(precpred(_ctx, 1)))
                        throw FailedPredicateException(this, "precpred(_ctx, 1)");
                    setState(361);
                    match(SysyParser::Neq);
                    setState(362);
                    relExp(0);
                    break;
                }

                default: break;
                }
            }
            setState(367);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- LAndExpContext
//------------------------------------------------------------------

SysyParser::LAndExpContext::LAndExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::LAndExpContext::getRuleIndex() const
{
    return SysyParser::RuleLAndExp;
}

void SysyParser::LAndExpContext::copyFrom(LAndExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LAndExp_Context
//------------------------------------------------------------------

SysyParser::EqExpContext* SysyParser::LAndExp_Context::eqExp()
{
    return getRuleContext<SysyParser::EqExpContext>(0);
}

SysyParser::LAndExp_Context::LAndExp_Context(LAndExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::LAndExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLAndExp_(this);
}

void SysyParser::LAndExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLAndExp_(this);
}

std::any SysyParser::LAndExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLAndExp_(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AndContext ------------------------------------------------------------------

SysyParser::LAndExpContext* SysyParser::AndContext::lAndExp()
{
    return getRuleContext<SysyParser::LAndExpContext>(0);
}

tree::TerminalNode* SysyParser::AndContext::And()
{
    return getToken(SysyParser::And, 0);
}

SysyParser::EqExpContext* SysyParser::AndContext::eqExp()
{
    return getRuleContext<SysyParser::EqExpContext>(0);
}

SysyParser::AndContext::AndContext(LAndExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::AndContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterAnd(this);
}

void SysyParser::AndContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitAnd(this);
}

std::any SysyParser::AndContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitAnd(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::LAndExpContext* SysyParser::lAndExp()
{
    return lAndExp(0);
}

SysyParser::LAndExpContext* SysyParser::lAndExp(int precedence)
{
    ParserRuleContext*          parentContext = _ctx;
    size_t                      parentState   = getState();
    SysyParser::LAndExpContext* _localctx =
        _tracker.createInstance<LAndExpContext>(_ctx, parentState);
    SysyParser::LAndExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 62;
    enterRecursionRule(_localctx, 62, SysyParser::RuleLAndExp, precedence);


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
        _localctx       = _tracker.createInstance<LAndExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(369);
        eqExp(0);
        _ctx->stop = _input->LT(-1);
        setState(376);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                auto newContext = _tracker.createInstance<AndContext>(
                    _tracker.createInstance<LAndExpContext>(parentContext, parentState)
                );
                _localctx = newContext;
                pushNewRecursionContext(newContext, startState, RuleLAndExp);
                setState(371);

                if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
                setState(372);
                match(SysyParser::And);
                setState(373);
                eqExp(0);
            }
            setState(378);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

SysyParser::LOrExpContext::LOrExpContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}


size_t SysyParser::LOrExpContext::getRuleIndex() const
{
    return SysyParser::RuleLOrExp;
}

void SysyParser::LOrExpContext::copyFrom(LOrExpContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- OrContext ------------------------------------------------------------------

SysyParser::LOrExpContext* SysyParser::OrContext::lOrExp()
{
    return getRuleContext<SysyParser::LOrExpContext>(0);
}

tree::TerminalNode* SysyParser::OrContext::Or()
{
    return getToken(SysyParser::Or, 0);
}

SysyParser::LAndExpContext* SysyParser::OrContext::lAndExp()
{
    return getRuleContext<SysyParser::LAndExpContext>(0);
}

SysyParser::OrContext::OrContext(LOrExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::OrContext::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterOr(this);
}

void SysyParser::OrContext::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitOr(this);
}

std::any SysyParser::OrContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitOr(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LOrExp_Context
//------------------------------------------------------------------

SysyParser::LAndExpContext* SysyParser::LOrExp_Context::lAndExp()
{
    return getRuleContext<SysyParser::LAndExpContext>(0);
}

SysyParser::LOrExp_Context::LOrExp_Context(LOrExpContext* ctx)
{
    copyFrom(ctx);
}

void SysyParser::LOrExp_Context::enterRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->enterLOrExp_(this);
}

void SysyParser::LOrExp_Context::exitRule(tree::ParseTreeListener* listener)
{
    auto parserListener = dynamic_cast<SysyListener*>(listener);
    if (parserListener != nullptr) parserListener->exitLOrExp_(this);
}

std::any SysyParser::LOrExp_Context::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<SysyVisitor*>(visitor))
        return parserVisitor->visitLOrExp_(this);
    else
        return visitor->visitChildren(this);
}

SysyParser::LOrExpContext* SysyParser::lOrExp()
{
    return lOrExp(0);
}

SysyParser::LOrExpContext* SysyParser::lOrExp(int precedence)
{
    ParserRuleContext*         parentContext = _ctx;
    size_t                     parentState   = getState();
    SysyParser::LOrExpContext* _localctx =
        _tracker.createInstance<LOrExpContext>(_ctx, parentState);
    SysyParser::LOrExpContext* previousContext = _localctx;
    (void)previousContext;   // Silence compiler, in case the context is not used by generated code.
    size_t startState = 64;
    enterRecursionRule(_localctx, 64, SysyParser::RuleLOrExp, precedence);


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
        _localctx       = _tracker.createInstance<LOrExp_Context>(_localctx);
        _ctx            = _localctx;
        previousContext = _localctx;

        setState(380);
        lAndExp(0);
        _ctx->stop = _input->LT(-1);
        setState(387);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty()) triggerExitRuleEvent();
                previousContext = _localctx;
                auto newContext = _tracker.createInstance<OrContext>(
                    _tracker.createInstance<LOrExpContext>(parentContext, parentState)
                );
                _localctx = newContext;
                pushNewRecursionContext(newContext, startState, RuleLOrExp);
                setState(382);

                if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
                setState(383);
                match(SysyParser::Or);
                setState(384);
                lAndExp(0);
            }
            setState(389);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

bool SysyParser::sempred(RuleContext* context, size_t ruleIndex, size_t predicateIndex)
{
    switch (ruleIndex) {
    case 27: return mulExpSempred(antlrcpp::downCast<MulExpContext*>(context), predicateIndex);
    case 28: return addExpSempred(antlrcpp::downCast<AddExpContext*>(context), predicateIndex);
    case 29: return relExpSempred(antlrcpp::downCast<RelExpContext*>(context), predicateIndex);
    case 30: return eqExpSempred(antlrcpp::downCast<EqExpContext*>(context), predicateIndex);
    case 31: return lAndExpSempred(antlrcpp::downCast<LAndExpContext*>(context), predicateIndex);
    case 32: return lOrExpSempred(antlrcpp::downCast<LOrExpContext*>(context), predicateIndex);

    default: break;
    }
    return true;
}

bool SysyParser::mulExpSempred(MulExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

bool SysyParser::addExpSempred(AddExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 3: return precpred(_ctx, 2);
    case 4: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

bool SysyParser::relExpSempred(RelExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);
    case 7: return precpred(_ctx, 2);
    case 8: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

bool SysyParser::eqExpSempred(EqExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 9: return precpred(_ctx, 2);
    case 10: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

bool SysyParser::lAndExpSempred(LAndExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 11: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

bool SysyParser::lOrExpSempred(LOrExpContext* _localctx, size_t predicateIndex)
{
    switch (predicateIndex) {
    case 12: return precpred(_ctx, 1);

    default: break;
    }
    return true;
}

void SysyParser::initialize()
{
#if ANTLR4_USE_THREAD_LOCAL_CACHE
    sysyParserInitialize();
#else
    ::antlr4::internal::call_once(sysyParserOnceFlag, sysyParserInitialize);
#endif
}
