#include "../../build/parser.tab.hpp"

#include <iostream>
#include <vector>

int yylex(void);
YYSTYPE yylval;

std::string token_to_string(yytokentype token){
    switch (token){
        case IDENTIFIER:
            return "IDENTIFIER";
        case CONSTANT:
            return "CONSTANT";
        case STRING_LITERAL:
            return "STRING_LITERAL";
        case SIZEOF:
            return "SIZEOF";
        case PTR_OP:
            return "PTR_OP";
        case INC_OP:
            return "INC_OP";
        case DEC_OP:
            return "DEC_OP";
        case LEFT_OP:
            return "LEFT_OP";
        case RIGHT_OP:
            return "RIGHT_OP";
        case LE_OP:
            return "LE_OP";
        case GE_OP:
            return "GE_OP";
        case EQ_OP:
            return "EQ_OP";
        case NE_OP:
            return "NE_OP";
        case AND_OP:
            return "AND_OP";
        case OR_OP:
            return "OR_OP";
        case MUL_ASSIGN:
            return "MUL_ASSIGN";
        case DIV_ASSIGN:
            return "DIV_ASSIGN";
        case MOD_ASSIGN:
            return "MOD_ASSIGN";
        case ADD_ASSIGN:
            return "ADD_ASSIGN";
        case SUB_ASSIGN:
            return "SUB_ASSIGN";
        case LEFT_ASSIGN:
            return "LEFT_ASSIGN";
        case RIGHT_ASSIGN:
            return "RIGHT_ASSIGN";
        case AND_ASSIGN:
            return "AND_ASSIGN";
        case XOR_ASSIGN:
            return "XOR_ASSIGN";
        case OR_ASSIGN:
            return "OR_ASSIGN";
        case TYPE_NAME:
            return "TYPE_NAME";
        case TYPEDEF:
            return "TYPEDEF";
        case CHAR:
            return "CHAR";
        case SHORT:
            return "SHORT";
        case INT:
            return "INT";
        case LONG:
            return "LONG";
        case SIGNED:
            return "SIGNED";
        case UNSIGNED:
            return "UNSIGNED";
        case FLOAT:
            return "FLOAT";
        case DOUBLE:
            return "DOUBLE";
        case VOLATILE:
            return "VOLATILE";
        case VOID:
            return "VOID";
        case STRUCT:
            return "STRUCT";
        case UNION:
            return "UNION";
        case ENUM:
            return "ENUM";
        case CASE:
            return "CASE";
        case DEFAULT:
            return "DEFAULT";
        case IF:
            return "IF";
        case ELSE:
            return "ELSE";
        case SWITCH:
            return "SWITCH";
        case WHILE:
            return "WHILE";
        case DO:
            return "DO";
        case FOR:
            return "FOR";
        case CONTINUE:
            return "CONTINUE";
        case BREAK:
            return "BREAK";
        case RETURN:
            return "RETURN";
        case 0:
            return "END";
        default:
            return std::string(1,(char) token) ;
    }

}


int main() {
    std::vector<std::string> tokens;
    std::string result ="";

    while (1) {
        yytokentype type = (yytokentype) yylex();

        if (type == 0) {
            break;

        }
        tokens.push_back(token_to_string(type));

    }

        for (std::string token : tokens ) {
            result += " " + token;
        }
        std::cout << result << std::endl;

        return 0;

}
