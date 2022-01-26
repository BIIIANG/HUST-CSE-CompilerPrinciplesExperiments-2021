%{
#include "string.h"
#include "def.h"

extern int yycolumn;

#define YYSTYPE yylval
extern "C"
{	
	int yywrap(void);
	int yylex(void);
}

void flexout(std::string name,std::string value){
  std::cout << name << "\t:" << value << std::endl;
}
%}
%option yylineno

RELOP       "<"|">"|">="|"<="|"=="|"!="
ID          [A-Za-z][A-Za-z0-9]*
INT	        [\-]?[1-9][0-9]*|0
HEX         0[Xx][0-9a-fA-F]+
OCT         0[0-7]+
ILHEX       0[Xx][0-9a-fA-F]*[G-Zg-z]+[A-Za-z0-9]*
ILOCT       0[0-7]*[8-9A-Za-z]+[A-Za-z0-9]*
FLOAT       [-+]?[0-9]*\.[0-9]+
SCIEN       [-+]?[0-9]?[\.[0-9]*]?[Ee]{1}[-+]?[0-9]+

%%

"int"       { flexout("TYPE", yytext); }
"float"	    { flexout("TYPE", yytext); }
"char"      { flexout("TYPE", yytext); }
{RELOP}     { flexout("RELOP", yytext); }
"++"        { flexout("PLUSPLUS", yytext); }
"--"        { flexout("MINUSMINUS", yytext); }
"+="        { flexout("PLUSASS", yytext); }
"-="        { flexout("MINUSASS", yytext); }
";"	        { flexout("SEMI", yytext); }
","	        { flexout("COMMA", yytext); }
"="	        { flexout("ASSIGNOP", yytext); }
"+"	        { flexout("PLUS", yytext); }
"-"	        { flexout("MINUS", yytext); }
"*"	        { flexout("STAR", yytext); }
"/"	        { flexout("DIV", yytext); }
"&&"        { flexout("AND", yytext); }
"||"        { flexout("OR", yytext); }
"."	        { flexout("DOT", yytext); }
"!"	        { flexout("NOT", yytext); }
"("	        { flexout("LP", yytext); }
")"	        { flexout("RP", yytext); }
"["	        { flexout("LB", yytext); }
"]"	        { flexout("RB", yytext); }
"{"	        { flexout("LC", yytext); }
"}"	        { flexout("RC", yytext); }
"struct"    { flexout("STRUCT", yytext); }
"return"    { flexout("RETURN", yytext); }
"if"        { flexout("IF", yytext); }
"else"      { flexout("ELSE", yytext); }
"while"     { flexout("WHILE", yytext); }
{ID}        { flexout("ID", yytext); }
{INT}       { flexout("INT", yytext); }
{HEX}       { flexout("INT", yytext); }
{OCT}       { flexout("INT", yytext); }
{FLOAT}     { flexout("FLOAT", yytext); }
{SCIEN}     { flexout("FLOAT", yytext); }
  

[\n]        { yycolumn=1; }
[ \r\t]	    { /*printf("过滤空格等字符\n");*/ }

{ILHEX}     { printf("Error type A at Line %d: Illegal hexadecimal number \'%s\'\n", yylineno, yytext); }
{ILOCT}     { printf("Error type A at Line %d: Illegal octal number \'%s\'\n", yylineno, yytext); }
.           { printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); }

%%

int yywrap()
{
    return 1;
}
