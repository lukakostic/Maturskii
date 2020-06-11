#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <bitset>

#define DEBUG false
#define DBG if(DEBUG)

//For tokenizer enum values
typedef uint32_t Token;
#define TO_BITS(T) std::bitset<32>((uint32_t)T)

//For indexes, made uint16_t so it takes less space in bimaps
typedef uint16_t IndexType;

union Number {
    IndexType s; //index
    std::uint_fast64_t u; //unsigned integer literal?
    std::int_fast64_t i; //signed integer literal
    double d; //double literal
};

//General Token: Token, literal or index
struct Instruction{
    Token t; //Token (aka token, enum)
    Number data;
};


struct Tree {
    enum class TreeType {
        Package, // Main code or other code files
        Arguments, // ()
        Array, // []
        Function // {}
    } type;
    std::vector<Instruction> tokens;

    Tree();
    Tree(TreeType treeType);
};

constexpr int BITS = 32; //tokenizer type bits
constexpr int BITS_GROUP = 8; //bits for group. Represents what group token belongs.
constexpr int BITS_DATA = 8; //bits for data. Represents how many data tokens follow.
//remaining 16 bits are for index/value. Represents base value/index in enum list.
//bits in hex: DD GG II II
constexpr Token DATA_MASK = (Token)(0xFF'00'00'00);
constexpr Token GROUP_MASK = (Token)(0x00'FF'00'00);



constexpr int DATA_OFFSET = BITS - BITS_DATA;
constexpr int GROUP_OFFSET = DATA_OFFSET - BITS_GROUP;


//Encode group and data into index
constexpr Token EncodeToken(unsigned index,unsigned group,unsigned data){
    return (Token)(index | (group<<GROUP_OFFSET) | (data<<DATA_OFFSET));
}

//Decode data, group or index
inline unsigned DecodeData(Token value){
    return (unsigned)((value & DATA_MASK) >> DATA_OFFSET);
}
inline unsigned DecodeGroup(Token value){
    return (unsigned)((value & GROUP_MASK) >> GROUP_OFFSET);
}
inline unsigned DecodeIndex(Token value){
    return (unsigned)(value & ~(DATA_MASK | GROUP_MASK));
}

//Commonly used tokens
//GROUP is macro defined above call
#define TOKEN(I) EncodeToken(I,GROUP,0) //Token without data
#define TOKEN_1(I) EncodeToken(I,GROUP,1) //Token with 1 data
#define TOKEN_D(I,D) EncodeToken(I,GROUP,D) //Token with some data

#define TOKEN_BITS(X) std::bitset<BITS>(X) //Token to bits