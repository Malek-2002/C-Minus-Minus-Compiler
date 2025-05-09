#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "semantic/symbol_table.hpp"
#include "error/error_handler.hpp"

// Define static member variables
std::string SymbolTableGenerator::tableFilename = "logs/output_symbol_table.csv";
std::vector<SymbolEntry> SymbolTableGenerator::tableEntries;
bool SymbolTableGenerator::headerAdded = false;

std::string SymbolTableGenerator::getScopePath(BlockNode* block) {
    if (block == nullptr) {
        return "global";
    }
    
    BlockNode* current = block;
    std::string scope = "";
    
    while (current != nullptr) {
        scope = "blk" + std::to_string(current->getId()) + (scope.empty() ? "" : "." + scope);
        current = current->getParent();
    }
    
    return scope;
}

int SymbolTableGenerator::getCurrentLastId() {
    if (tableEntries.empty()) {
        return 0;
    }
    
    int lastId = 0;
    
    for (const auto& entry : tableEntries) {
        lastId = std::max(lastId, entry.id);
    }
    
    return lastId;
}

void SymbolTableGenerator::initializeEntriesIfNeeded() {
    // No header entry needed with the new SymbolEntry struct approach
    headerAdded = true;
}

void SymbolTableGenerator::setTableFilename(const std::string& filename) {
    tableFilename = filename;
}

// Helper function to escape CSV values
std::string escapeCSV(const std::string& value) {
    // If the value contains comma, quote, or newline, wrap it in quotes and escape quotes
    bool needsQuotes = value.find(',') != std::string::npos || 
                      value.find('"') != std::string::npos || 
                      value.find('\n') != std::string::npos;
    
    if (!needsQuotes)
        return value;
    
    std::string escaped = "\"";
    for (char c : value) {
        if (c == '"')
            escaped += "\"\""; // Double quotes to escape quotes
        else
            escaped += c;
    }
    escaped += "\"";
    
    return escaped;
}

bool SymbolTableGenerator::appendBlockSymbols(const std::unordered_map<std::string, Symbol>& symbolTable, 
                                          const std::unordered_map<std::string, FunctionSymbol>& functionTable,
                                          BlockNode* block) {
    // Make sure entries are initialized
    initializeEntriesIfNeeded();
    
    // Get current ID
    int currentId = getCurrentLastId();
    
    // Get the scope path for this block
    std::string scope = getScopePath(block);
    
    // Process symbols
    for (const auto& symbolPair : symbolTable) {
        const Symbol& symbol = symbolPair.second;
        
        SymbolEntry entry;
        entry.id = ++currentId;
        entry.name = symbol.getName();
        entry.type = symbol.getIdentifierType();
        entry.dataType = symbol.getType();
        entry.lineNumber = symbol.getLineNumber();
        entry.scope = scope;
        entry.isInitialized = symbol.checkInitialization();
        entry.isUsed = symbol.getIsUsed();
        entry.value = symbol.getValue();
        
        tableEntries.push_back(entry);

        if(!symbol.getIsUsed()) {
            ErrorHandler::getInstance()->reportWarning("Variable " + symbol.getName() + " in scope " + scope +" is declared but never used", symbol.getLineNumber());
        }
    }
    
    // Process functions
    for (const auto& functionPair : functionTable) {
        const FunctionSymbol& function = functionPair.second;
        
        SymbolEntry entry;
        entry.id = ++currentId;
        entry.name = function.getName();
        entry.type = "function";
        entry.dataType = function.getReturnType();
        entry.lineNumber = function.getLineNumber();
        entry.scope = scope;
        entry.isInitialized = function.getIsDefined();
        entry.isUsed = function.getIsUsed();
        entry.value = "";
        
        tableEntries.push_back(entry);

        if(!function.getIsUsed()) {
            ErrorHandler::getInstance()->reportWarning("Function " + function.getName() + "  is declared but never used", function.getLineNumber());
        }
    }
    
    return true;
}

bool SymbolTableGenerator::writeToFile() {
    std::ofstream outFile(tableFilename);
    if (!outFile.is_open()) {
        return false;
    }
    
    // Write header
    outFile << "ID,Name,Type,DataType,Line,Scope,isInitialized,isUsed,Value" << std::endl;
    
    // Sort entries by line number before writing
    std::sort(tableEntries.begin(), tableEntries.end(), 
              [](const SymbolEntry& a, const SymbolEntry& b) {
                  return a.lineNumber < b.lineNumber;
              });
    
    // Write entries
    for (const auto& entry : tableEntries) {
        outFile << entry.id << ","
                << escapeCSV(entry.name) << ","
                << entry.type << ","
                << escapeCSV(entry.dataType) << ","
                << entry.lineNumber << ","
                << escapeCSV(entry.scope) << ","
                << (entry.isInitialized ? "true" : "false") << ","
                << (entry.isUsed ? "true" : "false") << ","
                << escapeCSV(entry.value) << std::endl;
    }
    
    outFile.close();
    return true;
}

bool SymbolTableGenerator::clearSymbolTable() {
    std::ofstream outFile(tableFilename);
    if (outFile.is_open()) {
        outFile.close();
    }
    tableEntries.clear();
    headerAdded = false;
    initializeEntriesIfNeeded();
    return true;
}

const std::vector<SymbolEntry>& SymbolTableGenerator::getEntries() {
    return tableEntries;
}