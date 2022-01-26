%{
#include <stdio.h>
#include <math.h>
extern int yylineno;
int yylex();
void yyerror(const char *s);
%}

%define api.value.type {double}
%token NUM
%token EOL
%left ADD 
%left SUB 
%left MUL 
%left DIV
%right EXPO
%precedence NEG
%token LP
%token RP

%%
calclist:
	%empty
	| calclist exp EOL { printf ("=%.10g\n", $2); }
	;
exp:term
   	| exp ADD exp   { $$ = $1 + $3; }
	| exp SUB exp   { $$ = $1 - $3; }
    | exp MUL exp   { $$ = $1 * $3; }
    | exp DIV exp   { $$ = $1 / $3; }
    | exp EXPO exp  { $$ = pow ($1, $3); }
    | SUB exp %prec NEG { $$ = -$2; }
    | LP exp RP     { $$ = $2; }
	| error {}
	;

term:NUM
	;
%%

int main (int args, char **argv) {
	yyparse ();
	return 0;
}
void yyerror (char const *s) {
	fprintf (stderr, "MyError:%s yylineno:%d\n", s, yylineno);	
}
