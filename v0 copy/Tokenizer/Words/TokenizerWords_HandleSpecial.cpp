#include "Tokenizer/Words/TokenizerWords.hpp"
#include "Tokenizer/Words/TokenizerWordsStates.hpp"
#include "Tokenizer/Words/TokenizerWordsTokens.hpp"

bool TokenizerWords::HandleSpecial(){
  if(stateGroup != TokenizerWordState_InStringLiteral){
    
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\0'){
      Break();
      return true;
    }

    if (c == '#'){
      Break(), AddToken(TokenizerWordToken::Hashtag);
      return true;
    }
    if (c == '.'){
      Break(), AddToken(TokenizerWordToken::Dot);
      return true;
    }
    if (c == ','){
      Break(), AddToken(TokenizerWordToken::Comma);
      return true;
    }
    /*
    if (c == ';'){
      Break(), AddToken(TokenizerWordToken::Semicolon);
      return true;
    }
    if (c == '='){
      Break(), AddToken(TokenizerWordToken::Equal);
      return true;
    }
    if (c == '-'){
      Break(), AddToken(TokenizerWordToken::Minus);
      return true;
    }
    if (c == '+'){
      Break(), AddToken(TokenizerWordToken::Plus);
      return true;
    }
    if (c == '*'){
      Break(), AddToken(TokenizerWordToken::Star);
      return true;
    }
    if (c == '/'){
      Break(), AddToken(TokenizerWordToken::Slash);
      return true;
    }
    if (c == '%'){
      Break(), AddToken(TokenizerWordToken::Percent);
      return true;
    }
    if (c == '!'){
      Break(), AddToken(TokenizerWordToken::Exclamation);
      return true;
    }
    if (c == '~'){
      Break(), AddToken(TokenizerWordToken::Tilda);
      return true;
    }
    if (c == '$'){
      Break(), AddToken(TokenizerWordToken::Dollar);
      return true;
    }
    if (c == '@'){
      Break(), AddToken(TokenizerWordToken::At);
      return true;
    }
    if (c == '^'){
      Break(), AddToken(TokenizerWordToken::Caret);
      return true;
    }
    if (c == '|'){
      Break(), AddToken(TokenizerWordToken::Pipe);
      return true;
    }
    if (c == '&'){
      Break(), AddToken(TokenizerWordToken::And);
      return true;
    }
    if (c == '>'){
      Break(), AddToken(TokenizerWordToken::Greater);
      return true;
    }
    if (c == '<'){
      Break(), AddToken(TokenizerWordToken::Lesser);
      return true;
    }
    */
   
    if (c == '('){
      Break(), AddToken(TokenizerWordToken::Parenthesis_Open);
      return true;
    }
    if (c == ')'){
      Break(), AddToken(TokenizerWordToken::Parenthesis_Close);
      return true;
    }
    
    if (c == '['){
      Break(), AddToken(TokenizerWordToken::Bracket_Open);
      return true;
    }
    if (c == ']'){
      Break(), AddToken(TokenizerWordToken::Bracket_Close);
      return true;
    }
    
    if (c == '{'){
      Break(), AddToken(TokenizerWordToken::Brace_Open);
      return true;
    }
    if (c == '}'){
      Break(), AddToken(TokenizerWordToken::Brace_Close);
      return true;
    }
    
  }
  
  return false;
}