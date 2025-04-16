#include "handler.hpp"
#include "symbol_table_generator.hpp"
// Initialize static member
ErrorHandler *ErrorHandler::instance = nullptr;

/********************************
 * ErrorHandler Implementation
 ********************************/
ErrorHandler::ErrorHandler()
{
    errorFile.open("./error_file.txt");
    if (!errorFile.is_open())
    {
        std::cerr << "Failed to open error file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

ErrorHandler *ErrorHandler::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ErrorHandler();
    }
    return instance;
}

void ErrorHandler::reportError(const std::string &message, int lineNumber)
{
    std::cerr << "Error at line " << lineNumber << ": " << message << std::endl;
    errorFile << "Error at line " << lineNumber << ": " << message << std::endl;
    exit(EXIT_FAILURE);
}

ErrorHandler::~ErrorHandler()
{
    errorFile.close();
    delete instance;
}

/********************************
 * ArithmeticTypeChecker Implementation
 ********************************/
std::string ArithmeticTypeChecker::checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // Check if types are compatible for arithmetic operations
    if (op1Type == "string" || op2Type == "string" ||
        op1Type == "char" || op2Type == "char" ||
        op1Type == "void" || op2Type == "void")
    {
        errorHandler->reportError("Invalid operator for given types", lineNumber);
    }

    // Return the resulting type (promote to float if one operand is float)
    if (op1Type == "float" || op2Type == "float")
    {
        return "float";
    }
    return op1Type;
}

std::string ArithmeticTypeChecker::checkType(const std::string &opType, int lineNumber)
{
    ErrorHandler *errorHandler = ErrorHandler::getInstance();

    // For unary operations like negation
    if (opType != "int" && opType != "float")
    {
        errorHandler->reportError("Invalid operator for given type", lineNumber);
    }
    return opType;
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
std::unique_ptr<TypeChecker> TypeCheckerFactory::createTypeChecker(const std::string &operatorType)
{
    if (operatorType == "arithmetic")
    {
        return std::make_unique<ArithmeticTypeChecker>();
    }
    else if (operatorType == "boolean")
    {
        return std::make_unique<BooleanTypeChecker>();
    }
    else if (operatorType == "bitwise")
    {
        return std::make_unique<BitwiseTypeChecker>();
    }
    throw std::invalid_argument("Unknown operator type: " + operatorType);
}

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
        generator.pushInt(value == "true" ? 1 : 0);
    }
    else if (type == "string" || type == "char")
    {
        generator.pushString(value);
    }
}

/********************************
 * IdentifierNode Implementation
 ********************************/
IdentifierNode::IdentifierNode(const std::string &name, BlockNode *block, int lineNumber)
    : name(name), block(block), lineNumber(lineNumber) {}

std::string IdentifierNode::getType() const
{
    if (!block->getSymbol(name))
    {
        ErrorHandler *errorHandler = ErrorHandler::getInstance();
        errorHandler->reportError("uninisialized valiable " + name, lineNumber);
    }
    return block->getSymbol(name)->getType();
}

std::string IdentifierNode::getName() const
{
    return name;
}

