%{
#include <stdio.h>
#include "1.7.Bison-InfixNotationCalc.tab.h"
%}

NUM             [1-9][0-9]*|0
EOL             \n
ADD			    \+
SUB			    \-
MUL			    \*
DIV			    \/
EXP             \^
LP    			\(
RP  			\)

%%  
{NUM}           { yylval = atoi(yytext); printf("Type(%d):NUM Val=%s\n", NUM, yytext); return NUM; }
{EOL}           { return EOL; }
{ADD}           { printf("Type(%d):ADD\n", ADD); return ADD; }
{SUB}           { printf("Type(%d):SUB\n", SUB); return SUB; }
{MUL}           { printf("Type(%d):MUL\n", MUL); return MUL; }
{DIV}           { printf("Type(%d):DIV\n", DIV); return DIV; }
{EXP}           { printf("Type(%d):EXPO\n", EXPO); return EXPO; }
{LP}            { printf("Type(%d):LP\n", LP); return LP; }
{RP}            { printf("Type(%d):RP\n", RP); return RP; }

%%

int yywrap() { return 1; }
