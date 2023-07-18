/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SQL_TAB_HPP_INCLUDED
# define YY_YY_SQL_TAB_HPP_INCLUDED
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
    SELECT = 258,
    DISTINCT = 259,
    SELECT_OPT = 260,
    FROM = 261,
    WHERE = 262,
    JOIN_TYPE = 263,
    JOIN = 264,
    STRAIGHT_JOIN = 265,
    INDEX = 266,
    USE = 267,
    ON = 268,
    USING = 269,
    IGNORE = 270,
    FORCE = 271,
    FOR = 272,
    QUICK = 273,
    LOW_PRIORITY = 274,
    GROUP = 275,
    ORDER = 276,
    BY = 277,
    ASC = 278,
    DESC = 279,
    INSERT = 280,
    UPDATE = 281,
    DELETE = 282,
    SHOW = 283,
    INTO = 284,
    AS = 285,
    IN = 286,
    ANY = 287,
    EXISTS = 288,
    IS = 289,
    NULLX = 290,
    UNKNOWN = 291,
    FALSEX = 292,
    TRUEX = 293,
    DEFAULT = 294,
    EQUAL = 295,
    N_EQUAL = 296,
    MULTIPLY = 297,
    DIVIDE = 298,
    POWER = 299,
    NEWLINE = 300,
    SHIFT = 301,
    BASIC_OP = 302,
    BETWEEN = 303,
    CASE = 304,
    WHEN = 305,
    THEN = 306,
    ELSE = 307,
    END_CASE = 308,
    CAST = 309,
    DATA_TYPE = 310,
    BINARY = 311,
    CHAR_TYPE = 312,
    REGEXP = 313,
    HAVING = 314,
    LIMIT = 315,
    OFFSET = 316,
    PROCEDURE = 317,
    UNION = 318,
    SET = 319,
    INTEGER = 320,
    STRING = 321,
    Q_STRING = 322,
    DQ_STRING = 323,
    NAME = 324,
    VARIABLE = 325,
    O_BRACE = 326,
    C_BRACE = 327,
    BIT_OR = 328,
    BIT_AND = 329,
    NEG = 330,
    END = 331,
    COMMA = 332,
    DOT = 333,
    AND = 334,
    OR = 335,
    NOT = 336,
    XOR = 337,
    LIKE = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "sql.ypp" /* yacc.c:1909  */

  int int_val;
  class SQLString * str_val;
  class Expression * exp_val;

#line 144 "sql.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SQL_TAB_HPP_INCLUDED  */
