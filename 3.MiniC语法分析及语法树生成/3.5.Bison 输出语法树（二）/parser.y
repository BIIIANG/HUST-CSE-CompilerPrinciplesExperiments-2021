%locations
/* bison的.y文件中，加入%locations，这样bison加入-d编译后的.h符号表文件中
 * 会多出一个YYLTYPE结构体定义和一个该结构体类型的全局变量yylloc
 * 这样，flex的.l文件include该.h文件后，该结构体类型就可以被flex知道
 * 且flex可以向yylloc里面填入信息。
 */

%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "def.h"

#include <bits/stdc++.h>
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
char myerror[255];
extern NProgram *p;
extern int allerror;
void myyyerror();

extern "C"{
void yyerror(const char* fmt, ...);
extern int yylex(void);
}
%}

%union {
    NExtDefFunDec  *nExtDefFunDec;
    NExtDefList *nExtDefList;
    NExtDef *nExtDef;
    NSpecifier *nSpecifier;
    NExtDecList *nExtDecList;
    NDecList *nDecList;
    NVarDec *nVarDec;
    NFunDec *nFunDec;
    NCompSt *nCompSt;
    NVarList *nVarList;
    NParamDec *nParamDec;
    NDefList *nDefList;
    NDec *nDec;
    NDef *nDef;
    NStmtList *nStmtList;
    NStmt *nStmt;
    NExpression *nExpression;
    NArgs *nArgs;
    NIdentifier *nIdentifier;
    NStructSpecifier *nStructSpecifier;

    NTag *nTag;         // mark
    NOptTag *nOptTag;   // mark

    std::string *text;
    int     type_int;
    int     line;
    float   type_float;
    int     type_char;
    char    type_id[32];
}
// union的默认结构体类型为YYSTYPE，相当于自己把YYSTYPE重新定义为union类型。所以相应的yylval也变为union类型。
// 这个union类型-d选项编译时会放在头文件中
// %type 定义非终结符的语义值类型
%type  <nExtDefFunDec> program
%type  <nExtDefList> ExtDefList
%type  <nExtDef> ExtDef
%type  <nSpecifier> Specifier
%type  <nExtDecList> ExtDecList
%type  <nDecList> DecList
%type  <nVarDec> VarDec
%type  <nFunDec> FunDec
%type  <nCompSt> CompSt

%type  <nDefList> DefList
%type  <nVarList> VarList
%type  <nParamDec> ParamDec
%type  <nDec> Dec
%type  <nDef> Def
%type  <nStmtList> StmtList

%type  <nExpression> Exp
%type  <nStmt> Stmt
%type  <nArgs> Args
// %type  <nIdentifier> OptTag  Tag
%type  <nOptTag> OptTag     // mark
%type  <nTag> Tag           // mark
%type  <nStructSpecifier> StructSpecifier
//% token 定义终结符的语义值类型
%token <type_int> INT
%token <type_id> ID RELOP TYPE
%token <type_float> FLOAT
%token <type_char> CHAR
%token <line> STRUCT LP RP LC RC LB RB SEMI COMMA
%token <line> DOT PLUS MINUS STAR DIV MOD ASSIGNOP AND OR NOT
%token <line> IF BREAK ELSE WHILE RETURN PLUSASS MINUSASS STARASS DIVASS MODASS PLUSPLUS MINUSMINUS

%left COMMA
%left ASSIGNOP PLUSASS MINUSASS STARASS DIVASS MODASS
//先不支持？三目运算
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV MOD
%right UMINUS NOT UPLUSPLUS UMINUSMINUS
%left PLUSPLUS MINUSMINUS 
%right DOT
%left LB

%nonassoc LOWER_THEN_ELSE //无结合性
%nonassoc ELSE

%%
/*High-level Definitions*/
program:
    ExtDefList                  { p = new NProgram($1); if($1) p->line = $1->line; } /*显示语法树*/
    ;
ExtDefList:
    %empty                      { $$ = nullptr; }
    | ExtDef ExtDefList         { $$ = new NExtDefList(*$1, $2); $$->line = $1->line; }
    ;
ExtDef: 
    Specifier ExtDecList SEMI   { $$ = new NExtDef(*$1, $2); $$->line = $1->line; }
    | Specifier SEMI            { $$ = new NExtDef(*$1); $$->line = $1->line; } 
    | Specifier FunDec CompSt   { $$ = new NExtDef(*$1, $2, $3); $$->line = $1->line; }
    ;
