#include "ast/control_flow_nodes.hpp"
#include "ast/expression_nodes.hpp"
#include "codegen/quadruples_generator.hpp"
#include "error/error_handler.hpp"
#include "semantic/symbol_table.hpp"

// IfNode implementation
IfNode::IfNode(std::unique_ptr<ASTNode> condition,
               std::unique_ptr<BlockNode> thenBlock,
               std::unique_ptr<ASTNode> elseStatement,
               int lineNumber)
    : condition(std::move(condition)),
      thenBlock(std::move(thenBlock)),
      elseStatement(std::move(elseStatement)),
      lineNumber(lineNumber) {}

std::string IfNode::getType() const
{
    return "void"; // Control flow statements don't have a type
}

void IfNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate a unique label for this if statement
    static int ifCounter = 0;
    std::string ifLabel = "if_" + std::to_string(ifCounter++);
    std::string elseLabel = ifLabel + "_else";
    std::string endLabel = ifLabel + "_end";

    condition->getType();
    // Generate code for condition
    condition->generateCode(generator);

    // Jump to else block if condition is false
    generator.handleConditionalJump("JZ", elseLabel);

    // Generate code for then block
    thenBlock->generateCode(generator);

    // Jump to end after then block
    generator.handleJump(endLabel);

    // Else label
    generator.addQuadruple("LABEL", "", "", elseLabel);

    // Generate code for else block if it exists
    if (elseStatement)
    {
        elseStatement->generateCode(generator);
    }

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// WhileNode implementation
WhileNode::WhileNode(std::unique_ptr<ASTNode> condition,
                     std::unique_ptr<BlockNode> body,
                     int loopId,
                     int lineNumber)
    : condition(std::move(condition)),
      body(std::move(body)),
      loopId(loopId),
      lineNumber(lineNumber) {}

std::string WhileNode::getType() const
{
    return "void";
}

void WhileNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate unique labels for this while loop
    std::string startLabel = "while_" + std::to_string(loopId) + "_start";
    std::string endLabel = "while_" + std::to_string(loopId) + "_end";

    // Start label
    generator.addQuadruple("LABEL", "", "", startLabel);

    condition->getType();
    // Generate code for condition
    condition->generateCode(generator);

    // Jump to end if condition is false
    generator.handleConditionalJump("JZ", endLabel);

    // Generate code for body
    body->generateCode(generator);

    // Jump back to start
    generator.handleJump(startLabel);

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// DoWhileNode implementation
DoWhileNode::DoWhileNode(std::unique_ptr<BlockNode> body,
                         std::unique_ptr<ASTNode> condition,
                         int loopId,
                         int lineNumber)
    : body(std::move(body)),
      condition(std::move(condition)),
      loopId(loopId),
      lineNumber(lineNumber) {}

std::string DoWhileNode::getType() const
{
    return "void";
}

void DoWhileNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate unique labels for this do-while loop
    std::string startLabel = "do_while_" + std::to_string(loopId) + "_start";
    std::string condLabel = "do_while_" + std::to_string(loopId) + "_cond";
    std::string endLabel = "do_while_" + std::to_string(loopId) + "_end";

    // Start label
    generator.addQuadruple("LABEL", "", "", startLabel);

    // Generate code for body
    body->generateCode(generator);

    // Condition label
    generator.addQuadruple("LABEL", "", "", condLabel);

    condition->getType();
    // Generate code for condition
    condition->generateCode(generator);

    // Jump back to start if condition is true (opposite of while loop)
    generator.handleConditionalJump("JNZ", startLabel);

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// ForNode implementation
ForNode::ForNode(std::unique_ptr<ASTNode> initialization,
                 std::unique_ptr<ASTNode> condition,
                 std::unique_ptr<ASTNode> update,
                 std::unique_ptr<BlockNode> body,
                 int loopId,
                 int lineNumber)
    : initialization(std::move(initialization)),
      condition(std::move(condition)),
      update(std::move(update)),
      body(std::move(body)),
      loopId(loopId),
      lineNumber(lineNumber) {}

std::string ForNode::getType() const
{
    return "void";
}

