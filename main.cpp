#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "lexer.h"

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
