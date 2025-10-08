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

/**
 * ****************************
 * General math functions
 * ****************************
 */
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

RCAPI i32 rcrandom();
RCAPI i32 rcrandom_in_range(i32 min, i32 max);
RCAPI f32 rcfrandom();
RCAPI f32 rcfrandom_in_range(f32 min, f32 max);

/**
 * ****************************
 * Vec2 math functions
 * ****************************
 */

RCINLINE vec2 vec2_create(f32 x, f32 y)
{
    vec2 out_vec;
    out_vec.x = x;
    out_vec.y = y;
    return out_vec;
}

RCINLINE vec2 vec2_zero()
{
    return (vec2){0.0f, 0.0f};
}

RCINLINE vec2 vec2_one()
{
    return (vec2){1.0f, 1.0f};
}

RCINLINE vec2 vec2_right()
{
    return (vec2){1.0f, 0.0f};
}

RCINLINE vec2 vec2_left()
{
    return (vec2){-1.0f, 0.0f};
}

RCINLINE vec2 vec2_up()
{
    return (vec2){0.0f, 1.0f};
}

RCINLINE vec2 vec2_down()
{
    return (vec2){0.0f, -1.0f};
}

/**
 * @brief Adds vector_1 to vector_0 and returns the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The resulting vector.
 */
RCINLINE vec2 vec2_add(vec2 vec_0, vec2 vec_1)
{
    return (vec2){vec_0.x + vec_1.x,
                  vec_0.y + vec_1.y};
}

/**
 * @brief Subtracts vector_1 from vector_0 and returns the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The resulting vector.
 */
RCINLINE vec2 vec2_sub(vec2 vec_0, vec2 vec_1)
{
    return (vec2){vec_0.x - vec_1.x,
                  vec_0.y - vec_1.y};
}

/**
 * @brief Multiplies vector_0 by vector_1 and returns the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The resulting vector.
 */
RCINLINE vec2 vec2_mul(vec2 vec_0, vec2 vec_1)
{
    return (vec2){vec_0.x * vec_1.x,
                  vec_0.y * vec_1.y};
}

/**
 * @brief Divides vector_0 by vector_1 and returns the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The resulting vector.
 */
RCINLINE vec2 vec2_div(vec2 vec_0, vec2 vec_1)
{
    return (vec2){vec_0.x / vec_1.x,
                  vec_0.y / vec_1.y};
}

/**
 * @brief Returns the squared length of the provided vector.
 *
 * @param vec The vector to retrieve the squared length of.
 * @return The squared length.
 */
RCINLINE f32 vec2_length_squared(vec2 vec)
{
    return (f32)(vec.x * vec.x + vec.y * vec.y);
}

/**
 * @brief Returns the length of the provided vector.
 *
 * @param vec The vector to retrieve the length of.
 * @return The length.
 */
RCINLINE f32 vec2_length(vec2 vec)
{
    return rcsqrt(vec2_length_squared(vec));
}

/**
 * @brief Normalize the provided vector in place to a unit (-1, 1) vector.
 *
 * @param vec A pointer to the vector to be normalized.
 */
RCINLINE void vec2_normalize(vec2 *vec)
{
    const f32 length = vec2_length(*vec);
    vec->x /= length;
    vec->y /= length;
}

/**
 * @brief Does the same as vec2_normalize, but returns a copy of the normalized vector instead of normalizing the vector in-place.
 *
 * @param vec The vector to be normalized.
 * @return The normalized vector for the supplied vector.
 */
RCINLINE vec2 vec2_normalized(vec2 vec)
{
    vec2_normalize(&vec);
    return vec;
}

/**
 * @brief Compares all elements of vec_0 and vec_1 and ensures that the difference is less than
 * the provided tolerance.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @param tolerance The difference tolerance. Commonly RC_FLOAT_EPSILON.
 * @return True if within tolerance; false otherwise.
 */
RCINLINE b8 vec2_compare(vec2 vec_0, vec2 vec_1, f32 tolerance)
{
    if (rcabs(vec_0.x - vec_1.x) > tolerance)
    {
        return FALSE;
    }

    if (rcabs(vec_0.y - vec_1.y) > tolerance)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief Returns the distance between vec_0 and vec_1.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The distance between the two supplied vectors.
 */
RCINLINE f32 vec2_distance(vec2 vec_0, vec2 vec_1)
{
    vec2 distance = (vec2){
        vec_0.x - vec_1.x,
        vec_0.y - vec_1.y,
    };
    return vec2_length(distance);
}