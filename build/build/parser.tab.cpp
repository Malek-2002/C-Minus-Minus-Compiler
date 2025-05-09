/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.ypp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>


// Include headers from the new directory structure
// Include headers from the new directory structure
#include "ast/ast_node.hpp"
#include "ast/block_node.hpp"
#include "ast/expression_nodes.hpp"
#include "ast/statement_nodes.hpp"
#include "ast/control_flow_nodes.hpp"
#include "ast/function_nodes.hpp"
#include "error/error_handler.hpp"
#include "semantic/symbol.hpp"
#include "semantic/symbol_table.hpp"
#include "codegen/quadruples_generator.hpp"

int yylex();
void yyerror(const char* s);
extern int yylineno;  // Needed to track line numbers

// Global objects
extern BlockNode* currBlock;
// Stack to keep track of loop labels for break stmts
std::vector<std::string> loopEndLabels;

// Global variables for function parameter and argument handling
std::vector<std::pair<std::string, std::string>> currentParameters;
std::vector<std::unique_ptr<ASTNode>> currentArguments;
std::vector<std::pair<std::unique_ptr<ASTNode>, std::unique_ptr<BlockNode>>> caseexprs;
std::unique_ptr<BlockNode> defaultBlock = nullptr;

std::string curr_function_name = "";
std::string curr_function_type = "";
bool curr_func_return_shown = false;
bool function_declared = false;
int lable_num = 0;
std::stack<std::string> endLabelsStack;
std::stack<std::string> continueLabelsStack;
std::stack<int> loopCntStack;
int blockIdCounter = 0;
// Helper function to clear parameter list
void clearParameters() {
    currentParameters.clear();
}

// Helper function to add a parameter
void addParameter(const std::string& type, const std::string& name) {
    currentParameters.push_back(std::make_pair(type, name));
}

// Helper function to get and clear arguments
std::vector<std::unique_ptr<ASTNode>> getAndClearArguments() {
    std::vector<std::unique_ptr<ASTNode>> args;
    args.swap(currentArguments);
    return args;
}

