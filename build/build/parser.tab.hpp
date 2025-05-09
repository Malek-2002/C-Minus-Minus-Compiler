/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_MALEK_WORK_ZCOMPI_CALCULATOR_BUILD_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_HOME_MALEK_WORK_ZCOMPI_CALCULATOR_BUILD_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_VALUE = 259,            /* STRING_VALUE  */
    CHAR_VALUE = 260,              /* CHAR_VALUE  */
    INT_VALUE = 261,               /* INT_VALUE  */
    FLOAT_VALUE = 262,             /* FLOAT_VALUE  */
    BOOL_VALUE = 263,              /* BOOL_VALUE  */
    INT = 264,                     /* INT  */
    FLOAT = 265,                   /* FLOAT  */
    STRING = 266,                  /* STRING  */
    CHAR = 267,                    /* CHAR  */
    BOOL = 268,                    /* BOOL  */
    VOID = 269,                    /* VOID  */
    CONSTANT = 270,                /* CONSTANT  */
    PRINT = 271,                   /* PRINT  */
    RETURN = 272,                  /* RETURN  */
    LOGICAL_AND = 273,             /* LOGICAL_AND  */
    LOGICAL_OR = 274,              /* LOGICAL_OR  */
    LOGICAL_NOT = 275,             /* LOGICAL_NOT  */
    EQUAL = 276,                   /* EQUAL  */
    NOT_EQUAL = 277,               /* NOT_EQUAL  */
    GT = 278,                      /* GT  */
    LT = 279,                      /* LT  */
    GTE = 280,                     /* GTE  */
    LTE = 281,                     /* LTE  */
    EQ = 282,                      /* EQ  */
    SEMICOLON = 283,               /* SEMICOLON  */
    MOD = 284,                     /* MOD  */
    ADD = 285,                     /* ADD  */
    SUB = 286,                     /* SUB  */
    MUL = 287,                     /* MUL  */
    DIV = 288,                     /* DIV  */
    BITWISE_XOR = 289,             /* BITWISE_XOR  */
    BITWISE_OR = 290,              /* BITWISE_OR  */
    BITWISE_AND = 291,             /* BITWISE_AND  */
    SHL = 292,                     /* SHL  */
    SHR = 293,                     /* SHR  */
    SWITCH = 294,                  /* SWITCH  */
    BREAK = 295,                   /* BREAK  */
    CASE = 296,                    /* CASE  */
    DEFAULT = 297,                 /* DEFAULT  */
    IF = 298,                      /* IF  */
    ELSE = 299,                    /* ELSE  */
    FOR = 300,                     /* FOR  */
    WHILE = 301,                   /* WHILE  */
    DO = 302,                      /* DO  */
    CONTINUE = 303,                /* CONTINUE  */
    UMINUS = 304                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 67 "src/parser.ypp"

    std::string* strVal;
    ASTNode* node;
    BlockNode* blockNode;
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;

#line 123 "/home/malek/work/zcompi/calculator/build/build/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_MALEK_WORK_ZCOMPI_CALCULATOR_BUILD_BUILD_PARSER_TAB_HPP_INCLUDED  */
