#pragma once
#include <string>

enum class TokenType
{
    KEYWORD,
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    OPERATOR,
    PUNCTUATOR,
    UNKNOWN
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value) : type(type), value(value) {};
};
