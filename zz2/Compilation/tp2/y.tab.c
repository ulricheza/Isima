
/* A Bison parser, made by GNU Bison 2.4.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 13 "anasyn.y"


/* quelques include pour faire des affichages */
#include <stdio.h>

#include "files.h"
#include "table.h"

/* Pour l'affichage du parcours des regles lors de l'analyse 
   syntaxique                                                */
#undef DEBUG_S
#define DEBUG_S

/* prototype de la fonction d'erreur */
void yyerror(char *);

extern int yylineno;



/* Line 189 of yacc.c  */
#line 94 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 222 of yacc.c  */
#line 34 "anasyn.y"

   int   entier;
   int   no_ident;
   char *chaine;



/* Line 222 of yacc.c  */
#line 206 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 218 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   170

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      45,    46,    49,    38,    44,    39,    36,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    35,
      47,    37,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    12,    13,    15,    17,    20,    22,
      24,    26,    28,    31,    33,    36,    41,    43,    46,    49,
      51,    53,    56,    58,    61,    66,    68,    70,    72,    74,
      77,    81,    83,    86,    91,    98,   100,   104,   106,   108,
     113,   116,   118,   121,   126,   128,   130,   132,   134,   138,
     147,   148,   152,   154,   158,   162,   164,   166,   168,   170,
     172,   177,   179,   183,   187,   189,   193,   194,   196,   198,
     200,   202,   204,   206,   210,   217,   226,   232,   239,   242,
     243,   246,   248,   251,   255,   257,   261,   263,   267,   269,
     271,   273,   275,   277,   279,   281,   284,   287,   291,   293,
     295,   297,   299,   301,   305,   307,   309,   311,   313,   315,
     319,   322,   324,   326,   328
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    22,     5,    35,    53,    36,    -1,    54,
      88,    -1,    -1,    55,    -1,    56,    -1,    55,    56,    -1,
      57,    -1,    61,    -1,    73,    -1,    79,    -1,    13,    58,
      -1,    59,    -1,    58,    59,    -1,     5,    37,    60,    35,
      -1,     3,    -1,    38,     3,    -1,    39,     3,    -1,     4,
      -1,     5,    -1,    27,    62,    -1,    63,    -1,    62,    63,
      -1,     5,    37,    64,    35,    -1,    65,    -1,    66,    -1,
      69,    -1,    72,    -1,    40,    76,    -1,    23,    67,    15,
      -1,    68,    -1,    67,    68,    -1,    76,    41,    78,    35,
      -1,    11,    42,    70,    43,    20,    76,    -1,    71,    -1,
      70,    44,    71,    -1,     3,    -1,     5,    -1,    25,    42,
      71,    43,    -1,    28,    74,    -1,    75,    -1,    74,    75,
      -1,    76,    41,    78,    35,    -1,    77,    -1,     5,    -1,
      34,    -1,     5,    -1,    78,    44,     5,    -1,    16,     5,
      80,    41,    84,    35,    85,    35,    -1,    -1,    45,    81,
      46,    -1,    82,    -1,    81,    35,    82,    -1,    83,    41,
      78,    -1,     5,    -1,    77,    -1,     5,    -1,    77,    -1,
      53,    -1,     5,    45,    87,    46,    -1,    99,    -1,    87,
      44,    99,    -1,    12,    89,    15,    -1,    90,    -1,    89,
      35,    90,    -1,    -1,    88,    -1,    91,    -1,    92,    -1,
      93,    -1,    94,    -1,    86,    -1,    95,     9,    99,    -1,
      17,    45,    99,    46,    26,    90,    -1,    17,    45,    99,
      46,    26,    90,    14,    90,    -1,    29,    45,    99,    46,
      90,    -1,    31,    91,    32,    99,    33,    90,    -1,     5,
      96,    -1,    -1,    96,    97,    -1,    40,    -1,    36,     5,
      -1,    42,    98,    43,    -1,    99,    -1,    98,    44,    99,
      -1,   101,    -1,   101,   100,   101,    -1,    37,    -1,    47,
      -1,    48,    -1,     6,    -1,     7,    -1,     8,    -1,   103,
      -1,    38,   103,    -1,    39,   103,    -1,   101,   102,   103,
      -1,    38,    -1,    39,    -1,    21,    -1,    30,    -1,   105,
      -1,   103,   104,   105,    -1,    49,    -1,    50,    -1,    10,
      -1,    95,    -1,   106,    -1,    45,    99,    46,    -1,    19,
     105,    -1,    86,    -1,     3,    -1,     4,    -1,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    86,    95,    97,   101,   102,   106,   112,
     118,   124,   138,   142,   143,   147,   156,   157,   158,   159,
     160,   166,   170,   171,   175,   184,   185,   186,   187,   192,
     202,   212,   213,   217,   227,   237,   238,   242,   248,   258,
     269,   273,   274,   278,   287,   288,   292,   296,   297,   303,
     311,   313,   322,   325,   331,   340,   341,   345,   346,   351,
     357,   366,   367,   372,   380,   381,   389,   391,   397,   403,
     409,   415,   421,   425,   431,   432,   436,   440,   446,   449,
     451,   455,   456,   457,   461,   462,   469,   475,   484,   485,
     486,   487,   488,   489,   493,   494,   495,   496,   500,   501,
     502,   503,   507,   508,   512,   513,   514,   518,   519,   520,
     521,   522,   526,   527,   528
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CSTE_ENTIERE", "CSTE_CHAINE", "IDENT",
  "LE", "GE", "NE", "AFFECT", "AND", "ARRAY", "FBEGIN", "CONST", "ELSE",
  "END", "FUNCTION", "IF", "NIL", "NOT", "OF", "OR", "PROGRAM", "RECORD",
  "RETURN", "STRING", "THEN", "TYPE", "VAR", "WHILE", "XOR", "FOR", "TO",
  "LOOP", "INTEGER", "';'", "'.'", "'='", "'+'", "'-'", "'^'", "':'",
  "'['", "']'", "','", "'('", "')'", "'<'", "'>'", "'*'", "'/'", "$accept",
  "program", "bloc", "partie_decl", "decls", "decl", "partie_decl_const",
  "liste_decl_const", "decl_const", "const", "partie_decl_type",
  "liste_decl_type", "decl_type", "type", "type_ptr", "type_struct",
  "liste_champs", "champ", "type_tableau", "liste_indice", "indice",
  "type_ch_de_car", "partie_decl_var", "liste_decl_var", "decl_var",
  "type_var", "type_predef", "liste_ident", "partie_decl_fonc", "lpf",
  "liste_pf", "pf", "type_param", "type_retour", "corps", "appel_fonc",
  "lpe", "partie_instr", "instrs", "instr", "affect", "if_instr",
  "while_instr", "for_instr", "acces_var", "qualifs", "qualif",
  "liste_expression", "expression", "op_rel", "expression_simple",
  "op_add", "terme", "op_mult", "facteur", "cste_non_signee", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    59,    46,    61,    43,    45,
      94,    58,    91,    93,    44,    40,    41,    60,    62,    42,
      47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    58,    58,    59,    60,    60,    60,    60,
      60,    61,    62,    62,    63,    64,    64,    64,    64,    65,
      66,    67,    67,    68,    69,    70,    70,    71,    71,    72,
      73,    74,    74,    75,    76,    76,    77,    78,    78,    79,
      80,    80,    81,    81,    82,    83,    83,    84,    84,    85,
      86,    87,    87,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    91,    92,    92,    93,    94,    95,    96,
      96,    97,    97,    97,    98,    98,    99,    99,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   102,   103,   103,   104,   104,   104,   105,   105,   105,
     105,   105,   106,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     0,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     2,     4,     1,     2,     2,     1,
       1,     2,     1,     2,     4,     1,     1,     1,     1,     2,
       3,     1,     2,     4,     6,     1,     3,     1,     1,     4,
       2,     1,     2,     4,     1,     1,     1,     1,     3,     8,
       0,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     3,     6,     8,     5,     6,     2,     0,
       2,     1,     2,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       2,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,     0,     0,
       0,     0,     5,     6,     8,     9,    10,    11,     0,    12,
      13,    50,     0,    21,    22,    45,    46,    40,    41,     0,
      44,     2,    66,     3,     7,     0,    14,     0,     0,     0,
      23,    42,     0,    79,     0,     0,     0,    72,    67,     0,
      64,    68,    69,    70,    71,     0,    16,    19,    20,     0,
       0,     0,    55,    56,     0,    52,     0,     0,     0,     0,
       0,     0,     0,    25,    26,    27,    28,    47,     0,     0,
      78,     0,     0,    79,     0,    63,    66,     0,    17,    18,
      15,     0,    51,     0,    57,    58,     0,     0,     0,    31,
       0,     0,    29,    24,    43,     0,   112,   113,   114,     0,
       0,     0,     0,   111,     0,   107,    61,    86,    94,   102,
     108,     0,    81,     0,    80,     0,     0,     0,    65,    73,
      53,    54,     4,    37,    38,     0,    35,    30,    32,     0,
       0,    48,   110,    95,    96,     0,     0,    60,    91,    92,
      93,   100,   101,    88,    98,    99,    89,    90,     0,     0,
     106,   104,   105,     0,    82,     0,    84,     0,    66,     0,
      59,     0,     0,     0,     0,    39,   109,    62,    87,    97,
     103,    83,     0,    66,    76,    66,    49,     0,    36,    33,
      85,    74,    77,    34,    66,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    10,    11,    12,    13,    14,    19,    20,    61,
      15,    23,    24,    72,    73,    74,    98,    99,    75,   135,
     136,    76,    16,    27,    28,    29,    30,    78,    17,    38,
      64,    65,    66,    96,   171,   113,   114,    48,    49,    50,
      51,    52,    53,    54,   115,    80,   124,   165,   116,   158,
     117,   159,   118,   163,   119,   120
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int16 yypact[] =
{
      -2,    25,    43,    45,  -101,    65,    48,    85,    89,    16,
      29,    86,    65,  -101,  -101,  -101,  -101,  -101,    67,    48,
    -101,    52,    79,    89,  -101,  -101,  -101,    16,  -101,    80,
    -101,  -101,    84,  -101,  -101,    30,  -101,    18,    81,    -1,
    -101,  -101,   118,    83,    87,    90,   119,  -101,  -101,    60,
    -101,  -101,  -101,  -101,  -101,   116,  -101,  -101,  -101,   126,
     127,    96,  -101,  -101,   -18,  -101,    92,    37,    97,    16,
      98,    16,    99,  -101,  -101,  -101,  -101,  -101,    -3,    69,
      63,    69,    69,  -101,   106,  -101,    84,    69,  -101,  -101,
    -101,    18,  -101,   118,  -101,  -101,   108,   107,    14,  -101,
     100,   107,  -101,  -101,  -101,   137,  -101,  -101,  -101,    41,
      41,    41,    69,  -101,    73,  -101,  -101,    19,    27,  -101,
    -101,   139,  -101,    69,  -101,   101,   102,    69,  -101,  -101,
    -101,   105,    65,  -101,  -101,   -28,  -101,  -101,  -101,   118,
     103,  -101,  -101,    27,    27,   104,    69,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,    69,    41,
    -101,  -101,  -101,    41,  -101,    40,  -101,   129,    84,   112,
    -101,   121,   138,   107,    47,  -101,  -101,  -101,    88,    27,
    -101,  -101,    69,    84,  -101,    84,  -101,    16,  -101,  -101,
    -101,   143,  -101,  -101,    84,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,    28,  -101,  -101,   147,  -101,  -101,   142,  -101,
    -101,  -101,   141,  -101,  -101,  -101,  -101,    68,  -101,  -101,
     -94,  -101,  -101,  -101,   140,   -67,   -29,   -75,  -101,  -101,
    -101,    74,  -101,  -101,  -101,   -31,  -101,   157,  -101,   -83,
     123,  -101,  -101,  -101,   -32,  -101,  -101,  -101,   -76,  -101,
      12,  -101,   -98,  -101,  -100,  -101
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    47,   100,   128,   102,   125,   126,   140,    63,   142,
      68,   129,   143,   144,    55,   172,   173,    91,   131,    25,
       1,    25,    69,    62,    70,   148,   149,   150,    92,   137,
       3,   100,   104,    56,    57,    58,   145,   160,    95,    71,
     151,   105,    94,     4,   106,   107,    43,   166,    26,   152,
      26,   169,    26,    18,    55,    47,   153,   154,   155,   108,
     109,   179,    63,   180,   174,    31,   156,   157,    59,    60,
     177,    26,   106,   107,    43,    85,   161,   162,     6,   188,
       5,     7,   189,   181,   182,   184,   112,   108,   109,    43,
      21,   105,     8,     9,    22,    86,    32,    37,    32,   121,
     191,    44,   192,   122,    35,   123,   190,   110,   111,   151,
     133,   195,   134,    45,   112,    46,    39,   146,   152,   147,
     193,    42,    67,    77,    83,    87,   154,   155,    79,    88,
      89,    90,    81,    93,   103,    82,    55,    47,   127,    97,
     101,   139,   141,   132,   164,   185,   175,   167,   168,   105,
     176,    55,    47,    55,    47,   183,   186,   194,   187,    34,
     170,    36,    55,    47,    40,   130,   138,    41,    33,    84,
     178
};

