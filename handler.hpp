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
#include <sstream>
#include <iomanip>
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
    ErrorHandler();
    
public:
    static ErrorHandler* getInstance();
    void reportError(const std::string& message, int lineNumber);
    void reportWarning(const std::string& message);
    ~ErrorHandler();
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
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override;
    std::string checkType(const std::string& opType, int lineNumber) override;
};

// Concrete strategy for boolean operations
class BooleanTypeChecker : public TypeChecker {
public:
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override;
    std::string checkType(const std::string& opType, int lineNumber) override;
};

// Concrete strategy for bitwise operations
class BitwiseTypeChecker : public TypeChecker {
public:
    std::string checkTypes(const std::string& op1Type, const std::string& op2Type, int lineNumber) override;
    std::string checkType(const std::string& opType, int lineNumber) override;
};

/********************************
 * Factory Method Pattern for Type Checker creation
 ********************************/
class TypeCheckerFactory {
public:
    static std::unique_ptr<TypeChecker> createTypeChecker(const std::string& operatorType);
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
    LiteralNode(const std::string& type, const std::string& value);
    std::string getType() const override;
    std::string getValue() const;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Leaf node for identifiers
class IdentifierNode : public ASTNode {
private:
    std::string name;
    BlockNode* block;
    int lineNumber;
    
public:
    IdentifierNode(const std::string& name, BlockNode* block, int lineNumber);
    std::string getType() const override;
    std::string getName() const;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for unary operations
class UnaryOpNode : public ASTNode {
private:
    std::string op;
    std::unique_ptr<ASTNode> operand;
    int lineNumber;
    
public:
    UnaryOpNode(const std::string& op, std::unique_ptr<ASTNode> operand, int lineNumber);
    std::string getType() const override;
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
                 std::unique_ptr<ASTNode> right, int lineNumber);
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Symbol class definition
class Symbol {
private:
    std::string name;
    std::string type;
    std::string value; 
    int lineNumber;
    bool isConst;
    bool isInitialized;

public:
    Symbol(const std::string& name, const std::string& type, bool isConst = false, int lineNumber = 0);
    Symbol(const std::string& name, const std::string& type, const std::string& value, bool isConst = false, int lineNumber = 0);

    // Getters
    const std::string& getName() const;
    const std::string& getType() const;
    const std::string& getValue() const;
    bool isConstant() const;
    bool checkInitialization() const;
    int getLineNumber() const;
    void setValue(const std::string& newValue);
    void setIsConst(bool constStatus);
    void setInitialized();
    std::string toString() const;
};

class FunctionSymbol {
    private:
        std::string name;
        std::string returnType;
        std::vector<std::pair<std::string, std::string>> parameters; // <type, name>
        bool isDefined;
        bool hasReturnStatement;
        int lineNumber;
    public:
        // Constructor
        FunctionSymbol(const std::string& name, const std::string& returnType, 
                      bool isDefined = false, int lineNumber = 0);
    
        // Getters
        const std::string& getName() const;
        const std::string& getReturnType() const;
        const std::vector<std::pair<std::string, std::string>>& getParameters() const;
        bool getIsDefined() const;
        bool getHasReturnStatement() const;
    
        // Setters
        void setName(const std::string& newName);
        void setReturnType(const std::string& type);
        void setIsDefined(bool defined);
        void setHasReturnStatement(bool hasReturn);
    
        // Parameter management
        void addParameter(const std::string& type, const std::string& name);
        void removeParameter(size_t index);
        void clearParameters();
    
        // Utility methods
        size_t getParameterCount() const;
        std::string getParameterType(size_t index) const;
        std::string getParameterName(size_t index) const;
        int getLineNumber() const;
        // Signature generation
        std::string getSignature() const;
    
        // String representation
        std::string toString() const;
    };

// Composite node for blocks
class BlockNode : public ASTNode {
private:
    int id;
    std::vector<std::unique_ptr<ASTNode>> statements;
    std::unordered_map<std::string, Symbol> symbolTable;
    std::unordered_map<std::string, FunctionSymbol> functionTable;
    BlockNode* parent;

public:
    // Constructors
    BlockNode(int id = 0, BlockNode* parent = nullptr);
    
    // Statement management
    void addStatement(std::unique_ptr<ASTNode> statement);
    const std::vector<std::unique_ptr<ASTNode>>& getStatements() const;
    size_t statementCount() const;
    bool isEmpty() const;
    
