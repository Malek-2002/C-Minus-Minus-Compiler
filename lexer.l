%{
    #include "handler.hpp"
    #include<string>
    #include "parser.tab.hpp"
%}
%option yylineno
%option noyywrap
%%
\/\/[\s\t]*.*[\s\t]* 

"int"      {return INT;}
"float"    {return FLOAT;}
"string"   {return STRING;}
"char"     {return CHAR;}
"bool"     {return BOOL;}

"print"    {return PRINT;}
"void"     {return VOID;}

"switch"   {return SWITCH;}
"break"    {return BREAK;}

"case"     {return CASE;}
"default"  {return DEFAULT;}

return {return RETURN;}

"if"       {return IF;}
"else"     {return ELSE;}

"for"      {return FOR;}
"while"    {return WHILE;}
"do"       {return DO;}

"true"     {yylval.boolVal = true; return BOOL_VALUE;}
"false"    {yylval.boolVal = false;return BOOL_VALUE;}     

"&&"      {return LOGICAL_AND;}
"||"       {return LOGICAL_OR;}
"!"        {return LOGICAL_NOT;}

"=="       {return EQUAL;}
"!="       {return NOT_EQUAL;}

">"        {return GT;}
"<"        {return LT;}

"="        {return EQ;}         
";"        {return SEMICOLON;}

"%"        {return MOD;}
"+"        {return ADD;}
"-"        {return SUB;}
"*"        {return MUL;}
"/"        {return DIV;}
"^"        {return POW;}

"|"        {return BITWISE_OR;}
"&"        {return BITWISE_AND;}
"<<"       {return SHL;}
">>"       {return SHR;}


[){}(:,]               {return *yytext;}
[a-zA-Z_][a-zA-Z0-9_]* {yylval.strVal = new std::string(yytext); return IDENTIFIER;}

\'.\'         {yylval.charVal = yytext[1]; return CHAR_VALUE;}
\".*\"        {yylval.strVal = new std::string(yytext + 1, strlen(yytext) - 2); return STRING_VALUE;}

[0-9]+         {yylval.intVal = atoi(yytext); return INT_VALUE;}
[0-9]+\.[0-9]+ {yylval.floatVal = atof(yytext);return FLOAT_VALUE;}

[ \t]+
\n
.              {return *yytext;}
%%