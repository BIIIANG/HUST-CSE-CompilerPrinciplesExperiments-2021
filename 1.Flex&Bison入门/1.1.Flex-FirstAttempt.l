    int num_lines=0,num_chars=0;
%%
\n ++num_lines;
.  ++num_chars;
%%
//int yywrap() { return 1; }
int main()
{
    yylex();
    printf("Lines=%d,Chars=%d\n",num_lines,num_chars);
}