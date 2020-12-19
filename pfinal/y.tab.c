/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "alfa.y"

    #include <stdio.h>
    #include "pruebaSintactico.h"
    #define ECHOYYPARSE(rulenum, text) fprintf(yyout, ";R%d:\t%s\n", rulenum, text)
    int yylex();

#line 78 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 189 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_MAIN = 3,                   /* TOK_MAIN  */
  YYSYMBOL_TOK_SCANF = 4,                  /* TOK_SCANF  */
  YYSYMBOL_TOK_PRINTF = 5,                 /* TOK_PRINTF  */
  YYSYMBOL_TOK_FUNCTION = 6,               /* TOK_FUNCTION  */
  YYSYMBOL_TOK_RETURN = 7,                 /* TOK_RETURN  */
  YYSYMBOL_TOK_IF = 8,                     /* TOK_IF  */
  YYSYMBOL_TOK_ELSE = 9,                   /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 10,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_INT = 11,                   /* TOK_INT  */
  YYSYMBOL_TOK_BOOLEAN = 12,               /* TOK_BOOLEAN  */
  YYSYMBOL_TOK_ARRAY = 13,                 /* TOK_ARRAY  */
  YYSYMBOL_TOK_AND = 14,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 15,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 16,                   /* TOK_NOT  */
  YYSYMBOL_TOK_IGUAL = 17,                 /* TOK_IGUAL  */
  YYSYMBOL_TOK_DISTINTO = 18,              /* TOK_DISTINTO  */
  YYSYMBOL_TOK_MENORIGUAL = 19,            /* TOK_MENORIGUAL  */
  YYSYMBOL_TOK_MAYORIGUAL = 20,            /* TOK_MAYORIGUAL  */
  YYSYMBOL_TOK_MENOR = 21,                 /* TOK_MENOR  */
  YYSYMBOL_TOK_MAYOR = 22,                 /* TOK_MAYOR  */
  YYSYMBOL_TOK_CONSTANTE_ENTERA = 23,      /* TOK_CONSTANTE_ENTERA  */
  YYSYMBOL_TOK_TRUE = 24,                  /* TOK_TRUE  */
  YYSYMBOL_TOK_FALSE = 25,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_IDENTIFICADOR = 26,         /* TOK_IDENTIFICADOR  */
  YYSYMBOL_27_ = 27,                       /* '+'  */
  YYSYMBOL_28_ = 28,                       /* '-'  */
  YYSYMBOL_29_ = 29,                       /* '*'  */
  YYSYMBOL_30_ = 30,                       /* '/'  */
  YYSYMBOL_UMINUS = 31,                    /* UMINUS  */
  YYSYMBOL_32_ = 32,                       /* '{'  */
  YYSYMBOL_33_ = 33,                       /* '}'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '['  */
  YYSYMBOL_36_ = 36,                       /* ']'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* '='  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_programa = 42,                  /* programa  */
  YYSYMBOL_declaraciones = 43,             /* declaraciones  */
  YYSYMBOL_declaracion = 44,               /* declaracion  */
  YYSYMBOL_clase = 45,                     /* clase  */
  YYSYMBOL_clase_escalar = 46,             /* clase_escalar  */
  YYSYMBOL_tipo = 47,                      /* tipo  */
  YYSYMBOL_clase_vector = 48,              /* clase_vector  */
  YYSYMBOL_identificadores = 49,           /* identificadores  */
  YYSYMBOL_funciones = 50,                 /* funciones  */
  YYSYMBOL_funcion = 51,                   /* funcion  */
  YYSYMBOL_parametros_funcion = 52,        /* parametros_funcion  */
  YYSYMBOL_resto_parametros_funcion = 53,  /* resto_parametros_funcion  */
  YYSYMBOL_parametro_funcion = 54,         /* parametro_funcion  */
  YYSYMBOL_declaraciones_funcion = 55,     /* declaraciones_funcion  */
  YYSYMBOL_sentencias = 56,                /* sentencias  */
  YYSYMBOL_sentencia = 57,                 /* sentencia  */
  YYSYMBOL_sentencia_simple = 58,          /* sentencia_simple  */
  YYSYMBOL_bloque = 59,                    /* bloque  */
  YYSYMBOL_asignacion = 60,                /* asignacion  */
  YYSYMBOL_elemento_vector = 61,           /* elemento_vector  */
  YYSYMBOL_condicional = 62,               /* condicional  */
  YYSYMBOL_bucle = 63,                     /* bucle  */
  YYSYMBOL_lectura = 64,                   /* lectura  */
  YYSYMBOL_escritura = 65,                 /* escritura  */
  YYSYMBOL_retorno_funcion = 66,           /* retorno_funcion  */
  YYSYMBOL_exp = 67,                       /* exp  */
  YYSYMBOL_lista_expresiones = 68,         /* lista_expresiones  */
  YYSYMBOL_resto_lista_expresiones = 69,   /* resto_lista_expresiones  */
  YYSYMBOL_comparacion = 70,               /* comparacion  */
  YYSYMBOL_constante = 71,                 /* constante  */
  YYSYMBOL_constante_logica = 72,          /* constante_logica  */
  YYSYMBOL_constante_entera = 73,          /* constante_entera  */
  YYSYMBOL_identificador = 74              /* identificador  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,    29,    27,    37,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,    40,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      25,    26,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    33,    33,    36,    38,    40,    42,    43,    45,    47,
      48,    50,    53,    55,    58,    59,    60,    63,    66,    67,
      70,    71,    72,    75,    77,    78,    79,    80,    81,    82,
      83,    84,    86,    87,    89,    90,    92,    95,    97,    99,
     102,   103,   104,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   122,   125,   126,
     129,   131,   132,   133,   134,   135,   136,   138,   139,   141,
     142,   144,   146
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_MAIN",
  "TOK_SCANF", "TOK_PRINTF", "TOK_FUNCTION", "TOK_RETURN", "TOK_IF",
  "TOK_ELSE", "TOK_WHILE", "TOK_INT", "TOK_BOOLEAN", "TOK_ARRAY",
  "TOK_AND", "TOK_OR", "TOK_NOT", "TOK_IGUAL", "TOK_DISTINTO",
  "TOK_MENORIGUAL", "TOK_MAYORIGUAL", "TOK_MENOR", "TOK_MAYOR",
  "TOK_CONSTANTE_ENTERA", "TOK_TRUE", "TOK_FALSE", "TOK_IDENTIFICADOR",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "'{'", "'}'", "';'", "'['", "']'",
  "','", "'('", "')'", "'='", "$accept", "programa", "declaraciones",
  "declaracion", "clase", "clase_escalar", "tipo", "clase_vector",
  "identificadores", "funciones", "funcion", "parametros_funcion",
  "resto_parametros_funcion", "parametro_funcion", "declaraciones_funcion",
  "sentencias", "sentencia", "sentencia_simple", "bloque", "asignacion",
  "elemento_vector", "condicional", "bucle", "lectura", "escritura",
  "retorno_funcion", "exp", "lista_expresiones", "resto_lista_expresiones",
  "comparacion", "constante", "constante_logica", "constante_entera",
  "identificador", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    43,    45,    42,
      47,   282,   123,   125,    59,    91,    93,    44,    40,    41,
      61
};
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -13,    23,    42,   -32,   -32,   -32,     0,    24,    42,
      12,   -32,   -32,   -32,     5,     0,   117,    24,   -32,   -32,
      10,     8,    18,    12,    12,   114,   114,     9,    21,    15,
     117,    26,   -32,   -32,    38,   -32,   -32,   -32,   -32,   -32,
     -31,   -32,   -32,    12,   -32,    25,    41,   -32,   114,   -32,
     -32,   114,   114,   -32,   131,   -32,   -32,   -32,   -30,   131,
     114,   114,   -32,   -32,   -32,   114,   114,   114,   -32,   -32,
       0,   -32,   -32,     7,    48,   114,   114,   114,   114,   114,
     114,   114,    35,    61,   131,   121,   131,    12,    53,    46,
     114,   114,   114,   114,   114,   114,   -32,   -32,   -32,     2,
       2,     2,   -32,   -32,   104,    54,    62,    65,   -32,   -32,
      66,     0,   -32,   131,   131,   131,   131,   131,   131,   114,
     -32,   -32,   117,   117,    42,    46,   104,    68,    69,   -32,
     117,   -32,   -32,    90,   -32,    71,    73,   -32,   117,    76,
     -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     9,    10,     0,    15,     3,
       0,     6,     8,     7,     0,     0,     0,    15,     4,    72,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      24,     0,    27,    28,     0,    32,    33,    29,    30,    31,
       0,    14,     5,     0,    71,     0,     0,    40,     0,    69,
      70,     0,     0,    55,    41,    52,    67,    68,    51,    42,
       0,     0,     2,    25,    26,     0,     0,     0,    13,    11,
      18,    50,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,     0,    35,     0,    34,     0,     0,    20,
       0,     0,     0,     0,     0,     0,    53,    54,    48,    49,
      43,    44,    46,    45,    60,     0,     0,     0,    36,    21,
       0,     0,    17,    61,    62,    63,    64,    65,    66,     0,
      57,    56,     0,     0,    23,    20,    60,     0,     0,    22,
       0,    19,    59,    37,    39,     0,     0,    16,     0,     0,
      38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,    -7,   -32,   -32,   -32,     3,   -32,    63,    99,
     -32,   -32,     1,    33,   -32,   -27,   -32,   -32,   -32,   -32,
     -15,   -32,   -32,   -32,   -32,   -32,    -9,   -32,    27,   -32,
     -32,   -32,   107,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    11,    12,    13,    20,    16,
      17,    88,   112,    89,   130,    29,    30,    31,    32,    33,
      53,    35,    36,    37,    38,    39,    54,   105,   120,    74,
      55,    56,    57,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      21,    34,    18,    63,    66,    66,    40,     1,    81,    67,
      14,     5,     6,    46,    47,    34,    75,    59,    23,     3,
      40,    75,    76,     4,    90,    91,    92,    93,    94,    95,
      15,    79,    80,    21,    77,    78,    79,    80,    19,    71,
      22,    44,    72,    73,    42,    43,    96,    60,    62,    75,
      76,    82,    83,     5,     6,     7,    84,    85,    86,    61,
      64,    69,    77,    78,    79,    80,    98,    99,   100,   101,
     102,   103,   104,    87,   106,    75,    76,   109,    65,    70,
     111,   113,   114,   115,   116,   117,   118,    97,    77,    78,
      79,    80,   110,   121,   122,   127,   128,   123,   124,   136,
     107,   133,   134,   135,   137,   138,    68,    34,    34,   140,
     126,   139,    40,    40,    87,    34,    41,   129,    75,    76,
      40,    24,    25,    34,    26,    27,   131,    28,    40,    45,
      48,    77,    78,    79,    80,    75,    76,    44,    49,    50,
      19,   119,    51,    19,   125,    75,    76,     0,    77,    78,
      79,    80,    52,   132,     0,     0,     0,   108,    77,    78,
      79,    80
};

static const yytype_int16 yycheck[] =
{
      10,    16,     9,    30,    35,    35,    16,     3,    38,    40,
       7,    11,    12,    23,    24,    30,    14,    26,    15,    32,
      30,    14,    15,     0,    17,    18,    19,    20,    21,    22,
       6,    29,    30,    43,    27,    28,    29,    30,    26,    48,
      35,    23,    51,    52,    34,    37,    39,    38,    33,    14,
      15,    60,    61,    11,    12,    13,    65,    66,    67,    38,
      34,    36,    27,    28,    29,    30,    75,    76,    77,    78,
      79,    80,    81,    70,    39,    14,    15,    87,    40,    38,
      34,    90,    91,    92,    93,    94,    95,    39,    27,    28,
      29,    30,    39,    39,    32,   122,   123,    32,    32,     9,
      39,    33,    33,   130,    33,    32,    43,   122,   123,    33,
     119,   138,   122,   123,   111,   130,    17,   124,    14,    15,
     130,     4,     5,   138,     7,     8,   125,    10,   138,    22,
      16,    27,    28,    29,    30,    14,    15,    23,    24,    25,
      26,    37,    28,    26,   111,    14,    15,    -1,    27,    28,
      29,    30,    38,   126,    -1,    -1,    -1,    36,    27,    28,
      29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    42,    32,     0,    11,    12,    13,    43,    44,
      45,    46,    47,    48,    47,     6,    50,    51,    43,    26,
      49,    74,    35,    47,     4,     5,     7,     8,    10,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      74,    50,    34,    37,    23,    73,    74,    74,    16,    24,
      25,    28,    38,    61,    67,    71,    72,    73,    74,    67,
      38,    38,    33,    56,    34,    40,    35,    40,    49,    36,
      38,    67,    67,    67,    70,    14,    15,    27,    28,    29,
      30,    38,    67,    67,    67,    67,    67,    47,    52,    54,
      17,    18,    19,    20,    21,    22,    39,    39,    67,    67,
      67,    67,    67,    67,    67,    68,    39,    39,    36,    74,
      39,    34,    53,    67,    67,    67,    67,    67,    67,    37,
      69,    39,    32,    32,    32,    54,    67,    56,    56,    43,
      55,    53,    69,    33,    33,    56,     9,    33,    32,    56,
      33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    46,    47,
      47,    48,    49,    49,    50,    50,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    62,    62,    63,
      64,    65,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     1,     2,     3,     1,     1,     1,     1,
       1,     5,     1,     3,     2,     0,    10,     2,     0,     3,
       0,     2,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     7,    11,     7,
       2,     2,     2,     3,     3,     3,     3,     2,     3,     3,
       2,     1,     1,     3,     3,     1,     4,     2,     0,     3,
       0,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: TOK_MAIN '{' declaraciones funciones sentencias '}'  */
