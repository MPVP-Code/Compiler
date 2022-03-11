//
// Created by michal on 4. 3. 2022.
//

#ifndef AST_SCOPE_HPP
#define AST_SCOPE_HPP

#include "ast_node.hpp"
#include "ast_type.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>

class Scope : public Node
{
public:
    //Inherits branches & type
    std::vector<std::shared_ptr<Scope>> parent_scope;
    //std::map<std::string,Variable> var_map;

    Scope(){
        this->type = "Scope";
        this->branches={};
    }

    //Has gettype

    virtual double compile() const override{
        throw std::runtime_error("Scope compile not implemented.");
    }

    virtual double print() const override{
        throw std::runtime_error("Scope compile print not implemented.");
    }
};

class Global : public Scope
{
private:
    static std::unordered_map<std::string, int> registersMapping;
    static int currentRegister;
public:
    //Inherits branches & type

    Global(){
        this->type = "Global";
    }

    //Has gettype

    virtual double compile() const override{
        throw std::runtime_error("Global compile not implemented.");
    }

    virtual double print() const override{
        throw std::runtime_error("Global print not implemented.");
    }

    static void initCurrentRegister() {
        Global::currentRegister = 2;
    }

    static int getRegisterNumberForVariable(std::string *variable) {
        return 2;
        /*auto iterator = registersMapping.find(*variable);
        if (iterator == registersMapping.end()) {
            registersMapping.insert(std::pair<std::string, int>(*variable, currentRegister));
            currentRegister++;
        } else {
            result = iterator->second;
        }
        return result;*/
    }

    static std::string intToHex(int i)
    {
        std::stringstream stream;
        stream << "0x" << std::setfill ('0') << std::setw(sizeof(i)) << std::hex << i;
        return stream.str();
    }

};

#endif


