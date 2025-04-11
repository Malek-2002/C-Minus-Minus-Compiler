#include "symbol_table_generator.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Define static member variable
std::string SymbolTableGenerator::tableFilename = "symbol_table.txt";

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
    std::ifstream inFile(tableFilename);
    if (!inFile.is_open()) {
        return 0;
    }
    
    std::string line;
    int lastId = 0;
    
    // Skip header
    std::getline(inFile, line);
    
    // Read all lines to find the last ID
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        int id;
        if (iss >> id) {
            lastId = std::max(lastId, id);
        }
    }
    
    inFile.close();
    return lastId;
}

void SymbolTableGenerator::initializeFileIfNeeded() {
    // Check if file exists and is empty
    std::ifstream checkFile(tableFilename);
    bool fileEmpty = !checkFile.is_open() || checkFile.peek() == std::ifstream::traits_type::eof();
    checkFile.close();
    
    if (fileEmpty) {
        std::ofstream outFile(tableFilename);
        if (outFile.is_open()) {
            outFile << std::left 
                << std::setw(5) << "ID" << "\t\t"
                << std::setw(15) << "Name" << "\t\t"
                << std::setw(15) << "Type" << "\t\t"
                << std::setw(15) << "DataType" << "\t\t"
                << std::setw(5) << "Line" << "\t\t"
                << std::setw(15) << "Scope" << "\t\t"
                << std::setw(15) << "isInitialized" << "\t\t"
                << "Value" << std::endl;
            outFile.close();
        }
    }
}

void SymbolTableGenerator::setTableFilename(const std::string& filename) {
    tableFilename = filename;
    initializeFileIfNeeded();
}

bool SymbolTableGenerator::appendBlockSymbols(const std::unordered_map<std::string, Symbol>& symbolTable, 
                                            const std::unordered_map<std::string, FunctionSymbol>& functionTable,
                                            BlockNode* block) {
    // Make sure the file is initialized
    initializeFileIfNeeded();
    // Open the file in append mode
    std::ofstream outFile(tableFilename, std::ios::app);
    if (!outFile.is_open()) {
        return false;
    }
    
    // Get current ID (find the last used ID in the file)
    int currentId = getCurrentLastId();
    
    // Get the scope path for this block
    std::string scope = getScopePath(block);
    
    // Process symbols
    for (const auto& symbolPair : symbolTable) {
        const Symbol& symbol = symbolPair.second;
        
        outFile << std::left 
                << std::setw(5) << ++currentId << "\t\t"
                << std::setw(15) << symbol.getName() << "\t\t"
                << std::setw(15) << "variable" << "\t\t"
                << std::setw(15) << symbol.getType() << "\t\t"
                << std::setw(5) << symbol.getLineNumber() << "\t\t" // Line information if available
                << std::setw(15) << scope << "\t\t"
                << std::setw(15) << (symbol.checkInitialization() ? "true" : "false") << "\t\t"
                << symbol.getValue() << std::endl;
    }
    
    // Process functions
    for (const auto& functionPair : functionTable) {
        const FunctionSymbol& function = functionPair.second;
        
        // Add the function itself
        outFile << std::left 
                << std::setw(5) << ++currentId << "\t\t"
                << std::setw(15) << function.getName() << "\t\t"
                << std::setw(15) << "function" << "\t\t"
                << std::setw(15) << function.getReturnType() << "\t\t"
                << std::setw(5) << function.getLineNumber() << "\t\t"
                << std::setw(15) << scope << "\t\t"
                << std::setw(15) << (function.getIsDefined() ? "true" : "false") << "\t\t"
                << "" << std::endl;
        
        // Add function parameters
        const auto& params = function.getParameters();
        for (size_t i = 0; i < params.size(); i++) {
            outFile << std::left 
                    << std::setw(5) << ++currentId << "\t\t"
                    << std::setw(15) << params[i].second << "\t\t"
                    << std::setw(15) << "parameter" << "\t\t"
                    << std::setw(15) << params[i].first << "\t\t"
                    << std::setw(5) << function.getLineNumber() << "\t\t"
                    << std::setw(15) << scope + "." + function.getName() << "\t\t"
                    << std::setw(15) << "-" << "\t\t"
                    << "" << std::endl;
        }
    }
    
    outFile.close();
    return true;
}

bool SymbolTableGenerator::clearSymbolTable() {
    std::ofstream outFile(tableFilename, std::ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }
    
    outFile << std::left 
            << std::setw(5) << "ID" << "\t\t"
            << std::setw(15) << "Name" << "\t\t"
            << std::setw(15) << "Type" << "\t\t"
            << std::setw(15) << "DataType" << "\t\t"
            << std::setw(5) << "Line" << "\t\t"
            << std::setw(15) << "Scope" << "\t\t"
            << std::setw(15) << "isInitialized" << "\t\t"
            << "Value" << std::endl;
    
    outFile.close();
    return true;
}