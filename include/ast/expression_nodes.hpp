#pragma once

#include "ast_node.hpp"
#include "../codegen/quadruples_generator.hpp"

// Forward declarations
class BlockNode;

/**
 * Node representing a literal value (int, float, bool, string, etc.)
 */
class LiteralNode : public ASTNode {
private:
    std::string type;
    std::string value;

public:
    LiteralNode(const std::string& type, const std::string& value);
    
    std::string getType() const override;
    std::string getValue() const;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing an identifier reference
 */
class IdentifierNode : public ASTNode {
private:
    std::string name;
    BlockNode* block;
    int lineNumber;

public:
    IdentifierNode(const std::string& name, BlockNode* block, int lineNumber);
    
    std::string getType() const override;
    std::string getName() const;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a unary operation (-, !, etc.)
 */
class UnaryOpNode : public ASTNode {
private:
    std::string op;
    std::unique_ptr<ASTNode> operand;
    int lineNumber;

public:
    UnaryOpNode(const std::string& op, std::unique_ptr<ASTNode> operand, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a binary operation (+, -, *, /, etc.)
 */
class BinaryOpNode : public ASTNode {
private:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    int lineNumber;

public:
    BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left,
                std::unique_ptr<ASTNode> right, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};