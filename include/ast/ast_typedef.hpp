#ifndef AST_TYPEDEF_H
#define AST_TYPEDEF_H

#include "ast_node.hpp"

class TypeDef : public Node {
private:
    std::string basicType;
    std::string newType;
public:
      TypeDef(std::string _basicType, std::string _newType);

      std::string getBasicType() const;

      std::string getNewType() const;

      std::string compileToMIPS(const Node *parent_scope) const override;
};

#endif