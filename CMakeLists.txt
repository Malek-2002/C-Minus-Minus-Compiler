cmake_minimum_required(VERSION 3.10)
project(calculator VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create output directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)  # Source bin/ for executable
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/logs) # Source logs/ for log files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

# Ensure source logs/ directory is writable
execute_process(
    COMMAND chmod -R u+rwx,g+rx,o+rx ${CMAKE_CURRENT_SOURCE_DIR}/logs
    RESULT_VARIABLE CHMOD_RESULT
)
if(CHMOD_RESULT)
    message(WARNING "Failed to set permissions on source logs directory: ${CHMOD_RESULT}")
endif()

# Find required packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Generate lexer and parser
FLEX_TARGET(Lexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/build/lex.yy.c)
BISON_TARGET(Parser src/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/build/parser.tab.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/build/parser.tab.hpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Ensure lex.yy.c is compiled as C++
set_source_files_properties(${FLEX_Lexer_OUTPUTS} PROPERTIES LANGUAGE CXX)

# Source files
file(GLOB AST_SOURCES src/ast/*.cpp)
file(GLOB SEMANTIC_SOURCES src/semantic/*.cpp)
file(GLOB CODEGEN_SOURCES src/codegen/*.cpp)
file(GLOB ERROR_SOURCES src/error/*.cpp)

set(SOURCES
    src/main.cpp
    ${AST_SOURCES}
    ${SEMANTIC_SOURCES}
    ${CODEGEN_SOURCES}
    ${ERROR_SOURCES}
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
)

# Debug: Print collected sources
message("Collected sources: ${SOURCES}")

# Create executable
add_executable(calc ${SOURCES})

# Include directories
target_include_directories(calc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/build
)

# Set output directory for executable to source bin/
set_target_properties(calc
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

# Install targets
install(TARGETS calc
    RUNTIME DESTINATION bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

# Create data directory in build directory
add_custom_command(TARGET calc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/data
)

# Ensure data directory is writable
add_custom_command(TARGET calc POST_BUILD
    COMMAND chmod -R u+rwx,g+rx,o+rx ${CMAKE_BINARY_DIR}/data
    COMMENT "Setting permissions for data directory"
)

# Copy input file to build data directory
add_custom_command(TARGET calc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/data/input.txt
    ${CMAKE_BINARY_DIR}/data/input.txt
)

# Add custom run target
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/calc build/data/input.txt
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS calc
    COMMENT "Running calc with input.txt"
)