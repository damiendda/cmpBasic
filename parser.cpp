#include "parser.h"

#include <iostream>
#include <iterator>
#include <vector>


std::vector<Token>::iterator parseExpression(std::vector<Token>::iterator &it)
{
    while ((*it).type != Newline)
    {
        std::cout << "\t (" << (*it).type << ") " << (*it).value << std::endl; 
        it++;
    }
    return it;
}

std::vector<Token>::iterator parseKeyword(std::vector<Token>::iterator &it)
{
    if ((*it).value.compare("LET") == 0)
    {
        it++;
        if ((*it).type == Identifier)
        {
            std::cout << "Assign " << (*it).value;
            it++;
            it = parseExpression(it);
        }
        else
        {
            std::cout << "ERROR parsing" << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR to manage" << std::endl;
    }

    return it;
}

std::vector<Token>::iterator newLineParsing(std::vector<Token>::iterator &it)
{
    if (Number == (*it).type)
    {
        it++;
    }

    switch((*it).type)
    {
        case Keyword:
            it = parseKeyword(it);
            break;
        case Comment:
            // Manage end
            while ((*it).type != Newline)
            {
                it++;
            }
            it++;
            break;
        case Newline:
            it++;
            break;
        default:
            std::cout << "ERROR (" << (*it).value << ") " << tokenTypeToString((*it).type) << " UNKNOWN" << std::endl;
            it++;
            break;
    }

    return it;
}

void parse(std::vector<Token> tokens)
{
    bool end = false;
    std::vector<Token>::iterator it = tokens.begin();

    while (end == false && it != tokens.end())
    {
        it = newLineParsing(it);
    }
}