#line 34 "alfa.y"
    {ECHOYYPARSE(1, "<programa> ::= main { <declaraciones> <funciones> <sentencias> }");}
#line 1343 "y.tab.c"
    break;

  case 3: /* declaraciones: declaracion  */
#line 37 "alfa.y"
    {ECHOYYPARSE(2, "<declaraciones> ::= <declaracion>");}
#line 1349 "y.tab.c"
    break;

  case 4: /* declaraciones: declaracion declaraciones  */
#line 39 "alfa.y"
    {ECHOYYPARSE(3, "<declaraciones> ::= <declaracion> <declaraciones>");}
#line 1355 "y.tab.c"
    break;

  case 5: /* declaracion: clase identificadores ';'  */
#line 41 "alfa.y"
    {ECHOYYPARSE(4, "<declaracion> ::= <clase> <identificadores> ;");}
#line 1361 "y.tab.c"
    break;

  case 6: /* clase: clase_escalar  */
#line 42 "alfa.y"
                                    {ECHOYYPARSE(5, "<clase> ::= <clase_escalar>");}
#line 1367 "y.tab.c"
    break;

  case 7: /* clase: clase_vector  */
#line 43 "alfa.y"
                                    {ECHOYYPARSE(7, "<clase> ::= <clase_vector>");}
