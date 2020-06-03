#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"
#include "Tokenizers.hpp"

//TokenizerState Groups:
#define TokenizerWord_Normal 0
#define TokenizerWord_InComment 1
#define TokenizerWord_InNumberLiteral 2
#define TokenizerWord_InStringLiteral 3

enum class TokenizerWord : TokenType
{

#define GROUP TokenizerWord_Normal
    Normal = TOKEN,
#undef GROUP

#define GROUP TokenizerWord_InComment
    InComment = TOKEN,
    InCommentMultiline = TOKEN,
#undef GROUP

#define GROUP TokenizerWord_InNumberLiteral
    InInteger = TOKEN,
    InDecimal = TOKEN,
#undef GROUP

#define GROUP TokenizerWord_InStringLiteral
    InStringQuote = TOKEN,
    InStringDoubleQuote = TOKEN,
    InStringBacktick = TOKEN,
#undef GROUP

};



struct Tokenizer_Words
{
    TokenizerWord state;
    char c; // current char
    char pc; // previous char. dont rely on it, use c mainly.
    
    bool escapeNext; //used in string literals
    std::string chars; //current word

    std::vector<Token> tokens;

    //bidirectional map, vector of all words (identifiers or string literals).
    //both index and string must be unique
    //word counter, increments when added
    std::size_t word_count;
    std::unordered_map<std::string, std::size_t> word_str2index;
    std::unordered_map<std::size_t, std::string> word_index2str;

    Tokenizer_Words(const std::string &code);

    std::size_t AddWord(std::string word);

    void AddToken(TokenizerToken t);
    void AddToken(Token t);
    void Break(); //Space or other break encountered, end current identifier

    void FeedChar(char ch); //process next char
    bool HandleComments(unsigned int helperStateGroup);
    bool HandleSpecial(unsigned int helperStateGroup);
    bool HandleNormal(unsigned int helperStateGroup);

};