void IdentifierNode::generateCode(QuadruplesGenerator &generator)
{
    if (!block->getSymbol(name))
    {
        ErrorHandler *errorHandler = ErrorHandler::getInstance();
        errorHandler->reportError("uninisialized valiable " + name, lineNumber);
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
        checker = TypeCheckerFactory::createTypeChecker("arithmetic");
    }
    else if (op == "!")
    {
        checker = TypeCheckerFactory::createTypeChecker("boolean");
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

    if (op == "+" || op == "-" || op == "*" || op == "/"  || op == "^")
    {
        checker = TypeCheckerFactory::createTypeChecker("arithmetic");
    }
    else if (op == "&&" || op == "||" || op == "==" || op == "!=" ||
             op == ">" || op == "<" || op == ">=" || op == "<=")
    {
        checker = TypeCheckerFactory::createTypeChecker("boolean");
    }
    else if (op == "|" || op == "&" || op == "<<" || op == ">>" || op == "%")
    {
        checker = TypeCheckerFactory::createTypeChecker("bitwise");
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
        generator.handleArithmeticOp("POW", left->getType(), right->getType());
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
        generator.handleArithmeticOp("BAND", left->getType(), right->getType());
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

/********************************
 * Symbol Implementation
 ********************************/
Symbol::Symbol(const std::string &name, const std::string &type, bool isConst, int lineNumber)
    : name(name), type(type), value(""), isConst(isConst), isInitialized(false), lineNumber(lineNumber) {}

Symbol::Symbol(const std::string &name, const std::string &type, const std::string &value, bool isConst, int lineNumber)
    : name(name), type(type), value(value), isConst(isConst), isInitialized(!value.empty()), lineNumber(lineNumber) {}

const std::string &Symbol::getName() const
{
    return name;
}

const std::string &Symbol::getType() const
{
    return type;
}

const std::string &Symbol::getValue() const
{
    return value;
}

int Symbol::getLineNumber() const
{
    return lineNumber;
}

bool Symbol::isConstant() const
{
    return isConst;
}

bool Symbol::checkInitialization() const
{
    return isInitialized;
}

void Symbol::setValue(const std::string &newValue)
{
    value = newValue;
    isInitialized = true;
}

void Symbol::setIsConst(bool constStatus)
{
    isConst = constStatus;
}

void Symbol::setInitialized()
{
    isInitialized = true;
}

std::string Symbol::toString() const
{
    return "Symbol{name='" + name +
           "', type='" + type +
           "', value='" + value +
           "', isConst=" + (isConst ? "true" : "false") +
           ", isInitialized=" + (isInitialized ? "true" : "false") + "}";
}

FunctionSymbol::FunctionSymbol(const std::string &name, const std::string &returnType,
                               bool isDefined, int lineNumber)
    : name(name), returnType(returnType), isDefined(isDefined),
      hasReturnStatement(false), lineNumber(lineNumber) {}

// Getters
const std::string &FunctionSymbol::getName() const
{
    return name;
}

const std::string &FunctionSymbol::getReturnType() const
{
    return returnType;
}

const std::vector<std::pair<std::string, std::string>> &FunctionSymbol::getParameters() const
{
    return parameters;
}

bool FunctionSymbol::getIsDefined() const
{
    return isDefined;
}

int FunctionSymbol::getLineNumber() const
{
    return lineNumber;
}

bool FunctionSymbol::getHasReturnStatement() const
{
    return hasReturnStatement;
}

// Setters
void FunctionSymbol::setName(const std::string &newName)
{
    name = newName;
}

void FunctionSymbol::setReturnType(const std::string &type)
{
    returnType = type;
}

void FunctionSymbol::setIsDefined(bool defined)
{
    isDefined = defined;
}

void FunctionSymbol::setHasReturnStatement(bool hasReturn)
{
    hasReturnStatement = hasReturn;
}

// Parameter management
void FunctionSymbol::addParameter(const std::string &type, const std::string &name)
{
    parameters.emplace_back(type, name);
}

void FunctionSymbol::removeParameter(size_t index)
{
    if (index < parameters.size())
    {
        parameters.erase(parameters.begin() + index);
    }
}

void FunctionSymbol::clearParameters()
{
    parameters.clear();
}

// Utility methods
size_t FunctionSymbol::getParameterCount() const
{
    return parameters.size();
}

std::string FunctionSymbol::getParameterType(size_t index) const
{
    if (index < parameters.size())
    {
        return parameters[index].first;
    }
    return "";
}

std::string FunctionSymbol::getParameterName(size_t index) const
{
    if (index < parameters.size())
    {
        return parameters[index].second;
    }
    return "";
}

// Signature generation
std::string FunctionSymbol::getSignature() const
{
    std::string signature = returnType + " " + name + "(";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        if (i > 0)
            signature += ", ";
        signature += parameters[i].first; // Only include type in signature
    }
    signature += ")";
    return signature;
}

// String representation
std::string FunctionSymbol::toString() const
{
    std::string str = returnType + " " + name + "(";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        if (i > 0)
            str += ", ";
        str += parameters[i].first + " " + parameters[i].second;
    }
    str += ")";

    return str;
}

/********************************
 * BlockNode Implementation
 ********************************/
BlockNode::BlockNode(int id, BlockNode *parent)
    : id(id), parent(parent) {}

void BlockNode::addStatement(std::unique_ptr<ASTNode> statement)
{
    statements.push_back(std::move(statement));
}

const std::vector<std::unique_ptr<ASTNode>> &BlockNode::getStatements() const
{
    return statements;
}

size_t BlockNode::statementCount() const
{
    return statements.size();
}

bool BlockNode::isEmpty() const
{
    return statements.empty();
}

bool BlockNode::addSymbol(const Symbol &symbol)
{
    if (symbolTable.find(symbol.getName()) != symbolTable.end())
        return false;
    auto result = symbolTable.emplace(symbol.getName(), symbol);
    return result.second;
}

bool BlockNode::symbolExists(const std::string &name) const
{
    return symbolTable.find(name) != symbolTable.end() ||
           (parent && parent->symbolExists(name));
}

Symbol *BlockNode::getSymbol(const std::string &name)
{
    auto it = symbolTable.find(name);
    if (it != symbolTable.end())
    {
        return &it->second;
    }
    return parent ? parent->getSymbol(name) : nullptr;
}

const Symbol *BlockNode::getSymbol(const std::string &name) const
{
    auto it = symbolTable.find(name);
    if (it != symbolTable.end())
    {
        return &it->second;
    }
    return parent ? parent->getSymbol(name) : nullptr;
}

bool BlockNode::updateSymbolValue(const std::string &name, const std::string &value)
{
    Symbol *symbol = getSymbol(name);
    if (symbol)
    {
        symbol->setValue(value);
        return true;
    }
    return false;
}

const std::unordered_map<std::string, Symbol> &BlockNode::getSymbolTable() const
{
    return symbolTable;
}

BlockNode *BlockNode::getParent() const
{
    return parent;
}

void BlockNode::setParent(BlockNode *newParent)
{
    parent = newParent;
}

int BlockNode::getId() const
{
    return id;
}

std::string BlockNode::getType() const
{
    return "void";
}

void BlockNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate code for all statements in the block
    for (auto &statement : statements)
    {
        statement->generateCode(generator);
    }
    SymbolTableGenerator::appendBlockSymbols(symbolTable, functionTable, this);
}

