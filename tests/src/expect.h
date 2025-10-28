#include <core/logger.h>
#include <math/rcmath.h>

#define expect_should_be(expected, actual)                                                              \
    if (actual != expected)                                                                             \
    {                                                                                                   \
        RCERROR("--> Expected %lld, but got: %lld. File: %s:%d.", expected, actual, __FILE__, __LINE__) \
        return false;                                                                                   \
    }