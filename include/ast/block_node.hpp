#pragma once

#include "ast_node.hpp"
#include "../semantic/symbol.hpp"
#include <unordered_map>
#include <vector>

/**
 * Node representing a block of code (sequence of statements with its own scope)
 */

/*
    {  
        int a = 1;
        {
            int b = a + 1;
            {
                int y  = a;
            }
        }
    }

*/


class BlockNode : public ASTNode {
private:
    int id;
    BlockNode* parent;
    std::vector<std::unique_ptr<ASTNode>> statements;
    std::unordered_map<std::string, Symbol> symbolTable;
    std::unordered_map<std::string, FunctionSymbol> functionTable;
public:
    BlockNode(int id, BlockNode* parent);
    
    void addStatement(std::unique_ptr<ASTNode> statement);
    const std::vector<std::unique_ptr<ASTNode>>& getStatements() const;
    size_t statementCount() const;
    bool isEmpty() const;
    
    // Symbol table management
    bool addSymbol(const Symbol& symbol);
    bool symbolExists(const std::string& name) const;
    Symbol* getSymbol(const std::string& name);
    const Symbol* getSymbol(const std::string& name) const;
    bool updateSymbolValue(const std::string& name, const std::string& value);
    const std::unordered_map<std::string, Symbol>& getSymbolTable() const;
    
    // Function table management
    bool addFunction(const FunctionSymbol& function);
    FunctionSymbol* getFunction(const std::string& name);
    bool functionExists(const std::string& name) const;
    
    // Block management
    BlockNode* getParent() const;
    void setParent(BlockNode* newParent);
    int getId() const;
    
    // ASTNode implementation
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};