bool BlockNode::addFunction(const FunctionSymbol &function)
{
    // Check if at global scope (only allow function declarations at global scope)
    if (parent != nullptr)
    {
        return false;
    }

    auto result = functionTable.emplace(function.getName(), function);
    return result.second;
}

FunctionSymbol *BlockNode::getFunction(const std::string &name)
{
    // Go to global scope to look for functions
    BlockNode *globalScope = this;
    while (globalScope->parent != nullptr)
    {
        globalScope = globalScope->parent;
    }

    auto it = globalScope->functionTable.find(name);
    if (it != globalScope->functionTable.end())
    {
        return &it->second;
    }
    return nullptr;
}

bool BlockNode::functionExists(const std::string &name) const
{
    // Go to global scope to look for functions
    const BlockNode *globalScope = this;
    while (globalScope->parent != nullptr)
    {
        globalScope = globalScope->parent;
    }

    return globalScope->functionTable.find(name) != globalScope->functionTable.end();
}

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
        if((symbol->getType() == "float" && initializer->getType() == "int") ||
            (symbol->getType() == "int" && initializer->getType() == "float")) {
        }
        else if (initializer->getType() != symbol->getType())
        {
            ErrorHandler::getInstance()->reportError("Type of '" + identifier + "' is not " + initializer->getType(), lineNumber);
        }
        initializer->generateCode(generator);
        // Attempt to cast to LiteralNode*
        LiteralNode* literalNode = dynamic_cast<LiteralNode*>(initializer.get());

        if (literalNode != nullptr) {
            symbol->setValue(literalNode->getValue());
        }
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
    // First look up the identifier to check it exists and get its type
    Symbol *symbol = block->getSymbol(identifier);

    if (symbol == nullptr)
    {
        ErrorHandler::getInstance()->reportError("Undeclared Variable'" + identifier + "' is used", lineNumber);
    }

    // Check if it's a constant (can't reassign)
    if (symbol->isConstant())
    {
        ErrorHandler::getInstance()->reportError("Cannot reassign constant " + identifier, lineNumber);
    }
    else if((symbol->getType() == "float" && expression->getType() == "int") ||
       (symbol->getType() == "int" && expression->getType() == "float")) {
    }
    else if (expression->getType() != symbol->getType())
    {
        ErrorHandler::getInstance()->reportError("Type of '" + identifier + "' is not " + expression->getType(), lineNumber);
    }

    // Generate code for the expression
    expression->generateCode(generator);

    // Generate the assignment
    generator.handleAssignment(identifier);
    symbol->setInitialized();
}

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

    // Generate code for condition
    condition->generateCode(generator);

    // Jump to else block if condition is false
    generator.addQuadruple("JUMPZ", "", "", elseLabel);

    // Generate code for then block
    thenBlock->generateCode(generator);

    // Jump to end after then block
    generator.addQuadruple("JUMP", "", "", endLabel);

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
                     std::string endLabel,
                     int lineNumber)
    : condition(std::move(condition)),
      body(std::move(body)),
      endLabel(endLabel),
      lineNumber(lineNumber) {}

