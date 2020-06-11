#pragma once
#include<stdio.h>
#include<vector>
#include<string>

////
struct Data;
struct NamedData;
struct Variable;
////


enum class Type{
  Null,
  Integer,
  Decimal,
  Map,
  Array,
  Function,
  Reference,
  Identifier,
  Type
};

struct Map{
  std::vector<NamedData> pairs;

};

struct Data{
Type type;
void* data;

Data(){
type = Type::Null;
data = nullptr;
}
Data(int i){
type = Type::Integer;
data = new int(i);
}
Data(float i){
type = Type::Decimal;
data = new float(i);
}
Data(Map* i){
type = Type::Map;
data = i;
}
};

struct NamedData{
std::string name;
Data data;

NamedData(){
name = "";
data = Data();
}

NamedData(std::string _name):name(_name){}

NamedData(std::string _name,Data _data):name(_name),data(_data){}
};

struct Variable{
NamedData var;
};


