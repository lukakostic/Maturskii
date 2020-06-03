#pragma once
#include <cstddef>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"

//Groups:
#define TokenType_Identifier 0 //multi char names
#define TokenType_Special 1  // ()[]{}  //single char
#define TokenType_Literal 2 //numbers, strings
//Step 2:
#define TokenType_Tree 3

/*
Some are used in both steps (first 2 steps of compilation),
Some in only one.
*/

enum class TokenizerToken : TokenType
{

#define GROUP TokenType_Identifier
    Identifier = TOKEN_1, //identifier
#undef GROUP

#define GROUP TokenType_Special
    ToIdentifier = TOKEN, //NOT IMPLEMENTED
    Dot = TOKEN, //NOT IMPLEMENTED

    //Step 1:
    Comma = TOKEN, //NOT IMPLEMENTED

    Parenthesis_Open = TOKEN, //(
    Parenthesis_Close= TOKEN, //)
    Bracket_Open = TOKEN, //[
    Bracket_Close= TOKEN, //]
    Brace_Open = TOKEN, //{
    Brace_Close= TOKEN, //}
#undef GROUP

#define GROUP TokenType_Literal
    //Numbers:
    LiteralInteger = TOKEN_1,    // -6 , 456, \0A2E21
    LiteralDecimal = TOKEN_1,    // 2.3 , -0.2 , .1 , -.321
    
    //Strings:
    LiteralString = TOKEN_1,

    //Step 2:
    LiteralNull = TOKEN, //null //NOT IMPLEMENTED
    LiteralIdentifier = TOKEN_1, //$idk //NOT IMPLEMENTED
#undef GROUP

//Step 2
#define GROUP TokenType_Tree
    Parenthesis = TOKEN_1, //()
    Bracket = TOKEN_1, //[]
    Brace = TOKEN_1, //{}
#undef GROUP
};