#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "lexer.h"

enum Sates
{
    P_IDLE,
};


void parse(std::vector<Token> tokens);

#endif
