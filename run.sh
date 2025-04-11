#!/bin/bash

# Cleanup function to remove generated files
cleanup() {
    echo "Cleaning up generated files..."
    rm -f parser.tab.cpp parser.tab.hpp lex.yy.c calc
    echo "Cleanup complete"
}

# Build script for calculator project

# Step 1: Generate parser files with Bison
echo "Generating parser with Bison..."
bison -d -o parser.tab.cpp parser.ypp
if [ $? -ne 0 ]; then
    echo "Bison failed to generate parser"
    exit 1
fi

# Step 2: Generate lexer with Flex
echo "Generating lexer with Flex..."
flex -o lex.yy.c lexer.l
if [ $? -ne 0 ]; then
    echo "Flex failed to generate lexer"
    exit 1
fi

# Step 3: Compile all source files
echo "Compiling project..."
g++ -std=c++17 -o calc lex.yy.c parser.tab.cpp main.cpp handler.cpp symbol_table_generator.cpp
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    cleanup
    exit 1
fi

echo "Build successful! Executable 'calc' created"

# Step 4: Run the calculator
echo "Running the calculator..."
./calc input.txt

# Step 5: Clean up generated files
cleanup