static const yytype_uint8 yycheck[] =
{
      32,    32,    69,    86,    71,    81,    82,   101,    37,   109,
      11,    87,   110,   111,    46,    43,    44,    35,    93,     5,
      22,     5,    23,     5,    25,     6,     7,     8,    46,    15,
       5,    98,    35,     3,     4,     5,   112,    10,    67,    40,
      21,    44,     5,     0,     3,     4,     5,   123,    34,    30,
      34,   127,    34,     5,    86,    86,    37,    38,    39,    18,
      19,   159,    91,   163,   139,    36,    47,    48,    38,    39,
     146,    34,     3,     4,     5,    15,    49,    50,    13,   173,
      35,    16,    35,    43,    44,   168,    45,    18,    19,     5,
       5,    44,    27,    28,     5,    35,    12,    45,    12,    36,
     183,    17,   185,    40,    37,    42,   182,    38,    39,    21,
       3,   194,     5,    29,    45,    31,    37,    44,    30,    46,
     187,    41,    41,     5,     5,     9,    38,    39,    45,     3,
       3,    35,    45,    41,    35,    45,   168,   168,    32,    42,
      42,    41,     5,    35,     5,    33,    43,    46,    46,    44,
      46,   183,   183,   185,   185,    26,    35,    14,    20,    12,
     132,    19,   194,   194,    23,    91,    98,    27,    11,    46,
     158
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    52,     5,     0,    35,    13,    16,    27,    28,
      53,    54,    55,    56,    57,    61,    73,    79,     5,    58,
      59,     5,     5,    62,    63,     5,    34,    74,    75,    76,
      77,    36,    12,    88,    56,    37,    59,    45,    80,    37,
      63,    75,    41,     5,    17,    29,    31,    86,    88,    89,
      90,    91,    92,    93,    94,    95,     3,     4,     5,    38,
      39,    60,     5,    77,    81,    82,    83,    41,    11,    23,
      25,    40,    64,    65,    66,    69,    72,     5,    78,    45,
      96,    45,    45,     5,    91,    15,    35,     9,     3,     3,
      35,    35,    46,    41,     5,    77,    84,    42,    67,    68,
      76,    42,    76,    35,    35,    44,     3,     4,    18,    19,
      38,    39,    45,    86,    87,    95,    99,   101,   103,   105,
     106,    36,    40,    42,    97,    99,    99,    32,    90,    99,
      82,    78,    35,     3,     5,    70,    71,    15,    68,    41,
      71,     5,   105,   103,   103,    99,    44,    46,     6,     7,
       8,    21,    30,    37,    38,    39,    47,    48,   100,   102,
      10,    49,    50,   104,     5,    98,    99,    46,    46,    99,
      53,    85,    43,    44,    78,    43,    46,    99,   101,   103,
     105,    43,    44,    26,    90,    33,    35,    20,    71,    35,
      99,    90,    90,    76,    14,    90
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 78 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"program %s\n",tab_symb[(yyvsp[(2) - (5)].no_ident)]);
      #endif
   }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 87 "anasyn.y"
    {
   }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 95 "anasyn.y"
    { 
   }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 107 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl := partie_decl_const\n"); 
      #endif
   }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 113 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl := partie_decl_type\n"); 
      #endif
   }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 119 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl := partie_decl_var\n"); 
      #endif
   }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 125 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl := partie_decl_fonc\n"); 
      #endif
   }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 148 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl_const := %s = const\n",tab_symb[(yyvsp[(1) - (4)].no_ident)]); 
      #endif
   }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 176 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl_type := %s = type\n",tab_symb[(yyvsp[(1) - (4)].no_ident)]); 
      #endif
   }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 193 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"type_ptr ^ \n"); 
      #endif
   }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 203 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"type_record\n"); 
      #endif
   }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 218 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"champ : type = \n"); 
      #endif
   }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 228 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"type_tableau type_predef\n"); 
      #endif
   }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 243 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"indice = %i\n",(yyvsp[(1) - (1)].entier)); 
      #endif
   }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 249 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"indice = %s\n",tab_symb[(yyvsp[(1) - (1)].no_ident)]); 
      #endif
   }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 259 "anasyn.y"
    {
      #ifdef DEBUG_S
         fprintf(synt,"type_chaine\n"); 
      #endif
   }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 279 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"decl_var := type_var : liste_ident\n"); 
      #endif
   }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 304 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"FUNCTION %s lpf : type_retour; corps;\n",tab_symb[(yyvsp[(2) - (8)].no_ident)]);
      #endif
   }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 314 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"lpf := ( liste_pf )\n"); 
      #endif
   }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 323 "anasyn.y"
    { 
   }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 326 "anasyn.y"
    { 
   }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 332 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"liste_pf := type_param : liste_ident\n"); 
      #endif
   }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 358 "anasyn.y"
    { 
      #ifdef DEBUG_S
         fprintf(synt,"appel_fonc %s\n",tab_symb[(yyvsp[(1) - (4)].no_ident)]); 
      #endif
   }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 373 "anasyn.y"
    { 
   }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 382 "anasyn.y"
    { 
   }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 389 "anasyn.y"
    { 
   }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 392 "anasyn.y"
    { 
      #ifdef DEBUG_S
      fprintf(synt,"instr : partie_instr\n"); 
      #endif
   }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 398 "anasyn.y"
    { 
      #ifdef DEBUG_S
      fprintf(synt,"instr : affectation\n"); 
      #endif
   }
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 404 "anasyn.y"
    { 
      #ifdef DEBUG_S
      fprintf(synt,"instr : if_instr\n"); 
      #endif
   }
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 410 "anasyn.y"
    { 
      #ifdef DEBUG_S
      fprintf(synt,"instr : while_instr\n"); 
      #endif
   }
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 416 "anasyn.y"
    {
      #ifdef DEBUG_S
      fprintf(synt,"instr : for_instr\n"); 
      #endif
   }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 426 "anasyn.y"
    {
   }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 470 "anasyn.y"
    {
      #ifdef DEBUG_S
      fprintf(synt,"expression\n"); 
      #endif
   }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 476 "anasyn.y"
    {
      #ifdef DEBUG_S
      fprintf(synt,"expression op_rel expression\n"); 
      #endif
   }
    break;



/* Line 1455 of yacc.c  */
#line 1945 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 531 "anasyn.y"


/* ----------------------------------------------------------------- */
/* Affiche le message d'erreur msg                                   */
void yyerror(char *msg)
{
 if(!msg || *msg=='\0')
  fprintf(stderr, "Erreur ligne %d\n", yylineno);
 else
  fprintf(stderr, "Erreur ligne %d : %s\n", yylineno, msg);
}

/* ------------------- fin de anasyn.y ----------------------------- */