#line 1373 "y.tab.c"
    break;

  case 8: /* clase_escalar: tipo  */
#line 46 "alfa.y"
    {ECHOYYPARSE(9, "<clase_escalar> ::= <tipo>");}
#line 1379 "y.tab.c"
    break;

  case 9: /* tipo: TOK_INT  */
#line 47 "alfa.y"
                                    {ECHOYYPARSE(10, "<tipo> ::= int");}
#line 1385 "y.tab.c"
    break;

  case 10: /* tipo: TOK_BOOLEAN  */
#line 48 "alfa.y"
                                    {ECHOYYPARSE(11, "<tipo> ::= boolean");}
#line 1391 "y.tab.c"
    break;

  case 11: /* clase_vector: TOK_ARRAY tipo '[' constante_entera ']'  */
#line 51 "alfa.y"
    {ECHOYYPARSE(15, "<clase_vector> ::= TOK_ARRAY <tipo> [ <constante_entera> ]");}
#line 1397 "y.tab.c"
    break;

  case 12: /* identificadores: identificador  */
#line 54 "alfa.y"
    {ECHOYYPARSE(18, "<identificadores> ::= <identificador>");}
#line 1403 "y.tab.c"
    break;

  case 13: /* identificadores: identificador ',' identificadores  */
#line 56 "alfa.y"
    {ECHOYYPARSE(19, "<identificadores> ::= <identificador> , <identificadores>");}
