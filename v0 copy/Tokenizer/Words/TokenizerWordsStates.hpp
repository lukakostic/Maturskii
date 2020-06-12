#pragma once
#include "Tokens.hpp"

//TokenizerState Groups:
#define TokenizerWordState_Normal 1
#define TokenizerWordState_InComment 2
#define TokenizerWordState_InNumberLiteral 3
#define TokenizerWordState_InStringLiteral 4

enum class TokenizerWordState : Token
{

#define GROUP TokenizerWordState_Normal
    Normal = TOKEN,
#undef GROUP

#define GROUP TokenizerWordState_InComment
    InComment = TOKEN,
    InCommentMultiline = TOKEN,
#undef GROUP

#define GROUP TokenizerWordState_InNumberLiteral
    InInteger = TOKEN,
    InDecimal = TOKEN,
#undef GROUP

#define GROUP TokenizerWordState_InStringLiteral
    InStringQuote = TOKEN,
    InStringDoubleQuote = TOKEN,
    InStringBacktick = TOKEN,
#undef GROUP

};