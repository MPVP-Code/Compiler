#ifndef lexer_hpp
#define lexer_hpp

#include <string>

enum TokenType{
    NONE = 0,
    VARIABLE   = 1,
    EQUALS_SIGN = 2,
    NUMBER   = 3,
};

extern int yylex();

#endif
