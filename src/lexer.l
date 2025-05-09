%{
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
    #include <string>
    #include "parser.tab.hpp"
    // External functions for column tracking
    extern void update_column();
    extern void reset_column();
%}
%option yylineno
%option noyywrap
%%
\/\/[\s\t]*.*[\s\t]* { update_column(); }

"int"      { update_column(); return INT; }
"float"    { update_column(); return FLOAT; }
"string"   { update_column(); return STRING; }
"char"     { update_column(); return CHAR; }
"bool"     { update_column(); return BOOL; }

"print"    { update_column(); return PRINT; }
"void"     { update_column(); return VOID; }
"const"    { update_column(); return CONSTANT; }

"switch"   { update_column(); return SWITCH; }
"break"    { update_column(); return BREAK; }
"continue" { update_column(); return CONTINUE; }

"case"     { update_column(); return CASE; }
"default"  { update_column(); return DEFAULT; }

return     { update_column(); return RETURN; }

"if"       { update_column(); return IF; }
"else"     { update_column(); return ELSE; }

"for"      { update_column(); return FOR; }
"while"    { update_column(); return WHILE; }
"do"       { update_column(); return DO; }

"true"     { update_column(); yylval.boolVal = true; return BOOL_VALUE; }
"false"    { update_column(); yylval.boolVal = false; return BOOL_VALUE; }     

"&&"       { update_column(); return LOGICAL_AND; }
"||"       { update_column(); return LOGICAL_OR; }
"!"        { update_column(); return LOGICAL_NOT; }

"=="       { update_column(); return EQUAL; }
"!="       { update_column(); return NOT_EQUAL; }

">"        { update_column(); return GT; }
"<"        { update_column(); return LT; }
">="       { update_column(); return GTE; }
"<="       { update_column(); return LTE; }

"="        { update_column(); return EQ; }         
";"        { update_column(); return SEMICOLON; }

"%"        { update_column(); return MOD; }
"+"        { update_column(); return ADD; }
"-"        { update_column(); return SUB; }
"*"        { update_column(); return MUL; }
"/"        { update_column(); return DIV; }

"^"        { update_column(); return BITWISE_XOR; }
"|"        { update_column(); return BITWISE_OR; }
"&"        { update_column(); return BITWISE_AND; }
"<<"       { update_column(); return SHL; }
">>"       { update_column(); return SHR; }


[){}(:,]   { update_column(); return *yytext; }
[a-zA-Z_][a-zA-Z0-9_]* { update_column(); yylval.strVal = new std::string(yytext); return IDENTIFIER; }

\'.\'      { update_column(); yylval.charVal = yytext[1]; return CHAR_VALUE; }
\"([^\"\\]|\\.)*\"   { update_column(); yylval.strVal = new std::string(yytext + 1, strlen(yytext) - 2); return STRING_VALUE; }

[0-9]+     { update_column(); yylval.intVal = atoi(yytext); return INT_VALUE; }
[0-9]+\.[0-9]+ { update_column(); yylval.floatVal = atof(yytext); return FLOAT_VALUE; }

[ \t]+     { update_column(); }
\n         { reset_column(); }
.          { update_column(); return *yytext; }
%%