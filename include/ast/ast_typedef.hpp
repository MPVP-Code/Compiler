#ifndef AST_TYPEDEF_H
#define AST_TYPEDEF_H

#include "ast_node.hpp"

class TypeDef : public Node {
public:
        std::string basicType;
        std::string newType;
      TypeDef(std::string _basicType, std::string _newType);

//      std::string getBasicType() const;
//
//      std::string getNewType() const;

      std::string compileToMIPS(const Node *parent_scope) const override;

      virtual void generate_var_maps(Node *parent);


};

#endif