#include "astnode.h"
#include "parser.hpp"

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int allerror;
extern "C"
{
    extern int yylex(void);
}

int yycolumn = 1;
int spaces = 0;

extern int yylastidlineno; // mark

NProgram *p = nullptr;

int main(int argc, char *argv[])
{
    yyin = fopen(argv[1], "r");
    if (!yyin)
        return 1;
    yylineno = 1;
    allerror = 0;
    // yylex();
    yyparse();
    if (allerror)
        return 1;
    if (p)
    {
        p->parse();

        // Init
        // InitializeModuleAndPassManager();
        // p->codegen();
    }
    return 0;
}