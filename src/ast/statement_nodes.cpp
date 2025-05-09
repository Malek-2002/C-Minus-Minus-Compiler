
#include "ast/statement_nodes.hpp"
#include "error/error_handler.hpp"
#include "codegen/quadruples_generator.hpp"
#include "ast/expression_nodes.hpp"
#include <string>
/********************************
 * DeclarationNode Implementation
 ********************************/
DeclarationNode::DeclarationNode(const std::string type, const std::string identifier, bool isConstant,
                                 std::unique_ptr<ASTNode> initializer, BlockNode *block, int lineNumber)
    : type(type), identifier(identifier), isConstant(isConstant), initializer(std::move(initializer)),
      block(block), lineNumber(lineNumber)
{
}

std::string DeclarationNode::getType() const
{
    return type;
}

#include <string>    // For std::to_string
#include <algorithm> // For std::reverse (if custom int_to_string needed)

void DeclarationNode::generateCode(QuadruplesGenerator &generator)
{
    // First declare the variable/constant in symbol table
    Symbol newSymbol(identifier, type, isConstant, lineNumber);
    bool result = block->addSymbol(newSymbol);
    if (!result)
    {
        // Handle error: symbol already exists in this scope
        ErrorHandler::getInstance()->reportError("Redeclaration of '" + identifier + "' in same scope", lineNumber);
        return;
    }

    // If there's an initializer, generate code for it
    if (initializer)
    {
        // Get the symbol we just added
        Symbol *symbol = block->getSymbol(identifier);
        if (symbol == nullptr)
        {
            ErrorHandler::getInstance()->reportError("Internal error: Symbol '" + identifier + "' not found after declaration", lineNumber);
            return;
        }

        // Get the initializer's type
        std::string initializerType = initializer->getType();
        std::string symbolType = symbol->getType();

        if (initializerType.empty())
        {
            ErrorHandler::getInstance()->reportError("Initializer type is empty for '" + identifier + "'", lineNumber);
            return;
        }

        // Type checking logic - allow assignments between char, int, float, bool
        bool isTypeCompatible = false;
        bool needsCast = false;
        bool isString = false;

        // Check if either type is a string - we'll keep strings incompatible with numeric types
        if (symbolType == "string" || initializerType == "string")
        {
            isString = true;
            // Only allow string-to-string assignment
            isTypeCompatible = (symbolType == initializerType);
        }
        else
        {
            // For non-string types (char, int, float, bool), allow cross-type assignments
            const std::vector<std::string> numericTypes = {"char", "int", "float", "bool"};

            // Check if both types are in our list of compatible types
            bool symbolIsNumeric = std::find(numericTypes.begin(), numericTypes.end(), symbolType) != numericTypes.end();
            bool initializerIsNumeric = std::find(numericTypes.begin(), numericTypes.end(), initializerType) != numericTypes.end();

            isTypeCompatible = symbolIsNumeric && initializerIsNumeric;

            // Need to cast if types differ
            needsCast = (symbolType != initializerType) && isTypeCompatible;
        }

        // Report error if types are incompatible
        if (!isTypeCompatible)
        {
            ErrorHandler::getInstance()->reportError(
                "Cannot initialize '" + identifier + "' of type '" + symbolType + "' with '" + initializerType + "'",
                lineNumber);
            return;
        }

        // Generate code for the initializer
        initializer->generateCode(generator);

        // Handle type conversion with CAST quadruple if types differ
        if (needsCast)
        {
            // Generate CAST quadruple for type conversion
            generator.handlelCast(symbolType);
        }

        // Attempt to cast to LiteralNode* for setting symbol value
        LiteralNode *literalNode = dynamic_cast<LiteralNode *>(initializer.get());
        if (literalNode != nullptr)
        {
            std::string value = literalNode->getValue();

            // Handle conversion based on symbol type and initializer type
            if (symbolType == "bool")
            {
                // Convert numeric types to bool
                if (initializerType == "int" || initializerType == "float")
                {
                    try
                    {
                        double numericValue = std::stod(value);
                        value = (numericValue != 0) ? "true" : "false";
                    }
                    catch (...)
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Invalid numeric value for bool conversion: '" + value + "'",
                            lineNumber);
                        value = "false";
                    }
                }
                else if (initializerType == "char")
                {
                    // Convert char to bool (non-zero ASCII value = true)
                    if (!value.empty())
                    {
                        char charValue = value[0];
                        value = (charValue != 0) ? "true" : "false";
                    }
                    else
                    {
                        value = "false";
                    }
                }
            }
            else if (symbolType == "int")
            {
                if (initializerType == "bool")
                {
                    // Convert bool to int (true -> 1, false -> 0)
                    value = (value == "true") ? "1" : "0";
                }
                else if (initializerType == "float")
                {
                    // Convert float to int
                    try
                    {
                        int intValue = static_cast<int>(std::stof(value));
                        value = std::to_string(intValue);
                    }
                    catch (...)
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Invalid float value for int conversion: '" + value + "'",
                            lineNumber);
                        value = "0";
                    }
                }
                else if (initializerType == "char")
                {
                    // Convert char to int (ASCII value)
                    if (!value.empty())
                    {
                        int asciiValue = static_cast<int>(value[0]);
                        value = std::to_string(asciiValue);
                    }
                    else
                    {
                        value = "0";
                    }
                }
            }
            else if (symbolType == "float")
            {
                if (initializerType == "bool")
                {
                    // Convert bool to float (true -> 1.0, false -> 0.0)
                    value = (value == "true") ? "1.0" : "0.0";
                }
                else if (initializerType == "int")
                {
                    // Convert int to float
                    try
                    {
                        float floatValue = static_cast<float>(std::stoi(value));
                        value = std::to_string(floatValue);
                    }
                    catch (...)
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Invalid int value for float conversion: '" + value + "'",
                            lineNumber);
                        value = "0.0";
                    }
                }
                else if (initializerType == "char")
                {
                    // Convert char to float (ASCII value)
                    if (!value.empty())
                    {
                        float asciiValue = static_cast<float>(value[0]);
                        value = std::to_string(asciiValue);
                    }
                    else
                    {
                        value = "0.0";
                    }
                }
            }
            else if (symbolType == "char")
            {
                if (initializerType == "bool")
                {
                    // Convert bool to char (true -> '1', false -> '0')
                    value = (value == "true") ? "1" : "0";
                }
                else if (initializerType == "int")
                {
                    // Convert int to char (ASCII character)
                    try
                    {
                        int intValue = std::stoi(value);
                        // Ensure the value is within valid ASCII range
                        if (intValue >= 0 && intValue <= 127)
                        {
                            value = static_cast<char>(intValue);
                        }
                        else
                        {
                            ErrorHandler::getInstance()->reportWarning(
                                "Int value out of ASCII range for char conversion: '" + value + "'",
                                lineNumber);
                            value = "0";
                        }
                    }
                    catch (...)
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Invalid int value for char conversion: '" + value + "'",
                            lineNumber);
                        value = "0";
                    }
                }
                else if (initializerType == "float")
                {
                    // Convert float to char (ASCII character)
                    try
                    {
                        int intValue = static_cast<int>(std::stof(value));
                        // Ensure the value is within valid ASCII range
                        if (intValue >= 0 && intValue <= 127)
                        {
                            value = static_cast<char>(intValue);
                        }
                        else
                        {
                            ErrorHandler::getInstance()->reportWarning(
                                "Float value out of ASCII range for char conversion: '" + value + "'",
                                lineNumber);
                            value = "0";
                        }
                    }
                    catch (...)
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Invalid float value for char conversion: '" + value + "'",
                            lineNumber);
                        value = "0";
                    }
                }
            }

            symbol->setValue(value);
        }

        // Generate DECLARE quadruple
        generator.addQuadruple("declare", type, "blk" + std::to_string(block->getId()), identifier);

        // Handle the assignment
        generator.handleAssignment(identifier);

        // Mark the symbol as initialized
        symbol->setInitialized();
    }
}

