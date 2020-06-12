#include "Runtime/Runtime.hpp"

Variables::TypedData Runtime::Run(std::vector<Variables::TypedData> arguments)
{
  DBG std::cout<<"\n-----------RUN-----------\n";
  DBG tokenPack->Debug(fn.bodyTree,0,false,1,0);
  DBG std::cout<<"\n-------------------------\n";

  /*
  Main parts are:

  defining
  calling functions
  built in functions calling backend c++ code
  */
  Instruction helper;
  for (int i = 0; i < tokenPack->trees[fn.bodyTree].tokens.size(); i++)
  {
    //tokenPack->Debug(fn.bodyTree,i,true,0,0);
    stack.clear();
    if(
      Handle_FnCalls(fn.bodyTree, &i) == false //handle function calls
    ){
      if(tokenPack->TokenAt(fn.bodyTree,i) == Tokens::Identifier)
      {
        IndexType identifier = tokenPack->IndexAt(fn.bodyTree,i+1);
        if(IsTokenAt(i+2, fn.bodyTree, nullptr, Tokens::Equal))
        {
          //Assignment
          i+=3;
          Instruction ins1;
          Instruction ins2;
          if(At(i, fn.bodyTree, &ins1) && ((Tokens)ins1.t) == Tokens::Tree && At(i+2, fn.bodyTree, &ins2) && ((Tokens)ins2.t) == Tokens::Tree){
            At(i+1, fn.bodyTree, &ins1);
            At(i+3, fn.bodyTree, &ins2);
            //DBG std::cout <<"FN DEF\n";
            Variables::TypedData data;

            Variables::Function fn2;
            fn2.argumentsTree = ins1.data.s;
            fn2.bodyTree = ins2.data.s;

            functions.push_back(fn2);
            data.type = Variables::TypedData::Type::Function;
            data.dataPtr = &functions.back();

            variables[identifier] = data;
            i+=3;
          }else{
            Variables::TypedData data;
            if(Resolve(fn.bodyTree, &i, &data)){
              //std::cout << "INSERTING " << (int)data.type << " INTO " << tokenPack->GetIdentifier(identifier);
              variables[identifier] = data;
            }else{
              std::cout<<"COULDNT RESOLVE";
              for(;;){}
            }
          }
        }
      }
      //std::cout<<"\nUNHANDLED\n";
      //for(;;){}
    }

  }
  

  return Variables::TypedData{Variables::TypedData::Type::Null, nullptr};
}



Variables::TypedData Runtime::CallFn(IndexType identifier, IndexType argumentTree){
  DBG std::cout << "fnCALL: '" << tokenPack->GetIdentifier(identifier) << "'(\n";
  DBG tokenPack->Debug(argumentTree,0,false,1,0);
  
  for (int i = 0; i < tokenPack->trees[argumentTree].tokens.size(); i++)
  {
    if(
      Handle_FnCalls(argumentTree,&i) == false
    ){
      DBG std::cout<<"Handling values\n";
      Variables::TypedData out;
      //Handle values
      if(Resolve(argumentTree, &i, &out) == true){
        stack.push_back(out);
      }
      else if(ToNextComma(argumentTree,&i) == false) break;
    }
  }
  DBG std::cout << ")\n";
//std::cout << tokenPack->GetIdentifier(identifier);
  auto f = variables.find(identifier);
  if(f != variables.end()){
    if(identifier<2)
    return InternalFunction(identifier);
    
    //std::cout << ((Variables::Function*)f->second.dataPtr)->bodyTree;
    //Variables::Function
    //stack.clear();
    int l = 0;
    Handle_FnCalls(((Variables::Function*)f->second.dataPtr)->bodyTree, &l);
    //tokenPack->Debug(((Variables::Function*)f->second.dataPtr)->bodyTree);
  }else
  {
    std::cout << "UNKNOWN FN CALL NAME";
    for(;;){}
  }
  

  return Variables::TypedData{Variables::TypedData::Type::Null};
}




bool Runtime::Handle_FnCalls(IndexType tree, int* i)
{
  if(tokenPack->TokenAt(tree,*i) == Tokens::Identifier)
  {
    //Is next () tree? function call.
    if(IsTokenAt(*i+2, tree, nullptr, Tokens::Tree))
    {
      DBG std::cout<<"Handling FNCall\n";
      stack.push_back(CallFn(tokenPack->trees[tree].tokens[*i+1].data.s, tokenPack->trees[tree].tokens[*i+3].data.s));
      *i=*i+3;
      return true;
    }
  }
  return false;
}