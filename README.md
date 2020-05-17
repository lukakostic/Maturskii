# Maturskii

# Concept

Quick & dirty flexible scripting and hacking-things-together language.

## Flexible, Quick & Dirty?

Dirty because it doesnt save you froom undefined behaviour, and is very prone to it, as it lets users do almost anything.
You can change some very fundamental parts of the language, such as renaming built in functions and operators.
Your operators can be symbols or even strings ( '&' vs 'and' )
?You can even replace the bracket/brace/pharentese symbols to some other symbols or strings.
But thats what makes it flexible and quick to do small scripts and projects in.

Execute functions in local or global scopes, push things to global stack, and all kinds of other crazy things.

Aims to unify macros and functions to use same or similar syntax.

You can of course do larger projects too but these are the downsides:
- Not stricly typed, so you dont know what type or form an object is in.
-? No packages/imports
- The user can easily brake things down the line by changing some fundamental parts of the language.
- Not the fastest thing around.
-? No declarations, all implicitly declarated so prone to typos

# Specs/Docs

## Reserved chars (includes space):
(){}[] ,

() same as in c,c#,js..
<identifier>(){} for functions
(){} for same scope functions //allow this for named functions too somehow?
{} for object
[] for arrays or indexing/attributes
, like ; in c#, executes previous command or separates

Each operator, built in or not, is just a function object. Some functions are tied into backend, some are user made. You can see and reorder them with the replace operator.


##Comments:
// /* */


rename function can rename existing and built in functions. in c++ side functions all have string names (built in and not), with a pointer to an action tree of the function.


## Custom operators:

//All operators have same presidence
//bioperator //eg &&
_&_ && (a,b){
return and(a,b),
}),
*_&_* spaced bioperator//eg and

&_ pre operator //eg !
*&_* spaced pre operator //eg not

_& post operator //eg ++
*_&* spaced post operator

& standalone operator, so like a function //eg ;
*&* spaced standalone operator, so like a function //eg break





//declare bioperator '&'
_$_ & (a,b){
    return +(a,b);
}

//space not required
c = a&b;

//declare spaced bioperator 'and' (notice two _)
*_$_* and (a,b){
    return +(a,b);
}

//space required
c = a and b;

//pre operator
$_ & (a){
    return !(a);
}

//no space needed
c = &a;

//spaced pre operator
*&_* and (a){
    
}