    // Symbol table management
    bool addSymbol(const Symbol& symbol);
    bool symbolExists(const std::string& name) const;
    Symbol* getSymbol(const std::string& name);
    const Symbol* getSymbol(const std::string& name) const;
    bool updateSymbolValue(const std::string& name, const std::string& value);
    const std::unordered_map<std::string, Symbol>& getSymbolTable() const;
    bool addFunction(const FunctionSymbol& function);
    FunctionSymbol* getFunction(const std::string& name);
    bool functionExists(const std::string& name) const;
    // Block hierarchy management
    BlockNode* getParent() const;
    void setParent(BlockNode* newParent);
    int getId() const;
    
    std::string getType() const override;
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
    DeclarationNode(const std::string type, const std::string identifier, bool isConstant,
                    std::unique_ptr<ASTNode> initializer, BlockNode* block, int lineNumber);
    
    std::string getType() const override;
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
                   BlockNode* block, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for print statements
class PrintNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression;
    
public:
    PrintNode(std::unique_ptr<ASTNode> expression);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

class IfNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<BlockNode> thenBlock;
    std::unique_ptr<ASTNode> elseStatement; // Can be another IfNode for else-if or a BlockNode for else
    int lineNumber;
    
public:
    IfNode(std::unique_ptr<ASTNode> condition, 
           std::unique_ptr<BlockNode> thenBlock,
           std::unique_ptr<ASTNode> elseStatement, 
           int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for while statements
class WhileNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<BlockNode> body;
    std::string endLabel;
    int lineNumber;
    
public:
    WhileNode(std::unique_ptr<ASTNode> condition, 
              std::unique_ptr<BlockNode> body,
              std::string endLabel,
              int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for do-while statements
class DoWhileNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<BlockNode> body;
    std::string endLabel;
    int lineNumber;
    
public:
    DoWhileNode(std::unique_ptr<BlockNode> body,
                std::unique_ptr<ASTNode> condition,
                std::string endLabel,
                int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Composite node for for statements
class ForNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> initialization;
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> update;
    std::unique_ptr<BlockNode> body;
    std::string endLabel;
    int lineNumber;
    
public:
    ForNode(std::unique_ptr<ASTNode> initialization,
            std::unique_ptr<ASTNode> condition,
            std::unique_ptr<ASTNode> update,
            std::unique_ptr<BlockNode> body,
            std::string endLabel,
            int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Function declaration node
class FunctionDeclarationNode : public ASTNode {
private:
    std::string returnType;
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters; // <type, name>
    std::unique_ptr<BlockNode> body;
    BlockNode* parentBlock;
    int lineNumber;
    
public:
    FunctionDeclarationNode(const std::string& returnType, const std::string& name,
                          std::vector<std::pair<std::string, std::string>> parameters,
                          std::unique_ptr<BlockNode> body, BlockNode* parentBlock, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Function call node
class FunctionCallNode : public ASTNode {
private:
    std::string name;
    std::vector<std::unique_ptr<ASTNode>> arguments;
    BlockNode* block;
    int lineNumber;
    
public:
    FunctionCallNode(const std::string& name, std::vector<std::unique_ptr<ASTNode>> arguments,
                    BlockNode* block, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Return statement nodek
class ReturnNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression; // Optional (can be nullptr for void functions)
    BlockNode* block;
    std::string returnType;
    int lineNumber;
    
public:
    ReturnNode(std::unique_ptr<ASTNode> expression, BlockNode* block, std::string returnType, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

// Node for break statements
class BreakNode : public ASTNode {
private:
    std::string endLabel;
    int lineNumber;
    
public:
    BreakNode(std::string endLabel, int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};
    
class SwitchNode : public ASTNode {
private:
    std::unique_ptr<ASTNode> expression;
    std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases;
    std::unique_ptr<BlockNode> defaultCase;
    std::string endLabel;
    int lineNumber;
    
public:
    SwitchNode(std::unique_ptr<ASTNode> expression,
               std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases,
               std::unique_ptr<BlockNode> defaultCase,
               std::string endLabel,
               int lineNumber);
    
    std::string getType() const override;
    void generateCode(QuadruplesGenerator& generator) override;
};

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
    QuadruplesGenerator(const std::string& filename);
    ~QuadruplesGenerator();
    
    std::string generateTemp();
    void addQuadruple(const std::string& op, const std::string& arg1, 
                     const std::string& arg2, const std::string& result);
    void pushInt(int value);
    void pushFloat(float value);
    void pushString(const std::string& value);
    void handleArithmeticOp(const std::string& op, const std::string& leftType, const std::string& rightType);
    void handleAssignment(const std::string& identifier);
    void handlePrint();
    void handleIdentifier(const std::string& identifier, const std::string& op = "PUSH");
    void handleFunctionDeclaration(const std::string& name);
    void handleFunctionCall(const std::string& name, int argCount);
    void handleReturn(bool hasReturnValue);
    void handleParameter(int paramIndex);
    void handleArgument(int argIndex);
};

#endif