#ifndef LEXER_H
#define LEXER_H

#include <string>

enum TokenType
{
    DefineVar, // DIM <Identifier> AS <Type>
    Type, // INTEGER or STRING or LONG or SINGLE or DOUBLE
    Keyword,
    Function,
    Comment,
    String,
    Identifier,
    Number,
    ArithmeticOperator,
    RelationnalOperator,
    Equals,
    Colon,
    Semicolon,
    Comma,
    Newline,
    OpenParenthese,
    CloseParenthese,
    Undefined,
};

struct Token
{
    TokenType type;
    std::string value;

};

std::string tokenTypeToString(TokenType tokenType);
std::vector<Token> tokenize(std::string &sourceCode);

#endif
