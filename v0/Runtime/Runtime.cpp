#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"
#include "Tokens.hpp"
#include "TokenPack.hpp"
#include "Runtime/Variables.hpp"

#include "Runtime/Runtime.hpp"


Runtime::Runtime(Runtime* _parentRuntime, RuntimeType rType, TokenPack* _tokenPack, Variables::Function _fn)
{
  type = rType;
  parentRuntime = _parentRuntime;
  tokenPack = _tokenPack;
  fn = _fn;
  stack = std::vector<Variables::TypedData>();

  variables = std::unordered_map<IndexType, Variables::TypedData>();

  functions = std::list<Variables::Function>();
  objects = std::list<Variables::Object>();
  numbers = std::list<Number>();
  strings = std::list<std::string>();
}




bool Runtime::At(int indx, IndexType tree, Instruction* token){
  if(indx<0 || indx >= tokenPack->trees[tree].tokens.size()) return false;
  *token = tokenPack->trees[tree].tokens[indx];
  return true;
}
bool Runtime::IsTokenAt(int indx, IndexType tree, Instruction* token, Tokens isAt){
  if(indx<0 || indx >= tokenPack->trees[tree].tokens.size()) return false;
  if(token!=nullptr)*token = tokenPack->trees[tree].tokens[indx];
  if((Tokens)(tokenPack->trees[tree].tokens[indx].t) == isAt)return true;
  return false;
}



bool Runtime::ToNextComma(IndexType tree, int* i){
  *i = *i + 1;
  for (; *i < tokenPack->trees[tree].tokens.size(); *i++)
  {
    if(tokenPack->TokenAt(tree,*i) == Tokens::Comma) return true;
  }
  return false;
}






//Identifier or literals to value
bool Runtime::Resolve(IndexType tree, int* i, Variables::TypedData* out){
  if(tokenPack->TokenAt(tree,*i) == Tokens::Identifier)
  {
    auto f = variables.find(tokenPack->IndexAt(tree,*i+1));

    if(f == variables.end()){
      std::cout << "COULDNT FIND IDENTIFIER";
      for(;;){}
    }

    *out = f->second;
    *i = *i + 1;
    return true;
  }
  else if(tokenPack->TokenAt(tree,*i) == Tokens::LiteralDecimal)
  {
    double d = tokenPack->trees[tree].tokens[*i+1].data.d;
    Number n;
    n.d = d;
    numbers.push_back(n);
    out->type = Variables::TypedData::Type::Decimal;
    out->dataPtr = {&numbers.back()};
    *i = *i + 1;
    return true;
  }
  else if(tokenPack->TokenAt(tree,*i) == Tokens::LiteralInteger)
  {
    auto d = tokenPack->trees[tree].tokens[*i+1].data.i;
    Number n;
    n.i = d;
    numbers.push_back(n);
    out->type = Variables::TypedData::Type::Integer;
    out->dataPtr = {&numbers.back()};
    *i = *i + 1;
    return true;
  }
  else if(tokenPack->TokenAt(tree,*i) == Tokens::LiteralString)
  {
    strings.push_back(tokenPack->strings[tokenPack->trees[tree].tokens[*i+1].data.s]);
    out->type = Variables::TypedData::Type::String;
    out->dataPtr = {&strings.back()};
    *i = *i + 1;
    return true;
  }
  return false;
}
