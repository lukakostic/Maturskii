# maturskii

# PART 0. just the tokenizer:

# tokenizer
tokenization is done in 3 steps:

## 1: grouping into words
Reserved characters, numeric/string literals and identifiers into linear list. space separates but doesnt get included in words. comma (,) does. comments ignored

## 2: bracket/brace/parenthese trees
everything in {}, [], () is put into a tree containing the words inside. trees get put into a list, so they can be called later by index.

## 3: tokens
* identifiers\
`holds id to identifier. identifier string added to identifiers list`
* numeric literals\
`holds numeric value`
* string literals\
`holds id to string. string added to strings list`
* function calls
 ###### idk how to represent function calls, maybe holds
* special (reserved characters and groupings such as ??)
* compound (bracketed), contains other tokens\
`holds id to tree`


## reserved chars:
()[]{}

space and newline are separators
