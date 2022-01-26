%{
#include <ctype.h>
#include <stdio.h>
#include <math.h>
int yylex (void);
void yyerror (char const *);
%}

%token NUM
%define api.value.type {double}
%left '+' '-'
%left '*' '/'
%right 'n'
%right '^'

%% 
/* Grammar rules and actions follow.  */
input:
    %empty
    | input line
    ;
line:
    '\n'
    | exp '\n'      { printf ("%.10g\n", $1); }
    ;
exp:
    NUM             { $$ = $1; }
    | exp exp '+'   { $$ = $1 + $2; }
    | exp exp '-'   { $$ = $1 - $2; }
    | exp exp '*'   { $$ = $1 * $2; }
    | exp exp '/'   { $$ = $1 / $2; }
    | exp exp '^'   { $$ = pow ($1, $2); }
    | exp 'n'       { $$ = -$1; }
    ;
%%
/* The lexical analyzer returns a double floating point
number on the stack and the token NUM, or the numeric code
of the character read if not a number.  
It skips all blanks and tabs, and returns 0 for end-of-input.  */
int yylex (void)
{
    int c;
    /* Skip white space.  */
    while ((c = getchar ()) == ' ' || c == '\t') { continue; }
    /* Process numbers.  */
    if (c == '.' || isdigit (c))
    {
        ungetc (c, stdin);
        scanf ("%lf", &yylval);
        return NUM;
    }
    /* Return end-of-input.  */
    if (c == EOF)
        return 0;
    if (c == '!')
        return 0;
    /* Return a single char.  */
    return c;
}
int main (int argc, char** argv)
{
    yyparse ();
    return 0;
}
/* Called by yyparse on error.  */
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}