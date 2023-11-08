#include "mmp_lw.h"

/* extern struct _FooNamespace {
    int foo;
    void (*Test)();
    struct _BarNamespace {
        int bar;
        void (*Test)();
    } Bar$;
} Foo$; */

/* namespace(
    Foo,
    var(int foo);
    fn((Test)());
    inner(
        Bar,
        var(int bar);
        fn((Test)(), void);
    );
); */

/* namespace_impl(
    Foo,
    fn((Test)()) {
        printf("Foo::Test\n");
    };
    inner(
        Bar,
        fn((Test)(), void) {
            printf("Foo::Bar::Test\n");
        };
    );
); */

#define var(_Type_id_Declaration)      ), 0var, _Type_id_Declaration, 0sep, 0call(
#define fn(_EnclosedIdParamsEach, ...) ), 0fn, _EnclosedIdParamsEach, MMP_IF(MMP_IS_EMPTY(__VA_ARGS__))(MMP_THEN void, MMP_ELSE __VA_ARGS__), 0sep, 0call(
#define inner(_NS, ...)                ), 0inner, _NS, 0sep, 0call(__VA_ARGS__), 0inner_end, 0sep, 0call(

#define COMPARE_0end(_X)       _X
#define COMPARE_0sep(_X)       _X
#define COMPARE_0var(_X)       _X
#define COMPARE_0fn(_X)        _X
#define COMPARE_0inner(_X)     _X
#define COMPARE_0inner_end(_X) _X
#define COMPARE_0pass(_X)      _X

#define $IS_CMD(_X)          MMP_BOOL_OPER_OVLD_UNARY($IS_CMD_, _X, 0)
#define __$IS_CMD_0end       EXISTS(1)
#define __$IS_CMD_0sep       EXISTS(1)
#define __$IS_CMD_0var       EXISTS(1)
#define __$IS_CMD_0fn        EXISTS(1)
#define __$IS_CMD_0inner     EXISTS(1)
#define __$IS_CMD_0inner_end EXISTS(1)
#define __$IS_CMD_0pass      EXISTS(1)

#define $REF(_id)          *_id
#define $REF_ENCLOSED(_id) MMP_ENCLOSE($REF(_id))
#define $FNPTR(_EnclosedIdParamsEach, _ReturnType) \
    _ReturnType $REF_ENCLOSED _EnclosedIdParamsEach

/* If a call to a preprocessing function is passed as a parameter
 * ex) MACRO(FUNC()),
 * first BLOCK the preprocessing function that calls the parameter list as an argument
 * ex) MACRO BLOCK(FUNC())
 * */

#define namespace(_NS, ...)                                  \
    extern struct _##_NS##Namespace {                        \
        MMP_EVAL(NSPRS(_NS, 0sep, 0call(__VA_ARGS__), 0end)) \
    } _NS##$

#define namespace_impl(_NS, ...)        \
    NSDPRS(_NS, __VA_ARGS__)            \
    struct _##_NS##Namespace _NS##$ = { \
        NSIPRS(_NS, __VA_ARGS__)        \
    }

#define NSPRS(_NS, _HEAD, ...)  \
    MMP_IF($IS_CMD(_HEAD))      \
    (                           \
        MMP_THEN NSPRS_##_HEAD, \
        MMP_ELSE NSPRS_RECUR    \
    ) MMP_BLOCK(_NS, __VA_ARGS__)

#define NSPRS_RECUR(_NS, ...) \
    NSPRS MMP_BLOCK(_NS, __VA_ARGS__)

#define NSPRS_0end(...) MMP_EMPTY()

#define NSPRS_EXPAND_0call(...) __VA_ARGS__
#define NSPRS_0sep(_NS, _0callSepEnclosed, ...) \
    NSPRS_EXPAND_##_0callSepEnclosed            \
        NSPRS                                   \
        MMP_BLOCK(_NS, __VA_ARGS__)

#define NSPRS_0var(_NS, _Type_id_Declaration, ...) \
    _Type_id_Declaration NSPRS MMP_BLOCK(_NS, __VA_ARGS__)

#define NSPRS_0fn(_NS, _EnclosedIdParamsEach, _ReturnType, ...) \
    $FNPTR MMP_BLOCK(_EnclosedIdParamsEach, _ReturnType)        \
    NSPRS MMP_BLOCK(_NS, __VA_ARGS__)

#define NSPRS_0inner(_NS, _INNER, ...) \
    struct _##_INNER {                 \
        NSPRS MMP_BLOCK(LIST_PUSH(_NS, _INNER), __VA_ARGS__)

#define NSPRS_0inner_end(_NS, ...)         \
    }                                      \
    MMP_CONCAT MMP_BLOCK(LIST_POP(_NS), $) \
    NSPRS MMP_BLOCK(LIST_POPPED(_NS), __VA_ARGS__)

#define LIST_PUSH(_LIST, _ITEM) \
    (_ITEM, MMP_UNCLOSE_OPT(_LIST))
#define LIST_POP(_LIST) \
    MMP_1ST MMP_BLOCK(MMP_UNCLOSE_OPT(_LIST))
#define LIST_POPPED(_LIST) \
    (MMP_REST MMP_BLOCK(MMP_UNCLOSE_OPT(_LIST)))

namespace(
    Foo,
    var(int foo);
    fn((Test)());
    inner(
        Bar,
        var(int bar);
        fn((Test)(), void);
    );
);

#define NSDPRS(_NS, ...)        \
    MMP_IF($IS_CMD(_HEAD))      \
    (                           \
        MMP_THEN NSPRS_##_HEAD, \
        MMP_ELSE NSDPRS_RECUR   \
    ) MMP_BLOCK(_NS, __VA_ARGS__)

#define NSDPRS_RECUR(_NS, ...) \
    NSDPRS MMP_BLOCK(_NS, __VA_ARGS__)

#define NSDPRS_0var(_NS, _Type_id_Declaration, ...) \
    NSDPRS MMP_BLOCK(_NS, 0pass, __VA_ARGS__)

#define NSDPRS_0pass(_NS, _HEAD, ...) \
    NSDPRS MMP_BLOCK(_NS, __VA_ARGS__)


// TODO(DevDasae): implement list join
#define LIST_JOIN(_LIST, _SEP) \
    (MMP_CONCAT3 MMP_BLOCK(LIST_POP(_LIST), LIST_POPPED(_LIST)))



#define NSPRS_0fn(_NS, _EnclosedIdParamsEach, _ReturnType, ...) \
    $FNPTR MMP_BLOCK(_EnclosedIdParamsEach, _ReturnType)        \
    NSPRS MMP_BLOCK(_NS, __VA_ARGS__)

#define NSDPRS_0end(...)         MMP_EMPTY()
#define NSDPRS_EXPAND_0call(...) __VA_ARGS__
#define NSDPRS_0sep(_NS, _0callSepEnclosed, ...) \
    NSDPRS_EXPAND_##_0callSepEnclosed            \
        NSDPRS                                   \
        MMP_BLOCK(_NS, __VA_ARGS__)



#define NSIPRS(_NS, ...)

namespace_impl(
    Foo,
    fn((Test)()) {
        printf("Foo::Test\n");
    };
    inner(
        Bar, fn((Test)(), void) {
            printf("Foo::Bar::Test\n");
        };
    );
);

void test() {
}
