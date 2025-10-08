#pragma once

#include "defines.h"
#include "math_types.h"

#define RC_PI 3.14159265358979323846f
#define RC_PI_2 (2 * RC_PI)
#define RC_HALF_PI (0.5f * RC_PI)
#define RC_QUARTER_PI (0.25f * RC_PI)
#define RC_ONE_OVER_PI (1.0f / RC_PI)
#define RC_ONE_OVER_TWO_PI (1.0f / RC_PI_2)
#define RC_SQRT_TWO 1.41421356237309504880f
#define RC_SQRT_THREE 1.73205080756887729352f
#define RC_SQRT_ONE_OVER_TWO 0.70710678118654752440f
#define RC_SQRT_ONE_OVER_THREE 0.57735026918962576450f
#define RC_DEG2RAD_MULTIPLIER_ (RC_PI / 180.0f)
#define RC_RAD2DEG_MULTIPLIER (180.0f / RC_PI)

#define RC_SEC_TO_MS_MULTIPLIER 1000.0f
#define RC_MS_TO_SEC_MULTIPLIER 0.001f

#define RC_INFINITY 1e30f
#define RC_FLOAT_EPSILON 1.192092896e-07f

/* General math functions */
RCAPI f32 rcsin(f32 x);
RCAPI f32 rccos(f32 x);
RCAPI f32 rctan(f32 x);
RCAPI f32 rcacos(f32 x);
RCAPI f32 rcsqrt(f32 x);
RCAPI f32 rcabs(f32 x);

RCINLINE b8 is_power_of_2(u64 value)
{
    return (value != 0) && ((value & (value - 1)) == 0);
}