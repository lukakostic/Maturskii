#pragma once
#include <vector>
#include <string>
#include <unordered_map>


#include "Tokenizer/TokenizerStates.hpp"
#include "Tokens.hpp"

#include "TokenPack.hpp"

struct Tokenizer
{
    TokenPack *tokenPack;
    

    TokenizerState state;
    unsigned stateGroup; //so we dont need to calc every time

    /////////////// character ops ///////////////
    char c; // current char
    char pc; // previous char. dont rely on it, use c mainly.
    std::string chars; //current word

    bool escapeNext; //used in string literals
    /////////////////////////////////////////////
    
    /////////////// tree ops ///////////////
    std::vector<IndexType> treeStack;
    IndexType currentTree;
    /////////////////////////////////////////////
    
    Tokenizer(TokenPack *_tokenPack, const std::string &code);

    IndexType AddTreeStack(IndexType tree);
    IndexType PopTreeStack();


    void ChangeState(TokenizerState newState); //Change and calculate group
    
    void Break(); //Space or other break encountered, end current token

    void FeedChar(char ch); //process next char
    bool HandleComments();
    bool HandleSpecial();
    bool HandleStringLiterals();
    bool HandleNumberLiterals();
    bool HandleNormal();

    char EscapeChar(char c);

};