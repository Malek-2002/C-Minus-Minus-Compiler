#ifndef SYMBOL_TABLE_GENERATOR_HPP
#define SYMBOL_TABLE_GENERATOR_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "ast/block_node.hpp"
// Define a struct to hold symbol table entries
struct SymbolEntry {
    int id;                  // Symbol ID
    std::string name;        // Symbol name
    std::string type;        // "variable" or "function"
    std::string dataType;    // Data type of the symbol
    int lineNumber;          // Line number where symbol is declared
    std::string scope;       // Symbol scope path
    bool isInitialized;      // Whether symbol is initialized
    bool isUsed;             // Whether symbol is used
    std::string value;       // Value (if applicable)
};

class SymbolTableGenerator {
private:
    static std::string tableFilename; // The file where all symbols will be stored
    static std::vector<SymbolEntry> tableEntries; // Vector to store symbol entries
    static bool headerAdded; // Flag to track if header has been added
    
    // Helper method to determine the full scope path
    static std::string getScopePath(BlockNode* block);
    
    // Helper method to get the last used ID in the symbol table entries
    static int getCurrentLastId();
    
    // Add header to the entries vector if needed
    static void initializeEntriesIfNeeded();

public:
    // Set the filename for the symbol table
    static void setTableFilename(const std::string& filename);
    
    // Append symbols from a block to the symbol entries vector
    static bool appendBlockSymbols(const std::unordered_map<std::string, Symbol>& symbolTable, 
                                  const std::unordered_map<std::string, FunctionSymbol>& functionTable,
                                  BlockNode* block);
    
    // Write the stored entries to the symbol table file
    static bool writeToFile();
    
    // Clear the symbol table entries (for resetting between compilations)
    static bool clearSymbolTable();
    
    // Get the current entries (for testing/debugging)
    static const std::vector<SymbolEntry>& getEntries();
};

#endif // SYMBOL_TABLE_GENERATOR_HPP