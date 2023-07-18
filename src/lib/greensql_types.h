#ifndef GREENSQL_TYPES_H
#define GREENSQL_TYPES_H

// defines common types if not already defined

#include <cinttypes>
#include <cstddef>
#include <cstdint>

typedef uint16_t Port;

/* use these macros for 64 bit format portability */
#define STDu64 "%" PRIu64
#define FMTu64(fmt) "%" fmt PRIu64

#define STDi64 "%" PRIi64
#define FMTi64(fmt) "%" fmt PRIi64

#define STDx64 "%" PRIx64
#define FMTx64(fmt) "%" fmt PRIx64

#define UNUSED(x) (void)(x)

#ifdef NDEBUG
#define NORETURN_ASSERT
#else
#define NORETURN_ASSERT [[noreturn]]
#endif

#ifndef SO_PUBLIC
#if defined _WIN32 || defined __CYGWIN__
#  ifdef __GNUC__
#    define SO_PUBLIC __attribute__((dllimport))
#  else
#    define SO_PUBLIC __declspec(dllimport)
#  endif
#  define DLL_LOCAL
#else
#  ifdef HAVE_VISIBILITY
#    define SO_PUBLIC  __attribute__ ((visibility("default")))
#    define SO_PRIVATE __attribute__ ((visibility("hidden")))
#  else
#    define SO_PUBLIC
#    define SO_PRIVATE
#  endif
#endif
#endif

#if !defined(__GNUC__) || __GNUC__ < 2 || \
    (__GNUC__ == 2 && __GNUC_MINOR__ < 5)
#define __attribute__(x)    /* delete __attribute__ if non-gcc or gcc1 */
#endif

#endif