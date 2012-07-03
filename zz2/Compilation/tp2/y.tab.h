
/* A Bison parser, made by GNU Bison 2.4.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CSTE_ENTIERE = 258,
     CSTE_CHAINE = 259,
     IDENT = 260,
     LE = 261,
     GE = 262,
     NE = 263,
     AFFECT = 264,
     AND = 265,
     ARRAY = 266,
     FBEGIN = 267,
     CONST = 268,
     ELSE = 269,
     END = 270,
     FUNCTION = 271,
     IF = 272,
     NIL = 273,
     NOT = 274,
     OF = 275,
     OR = 276,
     PROGRAM = 277,
     RECORD = 278,
     RETURN = 279,
     STRING = 280,
     THEN = 281,
     TYPE = 282,
     VAR = 283,
     WHILE = 284,
     XOR = 285,
     FOR = 286,
     TO = 287,
     LOOP = 288,
     INTEGER = 289
   };
#endif
/* Tokens.  */
#define CSTE_ENTIERE 258
#define CSTE_CHAINE 259
#define IDENT 260
#define LE 261
#define GE 262
#define NE 263
#define AFFECT 264
#define AND 265
#define ARRAY 266
#define FBEGIN 267
#define CONST 268
#define ELSE 269
#define END 270
#define FUNCTION 271
#define IF 272
#define NIL 273
#define NOT 274
#define OF 275
#define OR 276
#define PROGRAM 277
#define RECORD 278
#define RETURN 279
#define STRING 280
#define THEN 281
#define TYPE 282
#define VAR 283
#define WHILE 284
#define XOR 285
#define FOR 286
#define TO 287
#define LOOP 288
#define INTEGER 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1740 of yacc.c  */
#line 34 "anasyn.y"

   int   entier;
   int   no_ident;
   char *chaine;



/* Line 1740 of yacc.c  */
#line 128 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