#line 134 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_VALUE = 4,               /* STRING_VALUE  */
  YYSYMBOL_CHAR_VALUE = 5,                 /* CHAR_VALUE  */
  YYSYMBOL_INT_VALUE = 6,                  /* INT_VALUE  */
  YYSYMBOL_FLOAT_VALUE = 7,                /* FLOAT_VALUE  */
  YYSYMBOL_BOOL_VALUE = 8,                 /* BOOL_VALUE  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_STRING = 11,                    /* STRING  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_BOOL = 13,                      /* BOOL  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_CONSTANT = 15,                  /* CONSTANT  */
  YYSYMBOL_PRINT = 16,                     /* PRINT  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_LOGICAL_AND = 18,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 19,                /* LOGICAL_OR  */
  YYSYMBOL_LOGICAL_NOT = 20,               /* LOGICAL_NOT  */
  YYSYMBOL_EQUAL = 21,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 22,                 /* NOT_EQUAL  */
  YYSYMBOL_GT = 23,                        /* GT  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GTE = 25,                       /* GTE  */
  YYSYMBOL_LTE = 26,                       /* LTE  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_SEMICOLON = 28,                 /* SEMICOLON  */
  YYSYMBOL_MOD = 29,                       /* MOD  */
  YYSYMBOL_ADD = 30,                       /* ADD  */
  YYSYMBOL_SUB = 31,                       /* SUB  */
  YYSYMBOL_MUL = 32,                       /* MUL  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_BITWISE_XOR = 34,               /* BITWISE_XOR  */
  YYSYMBOL_BITWISE_OR = 35,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_AND = 36,               /* BITWISE_AND  */
  YYSYMBOL_SHL = 37,                       /* SHL  */
  YYSYMBOL_SHR = 38,                       /* SHR  */
  YYSYMBOL_SWITCH = 39,                    /* SWITCH  */
  YYSYMBOL_BREAK = 40,                     /* BREAK  */
  YYSYMBOL_CASE = 41,                      /* CASE  */
  YYSYMBOL_DEFAULT = 42,                   /* DEFAULT  */
  YYSYMBOL_IF = 43,                        /* IF  */
  YYSYMBOL_ELSE = 44,                      /* ELSE  */
  YYSYMBOL_FOR = 45,                       /* FOR  */
  YYSYMBOL_WHILE = 46,                     /* WHILE  */
  YYSYMBOL_DO = 47,                        /* DO  */
  YYSYMBOL_CONTINUE = 48,                  /* CONTINUE  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_50_ = 50,                       /* '{'  */
  YYSYMBOL_51_ = 51,                       /* '}'  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* ':'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_program = 57,                   /* program  */
  YYSYMBOL_BLOCK = 58,                     /* BLOCK  */
  YYSYMBOL_59_1 = 59,                      /* $@1  */
  YYSYMBOL_stmt = 60,                      /* stmt  */
  YYSYMBOL_expr = 61,                      /* expr  */
  YYSYMBOL_opt_else_if_stmt = 62,          /* opt_else_if_stmt  */
  YYSYMBOL_if_stmt = 63,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 64,                /* while_stmt  */
  YYSYMBOL_65_2 = 65,                      /* $@2  */
  YYSYMBOL_do_while_stmt = 66,             /* do_while_stmt  */
  YYSYMBOL_67_3 = 67,                      /* $@3  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_69_4 = 69,                      /* $@4  */
  YYSYMBOL_switch_stmt = 70,               /* switch_stmt  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_CASES = 72,                     /* CASES  */
  YYSYMBOL_case_stmt = 73,                 /* case_stmt  */
  YYSYMBOL_break_stmt = 74,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 75,             /* continue_stmt  */
  YYSYMBOL_print_stmt = 76,                /* print_stmt  */
  YYSYMBOL_type = 77,                      /* type  */
  YYSYMBOL_function_call_stmt = 78,        /* function_call_stmt  */
  YYSYMBOL_79_6 = 79,                      /* $@6  */
  YYSYMBOL_ARGUMENTS = 80,                 /* ARGUMENTS  */
  YYSYMBOL_81_7 = 81,                      /* $@7  */
  YYSYMBOL_function_declr_stmt = 82,       /* function_declr_stmt  */
  YYSYMBOL_83_8 = 83,                      /* $@8  */
  YYSYMBOL_ARGS = 84,                      /* ARGS  */
  YYSYMBOL_ARG_DECL = 85,                  /* ARG_DECL  */
  YYSYMBOL_return_stmt = 86,               /* return_stmt  */
  YYSYMBOL_assign_stmt = 87,               /* assign_stmt  */
  YYSYMBOL_declr_stmt = 88                 /* declr_stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   717

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,     2,     2,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   137,   142,   142,   156,   157,   158,   159,
     160,   161,   162,   163,   165,   166,   167,   168,   169,   170,
     172,   173,   180,   181,   182,   183,   184,   185,   187,   189,
     191,   194,   198,   202,   206,   210,   214,   218,   223,   227,
     231,   235,   239,   243,   248,   252,   257,   261,   265,   269,
     277,   280,   283,   289,   296,   296,   313,   313,   330,   330,
     368,   368,   389,   390,   394,   402,   413,   421,   430,   437,
     438,   439,   440,   441,   442,   447,   447,   458,   458,   462,
     466,   474,   474,   501,   502,   503,   507,   516,   523,   536,
     544,   549,   554,   559
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_VALUE", "CHAR_VALUE", "INT_VALUE", "FLOAT_VALUE", "BOOL_VALUE",
  "INT", "FLOAT", "STRING", "CHAR", "BOOL", "VOID", "CONSTANT", "PRINT",
  "RETURN", "LOGICAL_AND", "LOGICAL_OR", "LOGICAL_NOT", "EQUAL",
  "NOT_EQUAL", "GT", "LT", "GTE", "LTE", "EQ", "SEMICOLON", "MOD", "ADD",
  "SUB", "MUL", "DIV", "BITWISE_XOR", "BITWISE_OR", "BITWISE_AND", "SHL",
  "SHR", "SWITCH", "BREAK", "CASE", "DEFAULT", "IF", "ELSE", "FOR",
  "WHILE", "DO", "CONTINUE", "UMINUS", "'{'", "'}'", "'('", "')'", "':'",
  "','", "$accept", "program", "BLOCK", "$@1", "stmt", "expr",
  "opt_else_if_stmt", "if_stmt", "while_stmt", "$@2", "do_while_stmt",
  "$@3", "for_stmt", "$@4", "switch_stmt", "$@5", "CASES", "case_stmt",
  "break_stmt", "continue_stmt", "print_stmt", "type",
  "function_call_stmt", "$@6", "ARGUMENTS", "$@7", "function_declr_stmt",
  "$@8", "ARGS", "ARG_DECL", "return_stmt", "assign_stmt", "declr_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,   145,   -84,   -22,   -15,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   207,   -39,    15,    15,
      15,   -84,   -11,   -25,   -24,   -84,   -84,     2,   -84,    15,
     -84,   -84,   538,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,    30,   -84,   -84,     8,   -84,   -84,   -84,   -84,    15,
     -84,    35,    15,   -12,   622,   -84,   -84,   -10,   -84,    15,
     -84,    -9,    -5,   -84,   -84,   387,    15,    15,    15,    15,
      15,    15,    15,    15,   -84,    15,    15,    15,    15,    15,
      15,    15,    15,    15,    15,   -20,   -84,   559,    15,    -2,
     412,    15,   437,   299,    15,    -7,   195,   -84,   661,   643,
      55,    55,   100,   100,   100,   100,    13,    67,    67,    13,
      13,   -84,   679,   149,   198,   198,    15,   -84,   -84,   -84,
     334,    16,    15,   -84,    43,   462,    -5,   299,   487,    20,
     -84,   580,   207,   -84,   -84,   601,   -84,    24,    31,   299,
      -5,    15,   -84,    74,    37,    28,    15,   -84,   -84,   -34,
     -84,    41,   -84,   512,   -84,    -5,   207,   -84,   -27,   -84,
     -84,    45,    75,   -84,   -84,    15,    48,   -84,   -84,   -84,
     -84,   361,    -5,   247,    -5,   -84,   -84,   -84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     1,     0,    22,    26,    27,    23,    24,    25,
      69,    70,    72,    73,    71,    74,     0,     0,    87,     0,
       0,    60,     0,     0,     0,    54,    56,     0,     4,     0,
      15,     2,     0,     9,    10,    11,    12,    18,    13,    19,
      14,     0,    29,    17,     0,     7,     6,    20,    21,     0,
      75,     0,     0,    22,    88,    31,    30,     0,    66,     0,
      58,     0,     0,    67,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    80,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    39,    38,
      44,    45,    46,    47,    48,    49,    37,    32,    33,    34,
      35,    36,    40,    41,    42,    43,     0,    91,    81,    89,
      79,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       5,     0,    85,    77,    76,     0,    68,     0,    52,     0,
       0,     0,    90,     0,     0,    84,    80,    92,    63,     0,
      53,     0,    55,     0,    86,     0,    85,    78,     0,    50,
      51,     0,     0,    82,    83,     0,     0,    61,    62,     3,
      57,     0,     0,     0,     0,    65,    59,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -59,   -58,   -84,   -83,   -18,   -84,   -44,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -13,   -84,   -84,   -40,   -84,   -84,   -84,   -49,   -84,
     -84,   -84,   -84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    30,    64,    31,    32,   150,    33,    34,    61,
      35,    62,    36,    93,    37,    57,   158,   168,    38,    39,
      40,    41,    42,    88,   121,   146,    43,   132,   144,   145,
      44,    45,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      54,    55,    56,    51,    95,    96,    47,   116,   117,    23,
     127,    65,    49,    52,   165,   166,    28,    58,    53,     5,
       6,     7,     8,     9,   167,   122,   123,    59,    60,    48,
      63,    87,   118,    85,    90,    19,    86,    50,    89,   129,
      50,    92,    91,    94,   139,    28,    20,    80,    98,    99,
     100,   101,   102,   103,   104,   105,   151,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    29,   138,   134,
     120,   136,   141,   125,   148,   149,   128,   154,    70,    71,
      72,    73,   152,   156,    75,    76,    77,    78,    79,    80,
     155,   159,    83,    84,   161,   169,    75,   163,   131,    78,
      79,    80,   172,   170,   135,   160,   157,   164,     0,     0,
     173,     0,     0,     0,   175,     0,   177,     0,     0,   143,
       0,     0,     0,   153,     0,     0,     0,     0,   120,    75,
      76,    77,    78,    79,    80,     0,     0,    83,    84,     0,
       0,     0,     0,   143,     0,     2,     3,   171,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,    19,     0,     0,     0,     0,
      68,    69,    70,    71,    72,    73,    20,     0,    75,    76,
      77,    78,    79,    80,    21,    22,    83,    84,    23,     0,
      24,    25,    26,    27,     0,    28,     3,    29,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,     0,     0,    19,    10,    11,    12,    13,
      14,    15,     0,     0,     0,     0,    20,    75,    76,    77,
      78,    79,    80,     0,    21,    22,     0,     0,    23,     0,
      24,    25,    26,    27,     0,    28,   130,    29,     3,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,     0,     0,     0,    21,    22,     0,     0,
      23,     0,    24,    25,    26,    27,     0,    28,   176,    29,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,     0,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,    21,    22,
       0,     0,    23,     0,    24,    25,    26,    27,     0,    28,
       0,    29,    66,    67,     0,    68,    69,    70,    71,    72,
      73,     0,     0,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,     0,     0,    66,
      67,     0,    68,    69,    70,    71,    72,    73,     0,   133,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,     0,     0,     0,     0,    66,    67,     0,    68,    69,
      70,    71,    72,    73,     0,   174,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,     0,     0,
      66,    67,     0,    68,    69,    70,    71,    72,    73,     0,
      97,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,    66,    67,     0,    68,    69,
      70,    71,    72,    73,     0,   124,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,     0,     0,
      66,    67,     0,    68,    69,    70,    71,    72,    73,     0,
     126,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,    66,    67,     0,    68,    69,
      70,    71,    72,    73,     0,   137,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,     0,     0,     0,
      66,    67,     0,    68,    69,    70,    71,    72,    73,     0,
     140,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,     0,    66,    67,     0,    68,
      69,    70,    71,    72,    73,   162,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    66,    67,     0,
      68,    69,    70,    71,    72,    73,     0,   119,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    66,    67,
       0,    68,    69,    70,    71,    72,    73,     0,   142,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    66,
      67,     0,    68,    69,    70,    71,    72,    73,     0,   147,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      66,    67,     0,    68,    69,    70,    71,    72,    73,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    66,     0,     0,    68,    69,    70,    71,    72,    73,
       0,     0,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    68,    69,    70,    71,    72,    73,     0,     0,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      68,    69,    70,    71,    72,    73,     0,     0,    75,    76,
      77,    78,    79,    80,     0,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
      18,    19,    20,    16,    62,    64,    28,    27,    28,    43,
      93,    29,    27,    52,    41,    42,    50,    28,     3,     4,
       5,     6,     7,     8,    51,    27,    28,    52,    52,    51,
      28,    49,    52,     3,    52,    20,    28,    52,     3,    46,
      52,    59,    52,    52,   127,    50,    31,    34,    66,    67,
      68,    69,    70,    71,    72,    73,   139,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    52,   126,    53,
      88,    28,    52,    91,    50,    44,    94,     3,    23,    24,
      25,    26,   140,    55,    29,    30,    31,    32,    33,    34,
      53,   149,    37,    38,    53,    50,    29,   155,   116,    32,
      33,    34,    54,    28,   122,   149,   146,   156,    -1,    -1,
     169,    -1,    -1,    -1,   172,    -1,   174,    -1,    -1,   132,
      -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,   146,    29,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    -1,
      -1,    -1,    -1,   156,    -1,     0,     1,   165,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      21,    22,    23,    24,    25,    26,    31,    -1,    29,    30,
      31,    32,    33,    34,    39,    40,    37,    38,    43,    -1,
      45,    46,    47,    48,    -1,    50,     1,    52,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    31,    29,    30,    31,
      32,    33,    34,    -1,    39,    40,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    -1,    50,    51,    52,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      43,    -1,    45,    46,    47,    48,    -1,    50,    51,    52,
       1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    -1,    50,
      -1,    52,    18,    19,    -1,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    -1,    21,    22,    23,    24,    25,    26,    -1,    55,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,    22,
      23,    24,    25,    26,    -1,    54,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      53,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,    22,
      23,    24,    25,    26,    -1,    53,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      53,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,    22,
      23,    24,    25,    26,    -1,    53,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      53,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,
      22,    23,    24,    25,    26,    53,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    18,    19,    -1,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    18,    19,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    18,
      19,    -1,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    18,    -1,    -1,    21,    22,    23,    24,    25,    26,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    57,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    20,
      31,    39,    40,    43,    45,    46,    47,    48,    50,    52,
      58,    60,    61,    63,    64,    66,    68,    70,    74,    75,
      76,    77,    78,    82,    86,    87,    88,    28,    51,    27,
      52,    77,    52,     3,    61,    61,    61,    71,    28,    52,
      52,    65,    67,    28,    59,    61,    18,    19,    21,    22,
      23,    24,    25,    26,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     3,    28,    61,    79,     3,
      61,    52,    61,    69,    52,    58,    57,    53,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    27,    28,    52,    28,
      61,    80,    27,    28,    53,    61,    53,    60,    61,    46,
      51,    61,    83,    55,    53,    61,    28,    53,    58,    60,
      53,    52,    28,    77,    84,    85,    81,    28,    50,    44,
      62,    60,    58,    61,     3,    53,    55,    80,    72,    58,
      63,    53,    53,    58,    84,    41,    42,    51,    73,    50,
      28,    61,    54,    57,    54,    58,    51,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    57,    59,    58,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    62,    63,    65,    64,    67,    66,    69,    68,
      71,    70,    72,    72,    73,    73,    74,    75,    76,    77,
      77,    77,    77,    77,    77,    79,    78,    81,    80,    80,
      80,    83,    82,    84,    84,    84,    85,    86,    86,    87,
      88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     0,     4,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     0,     6,     0,     6,     0,     8,     0,    10,
       0,     8,     2,     0,     4,     3,     2,     2,     5,     1,
       1,     1,     1,     1,     1,     0,     5,     0,     4,     1,
       0,     0,     7,     3,     1,     0,     2,     1,     2,     4,
       5,     3,     6,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: program stmt  */
