#pragma once
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"
#include "TokenPack.hpp"
#include "Runtime/Variables.hpp"
#include "Runtime/Runtime.hpp"

struct Executioner
{
  TokenPack* tokenPack;
  std::vector<Runtime*> runtimes;
  IndexType currentRuntime;

  void Run(TokenPack* _tokenPack);
};