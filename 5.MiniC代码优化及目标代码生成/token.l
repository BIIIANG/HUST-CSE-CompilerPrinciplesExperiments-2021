%{
#include "string.h"
#include "def.h"
#include "parser.hpp"

extern int allerror;
extern int yycolumn;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
/*为了获得列号，使用lex提供的YY_USER_ACTION宏，对它重新定义，定义为一个函数，每次在识别成分之前会调用该函数，获得yylloc结构信息，包括first_line、first_column、last_line、last_column。这些信息在之后语法分析错误处理的时候也可以用上，用来定位出错位置。*/
// typedef union {
// 	//flex进行scanner，将数值存入yylval。而bison读取yylval之中的值。
// 	//
// 	int type_int;
// 	float type_float;//这里可能有错
// 	int type_char;//int 肯定可以保存char啊
// 	char type_id[32];
// 	struct node *ptr;
// } YYLVAL;
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
%}
%option yylineno 

id    [A-Za-z_][A-Za-z0-9_]*
INT_ten  0|([1-9][0-9]*)
INT_eight  [0](0|[1-7][0-7]*)
INT_sixteen  (0x|0X)[0-9A-Fa-f]+
int  {INT_ten}|{INT_eight}|{INT_sixteen}
char  \'[^'\\]\'
float ([0-9]*\.[0-9]+)|([0-9]+\.)|([0-9]*\.[0-9]+e(-)?[0-9]+)

%%
{INT_ten} 	{yylval.type_int=strtol(yytext,NULL,10);return INT;}
{INT_eight} { yylval.type_int=strtol(yytext,NULL,8);return INT;}
{INT_sixteen} {yylval.type_int=strtol(yytext,NULL,16);return INT;}

{float}      {yylval.type_float=atof(yytext); return FLOAT;}
{char}      {yylval.type_char=yytext[1]; return CHAR;/*这种情况下，正则需要简便处理*/}

"int"        {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);return TYPE;}
"char"      {strcpy(yylval.type_id,  yytext);return TYPE;}
"struct"     {yylval.line = yylineno;return STRUCT;}

"return"     {yylval.line = yylineno;return RETURN;}
"if"         {yylval.line = yylineno;return IF;}
"else"       {yylval.line = yylineno;return ELSE;}
"while"      {yylval.line = yylineno;return WHILE;}
"break"		{yylval.line = yylineno;return BREAK;}
{id}       {strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}

";"			{yylval.line = yylineno;return SEMI;}
","			{yylval.line = yylineno;return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);return RELOP;}
"="			{yylval.line = yylineno;return ASSIGNOP;}
"+="		{yylval.line = yylineno;return PLUSASS;}
"-="		{yylval.line = yylineno;return MINUSASS;}
"*="		{yylval.line = yylineno;return STARASS;}
"/="		{yylval.line = yylineno;return DIVASS;}
"%="		{yylval.line = yylineno;return MODASS;/*模运算可能后期有点难，先不支持*/}

"++"		{yylval.line = yylineno;return PLUSPLUS;}
"--" 		{yylval.line = yylineno;return MINUSMINUS;}

"+"			{yylval.line = yylineno;return PLUS;}
"-"			{yylval.line = yylineno;return MINUS;}
"*"			{yylval.line = yylineno;return STAR;}
"/"			{yylval.line = yylineno;return DIV;}
"%"			{yylval.line = yylineno;return MOD;}
"&&"        {yylval.line = yylineno;return AND;}
"||"		{yylval.line = yylineno;return OR;}
"!"			{yylval.line = yylineno;return NOT;}
"("			{yylval.line = yylineno;return LP;}
")"			{yylval.line = yylineno;return RP;}
"{"			{yylval.line = yylineno;return LC;}
"}"			{yylval.line = yylineno;return RC;}

"["			{yylval.line = yylineno;return LB;}
"]"			{yylval.line = yylineno;return RB;}

"."			{yylval.line = yylineno;return DOT;}

"#".*		{printf("预定义或头文件\n");}


[\n]		{yycolumn=1;}
[ \r\t]		{/*printf("过滤空格等字符\n");*/}
"//".*$	{}
\/\*([^*]|\*+[^/*])*\*+\/	{}

[0-9][a-zA-Z0-9_]* {allerror=1;printf("Error: Illegal ID \"%s\"\t at Line %d\n",yytext,yylineno);\
					strcpy(yylval.type_id,  yytext); return ID;/*标识非法id,但是仍旧当做正常id进行分析*/}
\'[^'\\]$	{allerror=1;printf("Warning: missing terminating ' character at Line %d\n",yylineno);yylval.type_char=yytext[1]; return CHAR;}
.			{allerror=1;if(yytext[0]=='\''){printf("Error: missing terminating ' character at Line %d\n",yylineno);yylval.type_char=yytext[1]; return CHAR;}
				else printf("Error: Mysterious character \"%s\"\t at Line %d\n",yytext,yylineno);}
%%

/*
//词法分析输出二元组
int main(int argc,char **argv)
{
	if(argc<2){
		fprintf(stderr,"need filename\n");
		return 1;
	}
	if(!(yyin=fopen(argv[1],"r"))){
		perror(argv[1]);
		return (1);
	}
	yylex();
	return 0;
}
*/

int yywrap()
{
return 1;
}