std::string WhileNode::getType() const
{
    return "void";
}

void WhileNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate unique labels for this while loop
    static int whileCounter = 0;
    std::string startLabel = "while_" + std::to_string(whileCounter) + "_start";
    // std::string endLabel = "while_" + std::to_string(whileCounter) + "_end";
    whileCounter++;

    // Start label
    generator.addQuadruple("LABEL", "", "", startLabel);

    // Generate code for condition
    condition->generateCode(generator);

    // Jump to end if condition is false
    generator.addQuadruple("JUMPZ", "", "", endLabel);

    // Generate code for body
    body->generateCode(generator);

    // Jump back to start
    generator.addQuadruple("JUMP", "", "", startLabel);

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// DoWhileNode implementation
DoWhileNode::DoWhileNode(std::unique_ptr<BlockNode> body,
                         std::unique_ptr<ASTNode> condition,
                         std::string endLabel,
                         int lineNumber)
    : body(std::move(body)),
      condition(std::move(condition)),
      endLabel(endLabel),
      lineNumber(lineNumber) {}

std::string DoWhileNode::getType() const
{
    return "void";
}

void DoWhileNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate unique labels for this do-while loop
    static int doWhileCounter = 0;
    std::string startLabel = "do_while_" + std::to_string(doWhileCounter) + "_start";
    std::string condLabel = "do_while_" + std::to_string(doWhileCounter) + "_cond";
    doWhileCounter++;

    // Start label
    generator.addQuadruple("LABEL", "", "", startLabel);

    // Generate code for body
    body->generateCode(generator);

    // Condition label
    generator.addQuadruple("LABEL", "", "", condLabel);

    // Generate code for condition
    condition->generateCode(generator);

    // Jump back to start if condition is true (opposite of while loop)
    generator.addQuadruple("JUMPNZ", "", "", startLabel);

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

// ForNode implementation
ForNode::ForNode(std::unique_ptr<ASTNode> initialization,
                 std::unique_ptr<ASTNode> condition,
                 std::unique_ptr<ASTNode> update,
                 std::unique_ptr<BlockNode> body,
                 std::string endLabel,
                 int lineNumber)
    : initialization(std::move(initialization)),
      condition(std::move(condition)),
      update(std::move(update)),
      body(std::move(body)),
      endLabel(endLabel),
      lineNumber(lineNumber) {}

std::string ForNode::getType() const
{
    return "void";
}

