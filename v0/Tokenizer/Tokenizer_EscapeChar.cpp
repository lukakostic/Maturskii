#include "Tokenizer/Tokenizer.hpp"

char Tokenizer::EscapeChar(char c){
  
  if(c == 'a') return '\a';
  if(c == 'b') return '\b';
  if(c == 'e') return '\e';
  if(c == 'f') return '\f';
  if(c == 'n') return '\n';
  if(c == 'r') return '\r';
  if(c == 't') return '\t';
  if(c == 'v') return '\v';
  if(c == '?') return '\?';
  
  return c;
}