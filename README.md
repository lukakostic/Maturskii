# Maturskii

Most dynamic and flexible language, making it the least safe i guess.

##Reserved chars (includes space):
(){}[] ,

() same as in c,c#,js..
<identifier>(){} for functions
(){} for same scope functions //allow this for named functions too somehow?
{} for object
[] for arrays or indexing/attributes
, like ; in c#, executes previous command or separates


##Comments:
// /* */


rename function can rename existing and built in functions. in c++ side functions all have string names (built in and not), with a pointer to an action tree of the function.


##Custom operators:

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

