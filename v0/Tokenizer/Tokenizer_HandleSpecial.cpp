#include <iostream>
#include "Tokenizer/Tokenizer.hpp"
#include "Tokenizer/TokenizerStates.hpp"
#include "Tokens.hpp"

bool Tokenizer::HandleSpecial()
{
  if (stateGroup != TokenizerState_InStringLiteral)
  {

    if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\0')
    {
      //DBG std::cout<<"\nempty char\n";///////////////////////////////
      Break();
      return true;
    }
    
    if (c == ',')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Comma);
      return true;
    }
/*
    if (c == '#')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Hashtag);
      return true;
    }
    
    if (c == '.')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Dot);
      return true;
    }

    if (c == ';')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Semicolon);
      return true;
    }
*/
    
    if (c == '=')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Equal);
      return true;
    }
    /*
    if (c == '-')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Minus);
      return true;
    }
    if (c == '+')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Plus);
      return true;
    }
    if (c == '*')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Star);
      return true;
    }
    if (c == '/')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Slash);
      return true;
    }
    if (c == '%')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Percent);
      return true;
    }
    if (c == '!')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Exclamation);
      return true;
    }
    if (c == '~')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Tilda);
      return true;
    }
    if (c == '$')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Dollar);
      return true;
    }
    if (c == '@')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::At);
      return true;
    }
    if (c == '^')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Caret);
      return true;
    }
    if (c == '|')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Pipe);
      return true;
    }
    if (c == '&')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::And);
      return true;
    }
    if (c == '>')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Greater);
      return true;
    }
    if (c == '<')
    {
      Break();
      tokenPack->AddToken(currentTree, Tokens::Lesser);
      return true;
    }
*/

    if (c == '(')
    {
      Break();
      currentTree = AddTreeStack(tokenPack->AddTreeToken(currentTree,Tree::TreeType::Arguments));
      return true;
    }
    if (c == ')')
    {
      Break();
      currentTree = PopTreeStack();
      return true;
    }

    if (c == '[')
    {
      Break();
      currentTree = AddTreeStack(tokenPack->AddTreeToken(currentTree,Tree::TreeType::Array));
      return true;
    }
    if (c == ']')
    {
      Break();
      currentTree = PopTreeStack();
      return true;
    }

    if (c == '{')
    {
      Break();
      currentTree = AddTreeStack(tokenPack->AddTreeToken(currentTree,Tree::TreeType::Function));
      return true;
    }
    if (c == '}')
    {
      Break();
      currentTree = PopTreeStack();
      //tokenPack->AddToken(currentTree, Tokens::Brace_Close);
      return true;
    }
  }

  return false;
}