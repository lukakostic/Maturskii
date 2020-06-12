#pragma once
#include "Tokens.hpp"

//Groups:
#define TokenTree_Identifier 1 //multi char names
#define TokenTree_Special 2  // ()[]{} ., //single char
#define TokenTree_Literal 3 //numbers, strings
#define TokenTree_Tree 4


enum class TokenizerTreeToken : Token
{

#define GROUP TokenTree_Identifier
    Identifier = TOKEN_1,
#undef GROUP

#define GROUP TokenTree_Special
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
#undef GROUP

#define GROUP TokenTree_Literal
    //Numbers:
    LiteralInteger = TOKEN_1,    // -6 , 456
    LiteralDecimal = TOKEN_1,    // 2.3 , -0.2
    
    //Strings:
    LiteralString = TOKEN_1, // "a"

    LiteralNull = TOKEN, //null
#undef GROUP

#define GROUP TokenTree_Tree
    Tree = TOKEN_1,
#undef GROUP

};