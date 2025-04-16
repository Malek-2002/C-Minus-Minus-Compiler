// error_handler.hpp
#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

class SyntaxErrorHandler {
private:
    std::vector<std::string> sourceLines;
    static SyntaxErrorHandler* instance;
    std::map<std::string, std::string> errorSuggestions;
    
    // Private constructor for singleton pattern
    SyntaxErrorHandler() {
        initializeErrorSuggestions();
    }
    
    void initializeErrorSuggestions();
    void analyzeCodeContext(int lineNo, int columnNo, const std::string& errorToken);

public:
    static SyntaxErrorHandler* getInstance();
    void loadSourceFile(const std::string& filename);
    void reportSyntaxError(const char* message, int lineNo, int columnNo);
    std::string getSuggestion(const std::string& errorMsg);
    void displayErrorLine(int lineNo, int columnNo);
};

#endif // ERROR_HANDLER_HPP