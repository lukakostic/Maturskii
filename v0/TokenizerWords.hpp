#pragma once
#include <cstddef>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>

//TokenType Groups:
#define TokenWords_Identifier 0  // variable, pushes to stack -> string
#define TokenWords_Complex 1     // (), [], {}, a.b.c -> ComplexType, vector of tokens (separated by , or space/nothing if fn call / assignment with null return)
#define TokenWords_Literal 2     // literal data (check LiteralType) -> LiteralType, data
#define TokenWords_BiOperator 3  // : = ^ :: =: ^: > < >= <= == != //Looks at tokens on left and right of itself
#define TokenWords_PreOperator 4 // & | # //Looks at token right of itself
#define TokenWords_Call 5        // ret ; ~ //standalone call without need for ()

//Lets say size_t is 32 bit
//Last 7 bits (of 32) are used to group tokenTypes (group mask: F 1110 00 0000 = FE00 0000 )
//Last 8th bit (of 32) is used to indicate if the token carries data (group mask: 0 0001 00 0000 = 0100 0000 )
//Allowing 2^7 (128) SubTokenGroups, Data yes or no, and 2^24 (16777216) TokenGroups
#define GetTokenGroup(INDEX) ((((unsigned int)INDEX) & 0xFE000000) >> 25)
#define GetTokenData(INDEX) ((((unsigned int)INDEX) & 0x01000000) >> 24)

enum class TokenWordType : std::size_t
{

#define ENCODE_TOKEN(HAS_DATA) (__COUNTER__ | ((GROUP << 25) | (HAS_DATA << 24))) //Encode group into index
#define Token ENCODE_TOKEN(0)
#define DataToken ENCODE_TOKEN(1)

#define GROUP TokenWords_Identifier
    Identifier = DataToken, //identifier
#undef GROUP

#define GROUP TokenWords_Complex
    Parenthesized = DataToken, //()
    Bracketed = DataToken,     //[]
    Braced = DataToken,        //{}
    Dotted = DataToken,        // . symbol: box.attrs.color , box.$color.r , box.attrs.area() , array.0
#undef GROUP

#define GROUP TokenWords_Literal
    Null = DataToken,              // null
    LiteralIdentifier = DataToken, // $'test' = test
    LiteralInteger = DataToken,    // -6 , 456, \0A2E21
    LiteralDecimal = DataToken,    // 2.3 , -0.2 , .1 , -.321
    LiteralString = DataToken,     //all strings are multiline, you can use `"' in strings: "`'string'`", `'"string"'`, 'a'
#undef GROUP

#define GROUP TokenWords_PreOperator
    IdentifierFrom = Token, // $ symbol: $var -> identifier from value of var (string) MacroSign = Token, // # symbol: #fn(){} , #fn()
#undef GROUP


#undef ENCODE_TOKEN
#undef Token
#undef DataToken
};