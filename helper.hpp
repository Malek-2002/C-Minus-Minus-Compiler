#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <stdexcept>

// Forward declarations
class BlockNode;
class QuadruplesGenerator;
class ErrorHandler;
class TypeChecker;

/********************************
 * Singleton Pattern for Error Handler
 ********************************/
class ErrorHandler {
private:
    static ErrorHandler* instance;
    std::ofstream errorFile;
    
    // Private constructor (Singleton)
    ErrorHandler() {
        errorFile.open("./output/error_file.txt");
        if (!errorFile.is_open()) {
            std::cerr << "Failed to open error file." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
public:
    static ErrorHandler* getInstance() {
        if (instance == nullptr) {
            instance = new ErrorHandler();
        }
        return instance;
    }
    
    void reportError(const std::string& message, int lineNumber) {
        std::cerr << "Error at line " << lineNumber << ": " << message << std::endl;
        errorFile << "Error at line " << lineNumber << ": " << message << std::endl;
        exit(EXIT_FAILURE);
    }
    
    void reportWarning(const std::string& message) {
        std::cerr << "Warning: " << message << std::endl;
        errorFile << "Warning: " << message << std::endl;
    }
    
    ~ErrorHandler() {
        errorFile.close();
        delete instance;
    }
};

/********************************
 * Strategy Pattern for Type Checking
 ********************************/
class TypeChecker {
public:
    virtual ~TypeChecker() = default;
    virtual std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) = 0;
    virtual std::string checkType(const std::string& opType, int lineNumber) = 0;
};

// Concrete strategy for arithmetic operations
class ArithmeticTypeChecker : public TypeChecker {
public:
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // Check if types are compatible for arithmetic operations
        if (op1Type == "string" || op2Type == "string" ||
            op1Type == "char" || op2Type == "char" ||
            op1Type == "void" || op2Type == "void") {
            errorHandler->reportError("Invalid operator for given types", lineNumber);
        }
        
        // Return the resulting type (promote to float if one operand is float)
        if (op1Type == "float" || op2Type == "float") {
            return "float";
        }
        return op1Type;
    }
    
    std::string checkType(const std::string& opType, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // For unary operations like negation
        if (opType != "int" && opType != "float") {
            errorHandler->reportError("Invalid operator for given type", lineNumber);
        }
        return opType;
    }
};

// Concrete strategy for boolean operations
class BooleanTypeChecker : public TypeChecker {
public:
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // Check if types are compatible for boolean operations
        if (op1Type == "string" || op2Type == "string" ||
            op1Type == "char" || op2Type == "char" ||
            op1Type == "void" || op2Type == "void") {
            errorHandler->reportError("Invalid operator for given types", lineNumber);
        }
        
        return "bool";
    }
    
    std::string checkType(const std::string& opType, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // For unary operations like logical NOT
        if (opType == "string" || opType == "char" || opType == "void") {
            errorHandler->reportError("Invalid operator for given type", lineNumber);
        }
        
        return "bool";
    }
};

// Concrete strategy for bitwise operations
class BitwiseTypeChecker : public TypeChecker {
public:
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // Check if types are compatible for bitwise operations (int only)
        if (op1Type != "int" || op2Type != "int") {
            errorHandler->reportError("Bitwise operators require integer operands", lineNumber);
        }
        
        return "int";
    }
    
    std::string checkType(const std::string& opType, int lineNumber) override {
        ErrorHandler* errorHandler = ErrorHandler::getInstance();
        
        // For unary operations (not typically used with bitwise)
        if (opType != "int") {
            errorHandler->reportError("Bitwise operators require integer operands", lineNumber);
        }
        
        return "int";
    }
};

/********************************
 * Factory Method Pattern for Type Checker creation
 ********************************/