#line 1409 "y.tab.c"
    break;

  case 14: /* funciones: funcion funciones  */
#line 58 "alfa.y"
                                        {ECHOYYPARSE(20, "<funciones> ::= <funcion> <funciones>");}
#line 1415 "y.tab.c"
    break;

  case 15: /* funciones: %empty  */
#line 59 "alfa.y"
                                        {ECHOYYPARSE(21, "<funciones> ::= ");}
#line 1421 "y.tab.c"
    break;

  case 16: /* funcion: TOK_FUNCTION tipo identificador '(' parametros_funcion ')' '{' declaraciones_funcion sentencias '}'  */
#line 62 "alfa.y"
    {ECHOYYPARSE(22, "<funcion> ::= function <tipo> <identificador> ( <parametro_funcion> ) { <declaraciones_funcion> <sentencias> }");}
#line 1427 "y.tab.c"
    break;

  case 17: /* parametros_funcion: parametro_funcion resto_parametros_funcion  */
#line 64 "alfa.y"
    {ECHOYYPARSE(23, "<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>");}
#line 1433 "y.tab.c"
    break;

  case 18: /* parametros_funcion: %empty  */
#line 66 "alfa.y"
    {ECHOYYPARSE(24, "<parametros_funcion> ::= ");}
#line 1439 "y.tab.c"
    break;

  case 19: /* resto_parametros_funcion: ';' parametro_funcion resto_parametros_funcion  */
