#pragma once

#include <string>
#include <memory>

// Forward declarations
class QuadruplesGenerator;

/**
 * Abstract base class for all Abstract Syntax Tree nodes
 */
class ASTNode {
public:
    virtual ~ASTNode() = default;
    
    /**
     * Returns the type of the expression represented by this node
     */
    virtual std::string getType() const = 0;
    
    /**
     * Generates intermediate code for this node
     */
    virtual void generateCode(QuadruplesGenerator& generator) = 0;
};