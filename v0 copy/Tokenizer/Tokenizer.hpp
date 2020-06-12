#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Tokens.hpp"

struct Tokenizer;

#include "Tokenizer/Words/TokenizerWords.hpp"
#include "Tokenizer/Trees/TokenizerTrees.hpp"

struct Tokenizer
{
  //bidirectional map, vector of all identifiers
  //both index and string must be unique
  IndexType identifierCount;
  std::unordered_map<std::string, IndexType> identifierToIndex;
  std::unordered_map<IndexType, std::string> indexToIdentifier;

  //List of all string literals
  std::vector<std::string> strings;

  //All trees
  std::vector<Tree> trees;
  
  Tokenizer();
  
  IndexType AddIdentifier(std::string word);
  std::string GetIdentifier(IndexType indx);

  IndexType AddString(std::string word);
  std::string GetString(IndexType indx);

  IndexType AddTree(Tree::TreeType treeType);
  Tree* GetTree(IndexType indx);
  
  void FillReservedIdentifiers();

  void Build(const std::string &code);
};