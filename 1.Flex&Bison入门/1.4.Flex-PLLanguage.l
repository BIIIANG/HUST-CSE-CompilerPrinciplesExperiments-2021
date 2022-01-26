/* PL词法分析器 */
/* 功能：能够识别出PL支持的所有单词符号并给出种别值 */
/* 说明：在下面的begin和end之间添加代码，已经实现了标识符和整常量的识别，你需要完成剩下的部分，加油吧！ */
/* 提示：因为是顺序匹配，即从上至下依次匹配规则，所以需要合理安排顺序～ */
%{
#include <stdio.h>
%}

OFSYM			of
ARRAYSYM		array
PROGRAMSYM		program
MODSYM			mod
ANDSYM			and
ORSYM			or
NOTSYM			not
BEGINSYM		begin
ENDSYM			end
IFSYM			if
THENSYM			then
ELSESYM			else
WHILESYM		while
DOSYM			do
CALLSYM			call
CONSTSYM		const
TYPESYM			type
VARSYM			var
PROCSYM			procedure

INTCON			[\-]?[1-9][0-9]*|0
IDENT			[A-Za-z][A-Za-z0-9]*
CHARCON         '[^']*'
 
PLUS			\+
MINUS			\-
TIMES			\*
DIVSYM			\/
EQL				=
NEQ				<>
LSS				<
LEQ				<=
GTR				>
GEQ				>=

LBRACK			\[
RBRACK			\]
LPAREN			\(
RPAREN			\)
COMMA			,
SEMICOLON		;
PERIOD			\.
BECOME			:=
COLON			:

ERROR			[~!@#\$%\^&_\\]
%%  

{OFSYM}			{printf("%s: OFSYM\n", yytext);}
{ARRAYSYM}		{printf("%s: ARRAYSYM\n", yytext);}
{PROGRAMSYM}	{printf("%s: PROGRAMSYM\n", yytext);}
{MODSYM}		{printf("%s: MODSYM\n", yytext);}
{ANDSYM}		{printf("%s: ANDSYM\n", yytext);}
{ORSYM}			{printf("%s: ORSYM\n", yytext);}
{NOTSYM}		{printf("%s: NOTSYM\n", yytext);}
{BEGINSYM}		{printf("%s: BEGINSYM\n", yytext);}
{ENDSYM}		{printf("%s: ENDSYM\n", yytext);}
{IFSYM}			{printf("%s: IFSYM\n", yytext);}
{THENSYM}		{printf("%s: THENSYM\n", yytext);}
{ELSESYM}		{printf("%s: ELSESYM\n", yytext);}
{WHILESYM}		{printf("%s: WHILESYM\n", yytext);}
{DOSYM}			{printf("%s: DOSYM\n", yytext);}
{CALLSYM}		{printf("%s: CALLSYM\n", yytext);}
{CONSTSYM}		{printf("%s: CONSTSYM\n", yytext);}
{TYPESYM}		{printf("%s: TYPESYM\n", yytext);}
{VARSYM}		{printf("%s: VARSYM\n", yytext);}
{PROCSYM}		{printf("%s: PROCSYM\n", yytext);}

{INTCON}		{printf("%s: INTCON\n", yytext);}
{IDENT}			{printf("%s: IDENT\n", yytext);}
{CHARCON}       {printf("%s: CHARCON\n", yytext);}
 
{PLUS}			{printf("%s: PLUS\n", yytext);}
{MINUS}			{printf("%s: MINUS\n", yytext);}
{TIMES}			{printf("%s: TIMES\n", yytext);}
{DIVSYM}		{printf("%s: DIVSYM\n", yytext);}
{EQL}			{printf("%s: EQL\n", yytext);}
{NEQ}			{printf("%s: NEQ\n", yytext);}
{LSS}			{printf("%s: LSS\n", yytext);}
{LEQ}			{printf("%s: LEQ\n", yytext);}
{GTR}			{printf("%s: GTR\n", yytext);}
{GEQ}			{printf("%s: GEQ\n", yytext);}

{LBRACK}		{printf("%s: LBRACK\n", yytext);}
{RBRACK}		{printf("%s: RBRACK\n", yytext);}
{LPAREN}		{printf("%s: LPAREN\n", yytext);}
{RPAREN}		{printf("%s: RPAREN\n", yytext);}
{COMMA}			{printf("%s: COMMA\n", yytext);}
{SEMICOLON}		{printf("%s: SEMICOLON\n", yytext);}
{PERIOD}		{printf("%s: PERIOD\n", yytext);}
{BECOME}		{printf("%s: BECOME\n", yytext);}
{COLON}			{printf("%s: COLON\n", yytext);}

{ERROR}			{printf("%s: ERROR\n", yytext);}

\n				{}
.				{}
%%

int yywrap() { return 1; }
int main(int argc, char **argv)
{
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex());
	return 0;
}