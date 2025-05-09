#include "semantic/type_checker.hpp"
#include "error/error_handler.hpp"

/********************************
 * ArithmeticTypeChecker Implementation
 ********************************/
std::string ArithmeticTypeChecker::checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // Check if types are compatible for arithmetic operations
    if (op1Type == "void" || op2Type == "void")
    {
        errorHandler->reportError("Invalid operator for given types", lineNumber);
        return "int"; // Return a default type to prevent cascade errors
    }

    // String concatenation (only for + operator)
    if (op1Type == "string" && op2Type == "string") 
    {
        if (this->op == "+") 
        {
            return "string";
        } 
        else 
        {
            errorHandler->reportError("String type only supports + operator for concatenation", lineNumber);
            return "string"; // Return string to prevent cascade errors
        }
    }

    // String with non-string operands is invalid
    if (op1Type == "string" || op2Type == "string") 
    {
        errorHandler->reportError("Cannot perform arithmetic operations between string and non-string types", lineNumber);
        return "string"; // Return a type to prevent cascade errors
    }

    // Type promotion rules for numeric and boolean types
    
    // If either operand is float, result is float (highest precedence)
    if (op1Type == "float" || op2Type == "float")
    {
        return "float";
    }
    
    // If either operand is int, result is int (unless other operand is float)
    if (op1Type == "int" || op2Type == "int")
    {
        return "int";
    }
    
    // If either operand is char, result is char (unless other operand is int or float)
    if (op1Type == "char" || op2Type == "char")
    {
        return "char";
    }
    
    // If both operands are bool, result is int (bool arithmetic typically promotes to int)
    return "int";
}

std::string ArithmeticTypeChecker::checkType(const std::string &opType, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // For unary operations like negation
    if (opType == "string" || opType == "void")
    {
        errorHandler->reportError("Invalid operator for given type", lineNumber);
        return opType; // Return original type to prevent cascade errors
    }
    
    // Numeric promotion for unary operators
    if (opType == "bool")
    {
        return "int"; // bool promotes to int for arithmetic operations
    }
    
    return opType; // int, float, and char remain unchanged
}

void ArithmeticTypeChecker::setOperator(const std::string &op)
{
    this->op = op;
}

/********************************
 * ComparisonTypeChecker Implementation
 ********************************/
std::string ComparisonTypeChecker::checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // Check if types are compatible for comparison operations
    if (op1Type == "void" || op2Type == "void")
    {
        errorHandler->reportError("Cannot compare void type", lineNumber);
        return "bool"; // Return bool even in error case to prevent cascade errors
    }

    // String can only be compared with string using == and !=
    if ((op1Type == "string" || op2Type == "string") && 
        (op1Type != op2Type || (this->op != "==" && this->op != "!=")))
    {
        errorHandler->reportError("String type can only be compared with string type using == or !=", lineNumber);
        return "bool";
    }

    // Other numeric types (int, float, char, bool) can be compared with each other
    return "bool";
}

std::string ComparisonTypeChecker::checkType(const std::string &opType, int lineNumber)
{
    // No unary comparison operators
    ErrorHandler *errorHandler = ErrorHandler::getInstance();
    errorHandler->reportError("Unexpected unary comparison operation", lineNumber);
    return "bool";
}

void ComparisonTypeChecker::setOperator(const std::string &op)
{
    this->op = op;
}

/********************************
 * BooleanTypeChecker Implementation
 ********************************/
std::string BooleanTypeChecker::checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // Check if types are compatible for boolean operations
    if (op1Type == "string" || op2Type == "string" ||
        op1Type == "char" || op2Type == "char" ||
        op1Type == "void" || op2Type == "void")
    {
        errorHandler->reportError("Invalid operator for given types", lineNumber);
    }

    return "bool";
}

std::string BooleanTypeChecker::checkType(const std::string &opType, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();
    
    // For unary operations like logical NOT
    if (opType == "string" || opType == "char" || opType == "void")
    {
        errorHandler->reportError("Invalid operator for given type", lineNumber);
    }

    return "bool";
}

/********************************
 * BitwiseTypeChecker Implementation
 ********************************/
std::string BitwiseTypeChecker::checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // Check if types are compatible for bitwise operations (int only)
    if (op1Type != "int" || op2Type != "int")
    {
        errorHandler->reportError("Bitwise operators require integer operands", lineNumber);
    }

    return "int";
}

std::string BitwiseTypeChecker::checkType(const std::string &opType, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // For unary operations (not typically used with bitwise)
    if (opType != "int")
    {
        errorHandler->reportError("Bitwise operators require integer operands", lineNumber);
    }

    return "int";
}

/********************************
 * TypeCheckerFactory Implementation
 ********************************/
std::unique_ptr<TypeChecker> TypeCheckerFactory::createTypeChecker(const std::string &operatorType, const std::string &op)
{
    if (operatorType == "arithmetic")
    {
        auto checker = std::make_unique<ArithmeticTypeChecker>();
        checker->setOperator(op);
        return checker;
    }
    else if (operatorType == "boolean")
    {
        return std::make_unique<BooleanTypeChecker>();
    }
    else if (operatorType == "bitwise")
    {
        return std::make_unique<BitwiseTypeChecker>();
    }
    else if (operatorType == "comparison")
    {
        auto checker = std::make_unique<ComparisonTypeChecker>();
        checker->setOperator(op);
        return checker;
    }
    throw std::invalid_argument("Unknown operator type: " + operatorType);
}