void ForNode::generateCode(QuadruplesGenerator &generator)
{
    const std::string prefix = "for_" + std::to_string(loopId) + "_";
    const std::string condLabel = prefix + "cond";
    const std::string bodyLabel = prefix + "body";
    const std::string updateLabel = prefix + "update";
    const std::string endLabel = prefix + "end";

    // 1. Initialization
    if (initialization)
    {
        initialization->generateCode(generator);
    }

    // 2. Condition check (first and every iteration)
    generator.addQuadruple("LABEL", "", "", condLabel);

    condition->getType();
    condition->generateCode(generator);

    // if (cond) goto body
    generator.handleConditionalJump("JNZ", bodyLabel);
    // else exit loop
    generator.handleJump(endLabel);

    // 3. Loop body
    generator.addQuadruple("LABEL", "", "", bodyLabel);
    body->generateCode(generator);

    // 4. Update clause
    generator.addQuadruple("LABEL", "", "", updateLabel);
    if (update)
    {
        update->generateCode(generator);
    }
    // go back to condition
    generator.handleJump(condLabel);

    // 5. Exit point
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// BreakNode implementation
BreakNode::BreakNode(std::string endLabel, int lineNumber) : endLabel(endLabel), lineNumber(lineNumber) {}

std::string BreakNode::getType() const
{
    return "void";
}

void BreakNode::generateCode(QuadruplesGenerator &generator)
{
    generator.handleJump(endLabel);
}

// BreakNode implementation
ContinueNode::ContinueNode(std::string endLabel, int lineNumber) : endLabel(endLabel), lineNumber(lineNumber) {}

std::string ContinueNode::getType() const
{
    return "void";
}

void ContinueNode::generateCode(QuadruplesGenerator &generator)
{
    generator.handleJump(endLabel);
}

SwitchNode::SwitchNode(std::unique_ptr<ASTNode> expression,
                       std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases,
                       std::unique_ptr<BlockNode> defaultCase,
                       std::string endLabel,
                       BlockNode *block,
                       int lineNumber)
    : expression(std::move(expression)),
      cases(std::move(cases)),
      defaultCase(std::move(defaultCase)),
      endLabel(endLabel),
      block(block),
      lineNumber(lineNumber) {}

std::string SwitchNode::getType() const
{
    return "void";
}

void SwitchNode::generateCode(QuadruplesGenerator &generator)
{
    if (expression->getType() != "int")
    {
        ErrorHandler::getInstance()->reportError("Switch expression must be an integer", lineNumber);
    }

    // Evaluate the switch expression once and store its value
    std::string numberStr;
    for (char c : endLabel)
    {
        if (isdigit(c))
        {
            numberStr += c;
        }
    }
    std::unordered_set<std::string> caseValues;
    for (const auto &casePair : cases)
    {
        // Get the case expression (first element of the pair)
        auto &caseExpr = casePair.first;
        std::string exprType = caseExpr->getType();

        // Check if the expression type is int
        if (exprType != "int")
        {
            ErrorHandler::getInstance()->reportError(
                "Switch case expression must be of type int, got '" + exprType + "'",
                lineNumber);
            continue;
        }

        // Try casting to LiteralNode or IdentifierNode for value checking
        LiteralNode *literalNode = dynamic_cast<LiteralNode *>(caseExpr.get());
        IdentifierNode *identifierNode = dynamic_cast<IdentifierNode *>(caseExpr.get());

        if (literalNode != nullptr)
        {
            // LiteralNode: Check for duplicate values
            std::string value = literalNode->getValue();
            if (caseValues.find(value) != caseValues.end())
            {
                ErrorHandler::getInstance()->reportError(
                    "Duplicate case value '" + value + "' in switch statement",
                    lineNumber);
            }
            else
            {
                caseValues.insert(value);
            }
        }
        else if (identifierNode != nullptr)
        {
            // IdentifierNode: Check if it's a constant int and get its value
            Symbol *symbol = block->getSymbol(identifierNode->getName());
            if (symbol == nullptr)
            {
                ErrorHandler::getInstance()->reportError(
                    "Undeclared variable '" + identifierNode->getName() + "' used in switch case",
                    lineNumber);
            }
            else if (!symbol->isConstant())
            {
                ErrorHandler::getInstance()->reportError(
                    "Switch case identifier '" + identifierNode->getName() + "' must be a constant",
                    lineNumber);
            }
            else if (symbol->getType() != "int")
            {
                ErrorHandler::getInstance()->reportError(
                    "Switch case identifier '" + identifierNode->getName() + "' must be of type int, got '" + symbol->getType() + "'",
                    lineNumber);
            }
            else
            {
                // Check for duplicate values
                std::string value = symbol->getValue();
                if (caseValues.find(value) != caseValues.end())
                {
                    ErrorHandler::getInstance()->reportError(
                        "Duplicate case value '" + value + "' in switch statement",
                        lineNumber);
                }
                else
                {
                    caseValues.insert(value);
                }
            }
        }
        // Non-Literal/Non-Identifier: No value check needed, type is already verified as int
    }

    expression->generateCode(generator);
    std::string switchValue = "S" + numberStr;
    generator.addQuadruple("assign", generator.operandStack.top(), "", switchValue);
    generator.operandStack.pop();

    // Generate a unique label for each case and the end
    std::vector<std::string> caseLabels;
    for (size_t i = 0; i < cases.size(); i++)
    {
        caseLabels.push_back("case_" + std::to_string(i) + "_switch_" + numberStr);
    }

    // Generate code to jump to the appropriate case
    for (size_t i = 0; i < cases.size(); i++)
    {
        // Push switch value back on stack
        generator.operandStack.push(switchValue);

        // Evaluate the case expression
        if (cases[i].first->getType() == "int")
        {
            cases[i].first->generateCode(generator);
        }
        else
        {
            // ErrorHandler::getInstance()->reportError("Switch case expression must be an integer", lineNumber);
            return;
        }
        
        // Compare with switch value and generate conditional jump
        generator.handleArithmeticOp("EQ", expression->getType(), cases[i].first->getType());

        // Conditional jump to case label if equal
        generator.handleConditionalJump("JNZ", caseLabels[i]);
    }

    // If no case matches, jump to default or end
    if (defaultCase)
    {
        generator.handleJump("default_" + endLabel);
    }
    else
    {
        generator.handleJump(endLabel);
    }

    // Generate code for each case body
    for (size_t i = 0; i < cases.size(); i++)
    {
        generator.handleLabel(caseLabels[i]);
        cases[i].second->generateCode(generator);
    }

    // Generate code for default case if it exists
    if (defaultCase)
    {
        generator.handleLabel("default_" + endLabel);
        defaultCase->generateCode(generator);
    }

    // End of switch statement
    generator.handleLabel(endLabel);
}
