#include "../src/lexer.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> tokens;

    while (1) {
        TokenType type = (TokenType) yylex();

        if (type == NONE) {
            break;
        } else if (type == VARIABLE) {
            tokens.push_back("VARIABLE");
        } else if (type == EQUALS_SIGN) {
            tokens.push_back("EQUALS_SIGN");
        } else {
            tokens.push_back("NUMBER");
        }
    }

    std::string result = tokens[0];

    for(std::size_t i = 1; i < tokens.size(); i++) {
        result += " " + tokens[i];
    }
    std::cout << result << std::endl;

    return 0;
}