#line 131 "src/parser.ypp"
                      { 
            if ((yyvsp[0].node) != nullptr) {
                currBlock->addStatement(std::unique_ptr<ASTNode>((yyvsp[0].node))); 
            }
            (yyval.node) = nullptr;
        }
#line 1713 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 3: /* program: %empty  */
#line 137 "src/parser.ypp"
          { (yyval.node) = nullptr; }
#line 1719 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 4: /* $@1: %empty  */
#line 142 "src/parser.ypp"
            {
            // Create a new block with the current block as parent
            BlockNode* newBlock = new BlockNode(++blockIdCounter, currBlock);
            currBlock = newBlock;
        }
#line 1729 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 5: /* BLOCK: '{' $@1 program '}'  */
#line 146 "src/parser.ypp"
                      {
            // Set the result to the current block
            (yyval.blockNode) = currBlock;
            // Restore parent block
            currBlock = currBlock->getParent();
        }
#line 1740 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 6: /* stmt: declr_stmt  */
#line 156 "src/parser.ypp"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1746 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 7: /* stmt: assign_stmt  */
#line 157 "src/parser.ypp"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1752 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 8: /* stmt: expr SEMICOLON  */
#line 158 "src/parser.ypp"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1758 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 9: /* stmt: if_stmt  */
#line 159 "src/parser.ypp"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1764 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 10: /* stmt: while_stmt  */
#line 160 "src/parser.ypp"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1770 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 11: /* stmt: do_while_stmt  */
#line 161 "src/parser.ypp"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1776 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 12: /* stmt: for_stmt  */
#line 162 "src/parser.ypp"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1782 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 13: /* stmt: break_stmt  */
#line 163 "src/parser.ypp"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1788 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 14: /* stmt: print_stmt  */
#line 165 "src/parser.ypp"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1794 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 15: /* stmt: BLOCK  */
#line 166 "src/parser.ypp"
                { (yyval.node) = (yyvsp[0].blockNode); }
