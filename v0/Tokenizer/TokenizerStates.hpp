#pragma once
#include "TokenStructs.hpp"

//TokenizerState Groups:
#define TokenizerState_Normal 1
#define TokenizerState_InComment 2
#define TokenizerState_InNumberLiteral 3
#define TokenizerState_InStringLiteral 4

enum class TokenizerState : Token
{

#define GROUP TokenizerState_Normal
    Normal = TOKEN(1),
#undef GROUP

#define GROUP TokenizerState_InComment
    InComment = TOKEN(1),
    InCommentMultiline = TOKEN(2),
#undef GROUP

#define GROUP TokenizerState_InNumberLiteral
    InInteger = TOKEN(1),
    InDecimal = TOKEN(2),
#undef GROUP

#define GROUP TokenizerState_InStringLiteral
    InStringQuote = TOKEN(1),
    InStringDoubleQuote = TOKEN(2),
    InStringBacktick = TOKEN(3),
#undef GROUP

};