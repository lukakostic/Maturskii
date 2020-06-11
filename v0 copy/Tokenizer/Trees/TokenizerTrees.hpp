#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"
#include "Tokenizer/TokenPack.hpp"
#include "Tokenizer/Trees/TokenizerTreesTokens.hpp"


struct TokenizerTrees
{
    Tokenizer *tokenizer;

    std::vector<Instruction> *wordTokens;

    std::vector<Instruction> tokens;

    TokenizerTrees(Tokenizer *_tokenizer, std::vector<Instruction> *_wordTokens);

    bool GetToken(IndexType index, int offset, Instruction *i);
    bool GetWToken(IndexType index, int offset, Instruction *i);
    void AddToken(TokenizerTreeToken t);
    void AddToken(Instruction t);


    Instruction GetLast(int offsetFromEnd = 0);
    Instruction PopLast(int offsetFromEnd = 0);
    
    void FeedWTokens();

    void Debug(IndexType i = 0, bool single = false);
};