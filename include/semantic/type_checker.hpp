#ifndef TYPE_CHECKER_HPP
#define TYPE_CHECKER_HPP

#include <string>
#include <memory>

/********************************
 * TypeChecker Interface
 ********************************/
class TypeChecker
{
public:
    virtual ~TypeChecker() = default;
    virtual std::string checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber) = 0;
    virtual std::string checkType(const std::string &opType, int lineNumber) = 0;
};

/********************************
 * ArithmeticTypeChecker Class
 ********************************/
class ArithmeticTypeChecker : public TypeChecker
{
private:
    std::string op; // Stores the arithmetic operator to handle string concatenation correctly

public:
    std::string checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber) override;
    std::string checkType(const std::string &opType, int lineNumber) override;
    void setOperator(const std::string &op);
};

/********************************
 * ComparisonTypeChecker Class
 ********************************/
class ComparisonTypeChecker : public TypeChecker
{
private:
    std::string op; // Stores the comparison operator to handle string comparisons correctly

public:
    std::string checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber) override;
    std::string checkType(const std::string &opType, int lineNumber) override;
    void setOperator(const std::string &op);
};

/********************************
 * BooleanTypeChecker Class
 ********************************/
class BooleanTypeChecker : public TypeChecker
{
public:
    std::string checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber) override;
    std::string checkType(const std::string &opType, int lineNumber) override;
};

/********************************
 * BitwiseTypeChecker Class
 ********************************/
class BitwiseTypeChecker : public TypeChecker
{
public:
    std::string checkTypes(const std::string &op1Type, const std::string &op2Type, int lineNumber) override;
    std::string checkType(const std::string &opType, int lineNumber) override;
};

/********************************
 * TypeCheckerFactory Class
 ********************************/
class TypeCheckerFactory
{
public:
    static std::unique_ptr<TypeChecker> createTypeChecker(const std::string &operatorType, const std::string &op = "");
};

#endif // TYPE_CHECKER_HPP