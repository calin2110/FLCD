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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    FUN = 258,
    VOID = 259,
    INT_TYPE = 260,
    STRING_TYPE = 261,
    BOOL_TYPE = 262,
    READ = 263,
    WRITE = 264,
    DEF = 265,
    FINAL = 266,
    UNLESS = 267,
    ELSE = 268,
    UNTIL = 269,
    FORENUM = 270,
    FOREACH = 271,
    IN = 272,
    MAIN = 273,
    CONST = 274,
    ID = 275,
    PLUS_ASSIGN = 276,
    MINUS_ASSIGN = 277,
    MULTI_ASSIGN = 278,
    DIV_ASSIGN = 279,
    MOD_ASSIGN = 280,
    ASSIGN = 281,
    PLUS = 282,
    MINUS = 283,
    MULTI = 284,
    DIV = 285,
    MOD = 286,
    GEQ = 287,
    GT = 288,
    LEQ = 289,
    LT = 290,
    EQ = 291,
    NEQ = 292,
    AND = 293,
    OR = 294,
    OPEN_BRACKET = 295,
    CLOSE_BRACKET = 296,
    OPEN_BRACE = 297,
    CLOSE_BRACE = 298,
    COLON = 299,
    COMMA = 300,
    SEMICOLON = 301,
    OPEN_RIGHT_BRACKET = 302,
    CLOSE_RIGHT_BRACKET = 303
  };
#endif
/* Tokens.  */
#define FUN 258
#define VOID 259
#define INT_TYPE 260
#define STRING_TYPE 261
#define BOOL_TYPE 262
#define READ 263
#define WRITE 264
#define DEF 265
#define FINAL 266
#define UNLESS 267
#define ELSE 268
#define UNTIL 269
#define FORENUM 270
#define FOREACH 271
#define IN 272
#define MAIN 273
#define CONST 274
#define ID 275
#define PLUS_ASSIGN 276
#define MINUS_ASSIGN 277
#define MULTI_ASSIGN 278
#define DIV_ASSIGN 279
#define MOD_ASSIGN 280
#define ASSIGN 281
#define PLUS 282
#define MINUS 283
#define MULTI 284
#define DIV 285
#define MOD 286
#define GEQ 287
#define GT 288
#define LEQ 289
#define LT 290
#define EQ 291
#define NEQ 292
#define AND 293
#define OR 294
#define OPEN_BRACKET 295
#define CLOSE_BRACKET 296
#define OPEN_BRACE 297
#define CLOSE_BRACE 298
#define COLON 299
#define COMMA 300
#define SEMICOLON 301
#define OPEN_RIGHT_BRACKET 302
#define CLOSE_RIGHT_BRACKET 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
