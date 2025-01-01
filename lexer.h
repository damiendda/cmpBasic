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

std::string tokenTypeToString(TokenType tokenType)
{
    std::string res = "";

    switch(tokenType)
    {
        case DefineVar:
            res = "DEFINE_VAR";
            break;
        case Type:
            res = "TYPE";
            break;
        case Keyword:
            res = "KEYWORD";
            break;
        case Function:
            res = "FUNCTION";
            break;
        case Comment:
            res = "COMMENT";
            break;
        case String:
            res = "STRING";
            break;
        case Identifier:
            res = "IDENTIFIER";
            break;
        case Number:
            res = "NUMBER";
            break;
        case ArithmeticOperator:
            res = "ARITHMETIC_OPERATOR";
            break;
        case RelationnalOperator:
            res = "RELATIONNAL_OPERATOR";
            break;
        case Equals:
            res = "EQUALS";
            break;
        case Colon:
            res = "COLON";
            break;
        case Semicolon:
            res = "SEMICOLON";
            break;
        case Comma:
            res = "COMMA";
            break;
        case OpenParenthese:
            res = "OPEN_PARANTHESE";
            break;
        case CloseParenthese:
            res = "CLOSE_PARENTHESE";
            break;
        case Newline:
            res = "NEW_LINE";
            break;
        case Undefined:
        default:
            res = "Undefined !!";
            break;

    }
    return res;
}
