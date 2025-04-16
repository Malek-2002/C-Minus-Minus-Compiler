// error_handler.cpp
#include "error_handler.hpp"
#include <algorithm>
#include <regex>

SyntaxErrorHandler* SyntaxErrorHandler::instance = nullptr;

SyntaxErrorHandler* SyntaxErrorHandler::getInstance() {
    if (instance == nullptr) {
        instance = new SyntaxErrorHandler();
    }
    return instance;
}

void SyntaxErrorHandler::loadSourceFile(const std::string& filename) {
    sourceLines.clear();
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            sourceLines.push_back(line);
        }
        file.close();
    }
}

void SyntaxErrorHandler::initializeErrorSuggestions() {
    // Common syntax errors and their suggestions
    errorSuggestions["syntax error, unexpected"] = "Check for missing operators, parentheses, or semicolons";
    errorSuggestions["syntax error, unexpected '}'"] = "Mismatched braces or missing statements";
    errorSuggestions["syntax error, unexpected IDENTIFIER"] = "Check for missing operators or semicolons before this identifier";
    errorSuggestions["syntax error, unexpected SEMICOLON"] = "Unexpected semicolon or empty statement";
    errorSuggestions["syntax error, unexpected IF"] = "Make sure previous statement is properly terminated";
    errorSuggestions["syntax error, unexpected ELSE"] = "Make sure 'else' follows an 'if' statement directly";
    errorSuggestions["syntax error, unexpected '('"] = "Check for missing operator or function name";
    errorSuggestions["syntax error, unexpected ')'"] = "Mismatched parentheses or missing expression";
    errorSuggestions["syntax error, unexpected EQ"] = "Assignment requires a valid left-hand side";
    errorSuggestions["syntax error, unexpected TYPE"] = "Type declarations must be followed by an identifier";
    
    // More specific error patterns
    errorSuggestions["syntax error, unexpected SEMICOLON, expecting ')'"] = 
        "Remove the semicolon inside the parentheses. Example: if (x > 0) instead of if (x > 0;)";
    
    errorSuggestions["syntax error, unexpected ELSE"] = 
        "Make sure your 'else' follows an 'if' block without semicolons in between";
    
    errorSuggestions["syntax error, unexpected ')', expecting IDENTIFIER"] = 
        "Function parameters need identifiers. Example: int foo(int x) instead of int foo(int)";
    
    errorSuggestions["syntax error, unexpected ADD"] = 
        "Check operator precedence or add parentheses to clarify expression grouping";
    
    errorSuggestions["syntax error, unexpected EQ, expecting SEMICOLON"] = 
        "Did you mean '==' for comparison instead of '=' for assignment?";
    
    errorSuggestions["syntax error, unexpected STRING_VALUE"] = 
        "String literals must be properly terminated and used in a valid expression";
    
    errorSuggestions["syntax error, unexpected '{'"] = 
        "Opening braces must follow function declarations or control structures";
    
    errorSuggestions["syntax error, unexpected RETURN"] = 
        "Return statements must be inside functions and followed by an expression (if not void)";
    
    errorSuggestions["syntax error, unexpected INT_VALUE, expecting IDENTIFIER"] = 
        "Variable names cannot start with numbers. Use a letter or underscore";
}

std::string SyntaxErrorHandler::getSuggestion(const std::string& errorMsg) {
    for (const auto& pair : errorSuggestions) {
        if (errorMsg.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }
    return "Check syntax around this location";
}

void SyntaxErrorHandler::displayErrorLine(int lineNo, int columnNo) {
    if (lineNo <= 0 || lineNo > static_cast<int>(sourceLines.size())) {
        return;
    }
    
    // Convert to 0-based index
    int idx = lineNo - 1;
    std::string line = sourceLines[idx];
    
    // Ensure columnNo is within valid range
    columnNo = std::max(0, std::min(columnNo, static_cast<int>(line.length())));
    
    std::cout << lineNo << " | " << line << std::endl;
    std::cout << "  | ";
    
    // Print spaces up to the error position
    for (int i = 0; i < columnNo; i++) {
        std::cout << " ";
    }
    
    // Print error indicator
    std::cout << "^" << std::endl;
}

void SyntaxErrorHandler::analyzeCodeContext(int lineNo, int columnNo, const std::string& errorToken) {
    if (lineNo <= 0 || lineNo > static_cast<int>(sourceLines.size())) {
        return;
    }
    
    // Get the problematic line
    std::string line = sourceLines[lineNo - 1];
    
    // Check for common patterns
    if (errorToken == "if" && line.find("if(") != std::string::npos) {
        std::cout << "\033[1;33mTip:\033[0m Add a space after 'if': if (condition)" << std::endl;
    }
    
    if (line.find("==") != std::string::npos && line.find("=") != std::string::npos) {
        std::cout << "\033[1;33mTip:\033[0m Be careful with '=' (assignment) vs '==' (comparison)" << std::endl;
    }
    
    if (line.find(";") == std::string::npos) {
        std::cout << "\033[1;33mTip:\033[0m Missing semicolon at end of statement?" << std::endl;
    }
    
    if (line.find("{") != std::string::npos && lineNo < static_cast<int>(sourceLines.size())) {
        // Check indentation of next line
        std::string nextLine = sourceLines[lineNo];
        if (nextLine.find_first_not_of(" \t") == 0) {
            std::cout << "\033[1;33mTip:\033[0m Consider indenting statements inside blocks" << std::endl;
        }
    }
    
    // Check for missing brackets
    int openBrackets = 0;
    for (char c : line) {
        if (c == '{') openBrackets++;
        if (c == '}') openBrackets--;
    }
    
    if (openBrackets > 0) {
        std::cout << "\033[1;33mTip:\033[0m Missing closing brace '}'" << std::endl;
    } else if (openBrackets < 0) {
        std::cout << "\033[1;33mTip:\033[0m Unexpected closing brace '}'" << std::endl;
    }
}

void SyntaxErrorHandler::reportSyntaxError(const char* message, int lineNo, int columnNo) {
    std::cerr << "\033[1;31mSyntax error\033[0m at line " << lineNo << ": " << message << std::endl;
    
    // Display the line with error
    displayErrorLine(lineNo, columnNo);
    
    // Extract error token from message if possible
    std::string errorMsg(message);
    std::string errorToken = "";
    std::regex tokenRegex("unexpected ([^,]+)");
    std::smatch match;
    if (std::regex_search(errorMsg, match, tokenRegex) && match.size() > 1) {
        errorToken = match[1];
        errorToken.erase(std::remove(errorToken.begin(), errorToken.end(), '\''), errorToken.end());
    }
    
    // Provide suggestion
    std::string suggestion = getSuggestion(message);
    std::cerr << "\033[1;33mSuggestion:\033[0m " << suggestion << std::endl;
    
    // Analyze code context for additional tips
    analyzeCodeContext(lineNo, columnNo, errorToken);
}