class TypeCheckerFactory {
public:
    static std::unique_ptr<TypeChecker> createTypeChecker(const std::string& operatorType) {
        if (operatorType == "arithmetic") {
            return std::make_unique<ArithmeticTypeChecker>();
        } else if (operatorType == "boolean") {
            return std::make_unique<BooleanTypeChecker>();
        } else if (operatorType == "bitwise") {
            return std::make_unique<BitwiseTypeChecker>();
        }
        throw std::invalid_argument("Unknown operator type: " + operatorType);
    }
};

/********************************
 * Composite Pattern for AST Nodes
 ********************************/
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string getType() const = 0;
    virtual void generateCode(QuadruplesGenerator& generator) = 0;
};

// Leaf node for literals (int, float, bool, string, char)
class LiteralNode : public ASTNode {
private:
    std::string type;
    std::string value;
    
public:
    LiteralNode(const std::string& type, const std::string& value) 
        : type(type), value(value) {}
    
    std::string getType() const override {
        return type;
    }
    
    std::string getValue() const {
        return value;
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};

// Leaf node for identifiers
class IdentifierNode : public ASTNode {
private:
    std::string name;
    BlockNode* block;
    int lineNumber;
    
public:
    IdentifierNode(const std::string& name, BlockNode* block, int lineNumber) 
        : name(name), block(block), lineNumber(lineNumber) {
        }
    
    std::string getType() const override;
    std::string getName() const { return name; }
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for unary operations
class UnaryOpNode : public ASTNode {
private:
    std::string op;
    std::unique_ptr<ASTNode> operand;
    int lineNumber;
    
public:
    UnaryOpNode(const std::string& op, std::unique_ptr<ASTNode> operand, int lineNumber) 
        : op(op), operand(std::move(operand)), lineNumber(lineNumber) {}
    
