# maturskii

# concept
interpreted quick & dirty flexible scripting and hacking-things-together\
similar to javascript, but generally borrows concepts from many languages
###### no operators, just functions

# specs/docs

## reserved chars (includes space):
()[]{}, #$.


$ turns string to identifier $'id' or identifier literal $id

var.property\
var.$property `I D K`\
var\[$property\] `I D K`\
var\['property'\]\
var\[property\] `value of property`

## variables
all variables are either literal or objects

## literals
* identifier
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

{} is function body, takes no arguments

(arg1,arg2){} is a function body and arguments

function declaration:\
```
:($fn,(arg1,arg2){})
```

\# executes function in same scope, useful for macros: #fn(),

###### #{} code block always executed in same scope

function call:\
`functionName(argument1,argument2,...)`

## conditionals

cond?{}, `if condition is >0 (check literals), execute code block`\
cond??{}, `else if`\
???{}, `else`

## comments:
// /\* \*/\
// have a higher presidence, so // /\* will be a single line comment

## built in functions and objects
</br>

`=(identifier,value)`\
sets identifier to value

`:(identifier,value)`\
set identifier to reference

</br>

`rename(originalName, newName)`\
rename variable or function

</br>

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