ExtDecList: 
    VarDec                      { $$ = new NExtDecList(*$1, nullptr); $$->line = $1->line; }
    | VarDec COMMA ExtDecList   { $$ = new NExtDecList(*$1, $3); $$->line = $1->line; }
    ;

/*Specifiers*/
Specifier: 
    TYPE                        { /*if ($1[0] == 'i') $$ = new NSpecifier(*(new std::string("int")));
                                else $$ = new NSpecifier(*(new std::string("float")));*/
                                $$ = new NSpecifier(*(new std::string((char*)$1))); $$->line = yylineno; }   
    | StructSpecifier           { $$ = new NStructSpSpecifier(*$1); $$->line = $1->line; }   // mark
    ;
StructSpecifier: 
    STRUCT OptTag LC DefList RC { $$ = new NStructSpecifier($2, $4); $$->line = $1; }   
    | STRUCT Tag                { $$ = new NStructSpecifier($2); $$->line = $1; }   
    ;
OptTag: 
    ID                          { $$ = new NOptTag(*(new NIdentifier($1))); 
                                $$->line = atoi($1 + strlen($1) + 1); }  // mark
    | %empty                    { $$ = nullptr; }   
    ;
Tag:
    ID                          { $$ = new NTag(*(new NIdentifier($1))); 
                                $$->line = yylineno; }  // mark 
    ;

/*Declarators*/
VarDec:
    ID                          { $$ = new NVarDec(*(new NIdentifier($1))); $$->line = yylineno; }
    | VarDec LB INT RB          { $1->v.push_back($3); $$->line = $1->line; }    // mark
    ;
FunDec: 
    ID LP VarList RP            { $$ = new NFunDec(*(new NIdentifier($1)), $3); $$->line = yylineno; }
    | ID LP RP                  { $$ = new NFunDec(*(new NIdentifier($1)), nullptr); $$->line = yylineno; }
    ;
VarList: 
    ParamDec                    { $$ = new NVarList(*$1, nullptr); $$->line = $1->line; }
    | ParamDec COMMA VarList    { $$ = new NVarList(*$1, $3); $$->line = $1->line; }
    ;
ParamDec: 
    Specifier VarDec            { $$ = new NParamDec(*$1, *$2); $$->line = $1->line; }
    ;

/*Statements*/
CompSt:
    LC DefList StmtList RC      { $$ = new NCompSt($2, $3); $$->line = $1; }
    ;
StmtList:
    %empty                      { $$ = nullptr; }  
    | Stmt StmtList             { $$ = new NStmtList(*$1, $2); $$->line = $1->line; }
    ;
Stmt:
    Exp SEMI                    { $$ = new NExpStmt(*$1); $$->line = $1->line; }
    | CompSt                    { $$ = new NCompStStmt(*$1); $$->line = $1->line; }    // mark
    | RETURN Exp SEMI           { $$ = new NRetutnStmt(*$2); $$->line = $1; }
    | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   { $$ = new NIfStmt(*$3, *$5); $$->line = $1; }
    | IF LP Exp RP Stmt ELSE Stmt   { $$ = new NIfElseStmt(*$3, *$5, *$7); $$->line = $1; }
    | WHILE LP Exp RP Stmt      { $$ = new NWhileStmt(*$3, *$5); $$->line = $1; }
    | BREAK SEMI                { $$ = new NBreakStmt(); $$->line = $1; }
    ;

/*Local Definitions*/
DefList:
    %empty                      { $$ = nullptr; }
    | Def DefList               { $$ = new NDefList(*$1, $2); $$->line = $1->line; }
    ;
Def:
    Specifier DecList SEMI      { $$ = new NDef(*$1, $2); $$->line = $1->line; }
    ;
DecList:
    Dec                         { $$ = new NDecList(*$1, nullptr); $$->line = $1->line; }
    | Dec COMMA DecList         { $$ = new NDecList(*$1, $3); $$->line = $1->line; }
    ;
Dec:
    VarDec                      { $$ = new NDec(*$1); $$->line = $1->line; }
    | VarDec ASSIGNOP Exp       { $$ = new NDec(*$1, $3); $$->line = $1->line; }
    ;

