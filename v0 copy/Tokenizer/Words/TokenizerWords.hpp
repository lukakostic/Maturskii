#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"
#include "Tokenizer/TokenPack.hpp"
#include "Tokenizer/Words/TokenizerWordsStates.hpp"
#include "Tokenizer/Words/TokenizerWordsTokens.hpp"


struct TokenizerWords
{
    Tokenizer *tokenizer;

    TokenizerWordState state;
    unsigned stateGroup; //so we dont need to calc every time

    char c; // current char
    char pc; // previous char. dont rely on it, use c mainly.
    
    bool escapeNext; //used in string literals
    std::string chars; //current word

    std::vector<Instruction> tokens;


    TokenizerWords(Tokenizer *_tokenizer, const std::string &code);


    void ChangeState(TokenizerWordState newState); //Change and calculate group

    void AddToken(TokenizerWordToken t);
    void AddToken(Instruction t);
    void Break(); //Space or other break encountered, end current token

    Instruction GetLast(int offsetFromEnd = 0);
    Instruction PopLast(int offsetFromEnd = 0);
    
    void FeedChar(char ch); //process next char
    bool HandleComments();
    bool HandleSpecial();
    bool HandleStringLiterals();
    bool HandleNumberLiterals();
    bool HandleNormal();

    char EscapeChar(char c);

    void Debug(IndexType i = 0, bool single = false);
};