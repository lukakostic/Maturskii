#pragma once
#include <cstddef>
#include <cstdint>


typedef uint32_t TokenType;

//General Token: instruction, literal or index
union Token {
    TokenType t; //instruction (aka token, enum)
    std::size_t s; //index
    std::uint_fast64_t u; //unsigned integer literal?
    std::int_fast64_t i; //signed integer literal
    double d; //double literal
};

constexpr int BITS = 32; //tokenizer type bits
constexpr int BITS_GROUP = 8; //bits for group. Represents what group token belongs.
constexpr int BITS_DATA = 8; //bits for data. Represents how many data tokens follow.
//remaining 16 bits are for index/value. Represents base value/index in enum list.
//bits in hex: DD GG II II
constexpr TokenType DATA_MASK = (TokenType)(0xFF'00'00'00);
constexpr TokenType GROUP_MASK = (TokenType)(0x00'FF'00'00);



constexpr int DATA_OFFSET = BITS - BITS_DATA;
constexpr int GROUP_OFFSET = DATA_OFFSET - BITS_GROUP;


//Encode group and data into index
constexpr TokenType EncodeToken(unsigned index,unsigned group,unsigned data){
    return (TokenType)(index | (group<<GROUP_OFFSET) | (data<<DATA_OFFSET));
}

//Decode data, group or index
inline unsigned DecodeData(TokenType value){
    return (unsigned)((value & DATA_MASK) >> DATA_OFFSET);
}
inline unsigned DecodeGroup(TokenType value){
    return (unsigned)((value & GROUP_MASK) >> GROUP_OFFSET);
}
inline unsigned DecodeIndex(TokenType value){
    return (unsigned)(value & ~(DATA_MASK | GROUP_MASK));
}

//Commonly used tokens
//GROUP is macro defined above call
#define TOKEN EncodeToken(__COUNTER__,GROUP,0) //Token without data
#define TOKEN_1 EncodeToken(__COUNTER__,GROUP,1) //Token with 1 data
#define TOKEN_D(D) EncodeToken(__COUNTER__,GROUP,D) //Token with some data

#define TOKEN_BITS(X) std::bitset<BITS>(X) //TokenType to bits