#line 68 "alfa.y"
    {ECHOYYPARSE(25, "<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>");}
#line 1445 "y.tab.c"
    break;

  case 20: /* resto_parametros_funcion: %empty  */
#line 70 "alfa.y"
    {ECHOYYPARSE(26, "<resto_parametros_funcion> ::= ");}
#line 1451 "y.tab.c"
    break;

  case 21: /* parametro_funcion: tipo identificador  */
#line 71 "alfa.y"
                                            {ECHOYYPARSE(27, "<parametro_funcion> ::= <tipo> <identificador>");}
#line 1457 "y.tab.c"
    break;

  case 22: /* declaraciones_funcion: declaraciones  */
#line 73 "alfa.y"
    {ECHOYYPARSE(28, "<declaraciones_funcion> ::= <identificador> <identificador>");}
#line 1463 "y.tab.c"
    break;

  case 23: /* declaraciones_funcion: %empty  */
#line 75 "alfa.y"
    {ECHOYYPARSE(29, "<declaraciones_funcion> ::= ");}
#line 1469 "y.tab.c"
    break;

  case 24: /* sentencias: sentencia  */
#line 77 "alfa.y"
                                            {ECHOYYPARSE(30, "<sentencias> ::= <sentencia>");}
#line 1475 "y.tab.c"
    break;

  case 25: /* sentencias: sentencia sentencias  */
#line 78 "alfa.y"
                                            {ECHOYYPARSE(31, "<sentencias> ::= <sentencia> <sentencias>");}
#line 1481 "y.tab.c"
    break;

  case 26: /* sentencia: sentencia_simple ';'  */
