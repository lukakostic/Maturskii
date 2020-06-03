#pragma once
#include <cstddef>
#include <cstdint>

union Token { //hopefully 64 bits depending on double size but not important
    std::uint_fast64_t u; //instruction or index in list, unsigned integer literal?
    std::int_fast64_t i; //signed integer literal
    double d; //double literal
};

typedef uint16_t TokenType;

constexpr int BITS = 16; //token bits
constexpr int BITS_GROUP = 4; //bits for group (16 max). Represents what group token belongs.
constexpr int BITS_DATA = 4; //bits for data (16 max). Represents how many data tokens follow.
//remaining 8 bits are for index/value (256 max). Base value in enum list.
//DDDD GGGG IIII IIII
constexpr TokenType DATA_MASK = (TokenType)(0xF000); //MMMM 0000 0000 0000
constexpr TokenType GROUP_MASK = (TokenType)(0x0F00); //0000 MMMM 0000 0000



constexpr int DATA_OFFSET = BITS - BITS_DATA; // for 16 bits you need to shift by 12 to fill last 4 bits
constexpr int GROUP_OFFSET = DATA_OFFSET - BITS_GROUP; // for 16 bits you need to shift by 8


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