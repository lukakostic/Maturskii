# maturskii

# PART 0. just the tokenizer:

# tokenizer
tokenization is done in 3 steps:

## 1: grouping into words
Reserved characters, numeric/string literals and identifiers into linear list.
space, tab, newline separate but dont get included in tokens.
comments ignored.

## 2: bracket/brace/parenthese trees
everything in {}, [], () is put into a tree containing the tokens inside. trees get put into a list, so they can be called later by index.
null identifier turned to null token.

## 3: statements
groups tokens and token trees into statements:
functions, calls, assignments
every statement has a token that is being acted upon and values (tree or token)
token(tree of values)
token = value
token = {values}



- in front of numbers to negate????????????
/ as symbol ????????????