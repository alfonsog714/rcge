#include "rcmath.h"
#include "platform/platform.h"

#include <math.h>
#include <stdlib.h>

static b8 rand_seeded = FALSE;

/* The purpose of these is to avoid including math.h everywhere. */
f32 rcsin(f32 x)
{
    return sinf(x);
}

f32 rccos(f32 x)
{
    return cosf(x);
}

f32 rctan(f32 x)
{
    return tanf(x);
}

f32 rcacos(f32 x)
{
    return acosf(x);
}

f32 rcsqrt(f32 x)
{
    return sqrtf(x);
}

f32 rcabs(f32 x)
{
    return fabsf(x);
}

i32 rcrandom()
{
    if (!rand_seeded)
    {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }
    return rand();
}

i32 rcrandom_in_range(i32 min, i32 max)
{
    if (!rand_seeded)
    {
        srand((u32)platform_get_absolute_time());
        rand_seeded = TRUE;
    }

    return (rand() % (max - min + 1)) + min;
}

f32 rcfrandom()
{
    return (float)rcrandom() / (f32)RAND_MAX;
}

f32 rcfrandom_in_range(f32 min, f32 max)
{
    return min + ((float)rcrandom() / ((f32)RAND_MAX / (max - min)));
}