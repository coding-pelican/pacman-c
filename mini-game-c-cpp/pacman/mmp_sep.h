#ifndef MMP_SEP_H
#define MMP_SEP_H

/* MMP_SEPARATORS */

// #include "config.h"

// NOLINTBEGIN
#define SEP_NONE(...)
#define SEP_COMMA(...)             ,
#define SEP_SEMICOLON(...)         ;
#define SEP_PLUS(...)              +
#define SEP_MINUS(...)             -
#define SEP_TIMES(...)             *
#define SEP_DIVIDE(...)            /
#define SEP_MODULO(...)            %
#define SEP_AND(...)               &&
#define SEP_OR(...)                ||
#define SEP_LT(...)                <
#define SEP_LE(...)                <=
#define SEP_EQ(...)                ==
#define SEP_NEQ(...)               !=
#define SEP_GE(...)                >=
#define SEP_GT(...)                >
#define SEP_BIT_AND(...)           &
#define SEP_BIT_OR(...)            |
#define SEP_BIT_XOR(...)           ^
#define SEP_BIT_LSHIFT(...)        <<
#define SEP_BIT_RSHIFT(...)        >>
#define SEP_ASSIGN(...)            =
#define SEP_PLUS_ASSIGN(...)       +=
#define SEP_MINUS_ASSIGN(...)      -=
#define SEP_TIMES_ASSIGN(...)      *=
#define SEP_DIVIDE_ASSIGN(...)     /=
#define SEP_MODULO_ASSIGN(...)     %=
#define SEP_BIT_AND_ASSIGN(...)    &=
#define SEP_BIT_OR_ASSIGN(...)     |=
#define SEP_BIT_XOR_ASSIGN(...)    ^=
#define SEP_BIT_LSHIFT_ASSIGN(...) <<=
#define SEP_BIT_RSHIFT_ASSIGN(...) >>=
#define SEP_FIELD(...)             .
#define SEP_DEREF_FIELD(...)       ->
#define SEP_SPACE(...)             " "
#define SEP_TAB(...)               "\t"
#define SEP_LF(...)                "\n"
#define SEP_CR(...)                "\r"

#if !MMP_DONT_USE_DOLLAR_SIGN
#  define $$NONE(...)              SEP_NONE(__VA_ARGS__)
#  define $$COMMA(...)             SEP_COMMA(__VA_ARGS__)
#  define $$SEMICOLON(...)         SEP_SEMICOLON(__VA_ARGS__)
#  define $$PLUS(...)              SEP_PLUS(__VA_ARGS__)
#  define $$MINUS(...)             SEP_MINUS(__VA_ARGS__)
#  define $$TIMES(...)             SEP_TIMES(__VA_ARGS__)
#  define $$DIVIDE(...)            SEP_DIVIDE(__VA_ARGS__)
#  define $$MODULO(...)            SEP_MODULO(__VA_ARGS__)
#  define $$AND(...)               SEP_AND(__VA_ARGS__)
#  define $$OR(...)                SEP_OR(__VA_ARGS__)
#  define $$LT(...)                SEP_LT(__VA_ARGS__)
#  define $$LE(...)                SEP_LE(__VA_ARGS__)
#  define $$EQ(...)                SEP_EQ(__VA_ARGS__)
#  define $$NEQ(...)               SEP_NEQ(__VA_ARGS__)
#  define $$GE(...)                SEP_GE(__VA_ARGS__)
#  define $$GT(...)                SEP_GT(__VA_ARGS__)
#  define $$BIT_AND(...)           SEP_BIT_AND(__VA_ARGS__)
#  define $$BIT_OR(...)            SEP_BIT_OR(__VA_ARGS__)
#  define $$BIT_XOR(...)           SEP_BIT_XOR(__VA_ARGS__)
#  define $$BIT_LSHIFT(...)        SEP_BIT_LSHIFT(__VA_ARGS__)
#  define $$BIT_RSHIFT(...)        SEP_BIT_RSHIFT(__VA_ARGS__)
#  define $$ASSIGN(...)            SEP_ASSIGN(__VA_ARGS__)
#  define $$PLUS_ASSIGN(...)       SEP_PLUS_ASSIGN(__VA_ARGS__)
#  define $$MINUS_ASSIGN(...)      SEP_MINUS_ASSIGN(__VA_ARGS__)
#  define $$TIMES_ASSIGN(...)      SEP_TIMES_ASSIGN(__VA_ARGS__)
#  define $$DIVIDE_ASSIGN(...)     SEP_DIVIDE_ASSIGN(__VA_ARGS__)
#  define $$MODULO_ASSIGN(...)     SEP_MODULO_ASSIGN(__VA_ARGS__)
#  define $$BIT_AND_ASSIGN(...)    SEP_BIT_AND_ASSIGN(__VA_ARGS__)
#  define $$BIT_OR_ASSIGN(...)     SEP_BIT_OR_ASSIGN(__VA_ARGS__)
#  define $$BIT_XOR_ASSIGN(...)    SEP_BIT_XOR_ASSIGN(__VA_ARGS__)
#  define $$BIT_LSHIFT_ASSIGN(...) SEP_BIT_LSHIFT_ASSIGN(__VA_ARGS__)
#  define $$BIT_RSHIFT_ASSIGN(...) SEP_BIT_RSHIFT_ASSIGN(__VA_ARGS__)
#  define $$FIELD(...)             SEP_FIELD(__VA_ARGS__)
#  define $$DEREF_FIELD(...)       SEP_DEREF_FIELD(__VA_ARGS__)
#  define $$SPACE(...)             SEP_SPACE(__VA_ARGS__)
#  define $$TAB(...)               SEP_TAB(__VA_ARGS__)
#  define $$LF(...)                SEP_LF(__VA_ARGS__)
#  define $$CR(...)                SEP_CR(__VA_ARGS__)
#endif // !MMP_DONT_USE_DOLLAR_SIGN
// NOLINTEND

#endif // !MMP_SEP_H
