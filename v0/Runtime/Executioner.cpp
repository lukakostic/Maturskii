#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"
#include "TokenPack.hpp"
#include "Runtime/Variables.hpp"
#include "Runtime/Runtime.hpp"
#include "Runtime/Executioner.hpp"

void Executioner::Run(TokenPack* _tokenPack)
{
  tokenPack = _tokenPack;
  runtimes = std::vector<Runtime*>();

  currentRuntime = 0;

  Variables::Function fn = Variables::Function();
  fn.bodyTree = 0;

  auto rt = new Runtime(nullptr, Runtime::RuntimeType::Global, _tokenPack, fn);

  rt->variables.insert({0,{Variables::TypedData::Type::Null,nullptr}}); //null literal

  rt->variables.insert({1,{Variables::TypedData::Type::InternalFunction,nullptr}}); //print
  rt->variables.insert({2,{Variables::TypedData::Type::InternalFunction,nullptr}}); //print

  runtimes.push_back(rt);
  rt->Run(std::vector<Variables::TypedData>());
}