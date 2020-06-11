#include "Runtime/Runtime.hpp"

Variables::TypedData Runtime::InternalFunction(IndexType identifier){
  if(identifier == 1) //print
  {
    auto td = stack.back();
    stack.pop_back();
  
    if(td.type == Variables::TypedData::Type::String){
      std::cout << *((std::string*)td.dataPtr);
    }else if(td.type == Variables::TypedData::Type::Integer){
      std::cout << *((int64_t*)td.dataPtr);
    }else if(td.type == Variables::TypedData::Type::Decimal){
      std::cout << *((double*)td.dataPtr);
    }else if(td.type == Variables::TypedData::Type::Object){
      std::cout << "[OBJECT]";
    }else if(td.type == Variables::TypedData::Type::Function){
      std::cout << "[FUNCTION]";
    }
     
  }else if(identifier == 2) //+
  {
    auto td = stack.back();
    stack.pop_back();
    auto td2 = stack.back();
    stack.pop_back();

    Number n;
    //numbers.push_back()
    //auto ret = td;

    if(td.type == Variables::TypedData::Type::Integer && td2.type == Variables::TypedData::Type::Integer){
      //ret.
    }else if(td.type == Variables::TypedData::Type::Decimal){
      std::cout << *((double*)td.dataPtr);
    }
    
    //return ret;
  }

  return Variables::TypedData{Variables::TypedData::Type::Null, nullptr};
}