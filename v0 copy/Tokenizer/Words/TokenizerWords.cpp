#include <inttypes.h>
#include <iostream>
#include "TokenizerWords.hpp"
#include "Tokenizer/Words/TokenizerWordsStates.hpp"
#include "Tokenizer/Words/TokenizerWordsTokens.hpp"


TokenizerWords::TokenizerWords(Tokenizer *_tokenizer, const std::string &code)
{
  tokenizer = _tokenizer;
  state = TokenizerWordState::Normal;
  stateGroup = TokenizerWordState_Normal;
  
  pc = '\0';
  c = '\0';
  escapeNext = false;
  chars = std::string();
  tokens = std::vector<Instruction>();
  
	std::cout << "\n\n------Code-----\n\n";/////////////////////////////
  std::cout << code;
	std::cout << "\n\n---------------\n\n";/////////////////////////////

  for (char const &ch : code){
    std::cout << ch;/////////////////////////////
    FeedChar(ch);
  }

  FeedChar('\0');
}

void TokenizerWords::AddToken(TokenizerWordToken t){
  tokens.push_back({(Token)t});
}
void TokenizerWords::AddToken(Instruction t){
  tokens.push_back(t);
}



void TokenizerWords::Break(){
  std::cout <<"\nBreak: '"<<chars<<"' state ["<<DecodeIndex((Token)TokenizerWordState::Normal)<<"/ "<<DecodeIndex((Token)state)<<" /"<<DecodeIndex((Token)TokenizerWordState::InStringBacktick)<<"]\n";///////////////////////////////////
  if(chars.size() == 0)return;
  if(state == TokenizerWordState::Normal)
  {
    AddToken(TokenizerWordToken::Identifier);
    Instruction t;
    t.s = tokenizer->AddIdentifier(chars);
    AddToken(t);
  }
  else if(state == TokenizerWordState::InInteger)
  {
    AddToken(TokenizerWordToken::LiteralInteger);
    Instruction t;
    t.i = std::stoll(chars);
    AddToken(t);
  }
  else if(state == TokenizerWordState::InDecimal)
  {
    AddToken(TokenizerWordToken::LiteralDecimal);
    Instruction t;
    t.d = std::stod(chars);
    AddToken(t);
  }
  else if(stateGroup == TokenizerWordState_InStringLiteral)
  {
    AddToken(TokenizerWordToken::LiteralString);
    Instruction t;
    t.s = tokenizer->AddString(chars);
    AddToken(t);
  }

  std::cout << '[' << chars << ']';/////////////////////////////

  ChangeState(TokenizerWordState::Normal); //Situations when you shouldnt?
  chars = std::string();
}

Instruction TokenizerWords::GetLast(int offsetFromEnd){
  if(tokens.size()>offsetFromEnd) return tokens[(tokens.size()-1) - offsetFromEnd];

  Instruction t;
  t.u = 0; //unassigned
  return t;
}
Instruction TokenizerWords::PopLast(int offsetFromEnd){
  Instruction t;
  t.u = 0; //unassigned
  if(tokens.size()>offsetFromEnd) t = tokens[(tokens.size()-1) - offsetFromEnd];
  tokens.pop_back();
  return t;
}

void TokenizerWords::ChangeState(TokenizerWordState newState){
  state = newState;
  stateGroup = DecodeGroup((Token)state); //So we dont need to calculate every time
}

void TokenizerWords::FeedChar(char ch){
  pc = c;
  c = ch;


  if(
  HandleComments() == false &&
  HandleSpecial() == false &&
  HandleStringLiterals() == false &&
  HandleNumberLiterals() == false &&
  HandleNormal() == false
  ){
    //?
  }
}


bool TokenizerWords::HandleComments(){
	
	//See if you should exit comment mode
	if (stateGroup == TokenizerWordState_InComment)
  {
    //Exit comment mode or stay, either way handled = true
    
    if (state == TokenizerWordState::InComment && (c == '\n' || c=='\r' ))
        ChangeState(TokenizerWordState::Normal);
    else if (state == TokenizerWordState::InCommentMultiline && pc == '*' && c == '/')
        ChangeState(TokenizerWordState::Normal);
    
    return true;
  }
  //See if you should enter comment mode
  else if(pc == '/' && stateGroup != TokenizerWordState_InStringLiteral)
  {
    if(c=='*'){
      chars.pop_back();
      ////////////////////////////////PopLast(); //remove '/'
      Break(), ChangeState(TokenizerWordState::InCommentMultiline);
      return true;
    }
    else if(c=='/'){
      chars.pop_back();
      ////////////////////////////////PopLast(); //remove '/'
      Break(), ChangeState(TokenizerWordState::InComment);
      return true;
    }
  }

  return false;
}




bool TokenizerWords::HandleStringLiterals(){
  //Exit or add char to string
  if (stateGroup == TokenizerWordState_InStringLiteral)
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
    (state == TokenizerWordState::InStringQuote && c == '\'') ||
    (state == TokenizerWordState::InStringDoubleQuote && c == '"') ||
    (state == TokenizerWordState::InStringBacktick && c == '`')
    ){
      Break(), ChangeState(TokenizerWordState::Normal);
      return true;
    }

    //If still in string, add char
    chars.push_back(c);

    return true;
  }
  //Enter string if needed
  else if(state == TokenizerWordState::Normal)
  {
    if (c == '\''){
      Break(), ChangeState(TokenizerWordState::InStringQuote);
      return true;
    }else if (c == '"'){
      Break(), ChangeState(TokenizerWordState::InStringDoubleQuote);
      return true;
    }else if (c == '`'){
      Break(), ChangeState(TokenizerWordState::InStringBacktick);
      return true;
    }
  }

  return false;
}

bool TokenizerWords::HandleNumberLiterals(){
  //Turn to decimal or push char
  if (stateGroup == TokenizerWordState_InNumberLiteral)
  {
    //Turn to decimal if . found in number
    if(c == '.'){
      ChangeState(TokenizerWordState::InDecimal);
      chars.push_back('.');
      return true;
    }else{
      chars.push_back(c); //Keep adding chars, special will exit when needed.
    }
  }
  //Enter number?
  else if(state == TokenizerWordState::Normal)
  {
    //If not part of identifier (if digit first char)
    if(chars.size() == 0 && isdigit(c)){
      ChangeState(TokenizerWordState::InInteger);
      chars.push_back(c);
      return true;
    }
  }
  return false;
}

bool TokenizerWords::HandleNormal(){
	if(state == TokenizerWordState::Normal)
  {
    //Not handled yet, still in identifier so push char
    chars.push_back(c);
    return true; 
  }

  return false;
}

void TokenizerWords::Debug(IndexType i, bool single){
  IndexType len = tokens.size();

  for(; i<len; i++){
    TokenizerWordToken tt = (TokenizerWordToken)tokens[i].t;
    if(tt == TokenizerWordToken::Identifier){
      std::cout << "Identifier [" << tokenizer->GetIdentifier(tokens[++i].s) << "]\n";
    }else if(tt == TokenizerWordToken::LiteralString){
      std::cout << "String [" << tokenizer->GetString(tokens[++i].s) << "]\n";
    }else if(tt == TokenizerWordToken::LiteralInteger){
      std::cout << "Integer [" << tokens[++i].i << "]\n";
    }else if(tt == TokenizerWordToken::LiteralDecimal){
      std::cout << "Decimal [" << tokens[++i].d << "]\n";
    }else if( DecodeGroup(tokens[i].t) == TokenizerWord_Special){
      std::cout << "Spec\n";
    }else{
      std::cout << "?\n";
    }
    if(single)break;
  }
  
}