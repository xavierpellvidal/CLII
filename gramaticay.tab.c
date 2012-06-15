/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.2"

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
#line 1 "gramatica.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RegistreActivacio.h"
#include "RegistreC3A.h"
#include "gramaticay.tab.h"
#include "symtab.h"

#define YYLMAX 100

/* Amb aquest defines es pot controlar com ha anat la comprovacio de tipus */
#define COMPTIPUS_IGUALS 0				/* Els parametres son iguals */
#define COMPTIPUS_DIF_RED_PRIMER 1		/* diferent tipus, pero es pot adaptar perdent precisio pel primer */
#define COMPTIPUS_DIF_RED_SEGON 2		/* diferent tipus, pero es pot adaptar perdent precisio pel segon */
#define COMPTIPUS_DIF_NO_RED -1			/* diferent tipus i no es pot adaptar */

/* Els IDs estan ordenats de forma ascendent segons la precisio, aixi comparant es podra
veure facilment qui te mes o menys precisio.*/
#define ID_CHAR 1
#define ID_SHORT 2
#define ID_INT 3
#define ID_LONG 4
#define ID_FLOAT 5
#define ID_DOUBLE 6
#define ID_VOID 9

#define UNDEF -1
#define FUNCTION 10
#define ID_TYPEDEF 11
#define ID_STRUCT 12

#define LOCAL 0
#define GLOBAL -1

extern FILE *yyout;

/*Variables per a la taula de simbols*/
char *nom_id;
char *nom_programa;
char *nom_ambit;
char *nom_funcio;
char *punter;

char *cast;	/*per a guardar expresions de comparacions que necessitem tenir en string*/
char *castAux; /*per a guardar expresions de comparacions que necessitem tenir en string*/
char *op;

/*Punter per a afegir cometes simples als caracters*/
char *aux;
taula globalRA, localRA;
fila filaAux;
registre globalC3A, localC3A;
fil filAux;
int offsetL = 0;
int offsetG = 0;

int tipus_declaracio = UNDEF;

int isFunction = 0;
int isReturn = 0;
int isFunctionDeclaration = 0;
int numParam = 0;
int i, j;
int isStruct = 0;
int isFor = 0;

/* per controlar el numero de parametres quan inicialitzem una llista manualment "{2,3,4}" */
int nparams_initializer_list = 0;

sym_value_type info, infoAux;
int error_sym, error_sym2;
sym_scope_id ambit_actual;
sym_scope_id ambit_anterior;

extern int yylineno;
extern int yylex();
extern void yyerror(char*);

char string[100];
void inicialitzarInfo();
void mostraError(int codi,const char *lexema);
void string_output(char *, int row, int col);
void missatgeTS(char *, int row, int col);
void missatgeError(char *, int row, int col);
void missatgeWarning(char *, int row, int col);
int comprovacioTipus(int primer, int segon);
int obtenirMida(int tipus);
int obtenirMidaStruct(char * );
sym_value_type info, infoAux;



/* Line 189 of yacc.c  */
#line 166 "gramaticay.tab.c"

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
     BREAK = 258,
     CASE = 259,
     CHAR = 260,
     CONTINUE = 261,
     DEFAULT = 262,
     DO = 263,
     DOUBLE = 264,
     ELSE = 265,
     FLOAT = 266,
     FOR = 267,
     IF = 268,
     INT = 269,
     LONG = 270,
     RETURN = 271,
     SHORT = 272,
     SIZEOF = 273,
     STRUCT = 274,
     SWITCH = 275,
     TYPEDEF = 276,
     UNION = 277,
     VOID = 278,
     WHILE = 279,
     IDENTIFIER = 280,
     CHARACTER_CONSTANT = 281,
     INTEGER_CONSTANT = 282,
     FLOATING_CONSTANT = 283,
     STRING = 284,
     INC_OP = 285,
     DEC_OP = 286,
     LE_OP = 287,
     GE_OP = 288,
     EQ_OP = 289,
     NE_OP = 290,
     AND_OP = 291,
     OR_OP = 292,
     MUL_ASSIG = 293,
     DIV_ASSIG = 294,
     MOD_ASSIG = 295,
     ADD_ASSIG = 296,
     SUB_ASSIG = 297,
     TYPEDEF_IDENTIFIER = 298,
     IF_PREC = 299
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 94 "gramatica.y"

	struct{
		char *lexema;
		char *lexemac3a;
		int lenght;
		int rows;
		int columns;
		int tipus;
		int* trueList;
		int nTrue;
		int* falseList;
		int nFalse;
		int* nextList;
		int nNext;
		int quad;
		int valor;
		int sizeList;
		int tipusTypedef;
	}ident;



