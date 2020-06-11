#include <inttypes.h>
#include <iostream>
#include "TokenizerTrees.hpp"
#include "Tokenizer/TokenPack.hpp"
#include "Tokenizer/Trees/TokenizerTreesTokens.hpp"


TokenizerTrees::TokenizerTrees(Tokenizer *_tokenizer, std::vector<Instruction> *_wordTokens){
  tokenizer = _tokenizer;

  wordTokens = _wordTokens;
  tokens = std::vector<Instruction>();

  FeedWTokens();
  
}

bool TokenizerTrees::GetToken(IndexType index, int offset, Instruction *out){
  int indx = (((int)index)+offset);
  if(indx<0||indx>=tokens.size()) return false;
  *out = tokens[indx];
  return true;
}
bool TokenizerTrees::GetWToken(IndexType index, int offset, Instruction *out){
  int indx = (((int)index)+offset);
  if(indx<0||indx>=wordTokens->size()) return false;
  *out = wordTokens->at(indx);
  return true;
}
void TokenizerTrees::AddToken(TokenizerTreeToken t){
  tokens.push_back({(Token)t});
}
void TokenizerTrees::AddToken(Instruction t){
  tokens.push_back(t);
}



Instruction TokenizerTrees::GetLast(int offsetFromEnd){
  if(tokens.size()>offsetFromEnd) return tokens[(tokens.size()-1) - offsetFromEnd];

  Instruction t;
  t.u = 0; //unassigned
  return t;
}
Instruction TokenizerTrees::PopLast(int offsetFromEnd){
  Instruction t;
  t.u = 0; //unassigned
  if(tokens.size()>offsetFromEnd) t = tokens[(tokens.size()-1) - offsetFromEnd];
  tokens.pop_back();
  return t;
}




void TokenizerTrees::Debug(IndexType i, bool single){
  IndexType len = tokens.size();

  for(; i<len; i++){
    TokenizerTreeToken tt = (TokenizerTreeToken)tokens[i].t;
    /*
    if(tt == TokenizerTreeToken::Identifier){
      std::cout << "Identifier [" << tokenizer->GetIdentifier(tokens[++i].s) << "]\n";
    }else if(tt == TokenizerTreeToken::LiteralString){
      std::cout << "String [" << tokenizer->GetString(tokens[++i].s) << "]\n";
    }else if(tt == TokenizerTreeToken::LiteralInteger){
      std::cout << "Integer [" << tokens[++i].i << "]\n";
    }else if(tt == TokenizerTreeToken::LiteralDecimal){
      std::cout << "Decimal [" << tokens[++i].d << "]\n";
    }else if( DecodeGroup(tokens[i].t) == TokenTree_Special){
      std::cout << "Spec\n";
    }else{
      std::cout << "?\n";
    }
    */
    if(single)break;
  }
  
}