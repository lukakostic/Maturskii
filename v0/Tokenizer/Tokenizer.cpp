#include <inttypes.h>
#include <iostream>
#include "Tokenizer.hpp"
#include "Tokenizer/TokenizerStates.hpp"
#include "Tokens.hpp"


Tokenizer::Tokenizer(TokenPack *_tokenPack, const std::string &code)
{
  tokenPack = _tokenPack;

  state = TokenizerState::Normal;
  stateGroup = TokenizerState_Normal;
  
  pc = '\0';
  c = '\0';
  escapeNext = false;
  chars = std::string();
  
	DBG std::cout << "\n\n------Code-----\n\n";/////////////////////////////
  DBG std::cout << code;
	DBG std::cout << "\n\n---------------\n\n";/////////////////////////////

  
  currentTree = tokenPack->AddTree(Tree::TreeType::Package);
  AddTreeStack(currentTree);

  for (char const &ch : code){
    //DBG std::cout << ":" << ch;/////////////////////////////
    FeedChar(ch);
  }

  FeedChar('\0');
  
}

IndexType Tokenizer::AddTreeStack(IndexType tree){
  treeStack.push_back(tree);
  return tree;
}
IndexType Tokenizer::PopTreeStack(){
  treeStack.pop_back();
  return treeStack[treeStack.size()-1];
}

void Tokenizer::ChangeState(TokenizerState newState){
  state = newState;
  stateGroup = DecodeGroup((Token)state); //So we dont need to calculate every time
}


void Tokenizer::Break(){
  if(chars.size() == 0){
    DBG std::cout<<"\nBreak\n";///////////////////////////////
    return;
  }
  DBG std::cout <<"\nBreak: '"<<chars<<"' state ["<<DecodeIndex((Token)TokenizerState::Normal)<<"/ "<<DecodeIndex((Token)state)<<" /"<<DecodeIndex((Token)TokenizerState::InStringBacktick)<<"]\n";///////////////////////////////////
  
  if(state == TokenizerState::Normal)
  {
    tokenPack->AddToken(currentTree, Tokens::Identifier);
    Instruction t;
    t.data.s = tokenPack->AddIdentifier(chars);
    tokenPack->AddToken(currentTree, t);
  }
  else if(state == TokenizerState::InInteger)
  {
    tokenPack->AddToken(currentTree, Tokens::LiteralInteger);
    Instruction t;
    t.data.i = std::stoll(chars);
    tokenPack->AddToken(currentTree, t);
  }
  else if(state == TokenizerState::InDecimal)
  {
    tokenPack->AddToken(currentTree, Tokens::LiteralDecimal);
    Instruction t;
    t.data.d = std::stod(chars);
    tokenPack->AddToken(currentTree, t);
  }
  else if(stateGroup == TokenizerState_InStringLiteral)
  {
    tokenPack->AddToken(currentTree, Tokens::LiteralString);
    Instruction t;
    t.data.s = tokenPack->AddString(chars);
    tokenPack->AddToken(currentTree, t);
  }

  DBG std::cout << '[' << chars << ']';/////////////////////////////

  ChangeState(TokenizerState::Normal); //Situations when you shouldnt?
  chars = std::string();
}



void Tokenizer::FeedChar(char ch){
  pc = c;
  c = ch;


  if(
  HandleComments() == false &&
  HandleSpecial() == false &&
  HandleStringLiterals() == false &&
  HandleNumberLiterals() == false &&
  HandleNormal() == false
  ){
      std::cout<<"\nTOKENIZER UNHANDLED\n";
      for(;;){}
  }
}


bool Tokenizer::HandleComments(){
	
	//See if you should exit comment mode
	if (stateGroup == TokenizerState_InComment)
  {
    //Exit comment mode or stay, either way handled = true
    
    if (state == TokenizerState::InComment && (c == '\n' || c=='\r' ))
        ChangeState(TokenizerState::Normal);
    else if (state == TokenizerState::InCommentMultiline && pc == '*' && c == '/')
        ChangeState(TokenizerState::Normal);
    
    return true;
  }
  //See if you should enter comment mode
  else if(pc == '/' && stateGroup != TokenizerState_InStringLiteral)
  {
    if(c=='*'){
      chars.pop_back();
      ////////////////////////////////PopLast(); //remove '/'
      Break(), ChangeState(TokenizerState::InCommentMultiline);
      return true;
    }
    else if(c=='/'){
      chars.pop_back();
      ////////////////////////////////PopLast(); //remove '/'
      Break(), ChangeState(TokenizerState::InComment);
      return true;
    }
  }

  return false;
}




bool Tokenizer::HandleStringLiterals(){
  //Exit or add char to string
  if (stateGroup == TokenizerState_InStringLiteral)
  {
    if (escapeNext == true){
      chars.push_back(EscapeChar(c));
      escapeNext = false;
      return true;
    }else if (c == '\\'){
      escapeNext = true;
      return true;
    }

    //Exit string if correct quote encountered
    if (
    (state == TokenizerState::InStringQuote && c == '\'') ||
    (state == TokenizerState::InStringDoubleQuote && c == '"') ||
    (state == TokenizerState::InStringBacktick && c == '`')
    ){
      Break(), ChangeState(TokenizerState::Normal);
      return true;
    }

    //If still in string, add char
    chars.push_back(c);

    return true;
  }
  //Enter string if needed
  else if(state == TokenizerState::Normal)
  {
    if (c == '\''){
      Break(), ChangeState(TokenizerState::InStringQuote);
      return true;
    }else if (c == '"'){
      Break(), ChangeState(TokenizerState::InStringDoubleQuote);
      return true;
    }else if (c == '`'){
      Break(), ChangeState(TokenizerState::InStringBacktick);
      return true;
    }
  }

  return false;
}

bool Tokenizer::HandleNumberLiterals(){
  //Turn to decimal or push char
  if (stateGroup == TokenizerState_InNumberLiteral)
  {
    //Turn to decimal if . found in number
    if(c == '.'){
      ChangeState(TokenizerState::InDecimal);
      chars.push_back('.');
      return true;
    }else{
      chars.push_back(c); //Keep adding chars, special will exit when needed.
      return true;
    }
  }
  //Enter number?
  else if(state == TokenizerState::Normal)
  {
    //If not part of identifier (if digit first char)
    if(chars.size() == 0 && isdigit(c)){
      ChangeState(TokenizerState::InInteger);
      chars.push_back(c);
      return true;
    }
  }
  return false;
}

bool Tokenizer::HandleNormal(){
	if(state == TokenizerState::Normal)
  {
    //Not handled yet, still in identifier so push char
    chars.push_back(c);
    return true; 
  }

  return false;
}
