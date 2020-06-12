#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "TokenStructs.hpp"

struct TokenPack;

#include "Tokenizer/Tokenizer.hpp"

struct TokenPack
{
  std::vector<Tree> trees;

  //bidirectional map, vector of all identifiers
  //both index and string must be unique
  IndexType identifierCount;
  std::unordered_map<std::string, IndexType> identifierToIndex;
  std::unordered_map<IndexType, std::string> indexToIdentifier;

  //List of all string literals
  std::vector<std::string> strings;

  
  TokenPack();
  
  inline Tokens TokenAt(IndexType tree, IndexType i){
     //std::cout<<"TA["<<tree<<"]<"<<i<<"\n";
     //std::cout <<"TA " << TO_BITS(((Tokens)trees[tree].tokens[i].t)) << "   " << TO_BITS(Tokens::Identifier) << "\n";
    return (Tokens)trees[tree].tokens[i].t;
  }
  inline IndexType IndexAt(IndexType tree, IndexType i){
    return trees[tree].tokens[i].data.s;
  }

  void AddToken(IndexType tree, Tokens t);
  void AddToken(IndexType tree, Instruction t);
  IndexType AddTreeToken(IndexType tree, Tree::TreeType treeType);
  bool GetToken(IndexType tree, IndexType index, int offset, Instruction *i);
  bool GetLastToken(IndexType tree, int offsetFromEnd, Instruction *i);


  IndexType AddIdentifier(std::string word);
  std::string GetIdentifier(IndexType indx);

  IndexType AddString(std::string word);
  std::string GetString(IndexType indx);

  IndexType AddTree(Tree::TreeType treeType);
  Tree* GetTree(IndexType indx);
  

  void Build(const std::string &code);
  
  void Debug(IndexType tree, IndexType i = 0, bool single = false, int maxDepth = -1, int depth = 0);

  void FillReservedIdentifiers();
};