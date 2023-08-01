
// Generated from Sysy.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"


class SysyLexer : public antlr4::Lexer
{
public:
    enum {
        DecIntConst   = 1,
        OctIntConst   = 2,
        HexIntConst   = 3,
        DecFloatConst = 4,
        HexFloatConst = 5,
        StringConst   = 6,
        Int           = 7,
        Float         = 8,
        Void          = 9,
        Const         = 10,
        If            = 11,
        Else          = 12,
        While         = 13,
        Break         = 14,
        Continue      = 15,
        Return        = 16,
        Assign        = 17,
        Add           = 18,
        Sub           = 19,
        Mul           = 20,
        Div           = 21,
        Mod           = 22,
        Eq            = 23,
        Neq           = 24,
        Lt            = 25,
        Gt            = 26,
        Leq           = 27,
        Geq           = 28,
        Not           = 29,
        And           = 30,
        Or            = 31,
        Comma         = 32,
        Semicolon     = 33,
        Lparen        = 34,
        Rparen        = 35,
        Lbracket      = 36,
        Rbracket      = 37,
        Lbrace        = 38,
        Rbrace        = 39,
        Ident         = 40,
        Whitespace    = 41,
        LineComment   = 42,
        BlockComment  = 43
    };

    explicit SysyLexer(antlr4::CharStream* input);

    ~SysyLexer() override;


    std::string getGrammarFileName() const override;

    const std::vector<std::string>& getRuleNames() const override;

    const std::vector<std::string>& getChannelNames() const override;

    const std::vector<std::string>& getModeNames() const override;

    const antlr4::dfa::Vocabulary& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;

    const antlr4::atn::ATN& getATN() const override;

    // By default the static state used to implement the lexer is lazily initialized during the
    // first call to the constructor. You can call this function if you wish to initialize the
    // static state ahead of time.
    static void initialize();

private:
    // Individual action functions triggered by action() above.

    // Individual semantic predicate functions triggered by sempred() above.
};
