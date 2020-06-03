#pragma once
#include <inttypes.h>
#include "TokenizerWords.hpp"


Tokenizer_Words::Tokenizer_Words(const std::string &code){
  state = TokenizerWord::Normal;
  pc = '\0';
  c = '\0';
  escapeNext = false;
  chars = std::string();
  tokens = std::vector<Token>();

  word_count = 0;
  word_str2index = std::unordered_map<std::string, std::size_t>();
  word_index2str = std::unordered_map<std::size_t, std::string>();

  for (char const &ch : code)
    FeedChar(ch);

  FeedChar('\0');
}

void Tokenizer_Words::AddToken(TokenizerToken t){
  tokens.push_back({(TokenType)t});
}
void Tokenizer_Words::AddToken(Token t){
  tokens.push_back(t);
}


std::size_t Tokenizer_Words::AddWord(std::string word){
  auto find = word_str2index.find(word);
  //If not already in list
  if(find == word_str2index.end()){
    word_str2index.insert({word, word_count});
    word_index2str.insert({word_count, word});
    word_count++;
    return word_count-1;
  }
  return find->second;
}

void Tokenizer_Words::Break(){
  if(state == TokenizerWord::Normal)
  {
    AddToken(TokenizerToken::Identifier);
    AddToken({AddWord(chars)});
  }
  else if(state == TokenizerWord::InInteger)
  {
    AddToken(TokenizerToken::LiteralInteger);
    AddToken({std::stoll(chars)});
  }
  else if(state == TokenizerWord::InDecimal)
  {
    AddToken(TokenizerToken::LiteralDecimal);
    AddToken({std::stod(chars)});
  }
  else if(DecodeGroup((TokenType)state) == TokenizerWord_InStringLiteral)
  {
    AddToken(TokenizerToken::LiteralString);
    AddToken({AddWord(chars)});
  }

  chars = std::string();
}

void Tokenizer_Words::FeedChar(char ch){
  pc = c;
  c = ch;
  unsigned int helperStateGroup = DecodeGroup((TokenType)state);

  if(
  HandleComments(helperStateGroup) == false &&
  HandleSpecial(helperStateGroup) == false &&
  HandleNormal(helperStateGroup) == false
  ){
    //?
  }
}


bool Tokenizer_Words::HandleComments(unsigned int helperStateGroup){
	
	//See if you should exit comment mode
	if (helperStateGroup == TokenizerWord_InComment)
  {
    //Exit comment mode or stay, either way handled = true
    
    if (state == TokenizerWord::InComment && (c == '\n' || c=='\r' ))
        state = TokenizerWord::Normal;
    else if (state == TokenizerWord::InCommentMultiline && pc == '*' && c == '/')
        state = TokenizerWord::Normal;
    
    return true;
  }
  //See if you should enter comment mode
  else if(pc == '/' && helperStateGroup != TokenizerWord_InStringLiteral)
  {
    if(c=='*'){
      Break(), state == TokenizerWord::InCommentMultiline;
      return true;
    }
    else if(c=='/'){
      Break(), state == TokenizerWord::InComment;
      return true;
    }
  }

  return false;
}

bool Tokenizer_Words::HandleSpecial(unsigned int helperStateGroup){
  if(helperStateGroup != TokenizerWord_InStringLiteral){
    if (c == '('){
      Break(), AddToken(TokenizerToken::Parenthesis_Open);
      return true;
    }
    if (c == ')'){
      Break(), AddToken(TokenizerToken::Parenthesis_Close);
      return true;
    }
    
    if (c == '['){
      Break(), AddToken(TokenizerToken::Bracket_Open);
      return true;
    }
    if (c == ']'){
      Break(), AddToken(TokenizerToken::Bracket_Close);
      return true;
    }
    
    if (c == '{'){
      Break(), AddToken(TokenizerToken::Brace_Open);
      return true;
    }
    if (c == '}'){
      Break(), AddToken(TokenizerToken::Brace_Close);
      return true;
    }
    
    if (c == ' '){
      Break();
      return true;
    }
  }
  
  return false;
}


  
bool Tokenizer_Words::HandleNormal(unsigned int helperStateGroup){
	
  if (helperStateGroup == TokenizerWord_InStringLiteral)
  {
    if (escapeNext == true){
      chars.push_back(c);
      escapeNext = false;
      return true;
    }else if (c == '\\'){
      escapeNext = true;
      return true;
    }

    //Exit string if correct quote encountered
    if (
    (state == TokenizerWord::InStringQuote && c == '\'') ||
    (state == TokenizerWord::InStringDoubleQuote && c == '"') ||
    (state == TokenizerWord::InStringBacktick && c == '`')
    ){
      Break(), state = TokenizerWord::Normal;
      return true;
    }

    //If still in string, add char
    chars.push_back(c);

    return true;
  }
  else if (helperStateGroup == TokenizerWord_InNumberLiteral)
  {
    //Turn to decimal if . found in number
    if(c == '.'){
      state == TokenizerWord::InDecimal;
      chars.push_back('.');
      return true;
    }
  }
  else if(state == TokenizerWord::Normal)
  {
    //Enter string?
    if (c == '\''){
      Break(), state = TokenizerWord::InStringQuote;
      return true;
    }else if (c == '"'){
      Break(), state = TokenizerWord::InStringDoubleQuote;
      return true;
    }else if (c == '`'){
      Break(), state = TokenizerWord::InStringBacktick;
      return true;
    }

    //Enter number?
    //If not part of identifier (if digit first char)
    if(chars.size() == 0 && isdigit(c)){
      state = TokenizerWord::InInteger;
      return true;
    }

    //Hasnt entered anything or Break(), still in identifier
    chars.push_back(c);
    return true; 
  }

  return false;
}