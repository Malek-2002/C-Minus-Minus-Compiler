#pragma once

#include "ast_node.hpp"
#include "block_node.hpp"
#include <vector>
#include <utility>
#include <unordered_set>

/**
 * Node representing an if statement
 */

/*
    if(x > 10) {
        print(x);
    }
*/

class IfNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<BlockNode> thenBlock;
    std::unique_ptr<ASTNode> elseStatement;
    int lineNumber;

public:
    IfNode(std::unique_ptr<ASTNode> condition,
          std::unique_ptr<BlockNode> thenBlock,
          std::unique_ptr<ASTNode> elseStatement,
          int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a while loop
 */
class WhileNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<BlockNode> body;
    int loopId;
    int lineNumber;

public:
    WhileNode(std::unique_ptr<ASTNode> condition,
             std::unique_ptr<BlockNode> body,
             int loopId,
             int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a do-while loop
 */
class DoWhileNode : public ASTNode {
private:
    std::unique_ptr<BlockNode> body;
    std::unique_ptr<ASTNode> condition;
    int loopId;
    int lineNumber;

public:
    DoWhileNode(std::unique_ptr<BlockNode> body,
               std::unique_ptr<ASTNode> condition,
               int loopId,
               int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a for loop
 */
class ForNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> initialization;
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> update;
    std::unique_ptr<BlockNode> body;
    int loopId;
    int lineNumber;

public:
    ForNode(std::unique_ptr<ASTNode> initialization,
           std::unique_ptr<ASTNode> condition,
           std::unique_ptr<ASTNode> update,
           std::unique_ptr<BlockNode> body,
           int loopId,
           int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a switch statement
 */
class SwitchNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression;
    std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases;
    std::unique_ptr<BlockNode> defaultCase;
    std::string endLabel;
    BlockNode* block;
    int lineNumber;

public:
    SwitchNode(std::unique_ptr<ASTNode> expression,
              std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases,
              std::unique_ptr<BlockNode> defaultCase,
              std::string endLabel,
              BlockNode* block,
              int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a break statement
 */
class BreakNode : public ASTNode {
private:
    std::string endLabel;
    int lineNumber;

public:
    BreakNode(std::string endLabel, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

/**
 * Node representing a continue statement
 */
class ContinueNode : public ASTNode {
private:
    std::string endLabel;
    int lineNumber;

public:
    ContinueNode(std::string endLabel, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};