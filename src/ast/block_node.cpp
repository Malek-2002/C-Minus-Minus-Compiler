#include "ast/block_node.hpp"
#include "semantic/symbol_table.hpp"

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
