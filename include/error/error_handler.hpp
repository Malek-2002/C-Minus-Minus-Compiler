// error_handler.hpp
#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

class ErrorHandler {
private:
    static ErrorHandler* instance;
    std::ofstream errorFile;
    std::vector<std::string> sourceLines;
    std::map<std::string, std::string> errorSuggestions;
    bool errorsFound = false;
    // Private constructor for singleton pattern
    ErrorHandler();
    
    void initializeErrorSuggestions();
    std::string analyzeCodeContext(int lineNo, int columnNo, const std::string& errorToken);
    std::string getErrorLineDisplay(int lineNo, int columnNo);
    std::string extractErrorToken(const std::string& errorMsg);

public:
    static ErrorHandler* getInstance();
    void loadSourceFile(const std::string& filename);
    
    // General error reporting
    void reportError(const std::string& message, int lineNumber);
    void reportWarning(const std::string& message, int lineNumber);
    
    // Syntax error specific reporting
    void reportSyntaxError(const char* message, int lineNo, int columnNo);
    
    bool hasErrors() const {
        return errorsFound;
    }
    void setErrorsFound() {
        errorsFound = true;
    }
    ~ErrorHandler();
};

#endif // ERROR_HANDLER_HPP