#include "semantic/symbol.hpp"


/********************************
 * Symbol Implementation
 ********************************/
const std::string &Symbol::getName() const
{
    return name;
}

const std::string &Symbol::getType() const
{
    return type;
}

const std::string &Symbol::getValue() const
{
    return value;
}

int Symbol::getLineNumber() const
{
    return lineNumber;
}

std::string Symbol::getIdentifierType() const {
    return identifierType;
}

const bool Symbol::getIsUsed() const {
    return this->isUsed;
}

void Symbol::setUsed() {
    isUsed = true;
}

bool Symbol::isConstant() const
{
    return isConst;
}

bool Symbol::checkInitialization() const
{
    return isInitialized;
}

void Symbol::setValue(const std::string &newValue)
{
    value = newValue;
    isInitialized = true;
}

void Symbol::setIsConst(bool constStatus)
{
    isConst = constStatus;
}

void Symbol::setInitialized()
{
    isInitialized = true;
}

std::string Symbol::toString() const
{
    return "Symbol{name='" + name +
           "', type='" + type +
           "', value='" + value +
           "', isConst=" + (isConst ? "true" : "false") +
           ", isInitialized=" + (isInitialized ? "true" : "false") + "}";
}

FunctionSymbol::FunctionSymbol(const std::string &name, const std::string &returnType,
                               bool isDefined, int lineNumber)
    : name(name), returnType(returnType), isDefined(isDefined),
      hasReturnStatement(false), lineNumber(lineNumber) {}

// Getters
const std::string &FunctionSymbol::getName() const
{
    return name;
}

const std::string &FunctionSymbol::getReturnType() const
{
    return returnType;
}

const std::vector<std::pair<std::string, std::string>> &FunctionSymbol::getParameters() const
{
    return parameters;
}

bool FunctionSymbol::getIsDefined() const
{
    return isDefined;
}

int FunctionSymbol::getLineNumber() const
{
    return lineNumber;
}

bool FunctionSymbol::getHasReturnStatement() const
{
    return hasReturnStatement;
}

// Setters
void FunctionSymbol::setName(const std::string &newName)
{
    name = newName;
}

void FunctionSymbol::setReturnType(const std::string &type)
{
    returnType = type;
}

void FunctionSymbol::setIsDefined(bool defined)
{
    isDefined = defined;
}

void FunctionSymbol::setHasReturnStatement(bool hasReturn)
{
    hasReturnStatement = hasReturn;
}

// Parameter management
void FunctionSymbol::addParameter(const std::string &type, const std::string &name)
{
    parameters.emplace_back(type, name);
}

void FunctionSymbol::removeParameter(size_t index)
{
    if (index < parameters.size())
    {
        parameters.erase(parameters.begin() + index);
    }
}

void FunctionSymbol::clearParameters()
{
    parameters.clear();
}

// Utility methods
size_t FunctionSymbol::getParameterCount() const
{
    return parameters.size();
}

std::string FunctionSymbol::getParameterType(size_t index) const
{
    if (index < parameters.size())
    {
        return parameters[index].first;
    }
    return "";
}

std::string FunctionSymbol::getParameterName(size_t index) const
{
    if (index < parameters.size())
    {
        return parameters[index].second;
    }
    return "";
}

// Signature generation
std::string FunctionSymbol::getSignature() const
{
    std::string signature = returnType + " " + name + "(";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        if (i > 0)
            signature += ", ";
        signature += parameters[i].first; // Only include type in signature
    }
    signature += ")";
    return signature;
}

// String representation
std::string FunctionSymbol::toString() const
{
    std::string str = returnType + " " + name + "(";
    for (size_t i = 0; i < parameters.size(); ++i)
    {
        if (i > 0)
            str += ", ";
        str += parameters[i].first + " " + parameters[i].second;
    }
    str += ")";

    return str;
}

bool FunctionSymbol::getIsUsed() const
{
    return isUsed;
}
void FunctionSymbol::setIsUsed()
{
    isUsed = true;
}
