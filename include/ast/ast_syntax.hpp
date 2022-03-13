//
// Created by Michal on 13. 3. 2022.
//

#ifndef AST_SYNTAX_HPP
#define AST_SYNTAX_HPP
class Identifier : public Node{
public:
        std::string identifier;
    Identifier(std::string id){
        this->type = "Identifier";
        this->identifier = id;
    }
};
#endif
