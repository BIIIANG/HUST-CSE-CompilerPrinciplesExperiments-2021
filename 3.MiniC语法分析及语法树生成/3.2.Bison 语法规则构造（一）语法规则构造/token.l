%{
#include "string.h"
#include "def.h"
#include "parser.hpp"

extern int yycolumn;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
#define YYSTYPE yylval
extern "C"
{	
	int yywrap(void);
	int yylex(void);
}

void flexout(std::string name,std::string value){
  std::cout<<name<<"\t:"<<value<<std::endl;
}
//flex为bison提供行号信息

// xba：删除掉以下"/="行后的
// "%="		 {return MODASS;/*模运算可能后期有点难，先不支持*/}
// 以及"/"行后的
// "%"			 {return MOD;}
%}
%option yylineno 

id    [A-Za-z_][A-Za-z0-9_]*
int    ([1-9][0-9]*)|(0(x|X)[0-9a-fA-F]+|0)|(0[0-7]+)
char \'[^'\\]\'
float  ([0-9]*\.[0-9]+)|([0-9]+\.)|([0-9]*\.[0-9]+e(-)?[0-9]+)

%%
{int}        {yylval.type_int=atoi(yytext); return INT;}
{float}      {yylval.type_float=atof(yytext); return FLOAT;}
{char}       {yylval.type_char=yytext[1]; return CHAR;/*这种情况下，正则需要简便处理*/}

"int"        {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);return TYPE;}
"char"       {strcpy(yylval.type_id,  yytext);return TYPE;}
"struct"     {strcpy(yylval.type_id,  yytext);return STRUCT;}

"return"     {return RETURN;}
"if"         {return IF;}
"else"       {return ELSE;}
"while"      {return WHILE;}
"break"		 {return BREAK;}
{id}         {strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}

";"			 {return SEMI;}
","			 {return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);return RELOP;}
"="			 {return ASSIGNOP;}
"+="		 {return PLUSASS;}
"-="		 {return MINUSASS;}
"*="		 {return STARASS;}
"/="		 {return DIVASS;}

"++"		 {return PLUSPLUS;}
"--" 		 {return MINUSMINUS;}

"+"			 {return PLUS;}
"-"			 {return MINUS;}
"*"			 {return STAR;}
"/"			 {return DIV;}

"&&"         {return AND;}
"||"		 {return OR;}
"!"			 {return NOT;}
"("		 	 {return LP;}
")"			 {return RP;}
"{"			 {return LC;}
"}"			 {return RC;}

"["			 {return LB;}
"]"			 {return RB;}

"."			{return DOT;}

"#".*		{printf("预定义或头文件\n");}


[\n]		{yycolumn=1;}
[ \r\t]		{/*printf("过滤空格等字符\n");*/}
"//".*$	{}
\/\*([^*]|\*+[^/*])*\*+\/	{}

0[0-9]+ { printf("Error type A at Line %d: Illegal octal number '%s'\n",yylineno,yytext);}
0x[0-9a-zA-Z]* { printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n",yylineno,yytext);}


[0-9][a-zA-Z0-9_]* {printf("Error: Illegal ID \"%s\"\t at Line %d\n",yytext,yylineno);\
					strcpy(yylval.type_id,  yytext); return ID;/*标识非法id,但是仍旧当做正常id进行分析*/}
\'[^'\\]$	{printf("Warning: missing terminating ' character at Line %d\n",yylineno);yylval.type_char=yytext[1]; return CHAR; }
.			{if(yytext[0]=='\''){printf("Error: missing terminating ' character at Line %d\n",yylineno);yylval.type_char=yytext[1]; return CHAR; }
				else printf("Error type A at Line %d: Mysterious characters \'%s\'\n" ,yylineno,yytext);}

%%

int yywrap()
{
  return 1;
}