/********************************
 * AssignmentNode Implementation
 ********************************/
AssignmentNode::AssignmentNode(const std::string &identifier, std::unique_ptr<ASTNode> expression,
                               BlockNode *block, int lineNumber)
    : identifier(identifier), expression(std::move(expression)),
      block(block), lineNumber(lineNumber)
{
}

std::string AssignmentNode::getType() const
{
    return block->getSymbol(identifier)->getType();
}

void AssignmentNode::generateCode(QuadruplesGenerator &generator)
{
    // Look up the identifier to check it exists and get its type
    Symbol *symbol = block->getSymbol(identifier);

    if (symbol == nullptr)
    {
        ErrorHandler::getInstance()->reportError("Undeclared variable '" + identifier + "' is used", lineNumber);
        return; // Stop further processing to avoid null pointer issues
    }

    // Check if it's a constant (can't reassign)
    if (symbol->isConstant())
    {
        ErrorHandler::getInstance()->reportError("Cannot reassign constant '" + identifier + "'", lineNumber);
        return;
    }

    // Get the expression's type
    std::string expressionType = expression->getType();
    std::string symbolType = symbol->getType();

    if (expressionType.empty())
    {
        ErrorHandler::getInstance()->reportError("Expression type is empty for assignment to '" + identifier + "'", lineNumber);
        return;
    }

    // Type checking logic - allow assignments between char, int, float, bool
    bool isTypeCompatible = false;
    bool needsCast = false;
    bool isString = false;

    // Check if either type is a string - we'll keep strings incompatible with numeric types
    if (symbolType == "string" || expressionType == "string")
    {
        isString = true;
        // Only allow string-to-string assignment
        isTypeCompatible = (symbolType == expressionType);
    }
    else
    {
        // For non-string types (char, int, float, bool), allow cross-type assignments
        const std::vector<std::string> numericTypes = {"char", "int", "float", "bool"};

        // Check if both types are in our list of compatible types
        bool symbolIsNumeric = std::find(numericTypes.begin(), numericTypes.end(), symbolType) != numericTypes.end();
        bool expressionIsNumeric = std::find(numericTypes.begin(), numericTypes.end(), expressionType) != numericTypes.end();

        isTypeCompatible = symbolIsNumeric && expressionIsNumeric;

        // Need to cast if types differ
        needsCast = (symbolType != expressionType) && isTypeCompatible;
    }

    // Report error if types are incompatible
    if (!isTypeCompatible)
    {
        ErrorHandler::getInstance()->reportError(
            "Cannot assign '" + expressionType + "' to variable '" + identifier + "' of type '" + symbolType + "'",
            lineNumber);
        return;
    }

    // Generate code for the expression
    expression->generateCode(generator);

    // Handle type conversion with CAST quadruple if types differ
    if (needsCast)
    {
        // Generate CAST quadruple for type conversion
        generator.handlelCast(symbolType);
    }

    // Attempt to cast to LiteralNode* for setting symbol value
    LiteralNode *literalNode = dynamic_cast<LiteralNode *>(expression.get());
    if (literalNode != nullptr)
    {
        std::string value = literalNode->getValue();

        // Handle conversion based on symbol type and expression type
        if (symbolType == "bool")
        {
            // Convert numeric types to bool
            if (expressionType == "int" || expressionType == "float")
            {
                try
                {
                    double numericValue = std::stod(value);
                    value = (numericValue != 0) ? "true" : "false";
                }
                catch (...)
                {
                    ErrorHandler::getInstance()->reportWarning(
                        "Invalid numeric value for bool conversion: '" + value + "'",
                        lineNumber);
                    value = "false";
                }
            }
            else if (expressionType == "char")
            {
                // Convert char to bool (non-zero ASCII value = true)
                if (!value.empty())
                {
                    char charValue = value[0];
                    value = (charValue != 0) ? "true" : "false";
                }
                else
                {
                    value = "false";
                }
            }
        }
        else if (symbolType == "int")
        {
            if (expressionType == "bool")
            {
                // Convert bool to int (true -> 1, false -> 0)
                value = (value == "true") ? "1" : "0";
            }
            else if (expressionType == "float")
            {
                // Convert float to int
                try
                {
                    int intValue = static_cast<int>(std::stof(value));
                    value = std::to_string(intValue);
                }
                catch (...)
                {
                    ErrorHandler::getInstance()->reportWarning(
                        "Invalid float value for int conversion: '" + value + "'",
                        lineNumber);
                    value = "0";
                }
            }
            else if (expressionType == "char")
            {
                // Convert char to int (ASCII value)
                if (!value.empty())
                {
                    int asciiValue = static_cast<int>(value[0]);
                    value = std::to_string(asciiValue);
                }
                else
                {
                    value = "0";
                }
            }
        }
        else if (symbolType == "float")
        {
            if (expressionType == "bool")
            {
                // Convert bool to float (true -> 1.0, false -> 0.0)
                value = (value == "true") ? "1.0" : "0.0";
            }
            else if (expressionType == "int")
            {
                // Convert int to float
                try
                {
                    float floatValue = static_cast<float>(std::stoi(value));
                    value = std::to_string(floatValue);
                }
                catch (...)
                {
                    ErrorHandler::getInstance()->reportWarning(
                        "Invalid int value for float conversion: '" + value + "'",
                        lineNumber);
                    value = "0.0";
                }
            }
            else if (expressionType == "char")
            {
                // Convert char to float (ASCII value)
                if (!value.empty())
                {
                    float asciiValue = static_cast<float>(value[0]);
                    value = std::to_string(asciiValue);
                }
                else
                {
                    value = "0.0";
                }
            }
        }
        else if (symbolType == "char")
        {
            if (expressionType == "bool")
            {
                // Convert bool to char (true -> '1', false -> '0')
                value = (value == "true") ? "1" : "0";
            }
            else if (expressionType == "int")
            {
                // Convert int to char (ASCII character)
                try
                {
                    int intValue = std::stoi(value);
                    // Ensure the value is within valid ASCII range
                    if (intValue >= 0 && intValue <= 127)
                    {
                        value = static_cast<char>(intValue);
                    }
                    else
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Int value out of ASCII range for char conversion: '" + value + "'",
                            lineNumber);
                        value = "0";
                    }
                }
                catch (...)
                {
                    ErrorHandler::getInstance()->reportWarning(
                        "Invalid int value for char conversion: '" + value + "'",
                        lineNumber);
                    value = "0";
                }
            }
            else if (expressionType == "float")
            {
                // Convert float to char (ASCII character)
                try
                {
                    int intValue = static_cast<int>(std::stof(value));
                    // Ensure the value is within valid ASCII range
                    if (intValue >= 0 && intValue <= 127)
                    {
                        value = static_cast<char>(intValue);
                    }
                    else
                    {
                        ErrorHandler::getInstance()->reportWarning(
                            "Float value out of ASCII range for char conversion: '" + value + "'",
                            lineNumber);
                        value = "0";
                    }
                }
                catch (...)
                {
                    ErrorHandler::getInstance()->reportWarning(
                        "Invalid float value for char conversion: '" + value + "'",
                        lineNumber);
                    value = "0";
                }
            }
        }

        symbol->setValue(value);
    }

    // Handle the assignment
    generator.handleAssignment(identifier);

    // Mark the symbol as initialized
    symbol->setInitialized();
}

/********************************
 * PrintNode Implementation
 ********************************/
PrintNode::PrintNode(std::unique_ptr<ASTNode> expression)
    : expression(std::move(expression)) {}

std::string PrintNode::getType() const
{
    return "void";
}

void PrintNode::generateCode(QuadruplesGenerator &generator)
{
    expression->getType();
    // Generate code for the expression to be printed
    expression->generateCode(generator);
    // Generate print instruction
    generator.handlePrint();
}
