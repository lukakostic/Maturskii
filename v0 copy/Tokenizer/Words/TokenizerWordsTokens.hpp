#pragma once
#include "Tokens.hpp"

//Groups:
#define TokenizerWord_Identifier 1 //multi char names
#define TokenizerWord_Special 2  // ()[]{} ., //single char
#define TokenizerWord_Literal 3 //numbers, strings


enum class TokenizerWordToken : Token
{

#define GROUP TokenizerWord_Identifier
    Identifier = TOKEN_1,
#undef GROUP

#define GROUP TokenizerWord_Special
    Hashtag = TOKEN, // #
    Dot = TOKEN, // .
    Comma = TOKEN, // ,
    /*
    Semicolon = TOKEN, // ;
    Equal = TOKEN, // =
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
   
    Parenthesis_Open = TOKEN, // (
    Parenthesis_Close= TOKEN, // )
    Bracket_Open = TOKEN, // [
    Bracket_Close= TOKEN, // ]
    Brace_Open = TOKEN, // {
    Brace_Close= TOKEN, // }
#undef GROUP

#define GROUP TokenizerWord_Literal
    //Numbers:
    LiteralInteger = TOKEN_1,    // -6 , 456
    LiteralDecimal = TOKEN_1,    // 2.3 , -0.2
    
    //Strings:
    LiteralString = TOKEN_1, // "a"
#undef GROUP

};