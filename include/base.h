// base.h - mini C header i use everywhere
// public domain'd
// https://tryh4rd.dev/

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;

#define BASE_MAJOR_VERSION 0
#define BASE_MINOR_VERSION 0
#define BASE_PATCH_VERSION 1

#ifndef BASE_DEFAULT_ERROR_STRUCT
#    define BASE_DEFAULT_ERROR_STRUCT

typedef struct Error {
    const char* msg;
} Error;
#endif

#ifndef BASE_DEFAULT_RESULT_STRUCT
#    define BASE_DEFAULT_RESULT_STRUCT

typedef struct Result {
    bool ok;
    u64 code;
    Error err;
} Result;
#endif

#define ERROR_INIT(m) \
    (Error) {         \
        .msg = m      \
    }
#define RESULT_INIT(o, c, e)         \
    (Result) {                       \
        .ok = o, .code = c, .err = e \
    }

/* gcc/clang extension macros (fun!) */
#ifndef BASE_DISABLE_COMPILER_EXTENSION_MACROS
#    define likely(x)         __builtin_expect(!!(x), 1)
#    define unlikely(x)       __builtin_expect(!!(x), 0)
#    define cleanup(function) __attribute__((cleanup(function)))
#    define packed(name)      name __attribute__((packed))
#    define unreachable       __builtin_unreachable()
#    define panick            __builtin_trap()

#    ifndef BASE_NO_DEBUG
#        define assert(x)                   \
            ({                              \
                if (unlikely(!(x))) panick; \
            })
#    else
#        define assert(x) ((void)0)
#    endif
#endif

#ifndef BASE_NO_HANDY_MACROS
#    define max(x, y)           \
        ({                      \
            typeof(x) _x = (x); \
            typeof(y) _y = (y); \
            _x > _y ? _x : _y;  \
        })
#    define min(x, y)           \
        ({                      \
            typeof(x) _x = (x); \
            typeof(y) _y = (y); \
            _x < _y ? _x : _y;  \
        })
#    define base_abs(x)         \
        ({                      \
            typeof(x) _x = (x); \
            _x < 0 ? -_x : _x;  \
        })
#    define clamp(x, lo, hi)   (min(max((x), (lo)), (hi)))
#    define lerp(x, y, t)      ((x) + ((y) - (x)) * (t))
#    define between(x, lo, hi) ((x) >= (lo) && (x) <= (hi))
#    define array_len(array)   (sizeof(array) / sizeof((array)[0]))
#    define swap(x, y)            \
        ({                        \
            typeof(x) _tmp = (x); \
            x = (y);              \
            y = _tmp;             \
        })
#endif
