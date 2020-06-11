#pragma once
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"
#include "TokenPack.hpp"
#include "Runtime/Variables.hpp"


struct Runtime
{
  enum RuntimeType{
    Global,
    Local,
    Function
  } type;
  Runtime* parentRuntime;
  TokenPack* tokenPack;
  Variables::Function fn;

  std::vector<Variables::TypedData> stack;

  std::unordered_map<IndexType, Variables::TypedData> variables;
  std::vector<Instruction>* tokens;

  //Storages
  std::list<Variables::Function> functions;
  std::list<Variables::Object> objects;
  std::list<Number> numbers;
  std::list<std::string> strings;

  Runtime(Runtime* _parentRuntime, RuntimeType rType, TokenPack* _tokenPack, Variables::Function _fn);

  bool At(int indx, IndexType tree, Instruction* token);
  bool IsTokenAt(int indx, IndexType tree, Instruction* token, Tokens isAt);

  inline bool StackPushNotNull(Variables::TypedData td){
    if(td.type != Variables::TypedData::Type::Null){
      stack.push_back(td);
      return true;
    }
    return false;
  };
  bool ToNextComma(IndexType tree, int* i);

  
  Variables::TypedData Run(std::vector<Variables::TypedData> arguments);

  bool Handle_FnCalls(IndexType tree, int* i);
  //bool Handle_Values(IndexType tree, int* i);
  bool Resolve(IndexType tree, int* i, Variables::TypedData* out); //parentheses and identifier data

  Variables::TypedData InternalFunction(IndexType identifier);

  Variables::TypedData CallFn(IndexType identifier, IndexType argumentTree);

};
