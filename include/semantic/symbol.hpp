#pragma once

#include <string>
#include <vector>
#include <utility>

/**
 * Represents a variable or constant in the symbol table
 */
class Symbol {
private:
    std::string name;
    std::string type;
    std::string value;
    std::string identifierType;
    bool isConst;
    bool isInitialized;
    bool isUsed = false;
    int lineNumber;

public:
    Symbol(const std::string& name, const std::string& type, bool isConst, int lineNumber, const std::string& identifierType = "variable")
        : name(name), type(type), value(""), isConst(isConst), isInitialized(false), lineNumber(lineNumber), identifierType(identifierType) {};
    
    // Getters
    const std::string& getName() const;
    const std::string& getType() const;
    const std::string& getValue() const;
    int getLineNumber() const;
    std::string getIdentifierType() const; 
    const bool getIsUsed() const;
    bool isConstant() const;
    bool checkInitialization() const;
    
    // Setters
    void setValue(const std::string& newValue);
    void setIsConst(bool constStatus);
    void setInitialized();
    void setUsed();
    
    std::string toString() const;
};

/**
 * Represents a function in the symbol table
 */
class FunctionSymbol {
private:
    std::string name;
    std::string returnType;
    std::vector<std::pair<std::string, std::string>> parameters;
    bool isDefined;
    bool hasReturnStatement;
    bool isUsed = false;
    int lineNumber;

public:
    FunctionSymbol(const std::string& name, const std::string& returnType,
                 bool isDefined, int lineNumber);
    
    // Getters
    const std::string& getName() const;
    const std::string& getReturnType() const;
    const std::vector<std::pair<std::string, std::string>>& getParameters() const;
    bool getIsDefined() const;
    int getLineNumber() const;
    bool getHasReturnStatement() const;
    bool getIsUsed() const;
    
    // Setters
    void setName(const std::string& newName);
    void setReturnType(const std::string& type);
    void setIsDefined(bool defined);
    void setHasReturnStatement(bool hasReturn);
    void setIsUsed();
    
    // Parameter management
    void addParameter(const std::string& type, const std::string& name);
    void removeParameter(size_t index);
    void clearParameters();
    
    // Utility methods
    size_t getParameterCount() const;
    std::string getParameterType(size_t index) const;
    std::string getParameterName(size_t index) const;
    std::string getSignature() const;
    std::string toString() const;
};