/*Expressions*/
Exp:                            // $$结点type_id空置未用，正好存放运算符
    Exp ASSIGNOP Exp            { $$ = new NAssignment(*(new std::string("ASSIGNOP")), *$1, ASSIGNOP, *$3); $$->line = $1->line; }
    | Exp PLUSASS Exp           { $$ = new NAssignment(*(new std::string("PLUSASS")), *$1, PLUSASS, *$3); $$->line = $1->line; }
    | Exp MINUSASS Exp          { $$ = new NAssignment(*(new std::string("MINUSASS")), *$1, MINUSASS, *$3); $$->line = $1->line; }
    | Exp STARASS Exp           { $$ = new NAssignment(*(new std::string("STARASS")), *$1, STARASS, *$3); $$->line = $1->line; }
    | Exp DIVASS Exp            { $$ = new NAssignment(*(new std::string("DIVASS")), *$1, DIVASS, *$3); $$->line = $1->line; }
                                //这里利用BISON %prec表示和UMINUS同优先级
    | PLUSPLUS Exp %prec UPLUSPLUS      { $$ = new NSingleOperator(*(new std::string("UPLUSPLUS")), UPLUSPLUS, *$2); $$->line = $1; }
    | MINUSMINUS Exp %prec UMINUSMINUS  { $$ = new NSingleOperator(*(new std::string("UMINUSMINUS")), UMINUSMINUS, *$2); $$->line = $1; }
    | Exp PLUSPLUS                      { $$ = new NSingleOperator(*(new std::string("PLUSPLUS")), PLUSASS, *$1); $$->line = $1->line; }
    | Exp MINUSMINUS                    { $$ = new NSingleOperator(*(new std::string("MINUSMINUS")), PLUSASS, *$1); $$->line = $1->line; }

    | Exp AND Exp               { $$ = new NBinaryOperator(*(new std::string("AND")), *$1, AND, *$3); $$->line = $1->line; }
    | Exp OR Exp                { $$ = new NBinaryOperator(*(new std::string("OR")), *$1, OR, *$3); $$->line = $1->line; }
    | Exp RELOP Exp             { $$ = new NBinaryOperator($2, *$1, RELOP, *$3); $$->line = $1->line; }  //词法分析关系运算符号自身值保存在$2中
    | Exp PLUS Exp              { $$ = new NBinaryOperator(*(new std::string("PLUS")), *$1, PLUS, *$3); $$->line = $1->line; }
    | Exp MINUS Exp             { $$ = new NBinaryOperator(*(new std::string("MINUS")), *$1, MINUS, *$3); $$->line = $1->line; }
    | Exp STAR Exp              { $$ = new NBinaryOperator(*(new std::string("STAR")), *$1, STAR, *$3); $$->line = $1->line; }
    | Exp DIV Exp               { $$ = new NBinaryOperator(*(new std::string("DIV")), *$1, DIV, *$3); $$->line = $1->line; }
    | LP Exp RP                 { $$ = new NParenOperator(*$2); $$->line = $1; }
    | MINUS Exp %prec UMINUS    { $$ = new NSingleOperator(*(new std::string("UMINUS")), UMINUS, *$2); $$->line = $1; }//这里利用BISON %prec表示和UMINUS同优先级 相当于虚拟出一个运算符
    | NOT Exp                   { $$ = new NSingleOperator(*(new std::string("NOT")), NOT, *$2); $$->line = $1; }
    | ID LP Args RP             { $$ = new NMethodCall(*(new NIdentifier($1)), $3); $$->line = yylineno; }
    | ID LP RP                  { $$ = new NMethodCall(*(new NIdentifier($1))); $$->line = yylineno; }
    | Exp LB Exp RB             { $$ = new NListOperator(*$1, *$3); $$->line = $1->line; }
    | Exp DOT ID                { $$ = new NDotOperator(*$1, *(new NIdentifier($3))); $$->line = $1->line; }
    | ID                        { $$ = new NIdentifier($1); $$->line = yylineno; }
    | INT                       { $$ = new NInteger($1); $$->line = yylineno; }
    | FLOAT                     { $$ = new NFloat($1); $$->line = yylineno; }
    | CHAR                      { $$ = new NChar($1); $$->line = yylineno; }
    ;
Args:   
    Exp COMMA Args              { $$ = new NArgs(*$1, $3); $$->line = $1->line; }
    | Exp                       { $$ = new NArgs(*$1, nullptr); $$->line = $1->line; }
    ;

%%

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;//取参数对应的函数
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line, yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "%s", myerror);
    fprintf(stderr, "%s", ".\n");
    memset(myerror, 0, sizeof(myerror));
}	
void myyyerror()
{
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line, yylloc.first_column);
    fprintf(stderr, "%s", myerror);
    fprintf(stderr, "%s", ".\n");
    memset(myerror, 0, sizeof(myerror));
}