#line 79 "alfa.y"
                                            {ECHOYYPARSE(32, "<sentencia> ::= <sentencia_simple> ;");}
#line 1487 "y.tab.c"
    break;

  case 27: /* sentencia: bloque  */
#line 80 "alfa.y"
                                            {ECHOYYPARSE(33, "<sentencia> ::= <bloque>");}
#line 1493 "y.tab.c"
    break;

  case 28: /* sentencia_simple: asignacion  */
#line 81 "alfa.y"
                                            {ECHOYYPARSE(34, "<sentencia_simple> ::= <asignacion>");}
#line 1499 "y.tab.c"
    break;

  case 29: /* sentencia_simple: lectura  */
#line 82 "alfa.y"
                                            {ECHOYYPARSE(35, "<sentencia_simple> ::= <lectura>");}
#line 1505 "y.tab.c"
    break;

  case 30: /* sentencia_simple: escritura  */
#line 83 "alfa.y"
                                            {ECHOYYPARSE(36, "<sentencia_simple> ::= <escritura>");}
#line 1511 "y.tab.c"
    break;

  case 31: /* sentencia_simple: retorno_funcion  */
#line 84 "alfa.y"
                                            {ECHOYYPARSE(37, "<sentencia_simple> ::= <retorno_funcion>");}
#line 1517 "y.tab.c"
    break;

  case 32: /* bloque: condicional  */
#line 86 "alfa.y"
                                            {ECHOYYPARSE(40, "<bloque> ::= <condicional>");}
#line 1523 "y.tab.c"
    break;

  case 33: /* bloque: bucle  */
#line 87 "alfa.y"
                                            {ECHOYYPARSE(41, "<bloque> ::= <bucle>");}
#line 1529 "y.tab.c"
    break;

  case 34: /* asignacion: identificador '=' exp  */
#line 89 "alfa.y"
                                            {ECHOYYPARSE(43, "<asignacion> ::= <identificador> = <exp>");}
#line 1535 "y.tab.c"
    break;

  case 35: /* asignacion: elemento_vector '=' exp  */
#line 90 "alfa.y"
                                            {ECHOYYPARSE(44, "<asignacion> ::= <elemento_vector> = <exp>");}
#line 1541 "y.tab.c"
    break;

  case 36: /* elemento_vector: identificador '[' exp ']'  */
#line 93 "alfa.y"
    {ECHOYYPARSE(48, "<elemento_vector> ::= <identificador> [ <exp> ]");}
#line 1547 "y.tab.c"
    break;

  case 37: /* condicional: TOK_IF '(' exp ')' '{' sentencias '}'  */
#line 96 "alfa.y"
    {ECHOYYPARSE(50, "<condicional> ::= if ( <exp> ) { <sentencias> }");}
#line 1553 "y.tab.c"
    break;

  case 38: /* condicional: TOK_IF '(' exp ')' '{' sentencias '}' TOK_ELSE '{' sentencias '}'  */
#line 98 "alfa.y"
    {ECHOYYPARSE(51, "<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }");}
#line 1559 "y.tab.c"
    break;

  case 39: /* bucle: TOK_WHILE '(' exp ')' '{' sentencias '}'  */
#line 100 "alfa.y"
    {ECHOYYPARSE(52, "<bucle> ::= while ( <exp> ) { <sentencias> }");}
#line 1565 "y.tab.c"
    break;

  case 40: /* lectura: TOK_SCANF identificador  */
#line 102 "alfa.y"
                                            {ECHOYYPARSE(54, "<lectura> ::= scanf <identificador>");}
#line 1571 "y.tab.c"
    break;

  case 41: /* escritura: TOK_PRINTF exp  */
#line 103 "alfa.y"
                                            {ECHOYYPARSE(56, "<escritura> ::= printf <exp>");}
#line 1577 "y.tab.c"
    break;

  case 42: /* retorno_funcion: TOK_RETURN exp  */
#line 104 "alfa.y"
                                            {ECHOYYPARSE(61, "<retorno_funcion> ::= return <exp>");}
