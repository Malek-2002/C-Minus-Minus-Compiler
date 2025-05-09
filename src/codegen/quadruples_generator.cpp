#include "codegen/quadruples_generator.hpp"
#include <iostream>

/********************************
 * QuadruplesGenerator Implementation
 ********************************/
QuadruplesGenerator::QuadruplesGenerator(const std::string &filename) : tempVarCounter(0)
{
    outFile.open(filename, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening output file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

QuadruplesGenerator::~QuadruplesGenerator()
{
    if (outFile.is_open())
    {
        outFile.close();
    }
}

void QuadruplesGenerator::writeQuadruplesToFile()
{
    // Write header
    outFile << "index,op,arg1,arg2,result\n";

    // Write each quadruple in CSV format
    for (size_t i = 0; i < quadruples.size(); ++i)
    {
        outFile << i << ","
                << quadruples[i].op << ","
                << quadruples[i].arg1 << ","
                << quadruples[i].arg2 << ","
                << quadruples[i].result << "\n";
    }
}

std::string QuadruplesGenerator::generateTemp()
{

    tempVarCounter = (tempVarCounter + 1) % 10;
    return "t" + std::to_string(tempVarCounter);
}

void QuadruplesGenerator::addQuadruple(const std::string &op, const std::string &arg1,
                                      const std::string &arg2, const std::string &result)
{
    Quadruple quad;
    quad.op = op;
    quad.arg1 = arg1;
    quad.arg2 = arg2;
    quad.result = result;
    quadruples.push_back(quad);
}

void QuadruplesGenerator::pushInt(int value)
{
    // Store constant in a temporary variable
    std::string temp = generateTemp();
    addQuadruple("assign", std::to_string(value), "", temp);
    operandStack.push(temp);
}

void QuadruplesGenerator::pushFloat(float value)
{
    // Store constant in a temporary variable
    std::string temp = generateTemp();
    addQuadruple("assign", std::to_string(value), "", temp);
    operandStack.push(temp);
}

void QuadruplesGenerator::pushString(const std::string &value)
{
    // Store string constant in a temporary variable
    std::string temp = generateTemp();
    addQuadruple("assign", "\"" + value + "\"", "", temp);
    operandStack.push(temp);
}

void QuadruplesGenerator::handleArithmeticOp(const std::string &op, const std::string &leftType, const std::string &rightType)
{
    // For binary operations, pop two operands
    if (op != "NEG" && op != "NOT") {
        std::string right = operandStack.top(); operandStack.pop();
        std::string left = operandStack.top(); operandStack.pop();
        
        std::string temp = generateTemp();
        addQuadruple(op, left, right, temp);
        operandStack.push(temp);
    }
    // For unary operations, pop one operand
    else {
        std::string operand = operandStack.top(); operandStack.pop();
        
        std::string temp = generateTemp();
        addQuadruple(op, operand, "", temp);
        operandStack.push(temp);
    }
}

void QuadruplesGenerator::handleAssignment(const std::string &identifier)
{
    std::string value = operandStack.top(); operandStack.pop();
    addQuadruple("assign", value, "", identifier);
}

void QuadruplesGenerator::handlePrint()
{
    std::string value = operandStack.top(); operandStack.pop();
    addQuadruple("PRINT", value, "", "");
}

void QuadruplesGenerator::handleIdentifier(const std::string &identifier, const std::string &op)
{
    // Just push the identifier onto the stack
    if (op.empty()) {
        operandStack.push(identifier);
    } 
    // Otherwise handle with the specified operation
    else {
        std::string temp = generateTemp();
        addQuadruple(op, identifier, "", temp);
        operandStack.push(temp);
    }
}

void QuadruplesGenerator::handleFunctionDeclaration(const std::string &name, const std::string &returnType)
{
    // Function declaration
    addQuadruple("FUNC", returnType, "", name);
}

void QuadruplesGenerator::handleFunctionCall(const std::string &name, int argCount)
{
    // Handle arguments - they would be popped from the stack in reverse order
    std::vector<std::string> args;
    for (int i = 0; i < argCount; i++) {
        args.push_back(operandStack.top());
        operandStack.pop();
    }
    
    // Generate param quadruples in correct order
    for (int i = args.size() - 1; i >= 0; i--) {
        // Now we generate param quadruples with index to match the param_def
        // This helps maintain the relationship between call site and declaration
        addQuadruple("param", args[i], "", std::to_string(args.size() - 1 - i));
    }
    
    // Generate call and store result
    std::string temp = generateTemp();
    addQuadruple("call", name, std::to_string(argCount), temp);
    operandStack.push(temp);
}

void QuadruplesGenerator::handleReturn(bool hasReturnValue)
{
    if (hasReturnValue) {
        std::string value = operandStack.top(); operandStack.pop();
        addQuadruple("return", value, "", "");
    } else {
        addQuadruple("return", "", "", "");
    }
}

void QuadruplesGenerator::handleParameter(int paramIndex)
{
    // Parameters should have already been processed by the function call
    // This might be used for accessing parameters in function body
    std::string paramName = "param" + std::to_string(paramIndex);
    operandStack.push(paramName);
}

void QuadruplesGenerator::handleJump(const std::string &label)
{
    addQuadruple("JMP", "", "", label);
}

void QuadruplesGenerator::handleConditionalJump(const std::string &condition, const std::string &label)
{
    std::string condValue = operandStack.top(); operandStack.pop();
    addQuadruple(condition, condValue, "", label);
}

void QuadruplesGenerator::handleLabel(const std::string &label)
{
    addQuadruple("label", "", "", label);
}

void QuadruplesGenerator::handlelCast(const std::string &type)
{
    std::string temp = generateTemp();
    std::string value = operandStack.top(); operandStack.pop();
    addQuadruple("cast", type, value, temp);
    operandStack.push(temp);
}

void QuadruplesGenerator::handleParameterDefinition(const std::string& name, const std::string& type, int index)
{
    addQuadruple("param_declare", type,  std::to_string(index), name);
}