void ForNode::generateCode(QuadruplesGenerator &generator)
{
    // Generate unique labels for this for loop
    static int forCounter = 0;
    std::string condLabel = "for_" + std::to_string(forCounter) + "_cond";
    std::string bodyLabel = "for_" + std::to_string(forCounter) + "_body";
    std::string updateLabel = "for_" + std::to_string(forCounter) + "_update";
    forCounter++;

    // Generate initialization code
    if (initialization)
    {
        initialization->generateCode(generator);
    }

    // Jump to condition evaluation
    generator.addQuadruple("JUMP", "", "", condLabel);

    // Body label
    generator.addQuadruple("LABEL", "", "", bodyLabel);

    // Generate code for loop body
    body->generateCode(generator);

    // Update label
    generator.addQuadruple("LABEL", "", "", updateLabel);

    // Generate code for update expression
    if (update)
    {
        update->generateCode(generator);
    }

    // Condition label
    generator.addQuadruple("LABEL", "", "", condLabel);

    // Generate code for condition
    condition->generateCode(generator);

    // Jump to body if condition is true
    generator.addQuadruple("JUMPNZ", "", "", bodyLabel);

    // End label
    generator.addQuadruple("LABEL", "", "", endLabel);
}

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

    // Generate function declaration label
    generator.addQuadruple("FUNC_LABEL", name, "", "");

    // Add parameters to the function's block scope
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        const auto &param = parameters[i];
        Symbol paramSymbol(param.second, param.first, false);
        paramSymbol.setInitialized(); // Parameters are always initialized
        body->addSymbol(paramSymbol);

        // Generate code to store parameter value
        generator.handleParameter(i);
    }

    // Generate code for function body
    body->generateCode(generator);

    // If no explicit return at end of function, add one
    if (returnType == "void")
    {
        generator.handleReturn(false);
    }

    // End of function
    generator.addQuadruple("END_FUNC", name, "", "");
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

    // Check argument count
    if (arguments.size() != function->getParameterCount())
    {
        ErrorHandler::getInstance()->reportError(
            "Function '" + name + "' called with wrong number of arguments (expected " +
                std::to_string(function->getParameterCount()) + ", got " +
                std::to_string(arguments.size()) + ")",
            lineNumber);
        return;
    }

    // Generate code for arguments in reverse order (stack convention)
    for (int i = arguments.size() - 1; i >= 0; --i)
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
            continue;
        }

        // Generate code for argument
        arguments[i]->generateCode(generator);
    }

    // Generate function call
    generator.handleFunctionCall(name, arguments.size());

    // Generate code to handle the return value if function is not void
    if (function->getReturnType() != "void")
    {
        std::string temp = generator.generateTemp();
        generator.addQuadruple("POP_RETURN", "", "", temp);
        generator.addQuadruple("PUSH", temp, "", "");
    }
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
    if (returnType != "void" && expression == nullptr)
    {
        ErrorHandler::getInstance()->reportError("Function declared to return '" + returnType +
                                                 "' but no return value provided", lineNumber);
        return;
    }
    if (returnType == "void" && expression)
    {
        ErrorHandler::getInstance()->reportError("Function declared to return 'void' but return value provided", lineNumber);
        return;
    }
    if (expression && expression->getType() != returnType)
    {
        ErrorHandler::getInstance()->reportError("Return type mismatch: expected '" + returnType +
                                                 "' but got '" + expression->getType() + "'", lineNumber);
        return;
    }
    // Generate code for return expression if it exists
    if (expression)
    {
        expression->generateCode(generator);
        generator.handleReturn(true);
    }
    else
    {
        generator.handleReturn(false);
    }
}

// BreakNode implementation
BreakNode::BreakNode(std::string endLabel, int lineNumber) : endLabel(endLabel), lineNumber(lineNumber) {}

std::string BreakNode::getType() const
{
    return "void";
}

void BreakNode::generateCode(QuadruplesGenerator &generator)
{
    generator.addQuadruple("JUMP", "", "", endLabel);
}

SwitchNode::SwitchNode(std::unique_ptr<ASTNode> expression,
                       std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> cases,
                       std::unique_ptr<BlockNode> defaultCase,
                       std::string endLabel,
                       int lineNumber)
    : expression(std::move(expression)), 
      cases(std::move(cases)), 
      defaultCase(std::move(defaultCase)),
      endLabel(endLabel),
      lineNumber(lineNumber) {}

std::string SwitchNode::getType() const {
    return "void";
}

