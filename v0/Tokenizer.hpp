#pragma once
#include <cstddef>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>

//TokenType Groups:
#define Token_Identifier 0  // variable, pushes to stack -> string
#define Token_Complex 1     // (), [], {}, a.b.c -> ComplexType, vector of tokens (separated by , or space/nothing if fn call / assignment with null return)
#define Token_Literal 2     // literal data (check LiteralType) -> LiteralType, data
#define Token_BiOperator 3  // : = ^ :: =: ^: > < >= <= == != //Looks at tokens on left and right of itself
#define Token_PreOperator 4 // & | # //Looks at token right of itself
#define Token_Call 5        // ret ; ~ //standalone call without need for ()

//Lets say size_t is 32 bit
//Last 7 bits (of 32) are used to group tokenTypes (group mask: F 1110 00 0000 = FE00 0000 )
//Last 8th bit (of 32) is used to indicate if the token carries data (group mask: 0 0001 00 0000 = 0100 0000 )
//Allowing 2^7 (128) SubTokenGroups, Data yes or no, and 2^24 (16777216) TokenGroups
#define GetTokenGroup(INDEX) ((((unsigned int)INDEX) & 0xFE000000) >> 25)
#define GetTokenData(INDEX) ((((unsigned int)INDEX) & 0x01000000) >> 24)

enum class TokenType : std::size_t
{

#define ENCODE_TOKEN(HAS_DATA) (__COUNTER__ | ((GROUP << 25) | (HAS_DATA << 24))) //Encode group into index
#define Token ENCODE_TOKEN(0)
#define DataToken ENCODE_TOKEN(1)

#define GROUP Token_Identifier
    Identifier = DataToken, //identifier
#undef GROUP

#define GROUP Token_Complex
    Parenthesized = DataToken, //()
    Bracketed = DataToken,     //[]
    Braced = DataToken,        //{}
    Dotted = DataToken,        // . symbol: box.attrs.color , box.$color.r , box.attrs.area() , array.0
#undef GROUP

#define GROUP Token_Literal
    Null = DataToken,              // null
    LiteralIdentifier = DataToken, // $'test' = test
    LiteralInteger = DataToken,    // -6 , 456, \0A2E21
    LiteralDecimal = DataToken,    // 2.3 , -0.2 , .1 , -.321
    LiteralString = DataToken,     //all strings are multiline, you can use `"' in strings: "`'string'`", `'"string"'`, 'a'
#undef GROUP

#define GROUP Token_PreOperator
    IdentifierFrom = Token, // $ symbol: $var -> identifier from value of var (string) MacroSign = Token, // # symbol: #fn(){} , #fn()
#undef GROUP


#undef ENCODE_TOKEN
#undef Token
#undef DataToken
};

//TokenizerState Groups:
#define TokenizerState_Normal 0
#define TokenizerState_InComment 1
#define TokenizerState_InLiteral 2

//Similar to token groups, last 7 bits (of 32) are used to group TokenizerStateGroups
#define GetTokenizerStateGroup(INDEX) ((((unsigned int)INDEX) & 0xFE000000) >> 25)

enum class TokenizerState : uint_fast32_t
{

#define State (__COUNTER__ | ((GROUP << 25))) //Encode group into index

#define GROUP TokenizerState_Normal
    Normal,
#undef GROUP

#define GROUP TokenizerState_InComment
    InComment = State,
    InCommentMultiline = State,
#undef GROUP

#define GROUP TokenizerState_InLiteral
    InStringQuote = State,
    InStringDoubleQuote = State,
    InStringBacktick = State,
    InInteger = State,
    InDecimal = State,
    InIdentifier = State
#undef GROUP

#undef State
};

struct Tokenizer;

union Token {
    std::size_t ptr;
    std::intmax_t i;
    double d;
};

struct TokenPack
{

    //We will cast std::size_t to:
    //TokenType type;
    //void* data;
    /*
    //Vector structure example:
    TokenType (token type without data)
    TokenType (token type without data)
    TokenType (token type with data)
    data (index of data or )
    TokenType (token type without data)
    */
    std::vector<Token> tokens;

    //Identifier strings and their id, id gets used in tokenStream
    std::unordered_map<std::string, std::size_t> identifiers;
    //Literal string and identifier data
    std::vector<std::string> stringData;
    //decimals and integers are casted from std::size_t

    TokenPack(const std::string &code);

    void Debug();
    void DebugStep(Tokenizer *t);

    std::string GetIdentifierById(std::size_t id);
    
    inline void AddToken(Tokenizer *t, TokenType token);
    inline void AddToken(Tokenizer *t, Token token);
    inline Token StoreIdentifier(Tokenizer *t);
    inline Token StoreString(Tokenizer *t);
    inline bool AddIdentifier(Tokenizer *t);
    inline void AddLiteralInteger(Tokenizer *t);
    inline void AddLiteralDecimal(Tokenizer *t);
    inline void AddLiteralString(Tokenizer *t);
    inline void AddLiteralIdentifier(Tokenizer *t);
};

struct Tokenizer
{
    TokenPack *tokenPack;

    std::size_t identifierCounter;

    //char pc; // previous char//////////////////////Dok se ne ispravi pc == ':' || pc == '=' || pc =='^' nema!
    char c; // current char
    bool escapeNext;
    TokenizerState state;
    std::string charBuffer;

    //sum of all lower (inner) tokens.length()
    //used so you know where each tree ends
    std::vector<std::size_t> tokenTreeStack;
    /*
    //count is used for serializing all tokens into flat vector (if compiling)
    //not needed if going to be executed

    token
    token
    token(token tree)
    7 (num of nodes till closing brace/bracket/parenthese/identifier)
    {
        token(var 1)
        token(token tree)
        3 (num of nodes till closing brace/bracket/parenthese/identifier)
        {
            token(var a)
            token(var b)
            token(var c)
        }
        token(var 2)
    }
    token
    token

    */

    Tokenizer(TokenPack *_tokenPack);

    void FeedChar();
    bool HandleSpecial(unsigned int helperStateGroup);
    bool HandleComments(unsigned int helperStateGroup);
    bool HandleLiterals(unsigned int helperStateGroup);
    bool HandleFeedChar(unsigned int helperStateGroup);
    inline bool IsValidIdentifierChar(char c, bool first = true);
    inline void ResetAll();
    inline void ResetBuffer();
};