    std::string getType() const override {
        std::unique_ptr<TypeChecker> checker;
        
        if (op == "-") {
            checker = TypeCheckerFactory::createTypeChecker("arithmetic");
        } else if (op == "!") {
            checker = TypeCheckerFactory::createTypeChecker("boolean");
        } else {
            ErrorHandler::getInstance()->reportError("Unknown unary operator: " + op, lineNumber);
        }
        
        return checker->checkType(operand->getType(), lineNumber);
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for binary operations
class BinaryOpNode : public ASTNode {
private:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    int lineNumber;
    
public:
    BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left, 
                 std::unique_ptr<ASTNode> right, int lineNumber) 
        : op(op), left(std::move(left)), right(std::move(right)), lineNumber(lineNumber) {}
    
    std::string getType() const override {
        std::unique_ptr<TypeChecker> checker;
        
        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "^") {
            checker = TypeCheckerFactory::createTypeChecker("arithmetic");
        } else if (op == "&&" || op == "||" || op == "==" || op == "!=" || 
                   op == ">" || op == "<" || op == ">=" || op == "<=") {
            checker = TypeCheckerFactory::createTypeChecker("boolean");
        } else if (op == "|" || op == "&" || op == "<<" || op == ">>") {
            checker = TypeCheckerFactory::createTypeChecker("bitwise");
        } else {
            ErrorHandler::getInstance()->reportError("Unknown binary operator: " + op, lineNumber);
        }
        
        return checker->checkTypes(left->getType(), right->getType(), lineNumber);
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for declaration statements
class DeclarationNode : public ASTNode {
private:
    std::string type;
    std::string identifier;
    bool isConstant;
    std::unique_ptr<ASTNode> initializer;
    BlockNode* block;
    int lineNumber;
    
public:
    DeclarationNode(const std::string& type, const std::string& identifier, bool isConstant,
                    std::unique_ptr<ASTNode> initializer, BlockNode* block, int lineNumber) 
        : type(type), identifier(identifier), isConstant(isConstant), initializer(std::move(initializer)),
          block(block), lineNumber(lineNumber) {
            
          }
    
    std::string getType() const override {
        return type;
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for assignment statements
class AssignmentNode : public ASTNode {
private:
    std::string identifier;
    std::unique_ptr<ASTNode> expression;
    BlockNode* block;
    int lineNumber;    
public:
    AssignmentNode(const std::string& identifier, std::unique_ptr<ASTNode> expression,
                   BlockNode* block, int lineNumber) 
        : identifier(identifier), expression(std::move(expression)), 
          block(block), lineNumber(lineNumber) {

          }
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for print statements
class PrintNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression;
    
public:
    PrintNode(std::unique_ptr<ASTNode> expression) 
        : expression(std::move(expression)) {}
    
    std::string getType() const override {
        return "void";
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};


#include <string>

class Symbol {
private:
    std::string name;
    std::string type;
    std::string value; 
    bool isConst;
    bool isInitialized;

public:
    
    Symbol(const std::string& name, const std::string& type, bool isConst = false)
        : name(name), type(type), value(""), isConst(isConst), isInitialized(false) {
        }
    
    Symbol(const std::string& name, const std::string& type, const std::string& value, bool isConst = false)
        : name(name), type(type), value(value), isConst(isConst), isInitialized(!value.empty()) {}

    // Getters
    const std::string& getName() const { return name; }
    const std::string& getType() const { return type; }
    const std::string& getValue() const { return value; }
    bool isConstant() const { return isConst; }
    bool checkInitialization() const { return isInitialized; }

    void setValue(const std::string& newValue) {
        if (!isConst) {
            value = newValue;
            isInitialized = true;
        }
    }
    
    void setIsConst(bool constStatus) { isConst = constStatus; }
    void setInitialized () { this->isInitialized = true;}
    
    std::string toString() const {
        return "Symbol{name='" + name + 
               "', type='" + type + 
               "', value='" + value + 
               "', isConst=" + (isConst ? "true" : "false") + 
               ", isInitialized=" + (isInitialized ? "true" : "false") + "}";
    }
};

// Composite node for blocks
class BlockNode : public ASTNode {
private:
    int id;
    std::vector<std::unique_ptr<ASTNode>> statements;
    std::unordered_map<std::string, Symbol> symbolTable;
    BlockNode* parent;

public:
    // Constructors
    BlockNode(int id = 0, BlockNode* parent = nullptr) 
        : id(id), parent(parent) {}
    
    // Statement management
    void addStatement(std::unique_ptr<ASTNode> statement) {
        statements.push_back(std::move(statement));
    }
    
    const std::vector<std::unique_ptr<ASTNode>>& getStatements() const {
        return statements;
    }
    
    size_t statementCount() const {
        return statements.size();
    }
    
    bool isEmpty() const {
        return statements.empty();
    }
    
    // Symbol table management
    bool addSymbol(const Symbol& symbol) {
        if(symbolTable.find(symbol.getName()) != symbolTable.end())
            return false;
        auto result = symbolTable.emplace(symbol.getName(), symbol);
        return result.second; 
    }
    
    bool symbolExists(const std::string& name) const {
        return symbolTable.find(name) != symbolTable.end() || 
               (parent && parent->symbolExists(name));
    }
    
    Symbol* getSymbol(const std::string& name) {
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            return &it->second;
        }
        return parent ? parent->getSymbol(name) : nullptr;
    }
    
    const Symbol* getSymbol(const std::string& name) const {
        auto it = symbolTable.find(name);
        if (it != symbolTable.end()) {
            return &it->second;
        }
        return parent ? parent->getSymbol(name) : nullptr;
    }
    
    bool updateSymbolValue(const std::string& name, const std::string& value) {
        Symbol* symbol = getSymbol(name);
        if (symbol) {
            symbol->setValue(value);
            return true;
        }
        return false;
    }
    
    const std::unordered_map<std::string, Symbol>& getSymbolTable() const {
        return symbolTable;
    }
    
    // Block hierarchy management
    BlockNode* getParent() const {
        return parent;
    }
    
    void setParent(BlockNode* newParent) {
        parent = newParent;
    }
    
    int getId() const {
        return id;
    }
    
    std::string getType() const override {
        return "void";
    }
    
    void generateCode(QuadruplesGenerator& generator) override;
};

/********************************
 * Symbol class with Builder Pattern
 ********************************/

    /********************************
 * Visitor Pattern for Type Checking & Code Generation
 ********************************/
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(LiteralNode* node) = 0;
    virtual void visit(IdentifierNode* node) = 0;
    virtual void visit(UnaryOpNode* node) = 0;
    virtual void visit(BinaryOpNode* node) = 0;
    virtual void visit(DeclarationNode* node) = 0;
    virtual void visit(AssignmentNode* node) = 0;
    virtual void visit(PrintNode* node) = 0;
    virtual void visit(BlockNode* node) = 0;
};

/********************************
 * QuadruplesGenerator (Code Generator)
 ********************************/
class QuadruplesGenerator {
private:
    std::ofstream outFile;
    int tempVarCounter;
    std::vector<std::string> quadruples;
    
public:
    QuadruplesGenerator(const std::string& filename) : tempVarCounter(0) {
        outFile.open(filename);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open quadruples output file." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    ~QuadruplesGenerator() {
        if (outFile.is_open()) {
            // Write all quadruples to file
            for (size_t i = 0; i < quadruples.size(); ++i) {
                outFile << i << ": " << quadruples[i] << std::endl;
            }
            outFile.close();
        }
    }
    
    std::string generateTemp() {
        return "t" + std::to_string(tempVarCounter++);
    }
    
    void addQuadruple(const std::string& op, const std::string& arg1, 
                     const std::string& arg2, const std::string& result) {
        std::string quad = op + " " + arg1 + " " + arg2 + " " + result;
        quadruples.push_back(quad);
    }
    
    void pushInt(int value) {
        // Implementation for pushing integers
        addQuadruple("PUSH", std::to_string(value), "_", "_");
    }
    
    void pushFloat(float value) {
        // Implementation for pushing floats
        addQuadruple("PUSH", std::to_string(value), "_", "_");
    }
    
    void pushString(const std::string& value) {
        // Implementation for pushing strings
        addQuadruple("PUSH", "\"" + value + "\"", "_", "_");
    }
    
    void handleArithmeticOp(const std::string& op, const std::string& leftType, const std::string& rightType) {
        std::string resultVar = generateTemp();
        addQuadruple(op, "_", "_", resultVar);
        // Push result back on stack for further operations
        addQuadruple("PUSH", resultVar, "_", "_");
    }
    
    void handleAssignment(const std::string& identifier) {
        addQuadruple("POP", "_", "_", identifier);
    }
    
    void handlePrint() {
        addQuadruple("PRINT", "_", "_", "_");
    }
    
    void handleIdentifier(const std::string& identifier, const std::string& op = "PUSH") {
        addQuadruple(op, identifier, "_", "_");
    }
};

// Implementation of AST Node methods after QuadruplesGenerator is defined
void LiteralNode::generateCode(QuadruplesGenerator& generator) {
    if (type == "int") {
        generator.pushInt(std::stoi(value));
    } else if (type == "float") {
        generator.pushFloat(std::stof(value));
    } else if (type == "bool") {
        generator.pushInt(value == "true" ? 1 : 0);
    } else if (type == "string" || type == "char") {
        generator.pushString(value);
    }
}

std::string IdentifierNode::getType() const {
    return block->getSymbol(name)->getType();
}

void IdentifierNode::generateCode(QuadruplesGenerator& generator) {
    generator.handleIdentifier(name);
}

void UnaryOpNode::generateCode(QuadruplesGenerator& generator) {
    operand->generateCode(generator);
    
    if (op == "-") {
        generator.handleArithmeticOp("NEG", operand->getType(), "");
    } else if (op == "!") {
        generator.handleArithmeticOp("NOT", operand->getType(), "");
    }
}

void BinaryOpNode::generateCode(QuadruplesGenerator& generator) {
    // Generate code for left and right operands
    left->generateCode(generator);
    right->generateCode(generator);
    
    // Generate operation code based on operator type
    if (op == "+") {
        generator.handleArithmeticOp("ADD", left->getType(), right->getType());
    } else if (op == "-") {
        generator.handleArithmeticOp("SUB", left->getType(), right->getType());
    } else if (op == "*") {
        generator.handleArithmeticOp("MUL", left->getType(), right->getType());
    } else if (op == "/") {
        generator.handleArithmeticOp("DIV", left->getType(), right->getType());
    } else if (op == "%") {
        generator.handleArithmeticOp("MOD", left->getType(), right->getType());
    } else if (op == "^") {
        generator.handleArithmeticOp("POW", left->getType(), right->getType());
    } else if (op == "||") {
        generator.handleArithmeticOp("OR", left->getType(), right->getType());
    } else if (op == "&&") {
        generator.handleArithmeticOp("AND", left->getType(), right->getType());
    } else if (op == "==") {
        generator.handleArithmeticOp("EQ", left->getType(), right->getType());
    } else if (op == "!=") {
        generator.handleArithmeticOp("NEQ", left->getType(), right->getType());
    } else if (op == ">") {
        generator.handleArithmeticOp("GT", left->getType(), right->getType());
    } else if (op == "<") {
        generator.handleArithmeticOp("LT", left->getType(), right->getType());
    } else if (op == ">=") {
        generator.handleArithmeticOp("GTE", left->getType(), right->getType());
    } else if (op == "<=") {
        generator.handleArithmeticOp("LTE", left->getType(), right->getType());
    } else if (op == "|") {
        generator.handleArithmeticOp("BOR", left->getType(), right->getType());
    } else if (op == "&") {
        generator.handleArithmeticOp("BAND", left->getType(), right->getType());
    } else if (op == "<<") {
        generator.handleArithmeticOp("SHL", left->getType(), right->getType());
    } else if (op == ">>") {
        generator.handleArithmeticOp("SHR", left->getType(), right->getType());
    }
}

void DeclarationNode::generateCode(QuadruplesGenerator& generator) {
    // First declare the variable/constant in symbol table
    printf("in generate code declaration\n");
    Symbol newSymbol(identifier, type, isConstant);
    // Try to add the symbol to the current block
    bool result = block->addSymbol(newSymbol);
    if (!result) {
        // Handle error: symbol already exists in this scope
        ErrorHandler::getInstance()->reportError("Redeclaration of '" + identifier + "' in same scope", lineNumber);
        return;
    }

    // If there's an initializer, generate code for it
    if (initializer) {
        // Generate code for the initializer expression
        initializer->generateCode(generator);
        
        // Get the symbol we just added
        Symbol* symbol = block->getSymbol(identifier);

        // Handle the assignment
        generator.handleAssignment(identifier);
        
        // Mark the symbol as initialized
        symbol->setInitialized();
        
        // If this is a constant, we should also set its value
        // if (isConst) {
        //     // For constants, we can typically get the initializer's computed value
        //     std::string initValue = generator.getLastComputedValue();
        //     symbol->setValue(initValue);
        // }
    }
}

std::string AssignmentNode::getType() const {
    return block->getSymbol(identifier)->getType();
}

void AssignmentNode::generateCode(QuadruplesGenerator& generator) {
    // First look up the identifier to check it exists and get its type
    Symbol* symbol = block->getSymbol(identifier);
    
    // Check if it's a constant (can't reassign)
    if (symbol->isConstant()) {
        ErrorHandler::getInstance()->reportError("Cannot reassign constant " + identifier, lineNumber);
    }
    
    // Generate code for the expression
    expression->generateCode(generator);
    
    // Generate the assignment
    generator.handleAssignment(identifier);
    symbol->setInitialized();
}

void PrintNode::generateCode(QuadruplesGenerator& generator) {
    // Generate code for the expression to be printed
    expression->generateCode(generator);
    
    // Generate print instruction
    generator.handlePrint();
}

void BlockNode::generateCode(QuadruplesGenerator& generator) {
    
    // Generate code for all statements in the block
    for (auto& statement : statements) {
        statement->generateCode(generator);
    }
    
}




#endif