#line 1800 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 16: /* stmt: return_stmt SEMICOLON  */
#line 167 "src/parser.ypp"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1806 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 17: /* stmt: function_declr_stmt  */
#line 168 "src/parser.ypp"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1812 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 18: /* stmt: switch_stmt  */
#line 169 "src/parser.ypp"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1818 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 19: /* stmt: continue_stmt  */
#line 170 "src/parser.ypp"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1824 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 20: /* stmt: error SEMICOLON  */
#line 172 "src/parser.ypp"
                          { yyerrok; yyclearin; (yyval.node) = NULL; }
#line 1830 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 21: /* stmt: error '}'  */
#line 173 "src/parser.ypp"
                    { yyerrok; yyclearin; (yyval.node) = NULL; }
#line 1836 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 22: /* expr: IDENTIFIER  */
#line 180 "src/parser.ypp"
                      { (yyval.node) = new IdentifierNode(*(yyvsp[0].strVal), currBlock, yylineno); delete (yyvsp[0].strVal); }
#line 1842 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 23: /* expr: INT_VALUE  */
#line 181 "src/parser.ypp"
                      { (yyval.node) = new LiteralNode("int", std::to_string((yyvsp[0].intVal))); }
#line 1848 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 24: /* expr: FLOAT_VALUE  */
#line 182 "src/parser.ypp"
                      { (yyval.node) = new LiteralNode("float", std::to_string((yyvsp[0].floatVal))); }
