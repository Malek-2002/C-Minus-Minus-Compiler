#include "ast/function_nodes.hpp"
#include "error/error_handler.hpp"
#include "codegen/quadruples_generator.hpp"

/********************************
 * FunctionDeclarationNode Implementation
 ********************************/
FunctionDeclarationNode::FunctionDeclarationNode(const std::string &returnType, const std::string &name,
                                                 std::vector<std::pair<std::string, std::string>> parameters,
                                                 std::unique_ptr<BlockNode> body, BlockNode *parentBlock, int lineNumber)
    : returnType(returnType), name(name), parameters(std::move(parameters)),
      body(std::move(body)), parentBlock(parentBlock), lineNumber(lineNumber) {}

std::string FunctionDeclarationNode::getType() const
{
    return returnType;
}

void FunctionDeclarationNode::generateCode(QuadruplesGenerator &generator)
{
    // Create function symbol and add to global function table
    FunctionSymbol funcSymbol(name, returnType, true, lineNumber);

    // Add parameters to function symbol
    for (const auto &param : parameters)
    {
        funcSymbol.addParameter(param.first, param.second);
    }

    // Check if function already exists
    if (parentBlock->functionExists(name))
    {
        ErrorHandler::getInstance()->reportError("Function '" + name + "' already declared", lineNumber);
        return;
    }

    // Add function to parent block's function table
    parentBlock->addFunction(funcSymbol);

    // Generate function declaration
    generator.handleFunctionDeclaration(name, returnType);
    
    // Generate parameter definition quadruples
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        const auto &param = parameters[i];
        // Generate param_def quadruple with name, type, and position
        generator.handleParameterDefinition(param.second, param.first, i);
        
        // Add parameter to the function's block scope
        Symbol paramSymbol(param.second, param.first, false, lineNumber, "parameter");
        paramSymbol.setInitialized(); // Parameters are always initialized
        body->addSymbol(paramSymbol);
    }

    // Generate code for function body
    body->generateCode(generator);

    // If no explicit return at end of function, add one
    if (returnType == "void")
    {
        generator.handleReturn(false);
    }

    // End of function
    generator.addQuadruple("ENDFUNC", "", "", name);
}

/********************************
 * FunctionCallNode Implementation
 ********************************/
FunctionCallNode::FunctionCallNode(const std::string &name, std::vector<std::unique_ptr<ASTNode>> arguments,
                                   BlockNode *block, int lineNumber)
    : name(name), arguments(std::move(arguments)), block(block), lineNumber(lineNumber) {}

std::string FunctionCallNode::getType() const
{
    // Check if function exists
    FunctionSymbol *function = block->getFunction(name);
    if (!function)
    {
        ErrorHandler::getInstance()->reportError("Function '" + name + "' not declared", lineNumber);
        return "void"; // Default to void for error recovery
    }
    return function->getReturnType();
}

void FunctionCallNode::generateCode(QuadruplesGenerator &generator)
{
    // Check if function exists
    FunctionSymbol *function = block->getFunction(name);
    if (!function)
    {
        ErrorHandler::getInstance()->reportError("Function '" + name + "' not declared", lineNumber);
        return;
    }
    function->setIsUsed();

    // Check argument count
    if (arguments.size() != function->getParameterCount())
    {
        ErrorHandler::getInstance()->reportError(
            "Function '" + name + "' called with wrong number of arguments (expected " +
                std::to_string(function->getParameterCount()) + ", got " +
                std::to_string(arguments.size()) + ")",
            lineNumber);
        // return;
    }

    // Generate code for arguments in the correct order
    // The QuadruplesGenerator::handleFunctionCall will handle the reversal internally
    for (size_t i = 0; i < arguments.size(); ++i)
    {
        // Type check argument against parameter
        std::string paramType = function->getParameterType(i);
        std::string argType = arguments[i]->getType();

        if (paramType != argType)
        {
            ErrorHandler::getInstance()->reportError(
                "Argument " + std::to_string(i + 1) + " of function '" + name +
                    "' has wrong type (expected " + paramType + ", got " + argType + ")",
                lineNumber);
            // continue;
        }

        // Generate code for argument
        arguments[i]->generateCode(generator);
    }

    // Generate function calls
    generator.handleFunctionCall(name, arguments.size());
}

/********************************
 * ReturnNode Implementation
 ********************************/
ReturnNode::ReturnNode(std::unique_ptr<ASTNode> expression, BlockNode *block, std::string returnType, int lineNumber)
    : expression(std::move(expression)), block(block), returnType(returnType), lineNumber(lineNumber) {}

std::string ReturnNode::getType() const
{
    return expression ? expression->getType() : "void";
}

void ReturnNode::generateCode(QuadruplesGenerator &generator)
{
    // Check if return type matches function's declared return type
    // This would require knowing the enclosing function's return type
    // For simplicity, we'll assume this is checked elsewhere

    if(returnType.empty()) {
        ErrorHandler::getInstance()->reportError("Return without function declared", lineNumber);
        return;
    }
    if (returnType != "void" && expression == nullptr)
    {
        ErrorHandler::getInstance()->reportError("Function declared to return '" + returnType +
                                                     "' but no return value provided",
                                                 lineNumber);
        return;
    }
    if (returnType == "void" && expression)
    {
        ErrorHandler::getInstance()->reportError("Function declared to return 'void' but return value provided", lineNumber);
        return;
    }
    if ((returnType == "float" && expression->getType() == "int") ||
        (returnType == "int" && expression->getType() == "float"))
    {
    }
    else if (expression && expression->getType() != returnType)
    {
        ErrorHandler::getInstance()->reportError("Return type mismatch: expected '" + returnType +
                                                     "' but got '" + expression->getType() + "'",
                                                 lineNumber);
        return;
    }
    // Generate code for return expression if it exists
    if (expression)
    {
        expression->generateCode(generator);
        generator.handleReturn(true);
    }
}