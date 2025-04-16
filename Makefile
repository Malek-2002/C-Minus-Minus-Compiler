# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# Source files
LEX_SRC := lexer.l
YACC_SRC := parser.ypp
CPP_SRCS := main.cpp handler.cpp symbol_table_generator.cpp error_handler.cpp

# Generated files
LEX_OUT := lex.yy.c
YACC_CPP := parser.tab.cpp
YACC_HPP := parser.tab.hpp
TARGET := calc

# Default target
all: $(TARGET)

# Final executable depends on generated files and source files
$(TARGET): $(LEX_OUT) $(YACC_CPP) $(CPP_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(LEX_OUT) $(YACC_CPP) $(CPP_SRCS)

# Lexer generation depends on parser header (for token definitions)
$(LEX_OUT): $(LEX_SRC) $(YACC_HPP)
	flex -o $@ $<

# Parser generation (produces both .cpp and .hpp)
$(YACC_CPP) $(YACC_HPP): $(YACC_SRC)
	bison -d -o $(YACC_CPP) $<

# Run target
run: $(TARGET)
	./$(TARGET) input.txt

# Clean generated files
clean:
	rm -f $(LEX_OUT) $(YACC_CPP) $(YACC_HPP) $(TARGET)

.PHONY: all clean run