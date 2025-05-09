
# C Minus Minus
![enter image description here](https://sdmntpritalynorth.oaiusercontent.com/files/00000000-7e60-6246-b687-45dc568a4ebf/raw?se=2025-04-28T03:02:00Z&sp=r&sv=2024-08-04&sr=b&scid=51356515-abd9-5faa-bedf-336887a60071&skoid=59d06260-d7df-416c-92f4-051f0b47c607&sktid=a48cca56-e6da-484e-a814-9c849652bcb3&skt=2025-04-27T08:21:48Z&ske=2025-04-28T08:21:48Z&sks=b&skv=2024-08-04&sig=9Zzvcmt%2bUm4JdiOpdj4iTdtRLJhEVJhhlhZw6B8eInw=)

## Table of Contents

- [C Plus Minus](#c-plus-minus)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Run Steps](#run-steps)
  - [Tools and Technologies](#tools-and-technologies)
  - [Tokens](#tokens)
  - [Syntax](#syntax)
    - [Data Types](#data-types)
    - [Operators](#operators)
    - [Conditional Statements](#conditional-statements)
    - [Loops](#loops)
    - [Functions](#functions)
  - [Quadruples](#quadruples)
    - [Procedures](#procedures)
    - [Variables](#variables)
    - [Branching \& Jumps](#branching--jumps)
    - [Arithmetic Operations](#arithmetic-operations)
    - [Bitwise Operations](#bitwise-operations)
    - [Logical Operations](#logical-operations)
  - [Production Rules](#production-rules)
  - [Semantic Errors](#semantic-errors)
  - [Semantic Errors](#semantic-errors-1)
  - [Desktop Application](#desktop-application)

## Introduction

The designed language is a `C` like programming language.

Sample program:

```c
const int a = 5;
float b = 6;
print ("Operations:");
if (a == 5) {
    print ("a is 5");
}
else {
    if (b == 6) {
        print ("b is 6");
    }
    else {
        print ("b is not 6");
    }
}
```

## How To Use Steps
- write your program in data/input.txt file 
- or use any ready-made program in tests file
 - then run these commands
- `mkdir build`: create build file
- `cd build`: enter build file
- `cmake ..`: generate the build system
- `make`:  compile the project
- `make run` run the project

You can run the desktop application by going to the project directory and run: 
`python3 ./gui.py`

## Tools and Technologies

<ol>
   <li>Lex: It breaks down the input text into a sequence of tokens, which are then passed on to the parser for further processing.</li>
   <li>Yacc: It takes a sequence of tokens as input and produces a parse tree or an abstract syntax tree (AST) that represents the structure of the input according to the grammar rules.</li>
      <li>C++ Programming Language</li>
</ol>


## Tokens

<table>
   <tr>
      <th align="left">Token</th>
      <th align="left">Regex</th>
      <th align="left">Description</th>
   </tr>
   <tr>
      <td>INLINE_COMMENT</td>
      <td>\/\/[\s\t]*.*[\s\t]*</td>
      <td>Single-line comment starting with //, followed by any characters until newline.</td>
   </tr>
   <tr>
      <td>INT</td>
      <td>"int"</td>
      <td>Keyword for integer data type.</td>
   </tr>
   <tr>
      <td>FLOAT</td>
      <td>"float"</td>
      <td>Keyword for floating-point data type.</td>
   </tr>
   <tr>
      <td>STRING</td>
      <td>"string"</td>
      <td>Keyword for string data type.</td>
   </tr>
   <tr>
      <td>CHAR</td>
      <td>"char"</td>
      <td>Keyword for character data type.</td>
   </tr>
   <tr>
      <td>BOOL</td>
      <td>"bool"</td>
      <td>Keyword for boolean data type.</td>
   </tr>
   <tr>
      <td>PRINT</td>
      <td>"print"</td>
      <td>Keyword for print statement.</td>
   </tr>
   <tr>
      <td>VOID</td>
      <td>"void"</td>
      <td>Keyword for void type (e.g., for functions with no return value).</td>
   </tr>
   <tr>
      <td>CONSTANT</td>
      <td>"const"</td>
      <td>Keyword for constant declaration.</td>
   </tr>
   <tr>
      <td>SWITCH</td>
      <td>"switch"</td>
      <td>Keyword for switch statement.</td>
   </tr>
   <tr>
      <td>BREAK</td>
      <td>"break"</td>
      <td>Keyword for breaking out of a loop or switch.</td>
   </tr>
   <tr>
      <td>CONTINUE</td>
      <td>"continue"</td>
      <td>Keyword for skipping to the next iteration of a loop.</td>
   </tr>
   <tr>
      <td>CASE</td>
      <td>"case"</td>
      <td>Keyword for case label in switch statement.</td>
   </tr>
   <tr>
      <td>DEFAULT</td>
      <td>"default"</td>
      <td>Keyword for default case in switch statement.</td>
   </tr>
   <tr>
      <td>RETURN</td>
      <td>"return"</td>
      <td>Keyword for returning a value from a function.</td>
   </tr>
   <tr>
      <td>IF</td>
      <td>"if"</td>
      <td>Keyword for if conditional statement.</td>
   </tr>
   <tr>
      <td>ELSE</td>
      <td>"else"</td>
      <td>Keyword for else conditional statement.</td>
   </tr>
   <tr>
      <td>FOR</td>
      <td>"for"</td>
      <td>Keyword for for loop.</td>
   </tr>
   <tr>
      <td>WHILE</td>
      <td>"while"</td>
      <td>Keyword for while loop.</td>
   </tr>
   <tr>
      <td>DO</td>
      <td>"do"</td>
      <td>Keyword for do-while loop.</td>
   </tr>
   <tr>
      <td>BOOL_VALUE</td>
      <td>"true"</td>
      <td>Boolean true value, sets yylval.boolVal = true.</td>
   </tr>
   <tr>
      <td>BOOL_VALUE</td>
      <td>"false"</td>
      <td>Boolean false value, sets yylval.boolVal = false.</td>
   </tr>
   <tr>
      <td>LOGICAL_AND</td>
      <td>"&&"</td>
      <td>Logical AND operator.</td>
   </tr>
   <tr>
      <td>LOGICAL_OR</td>
      <td>"||"</td>
      <td>Logical OR operator.</td>
   </tr>
   <tr>
      <td>LOGICAL_NOT</td>
      <td>"!"</td>
      <td>Logical NOT operator.</td>
   </tr>
   <tr>
      <td>EQUAL</td>
      <td>"=="</td>
      <td>Equality comparison operator.</td>
   </tr>
   <tr>
      <td>NOT_EQUAL</td>
      <td>"!="</td>
      <td>Inequality comparison operator.</td>
   </tr>
   <tr>
      <td>GT</td>
      <td>">"</td>
      <td>Greater than operator.</td>
   </tr>
   <tr>
      <td>LT</td>
      <td>"<"</td>
      <td>Less than operator.</td>
   </tr>
   <tr>
      <td>GTE</td>
      <td>">="</td>
      <td>Greater than or equal to operator.</td>
   </tr>
   <tr>
      <td>LTE</td>
      <td>"<="</td>
      <td>Less than or equal to operator.</td>
   </tr>
   <tr>
      <td>EQ</td>
      <td>"="</td>
      <td>Assignment operator.</td>
   </tr>
   <tr>
      <td>SEMICOLON</td>
      <td>";"</td>
      <td>Semicolon to mark the end of a statement.</td>
   </tr>
   <tr>
      <td>MOD</td>
      <td>"%"</td>
      <td>Modulus operator.</td>
   </tr>
   <tr>
      <td>ADD</td>
      <td>"+"</td>
      <td>Addition operator.</td>
   </tr>
   <tr>
      <td>SUB</td>
      <td>"-"</td>
      <td>Subtraction operator.</td>
   </tr>
   <tr>
      <td>MUL</td>
      <td>"*"</td>
      <td>Multiplication operator.</td>
   </tr>
   <tr>
      <td>DIV</td>
      <td>"/"</td>
      <td>Division operator.</td>
   </tr>
   <tr>
      <td>BITWISE_XOR</td>
      <td>"^"</td>
      <td>Bitwise XOR operator.</td>
   </tr>
   <tr>
      <td>BITWISE_OR</td>
      <td>"|"</td>
      <td>Bitwise OR operator.</td>
   </tr>
   <tr>
      <td>BITWISE_AND</td>
      <td>"&"</td>
      <td>Bitwise AND operator.</td>
   </tr>
   <tr>
      <td>SHL</td>
      <td>"<<"</td>
      <td>Left shift operator.</td>
   </tr>
   <tr>
      <td>SHR</td>
      <td>">>"</td>
      <td>Right shift operator.</td>
   </tr>
   <tr>
      <td>PUNCTUATORS</td>
      <td>[){}(:,]</td>
      <td>Language punctuators (parentheses, braces, comma, colon).</td>
   </tr>
   <tr>
      <td>IDENTIFIER</td>
      <td>[a-zA-Z_][a-zA-Z0-9_]*</td>
      <td>Identifier (variable/function names starting with a letter or underscore).</td>
   </tr>
   <tr>
      <td>CHAR_VALUE</td>
      <td>\'.\'</td>
      <td>Single character literal enclosed in single quotes, sets yylval.charVal.</td>
   </tr>
   <tr>
      <td>STRING_VALUE</td>
      <td>\"([^\"\\]|\\.)*\"</td>
      <td>String literal enclosed in double quotes, sets yylval.strVal.</td>
   </tr>
   <tr>
      <td>INT_VALUE</td>
      <td>[0-9]+</td>
      <td>Integer literal, sets yylval.intVal.</td>
   </tr>
   <tr>
      <td>FLOAT_VALUE</td>
      <td>[0-9]+\.[0-9]+</td>
      <td>Floating-point literal, sets yylval.floatVal.</td>
   </tr>
   <tr>
      <td>SPACE</td>
      <td>[ \t]+</td>
      <td>One or more spaces or tabs (ignored, updates column).</td>
   </tr>
   <tr>
      <td>NEW_LINE</td>
      <td>\n</td>
      <td>Newline character (resets column).</td>
   </tr>
   <tr>
      <td>UNKNOWN</td>
      <td>.</td>
      <td>Any unmatched single character, returns the character itself.</td>
   </tr>
</table>

## Syntax

### Data Types

Tha language supports the following data types:

- Integer
- Float
- Boolean
- Char
- String

It supports modifiers like `const` as well.

```c
const int a = 10;
int b = 20;
float c = 10.5;
bool d = true;
char ch = 'c';
string e = "Hello World";
```

### Operators

The language supports the common operators in C.

```c
// Arithmetic operators
a = b + c;
a = b - c;
a = b * c;
a = b / c;
a = b % c;
// Bitwise operators
a = b & c;
a = b | c;
a = b ^ c;
// Logical operators
a = b && c;
a = b || c;
a = !b;
// Relational operators
a = b == c;
a = b != c;
a = b > c;
a = b >= c;
a = b < c;
a = b <= c;
// Shift operators
a = b << c;
a = b >> c;
```

### Conditional Statements

The language supports the if-else, if-elif-else, and switch-case statements.

```c
int a = 10;
// if statement
if (a == 10) {
    print("if");
    print("another if");
}
else if (a == 11) {
    print("elif");
    print("another elif");
}
else {
    print("else");
    print("another else");
    if (a == 10) {
        print("if");
        print("another if");
    }
    else {
        print("else");
        print("another else");
    }
}
if (a == 10) {
    print("if");
    print("another if");
}
else if(a == 11) {
    print("else");
    print("another else");
}
// switch-case statement
switch (a) {
    default:
        print("default");
        break;
}
switch (a) {
    case 1:  {
        print("1");
        break;
		}    
    case 2: { 
        print("2");
        break;
    }
    case 3: { 
        print("3");
        break;
	}
}

switch (a) {
    case 1: {
        print("1");
        break;
	}    
    case 2: { 
        print("2");
        break;
    }
    case 3: {
        print("3");
        break;
	}    
    default: { 
        print("default");
        break;
    }
}
```

### Loops

The language supports the while, for, and repeat-until loops.

```c
// while loop
a = 0;
while (a < 20) {
    print(a);
    a = a + 1;
}
print(a);
while (a < 20) {
    if (a == 10) {
        print(a);
    }
    a = a + 1;
}
// for loop
for (a=2 ; a<10; a = a+1; ) {
    print(a);
}
for (a=2 ; a<10; a= a+1; ) {
    print(a);
    b = a;
    while (b < 10) {
        if (b == 5) {
            print("hi");
            print(b);
        }
        
        b = b + 1;
    }
}
// repeat-until loop
a = 0;
do{
    print(a);
    a = a + 1;
    print(a);
} while (a == 1);
do {
    print(a);
    a = a + 1;
    if (a == 1) {
        print(a);
    }
} while (a == 1);
```

### Functions

The language supports functions with and without parameters.

```c
int y (){
    print("y");
    return 1;
}
int x(int a, int b) {
    print("add");
    return a + b;
}
x(1, 2); // function call
a = y(); // function call and assignment
```

N.B.: you can't define a function inside any scope.


## Quadruples

### Procedures

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **FUNC**       | Start of a function declaration                                   | function name   |                 |                 |
 **call**       | Calls a function with specified arguments                         | function name   | arg count       | temp var        |
 **return**     | Return from a function, optionally with a value                   | value (if any)  |                 |                 |
 **param**      | Pass an argument to a function                                    | argument value  |                 |                 |

### Variables

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **assign**     | Assign a value to a variable or temporary                         | value           |                 | identifier/temp |
  **declare**       | declare a variable in the scope                                | type            | blk_id           | identifier name        |
 **cast**       | Cast the value to a specified type                                | type            | temp var           | temp var        |

### Branching & Jumps

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **JMP**        | Unconditional jump to the specified label                         | label           |                 |                 |
 **JNZ**        | Jump to label if condition is true (used for conditionals)        | condition value |                 | label           |
 **JZ**        | Jump to label if condition is false (used for conditionals)       | condition value |                 | label           |
 **Label**      | Define a label for jumps                                          |                 |                 | label           |

### Arithmetic Operations

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **NEG**        | Negate the value of an expression (unary minus)                   | operand         |                 | temp var        |
 **ADD**        | Add two values                                                    | left operand    | right operand   | temp var        |
 **SUB**        | Subtract two values                                               | left operand    | right operand   | temp var        |
 **MUL**        | Multiply two values                                               | left operand    | right operand   | temp var        |
 **DIV**        | Divide two values                                                 | left operand    | right operand   | temp var        |
 **MOD**        | Compute modulus of two values                                     | left operand    | right operand   | temp var        |

### Bitwise Operations

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **BITWISE_OR** | Perform bitwise OR on two values                                  | left operand    | right operand   | temp var        |
 **BITWISE_AND**| Perform bitwise AND on two values                                 | left operand    | right operand   | temp var        |
 **BITWISE_XOR**| Perform bitwise XOR on two values                                 | left operand    | right operand   | temp var        |
 **SHL**        | Shift left the value                                              | left operand    | right operand   | temp var        |
 **SHR**        | Shift right the value                                             | left operand    | right operand   | temp var        |

### Logical Operations

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **LOGICAL_OR** | Perform logical OR on two values                                  | left operand    | right operand   | temp var        |
 **LOGICAL_AND**| Perform logical AND on two values                                 | left operand    | right operand   | temp var        |
 **NOT**        | Perform logical NOT on a value                                    | operand         |                 | temp var        |
 **EQ**         | Check if two values are equal                                     | left operand    | right operand   | temp var        |
 **NEQ**        | Check if two values are not equal                                 | left operand    | right operand   | temp var        |
 **GT**         | Check if left value is greater than right                         | left operand    | right operand   | temp var        |
 **GEQ**        | Check if left value is greater than or equal to right             | left operand    | right operand   | temp var        |
 **LT**         | Check if left value is less than right                            | left operand    | right operand   | temp var        |
 **LEQ**        | Check if left value is less than or equal to right                | left operand    | right operand   | temp var        |

### Input/Output Operations

 **Quadruples** | **Description**                                                   |    **ARG1**     |    **ARG2**     |    **RES**      |
----------------|-------------------------------------------------------------------|-----------------|-----------------|-----------------|
 **PRINT**      | Output the value to the console                                   | value           |                 |                 |
## Production Rules

<ul> <li>program → program stmt | ε</li> <br> <li>BLOCK → { program }</li> <br> <li>stmt → declr_stmt | assign_stmt | expr ; | if_stmt | while_stmt | do_while_stmt | for_stmt | break_stmt | print_stmt | BLOCK | return_stmt ; | function_declr_stmt | switch_stmt | continue_stmt | error ; | error }</li> <br> <li>expr → IDENTIFIER | INT_VALUE | FLOAT_VALUE | BOOL_VALUE | STRING_VALUE | CHAR_VALUE | ( expr ) | function_call_stmt | - expr | ! expr | expr + expr | expr - expr | expr * expr | expr / expr | expr % expr | expr | expr | expr & expr | expr ^ expr | expr << expr | expr >> expr | expr == expr | expr != expr | expr > expr | expr < expr | expr >= expr | expr <= expr | expr && expr | expr || expr</li> <br> <li>opt_else_if_stmt → ELSE BLOCK | ELSE if_stmt | ε</li> <br> <li>if_stmt → IF ( expr ) BLOCK opt_else_if_stmt</li> <br> <li>while_stmt → WHILE ( expr ) BLOCK</li> <br> <li>do_while_stmt → DO BLOCK WHILE ( expr ) ;</li> <br> <li>for_stmt → FOR ( stmt stmt stmt ) { program }</li> <br> <li>switch_stmt → SWITCH ( expr ) { CASES }</li> <br> <li>CASES → CASES case_stmt | ε</li> <br> <li>case_stmt → CASE expr : BLOCK | DEFAULT : BLOCK</li> <br> <li>break_stmt → BREAK ;</li> <br> <li>continue_stmt → CONTINUE ;</li> <br> <li>print_stmt → PRINT ( expr ) ;</li> <br> <li>type → INT | FLOAT | BOOL | STRING | CHAR | VOID</li> <br> <li>function_call_stmt → IDENTIFIER ( ARGUMENTS )</li> <br> <li>ARGUMENTS → expr , ARGUMENTS | expr | ε</li> <br> <li>function_declr_stmt → type IDENTIFIER ( ARGS ) BLOCK</li> <br> <li>ARGS → ARG_DECL , ARGS | ARG_DECL | ε</li> <br> <li>ARG_DECL → type IDENTIFIER</li> <br> <li>return_stmt → RETURN | RETURN expr</li> <br> <li>assign_stmt → IDENTIFIER = expr ;</li> <br> <li>declr_stmt → type IDENTIFIER = expr ; | type IDENTIFIER ; | CONSTANT type IDENTIFIER = expr ; | CONSTANT type IDENTIFIER ;</li> </ul>

Semantic Errors         
-------------------
 **Type Mismatch** 
 **Undeclared Variable**     
 **Redeclaration of variables**    
 **Constant Reassignment**
 **Continue with no loop defined**
 **Return with no function defined**
 **Switch with Repeated Cases**
 **Function Call with wrong Signature**
 **Function Redeclaration**      

Semantic Warnings         
-------------------
 **Unused Variables**
 **Unused Functions**      
 ********


## Desktop Application
A desktop application is to provide a user interface for the compiler. The application allows the user to select and edit a file from the file system and compile it. The application will then display the generated quadruples, the symbol table and error messages file.
- The main functionalities:
    - Open an existing file (load file)
    - Write a new file in the text editor
    - Save the file press save
    - Compile the file in one step
    - Compile the file step by step
    - Display the generated quadruples
    - Display the symbol table
    - Display the error messages file.