/* Line 214 of yacc.c  */
#line 269 "gramaticay.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 281 "gramaticay.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1023

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  180
/* YYNRULES -- Number of states.  */
#define YYNSTATES  330

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,     2,     2,    53,     2,     2,
      46,    47,    51,    49,    58,    50,    57,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    64,
      60,    48,    61,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    17,    19,
      21,    26,    27,    32,    33,    39,    43,    46,    49,    51,
      55,    57,    60,    63,    66,    69,    74,    76,    78,    80,
      82,    87,    89,    93,    97,   101,   103,   107,   111,   113,
     117,   121,   125,   129,   131,   135,   139,   141,   146,   148,
     153,   155,   161,   163,   165,   169,   171,   173,   175,   177,
     179,   181,   183,   187,   190,   194,   199,   204,   209,   212,
     214,   216,   220,   222,   226,   228,   230,   232,   234,   236,
     238,   240,   242,   244,   246,   252,   257,   259,   261,   263,
     266,   270,   272,   276,   278,   280,   284,   289,   290,   296,
     301,   305,   310,   312,   316,   319,   322,   324,   326,   330,
     332,   335,   338,   340,   344,   348,   353,   356,   360,   364,
     369,   371,   375,   380,   382,   386,   388,   390,   392,   394,
     396,   398,   403,   407,   408,   412,   413,   418,   419,   424,
     425,   431,   433,   437,   439,   442,   443,   444,   451,   462,
     468,   472,   476,   481,   489,   497,   500,   509,   517,   524,
     533,   541,   549,   552,   555,   558,   562,   564,   567,   571,
     573,   575,   576,   580,   585,   586,   591,   595,   599,   602,
     604
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     125,     0,    -1,    25,    -1,    67,    -1,    29,    -1,    46,
      85,    47,    -1,    27,    -1,    26,    -1,    28,    -1,    66,
      -1,    68,    55,    85,    56,    -1,    -1,    68,    46,    69,
      47,    -1,    -1,    68,    46,    70,    71,    47,    -1,    68,
      57,    25,    -1,    68,    30,    -1,    68,    31,    -1,    83,
      -1,    71,    58,    83,    -1,    68,    -1,    30,    72,    -1,
      31,    72,    -1,    73,    74,    -1,    18,    72,    -1,    18,
      46,   103,    47,    -1,    49,    -1,    50,    -1,    59,    -1,
      72,    -1,    46,   103,    47,    74,    -1,    74,    -1,    75,
      51,    74,    -1,    75,    52,    74,    -1,    75,    53,    74,
      -1,    75,    -1,    76,    49,    75,    -1,    76,    50,    75,
      -1,    76,    -1,    77,    60,    76,    -1,    77,    61,    76,
      -1,    77,    32,    76,    -1,    77,    33,    76,    -1,    77,
      -1,    78,    34,    77,    -1,    78,    35,    77,    -1,    78,
      -1,    79,    36,   117,    78,    -1,    79,    -1,    80,    37,
     117,    79,    -1,    80,    -1,    80,    62,    85,    63,    81,
      -1,    81,    -1,    81,    -1,    72,    84,    83,    -1,    48,
      -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,
      -1,    83,    -1,    85,    58,    83,    -1,    87,    64,    -1,
      87,    88,    64,    -1,    21,    87,    98,    64,    -1,    21,
       1,    98,    64,    -1,    21,    87,     1,    64,    -1,     1,
      64,    -1,    90,    -1,    89,    -1,    88,    58,    89,    -1,
      98,    -1,    98,    48,   106,    -1,    23,    -1,     5,    -1,
      17,    -1,    14,    -1,    15,    -1,    11,    -1,     9,    -1,
      92,    -1,    91,    -1,    43,    -1,    93,    25,    44,    94,
      45,    -1,    93,    44,    94,    45,    -1,    19,    -1,    22,
      -1,    95,    -1,    94,    95,    -1,   104,    96,    64,    -1,
      97,    -1,    96,    58,    97,    -1,    98,    -1,    25,    -1,
      46,    98,    47,    -1,    98,    55,    27,    56,    -1,    -1,
      98,    46,    99,   100,    47,    -1,    98,    46,   102,    47,
      -1,    98,    46,    47,    -1,    98,    46,     1,    47,    -1,
     101,    -1,   100,    58,   101,    -1,    87,    98,    -1,    87,
     105,    -1,    87,    -1,    25,    -1,   102,    58,    25,    -1,
     104,    -1,   104,   105,    -1,    90,   104,    -1,    90,    -1,
      46,   105,    47,    -1,    55,    27,    56,    -1,   105,    55,
      27,    56,    -1,    46,    47,    -1,    46,   100,    47,    -1,
     105,    46,    47,    -1,   105,    46,   100,    47,    -1,    83,
      -1,    44,   107,    45,    -1,    44,   107,    58,    45,    -1,
     106,    -1,   107,    58,   106,    -1,   109,    -1,   110,    -1,
     116,    -1,   119,    -1,   123,    -1,   124,    -1,     4,    82,
      63,   108,    -1,     7,    63,   108,    -1,    -1,    44,   111,
      45,    -1,    -1,    44,   130,   112,    45,    -1,    -1,    44,
     115,   113,    45,    -1,    -1,    44,   130,   115,   114,    45,
      -1,   108,    -1,   115,   117,   108,    -1,    64,    -1,    85,
      64,    -1,    -1,    -1,    13,    46,    85,    47,   117,   108,
      -1,    13,    46,    85,    47,   117,   108,    10,   118,   117,
     108,    -1,    20,    46,    85,    47,   108,    -1,    46,    85,
      64,    -1,   120,    85,    64,    -1,   121,    85,    47,   108,
      -1,    24,    46,   117,    85,    47,   117,   108,    -1,     8,
     108,    24,    46,    85,    47,    64,    -1,    12,   122,    -1,
      12,    46,    64,    85,    64,    85,    47,   108,    -1,    12,
      46,    64,    64,    85,    47,   108,    -1,    12,    46,    64,
      64,    47,   108,    -1,    12,    46,    85,    64,    64,    85,
      47,   108,    -1,    12,    46,    85,    64,    64,    47,   108,
      -1,    12,    46,    64,    85,    64,    47,   108,    -1,     6,
      64,    -1,     3,    64,    -1,    16,    64,    -1,    16,    85,
      64,    -1,   126,    -1,   125,   126,    -1,   125,     1,    47,
      -1,   127,    -1,    86,    -1,    -1,    98,   128,   110,    -1,
      87,    98,   130,   110,    -1,    -1,    87,    98,   129,   110,
      -1,    98,   130,   110,    -1,    87,     1,   110,    -1,     1,
     110,    -1,    86,    -1,   130,    86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   143,   143,   174,   177,   184,   198,   208,   220,   232,
     236,   280,   280,   313,   313,   371,   397,   399,   403,   426,
     447,   451,   453,   455,   476,   478,   482,   484,   486,   490,
     494,   548,   552,   621,   688,   757,   761,   828,   896,   898,
    1018,  1135,  1253,  1373,  1375,  1493,  1612,  1614,  1644,  1646,
    1676,  1679,  1683,  1689,  1693,  1760,  1762,  1764,  1766,  1768,
    1770,  1774,  1776,  1780,  1782,  1834,  1887,  1891,  1895,  1898,
    1904,  1906,  1910,  1977,  2036,  2041,  2046,  2051,  2057,  2062,
    2067,  2072,  2076,  2082,  2110,  2113,  2119,  2130,  2134,  2136,
    2140,  2155,  2157,  2161,  2168,  2238,  2240,  2277,  2277,  2327,
    2329,  2373,  2376,  2378,  2382,  2456,  2458,  2514,  2517,  2523,
    2527,  2531,  2533,  2537,  2539,  2541,  2543,  2545,  2547,  2549,
    2553,  2555,  2557,  2561,  2572,  2585,  2587,  2589,  2591,  2593,
    2595,  2599,  2601,  2605,  2605,  2623,  2623,  2640,  2640,  2661,
    2661,  2680,  2686,  2697,  2699,  2703,  2708,  2719,  2733,  2754,
    2758,  2771,  2795,  2819,  2837,  2839,  2843,  2845,  2847,  2849,
    2851,  2853,  2857,  2859,  2861,  2877,  2943,  2946,  2949,  2952,
    2954,  2957,  2957,  3060,  3062,  3062,  3147,  3149,  3151,  3154,
    3157
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BREAK", "CASE", "CHAR", "CONTINUE",
  "DEFAULT", "DO", "DOUBLE", "ELSE", "FLOAT", "FOR", "IF", "INT", "LONG",
  "RETURN", "SHORT", "SIZEOF", "STRUCT", "SWITCH", "TYPEDEF", "UNION",
  "VOID", "WHILE", "IDENTIFIER", "CHARACTER_CONSTANT", "INTEGER_CONSTANT",
  "FLOATING_CONSTANT", "STRING", "INC_OP", "DEC_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIG", "DIV_ASSIG",
  "MOD_ASSIG", "ADD_ASSIG", "SUB_ASSIG", "TYPEDEF_IDENTIFIER", "'{'",
  "'}'", "'('", "')'", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "IF_PREC",
  "'['", "']'", "'.'", "','", "'!'", "'<'", "'>'", "'?'", "':'", "';'",
  "$accept", "primary_expression", "constant", "postfix_expression", "$@1",
  "$@2", "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_AND_expression",
  "logical_OR_expression", "conditional_expression", "constant_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "type_specifier", "typedef_name",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "declarator", "$@3",
  "parameter_list", "parameter_declaration", "identifier_list",
  "type_name", "specifier_qualifier_list", "abstract_declarator",
  "initializer", "initializer_list", "statement", "labeled_statement",
  "compound_statement", "$@4", "$@5", "$@6", "$@7", "statement_list",
  "expression_statement", "m", "n", "selection_statement", "q", "p", "s",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "$@8", "$@9",
  "declaration_list", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   123,   125,    40,    41,    61,    43,
      45,    42,    47,    37,   299,    91,    93,    46,    44,    33,
      60,    62,    63,    58,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    66,    66,    67,    67,    67,    68,
      68,    69,    68,    70,    68,    68,    68,    68,    71,    71,
      72,    72,    72,    72,    72,    72,    73,    73,    73,    74,
      74,    75,    75,    75,    75,    76,    76,    76,    77,    77,
      77,    77,    77,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    83,    83,    84,    84,    84,    84,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    86,    87,
      88,    88,    89,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    92,    92,    93,    93,    94,    94,
      95,    96,    96,    97,    98,    98,    98,    99,    98,    98,
      98,    98,   100,   100,   101,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   106,   107,   107,   108,   108,   108,   108,   108,
     108,   109,   109,   111,   110,   112,   110,   113,   110,   114,
     110,   115,   115,   116,   116,   117,   118,   119,   119,   119,
     120,   121,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   124,   124,   124,   124,   125,   125,   125,   126,
     126,   128,   127,   127,   129,   127,   127,   127,   127,   130,
     130
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       4,     0,     4,     0,     5,     3,     2,     2,     1,     3,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     4,     1,     4,
       1,     5,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     3,     4,     4,     4,     2,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     1,     1,     1,     2,
       3,     1,     3,     1,     1,     3,     4,     0,     5,     4,
       3,     4,     1,     3,     2,     2,     1,     1,     3,     1,
       2,     2,     1,     3,     3,     4,     2,     3,     3,     4,
       1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     4,     3,     0,     3,     0,     4,     0,     4,     0,
       5,     1,     3,     1,     2,     0,     0,     6,    10,     5,
       3,     3,     4,     7,     7,     2,     8,     7,     6,     8,
       7,     7,     2,     2,     2,     3,     1,     2,     3,     1,
       1,     0,     3,     4,     0,     4,     3,     3,     2,     1,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    75,    80,    79,    77,    78,    76,    86,     0,
      87,    74,    94,    83,     0,   170,     0,    69,    82,    81,
       0,     0,     0,   166,   169,     0,    68,   178,     0,     0,
       0,     0,    63,     0,    70,     0,     0,     0,     0,     0,
       0,   179,     0,     0,     0,     1,     0,   167,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       7,     6,     8,     4,     0,     0,     0,    26,    27,    28,
     143,     9,     3,    20,    29,     0,    31,    35,    38,    43,
      46,    48,    50,    53,    61,     0,   141,   125,   126,     0,
     145,   127,   128,   129,   130,     0,     0,     0,     0,    95,
     177,     0,    64,     0,     0,     0,     0,   112,     0,    88,
       0,     0,   107,   100,     0,     0,     0,    72,   172,   180,
     176,   168,   163,    29,    52,     0,   162,     0,     0,     0,
       0,     0,   155,     0,   164,     0,     0,    24,     0,   145,
       0,    21,    22,     0,     0,   109,    16,    17,    13,     0,
       0,    56,    57,    58,    59,    60,    55,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   145,     0,     0,   144,   134,     0,     0,     0,   145,
      66,    67,    65,    71,     0,   120,    73,   175,   173,     0,
     111,    85,    89,     0,    91,    93,   101,   106,     0,   102,
      99,     0,    96,     0,   132,     0,     0,     0,     0,     0,
       0,   165,     0,     0,     0,     5,     0,     0,     0,   110,
       0,     0,     0,    15,    54,    32,    33,    34,    36,    37,
      41,    42,    39,    40,    44,    45,     0,     0,     0,    62,
     138,   142,   136,     0,   123,     0,    84,     0,    90,     0,
     104,   105,    98,     0,   108,   131,     0,     0,     0,   150,
     151,     0,   145,    25,     0,     0,    30,   116,     0,     0,
       0,     0,     0,    12,     0,    18,    10,    47,    49,     0,
     140,   121,     0,    92,   103,     0,     0,     0,     0,     0,
     152,     0,   149,   145,   117,   113,   114,   118,     0,     0,
      14,     0,    51,   122,   124,     0,   158,     0,     0,     0,
       0,     0,   147,     0,   119,   115,    19,   154,   157,   161,
       0,   160,     0,   146,   153,   156,   159,   145,     0,   148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    71,    72,    73,   220,   221,   274,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   125,    84,   157,
      85,    41,    42,    33,    34,    17,    18,    19,    20,   108,
     109,   193,   194,    21,   114,   268,   199,   115,   144,   110,
     269,   186,   245,    86,    87,    88,    89,   178,   176,   243,
      90,    91,   177,   327,    92,   130,   131,   132,    93,    94,
      22,    23,    24,    43,   104,    44
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -174
static const yytype_int16 yypact[] =
{
     705,    -1,  -174,  -174,  -174,  -174,  -174,  -174,  -174,   720,
    -174,  -174,  -174,  -174,     6,  -174,    32,  -174,  -174,  -174,
       4,   173,   584,  -174,  -174,   274,  -174,  -174,     6,    21,
     124,   -20,  -174,    60,  -174,   382,    22,   980,   -17,   599,
      42,  -174,    -4,   -20,   401,  -174,    -3,  -174,    24,   855,
      27,    51,   435,    71,    76,   607,   869,   106,   120,  -174,
    -174,  -174,  -174,  -174,   895,   895,   478,  -174,  -174,  -174,
    -174,  -174,  -174,    25,   225,   855,  -174,   257,   149,    44,
     280,   109,   -23,  -174,  -174,    83,  -174,  -174,  -174,   131,
     138,  -174,  -174,  -174,  -174,   336,    94,   177,    98,  -174,
    -174,     6,  -174,   762,   -20,   401,   980,   980,   938,  -174,
       6,   178,  -174,  -174,   980,    12,   191,   183,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,   167,  -174,   435,   228,   633,
     855,   855,  -174,   855,  -174,    84,   478,  -174,   855,  -174,
     855,  -174,  -174,    61,   212,   202,  -174,  -174,   222,   855,
     259,  -174,  -174,  -174,  -174,  -174,  -174,   855,  -174,   855,
     855,   855,   855,   855,   855,   855,   855,   855,   855,   855,
    -174,  -174,   855,   855,  -174,  -174,   229,   435,   266,   271,
    -174,  -174,  -174,  -174,   762,  -174,  -174,  -174,  -174,   953,
    -174,  -174,  -174,   169,  -174,   205,  -174,     3,    63,  -174,
    -174,   304,  -174,   435,  -174,   286,   659,   182,   248,    69,
      99,  -174,   287,   103,   855,  -174,   855,   536,   308,   216,
     289,   855,   164,  -174,  -174,  -174,  -174,  -174,   257,   257,
     149,   149,   149,   149,    44,    44,   855,   855,    23,  -174,
    -174,  -174,  -174,   301,  -174,    62,  -174,     6,  -174,   521,
     205,   216,  -174,   980,  -174,  -174,   855,   789,   249,   305,
    -174,   435,  -174,  -174,   435,   107,  -174,  -174,   142,   198,
     312,   158,   343,  -174,   144,  -174,  -174,   280,   109,   855,
    -174,  -174,   727,  -174,  -174,   150,   435,   156,   815,   829,
    -174,   435,  -174,  -174,  -174,  -174,  -174,  -174,   166,   315,
    -174,   855,  -174,  -174,  -174,   309,  -174,   435,   435,   168,
     435,   174,   362,   435,  -174,  -174,  -174,  -174,  -174,  -174,
     435,  -174,   435,  -174,  -174,  -174,  -174,  -174,   435,  -174
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -174,  -174,  -174,  -174,  -174,   -30,  -174,   -60,
     159,   161,   162,   139,   137,  -174,   -43,  -174,   -78,  -174,
     -46,    18,     1,  -174,   275,   -34,  -174,  -174,  -174,   272,
     -96,  -174,   130,   -12,  -174,  -107,   135,  -174,   253,   -39,
    -132,  -173,  -174,   -52,  -174,     7,  -174,  -174,  -174,  -174,
     295,  -174,  -134,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,   370,  -174,  -174,  -174,    29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -175
static const yytype_int16 yytable[] =
{
     128,    16,    30,   107,    35,   214,   124,   198,    27,   135,
      29,   244,   192,   219,   171,   158,    96,    98,    15,   123,
     143,    12,    97,    16,    25,   185,   137,   145,    12,    36,
     117,    12,   107,    31,   141,   142,   236,   237,   100,   172,
      15,    25,    14,    25,   121,   123,    12,    26,    37,   249,
     118,   120,    14,    27,    95,   146,   147,    12,   218,   200,
      32,    26,   119,    26,   105,   251,   106,    14,   190,   116,
     201,   148,   107,   107,   107,   204,   164,   165,    14,   224,
     149,   173,   150,   207,   208,   209,   279,   210,   122,   117,
     143,   126,   213,   192,   143,   239,    32,   145,   195,   225,
     226,   227,   107,   222,   166,   167,   185,   281,   215,   304,
     252,   187,   188,   119,   127,   197,   261,   129,   101,   173,
     282,   253,   133,   119,   102,   241,   238,   173,   291,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
      39,   173,   173,   275,    39,   170,   262,   174,   211,    40,
     264,   255,   138,    40,   293,   107,   266,   173,   180,   313,
     258,   173,   182,     2,   298,   173,   139,     3,   265,     4,
      39,    99,     5,     6,    38,     7,   175,     8,     2,    40,
      10,    11,     3,  -137,     4,   250,   123,     5,     6,   294,
       7,   300,     8,   328,     9,    10,    11,   305,   162,   163,
     253,    13,   301,   307,   185,   297,   123,   123,   173,   290,
     285,   287,   292,   314,   173,   320,    13,  -171,   197,    39,
     276,   322,   173,   316,   253,   196,   173,   247,    40,    39,
     203,   103,   173,   248,   306,   195,   302,    30,    40,   312,
     173,   181,   309,   311,   271,   295,   259,   202,   217,   123,
     197,    39,   205,   272,   197,   318,   319,   218,   321,   216,
      40,   324,   271,   151,   152,   153,   154,   155,   325,   -11,
     326,   272,   197,   156,   240,    38,   329,    48,    49,     2,
      50,    51,    52,     3,   223,     4,    53,    54,     5,     6,
      55,     7,    56,     8,    57,     9,    10,    11,    58,    59,
      60,    61,    62,    63,    64,    65,   173,   173,   159,   160,
     161,   242,   260,   288,   168,   169,  -139,    13,    25,  -133,
      66,   228,   229,    67,    68,   230,   231,   232,   233,   254,
     234,   235,   256,    69,   263,   270,   273,    38,    70,    48,
      49,     2,    50,    51,    52,     3,   280,     4,    53,    54,
       5,     6,    55,     7,    56,     8,    57,     9,    10,    11,
      58,    59,    60,    61,    62,    63,    64,    65,   296,   289,
     299,   315,   323,   317,   278,   277,   183,   283,   189,    13,
      25,  -135,    66,    38,     0,    67,    68,     2,   284,   212,
     179,     3,    47,     4,     0,    69,     5,     6,     0,     7,
      70,     8,    38,     9,    10,    11,     2,     0,     0,     0,
       3,     0,     4,     0,     0,     5,     6,     0,     7,     0,
       8,     0,     9,    10,    11,    13,  -174,     0,    39,     0,
     103,     0,     0,     0,     0,     0,     0,    40,    48,    49,
     -72,    50,    51,    52,    13,    25,   -72,    53,    54,     0,
       0,    55,     0,    56,     0,    57,     0,     0,     0,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
       0,    66,     0,     2,    67,    68,     0,     3,     0,     4,
       0,     0,     5,     6,    69,     7,    56,     8,     0,    70,
      10,    11,     0,    59,    60,    61,    62,    63,    64,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,    66,     0,     2,    67,    68,     0,
       3,     0,     4,     0,     0,     5,     6,    69,     7,     0,
       8,     2,     0,    10,    11,     3,    12,     4,     0,     0,
       5,     6,     0,     7,     0,     8,     0,     0,    10,    11,
       0,     0,     0,     0,    13,     0,     0,   249,   267,     0,
       0,     0,     0,     0,     0,     0,   218,     0,     0,    13,
       0,     0,   217,   267,    45,    46,     0,     0,     0,     2,
       0,   218,     0,     3,     0,     4,     0,     0,     5,     6,
     111,     7,     0,     8,   -97,     9,    10,    11,   -97,    12,
     -97,     0,     0,   -97,   -97,     0,   -97,     0,   -97,     0,
       0,   -97,   -97,     0,   112,    56,     0,    13,     0,     0,
      14,     0,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,   -97,     0,     0,     0,   113,     0,     0,     0,
       0,    56,     0,    66,     0,     0,    67,    68,    59,    60,
      61,    62,    63,    64,    65,     0,    69,     0,     0,     0,
       0,   134,     0,     0,     0,     0,     0,    56,     0,    66,
       0,     0,    67,    68,    59,    60,    61,    62,    63,    64,
      65,     0,    69,     0,     0,     0,     0,   206,     0,     0,
       0,     0,     0,     0,     0,    66,     1,     0,    67,    68,
       2,     0,     0,     0,     3,     0,     4,     0,    69,     5,
       6,    28,     7,   257,     8,     2,     9,    10,    11,     3,
      12,     4,     0,     0,     5,     6,     0,     7,     0,     8,
       0,     0,    10,    11,     0,    56,     0,     0,    13,     0,
       0,    14,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
       0,   184,   303,    66,     0,     0,    67,    68,     0,     0,
      56,     0,     0,     0,     0,     0,    69,    59,    60,    61,
      62,    63,    64,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   184,    56,    66,     0,
       0,    67,    68,     0,    59,    60,    61,    62,    63,    64,
      65,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,    66,   286,     0,    67,    68,
      59,    60,    61,    62,    63,    64,    65,    56,    69,     0,
       0,     0,     0,     0,    59,    60,    61,    62,    63,    64,
      65,    66,   308,     0,    67,    68,     0,     0,     0,     0,
       0,     0,     0,    56,    69,    66,   310,     0,    67,    68,
      59,    60,    61,    62,    63,    64,    65,    56,    69,     0,
       0,     0,     0,     0,    59,    60,    61,    62,    63,    64,
      65,    66,     0,     0,    67,    68,     0,     0,     0,     0,
       0,     0,     0,    56,    69,   136,     0,     0,    67,    68,
      59,    60,    61,    62,    63,    64,    65,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,     0,     2,    67,    68,     0,     3,     0,     4,
       0,     0,     5,     6,    69,     7,     0,     8,     2,     0,
      10,    11,     3,     0,     4,     0,     0,     5,     6,     0,
       7,     0,     8,     0,     0,    10,    11,     0,     0,     0,
       0,    13,     0,   191,     0,     2,     0,     0,     0,     3,
       0,     4,     0,     0,     5,     6,    13,     7,   246,     8,
       0,     0,    10,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13
};

static const yytype_int16 yycheck[] =
{
      52,     0,    14,    37,    16,   139,    49,   114,     1,    55,
       9,   184,   108,   145,    37,    75,    28,    29,     0,    49,
      66,    25,     1,    22,    44,   103,    56,    66,    25,    25,
      42,    25,    66,     1,    64,    65,   170,   171,    31,    62,
      22,    44,    46,    44,    47,    75,    25,    64,    44,    46,
      43,    44,    46,    46,    25,    30,    31,    25,    55,    47,
      64,    64,    44,    64,    35,   197,    44,    46,   107,    27,
      58,    46,   106,   107,   108,   127,    32,    33,    46,   157,
      55,    58,    57,   129,   130,   131,    63,   133,    64,   101,
     136,    64,   138,   189,   140,   173,    64,   136,   110,   159,
     160,   161,   136,   149,    60,    61,   184,    45,    47,   282,
      47,   104,   105,    95,    63,   114,    47,    46,    58,    58,
      58,    58,    46,   105,    64,   177,   172,    58,   262,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
      46,    58,    58,   221,    46,    36,    47,    64,    64,    55,
      47,   203,    46,    55,    47,   189,   216,    58,    64,   293,
     206,    58,    64,     5,   271,    58,    46,     9,   214,    11,
      46,    47,    14,    15,     1,    17,    45,    19,     5,    55,
      22,    23,     9,    45,    11,   197,   216,    14,    15,    47,
      17,    47,    19,   327,    21,    22,    23,    47,    49,    50,
      58,    43,    58,    47,   282,    47,   236,   237,    58,   261,
     256,   257,   264,    47,    58,    47,    43,    44,   217,    46,
      56,    47,    58,   301,    58,    47,    58,    58,    55,    46,
      63,    48,    58,    64,   286,   247,   279,   249,    55,   291,
      58,    64,   288,   289,    46,    47,    64,    56,    46,   279,
     249,    46,    24,    55,   253,   307,   308,    55,   310,    47,
      55,   313,    46,    38,    39,    40,    41,    42,   320,    47,
     322,    55,   271,    48,    45,     1,   328,     3,     4,     5,
       6,     7,     8,     9,    25,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    58,    58,    51,    52,
      53,    45,    64,    64,    34,    35,    45,    43,    44,    45,
      46,   162,   163,    49,    50,   164,   165,   166,   167,    25,
     168,   169,    46,    59,    47,    27,    47,     1,    64,     3,
       4,     5,     6,     7,     8,     9,    45,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    56,    64,
      27,    56,    10,    64,   237,   236,   101,   247,   106,    43,
      44,    45,    46,     1,    -1,    49,    50,     5,   253,   136,
      95,     9,    22,    11,    -1,    59,    14,    15,    -1,    17,
      64,    19,     1,    21,    22,    23,     5,    -1,    -1,    -1,
       9,    -1,    11,    -1,    -1,    14,    15,    -1,    17,    -1,
      19,    -1,    21,    22,    23,    43,    44,    -1,    46,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    55,     3,     4,
      58,     6,     7,     8,    43,    44,    64,    12,    13,    -1,
      -1,    16,    -1,    18,    -1,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    46,    -1,     5,    49,    50,    -1,     9,    -1,    11,
      -1,    -1,    14,    15,    59,    17,    18,    19,    -1,    64,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,     5,    49,    50,    -1,
       9,    -1,    11,    -1,    -1,    14,    15,    59,    17,    -1,
      19,     5,    -1,    22,    23,     9,    25,    11,    -1,    -1,
      14,    15,    -1,    17,    -1,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    43,
      -1,    -1,    46,    47,     0,     1,    -1,    -1,    -1,     5,
      -1,    55,    -1,     9,    -1,    11,    -1,    -1,    14,    15,
       1,    17,    -1,    19,     5,    21,    22,    23,     9,    25,
      11,    -1,    -1,    14,    15,    -1,    17,    -1,    19,    -1,
      -1,    22,    23,    -1,    25,    18,    -1,    43,    -1,    -1,
      46,    -1,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    18,    -1,    46,    -1,    -1,    49,    50,    25,    26,
      27,    28,    29,    30,    31,    -1,    59,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    18,    -1,    46,
      -1,    -1,    49,    50,    25,    26,    27,    28,    29,    30,
      31,    -1,    59,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,     1,    -1,    49,    50,
       5,    -1,    -1,    -1,     9,    -1,    11,    -1,    59,    14,
      15,     1,    17,    64,    19,     5,    21,    22,    23,     9,
      25,    11,    -1,    -1,    14,    15,    -1,    17,    -1,    19,
      -1,    -1,    22,    23,    -1,    18,    -1,    -1,    43,    -1,
      -1,    46,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    -1,    -1,    49,    50,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    -1,    59,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    18,    46,    -1,
      -1,    49,    50,    -1,    25,    26,    27,    28,    29,    30,
      31,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    46,    47,    -1,    49,    50,
      25,    26,    27,    28,    29,    30,    31,    18,    59,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      31,    46,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    59,    46,    47,    -1,    49,    50,
      25,    26,    27,    28,    29,    30,    31,    18,    59,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    30,
      31,    46,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    59,    46,    -1,    -1,    49,    50,
      25,    26,    27,    28,    29,    30,    31,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,     5,    49,    50,    -1,     9,    -1,    11,
      -1,    -1,    14,    15,    59,    17,    -1,    19,     5,    -1,
      22,    23,     9,    -1,    11,    -1,    -1,    14,    15,    -1,
      17,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    43,    -1,    45,    -1,     5,    -1,    -1,    -1,     9,
      -1,    11,    -1,    -1,    14,    15,    43,    17,    45,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     9,    11,    14,    15,    17,    19,    21,
      22,    23,    25,    43,    46,    86,    87,    90,    91,    92,
      93,    98,   125,   126,   127,    44,    64,   110,     1,    87,
      98,     1,    64,    88,    89,    98,    25,    44,     1,    46,
      55,    86,    87,   128,   130,     0,     1,   126,     3,     4,
       6,     7,     8,    12,    13,    16,    18,    20,    24,    25,
      26,    27,    28,    29,    30,    31,    46,    49,    50,    59,
      64,    66,    67,    68,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    83,    85,   108,   109,   110,   111,
     115,   116,   119,   123,   124,   130,    98,     1,    98,    47,
     110,    58,    64,    48,   129,   130,    44,    90,    94,    95,
     104,     1,    25,    47,    99,   102,    27,    98,   110,    86,
     110,    47,    64,    72,    81,    82,    64,    63,   108,    46,
     120,   121,   122,    46,    64,    85,    46,    72,    46,    46,
      46,    72,    72,    85,   103,   104,    30,    31,    46,    55,
      57,    38,    39,    40,    41,    42,    48,    84,    74,    51,
      52,    53,    49,    50,    32,    33,    60,    61,    34,    35,
      36,    37,    62,    58,    64,    45,   113,   117,   112,   115,
      64,    64,    64,    89,    44,    83,   106,   110,   110,    94,
     104,    45,    95,    96,    97,    98,    47,    87,   100,   101,
      47,    58,    56,    63,   108,    24,    64,    85,    85,    85,
      85,    64,   103,    85,   117,    47,    47,    46,    55,   105,
      69,    70,    85,    25,    83,    74,    74,    74,    75,    75,
      76,    76,    76,    76,    77,    77,   117,   117,    85,    83,
      45,   108,    45,   114,   106,   107,    45,    58,    64,    46,
      98,   105,    47,    58,    25,   108,    46,    64,    85,    64,
      64,    47,    47,    47,    47,    85,    74,    47,   100,   105,
      27,    46,    55,    47,    71,    83,    56,    78,    79,    63,
      45,    45,    58,    97,   101,    85,    47,    85,    64,    64,
     108,   117,   108,    47,    47,    47,    56,    47,   100,    27,
      47,    58,    81,    45,   106,    47,   108,    47,    47,    85,
      47,    85,   108,   117,    47,    56,    83,    64,   108,   108,
      47,   108,    47,    10,   108,   108,   108,   118,   117,   108
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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

/* Line 1464 of yacc.c  */
#line 143 "gramatica.y"
    {
								inicialitzarInfo();
								ambit_actual=sym_get_scope();
								
								if (ambit_actual==SYM_ROOT_SCOPE){
									error_sym=sym_global_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
								}
								else{
									error_sym=sym_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
								}
								
								if(error_sym == SYMTAB_OK){
									if (info.tipus == ID_TYPEDEF){
										(yyval.ident).tipus = info.tipus;
										(yyval.ident).tipusTypedef = info.tipusTypedef  ;
									}
									else{
									    (yyval.ident).lexema = (yyvsp[(1) - (1)].ident).lexema;
										(yyval.ident).tipus = info.tipus;
									}
									
									/*-----------------C3A------------------*/
									(yyval.ident).lexemac3a = (yyvsp[(1) - (1)].ident).lexema;
								}
								else{
									sprintf(string,"ERROR. Variable %s no definida en l'ambit %d.", (yyvsp[(1) - (1)].ident).lexema, ambit_actual);
									missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
									YYERROR;
								}
								sprintf(string,"primary_expression <- IDENTIFIER %s", (yyvsp[(1) - (1)].ident).lexema);
								string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 174 "gramatica.y"
    {
								sprintf(string,"primary_expression <- constant ");
								string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 177 "gramatica.y"
    {
		
								/*-----------------C3A------------------*/
								(yyval.ident).lexemac3a = (yyvsp[(1) - (1)].ident).lexemac3a;
								
								sprintf(string,"primary_expression <- STRING %s", (yyvsp[(1) - (1)].ident).lexema);
								string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 184 "gramatica.y"
    {
								(yyval.ident).tipus = (yyvsp[(2) - (3)].ident).tipus;
								
								/*-----------------C3A------------------*/
								(yyval.ident).lexemac3a = (yyvsp[(2) - (3)].ident).lexemac3a;
								(yyval.ident).trueList = (yyvsp[(2) - (3)].ident).trueList;
								(yyval.ident).nTrue = (yyvsp[(2) - (3)].ident).nTrue;
								(yyval.ident).falseList = (yyvsp[(2) - (3)].ident).falseList;
								(yyval.ident).nFalse = (yyvsp[(2) - (3)].ident).nFalse;
								
								sprintf(string,"primary_expression <- (expression) ");
								string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 198 "gramatica.y"
    {
							(yyval.ident).tipus = ID_INT;
							(yyval.ident).sizeList = UNDEF;
							(yyval.ident).valor= ID_INT;
							
							/*-----------------C3A------------------*/
							(yyval.ident).lexemac3a = (yyvsp[(1) - (1)].ident).lexema;
							
							sprintf(string,"constant <- INTEGER_CONSTANT %s", (yyvsp[(1) - (1)].ident).lexema);
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 208 "gramatica.y"
    {
							(yyval.ident).tipus = ID_CHAR;
							(yyval.ident).sizeList = UNDEF;
							(yyval.ident).valor = ID_CHAR;
							
							/*-----------------C3A------------------*/
							/*$$.lexemac3a = $1.lexema;*/
							sprintf(aux,"'%s'",(yyvsp[(1) - (1)].ident).lexema);
							(yyval.ident).lexemac3a = aux;
							
							sprintf(string,"constant <- CHARACTER_CONSTANT %s", (yyvsp[(1) - (1)].ident).lexema);
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 220 "gramatica.y"
    {
							(yyval.ident).tipus = ID_FLOAT;
							(yyval.ident).sizeList = UNDEF;
							(yyval.ident).valor = ID_FLOAT;
							
							/*-----------------C3A------------------*/
							(yyval.ident).lexemac3a = (yyvsp[(1) - (1)].ident).lexema;
							
							sprintf(string,"constant <- FLOATING_CONSTANT %s", (yyvsp[(1) - (1)].ident).lexema);
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 232 "gramatica.y"
    {
											(yyval.ident) = (yyvsp[(1) - (1)].ident);
											sprintf(string,"postfix_expression <- primary_expression ");
											string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 236 "gramatica.y"
    {
											inicialitzarInfo();
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup((yyvsp[(1) - (4)].ident).lexema,&info);
											}
											else{
												error_sym=sym_lookup((yyvsp[(1) - (4)].ident).lexema,&info);
											}
											if(error_sym == SYMTAB_OK){
												if ((yyvsp[(3) - (4)].ident).tipus != ID_INT){
													sprintf(string,"ERROR. Index ha de ser una expressio entera.");
													missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													YYERROR;
												}else if(info.sizeList != UNDEF){
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													sprintf(op,"%c",'*');
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %d %s %s", cast, ":=", obtenirMida(info.tipus), obtainOp(op, info.tipus), (yyvsp[(3) - (4)].ident).lexemac3a) ;
													localC3A = emet(filAux, localC3A);
													
													/*$$.lexemac3a = nouTemp();*/
													filAux = inicialitzarFil(filAux);
													sprintf((yyval.ident).lexemac3a, "%s[%s]", (yyvsp[(1) - (4)].ident).lexemac3a, cast);
													/*localC3A = emet(filAux, localC3A);*/
													
													sprintf(string,"(TS) Trobada la taula %s a la TS.", (yyvsp[(1) - (4)].ident).lexema);
													missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													(yyval.ident).tipus = info.tipus;
													(yyval.ident).sizeList = UNDEF;
												}else{
													sprintf(string,"ERROR. La variable no es una taula.");
													missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													YYERROR;
												}	
											}
											else{
												sprintf(string,"ERROR. Variable no definida.");
												missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
											}
											sprintf(string,"postfix_expression <- postfix_expression '[' expression ']' ");
											string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 280 "gramatica.y"
    {
							inicialitzarInfo();
							ambit_actual = sym_get_scope();
							
							error_sym=sym_global_lookup((yyvsp[(1) - (2)].ident).lexema,&info);
							
							if(info.tipus != FUNCTION){
								sprintf(string,"ERROR. La variable %s no es una funcio.", (yyvsp[(1) - (2)].ident).lexema);
								missatgeError(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
								YYERROR;
							}
							else{
								numParam = 0;
								
								nom_funcio = (char *)malloc(sizeof((yyvsp[(1) - (2)].ident).lexema));
								strcpy(nom_funcio, (yyvsp[(1) - (2)].ident).lexema);
							}	
							;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 297 "gramatica.y"
    {
									inicialitzarInfo();
									ambit_actual = sym_get_scope();
									
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(numParam != info.nParamsFuncio ){
										sprintf(string,"ERROR. En numero d'arguments no coincideix amb la declaracio.");
										missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
										YYERROR;
									}
									
									(yyval.ident).tipus = info.tipusFunction;
									
									sprintf(string,"postfix_expression <- postfix_expression '(' ')' ");
									string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 313 "gramatica.y"
    {
								inicialitzarInfo();
								ambit_actual = sym_get_scope();
								
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								if(info.tipus != FUNCTION){
									sprintf(string,"ERROR. La variable %s no es una funcio.", (yyvsp[(1) - (2)].ident).lexema);
									missatgeError(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
									YYERROR;
								} 
								else{
									numParam = 0;
									
									nom_funcio = (char *)malloc(sizeof((yyvsp[(1) - (2)].ident).lexema));
									strcpy(nom_funcio, (yyvsp[(1) - (2)].ident).lexema);
								}	
							;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 330 "gramatica.y"
    {
															inicialitzarInfo();
															ambit_actual = sym_get_scope();
															
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															if(numParam != info.nParamsFuncio ){
																
																sprintf(string,"ERROR. En numero d'arguments no coincideix amb la declaracio.");
																missatgeError(string,(yyvsp[(1) - (5)].ident).rows, (yyvsp[(1) - (5)].ident).columns);
																YYERROR;
															}
															
															for(i=0;i<info.nParamsFuncio;i++){
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "PARAM %s", info.parametres[i].parametrec3a);
																localC3A = emet(filAux, localC3A);															
															}
															
															(yyval.ident).tipus = info.tipusFunction;
															
															
															/*Check if function have a return statement*/
															
															if(info.tipusFunction != ID_VOID){
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s := CALL %s, %d", (yyval.ident).lexemac3a, nom_funcio, numParam);
																localC3A = emet(filAux, localC3A);	
																
															}else{							
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "CALL %s, %d", nom_funcio, numParam);
																localC3A = emet(filAux, localC3A);
															}
															
															/*Restart function name */
															strcpy(nom_funcio, nom_ambit);
															
															sprintf(string,"postfix_expression <- postfix_expression '(' argument_expression_list ')' ");
															string_output(string, (yyvsp[(1) - (5)].ident).rows, (yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 371 "gramatica.y"
    {
											nom_id = (char *)malloc(sizeof(char)*20);
											strcpy(nom_id, (yyvsp[(1) - (3)].ident).lexema);
											
											inicialitzarInfo();
											ambit_actual = sym_get_scope();

											/*Obtenim la variable creada amb el typedef struct, pero volem el valor per accedir al struct 'melon' i veure les dades*/
											error_sym=sym_lookup(nom_id,&info);
											/* Recuperem el struct original 'melon', no el creat*/
											error_sym=sym_lookup(info.valor,&infoAux);
											j = 0;
											
											for(i=0; i<infoAux.nParamsFuncio; i++){
												printf("Param %d: tipus %d  -> mida: %d\n", i,  infoAux.parametres[i].type, obtenirMida(infoAux.parametres[i].type));
												j += obtenirMida(infoAux.parametres[i].type);
												if (strcmp(infoAux.parametres[i].lexema, (yyvsp[(3) - (3)].ident).lexema) == 0){
													(yyval.ident).tipus = infoAux.parametres[i].type;
													j -= obtenirMida(infoAux.parametres[i].type);
													break;
												}
											}
											
											
											sprintf(string,"postfix_expression <- postfix_expression '.' IDENTIFIER ");
											string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 397 "gramatica.y"
    {sprintf(string,"postfix_expression <- postfix_expression INC_OP  ");
											string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 399 "gramatica.y"
    {sprintf(string,"postfix_expression <- postfix_expression DEC_OP ");
											string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 403 "gramatica.y"
    {
													inicialitzarInfo();
															
													/*Recuperem la funcio per guardar-hi el parametre*/
													error_sym=sym_global_lookup(nom_funcio,&info);
													
													if(info.parametres[numParam].type != (yyvsp[(1) - (1)].ident).tipus){
														sprintf(string,"ERROR. El tipus del parametre %d no coincideix amb la declaracio.", numParam + 1);
														missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
														YYERROR;
													}
													else{
														/*******************C3A******************/
														strcpy(info.parametres[numParam].parametrec3a, (yyvsp[(1) - (1)].ident).lexemac3a);
														
														sym_global_remove(nom_funcio);
														sym_global_add(nom_funcio,&info);
														
														numParam++;
													}
													
													sprintf(string,"argument_expression_list <- assignment_expression ");
													string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 426 "gramatica.y"
    {
															inicialitzarInfo();
															/*Recuperem la funcio per guardar-hi el parametre*/
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															if(info.parametres[numParam].type != (yyvsp[(3) - (3)].ident).tipus){
																sprintf(string,"ERROR. El tipus del parametre %d no coincideix amb la declaracio.", numParam + 1);
																missatgeError(string,(yyvsp[(3) - (3)].ident).rows, (yyvsp[(3) - (3)].ident).columns);
																YYERROR;
															}
															else{
																/*******************C3A******************/
																strcpy(info.parametres[numParam].parametrec3a, (yyvsp[(3) - (3)].ident).lexemac3a);
																sym_global_remove(nom_funcio);
																sym_global_add(nom_funcio,&info);
																numParam++;
															}
															sprintf(string,"argument_expression_list <- argument_expression_list ',' assignment_expression");
															string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 447 "gramatica.y"
    {
										(yyval.ident) = (yyvsp[(1) - (1)].ident);
										sprintf(string,"unary_expression <- postfix_expression ");
										string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 451 "gramatica.y"
    {sprintf(string,"unary_expression <- INC_OP unary_expression ");
										string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 453 "gramatica.y"
    {sprintf(string,"unary_expression <- DEC_OP unary_expression ");
										string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 455 "gramatica.y"
    {
										if ((yyvsp[(2) - (2)].ident).tipus != ID_CHAR){
											(yyval.ident).tipus = (yyvsp[(2) - (2)].ident).tipus;
											
											if ( (yyvsp[(1) - (2)].ident).lexema[0] == '-' ){
												/*-----------------C3A------------------*/
												(yyval.ident).lexemac3a = nouTemp();
												filAux = inicialitzarFil(filAux);
												sprintf(filAux.info, "%s %s %s %s", (yyval.ident).lexemac3a, ":=", signChange((yyvsp[(2) - (2)].ident).tipus), (yyvsp[(2) - (2)].ident).lexemac3a);
												localC3A = emet(filAux, localC3A);
											} else if  ( (yyvsp[(1) - (2)].ident).lexema[0] == '!' ){
												(yyval.ident).trueList = (yyvsp[(2) - (2)].ident).falseList;
												(yyval.ident).nTrue = (yyvsp[(2) - (2)].ident).nFalse;
												(yyval.ident).falseList = (yyvsp[(2) - (2)].ident).trueList;
												(yyval.ident).nFalse = (yyvsp[(2) - (2)].ident).nTrue;
											}
											
											
										}
										sprintf(string,"unary_expression <- unary_operator cast_expression ");
										string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 476 "gramatica.y"
    {sprintf(string,"unary_expression <- SIZEOF unary_expression ");
										string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 478 "gramatica.y"
    {sprintf(string,"unary_expression <- SIZEOF '(' type_name ')' ");
										string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 482 "gramatica.y"
    {sprintf(string,"unary_operator <- '+' ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 484 "gramatica.y"
    {sprintf(string,"unary_operator <- '-' ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 486 "gramatica.y"
    {sprintf(string,"unary_operator <- '!' ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 490 "gramatica.y"
    {
										(yyval.ident) = (yyvsp[(1) - (1)].ident);
										sprintf(string,"cast_expression <- unary_expression");
										string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 494 "gramatica.y"
    {
										if(((yyvsp[(2) - (4)].ident).tipus != UNDEF)&&((yyvsp[(4) - (4)].ident).tipus != UNDEF)) {
											
											int comprovacio = 0;
											comprovacio = comprovacioTipus((yyvsp[(2) - (4)].ident).tipus, (yyvsp[(4) - (4)].ident).tipus);
											
											switch (comprovacio) {
												case COMPTIPUS_IGUALS:
													(yyval.ident).tipus = (yyvsp[(2) - (4)].ident).tipus;
													sprintf(string,"(Cast) Sense efecte algun.");
													missatgeTS(string,(yyvsp[(2) - (4)].ident).rows, (yyvsp[(2) - (4)].ident).columns);
												break;
												case COMPTIPUS_DIF_RED_PRIMER:
													(yyval.ident).tipus = (yyvsp[(2) - (4)].ident).tipus;
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(2) - (4)].ident).tipus, (yyvsp[(4) - (4)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(4) - (4)].ident).lexemac3a);
													localC3A = emet(filAux, localC3A);
													
													sprintf(string,"(Cast) a tipus %d.", (yyvsp[(2) - (4)].ident).tipus);
													missatgeWarning(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
												break;
												case COMPTIPUS_DIF_RED_SEGON:
													(yyval.ident).tipus = (yyvsp[(2) - (4)].ident).tipus;
													
													/*-----------------C3A------------------*/
													cast = nouTemp();
													filAux = inicialitzarFil(filAux);
													sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(2) - (4)].ident).tipus, (yyvsp[(4) - (4)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(2) - (4)].ident).lexemac3a);
													localC3A = emet(filAux, localC3A);
													
													sprintf(string,"(Cast) a tipus %d.", (yyvsp[(2) - (4)].ident).tipus);
													missatgeWarning(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
												break;
												case COMPTIPUS_DIF_NO_RED:
													sprintf(string,"ERROR. (Cast) - Impossible fer cast a tipus %d.", (yyvsp[(2) - (4)].ident).tipus);
													missatgeError(string,(yyvsp[(2) - (4)].ident).rows, (yyvsp[(2) - (4)].ident).columns);
													YYERROR;
												break;
											}
										}
										else{
											sprintf(string,"ERROR. Variable sense tipus.");
											missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
											YYERROR;
										}	
													
										
										sprintf(string,"cast_expression <- '(' type_name ')' cast_expression ");
										string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 548 "gramatica.y"
    {
											(yyval.ident) = (yyvsp[(1) - (1)].ident);
											sprintf(string,"multiplicative_expression <- cast_expression");
											string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 552 "gramatica.y"
    {
													if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", (yyvsp[(1) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", cast, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(3) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", (yyvsp[(3) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Els tipus no es poden reduir.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															break;
														}
														
													}
													else{
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
														YYERROR;
													}	
													
													sprintf(string,"multiplicative_expression <- multiplicative_expression '*' cast_expression ");
													string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 621 "gramatica.y"
    {
													if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", (yyvsp[(1) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", cast, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(3) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", (yyvsp[(3) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la multiplicacio.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															break;
														}
													}
													else {
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
														YYERROR;
													}		
													sprintf(string,"multiplicative_expression <- multiplicative_expression '/' cast_expression ");
													string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 688 "gramatica.y"
    {
													if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
														
														int comprovacio = 0;
														comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
														
														switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", (yyvsp[(1) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", cast, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(3) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", (yyvsp[(3) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_NO_RED:
																sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes al modul.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															break;
														}	
													}
													else {
														sprintf(string,"ERROR. Variable sense tipus.");
														missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
														YYERROR;
													}		
													sprintf(string,"multiplicative_expression <- multiplicative_expression '%' cast_expression ");
													string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 757 "gramatica.y"
    {
														(yyval.ident) = (yyvsp[(1) - (1)].ident);
														sprintf(string,"additive_expression <- multiplicative_expression ");
														string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 761 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															
															int comprovacio = 0;
															comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
															
															switch (comprovacio) {
															case COMPTIPUS_IGUALS:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_PRIMER:
																(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), cast);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", (yyvsp[(1) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
															case COMPTIPUS_DIF_RED_SEGON:
																(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																
																/*-----------------C3A------------------*/
																cast = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																(yyval.ident).lexemac3a = nouTemp();
																filAux = inicialitzarFil(filAux);
																sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", cast, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(3) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																localC3A = emet(filAux, localC3A);
																
																sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", (yyvsp[(3) - (3)].ident).tipus);
																missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															break;
																case COMPTIPUS_DIF_NO_RED:
																	sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la suma.");
																	missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																	YYERROR;
																break;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}	
														sprintf(string,"additive_expression <- additive_expression '+' multiplicative_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 828 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															
															int comprovacio = 0;
															comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
															switch (comprovacio) {
																case COMPTIPUS_IGUALS:
																	(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																	/*-----------------C3A------------------*/
																	(yyval.ident).lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Operacio correcta del mateix tipus. Tipus %d.", info.tipus);
																	missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																break;
																case COMPTIPUS_DIF_RED_PRIMER:
																	(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																	/*-----------------C3A------------------*/
																	cast = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	(yyval.ident).lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", (yyvsp[(1) - (3)].ident).lexemac3a, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus), cast);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Comprovacio de tipus - Cast pel tipus del primer operand %d.", (yyvsp[(1) - (3)].ident).tipus);
																	missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																break;
																case COMPTIPUS_DIF_RED_SEGON:
																	(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																	
																	/*-----------------C3A------------------*/
																	cast = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	(yyval.ident).lexemac3a = nouTemp();
																	filAux = inicialitzarFil(filAux);
																	sprintf(filAux.info, "%s %s %s %s %s", (yyval.ident).lexemac3a, ":=", cast, obtainOp((yyvsp[(2) - (3)].ident).lexema, (yyvsp[(3) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																	localC3A = emet(filAux, localC3A);
																	
																	sprintf(string,"Comprovacio de tipus - Cast pel tipus del segon operand %d.", (yyvsp[(3) - (3)].ident).tipus);
																	missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																break;
																case COMPTIPUS_DIF_NO_RED:
																	sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la resta.");
																	missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																	YYERROR;
																break;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}	
														sprintf(string,"additive_expression <- additive_expression '-' multiplicative_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 896 "gramatica.y"
    {sprintf(string,"relational_expression <- additive_expression ");
														string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 898 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else {
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("LT", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}	
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("LT", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("LT", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														
														sprintf(string,"arelational_expression <- relational_expression '<' additive_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 1018 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else {
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("GT", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("GT", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("GT", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression '>' additive_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 1135 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else {
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("LE", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("LE", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("LE", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression LE_OP additive_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 1253 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else{
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("GE", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("GE", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("GE", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														sprintf(string,"relational_expression <- relational_expression GE_OP additive_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 1373 "gramatica.y"
    {sprintf(string,"equality_expression <- relational_expression");
														string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 1375 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else{
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("EQ", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("EQ", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("EQ", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														sprintf(string,"equality_expression <- equality_expression EQ_OP relational_expression ");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 1493 "gramatica.y"
    {
														if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (3)].ident).sizeList != UNDEF)||((yyvsp[(3) - (3)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																YYERROR;
															}
															else{
																(yyval.ident).tipus = ID_INT;
																
																int comprovacio = 0;
																comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																switch (comprovacio) {
																	case COMPTIPUS_IGUALS:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			filAux = inicialitzarFil(filAux);
																			
																			sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("NE", (yyvsp[(1) - (3)].ident).tipus), (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																	break;
																	case COMPTIPUS_DIF_RED_PRIMER:
																		(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																	
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("NE", (yyvsp[(1) - (3)].ident).tipus), cast);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_RED_SEGON:
																		(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																		
																		/*-----------------C3A------------------*/
																		if (isFor == 0){	
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(1) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(castAux, "%s %s %s", cast, obtainCompare("NE", (yyvsp[(1) - (3)].ident).tipus),  (yyvsp[(3) - (3)].ident).lexemac3a);
																			
																			(yyval.ident).trueList = (int *)malloc(sizeof(int)*20);
																			(yyval.ident).falseList = (int *)malloc(sizeof(int)*20);
																			
																			(yyval.ident).trueList = crearllista((yyval.ident).trueList, getSquad());
																			(yyval.ident).falseList = crearllista((yyval.ident).falseList, getSquad()+1);
																			
																			(yyval.ident).nTrue++;
																			(yyval.ident).nFalse++;
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "IF %s GOTO ", castAux);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "GOTO ");
																			localC3A = emet(filAux, localC3A);
																		}
																		
																	break;
																	case COMPTIPUS_DIF_NO_RED:
																		sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes expressio relacional.");
																		missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		YYERROR;
																	break;
																}
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															YYERROR;
														}
														sprintf(string,"equality_expression <- equality_expression NE_OP relational_expression");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 1612 "gramatica.y"
    {sprintf(string,"logical_AND_expression <- equality_expression ");
														string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 1614 "gramatica.y"
    {
														if(((yyvsp[(1) - (4)].ident).tipus != UNDEF)&&((yyvsp[(4) - (4)].ident).tipus != UNDEF)) {
															if(((yyvsp[(1) - (4)].ident).sizeList != UNDEF)||((yyvsp[(4) - (4)].ident).sizeList != UNDEF)){
																sprintf(string,"ERROR. Operacio amb tipus Llista.");
																missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
																YYERROR;
															}
															else {
																(yyval.ident).tipus = ID_INT;
																(yyval.ident).trueList = (int*)malloc(sizeof(int)*20);
																(yyval.ident).falseList = (int*)malloc(sizeof(int)*20);
																
																localC3A = completa((yyvsp[(1) - (4)].ident).trueList, (yyvsp[(1) - (4)].ident).nTrue, (yyvsp[(3) - (4)].ident).quad, localC3A);
																(yyval.ident).falseList = fusiona((yyval.ident).falseList, (yyvsp[(1) - (4)].ident).falseList, (yyvsp[(1) - (4)].ident).nFalse, (yyvsp[(4) - (4)].ident).falseList, (yyvsp[(4) - (4)].ident).nFalse);
																
																(yyval.ident).trueList = (yyvsp[(4) - (4)].ident).trueList;
																(yyval.ident).nTrue = (yyvsp[(4) - (4)].ident).nTrue;
																
																(yyval.ident).nFalse = (yyvsp[(1) - (4)].ident).nFalse + (yyvsp[(4) - (4)].ident).nFalse;
															}
														}
														else{
															sprintf(string,"ERROR. Variable sense tipus.");
															missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
															YYERROR;
														}
														sprintf(string,"logical_AND_expression <- logical_AND_expression AND_OP equality_expression ");
														string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 1644 "gramatica.y"
    {sprintf(string,"logical_OR_expression <- logical_AND_expression");
															string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 1646 "gramatica.y"
    {
															if(((yyvsp[(1) - (4)].ident).tipus != UNDEF)&&((yyvsp[(4) - (4)].ident).tipus != UNDEF)) {
																if(((yyvsp[(1) - (4)].ident).sizeList != UNDEF)||((yyvsp[(4) - (4)].ident).sizeList != UNDEF)){
																	sprintf(string,"ERROR. Operacio amb tipus Llista.");
																	missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
																	YYERROR;
																}
																else {
																	(yyval.ident).tipus = ID_INT;
																	(yyval.ident).trueList = (int*)malloc(sizeof(int)*20);
																	(yyval.ident).falseList = (int*)malloc(sizeof(int)*20);
																	
																	localC3A = completa((yyvsp[(1) - (4)].ident).falseList, (yyvsp[(1) - (4)].ident).nFalse, (yyvsp[(3) - (4)].ident).quad, localC3A);
																	(yyval.ident).trueList = fusiona((yyval.ident).trueList, (yyvsp[(1) - (4)].ident).trueList, (yyvsp[(1) - (4)].ident).nTrue, (yyvsp[(4) - (4)].ident).trueList, (yyvsp[(4) - (4)].ident).nTrue);
																	
																	(yyval.ident).falseList = (yyvsp[(4) - (4)].ident).falseList;
																	(yyval.ident).nFalse = (yyvsp[(4) - (4)].ident).nFalse;
																	
																	(yyval.ident).nTrue = (yyvsp[(1) - (4)].ident).nTrue + (yyvsp[(4) - (4)].ident).nTrue;
																}
															}
															else{
																sprintf(string,"ERROR. Variable sense tipus.");
																missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
																YYERROR;
															}
															sprintf(string,"logical_OR_expression <- logical_OR_expression OR_OP logical_AND_expression  ");
															string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 1676 "gramatica.y"
    {
															sprintf(string,"conditional_expression <- logical_OR_expression ");
															string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 1679 "gramatica.y"
    {sprintf(string,"conditional_expression <- logical_OR_expression '?' expression ':' conditional_expression ");
																		string_output(string, (yyvsp[(1) - (5)].ident).rows, (yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 1683 "gramatica.y"
    {
												(yyval.ident) = (yyvsp[(1) - (1)].ident);
												sprintf(string,"constant_expression <- conditional_expression ");
												string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 1689 "gramatica.y"
    {
														(yyval.ident) = (yyvsp[(1) - (1)].ident);
														sprintf(string,"assignment_expression <- conditional_expression ");
														string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 1693 "gramatica.y"
    {
																if(((yyvsp[(1) - (3)].ident).tipus != UNDEF)&&((yyvsp[(3) - (3)].ident).tipus != UNDEF)) {
																	int comprovacio = 0;
																	
																	comprovacio = comprovacioTipus((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus);
																	
																	switch (comprovacio) {
																		case COMPTIPUS_IGUALS:
																			(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																			
																			/*-----------------C3A------------------*/
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, ":=", (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Operacio correcta del mateix tipus.");
																			missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		break;
																		case COMPTIPUS_DIF_RED_PRIMER:
																			(yyval.ident).tipus = (yyvsp[(1) - (3)].ident).tipus;
																			
																			/*-----------------C3A------------------*/
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(1) - (3)].ident).tipus, (yyvsp[(3) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, ":=", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Comprovacio de tipus - (cast) al tipus %d ", (yyvsp[(1) - (3)].ident).tipus);
																			missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		break;
																		case COMPTIPUS_DIF_RED_SEGON:
																			(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
																			
																			/*-----------------C3A------------------*/
																			cast = nouTemp();
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast((yyvsp[(3) - (3)].ident).tipus, (yyvsp[(1) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(3) - (3)].ident).lexemac3a);
																			localC3A = emet(filAux, localC3A);
																			
																			filAux = inicialitzarFil(filAux);
																			sprintf(filAux.info, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, ":=", cast);
																			localC3A = emet(filAux, localC3A);
																			
																			sprintf(string,"Comprovacio de tipus - Perdua de presicio en l'assignacio (cast) al tipus %d.", (yyvsp[(1) - (3)].ident).tipus);
																			missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																		break;
																		case COMPTIPUS_DIF_NO_RED:
																			sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la assignacio.");
																			missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																			YYERROR;
																		break;
																	}
																}
																else{
																	sprintf(string,"ERROR. Variable sense tipus.");
																	missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
																	YYERROR;
																}	
																	
																sprintf(string,"assignment_expression <- unary_expression assignment_operator assignment_expression ");
																string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 1760 "gramatica.y"
    {sprintf(string,"assignment_operator <- '=' ");
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 1762 "gramatica.y"
    {sprintf(string,"assignment_operator <- MUL_ASSIG %s", (yyvsp[(1) - (1)].ident).lexema);
					string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 1764 "gramatica.y"
    {sprintf(string,"assignment_operator <- DIV_ASSIG %s", (yyvsp[(1) - (1)].ident).lexema);
					string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 1766 "gramatica.y"
    {sprintf(string,"assignment_operator <- MOD_ASSIG %s", (yyvsp[(1) - (1)].ident).lexema);
					string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 1768 "gramatica.y"
    {sprintf(string,"assignment_operator <- ADD_ASSIG %s", (yyvsp[(1) - (1)].ident).lexema);
					string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 1770 "gramatica.y"
    {sprintf(string,"assignment_operator <- SUB_ASSIG %s", (yyvsp[(1) - (1)].ident).lexema);
					string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 1774 "gramatica.y"
    {sprintf(string,"expression <- assignment_expression");
										string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 1776 "gramatica.y"
    {sprintf(string,"expression <- expression ',' assignment_expression");
											string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 1780 "gramatica.y"
    {sprintf(string,"declaration <- declaration_specifiers ; ");
											string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 1782 "gramatica.y"
    {
														if (isFunction == 1){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup(nom_funcio,&info);
															}
															else{
																error_sym=sym_lookup(nom_funcio,&info);
															}
															sprintf(string,"Guardada la declaracio de la funcio %s",nom_funcio);
															missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															info.isFunctionDeclaration = 1;
															isFunction = 0;
															sym_remove(nom_funcio);
															sym_add(nom_funcio,&info);
														}
														if (tipus_declaracio == ID_STRUCT){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup(nom_id,&info);
															}
															else{
																error_sym=sym_lookup(nom_id,&info);
															}
															sprintf(string,"Guardat el tipus d'struct de %s amb %s",(yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).lexema);
															missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
															
															strcpy(info.valor, (yyvsp[(1) - (3)].ident).lexema);
															
															sym_remove(nom_id);
															sym_add(nom_id,&info);
															
															filaAux = inicialitzarFila(filaAux);
															filaAux.nom = (yyvsp[(2) - (3)].ident).lexema;
															filaAux.mida = obtenirMidaStruct(info.valor);
															
															if (ambit_actual==SYM_ROOT_SCOPE){
																filaAux.offset = offsetG;
																offsetG = filaAux.mida + offsetG;
																globalRA = introduirFila(filaAux, globalRA);
															}
															else{
																filaAux.offset = offsetL;
																offsetL = filaAux.mida + offsetL;
																localRA = introduirFila(filaAux, localRA);
															}
															
														}
														sprintf(string,"declaration <- declaration_specifiers init_declarator_list ;");
														string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 1834 "gramatica.y"
    {
														if(isStruct == 0){
															inicialitzarInfo();
															ambit_actual=sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_lookup((yyvsp[(3) - (4)].ident).lexema,&info);
															}
															else{
																error_sym=sym_lookup((yyvsp[(3) - (4)].ident).lexema,&info);
															}
															
															if(error_sym == SYMTAB_OK){
																sprintf(string,"(TS) Trobat l'identificador %s a la TS.", (yyvsp[(3) - (4)].ident).lexema);
																missatgeTS(string,(yyvsp[(3) - (4)].ident).rows, (yyvsp[(3) - (4)].ident).columns);
																if(info.tipus == UNDEF){
																	info.tipus = ID_TYPEDEF;
																	info.tipusTypedef = tipus_declaracio;
																	sym_remove(nom_id);
																	sym_add(nom_id,&info);
																	sprintf(string,"Modificat el tipus de l'identificador %s amb tipus TYPEDEF que es %d", (yyvsp[(3) - (4)].ident).lexema, info.tipusTypedef);
																	missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
																}
																else{
																	sprintf(string,"ERROR. Variable ja definida.");
																	missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
																}	
															}
															else{
																sprintf(string,"ERROR. Variable no definida.");
																missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
															}
														} 
														else{
															
															strcpy(info.lexema, (yyvsp[(3) - (4)].ident).lexema);
															info.tipus = ID_TYPEDEF;
															info.tipusTypedef = ID_STRUCT;
															
															ambit_actual = sym_get_scope();
															if (ambit_actual==SYM_ROOT_SCOPE){
																error_sym=sym_global_add(nom_id,&info);
															}
															else{
																error_sym=sym_add(nom_id,&info);
															}
															
															sprintf(string,"TYPEDEF %s introduit a la TS com a STRUCT.", nom_id);
															missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
															
															isStruct = 0;
														}
														sprintf(string,"declaration <- TYPEDEF declaration_specifiers declarator ;");
														string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 1887 "gramatica.y"
    {	sprintf(string,"ERROR. TYPEDEF mal declarat.");
										missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
										yyerrok;;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 1891 "gramatica.y"
    {	sprintf(string,"ERROR. TYPEDEF mal declarat.");
													missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													yyerrok;;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 1895 "gramatica.y"
    {yyerrok;;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 1898 "gramatica.y"
    {
											(yyval.ident)=(yyvsp[(1) - (1)].ident);
											sprintf(string,"declaration_specifiers <- type_specifier ");
											string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 1904 "gramatica.y"
    {sprintf(string,"init_declarator_list <- init_declarator ");
												string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 1906 "gramatica.y"
    {sprintf(string,"init_declarator_list <- init_declarator_list ',' init_declarator ");
												string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 1910 "gramatica.y"
    {
									inicialitzarInfo();
									ambit_actual=sym_get_scope();
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
									}
									else{
										error_sym=sym_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
									}
									
									if(error_sym == SYMTAB_OK){
										sprintf(string,"(TS) Trobat l'identificador %s a la TS.", (yyvsp[(1) - (1)].ident).lexema);
										missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
										if(info.tipus == UNDEF){
											info.tipus = tipus_declaracio;
											
											sym_remove(nom_id);
											sym_add(nom_id,&info);
											sprintf(string,"Modificat el tipus de l'identificador %s amb tipus %d", (yyvsp[(1) - (1)].ident).lexema, info.tipus);
											missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
											
											filaAux = inicialitzarFila(filaAux);
											
											filaAux.nom = (yyvsp[(1) - (1)].ident).lexema;
											
											if(info.sizeList > -1){
												filaAux.mida = obtenirMida(info.tipus);
												if (ambit_actual==SYM_ROOT_SCOPE){
													filaAux.offset = offsetG;
													offsetG = (filaAux.mida * info.sizeList) + offsetG;
													globalRA = introduirFila(filaAux, globalRA);
												}
												else{
													filaAux.offset = offsetL;
													offsetL = (filaAux.mida * info.sizeList) + offsetL;
													localRA = introduirFila(filaAux, localRA);
												}
											}else if (info.tipus != ID_STRUCT) {
												filaAux.mida = obtenirMida(info.tipus);
												if (ambit_actual==SYM_ROOT_SCOPE){
													
													filaAux.offset = offsetG;
													offsetG += filaAux.mida;
													globalRA = introduirFila(filaAux, globalRA);
													
												}
												else{
													filaAux.offset = offsetL;
													offsetL += filaAux.mida;
													localRA = introduirFila(filaAux, localRA);
												}
											}
										}
										else if (info.tipus == FUNCTION){
										}
										else{
											sprintf(string,"ERROR. Variable ja definida.");
											missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
										}
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
									}
									
									sprintf(string,"init_declarator <- declarator ");
									string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 1977 "gramatica.y"
    {
									inicialitzarInfo();
									ambit_actual=sym_get_scope();
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup((yyvsp[(1) - (3)].ident).lexema,&info);
									}
									else{
										error_sym=sym_lookup((yyvsp[(1) - (3)].ident).lexema,&info);
									}
									if(error_sym == SYMTAB_OK){
										sprintf(string,"(TS) Trobat l'identificador %s a la TS.", (yyvsp[(1) - (3)].ident).lexema);
										missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
										if(info.tipus == UNDEF){
											if(info.sizeList == UNDEF){
												if((yyvsp[(1) - (3)].ident).tipus == (yyvsp[(3) - (3)].ident).tipus){
													(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
													info.tipus = tipus_declaracio;
													strcpy(info.valor, (yyvsp[(3) - (3)].ident).lexema);
													sym_remove(nom_id);
													sym_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s amb tipus %d", (yyvsp[(1) - (3)].ident).lexema, info.tipus);
													missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
													
												}else{
													sprintf(string,"ERROR. Tipus incorrectes en l'assignacio.");
													missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
													YYERROR;
												}	
											}
											/* si es una llista*/
											else{
												(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
												info.tipus = tipus_declaracio;
												if(info.sizeList != nparams_initializer_list){
													sprintf(string,"ERROR. El numero de parametres no coincideix amb la declaracio.");
													missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
												}
												else {
													sym_remove(nom_id);
													sym_add(nom_id,&info);
												}
											}
										}
										else {
											sprintf(string,"ERROR. Variable ja inicialitzada.");
											missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
											YYERROR;
										}
										
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
										YYERROR;
									}
									sprintf(string,"init_declarator <- declarator '=' initializer");
									string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 2036 "gramatica.y"
    {
						tipus_declaracio = ID_VOID;
						(yyval.ident).tipus = ID_VOID;
						sprintf(string,"type_specifier <- VOID ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 2041 "gramatica.y"
    {
						tipus_declaracio = ID_CHAR;
						(yyval.ident).tipus = ID_CHAR;
						sprintf(string,"type_specifier <- CHAR ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 2046 "gramatica.y"
    {
						tipus_declaracio = ID_SHORT;
						(yyval.ident).tipus = ID_SHORT;
						sprintf(string,"type_specifier <- SHORT ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 2051 "gramatica.y"
    {
						
						tipus_declaracio = ID_INT;
						(yyval.ident).tipus = ID_INT;
						sprintf(string,"type_specifier <- INT ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 2057 "gramatica.y"
    {
						tipus_declaracio = ID_LONG;
						(yyval.ident).tipus = ID_LONG;
						sprintf(string,"type_specifier <- LONG ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 2062 "gramatica.y"
    {
						tipus_declaracio = ID_FLOAT;
						(yyval.ident).tipus = ID_FLOAT;
						sprintf(string,"type_specifier <- FLOAT ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 2067 "gramatica.y"
    {
						tipus_declaracio = ID_DOUBLE;
						(yyval.ident).tipus = ID_DOUBLE;
						sprintf(string,"type_specifier <- DOUBLE ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 2072 "gramatica.y"
    {
								
								sprintf(string,"type_specifier <- struct_or_union_specifier");
								string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 2076 "gramatica.y"
    {
						
						sprintf(string,"type_specifier <- typedef_name ");
						string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 2082 "gramatica.y"
    {
									inicialitzarInfo();
									
									ambit_actual=sym_get_scope();
									
									if (ambit_actual==SYM_ROOT_SCOPE){
										error_sym=sym_global_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
									}
									else{
										error_sym=sym_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
									}
									
									if(error_sym == SYMTAB_OK){
										sprintf(string,"Trobat l'identificador %s a la TS.", (yyvsp[(1) - (1)].ident).lexema);
										missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
										(yyval.ident).tipus=info.tipusTypedef;
										tipus_declaracio = info.tipusTypedef;
									}
									else{
										sprintf(string,"ERROR. Variable no definida.");
										missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
										YYERROR;
									}
									
									sprintf(string,"typedef_name <- TYPEDEF_IDENTIFIER ");
									string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 2110 "gramatica.y"
    {
																						sprintf(string,"struct_or_union_specifier <- struct_or_union IDENTIFIER '{' struct_declaration_list '}'");
																						string_output(string, (yyvsp[(1) - (5)].ident).rows, (yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 2113 "gramatica.y"
    {
																						
																						sprintf(string,"struct_or_union_specifier <- struct_or_union '{' struct_declaration_list '}' ");
																						string_output(string, (yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 2119 "gramatica.y"
    {
							isStruct = 1;
							
							inicialitzarInfo();
									
							info.tipus = ID_TYPEDEF;
							info.tipusFunction = STRUCT;
							info.nParamsFuncio = 0;
							
							sprintf(string,"struct_or_union <- STRUCT ");
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 2130 "gramatica.y"
    {sprintf(string,"struct_or_union <- UNION ");
							string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 2134 "gramatica.y"
    {sprintf(string,"struct_declaration_list <- struct_declaration ");
													string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 2136 "gramatica.y"
    {sprintf(string,"struct_declaration_list <- struct_declaration_list struct_declaration ");
													string_output(string, (yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 2140 "gramatica.y"
    {
																			info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof(char)*20);
																			strcpy(info.parametres[info.nParamsFuncio].lexema, (yyvsp[(2) - (3)].ident).lexema);
																			info.parametres[info.nParamsFuncio].type = (yyvsp[(1) - (3)].ident).tipus;
																			info.nParamsFuncio++;
																			
																			
																			sprintf(string,"Parametre %s de tipus %d introduit al struct.", (yyvsp[(2) - (3)].ident).lexema, (yyvsp[(1) - (3)].ident).tipus);
																			missatgeTS(string,(yyvsp[(2) - (3)].ident).rows, (yyvsp[(2) - (3)].ident).columns);
																			
																			
																			sprintf(string,"struct_declaration <- specifier_qualifier_list struct_declarator_list ';' ");
																			string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 2155 "gramatica.y"
    {sprintf(string,"struct_declarator_list <- struct_declarator");
													string_output(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 2157 "gramatica.y"
    {sprintf(string,"struct_declarator_list <- struct_declarator_list ',' struct_declarator");
													string_output(string, (yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 2161 "gramatica.y"
    {
									
									
									sprintf(string,"struct_declarator <- declarator");
									string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 2168 "gramatica.y"
    {
							nom_id=(char *)malloc(sizeof(char)*(yyvsp[(1) - (1)].ident).lenght);
							strncpy(nom_id, (yyvsp[(1) - (1)].ident).lexema, (yyvsp[(1) - (1)].ident).lenght);
							if (isStruct == 0){
								inicialitzarInfo();
								ambit_actual = sym_get_scope();
								
								
								strcpy(info.lexema, nom_id);
								info.tipus = UNDEF;
								
								(yyval.ident).tipus = tipus_declaracio;
								
								info.ambit = ambit_actual;
								
								if(isFunction == 0){
										
										if (ambit_actual == SYM_ROOT_SCOPE){            
											error_sym = sym_global_add(nom_id,&info);
										}                                                
										else{                                            
											error_sym = sym_add(nom_id,&info);        
										}                                          
										if(error_sym == SYMTAB_OK){
											if(isFunction == 0){
												if(ambit_actual == SYM_ROOT_SCOPE ){
													sprintf(string,"Creada l'entrada a la TS dins de l'ambit global %s per a l'identificador %s ",nom_programa,(yyvsp[(1) - (1)].ident).lexema);
													missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
												}
												else{
													sprintf(string,"Creada l'entrada a la TS dins de l'ambit %s per a l'identificador %s ",nom_ambit,(yyvsp[(1) - (1)].ident).lexema);
													missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
												}
											}
										}
										else{
											ambit_actual=sym_get_scope();
											error_sym=sym_global_lookup((yyvsp[(1) - (1)].ident).lexema,&info);
											
												if(info.tipus != FUNCTION){
													sprintf(string,"ERROR. La variable ja existeix.");
													missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
													YYERROR;
												}
												else{
													if(tipus_declaracio != info.tipusFunction){
														sprintf(string,"ERROR. La funcio retorna un tipus incoherent a la declaracio anterior.");
														missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
														
														/*YYERROR;*/
													}
													else{
														numParam = 0;
														/*isFunctionDeclaration = 1;*/
													}
												}
											
										}
									
								}
								else{
									sprintf(string,"Parametre de la funcio de nom %s ", nom_id);
									missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
								}
							}else{ /* quan es una declaracio dins de struct*/
								(yyval.ident).tipus = tipus_declaracio;
							}
							
							sprintf(string,"declarator <- IDENTIFIER %s ", (yyvsp[(1) - (1)].ident).lexema);
							string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 2238 "gramatica.y"
    {sprintf(string,"declarator <- '(' declarator ')'");
							string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 2240 "gramatica.y"
    {
											inicialitzarInfo();
											nparams_initializer_list = 0;
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup((yyvsp[(1) - (4)].ident).lexema,&info);
											}
											else{
												error_sym=sym_lookup((yyvsp[(1) - (4)].ident).lexema,&info);
											}
											
											if(error_sym == SYMTAB_OK){
												sprintf(string,"(TS) Trobat l'identificador %s a la TS.", (yyvsp[(1) - (4)].ident).lexema);
												missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
												if(info.tipus == UNDEF){
													(yyval.ident).tipus = (yyvsp[(3) - (4)].ident).tipus;
													info.tipus = UNDEF;
													info.sizeList = atoi((yyvsp[(3) - (4)].ident).lexema);
													sym_remove(nom_id);
													sym_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s a Llista %d posicions.", (yyvsp[(1) - (4)].ident).lexema, info.sizeList);
													missatgeTS(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													
												}
												else{
													sprintf(string,"ERROR. Variable ja definida.");
													missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
													YYERROR;
												}	
											}
											else{
												sprintf(string,"ERROR. Variable no definida.");
												missatgeError(string,(yyvsp[(1) - (4)].ident).rows, (yyvsp[(1) - (4)].ident).columns);
												YYERROR;
											}
											sprintf(string,"declarator <- declarator '[' INTEGER_CONSTANT ']'");
											string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 2277 "gramatica.y"
    {
						inicialitzarInfo();
						ambit_actual=sym_get_scope();
						if (ambit_actual==SYM_ROOT_SCOPE){
							error_sym=sym_global_lookup((yyvsp[(1) - (2)].ident).lexema,&info);
						}
						else{
							error_sym=sym_lookup((yyvsp[(1) - (2)].ident).lexema,&info);
						}
						
						isFunction = 1;
						
						
						nom_funcio=(char *)malloc(sizeof(char)*(yyvsp[(1) - (2)].ident).lenght);
						strcpy(nom_funcio, (yyvsp[(1) - (2)].ident).lexema);
						
						if(error_sym == SYMTAB_OK){
							inicialitzarInfo();
							error_sym=sym_global_lookup(nom_funcio,&info);
							if(info.isFunctionDeclaration == 0){
								info.tipus = FUNCTION;
								info.tipusFunction = tipus_declaracio;
								
								/*Funcio de CL2*/
								if (info.tipusFunction != ID_VOID){
									filaAux = inicialitzarFila(filaAux);
									filaAux.nom = "return";
											
									filaAux.mida = obtenirMida(info.tipusFunction);
									filaAux.offset = offsetL;
										
									offsetL += filaAux.mida;
									
									localRA = introduirFila(filaAux, localRA);
								}
								
								info.nParamsFuncio = 0;
								sym_remove(nom_funcio);
								sym_global_add(nom_funcio,&info);
								sprintf(string,"Modificat el tipus de l'identificador %s. Es una funcio.", (yyvsp[(1) - (2)].ident).lexema);
								missatgeTS(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
								isFunction = 1;
							}
						}
						
					;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 2322 "gramatica.y"
    {
											/*isFunction = 0;*/
											
											sprintf(string,"declarator <- declarator '(' parameter_list ')'");
											string_output(string,(yyvsp[(1) - (5)].ident).rows,(yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 2327 "gramatica.y"
    {sprintf(string,"declarator <- declarator '(' identifier_list ')'");
											string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 2329 "gramatica.y"
    {
											inicialitzarInfo();
											ambit_actual=sym_get_scope();
											if (ambit_actual==SYM_ROOT_SCOPE){
												error_sym=sym_global_lookup((yyvsp[(1) - (3)].ident).lexema,&info);
											}
											else{
												error_sym=sym_lookup((yyvsp[(1) - (3)].ident).lexema,&info);
											}
											
											nom_funcio=(char *)malloc(sizeof(char)*(yyvsp[(1) - (3)].ident).lenght);
											strcpy(nom_funcio, (yyvsp[(1) - (3)].ident).lexema);
											
											if(error_sym == SYMTAB_OK){
												if(info.tipus == UNDEF){
													info.tipus = FUNCTION;
													info.tipusFunction = tipus_declaracio;
													
													/*Funcio de CL2*/
													if (info.tipusFunction != ID_VOID){
														filaAux = inicialitzarFila(filaAux);
														filaAux.nom = "return";
																
														filaAux.mida = obtenirMida(info.tipusFunction);
														filaAux.offset = offsetL;
															
														offsetL += filaAux.mida;
														
														localRA = introduirFila(filaAux, localRA);
													}
													
													info.nParamsFuncio = 0;
													sym_global_remove(nom_id);
													sym_global_add(nom_id,&info);
													sprintf(string,"Modificat el tipus de l'identificador %s. Es una funcio.", (yyvsp[(1) - (3)].ident).lexema);
													missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
													
												}
											}
											
											
											isFunction = 0;
											sprintf(string,"declarator <- declarator '(' ')'");
											string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 2373 "gramatica.y"
    {yyerrok;;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 2376 "gramatica.y"
    {sprintf(string,"parameter_list <- parameter_declaration");
												string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 2378 "gramatica.y"
    {sprintf(string,"parameter_list <- parameter_list ',' parameter_declaration");
												string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 2382 "gramatica.y"
    {
											inicialitzarInfo();
											/*Recuperem la funcio per guardar-hi el parametre*/
											error_sym = sym_global_lookup(nom_funcio,&info);
											if(info.isFunctionDeclaration == 1){
													inicialitzarInfo();
												
													/*Recuperem la funcio per guardar-hi el parametre*/
													error_sym=sym_global_lookup(nom_funcio,&info);
												
												if (info.parametres[numParam].type != (yyvsp[(1) - (2)].ident).tipus){
													if (numParam >= info.nParamsFuncio){
														sprintf(string,"ERROR. El parametre numero %d de la funcio no esta a la declaracio.", numParam+1);
														missatgeError(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
														info.nParamsFuncio++;
													}
													else{
														sprintf(string,"ERROR. El tipus de la variable %d no coincideix amb la declaracio.", numParam+1);
														missatgeError(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
													}
													info.parametres[numParam].lexema = (char *)malloc(sizeof((yyvsp[(2) - (2)].ident).lexema));
													info.parametres[numParam].hasName = 1;
													info.parametres[numParam].type = (yyvsp[(1) - (2)].ident).tipus;
													strcpy(info.parametres[numParam].lexema, (yyvsp[(2) - (2)].ident).lexema);
													sym_global_remove(nom_funcio);
													sym_global_add(nom_funcio,&info);
													numParam++;
												}
												else{
													info.parametres[numParam].lexema = (char *)malloc(sizeof((yyvsp[(2) - (2)].ident).lexema));
													info.parametres[numParam].hasName = 1;
													strcpy(info.parametres[numParam].lexema, (yyvsp[(2) - (2)].ident).lexema);
													sym_global_remove(nom_funcio);
													sym_global_add(nom_funcio,&info);
													numParam++;
												}
											}
											else if (isFunction == 1){
												inicialitzarInfo();
												
												/*Recuperem la funcio per guardar-hi el parametre*/
												error_sym=sym_global_lookup(nom_funcio,&info);
												info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof((yyvsp[(2) - (2)].ident).lexema)+1);
												
												info.parametres[info.nParamsFuncio].type= (yyvsp[(1) - (2)].ident).tipus;
												info.parametres[info.nParamsFuncio].hasName = 1;
												
												strcpy(info.parametres[info.nParamsFuncio].lexema, (yyvsp[(2) - (2)].ident).lexema);
												
												info.nParamsFuncio++;
												numParam++;
												
												sym_global_remove(nom_funcio);
												sym_global_add(nom_funcio,&info);
												
												
												
												filaAux = inicialitzarFila(filaAux);
												filaAux.nom = (yyvsp[(2) - (2)].ident).lexema;
												
												filaAux.mida = obtenirMida((yyvsp[(1) - (2)].ident).tipus);
												filaAux.offset = offsetL;
												
												offsetL += filaAux.mida;
												
												localRA = introduirFila(filaAux, localRA);
												
												
												
												sprintf(string,"Guardat l'identificador %s com a parametre de la funcio %s.", (yyvsp[(2) - (2)].ident).lexema, nom_funcio);
												missatgeTS(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
											}
											sprintf(string,"parameter_declaration <- declaration_specifiers declarator");
											string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 2456 "gramatica.y"
    {sprintf(string,"parameter_declaration <- declaration_specifiers abstract_declarator");
									string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 2458 "gramatica.y"
    {
							inicialitzarInfo();
							/*Recuperem la funcio per guardar-hi el parametre*/
							error_sym = sym_global_lookup(nom_funcio,&info);
							if(info.isFunctionDeclaration == 1){
								inicialitzarInfo();
								
								/*Recuperem la funcio per guardar-hi el parametre*/
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								if (info.parametres[numParam].type != (yyvsp[(1) - (1)].ident).tipus){
									sprintf(string,"ERROR. Variable no definida.");
									missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
									numParam++;
								}
								else{
									numParam++;
								}
							}
							else if (isFunction == 1){
								inicialitzarInfo();
								/*Recuperem la funcio per guardar-hi el parametre*/
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								
								
								info.parametres[info.nParamsFuncio].lexema = (char *)malloc(sizeof(4)+1);
								
								info.parametres[info.nParamsFuncio].type= (yyvsp[(1) - (1)].ident).tipus;
								info.parametres[info.nParamsFuncio].hasName = 0;
								strcpy(info.parametres[info.nParamsFuncio].lexema, "NULL");
								
								info.nParamsFuncio++;
								sym_global_remove(nom_funcio);
								sym_global_add(nom_funcio,&info);
								
								
								
								
								filaAux = inicialitzarFila(filaAux);
								filaAux.nom = "NULL";
								
								filaAux.mida = obtenirMida((yyvsp[(1) - (1)].ident).tipus);
								filaAux.offset = offsetL;
								
								offsetL += filaAux.mida;
								
								localRA = introduirFila(filaAux, localRA);
								
								sprintf(string,"Guardat el tipus %d com a parametre de la funcio %s.", (yyvsp[(1) - (1)].ident).tipus, nom_funcio);
								missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
							}
							sprintf(string,"parameter_declaration <- declaration_specifiers");
							string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 2514 "gramatica.y"
    {		
									sprintf(string,"identifier_list <- IDENTIFIER");
									string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 2517 "gramatica.y"
    {
									
									sprintf(string,"identifier_list <- identifier_list ',' IDENTIFIER ");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 2523 "gramatica.y"
    {
									(yyval.ident) = (yyvsp[(1) - (1)].ident);
									sprintf(string,"type_name <- specifier_qualifier_list");
									string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 2527 "gramatica.y"
    {sprintf(string,"type_name <- specifier_qualifier_list abstract_declarator");
									string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 2531 "gramatica.y"
    {sprintf(string,"specifier_qualifier_list <- type_specifier specifier_qualifier_list");
									string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 2533 "gramatica.y"
    {sprintf(string,"specifier_qualifier_list <- type_specifier");
									string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 2537 "gramatica.y"
    {sprintf(string,"abstract_declarator <- '(' abstract_declarator ')'");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 2539 "gramatica.y"
    {sprintf(string,"abstract_declarator <- '[' INTEGER_CONSTANT ']'");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 2541 "gramatica.y"
    {sprintf(string,"abstract_declarator <- abstract_declarator '[' INTEGER_CONSTANT ']'");
									string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 2543 "gramatica.y"
    {sprintf(string,"abstract_declarator <- '(' ')'");
									string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 2545 "gramatica.y"
    {sprintf(string,"abstract_declarator <- '(' parameter_list ')'");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 2547 "gramatica.y"
    {sprintf(string,"abstract_declarator <- abstract_declarator '(' ')'");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 2549 "gramatica.y"
    {sprintf(string,"abstract_declarator <- abstract_declarator '(' parameter_list ')'");
									string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 2553 "gramatica.y"
    {sprintf(string,"initializer <- assignment_expression");
									string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 2555 "gramatica.y"
    {sprintf(string,"initializer <- '{' initializer_list '}'");
								string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 2557 "gramatica.y"
    {sprintf(string,"initializer <- '{' initializer_list ',' '}'");
									string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 2561 "gramatica.y"
    {
								if((yyvsp[(1) - (1)].ident).tipus == tipus_declaracio){
									nparams_initializer_list ++;
									(yyval.ident).tipus = (yyvsp[(1) - (1)].ident).tipus;
								}else{
									sprintf(string,"ERROR. Tipus incorrectes en la incialitzacio de la taula.");
									missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
									YYERROR;
								}
								sprintf(string,"initializer_list <- initializer");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 2572 "gramatica.y"
    {
										if((yyvsp[(3) - (3)].ident).tipus == tipus_declaracio){
											nparams_initializer_list ++;
											(yyval.ident).tipus = (yyvsp[(3) - (3)].ident).tipus;
										}else{
											sprintf(string,"ERROR. Tipus incorrectes en la incialitzacio de la taula.");
											missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
											YYERROR;
										}
										sprintf(string,"initializer_list <- initializer_list ',' initializer ");
										string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 2585 "gramatica.y"
    {sprintf(string,"statement <- abeled_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 2587 "gramatica.y"
    {sprintf(string,"statement <- compound_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 2589 "gramatica.y"
    {sprintf(string,"statement <- expression_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 2591 "gramatica.y"
    {sprintf(string,"statement <- selection_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 2593 "gramatica.y"
    {sprintf(string,"statement <- iteration_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 2595 "gramatica.y"
    {sprintf(string,"statement <- jump_statement");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 2599 "gramatica.y"
    {sprintf(string,"labeled_statement <- CASE constant_expression ':' statement");
															string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 2601 "gramatica.y"
    {sprintf(string,"labeled_statement <- DEFAULT ':' statement");
								string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 2605 "gramatica.y"
    { 
							if(isReturn == 0){
							/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
							inicialitzarInfo();
							
							ambit_actual=sym_get_scope();
							error_sym=sym_global_lookup(nom_funcio,&info);
							
							if(error_sym == SYMTAB_OK){
								if(info.tipusFunction != ID_VOID){
									sprintf(string,"No hi ha sentencia RETURN. falta retornar un valor de tipus %d ", info.tipusFunction);
									missatgeWarning(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
								}
							}
						  }
						;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 2621 "gramatica.y"
    {sprintf(string,"compound_statement <- '{' '}' ");
								string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 2623 "gramatica.y"
    {
								if(isReturn == 0){
								  	/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
								  	inicialitzarInfo();
							
									ambit_actual=sym_get_scope();
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(error_sym == SYMTAB_OK){
										if(info.tipusFunction != ID_VOID){
											sprintf(string,"No hi ha sentencia RETURN. falta retornar un valor de tipus %d ", info.tipusFunction);
											missatgeWarning(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
										}
									}
								}
								;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 2638 "gramatica.y"
    {sprintf(string,"compound_statement <- '{' declaration_list '}'");
								string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 2640 "gramatica.y"
    {
							if(isReturn == 0){
							  	/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
							  	inicialitzarInfo();
								
								ambit_actual=sym_get_scope();
								error_sym=sym_global_lookup(nom_funcio,&info);
								
								if(error_sym == SYMTAB_OK){
									if(info.tipusFunction != ID_VOID){
										sprintf(string,"No hi ha sentencia RETURN. falta retornar un valor de tipus %d ", info.tipusFunction);
										missatgeWarning(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
									}
								}
							}
							;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 2655 "gramatica.y"
    {			(yyval.ident).nextList = (int *) malloc(sizeof(int)*20);
												(yyval.ident).nextList = (yyvsp[(2) - (4)].ident).nextList;
												(yyval.ident).nNext = (yyvsp[(2) - (4)].ident).nNext;
												
												sprintf(string,"compound_statement <- '{' statement_list '}' ");
												string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 2661 "gramatica.y"
    {  
										  if(isReturn == 0){
										  	/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
										  	inicialitzarInfo();
									
											ambit_actual=sym_get_scope();
											error_sym=sym_global_lookup(nom_funcio,&info);
											
											if(error_sym == SYMTAB_OK){
												if(info.tipusFunction != ID_VOID){
													sprintf(string,"No hi ha sentencia RETURN. Falta retornar un valor de tipus %d ", info.tipusFunction);
													missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
												}
											}
										  }
										  ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 2676 "gramatica.y"
    {sprintf(string,"compound_statement <- '{' declaration_list statement_list '}'");
												string_output(string,(yyvsp[(1) - (5)].ident).rows,(yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 2680 "gramatica.y"
    {
								
								/* la llista de seguentes es copia */
								
								sprintf(string,"statement_list <- statement ");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 2686 "gramatica.y"
    {
									
									localC3A = completa((yyvsp[(1) - (3)].ident).nextList, (yyvsp[(1) - (3)].ident).nNext, (yyvsp[(2) - (3)].ident).quad, localC3A);
									
									(yyval.ident).nextList = (yyvsp[(3) - (3)].ident).nextList;
									(yyval.ident).nNext = (yyvsp[(3) - (3)].ident).nNext;
									
									sprintf(string,"statement_list <- statement_list statement ");
									string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 2697 "gramatica.y"
    {sprintf(string,"expression_statement <- ';' ");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 2699 "gramatica.y"
    {sprintf(string,"expression_statement <- expression ';' ");
								string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 2703 "gramatica.y"
    {
		 (yyval.ident).quad = getSquad();
	;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 2708 "gramatica.y"
    {
		(yyval.ident).nextList = (int*)malloc(20*sizeof(int));
		(yyval.ident).nextList = crearllista((yyval.ident).nextList, getSquad());
		(yyval.ident).nNext++;
		
		filAux = inicialitzarFil(filAux);
		sprintf(filAux.info, "GOTO ");
		localC3A = emet(filAux, localC3A);	 
	;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 2719 "gramatica.y"
    {
															
															/*------------------------C3A----------------------*/
															localC3A = completa((yyvsp[(3) - (6)].ident).trueList, (yyvsp[(3) - (6)].ident).nTrue, (yyvsp[(5) - (6)].ident).quad, localC3A);
															
															(yyval.ident).nextList = (int*)malloc(20*sizeof(int));
															(yyval.ident).nextList = fusiona((yyval.ident).nextList, (yyvsp[(3) - (6)].ident).falseList, (yyvsp[(3) - (6)].ident).nFalse, (yyvsp[(6) - (6)].ident).nextList, (yyvsp[(6) - (6)].ident).nNext);
															
															(yyval.ident).nNext = (yyvsp[(3) - (6)].ident).nFalse + (yyvsp[(6) - (6)].ident).nNext;
															
															/*localC3A = completa($3.falseList, $3.nFalse, $7.quad, localC3A);*/
															
															sprintf(string,"selection_statement <- aux_selected_statement");
															string_output(string,(yyvsp[(1) - (6)].ident).rows,(yyvsp[(1) - (6)].ident).columns);;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 2733 "gramatica.y"
    {
														
														/*------------------------C3A----------------------*/
														localC3A = completa((yyvsp[(3) - (10)].ident).trueList, (yyvsp[(3) - (10)].ident).nTrue, (yyvsp[(5) - (10)].ident).quad, localC3A);
														localC3A = completa((yyvsp[(3) - (10)].ident).falseList, (yyvsp[(3) - (10)].ident).nFalse, (yyvsp[(9) - (10)].ident).quad, localC3A);
														
														(yyval.ident).nextList = (int *)malloc(sizeof(int)*20);
														
														/* utilitzada per a llista auxiliar per als dos fusiona*/
														(yyvsp[(2) - (10)].ident).nextList = (int *)malloc(sizeof(int)*20);
														
														(yyvsp[(2) - (10)].ident).nextList = fusiona((yyvsp[(2) - (10)].ident).nextList, (yyvsp[(8) - (10)].ident).nextList, (yyvsp[(8) - (10)].ident).nNext, (yyvsp[(10) - (10)].ident).nextList, (yyvsp[(10) - (10)].ident).nNext);
														(yyvsp[(2) - (10)].ident).nNext = (yyvsp[(8) - (10)].ident).nNext + (yyvsp[(10) - (10)].ident).nNext;
														
														(yyval.ident).nextList = fusiona((yyval.ident).nextList, (yyvsp[(6) - (10)].ident).nextList, (yyvsp[(6) - (10)].ident).nNext, (yyvsp[(2) - (10)].ident).nextList, (yyvsp[(2) - (10)].ident).nNext);
														(yyval.ident).nNext = (yyvsp[(6) - (10)].ident).nNext + (yyvsp[(2) - (10)].ident).nNext;
														
														/*localC3A = completa($9.nextList, $9.nNext, $12.quad, localC3A);*/
														
														sprintf(string,"selection_statement <- IF '(' expression ')' statement ELSE statement");
														string_output(string,(yyvsp[(1) - (10)].ident).rows,(yyvsp[(1) - (10)].ident).columns);;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 2754 "gramatica.y"
    {sprintf(string,"selection_statement <- SWITCH '(' expression ')' statement");
														string_output(string,(yyvsp[(1) - (5)].ident).rows,(yyvsp[(1) - (5)].ident).columns);;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 2758 "gramatica.y"
    {
							/* activem el detector de fors */
							isFor = 1;
							/*filAux = inicialitzarFil(filAux);*/
							/*sprintf(filAux.info, "%s", $2.lexemac3a);*/
							/*localC3A = emet(filAux, localC3A);	 */
							(yyval.ident).lexemac3a = (yyvsp[(2) - (3)].ident).lexemac3a;
							
							sprintf(string,"q <- FOR m '(' expression ';' ");
							string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);
						;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 2771 "gramatica.y"
    {
						isFor = 0;
						(yyval.ident).lexemac3a = (yyvsp[(1) - (3)].ident).lexemac3a;
						(yyval.ident).quad = getSquad();
						
						sprintf(cast, "%s %s %s", (yyvsp[(1) - (3)].ident).lexemac3a, obtainCompare("LE", (yyvsp[(2) - (3)].ident).tipus), (yyvsp[(2) - (3)].ident).lexemac3a);
						
						filAux = inicialitzarFil(filAux);
						sprintf(filAux.info, "IF %s GOTO %d", cast, (yyval.ident).quad + 2);
						localC3A = emet(filAux, localC3A); 
						
						(yyval.ident).nextList = (int *)malloc(sizeof(int)*20);
						(yyval.ident).nextList = crearllista((yyval.ident).nextList, getSquad());
						(yyval.ident).nNext++;
						
						filAux = inicialitzarFil(filAux);
						sprintf(filAux.info, "GOTO ");
						localC3A = emet(filAux, localC3A);
						
						sprintf(string,"p <- q expression ';' ");
						string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);
					;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 2795 "gramatica.y"
    {
									/* completa la llista de seguents del statement cap al increment i el salt al principi del for */
									localC3A = completa((yyvsp[(4) - (4)].ident).nextList, (yyvsp[(4) - (4)].ident).nNext, getSquad(), localC3A);
									
									filAux = inicialitzarFil(filAux);
									sprintf(filAux.info, "%s := %s + 1", (yyvsp[(1) - (4)].ident).lexemac3a, (yyvsp[(1) - (4)].ident).lexemac3a);
									localC3A = emet(filAux, localC3A); 
									
									filAux = inicialitzarFil(filAux);
									sprintf(filAux.info, "GOTO %d", (yyvsp[(1) - (4)].ident).quad);
									localC3A = emet(filAux, localC3A);
									
									(yyval.ident).nextList = (yyvsp[(1) - (4)].ident).nextList;
									(yyval.ident).nNext = (yyvsp[(1) - (4)].ident).nNext;
									
									localC3A = completa((yyvsp[(1) - (4)].ident).nextList, (yyvsp[(1) - (4)].ident).nNext, getSquad(), localC3A);
									
									
									
									sprintf(string,"s <- p expression ')' statement ");
									string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);
								;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 2819 "gramatica.y"
    {
															
															localC3A = completa((yyvsp[(4) - (7)].ident).trueList, (yyvsp[(4) - (7)].ident).nTrue, (yyvsp[(6) - (7)].ident).quad, localC3A);
															localC3A = completa((yyvsp[(7) - (7)].ident).nextList, (yyvsp[(4) - (7)].ident).nNext, (yyvsp[(3) - (7)].ident).quad, localC3A);
															
															(yyval.ident).nextList = (yyvsp[(4) - (7)].ident).falseList;
															(yyval.ident).nNext = (yyvsp[(4) - (7)].ident).nFalse;
															
															filAux = inicialitzarFil(filAux);
															sprintf(filAux.info, "GOTO %d", (yyvsp[(3) - (7)].ident).quad);
															localC3A = emet(filAux, localC3A);	 
															
															/* el getQuad apunta a la seguent lina despres del while i no posem m a la regla */
															/* com a les altres per no haver de partir la regla*/
															/*localC3A = completa($4.falseList, $4.nFalse, getSquad(), localC3A);*/
															
															sprintf(string,"iteration_statement <- WHILE '(' expression ')' statement");
															string_output(string,(yyvsp[(1) - (7)].ident).rows,(yyvsp[(1) - (7)].ident).columns);;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 2837 "gramatica.y"
    {sprintf(string,"iteration_statement <- DO statement WHILE '(' expression ')' ';'");
															string_output(string,(yyvsp[(1) - (7)].ident).rows,(yyvsp[(1) - (7)].ident).columns);;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 2839 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR s ");
															string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);
															;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 2843 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' ';' expression ';' expression ')' statement ");
															string_output(string,(yyvsp[(1) - (8)].ident).rows,(yyvsp[(1) - (8)].ident).columns);;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 2845 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' ';' ';' expression ')' statement ");
															string_output(string,(yyvsp[(1) - (7)].ident).rows,(yyvsp[(1) - (7)].ident).columns);;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 2847 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' ';' ';' ')' statement");
															string_output(string,(yyvsp[(1) - (6)].ident).rows,(yyvsp[(1) - (6)].ident).columns);;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 2849 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' expression ';' ';' expression ')' statement ");
															string_output(string,(yyvsp[(1) - (8)].ident).rows,(yyvsp[(1) - (8)].ident).columns);;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 2851 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' expression ';' ';' ')' statement ");
															string_output(string,(yyvsp[(1) - (7)].ident).rows,(yyvsp[(1) - (7)].ident).columns);;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 2853 "gramatica.y"
    {sprintf(string,"iteration_statement <- FOR '(' ';' expression ';' ')' statement ");
															string_output(string,(yyvsp[(1) - (7)].ident).rows,(yyvsp[(1) - (7)].ident).columns);;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 2857 "gramatica.y"
    {sprintf(string,"jump_statement <- CONTINUE ';'");
								string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 2859 "gramatica.y"
    {sprintf(string,"jump_statement <- BREAK ';'");
				string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 2861 "gramatica.y"
    {
				/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
				inicialitzarInfo();
				
				ambit_actual=sym_get_scope();
				error_sym=sym_global_lookup(nom_funcio,&info);
				
				if(error_sym == SYMTAB_OK){
					if(info.tipusFunction != ID_VOID){
						sprintf(string,"La sentencia RETURN no retorna cap valor. Ha de retornar un valor de tipus %d", info.tipusFunction);
						missatgeWarning(string,(yyvsp[(1) - (2)].ident).rows, (yyvsp[(1) - (2)].ident).columns);
					}
					isReturn = 1;
				}
				sprintf(string,"jump_statement <- RETURN ';'");
				string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 2877 "gramatica.y"
    {
							/* buscar el nom de la funcio i mirar el tipus, si no es void return warning */
							inicialitzarInfo();
							
							ambit_actual=sym_get_scope();
							error_sym=sym_global_lookup(nom_funcio,&info);
							
							if(error_sym == SYMTAB_OK){
							
								if(info.tipusFunction != (yyvsp[(2) - (3)].ident).tipus){
								
									int comprovacio = 0;
																	
									comprovacio = comprovacioTipus(info.tipusFunction, (yyvsp[(2) - (3)].ident).tipus);
									
									switch (comprovacio) {
										case COMPTIPUS_DIF_RED_PRIMER:
											/*-----------------C3A------------------*/
											cast = nouTemp();
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast(info.tipusFunction, (yyvsp[(2) - (3)].ident).tipus, COMPTIPUS_DIF_RED_PRIMER), (yyvsp[(2) - (3)].ident).lexemac3a);
											localC3A = emet(filAux, localC3A);
											
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s", (yyvsp[(2) - (3)].ident).lexemac3a, ":=", cast);
											localC3A = emet(filAux, localC3A);
											
											sprintf(string,"Comprovacio de tipus - (cast) al tipus %d ", (yyvsp[(1) - (3)].ident).tipus);
											missatgeWarning(string,(yyvsp[(2) - (3)].ident).rows, (yyvsp[(2) - (3)].ident).columns);
										break;
										case COMPTIPUS_DIF_RED_SEGON:
											/*-----------------C3A------------------*/
											cast = nouTemp();
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s %s", cast, ":=", obtainCast(info.tipusFunction, (yyvsp[(2) - (3)].ident).tipus, COMPTIPUS_DIF_RED_SEGON), (yyvsp[(2) - (3)].ident).lexemac3a);
											localC3A = emet(filAux, localC3A);
											
											filAux = inicialitzarFil(filAux);
											sprintf(filAux.info, "%s %s %s", (yyvsp[(2) - (3)].ident).lexemac3a, ":=", cast);
											localC3A = emet(filAux, localC3A);
											
											sprintf(string,"Comprovacio de tipus - Perdua de presicio en l'assignacio (cast) al tipus %d.", (yyvsp[(1) - (3)].ident).tipus);
											missatgeWarning(string,(yyvsp[(2) - (3)].ident).rows, (yyvsp[(2) - (3)].ident).columns);
										break;
										case COMPTIPUS_DIF_NO_RED:
											sprintf(string,"ERROR. Comprovacio de tipus - Tipus incorrectes a la assignacio.");
											missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
											YYERROR;
										break;
									}
								
									sprintf(string,"La sentencia RETURN retorna un valor que no es del tipus de la funcio.");
									missatgeWarning(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
								}
								
								isReturn = 1;
							}
							
							filAux = inicialitzarFil(filAux);
							sprintf(filAux.info, "RETURN %s", (yyvsp[(2) - (3)].ident).lexemac3a);
							localC3A = emet(filAux, localC3A);	
							
							sprintf(string,"jump_statement <- RETURN expression ';'");
							string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 2943 "gramatica.y"
    {sprintf(string,"translation_unit <- external_declaration");
										string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);
										;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 2946 "gramatica.y"
    {sprintf(string,"translation_unit <- translation_unit external_declaration");
											string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);
											/*imprimirTaula(globalRA, "Taula global");*/;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 2949 "gramatica.y"
    {yyerrok;;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 2952 "gramatica.y"
    {sprintf(string,"external_declaration <- function_definition");
											string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 2954 "gramatica.y"
    {sprintf(string,"external_declaration <- declaration");
					string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 2957 "gramatica.y"
    {
									error_sym = sym_get_scope();
									
									isFunction = 0;
									
									nom_ambit=(char *)malloc(sizeof(nom_funcio));
									strcpy(nom_ambit, nom_funcio);
									
									punter = (char *)malloc(50);
									
									error_sym=sym_push_scope();
									ambit_actual=sym_get_scope();
									
									if (error_sym!=SYMTAB_OK)
										mostraError(error_sym,(const char *)&nom_ambit);
									else {
										
										/*-----------------C3A------------------*/																				
										filAux = inicialitzarFil(filAux);
										sprintf(filAux.info, "%s %s ", "START", nom_funcio);
										localC3A = emet(filAux, localC3A);
										
										sprintf(string, "Apilat el nou ambit per a la funcio %s amb codi %d",nom_ambit,ambit_actual);
										missatgeTS(string, (yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
									}
									
									error_sym = sym_get_scope();
									ambit_actual = sym_get_scope();
									
									inicialitzarInfo();
									
									error_sym=sym_global_lookup(nom_funcio,&info);
									
									if(error_sym == SYMTAB_OK){
										for(i = 0; i < info.nParamsFuncio; i++){
											if (info.parametres[i].hasName == 0){
												sprintf(string,"ERROR. Declaracio del parametre %d de la funcio es erroni.", i+1);
												missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
											} else{
												infoAux.tipus = info.parametres[i].type;
												punter = info.parametres[i].lexema;
												error_sym = sym_remove(punter);
												error_sym = sym_add(punter, &infoAux);
												sprintf(string, "Parametre %s de la funcio %s guardat com a varible local de la funcio", info.parametres[i].lexema, nom_ambit);
												missatgeTS(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
											}
										}
										
									}
									error_sym=sym_global_lookup(nom_funcio,&info);
									if((numParam != info.nParamsFuncio) && (info.isFunctionDeclaration == 1)){
											sprintf(string,"ERROR. Numero de parametres incompatible amb la declaracio.");
											missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
											/*YYERROR;*/
									}
									else{
										if(info.isFunctionDeclaration == 0){
											info.tipusFunction = ID_VOID;
											error_sym = sym_global_remove(nom_funcio);
											error_sym = sym_global_add(nom_funcio, &info);
										}
										else{
											if (info.tipusFunction != ID_VOID){
												sprintf(string,"ERROR. La funcio previament declarada no es void, retorna un valor de tipus %d", info.tipusFunction);
												missatgeError(string,(yyvsp[(1) - (1)].ident).rows, (yyvsp[(1) - (1)].ident).columns);
												/*YYERROR;*/
											}
										}
									}
								;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 3026 "gramatica.y"
    {
													ambit_actual = sym_get_scope();
													error_sym = sym_pop_scope();
													
													error_sym=sym_global_lookup(nom_funcio,&info);
																										
													if (error_sym!=SYMTAB_OK){
														sprintf(string,"ERROR. No s'ha pogut desapilar el ambit %s.", nom_ambit);
														missatgeError(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
														YYERROR;
													}else{
													
													
														sprintf(string, "Desapilat correctament l'ambit %s amb codi %d",nom_ambit,ambit_actual);
														
														
														missatgeTS(string,(yyvsp[(1) - (3)].ident).rows, (yyvsp[(1) - (3)].ident).columns);
														sprintf(string, "Funcio %s", nom_funcio);
														
														
														
														/*-----------------C3A----------------*/
														imprimirTaula(localRA, string, info.nParamsFuncio);
														imprimirT(localC3A);
														
														localRA = esborrarTaula(localRA);
														localC3A = esborrarT(localC3A);
														
														offsetL = 0;
													}
													isReturn = 0;
											
													sprintf(string,"function_definition <- declarator compound_statement");
													string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 3060 "gramatica.y"
    {sprintf(string,"function_definition <- declarator_specifier declarator declaration_list compound_statement");
													string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 3062 "gramatica.y"
    {
											isFunction = 0;
											error_sym = sym_get_scope();
											
											nom_ambit=(char *)malloc(sizeof(nom_funcio));
											strcpy(nom_ambit, nom_funcio);
											
											punter = (char *)malloc(50);
											
											error_sym=sym_push_scope();
											ambit_actual=sym_get_scope();
											
											if (error_sym!=SYMTAB_OK)
												mostraError(error_sym,(const char *)&nom_ambit);
											else {
												/*-----------------C3A------------------*/																								
												filAux = inicialitzarFil(filAux);
												sprintf(filAux.info, "%s %s ", "START", nom_funcio);
												localC3A = emet(filAux, localC3A);
												
												sprintf(string, "Apilat el nou ambit per a la funcio %s amb codi %d",nom_ambit,ambit_actual);
												missatgeTS(string, (yyvsp[(2) - (2)].ident).rows, (yyvsp[(2) - (2)].ident).columns);
											}
											
											error_sym = sym_get_scope();
											ambit_actual = sym_get_scope();
											
											inicialitzarInfo();
											
											error_sym=sym_global_lookup(nom_funcio,&info);
											
											if((numParam != info.nParamsFuncio) && (info.isFunctionDeclaration == 1)){ 
												sprintf(string,"ERROR. Numero de parametres incompatible amb la declaracio.");
												missatgeError(string,(yyvsp[(2) - (2)].ident).rows, (yyvsp[(2) - (2)].ident).columns);
												/*YYERROR;*/
											}
											if(error_sym == SYMTAB_OK){
												for(i = 0; i < info.nParamsFuncio; i++){
													if(i >= numParam){
													
													}
													else if (info.parametres[i].hasName == 0){
														sprintf(string,"ERROR. Declaracio del parametre %d de la funcio es erroni.", i+1);
														missatgeError(string,(yyvsp[(2) - (2)].ident).rows, (yyvsp[(2) - (2)].ident).columns);
														/*YYERROR;*/
													} else {
														infoAux.tipus = info.parametres[i].type;
														punter = info.parametres[i].lexema;
														error_sym = sym_remove(punter);
														error_sym = sym_add(punter, &infoAux);
														sprintf(string, "Parametre %s de la funcio %s guardat com a varible local de la funcio", punter, nom_ambit);
														missatgeTS(string,(yyvsp[(2) - (2)].ident).rows, (yyvsp[(2) - (2)].ident).columns);
													}
												}
											}
										;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 3117 "gramatica.y"
    {
															
															ambit_actual = sym_get_scope();
															error_sym = sym_pop_scope();
															
															error_sym=sym_global_lookup(nom_funcio,&info);
															
															
															if (error_sym!=SYMTAB_OK){
																sprintf(string,"ERROR. No s'ha pogut desapilar el ambit %s.", nom_ambit);
																missatgeError(string,(yyvsp[(2) - (4)].ident).rows, (yyvsp[(2) - (4)].ident).columns);
															}else{
															
															
																sprintf(string, "Desapilat correctament l'ambit %s amb codi %d",nom_ambit,ambit_actual);
																
																missatgeTS(string,(yyvsp[(2) - (4)].ident).rows, (yyvsp[(2) - (4)].ident).columns);
																sprintf(string, "Funcio %s", nom_funcio);
																
																/*-----------------C3A----------------*/
																imprimirTaula(localRA, string, info.nParamsFuncio);
																imprimirT(localC3A);
																																
																localRA = esborrarTaula(localRA);
																localC3A = esborrarT(localC3A);
																offsetL = 0;
															}
															isReturn = 0;
															sprintf(string,"function_definition <- declaration_specifiers declarator compound_statement");
															string_output(string,(yyvsp[(1) - (4)].ident).rows,(yyvsp[(1) - (4)].ident).columns);;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 3147 "gramatica.y"
    {sprintf(string,"function_definition <- declarator declaration_list compound_statement");
													string_output(string,(yyvsp[(1) - (3)].ident).rows,(yyvsp[(1) - (3)].ident).columns);;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 3149 "gramatica.y"
    {yyerrok;;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 3151 "gramatica.y"
    {yyerrok;;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 3154 "gramatica.y"
    {
								sprintf(string,"declaration_list <- declaration");
								string_output(string,(yyvsp[(1) - (1)].ident).rows,(yyvsp[(1) - (1)].ident).columns);;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 3157 "gramatica.y"
    {
									sprintf(string,"declaration_list <- declaration_list declaration");
									string_output(string,(yyvsp[(1) - (2)].ident).rows,(yyvsp[(1) - (2)].ident).columns);;}
    break;



/* Line 1464 of yacc.c  */
#line 5933 "gramaticay.tab.c"
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



/* Line 1684 of yacc.c  */
#line 3162 "gramatica.y"


void string_output(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(Regla) %s\n",row,column, string);
	printf(aux);
	/*fprintf (yyout, aux);*/
}

void missatgeTS(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(TS)  \t%s\n",row,column, string);
	printf(aux);
	/*fprintf (yyout, aux);*/
}

int init_analisi_sintactic(char* filename){
	char string[20];
	int i=0;
	
	strcpy(string,"");
	
	for(i=0;i<20;i++){
		if(filename[i]=='.'){
			filename[i] = '\0';
			i =20;
		}
	}
	
	localRA = inicialitzarTaula(localRA);
	globalRA = inicialitzarTaula(globalRA);
	inicialitzarFitxer(filename);
	
	globalC3A = inicialitzarT(globalC3A);
	localC3A = inicialitzarT(localC3A);
	inicialitzarFit(filename);
	
	cast = (char *)malloc(20*sizeof(char));
	castAux = (char *)malloc(20*sizeof(char));
	op = (char *)malloc(5*sizeof(char));
	aux = (char *)malloc(20*sizeof(char));
	
	nom_programa = (char *)malloc(sizeof(filename));
	strcpy(nom_programa, filename);
	
	return 0;
}

int analisi_semantic(){
	int error;
	if (yyparse() == 0)
	{
	error =  EXIT_SUCCESS;
	} else {
	error =  EXIT_FAILURE;
	}
	return error;
}

int end_analisi_sintactic(){
	int error;
	
	imprimirTaula(globalRA, "Taula global", 0);
	imprimirT(globalC3A);
	
	error = fclose(yyout);
	
	if(error == 0){
	 error = EXIT_SUCCESS;
	}else{
	 error = EXIT_FAILURE;
	}
	return error;
}

void inicialitzarInfo(){
	strcpy(info.lexema, "");
	strcpy(info.lexemac3a, "");
	info.lenght = 1;
	info.rows = 0;
	info.columns = 0;
	info.tipus = UNDEF;
	info.sizeList = UNDEF;
	info.tipusTypedef = UNDEF;
	info.tipusFunction = UNDEF;
	info.nParamsFuncio = UNDEF;
	info.isFunctionDeclaration = 0;
	
	strcpy(infoAux.lexema, "");
	strcpy(infoAux.lexemac3a, "");
	infoAux.lenght = 1;
	infoAux.rows = 0;
	infoAux.columns = 0;
	infoAux.tipus = UNDEF;
	infoAux.sizeList = UNDEF;
	infoAux.tipusTypedef = UNDEF;
	infoAux.tipusFunction = UNDEF;
	infoAux.nParamsFuncio = UNDEF;
	infoAux.isFunctionDeclaration = 0;
	
	
}

void mostraError(int codi,const char *lexema)
{ 
	switch (codi){
	
	case SYMTAB_NO_MEMORY:	fprintf(stderr, "Error de gestio de la taula de simbols. Memoria insuficient no es pot crear l'entrada per a l'identificador %s !!! \n", lexema);
		break;

	case SYMTAB_DUPLICATE:	fprintf(stderr, "Error de gestio de la taula de simbols. L'entrada a la taula per a l'identificador %s ja existeix !!! \n", lexema);
		break;

	case SYMTAB_STACK_OVERFLOW:	fprintf(stderr, "Error de gestio de la taula de simbols. No es pot crear el nou ambit per al subprograma %s !!! \n",lexema);
		break;

	case SYMTAB_STACK_UNDERFLOW:	fprintf(stderr, "Error de gestio de la taula de simbols. No es pot desapilar l'ambit global %s !!! \n",lexema);
		break;

	case SYMTAB_NOT_TOP:	fprintf(stderr, "Error de gestio de la taula de simbols. No es permet desapilar l'ambit %s encara no tancat !!! \n",lexema);
		break;
	
	case SYMTAB_NOT_FOUND:	fprintf(stderr, "Error de gestio de la taula de simbols. L'entrada a la taula per a l'identificador %s no existeix !!! \n", lexema);
		break;
	}
}

void missatgeError(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(ERROR) %s\n",row,column, string);
	printf(aux);
	fprintf (yyout, aux);
}

void missatgeWarning(char *string, int row, int column){
	char *aux;
	aux = (char *)malloc(sizeof(char *)*200);
	sprintf(aux,"Linia %d.%d\t(WARNING)  %s\n",row,column, string);
	printf(aux);
	fprintf (yyout, aux);
}

int comprovacioTipus(int primer, int segon){
	int valor=-2;
	
	/* Si son variables hem de buscar el tipus al symtab 
	primer = simplificar_tipus_variable(primer, lex_primer);
	segon = simplificar_tipus_variable(segon, lex_segon);*/

	if (primer == segon){
		/* La comparacio sera a nivell*/
		valor = COMPTIPUS_IGUALS;
	} else {
		if (primer < segon && segon <= ID_DOUBLE){
			valor = COMPTIPUS_DIF_RED_SEGON; 
		} else if (primer > segon && primer <= ID_DOUBLE) {
			valor = COMPTIPUS_DIF_RED_PRIMER;
		} else {
			valor = COMPTIPUS_DIF_NO_RED;	
		}
	}
	return valor;
}

int obtenirMida(int tipus){
	switch(tipus){
		case ID_CHAR:
			return 1;
			break;
		case ID_SHORT:
			return 2;
			break;
		case ID_INT:
			return 4;
			break;
		case ID_LONG: 
			return 8;
			break;	
		case ID_FLOAT:
			return 4;
			break;
		case ID_DOUBLE: 
			return 8;
		break;	
	}
	return -1;
}

int obtenirMidaStruct(char * nomStruct){
	int x = 0;
	int mida = 0;
	
	inicialitzarInfo();
	ambit_actual=sym_get_scope();
	if (ambit_actual==SYM_ROOT_SCOPE){
		error_sym=sym_global_lookup(nomStruct,&info);
	}
	else{
		error_sym=sym_lookup(nomStruct,&info);
	}
	
	for(x=0;x<info.nParamsFuncio; x++){
		mida += obtenirMida(info.parametres[x].type);
	}
	
	return mida;
}


void yyerror(char *explanation){	
	fflush(yyout);
}