#line 1583 "y.tab.c"
    break;

  case 43: /* exp: exp '+' exp  */
#line 106 "alfa.y"
                                    {(yyval.numero) = (yyvsp[-2].numero) + (yyvsp[0].numero); ECHOYYPARSE(72, "<exp> ::= <exp> + <exp>");}
#line 1589 "y.tab.c"
    break;

  case 44: /* exp: exp '-' exp  */
#line 107 "alfa.y"
                                  {(yyval.numero) = (yyvsp[-2].numero) - (yyvsp[0].numero); ECHOYYPARSE(73, "<exp> ::= <exp> - <exp>");}
#line 1595 "y.tab.c"
    break;

  case 45: /* exp: exp '/' exp  */
#line 108 "alfa.y"
                                   {(yyval.numero) = (yyvsp[-2].numero) / (yyvsp[0].numero); ECHOYYPARSE(74, "<exp> ::= <exp> / <exp>");}
#line 1601 "y.tab.c"
    break;

  case 46: /* exp: exp '*' exp  */
#line 109 "alfa.y"
                                  {(yyval.numero) = (yyvsp[-2].numero) * (yyvsp[0].numero); ECHOYYPARSE(75, "<exp> ::= <exp> * <exp>");}
#line 1607 "y.tab.c"
    break;

  case 47: /* exp: '-' exp  */
#line 110 "alfa.y"
                                        {(yyval.numero) = - (yyvsp[0].numero); ECHOYYPARSE(76, "<exp> ::= - <exp>");}
#line 1613 "y.tab.c"
    break;

  case 48: /* exp: exp TOK_AND exp  */
#line 111 "alfa.y"
                                        {(yyval.numero) = (yyvsp[-2].numero) && (yyvsp[0].numero); ECHOYYPARSE(77, "<exp> ::= <exp> && <exp>");}
#line 1619 "y.tab.c"
    break;

  case 49: /* exp: exp TOK_OR exp  */
#line 112 "alfa.y"
                                        {(yyval.numero) = (yyvsp[-2].numero) || (yyvsp[0].numero); ECHOYYPARSE(78, "<exp> ::= <exp> || <exp>");}
#line 1625 "y.tab.c"
    break;

  case 50: /* exp: TOK_NOT exp  */
#line 113 "alfa.y"
                                            {(yyval.numero) = ! (yyvsp[0].numero); ECHOYYPARSE(79, "<exp> ::= ! <exp>");}
#line 1631 "y.tab.c"
    break;

  case 51: /* exp: identificador  */
#line 114 "alfa.y"
                                        {ECHOYYPARSE(80, "<exp> ::= <identificador>");}
#line 1637 "y.tab.c"
    break;

  case 52: /* exp: constante  */
#line 115 "alfa.y"
                                        {ECHOYYPARSE(81, "<exp> ::= <constante>");}
#line 1643 "y.tab.c"
    break;

  case 53: /* exp: '(' exp ')'  */
#line 116 "alfa.y"
                                        {(yyval.numero) = (yyvsp[-1].numero); ECHOYYPARSE(82, "<exp> ::= ( <exp> )");}
#line 1649 "y.tab.c"
    break;

  case 54: /* exp: '(' comparacion ')'  */
#line 117 "alfa.y"
                                        {(yyval.numero) = (yyvsp[-1].numero); ECHOYYPARSE(83, "<exp> ::= ( <comparacion> )");}
#line 1655 "y.tab.c"
    break;

  case 55: /* exp: elemento_vector  */
#line 118 "alfa.y"
                                        {ECHOYYPARSE(85, "<exp> ::= <elemento_vector>");}
#line 1661 "y.tab.c"
    break;

  case 56: /* exp: identificador '(' lista_expresiones ')'  */
#line 120 "alfa.y"
    {ECHOYYPARSE(88, "<exp> ::= <identificador> ( <lista_expresiones> )");}
