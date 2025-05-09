#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <stack>

/**
 * Represents a quadruple instruction (op, arg1, arg2, result)
 */
struct Quadruple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

/**
 * Generates quadruples (intermediate code) from AST
 */
class QuadruplesGenerator {
private:
    std::vector<Quadruple> quadruples;
    std::ofstream outFile;
    int tempVarCounter;
    
    std::string generateTemp();

public:
    std::stack<std::string> operandStack;
    
    QuadruplesGenerator(const std::string& filename);
    ~QuadruplesGenerator();
    
    void writeQuadruplesToFile();
    void addQuadruple(const std::string& op, const std::string& arg1, 
                     const std::string& arg2, const std::string& result);
    
    // Operations for code generation
    void pushInt(int value);
    void pushFloat(float value);
    void pushString(const std::string& value);
    void handleArithmeticOp(const std::string& op, const std::string& leftType, const std::string& rightType);
    void handleAssignment(const std::string& identifier);
    void handlePrint();
    void handleIdentifier(const std::string& identifier, const std::string& op = "");
    void handleFunctionDeclaration(const std::string& name, const std::string& returnType);
    void handleFunctionCall(const std::string& name, int argCount);
    void handleReturn(bool hasReturnValue);
    void handleParameter(int paramIndex);
    void handleJump(const std::string& label);
    void handleConditionalJump(const std::string& condition, const std::string& label);
    void handleLabel(const std::string& label);
    void handlelCast(const std::string& type);
    void handleParameterDefinition(const std::string& name, const std::string& type, int index);
};