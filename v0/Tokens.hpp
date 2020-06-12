#pragma once
#include "TokenStructs.hpp"

//Groups:
#define Tokenizer_Identifier 1 //multi char names
#define Tokenizer_Special 2  // ()[]{} ., //single char
#define Tokenizer_Literal 3 //numbers, strings
#define Tokenizer_Tree 4 //numbers, strings


enum class Tokens : Token
{

#define GROUP Tokenizer_Identifier
    Identifier = TOKEN_1(1),
#undef GROUP

#define GROUP Tokenizer_Special
    //Hashtag = TOKEN(1), // #
    //Dot = TOKEN(2), // .
    Comma = TOKEN(3), // ,
    
    //Semicolon = TOKEN(4), // ;
    
    Equal = TOKEN(5), // =
    /*
    Minus = TOKEN, // -
    Plus = TOKEN, // +
    Star = TOKEN, // *
    Slash = TOKEN, // /
    Percent = TOKEN, // %
    Exclamation = TOKEN, // !
    Tilda = TOKEN, // ~
    Dollar = TOKEN, // $
    At = TOKEN, // @
    Caret = TOKEN, // ^
    Pipe = TOKEN, // |
    And = TOKEN, // &
    Greater = TOKEN, // >
    Lesser = TOKEN, // <
    */
   /*
    Parenthesis_Open = TOKEN, // (
    Parenthesis_Close= TOKEN, // )
    Bracket_Open = TOKEN, // [
    Bracket_Close= TOKEN, // ]
    Brace_Open = TOKEN, // {
    Brace_Close= TOKEN, // }
    */
#undef GROUP

#define GROUP Tokenizer_Literal
    //Numbers:
    LiteralInteger = TOKEN_1(1),    // -6 , 456
    LiteralDecimal = TOKEN_1(2),    // 2.3 , -0.2
    
    //Strings:
    LiteralString = TOKEN_1(3), // "a"
#undef GROUP

#define GROUP Tokenizer_Tree
    Tree = TOKEN_1(1),
#undef GROUP

};