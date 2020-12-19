/* A Bison parser, made by GNU Bison 3.7.2.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_MAIN = 258,                /* TOK_MAIN  */
    TOK_SCANF = 259,               /* TOK_SCANF  */
    TOK_PRINTF = 260,              /* TOK_PRINTF  */
    TOK_FUNCTION = 261,            /* TOK_FUNCTION  */
    TOK_RETURN = 262,              /* TOK_RETURN  */
    TOK_IF = 263,                  /* TOK_IF  */
    TOK_ELSE = 264,                /* TOK_ELSE  */
    TOK_WHILE = 265,               /* TOK_WHILE  */
    TOK_INT = 266,                 /* TOK_INT  */
    TOK_BOOLEAN = 267,             /* TOK_BOOLEAN  */
    TOK_ARRAY = 268,               /* TOK_ARRAY  */
    TOK_AND = 269,                 /* TOK_AND  */
    TOK_OR = 270,                  /* TOK_OR  */
    TOK_NOT = 271,                 /* TOK_NOT  */
    TOK_IGUAL = 272,               /* TOK_IGUAL  */
    TOK_DISTINTO = 273,            /* TOK_DISTINTO  */
    TOK_MENORIGUAL = 274,          /* TOK_MENORIGUAL  */
    TOK_MAYORIGUAL = 275,          /* TOK_MAYORIGUAL  */
    TOK_MENOR = 276,               /* TOK_MENOR  */
    TOK_MAYOR = 277,               /* TOK_MAYOR  */
    TOK_CONSTANTE_ENTERA = 278,    /* TOK_CONSTANTE_ENTERA  */
    TOK_TRUE = 279,                /* TOK_TRUE  */
    TOK_FALSE = 280,               /* TOK_FALSE  */
    TOK_IDENTIFICADOR = 281,       /* TOK_IDENTIFICADOR  */
    UMINUS = 282                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TOK_MAIN 258
#define TOK_SCANF 259
#define TOK_PRINTF 260
#define TOK_FUNCTION 261
#define TOK_RETURN 262
#define TOK_IF 263
#define TOK_ELSE 264
#define TOK_WHILE 265
#define TOK_INT 266
#define TOK_BOOLEAN 267
#define TOK_ARRAY 268
#define TOK_AND 269
#define TOK_OR 270
#define TOK_NOT 271
#define TOK_IGUAL 272
#define TOK_DISTINTO 273
#define TOK_MENORIGUAL 274
#define TOK_MAYORIGUAL 275
#define TOK_MENOR 276
#define TOK_MAYOR 277
#define TOK_CONSTANTE_ENTERA 278
#define TOK_TRUE 279
#define TOK_FALSE 280
#define TOK_IDENTIFICADOR 281
#define UMINUS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "alfa.y"

    char cadena[100];
    int numero;

#line 125 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
