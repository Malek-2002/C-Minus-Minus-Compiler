// error_handler.cpp
#include "error/error_handler.hpp"
#include <algorithm>
#include <fstream>

ErrorHandler* ErrorHandler::instance = nullptr;


ErrorHandler::ErrorHandler()
{
    errorFile.open("logs/error_file.txt");
    if (!errorFile.is_open())
    {
        std::cerr << "Failed to open error file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

ErrorHandler* ErrorHandler::getInstance() {
    if (instance == nullptr) {
        instance = new ErrorHandler();
    }
    return instance;
}

void ErrorHandler::loadSourceFile(const std::string& filename) {
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

std::string ErrorHandler::getErrorLineDisplay(int lineNo, int columnNo) {
    if (lineNo <= 0 || lineNo > static_cast<int>(sourceLines.size())) {
        return "";
    }
    
    // Convert to 0-based index
    int idx = lineNo - 1;
    std::string line = sourceLines[idx];
    
    // Ensure columnNo is within valid range
    columnNo = std::max(0, std::min(columnNo, static_cast<int>(line.length())));
    
    std::string result = std::to_string(lineNo) + " | " + line + "\n";
    result += "  | ";
    
    // Add spaces up to the error position
    for (int i = 0; i < columnNo; i++) {
        result += " ";
    }
    
    // Add error indicator
    result += "^\n";
    
    return result;
}

std::string ErrorHandler::extractErrorToken(const std::string& errorMsg) {
    std::string token = "";
    size_t unexpectedPos = errorMsg.find("unexpected");
    
    if (unexpectedPos != std::string::npos) {
        size_t startPos = unexpectedPos + 10; // Length of "unexpected"
        
        // Skip spaces
        while (startPos < errorMsg.length() && errorMsg[startPos] == ' ') {
            startPos++;
        }
        
        // Check if token is quoted
        bool isQuoted = false;
        if (startPos < errorMsg.length() && errorMsg[startPos] == '\'') {
            isQuoted = true;
            startPos++;
        }
        
        size_t endPos;
        if (isQuoted) {
            endPos = errorMsg.find('\'', startPos);
            if (endPos == std::string::npos) {
                endPos = errorMsg.length();
            }
        } else {
            endPos = errorMsg.find(',', startPos);
            if (endPos == std::string::npos) {
                endPos = errorMsg.length();
            }
        }
        
        token = errorMsg.substr(startPos, endPos - startPos);
    }
    
    return token;
}

void ErrorHandler::reportError(const std::string& message, int lineNumber) {
    errorFile << "Error at line " << lineNumber << ": " << message << std::endl;
    setErrorsFound();
    // exit(EXIT_FAILURE);
}

void ErrorHandler::reportWarning(const std::string& message, int lineNumber) {
    errorFile << "Warning at line " << lineNumber << ": " << message << std::endl;
}

void ErrorHandler::reportSyntaxError(const char* message, int lineNo, int columnNo) {
    std::string errorMsg(message);
    
    std::cerr << "Syntax error at line " << lineNo << ": " << message << std::endl;
    errorFile << "Syntax error at line " << lineNo << ": " << message << std::endl;
    
    // Display the line with error
    std::string lineDisplay = getErrorLineDisplay(lineNo, columnNo);
    std::cerr << lineDisplay;
    errorFile << lineDisplay;
    
    // Extract error token from message
    std::string errorToken = extractErrorToken(errorMsg);
        
    setErrorsFound();

    std::cerr << std::endl; // Add a blank line for readability
    errorFile << std::endl; // Add a blank line for readability
}

ErrorHandler::~ErrorHandler() {
    if (errorFile.is_open()) {
        errorFile.close();
    }
    // Note: We don't delete instance here because it could lead to issues
    // if other parts of the program try to access it during shutdown
}