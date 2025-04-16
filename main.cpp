#include <iostream>
#include <fstream>
#include <string>
#include "handler.hpp"
#include "parser.tab.hpp"
#include "symbol_table_generator.hpp"
#include "error_handler.hpp"

extern int yyparse();
extern FILE* yyin;  // File pointer used by flex for input
extern int yylineno;
extern char* yytext; // Current token text from lexer
extern int yyleng;   // Length of current token

// Track column position
int current_column = 1;
int token_start_column = 1;

// Function called by flex for each token - keep track of column position
void update_column() {
    token_start_column = current_column;
    current_column += yyleng;
}

// Reset column counter for new lines
void reset_column() {
    current_column = 1;
    token_start_column = 1;
}

void yyerror(const char* s) {
    // Use our enhanced error handler
    SyntaxErrorHandler::getInstance()->reportSyntaxError(s, yylineno, token_start_column);
}

BlockNode* currBlock = new BlockNode(0, nullptr);  // Root block with ID 0
QuadruplesGenerator generator("output.txt");

int main(int argc, char* argv[]) {
    SymbolTableGenerator::setTableFilename("output_symbol_table.txt");
    SymbolTableGenerator::clearSymbolTable();
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Open input file
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }
    
    // Initialize error handler with source file
    SyntaxErrorHandler::getInstance()->loadSourceFile(argv[1]);

    // Set flex to read from file
    yyin = input_file;
    yylineno = 1;  // Reset line counter
    reset_column(); // Reset column counter

    // Parse the input
    int parse_result = yyparse();

    // Clean up
    fclose(input_file);

    if (parse_result != 0) {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }

    currBlock->generateCode(generator);

    delete currBlock;

    return 0;
}