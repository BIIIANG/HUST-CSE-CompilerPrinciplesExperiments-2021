%%
a*b             {printf("1");}
ca              {printf("2");}
a*ca*           {printf("3");}
%%
int main()
{
    yylex();
}