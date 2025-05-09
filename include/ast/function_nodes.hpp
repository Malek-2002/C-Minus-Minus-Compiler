#pragma once

#include "ast_node.hpp"
#include "block_node.hpp"
#include <vector>
#include <utility>

/**
 * Node representing a function declaration
 */
class FunctionDeclarationNode : public ASTNode
{
private:
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::unique_ptr<BlockNode> body;
    BlockNode *parentBlock;
    int lineNumber;

public:
    FunctionDeclarationNode(const std::string &returnType, const std::string &name,
                            std::vector<std::pair<std::string, std::string>> parameters,
                            std::unique_ptr<BlockNode> body, BlockNode *parentBlock, int lineNumber);

    std::string getType() const override;
    void generateCode(QuadruplesGenerator &generator) override;
};

/**
 * Node representing a function call
 */
class FunctionCallNode : public ASTNode
{
private:
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> arguments;
    BlockNode *block;
    int lineNumber;

public:
    FunctionCallNode(const std::string &name, std::vector<std::unique_ptr<ASTNode>> arguments,
                     BlockNode *block, int lineNumber);

    std::string getType() const override;
    void generateCode(QuadruplesGenerator &generator) override;
};

/**
 * Node representing a return statement
 */
class ReturnNode : public ASTNode
{
private:
    std::unique_ptr<ASTNode> expression;
    BlockNode *block;
    std::string returnType;
    int lineNumber;

public:
    ReturnNode(std::unique_ptr<ASTNode> expression, BlockNode *block, std::string returnType, int lineNumber);

    std::string getType() const override;
    void generateCode(QuadruplesGenerator &generator) override;
};