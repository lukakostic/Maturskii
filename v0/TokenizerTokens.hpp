#pragma once
#include <cstddef>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"

//Groups:
#define TokenizerType_Identifier 0 //multi char names
#define TokenizerType_Reserved 1  // ()[]{}  //single char
#define TokenizerType_Literal 2 //numbers, strings
//Step 2:
#define TokenizerType_Tree 3

/*
Some are used in both steps (first 2 steps of compilation),
Some in only one.
*/

enum class TokenizerType : TokenType
{

#define GROUP TokenizerType_Identifier
    Identifier = TOKEN_1, //identifier
#undef GROUP

#define GROUP TokenizerType_Reserved
    ToIdentifier = TOKEN,
    Dot = TOKEN,
    
    //Step 1:
    Comma = TOKEN,

    Parenthesis_Open = TOKEN, //(
    Parenthesis_Close= TOKEN, //)
    Bracket_Open = TOKEN, //[
    Bracket_Close= TOKEN, //]
    Brace_Open = TOKEN, //{
    Brace_Close= TOKEN, //}
#undef GROUP

#define GROUP TokenizerType_Literal
    //Numbers:
    LiteralInteger = TOKEN_1,    // -6 , 456, \0A2E21
    LiteralDecimal = TOKEN_1,    // 2.3 , -0.2 , .1 , -.321
    
    //Strings:
    LiteralStringDoubleQuote = TOKEN_1, // "
    LiteralStringTick = TOKEN_1, // `
    LiteralStringQuote = TOKEN_1, // '

    //Step 2:
    LiteralNull = TOKEN, //null
    LiteralIdentifier = TOKEN_1, //$idk
#undef GROUP

//Step 2
#define GROUP TokenizerType_Tree
    Parenthesis = TOKEN_1, //()
    Bracket = TOKEN_1, //[]
    Brace = TOKEN_1, //{}
#undef GROUP
};