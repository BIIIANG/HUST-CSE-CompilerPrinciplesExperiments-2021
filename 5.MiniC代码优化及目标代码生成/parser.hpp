/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    RELOP = 260,
    TYPE = 261,
    FLOAT = 262,
    CHAR = 263,
    STRUCT = 264,
    LP = 265,
    RP = 266,
    LC = 267,
    RC = 268,
    LB = 269,
    RB = 270,
    SEMI = 271,
    COMMA = 272,
    DOT = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    DIV = 277,
    MOD = 278,
    ASSIGNOP = 279,
    AND = 280,
    OR = 281,
    NOT = 282,
    IF = 283,
    BREAK = 284,
    ELSE = 285,
    WHILE = 286,
    RETURN = 287,
    PLUSASS = 288,
    MINUSASS = 289,
    STARASS = 290,
    DIVASS = 291,
    MODASS = 292,
    PLUSPLUS = 293,
    MINUSMINUS = 294,
    UMINUS = 295,
    UPLUSPLUS = 296,
    UMINUSMINUS = 297,
    LOWER_THEN_ELSE = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "parser.y"

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

        std::string *text;
	int    type_int;
        int line;
	float  type_float;
	int   type_char;
	char   type_id[32];

#line 131 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
