#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "lexer.h"

bool isDefineVar(const std::string &word)
{
    return (word.length() == 3 && word[0] == 'D'&&
        word[1] == 'I' && word[2] == 'M');
}

bool isType(const std::string &word)
{
    std::vector<std::string> types = {"INTEGER", "STRING",
        "LONG", "SINGLE", "DOUBLE"};

    for (const std::string &type : types) {
        if (type.compare(word) == 0) {
            return true;
        }
    }

    return false; 
}

bool isFunction(const std::string &word)
{
    std::vector<std::string> functions = {"PRINT", "GOTO", "END", "RND"};

    for (const std::string &function: functions) {
        if (function.compare(word) == 0) {
            return true;
        }
    }

    return false;
}

bool isKeyword(const std::string &word)
{
    std::vector<std::string> keywords = {"AS", "LET"};

    for (const std::string &keyword : keywords) {
        if (keyword.compare(word) == 0) {
            return true;
        }
    }

    return false;
}

bool isRelatinnalOperator(const std::string &word)
{
    std::vector<std::string> keywords = {">", ">=", "<", "<=", "=", "<>"};

    for (const std::string &keyword : keywords) {
        if (keyword.compare(word) == 0) {
            return true;
        }
    }

    return false;
}

bool isArithmeticOperator(const std::string &word)
{
    std::vector<std::string> keywords = {"*", "/", "-",
        "+"};

    for (const std::string &keyword : keywords) {
        if (keyword.compare(word) == 0) {
            return true;
        }
    }

    return false;
}

bool isNumber(const std::string &word)
{
    for (char c : word)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

bool isString(const std::string &word)
{
    int wLength = word.length();
    return (wLength > 1 && '"' == word[0] && '"' == word[wLength-1]); 
}

bool isIdentifier(const std::string &word)
{
    if (word.length() > 0) {
        if (('a' <= word[0] && 'z' >= word[0]) ||
            ('A' <= word[0] && 'Z' >= word[0]))
        {
            for (char c : word) {
                if (!(('a' <= c && 'z' >= c) ||
                      ('A' <= c && 'Z' >= c) ||
                      ('0' <= c && '9' >= c)   
                     )
                    )
                {
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool isEquals(const std::string &word)
{
    return (word.length() == 1 && word[0] == '=');
}

bool isComma(const std::string &word)
{
    return (word.length() == 1 && word[0] == ',');
}

bool isColon(const std::string &word)
{
    return (word.length() == 1 && word[0] == ':');
}

bool isSemicolon(const std::string &word)
{
    return (word.length() == 1 && word[0] == ';');
}

bool isComment(const std::string &word)
{
    return (word.length() == 3 && word[0] == 'R'&&
        word[1] == 'E' && word[2] == 'M');
}

bool isNewLine(const std::string &word)
{
    return (word.length() == 1 && word[0] == '\n');
}

std::vector<Token> tokenize(std::string &sourceCode)
{
    std::vector<Token> tokens;
    std::vector<std::string> words;
    std::string word = "";

    
    bool string_detected = false;
    // Split sourceCode to words
    for (char c : sourceCode)
    {
        if (c == '\n' && false == string_detected) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
            words.push_back("\n");
        } else if(c != ' ' && !word.empty() && false == string_detected) {
            if (isNumber(word) && (c < '0' || c > '9')) {
                words.push_back(word);
                word.clear();
            } else if (isIdentifier(word) &&
                !( (c >= '0' && c <= '9') ||
                   (c >= 'a' && c <= 'z') ||
                   (c >= 'A' && c <= 'Z'))) {
                words.push_back(word);
                word.clear();
            } else if (isRelatinnalOperator(word) ||
                isArithmeticOperator(word)) {
                words.push_back(word);
                word.clear();
            }
            word += c;
        } else if (c != ' ' || true == string_detected) {
            word += c;
            if ('"' == c) {
                if (true == string_detected) {
                    words.push_back(word);
                    word.clear();
                }
                string_detected = !string_detected;
            }
        } else if (!word.empty()){
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    for (std::string &w : words)
    {
        Token token;
        token.value = w;
        if (isDefineVar(w)){
            token.type = DefineVar;
        } else if (isEquals(w)) {
            token.type = Equals;
        } else if (isComma(w)) {
            token.type = Comma;
        } else if (isColon(w)) {
            token.type = Colon;
        } else if (isSemicolon(w)) {
            token.type = Semicolon;
        } else if (isNewLine(w)) {
            token.type = Newline;
        } else if (isKeyword(w)) {
            token.type = Keyword;
        } else if (isComment(w)) {
            token.type = Comment;
        } else if (isArithmeticOperator(w)) {
            token.type = ArithmeticOperator;
        } else if (isRelatinnalOperator(w)) {
            token.type = RelationnalOperator;
        } else if (isFunction(w)) {
            token.type = Function;
        } else if (isString(w)) {
            token.type = String;
        } else if (isType(w)) {
            token.type = Type;
        } else if (isNumber(w)) {
            token.type = Number;
        } else if (isIdentifier(w)) {
            token.type = Identifier;
        } else {
            token.type = Undefined;
        }
        tokens.push_back(token);
    }

    return tokens;
}

int main (int argc, char* argv[])
{
    std::string str = "";
    if (argc == 2)
    {
        std::ifstream file; 

        file.open(argv[1]);
        if (file.fail())
        {
            std::cout << "File failed to open." << std::endl;
            return 1;
        }

        std::stringstream buffer;

        buffer << file.rdbuf();
        str = buffer.str();
        file.close();
    }
    else
    {
        str = "DIM N AS INTEGER\n"
            "N = 9\n"
            "PRINT \"Hello pour la\" ; N ; \" fois\"\n";
    }

    std::vector<Token> tokens;

    std::cout << "Input : " << std::endl << str << std::endl;

    tokens = tokenize(str);

    for (Token token : tokens)
    {
        if (token.type == Newline)
        {
            std::cout << "NEW_LINE" << std::endl;
        }
        else
        {   
            std::cout << tokenTypeToString(token.type) << " : " << token.value << std::endl;
        }
    }

    return 0;
}
