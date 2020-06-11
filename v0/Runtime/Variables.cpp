#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"
#include "Runtime/Variables.hpp"

namespace Variables
{
  Function::Function(){
    argumentsTree = 0;
    bodyTree = 0;
  }
}