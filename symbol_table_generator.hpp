#ifndef SYMBOL_TABLE_GENERATOR_HPP
#define SYMBOL_TABLE_GENERATOR_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "handler.hpp"

class SymbolTableGenerator {
private:
    static std::string tableFilename; // The single file where all symbols are stored
    
    // Helper method to determine the full scope path
    static std::string getScopePath(BlockNode* block);
    
    // Helper method to get the last used ID in the symbol table file
    static int getCurrentLastId();
    
    // Initialize the symbol table file with a header if it doesn't exist
    static void initializeFileIfNeeded();

public:
    // Set the filename for the symbol table
    static void setTableFilename(const std::string& filename);
    
    // Append symbols from a block to the symbol table file
    static bool appendBlockSymbols(const std::unordered_map<std::string, Symbol>& symbolTable, 
                                  const std::unordered_map<std::string, FunctionSymbol>& functionTable,
                                  BlockNode* block);
    
    // Clear the symbol table file (for resetting between compilations)
    static bool clearSymbolTable();
};

#endif // SYMBOL_TABLE_GENERATOR_HPP