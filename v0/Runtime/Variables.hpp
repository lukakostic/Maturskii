#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "TokenStructs.hpp"

namespace Variables
{
  struct Object;
  struct Function;
  union Number;


  struct TypedData
  {
    enum class Type
    {
      Object,
      Function,

      InternalFunction,

      Array,  //actually an object
      String, //actually an array of int which is actually an object

      //No data
      Null,

      //NumberData
      Integer,
      Decimal,
    } type;
    void* dataPtr;
  };

  struct Object
  {
    std::unordered_map<IndexType, TypedData> properties;
  };

  struct Function
  {
    IndexType argumentsTree;
    IndexType bodyTree;

    Function();
  };

}