#line 1854 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 25: /* expr: BOOL_VALUE  */
#line 183 "src/parser.ypp"
                      { (yyval.node) = new LiteralNode("bool", (yyvsp[0].boolVal) ? "true" : "false"); }
#line 1860 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 26: /* expr: STRING_VALUE  */
#line 184 "src/parser.ypp"
                       { (yyval.node) = new LiteralNode("string", *(yyvsp[0].strVal)); delete (yyvsp[0].strVal); }
#line 1866 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 27: /* expr: CHAR_VALUE  */
#line 185 "src/parser.ypp"
                      { (yyval.node) = new LiteralNode("char", std::string(1, (yyvsp[0].charVal))); }
#line 1872 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 28: /* expr: '(' expr ')'  */
#line 187 "src/parser.ypp"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 1878 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 29: /* expr: function_call_stmt  */
#line 189 "src/parser.ypp"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1884 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 30: /* expr: SUB expr  */
#line 191 "src/parser.ypp"
                                 { 
            (yyval.node) = new UnaryOpNode("-", std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1892 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 31: /* expr: LOGICAL_NOT expr  */
#line 194 "src/parser.ypp"
                           {
            (yyval.node) = new UnaryOpNode("!", std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1900 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 32: /* expr: expr ADD expr  */
#line 198 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("+", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1909 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 33: /* expr: expr SUB expr  */
#line 202 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("-", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1918 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 34: /* expr: expr MUL expr  */
#line 206 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("*", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1927 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 35: /* expr: expr DIV expr  */
#line 210 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("/", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1936 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 36: /* expr: expr BITWISE_XOR expr  */
#line 214 "src/parser.ypp"
                                {
            (yyval.node) = new BinaryOpNode("^", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1945 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 37: /* expr: expr MOD expr  */
#line 218 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("%", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1954 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 38: /* expr: expr LOGICAL_OR expr  */
#line 223 "src/parser.ypp"
                               {
            (yyval.node) = new BinaryOpNode("||", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                  std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1963 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 39: /* expr: expr LOGICAL_AND expr  */
#line 227 "src/parser.ypp"
                                {
            (yyval.node) = new BinaryOpNode("&&", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                  std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1972 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 40: /* expr: expr BITWISE_OR expr  */
#line 231 "src/parser.ypp"
                               {
            (yyval.node) = new BinaryOpNode("|", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1981 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 41: /* expr: expr BITWISE_AND expr  */
#line 235 "src/parser.ypp"
                                {
            (yyval.node) = new BinaryOpNode("&", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1990 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 42: /* expr: expr SHL expr  */
#line 239 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("<<", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 1999 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 43: /* expr: expr SHR expr  */
#line 243 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode(">>", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2008 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 44: /* expr: expr EQUAL expr  */
#line 248 "src/parser.ypp"
                          {
            (yyval.node) = new BinaryOpNode("==", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2017 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 45: /* expr: expr NOT_EQUAL expr  */
#line 252 "src/parser.ypp"
                              {
            (yyval.node) = new BinaryOpNode("!=", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2026 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 46: /* expr: expr GT expr  */
#line 257 "src/parser.ypp"
                       {
            (yyval.node) = new BinaryOpNode(">", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2035 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 47: /* expr: expr LT expr  */
#line 261 "src/parser.ypp"
                       {
            (yyval.node) = new BinaryOpNode("<", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2044 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 48: /* expr: expr GTE expr  */
#line 265 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode(">=", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2053 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 49: /* expr: expr LTE expr  */
#line 269 "src/parser.ypp"
                        {
            (yyval.node) = new BinaryOpNode("<=", std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                 std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2062 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 50: /* opt_else_if_stmt: ELSE BLOCK  */
#line 277 "src/parser.ypp"
                   {
            (yyval.node) = (yyvsp[0].blockNode);
        }
#line 2070 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 51: /* opt_else_if_stmt: ELSE if_stmt  */
#line 280 "src/parser.ypp"
                       {
            (yyval.node) = (yyvsp[0].node);
        }
#line 2078 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 52: /* opt_else_if_stmt: %empty  */
#line 283 "src/parser.ypp"
          {
            (yyval.node) = nullptr;
        }
#line 2086 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 53: /* if_stmt: IF '(' expr ')' BLOCK opt_else_if_stmt  */
#line 289 "src/parser.ypp"
                                               {
            (yyval.node) = new IfNode(std::unique_ptr<ASTNode>((yyvsp[-3].node)), std::unique_ptr<BlockNode>((yyvsp[-1].blockNode)), std::unique_ptr<ASTNode>((yyvsp[0].node)), yylineno);
        }
#line 2094 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 54: /* $@2: %empty  */
#line 296 "src/parser.ypp"
              { 
            endLabelsStack.push("while_" + std::to_string(lable_num) + "_end"); 
            continueLabelsStack.push("while_" + std::to_string(lable_num) + "_start");
            loopCntStack.push(lable_num);
            lable_num++; }
#line 2104 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 55: /* while_stmt: WHILE $@2 '(' expr ')' BLOCK  */
#line 300 "src/parser.ypp"
                                              {
            (yyval.node) = new WhileNode(std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                              std::unique_ptr<BlockNode>((yyvsp[0].blockNode)), 
                              loopCntStack.top(),
                              yylineno);
            endLabelsStack.pop();
            continueLabelsStack.pop();
            loopCntStack.pop();
        }
#line 2118 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 56: /* $@3: %empty  */
#line 313 "src/parser.ypp"
           { 
            endLabelsStack.push("do_while_" + std::to_string(lable_num) + "_end");
            continueLabelsStack.push("do_while_" + std::to_string(lable_num) + "_cond");
            loopCntStack.push(lable_num); 
            lable_num++; }
#line 2128 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 57: /* do_while_stmt: DO $@3 BLOCK WHILE '(' expr ')' SEMICOLON  */
#line 317 "src/parser.ypp"
                                                              {
            (yyval.node) = new DoWhileNode(std::unique_ptr<BlockNode>((yyvsp[-5].blockNode)), 
                                std::unique_ptr<ASTNode>((yyvsp[-2].node)), 
                                loopCntStack.top(),
                                yylineno);
            endLabelsStack.pop();
            continueLabelsStack.pop();
            loopCntStack.pop();
        }
#line 2142 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 58: /* $@4: %empty  */
#line 330 "src/parser.ypp"
            {
        // Create a new block for the for loop (both parentheses stmts and body)
        BlockNode* newBlock = new BlockNode(++blockIdCounter, currBlock);
        currBlock = newBlock;
        endLabelsStack.push("for_" + std::to_string(lable_num) + "_end"); 
        continueLabelsStack.push("for_" + std::to_string(lable_num) + "_update");
        loopCntStack.push(lable_num);
        lable_num++;
    }
#line 2156 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 59: /* for_stmt: FOR '(' $@4 stmt stmt stmt ')' '{' program '}'  */
#line 341 "src/parser.ypp"
                    {
        // Store the for loop stmts
        std::unique_ptr<ASTNode> initStmt((yyvsp[-6].node));
        std::unique_ptr<ASTNode> condStmt((yyvsp[-5].node));
        std::unique_ptr<ASTNode> updateStmt((yyvsp[-4].node));
        
        // Use the current block for the body
        BlockNode* bodyBlock = currBlock;
        
        // Restore parent block
        currBlock = currBlock->getParent();
        
        // Create the ForNode
        (yyval.node) = new ForNode(std::move(initStmt), 
                         std::move(condStmt), 
                         std::move(updateStmt), 
                         std::unique_ptr<BlockNode>(bodyBlock), 
                         loopCntStack.top(),
                         yylineno);
        endLabelsStack.pop();
        continueLabelsStack.pop();
        loopCntStack.pop();
    }
#line 2184 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 60: /* $@5: %empty  */
#line 368 "src/parser.ypp"
           {
        // Clear previous case collections
        caseexprs.clear();
        defaultBlock = nullptr;
        
        // Push the end label for the switch (used by break stmts)
        endLabelsStack.push("switch_" + std::to_string(lable_num) + "_end"); 
        lable_num++;
    }
#line 2198 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 61: /* switch_stmt: SWITCH $@5 '(' expr ')' '{' CASES '}'  */
#line 376 "src/parser.ypp"
                                 {
        // Create the switch node with collected cases
        (yyval.node) = new SwitchNode(std::unique_ptr<ASTNode>((yyvsp[-4].node)), 
                           std::move(caseexprs), 
                           std::move(defaultBlock),
                           endLabelsStack.top(),
                           currBlock,
                           yylineno);
        endLabelsStack.pop();
    }
#line 2213 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 64: /* case_stmt: CASE expr ':' BLOCK  */
#line 394 "src/parser.ypp"
                        {
        // Add case to the collection
        caseexprs.push_back(std::make_pair(
            std::unique_ptr<ASTNode>((yyvsp[-2].node)),
            std::unique_ptr<BlockNode>((yyvsp[0].blockNode))
        ));
        (yyval.node) = nullptr; // No need to return a value for this rule
    }
#line 2226 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 65: /* case_stmt: DEFAULT ':' BLOCK  */
#line 402 "src/parser.ypp"
                        {
        if(defaultBlock != nullptr) {
            ErrorHandler::getInstance()->reportError("Default Case already exist", yylineno);
        }
        // Set default case
        defaultBlock = std::unique_ptr<BlockNode>((yyvsp[0].blockNode));
        (yyval.node) = nullptr; // No need to return a value for this rule
    }
#line 2239 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 66: /* break_stmt: BREAK SEMICOLON  */
#line 413 "src/parser.ypp"
                        { 
            if(!endLabelsStack.empty()) (yyval.node) = new BreakNode(endLabelsStack.top(), yylineno); 
            else ErrorHandler::getInstance()->reportError("Break outside of a loop", yylineno);
            }
#line 2248 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 67: /* continue_stmt: CONTINUE SEMICOLON  */
#line 421 "src/parser.ypp"
                           { 
            if(!continueLabelsStack.empty()) (yyval.node) = new ContinueNode(continueLabelsStack.top(), yylineno); 
            else ErrorHandler::getInstance()->reportError("Continue outside of a loop", yylineno);
            
            }
#line 2258 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 68: /* print_stmt: PRINT '(' expr ')' SEMICOLON  */
#line 430 "src/parser.ypp"
                                     {
            (yyval.node) = new PrintNode(std::unique_ptr<ASTNode>((yyvsp[-2].node)));
        }
#line 2266 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 69: /* type: INT  */
#line 437 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("int");   }
#line 2272 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 70: /* type: FLOAT  */
#line 438 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("float"); }
#line 2278 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 71: /* type: BOOL  */
#line 439 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("bool");  }
#line 2284 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 72: /* type: STRING  */
#line 440 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("string");}
#line 2290 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 73: /* type: CHAR  */
#line 441 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("char");  }
#line 2296 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 74: /* type: VOID  */
#line 442 "src/parser.ypp"
                    { (yyval.strVal) = new std::string("void");  }
#line 2302 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 75: /* $@6: %empty  */
#line 447 "src/parser.ypp"
                   {
        // Clear the arguments vector before starting to collect arguments
        currentArguments.clear();
    }
#line 2311 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 76: /* function_call_stmt: IDENTIFIER '(' $@6 ARGUMENTS ')'  */
#line 450 "src/parser.ypp"
                    {
        // Create the function call node with collected arguments
        (yyval.node) = new FunctionCallNode(*(yyvsp[-4].strVal), getAndClearArguments(), currBlock, yylineno);
        delete (yyvsp[-4].strVal);
    }
#line 2321 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 77: /* $@7: %empty  */
#line 458 "src/parser.ypp"
             {
        // Store the expr as an argument
        currentArguments.push_back(std::unique_ptr<ASTNode>((yyvsp[-1].node)));
    }
#line 2330 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 79: /* ARGUMENTS: expr  */
#line 462 "src/parser.ypp"
           {
        // Store the last expr as an argument
        currentArguments.push_back(std::unique_ptr<ASTNode>((yyvsp[0].node)));
    }
#line 2339 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 80: /* ARGUMENTS: %empty  */
#line 466 "src/parser.ypp"
                  {
        // No arguments
    }
#line 2347 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 81: /* $@8: %empty  */
#line 474 "src/parser.ypp"
                        {
        // Clear parameters before collecting new ones
        curr_function_name = *(yyvsp[-1].strVal);
        curr_function_type = *(yyvsp[-2].strVal);
        function_declared = true;
        if(currBlock->getParent() != nullptr) {
            ErrorHandler::getInstance()->reportError("Function " + curr_function_name + " should be global", yylineno);
        }
        clearParameters();
    }
#line 2362 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 82: /* function_declr_stmt: type IDENTIFIER '(' $@8 ARGS ')' BLOCK  */
#line 483 "src/parser.ypp"
                     {

        if(!curr_func_return_shown && curr_function_type != "void") {
            ErrorHandler::getInstance()->reportError("Function " + curr_function_name + " should return " + curr_function_type, yylineno);            
        }
        // Cre  ate the function declaration node with collected parameters
        (yyval.node) = new FunctionDeclarationNode(*(yyvsp[-6].strVal), *(yyvsp[-5].strVal), currentParameters, 
                                       std::unique_ptr<BlockNode>((yyvsp[0].blockNode)), 
                                       currBlock, yylineno);
        curr_func_return_shown = false;
        curr_function_name = "";
        curr_function_type = "";
        function_declared = false;
        delete (yyvsp[-6].strVal);
        delete (yyvsp[-5].strVal);
    }
#line 2383 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 86: /* ARG_DECL: type IDENTIFIER  */
#line 507 "src/parser.ypp"
                    {
        // Add parameter to the current parameter list
        addParameter(*(yyvsp[-1].strVal), *(yyvsp[0].strVal));
        delete (yyvsp[-1].strVal);
        delete (yyvsp[0].strVal);
    }
#line 2394 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 87: /* return_stmt: RETURN  */
#line 516 "src/parser.ypp"
           {
        if(!function_declared) {
            ErrorHandler::getInstance()->reportError("NO function has been declared", yylineno);
        }
        curr_func_return_shown = true;
        (yyval.node) = new ReturnNode(nullptr, currBlock, curr_function_type, yylineno);
    }
#line 2406 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 88: /* return_stmt: RETURN expr  */
#line 523 "src/parser.ypp"
                  {
        // Return with expr
        if(!function_declared) {
            ErrorHandler::getInstance()->reportError("NO function has been declared", yylineno);
        }
        curr_func_return_shown = true;

        (yyval.node) = new ReturnNode(std::unique_ptr<ASTNode>((yyvsp[0].node)), currBlock, curr_function_type, yylineno);
    }
#line 2420 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 89: /* assign_stmt: IDENTIFIER EQ expr SEMICOLON  */
#line 536 "src/parser.ypp"
                                     { 
            (yyval.node) = new AssignmentNode(*(yyvsp[-3].strVal), std::unique_ptr<ASTNode>((yyvsp[-1].node)), currBlock, yylineno);
            delete (yyvsp[-3].strVal);
        }
#line 2429 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 90: /* declr_stmt: type IDENTIFIER EQ expr SEMICOLON  */
#line 544 "src/parser.ypp"
                                          { 
            (yyval.node) = new DeclarationNode(*(yyvsp[-4].strVal), *(yyvsp[-3].strVal), false, std::unique_ptr<ASTNode>((yyvsp[-1].node)), currBlock, yylineno);
            delete (yyvsp[-4].strVal);
            delete (yyvsp[-3].strVal);
        }
#line 2439 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 91: /* declr_stmt: type IDENTIFIER SEMICOLON  */
#line 549 "src/parser.ypp"
                                    { 
            (yyval.node) = new DeclarationNode(*(yyvsp[-2].strVal), *(yyvsp[-1].strVal), false, nullptr, currBlock, yylineno);
            delete (yyvsp[-2].strVal);
            delete (yyvsp[-1].strVal);
        }
#line 2449 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 92: /* declr_stmt: CONSTANT type IDENTIFIER EQ expr SEMICOLON  */
#line 554 "src/parser.ypp"
                                                     { 
            (yyval.node) = new DeclarationNode(*(yyvsp[-4].strVal), *(yyvsp[-3].strVal), true, std::unique_ptr<ASTNode>((yyvsp[-1].node)), currBlock, yylineno);
            delete (yyvsp[-4].strVal);
            delete (yyvsp[-3].strVal);
        }
#line 2459 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;

  case 93: /* declr_stmt: CONSTANT type IDENTIFIER SEMICOLON  */
#line 559 "src/parser.ypp"
                                             { 
            ErrorHandler::getInstance()->reportError("Error declaring const variable without initialization", yylineno);
        }
#line 2467 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"
    break;


#line 2471 "/home/malek/work/zcompi/calculator/build/build/parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 564 "src/parser.ypp"
