#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "ast_node.h"
//#include "ast_scope.h"

Node::Node() {
    this->type = "Node";
}

/*    virtual std::string get_type() {
        return this->type;
    }

    virtual double compile() const {
        throw std::runtime_error(this->type + "compile not implemented.");
    }

    virtual double print() const {
        throw std::runtime_error(this->type + " print not implemented.");
    }

    virtual std::string to_string() const {
        throw std::runtime_error("Node print not implemented.");
    }

    virtual std::string compileToMIPS() const {
        throw std::runtime_error(this->type + " compileToMIPS not implemented.");
    }

    /*virtual void generate_var_maps(Scope *parent) {
        std::cout << "gen varmaps not overridden\n";
    }
};*/