#line 1667 "y.tab.c"
    break;

  case 57: /* lista_expresiones: exp resto_lista_expresiones  */
#line 123 "alfa.y"
    {ECHOYYPARSE(89, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
#line 1673 "y.tab.c"
    break;

  case 58: /* lista_expresiones: %empty  */
#line 125 "alfa.y"
    {ECHOYYPARSE(90, "<lista_expresiones> ::= ");}
#line 1679 "y.tab.c"
    break;

  case 59: /* resto_lista_expresiones: ',' exp resto_lista_expresiones  */
#line 127 "alfa.y"
    {ECHOYYPARSE(91, "<lista_expresiones> ::= <exp> <resto_lista_expresiones>");}
#line 1685 "y.tab.c"
    break;

  case 60: /* resto_lista_expresiones: %empty  */
#line 129 "alfa.y"
    {ECHOYYPARSE(92, "<resto_lista_expresiones> ::= ");}
#line 1691 "y.tab.c"
    break;

  case 61: /* comparacion: exp TOK_IGUAL exp  */
#line 131 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) == (yyvsp[0].numero); ECHOYYPARSE(93, "<exp> ::= <exp> == <exp>");}
#line 1697 "y.tab.c"
    break;

  case 62: /* comparacion: exp TOK_DISTINTO exp  */
#line 132 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) != (yyvsp[0].numero); ECHOYYPARSE(94, "<exp> ::= <exp> != <exp>");}
#line 1703 "y.tab.c"
    break;

  case 63: /* comparacion: exp TOK_MENORIGUAL exp  */
#line 133 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) <= (yyvsp[0].numero); ECHOYYPARSE(95, "<exp> ::= <exp> <= <exp>");}
#line 1709 "y.tab.c"
    break;

  case 64: /* comparacion: exp TOK_MAYORIGUAL exp  */
#line 134 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) >= (yyvsp[0].numero); ECHOYYPARSE(96, "<exp> ::= <exp> >= <exp>");}
#line 1715 "y.tab.c"
    break;

  case 65: /* comparacion: exp TOK_MENOR exp  */
#line 135 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) < (yyvsp[0].numero); ECHOYYPARSE(97, "<exp> ::= <exp> < <exp>");}
#line 1721 "y.tab.c"
    break;

  case 66: /* comparacion: exp TOK_MAYOR exp  */
#line 136 "alfa.y"
                                            {(yyval.numero) = (yyvsp[-2].numero) > (yyvsp[0].numero); ECHOYYPARSE(98, "<exp> ::= <exp> > <exp>");}
#line 1727 "y.tab.c"
    break;

  case 67: /* constante: constante_logica  */
#line 138 "alfa.y"
                                     {ECHOYYPARSE(99, "<constante> ::= <constante_logica>");}
#line 1733 "y.tab.c"
    break;

  case 68: /* constante: constante_entera  */
#line 139 "alfa.y"
                                     {ECHOYYPARSE(100, "<constante> ::= <constante_entera>");}
#line 1739 "y.tab.c"
    break;

  case 69: /* constante_logica: TOK_TRUE  */
#line 141 "alfa.y"
                                 {ECHOYYPARSE(102, "<constante_logica> ::= true");}
#line 1745 "y.tab.c"
    break;

  case 70: /* constante_logica: TOK_FALSE  */
#line 142 "alfa.y"
                                  {ECHOYYPARSE(103, "<constante_logica> ::= false");}
#line 1751 "y.tab.c"
    break;

  case 71: /* constante_entera: TOK_CONSTANTE_ENTERA  */
#line 144 "alfa.y"
                                            {ECHOYYPARSE(104, "<constante_entera> ::= numero");}
#line 1757 "y.tab.c"
    break;

  case 72: /* identificador: TOK_IDENTIFICADOR  */
#line 146 "alfa.y"
                                            {ECHOYYPARSE(108, "<identificador> ::= TOK_IDENTIFICADOR");}
#line 1763 "y.tab.c"
    break;


#line 1767 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 148 "alfa.y"

