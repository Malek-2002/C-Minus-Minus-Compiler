#include "ast/expression_nodes.hpp"
#include "semantic/symbol.hpp"
#include "error/error_handler.hpp"
#include "semantic/type_checker.hpp"
#include "ast/block_node.hpp"

/********************************
 * LiteralNode Implementation
 ********************************/
LiteralNode::LiteralNode(const std::string &type, const std::string &value)
    : type(type), value(value) {}

std::string LiteralNode::getType() const
{
    return type;
}

std::string LiteralNode::getValue() const
{
    return value;
}

void LiteralNode::generateCode(QuadruplesGenerator &generator)
{
    if (type == "int")
    {
        generator.pushInt(std::stoi(value));
    }
    else if (type == "float")
    {
        generator.pushFloat(std::stof(value));
    }
    else if (type == "bool")
    {
        generator.pushString(value);
    }
    else if (type == "string" || type == "char")
    {
        if (type == "string")
        {
            generator.pushString("\"\"" + value + "\"\"");
        }
        else // it's "char"
        {
            generator.pushString("'" + value + "'");
        }
    }
}

/********************************
 * IdentifierNode Implementation
 ********************************/
IdentifierNode::IdentifierNode(const std::string &name, BlockNode *block, int lineNumber)
    : name(name), block(block), lineNumber(lineNumber) {}

std::string IdentifierNode::getType() const
{
    Symbol *symbol = block->getSymbol(name);
    if (!symbol)
    {
        ErrorHandler *errorHandler = ErrorHandler::getInstance();
        errorHandler->reportError("uninisialized valiable " + name, lineNumber);
        return "";
    }
    symbol->setUsed();
    return symbol->getType();
}

std::string IdentifierNode::getName() const
{
    return name;
}

void IdentifierNode::generateCode(QuadruplesGenerator &generator)
{
    Symbol* symbol = block->getSymbol(name);
    if (!symbol)
    {
        ErrorHandler *errorHandler = ErrorHandler::getInstance();
        errorHandler->reportError("Undeclared valiable " + name, lineNumber);
        return;
    }
    if(symbol->checkInitialization() == false)
    {
        ErrorHandler *errorHandler = ErrorHandler::getInstance();
        errorHandler->reportWarning("you want to use uninisialized valiable " + name, lineNumber);
    }
    generator.handleIdentifier(name);
}

/********************************
 * UnaryOpNode Implementation
 ********************************/
UnaryOpNode::UnaryOpNode(const std::string &op, std::unique_ptr<ASTNode> operand, int lineNumber)
    : op(op), operand(std::move(operand)), lineNumber(lineNumber) {}

std::string UnaryOpNode::getType() const
{
    std::unique_ptr<TypeChecker> checker;

    if (op == "-")
    {
        checker = TypeCheckerFactory::createTypeChecker("arithmetic", op);
    }
    else if (op == "!")
    {
        checker = TypeCheckerFactory::createTypeChecker("boolean", op);
    }
    else
    {
        ErrorHandler::getInstance()->reportError("Unknown unary operator: " + op, lineNumber);
    }

    return checker->checkType(operand->getType(), lineNumber);
}

void UnaryOpNode::generateCode(QuadruplesGenerator &generator)
{
    operand->generateCode(generator);

    if (op == "-")
    {
        generator.handleArithmeticOp("NEG", operand->getType(), "");
    }
    else if (op == "!")
    {
        generator.handleArithmeticOp("NOT", operand->getType(), "");
    }
}


/********************************
 * BinaryOpNode Implementation
 ********************************/
BinaryOpNode::BinaryOpNode(const std::string &op, std::unique_ptr<ASTNode> left,
                           std::unique_ptr<ASTNode> right, int lineNumber)
    : op(op), left(std::move(left)), right(std::move(right)), lineNumber(lineNumber) {}

std::string BinaryOpNode::getType() const
{
    std::unique_ptr<TypeChecker> checker;

    if (op == "+" || op == "-" || op == "*" || op == "/")
    {
        checker = TypeCheckerFactory::createTypeChecker("arithmetic", op);
    }
    else if (op == "==" || op == "!=" || op == ">" || op == "<" || op == ">=" || op == "<=")
    {
        checker = TypeCheckerFactory::createTypeChecker("comparison", op);
    }
    else if (op == "&&" || op == "||")
    {
        checker = TypeCheckerFactory::createTypeChecker("boolean", op);
    }
    else if (op == "^" || op == "|" || op == "&" || op == "<<" || op == ">>" || op == "%")
    {
        checker = TypeCheckerFactory::createTypeChecker("bitwise", op);
    }
    else
    {
        ErrorHandler::getInstance()->reportError("Unknown binary operator: " + op, lineNumber);
    }

    return checker->checkTypes(left->getType(), right->getType(), lineNumber);
}

void BinaryOpNode::generateCode(QuadruplesGenerator &generator)
{    
    // Generate code for left and right operands
    left->generateCode(generator);
    right->generateCode(generator);
    
    // Generate operation code based on operator type
    if (op == "+")
    {
        generator.handleArithmeticOp("ADD", left->getType(), right->getType());
    }
    else if (op == "-")
    {
        generator.handleArithmeticOp("SUB", left->getType(), right->getType());
    }
    else if (op == "*")
    {
        generator.handleArithmeticOp("MUL", left->getType(), right->getType());
    }
    else if (op == "/")
    {
        generator.handleArithmeticOp("DIV", left->getType(), right->getType());
    }
    else if (op == "%")
    {
        generator.handleArithmeticOp("MOD", left->getType(), right->getType());
    }
    else if (op == "^")
    {
        generator.handleArithmeticOp("XOR", left->getType(), right->getType());
    }
    else if (op == "||")
    {
        generator.handleArithmeticOp("OR", left->getType(), right->getType());
    }
    else if (op == "&&")
    {
        generator.handleArithmeticOp("AND", left->getType(), right->getType());
    }
    else if (op == "==")
    {
        generator.handleArithmeticOp("EQ", left->getType(), right->getType());
    }
    else if (op == "!=")
    {
        generator.handleArithmeticOp("NEQ", left->getType(), right->getType());
    }
    else if (op == ">")
    {
        generator.handleArithmeticOp("GT", left->getType(), right->getType());
    }
    else if (op == "<")
    {
        generator.handleArithmeticOp("LT", left->getType(), right->getType());
    }
    else if (op == ">=")
    {
        generator.handleArithmeticOp("GTE", left->getType(), right->getType());
    }
    else if (op == "<=")
    {
        generator.handleArithmeticOp("LTE", left->getType(), right->getType());
    }
    else if (op == "|")
    {
        generator.handleArithmeticOp("BOR", left->getType(), right->getType());
    }
    else if (op == "&")
    {
        generator.handleArithmeticOp("BAND", left->getType(), right->getType());;
    }
    else if (op == "<<")
    {
        generator.handleArithmeticOp("SHL", left->getType(), right->getType());
    }
    else if (op == ">>")
    {
        generator.handleArithmeticOp("SHR", left->getType(), right->getType());
    }
}