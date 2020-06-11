#include <iostream>
#include <vector>
#include "Tokens.hpp"
#include "Tokenizer/TokenPack.hpp"

Tokenizer::Tokenizer(){

  identifierCount = 0;
  identifierToIndex = std::unordered_map<std::string, IndexType>();
  indexToIdentifier = std::unordered_map<IndexType, std::string>();

  FillReservedIdentifiers();
}

void Tokenizer::Build(const std::string &code){

  auto words = new TokenizerWords(this, code);
  
  std::cout << "\n\n-----Words-----\n\n";/////////////////////////////
	words->Debug();
  std::cout << "\n\n---------------\n\n";/////////////////////////////
  
  auto trees = new TokenizerTrees(this, &words->tokens);
  
  std::cout << "\n\n-----Trees-----\n\n";/////////////////////////////
	trees->Debug();
  std::cout << "\n\n---------------\n\n";/////////////////////////////
  
}

IndexType Tokenizer::AddIdentifier(std::string word){
  auto find = identifierToIndex.find(word);
  //If not already in list
  if(find == identifierToIndex.end()){
    identifierToIndex.insert({word, identifierCount});
    indexToIdentifier.insert({identifierCount, word});
    identifierCount++;
    return identifierCount-1; //end
  }
  return find->second;
}
std::string Tokenizer::GetIdentifier(IndexType indx){
  auto find = indexToIdentifier.find(indx);
  return find->second;
}


IndexType Tokenizer::AddString(std::string word){
  strings.push_back(word);
  return strings.size()-1; //end
}
std::string Tokenizer::GetString(IndexType indx){
  return strings[indx];
}


IndexType Tokenizer::AddTree(Tree::TreeType treeType){
    trees.push_back({treeType, std::vector<Instruction>()});
    return trees.size()-1; //end
}
Tree* Tokenizer::GetTree(IndexType indx){
    return &trees.at(indx); //end
}


void Tokenizer::FillReservedIdentifiers(){
  AddIdentifier("null"); //0

}

