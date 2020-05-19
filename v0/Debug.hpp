#pragma once
#include "Tokenizer.hpp"
#include <string>
#include <map>

std::map<TokenType,std::string> TokenTypeStrings =
{

    {TokenType::Identifier, "Identifier"},

    {TokenType::Parenthesized, "Parenthesized"},
    {TokenType::Bracketed, "Bracketed"},
    {TokenType::Braced, "Braced"},
    {TokenType::Dotted, "Dotted"},

    {TokenType::Null, "Null"},
    {TokenType::LiteralIdentifier, "LiteralIdentifier"},
    {TokenType::LiteralInteger, "LiteralInteger"},
    {TokenType::LiteralDecimal, "LiteralDecimal"},
    {TokenType::LiteralString, "LiteralString"},

    {TokenType::Assignment, "Assignment"},
    {TokenType::PointerAssignment, "PointerAssignment"},
    {TokenType::UpAssignment, "UpAssignment"},
    {TokenType::AssignmentPush, "AssignmentPush"},
    {TokenType::PointerAssignmentPush, "PointerAssignmentPush"},
    {TokenType::UpAssignmentPush, "UpAssignmentPush"},
    {TokenType::Greater, "Greater"},
    {TokenType::Lesser, "Lesser"},
    {TokenType::GreaterEqual, "GreaterEqual"},
    {TokenType::LesserEqual, "LesserEqual"},
    {TokenType::Equal, "Equal"},
    {TokenType::NotEqual, "NotEqual"},
    {TokenType::Add, "Add"},
    {TokenType::Subtract, "Subtract"},
    {TokenType::Multiply, "Multiply"},
    {TokenType::Divide, "Divide"},
    {TokenType::Bind, "Bind"},

    {TokenType::IdentifierFrom, "IdentifierFrom"},
    {TokenType::PointerTo, "PointerTo"},
    {TokenType::ValueOf, "ValueOf"},

    {TokenType::Return, "Return"},
    {TokenType::Pop, "Pop"},
    {TokenType::Clear, "Clear"}

};
