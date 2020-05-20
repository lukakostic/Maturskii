# maturskii

# concept
quick & dirty flexible scripting and hacking-things-together language\
similar to javascript, but generally borrows concepts from many languages

## flexible, quick & dirty?

Dirty because it doesnt save you froom undefined behaviour, and is very prone to it, as it lets users do almost anything\
You can change some very fundamental parts of the language, such as renaming built in functions and operators\
Your operators can be symbols or even strings ( '&' vs 'and' )\
?You can even replace the bracket/brace/pharentese symbols to some other symbols or strings\
But thats what makes it flexible and quick to do small scripts and projects in

Execute functions in local or global scopes, push things to global stack, and all kinds of other crazy things

Aims to unify macros and functions to use same or similar syntax

You can of course do larger projects too but these are the downsides:
* Not stricly typed, so you dont know what type or form an object is in
* ? No packages/imports
* The user can easily brake things down the line by changing some fundamental parts of the language
* Not the fastest thing around
* ? No declarations, all implicitly declarated so prone to typos

# specs/docs

## reserved chars (includes space):
(){}[] ,

## variables
all variables are either literal or objects

## literals
* numbers  `> all floats`
* strings  `> chars are strings of length 1`
* functions  `> more on that in #functions`
* null
* `> bools are 0 and >0`

> indexes and bools are internally rounded

## objects
all objects have intrinsic value (can be literal or object) and properties\
all properties are objects

## value vs reference
you can instantiate things as either by value or by reference\
references act as pointers, but you can set actual value of the object they are refering to

## functions
functions are also just variables

() same as in c,c#,js..\
<identifier>(){} for functions\
(){} for same scope functions >allow this for named functions too somehow?\
{} for object\
[] for arrays or indexing/attributes\
, like ; in c#, executes previous command or separates

each operator, built in or not, is just a function object. Some functions are tied into backend, some are user made. You can see and reorder them with the replace operator


## comments:
// /\* \*/\
// have a higher presidence, so // /\* will be a single line comment

## built in functions and objects

### functions

`=(identifier,value)`\
sets identifier to value

`:(identifier,value)`\
set identifier to reference

   

`rename(originalName, newName)`\
rename function can rename existing and built in functions. in c++ side functions all have string names (built in and not), with a pointer to an action tree of the function

   

`+(a,b)`\
adds a and b\
if strings, concatenate\
if numbers, subtract
> for bools, effectively acts as OR 

`-(a,b)`\
subtract number b from number a\
`-(a)`\
negate number a

`*(a,b)`\
multiplies numbers a and b
> for bools, effectively acts as AND
