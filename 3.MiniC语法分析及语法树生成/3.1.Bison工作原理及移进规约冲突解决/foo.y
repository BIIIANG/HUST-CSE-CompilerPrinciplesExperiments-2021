%union
{
 int ival;
 const char *sval;
}
%token <ival>NUM
%nterm <ival>exp

%left '-'
%left '+'

%%
exp:
     exp '+' exp
    |exp '-' exp
    |NUM
    ;
%% 