void SwitchNode::generateCode(QuadruplesGenerator& generator) {
    
    if(expression->getType() != "int" && expression->getType() != "char") {
        ErrorHandler::getInstance()->reportError("Switch expression must be an integer or character", lineNumber);
    }
    // Generate a unique label for each case
    std::vector<std::string> caseLabels;
    for (size_t i = 0; i < cases.size(); i++) {
        caseLabels.push_back("case_" + std::to_string(i) + "_" + endLabel);
    }
    
    // Generate code to jump to the appropriate case
    for (size_t i = 0; i < cases.size(); i++) {
        // Evaluate the case expression
        expression->generateCode(generator);
        if(cases[i].first->getType() == "int" || cases[i].first->getType() == "char") {
            cases[i].first->generateCode(generator);
        } else {
            ErrorHandler::getInstance()->reportError("Switch case expression must be an integer or character", lineNumber);
            return;
        }
        // Compare with switch value
        generator.addQuadruple("EQ", "", "", "");
        
        // Jump to case if true
        generator.addQuadruple("JUMPZ", caseLabels[i], "", "");
    }
    
    // If no case matches, jump to default or end
    if (defaultCase) {
        generator.addQuadruple("JUMP", "", "", "default_" + endLabel);
    } else {
        generator.addQuadruple("JUMP", "", "", endLabel);
    }
    
    // Generate code for each case body
    for (size_t i = 0; i < cases.size(); i++) {
        generator.addQuadruple("LABEL", "", "", caseLabels[i]);
        cases[i].second->generateCode(generator);
        // Note: No automatic "break" at the end of cases - 
        // this allows case fallthrough unless explicitly broken
    }
    
    // Generate code for default case if it exists
    if (defaultCase) {
        generator.addQuadruple("LABEL", "", "", "default_" + endLabel);
        defaultCase->generateCode(generator);
    }
    
    // End of switch statement
    generator.addQuadruple("LABEL", "", "", endLabel);
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
    // Generate code for the expression to be printed
    expression->generateCode(generator);
    // Generate print instruction
    generator.handlePrint();
}

/********************************
 * QuadruplesGenerator Implementation
 ********************************/
QuadruplesGenerator::QuadruplesGenerator(const std::string &filename) : tempVarCounter(0)
{
    outFile.open(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open quadruples output file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

QuadruplesGenerator::~QuadruplesGenerator()
{
    if (outFile.is_open())
    {
        // Write all quadruples to file
        for (size_t i = 0; i < quadruples.size(); ++i)
        {
            outFile << i << ": " << quadruples[i] << std::endl;
        }
        outFile.close();
    }
}

std::string QuadruplesGenerator::generateTemp()
{
    return "t" + std::to_string(tempVarCounter++);
}

void QuadruplesGenerator::addQuadruple(const std::string &op, const std::string &arg1,
                                       const std::string &arg2, const std::string &result)
{
    std::string quad = op + " " + arg1 + " " + arg2 + " " + result;
    // std::cout << quad << std::endl;
    quadruples.push_back(quad);
}

void QuadruplesGenerator::pushInt(int value)
{
    // Implementation for pushing integers
    addQuadruple("PUSH", std::to_string(value), "", "");
}

void QuadruplesGenerator::pushFloat(float value)
{
    // Implementation for pushing floats
    addQuadruple("PUSH", std::to_string(value), "", "");
}

void QuadruplesGenerator::pushString(const std::string &value)
{
    // Implementation for pushing strings
    addQuadruple("PUSH", "\"" + value + "\"", "", "");
}

void QuadruplesGenerator::handleArithmeticOp(const std::string &op, const std::string &leftType, const std::string &rightType)
{
    addQuadruple(op, "", "", "");
}

void QuadruplesGenerator::handleAssignment(const std::string &identifier)
{
    addQuadruple("POP", "", "", identifier);
}

void QuadruplesGenerator::handlePrint()
{
    addQuadruple("PRINT", "", "", "");
}

void QuadruplesGenerator::handleIdentifier(const std::string &identifier, const std::string &op)
{
    addQuadruple(op, identifier, "", "");
}

void QuadruplesGenerator::handleFunctionDeclaration(const std::string &name)
{
    // Already handled in FunctionDeclarationNode::generateCode
}

void QuadruplesGenerator::handleFunctionCall(const std::string &name, int argCount)
{
    addQuadruple("CALL", name, std::to_string(argCount), "");
}

void QuadruplesGenerator::handleReturn(bool hasReturnValue)
{
    addQuadruple("ret", "", "", "");
    // if (hasReturnValue)
    // {
    //     addQuadruple("RETURN_VAL", "", "", "");
    // }
    // else
    // {
    //     addQuadruple("RETURN", "", "", "");
    // }
}

void QuadruplesGenerator::handleParameter(int paramIndex)
{
    std::string paramVar = "param" + std::to_string(paramIndex);
    addQuadruple("STORE_PARAM", std::to_string(paramIndex), "", paramVar);
}

void QuadruplesGenerator::handleArgument(int argIndex)
{
    // This would typically be handled directly in function call
}