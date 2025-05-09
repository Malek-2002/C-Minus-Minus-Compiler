#pragma once

#include "ast_node.hpp"
#include "block_node.hpp"

/**
 * Node representing a variable/constant declaration
 */
class DeclarationNode : public ASTNode {
private:
    std::string type;
    std::string identifier;
    bool isConstant;
    std::unique_ptr<ASTNode> initializer;
    BlockNode* block;
    int lineNumber;

public:
    DeclarationNode(const std::string type, const std::string identifier, bool isConstant,
                  std::unique_ptr<ASTNode> initializer, BlockNode* block, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a variable assignment
 */
class AssignmentNode : public ASTNode {
private:
    std::string identifier;
    std::unique_ptr<ASTNode> expression;
    BlockNode* block;
    int lineNumber;

public:
    AssignmentNode(const std::string& identifier, std::unique_ptr<ASTNode> expression,
                  BlockNode* block, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a print statement
 */
class PrintNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression;

public:
    PrintNode(std::unique_ptr<ASTNode> expression);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};