# ZCompi Compiler

A compiler for a custom programming language that supports various programming constructs including variables, functions, control structures, and type checking.

## Technical Overview

- **Lexical Analysis**: Efficient tokenization using Flex, supporting complex patterns and whitespace handling.
- **Syntax Analysis**: Robust parsing with Bison, implementing a context-free grammar for language constructs.
- **Type System**: Comprehensive type checking with support for type promotion and operator overloading.
- **Symbol Table Management**: Hierarchical symbol table with scope resolution and efficient lookup.
- **Intermediate Code Generation**: Quadruple-based intermediate representation for optimized code generation.
- **Error Recovery**: Graceful error handling with detailed diagnostics and recovery mechanisms.
- **Memory Management**: Smart pointer-based AST node management for automatic memory cleanup.
- **Thread Safety**: Designed for potential multi-threaded compilation with synchronized error reporting.

## Features

- **Data Types**: Supports `int`, `float`, `string`, `char`, `bool`, and `void` types
- **Variables**: Variable declaration and assignment with type checking
- **Functions**: Function declaration and calls with parameter passing
- **Control Structures**:
  - If-else statements
  - While loops
  - Do-while loops
  - For loops
  - Switch-case statements
  - Break statements
- **Operators**:
  - Arithmetic: `+`, `-`, `*`, `/`, `%`, `^` (power)
  - Logical: `&&`, `||`, `!`
  - Comparison: `==`, `!=`, `>`, `<`, `>=`, `<=`
  - Bitwise: `|`, `&`, `<<`, `>>`
- **I/O**: Print statements for output
- **Error Handling**: Comprehensive error reporting with line numbers
- **Symbol Table**: Maintains information about variables and functions
- **Code Generation**: Generates quadruples for intermediate representation

## Project Structure

- `handler.hpp/cpp`: Core compiler components including error handling, type checking, and AST nodes
- `symbol_table_generator.hpp/cpp`: Manages symbol table generation and scope handling
- `lexer.l`: Lexical analyzer definition
- `parser.ypp`: Parser definition using Bison
- `main.cpp`: Entry point of the compiler

## Building the Project

### Prerequisites

- Flex (Fast Lexical Analyzer)
- Bison (GNU Parser Generator)
- C++ compiler (supporting C++11 or later)
- Make

### Build Steps

1. Generate the lexer and parser:
```bash
flex lexer.l
bison -d parser.ypp
```

2. Compile the project:
```bash
g++ -std=c++11 -o zcompi *.cpp
```

## Usage

```bash
./zcompi <input_file>
```

The compiler will:
1. Parse the input file
2. Generate a symbol table
3. Generate quadruples
4. Report any errors found during compilation

## Example Program

```c
int main() {
    int x = 10;
    float y = 3.14;
    string name = "ZCompi";
    
    if (x > 5) {
        print("x is greater than 5");
    } else {
        print("x is less than or equal to 5");
    }
    
    while (x > 0) {
        print(x);
        x = x - 1;
    }
    
    return 0;
}
```

## Error Handling

The compiler provides detailed error messages including:
- Line numbers where errors occur
- Type mismatch errors
- Undefined variable errors
- Function declaration errors
- Scope-related errors

## Output Files

- `output.txt`: Contains the generated quadruples
- `output_symbol_table.txt`: Contains the symbol table information
- `error_file.txt`: Contains compilation errors and warnings

## Design Patterns Used

- **Singleton Pattern**: For error handling
- **Strategy Pattern**: For type checking
- **Factory Method Pattern**: For type checker creation
- **Composite Pattern**: For AST nodes
- **Visitor Pattern**: For type checking and code generation

## License

[Add your license information here] 