#include <iostream>
#include <vector>

#include "TokenStructs.hpp"
#include "TokenPack.hpp"

TokenPack::TokenPack()
{
  trees = std::vector<Tree>();

  identifierCount = 0;
  identifierToIndex = std::unordered_map<std::string, IndexType>();
  indexToIdentifier = std::unordered_map<IndexType, std::string>();

  strings = std::vector<std::string>();

  FillReservedIdentifiers();
}



void TokenPack::AddToken(IndexType tree, Tokens t){
  //DBG std::cout<<"\nT\n";
  AddToken(tree, {(Token)t});
}
void TokenPack::AddToken(IndexType tree, Instruction t){
  //DBG std::cout<<"\nI <" << tree << ">\n";
  //trees[tree].tokens.push_back({0});
  trees[tree].tokens.push_back(t);
}
IndexType TokenPack::AddTreeToken(IndexType tree, Tree::TreeType treeType){
  AddToken(tree, Tokens::Tree);
  
  Instruction t;
  t.data.s = trees.size();
  AddToken(tree, t);
  IndexType i = AddTree(treeType);
  //Instruction t;t.s = i;AddToken(tree, t); //error
  
  return i;
}

bool TokenPack::GetToken(IndexType tree, IndexType index, int offset, Instruction *i){
  int ind = index + offset;
  if(ind>=0 && ind<trees[tree].tokens.size()){
    *i = trees[tree].tokens[(trees[tree].tokens.size()-1) + offset];
    return true;
  }

  return false;
}
bool TokenPack::GetLastToken(IndexType tree, int offsetFromEnd, Instruction *i){
  if(trees[tree].tokens.size()>offsetFromEnd){
    *i = trees[tree].tokens[(trees[tree].tokens.size()-1) - offsetFromEnd];
    return true;
  }

  return false;
}

IndexType TokenPack::AddIdentifier(std::string word){
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
std::string TokenPack::GetIdentifier(IndexType indx){
  auto find = indexToIdentifier.find(indx);
  return find->second;
}


IndexType TokenPack::AddString(std::string word){
  strings.push_back(word);
  return strings.size()-1; //end
}
std::string TokenPack::GetString(IndexType indx){
  return strings[indx];
}


IndexType TokenPack::AddTree(Tree::TreeType treeType){
  Tree tree = Tree(treeType);
  trees.push_back(tree);
  //DBG std::cout << "\ntrees size:" << trees.size() << "\n";
  return trees.size()-1; //end
}
Tree* TokenPack::GetTree(IndexType indx){
  return &trees.at(indx); //end
}


void TokenPack::Build(const std::string &code){

  auto t = new Tokenizer(this, code);
  
  DBG std::cout << "\n\n-----DEBUG-----\n\n";/////////////////////////////
	DBG Debug(0);
  DBG std::cout << "\n\n---------------\n\n";/////////////////////////////
  
}


void TokenPack::Debug(IndexType tree, IndexType i, bool single, int maxDepth, int depth){
  IndexType len = trees[tree].tokens.size();

  for(; i<len; i++){
    Tokens tt = TokenAt(tree,i);
    //std::cout<<"["<<tree<<"]:"<<i<<":\n";
    if(tt == Tokens::Identifier){
      std::cout << "Identifier [" << GetIdentifier(trees[tree].tokens[++i].data.s) << "]\n";
    }else if(tt == Tokens::LiteralString){
      std::cout << "String [" << GetString(IndexAt(tree,++i)) << "]\n";
    }else if(tt == Tokens::LiteralInteger){
      std::cout << "Integer [" << trees[tree].tokens[++i].data.i << "]\n";
    }else if(tt == Tokens::LiteralDecimal){
      std::cout << "Decimal [" << trees[tree].tokens[++i].data.d << "]\n";
    }else if( DecodeGroup(trees[tree].tokens[i].t) == Tokenizer_Special){
      std::cout << "Spec\n";
    }else if(tt == Tokens::Tree){
      std::cout << "Tree ";
      auto nd = IndexAt(tree,++i);
      std::cout<< nd <<"{\n";
      if(depth<maxDepth&&maxDepth!=-1)
        Debug(nd,0,false,depth+1,maxDepth);
      else
        std::cout<<"...\n";
      std::cout << "}\n";
    }else{
      std::cout << "?\n";
    }
    if(single)break;
  }
  
}

void TokenPack::FillReservedIdentifiers(){
  AddIdentifier("null"); //0
  AddIdentifier("print"); //1
  AddIdentifier("+"); //2

}

