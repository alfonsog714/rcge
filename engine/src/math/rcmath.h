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
#define RC_DEG2RAD_MULTIPLIER (RC_PI / 180.0f)
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

/**
 * ****************************
 * Vec3 math functions
 * ****************************
 */

/**
 * @brief Creates and returns a 3-element vector.
 *
 * @param x The first element.
 * @param y The second element.
 * @param z The third element.
 * @return A new 3-element vector.
 */
RCINLINE vec3 vec3_create(f32 x, f32 y, f32 z)
{
    return (vec3){x, y, z};
}

/**
 * @brief Returns a new vec3 containing the x, y, z components of
 * the provided vec4.
 *
 * @param vec The 4-component vector to extract from.
 * @return A new vec3.
 */
RCINLINE vec3 vec3_from_vec4(vec4 vec)
{
    return (vec3){vec.x, vec.y, vec.z};
}

/**
 * @brief Returns a new vec4 containing the provided vector's x, y
 * and z components and uses the provided w for the w component.
 *
 * @param vec The 3-component vector.
 * @param w The w component for the new vector.
 * @return The new vec4.
 */
RCINLINE vec4 vec3_to_vec4(vec3 vec, f32 w)
{
    return (vec4){vec.x, vec.y, vec.z, w};
}

RCINLINE vec3 vec3_zero()
{
    return (vec3){0.0f, 0.0f, 0.0f};
}

RCINLINE vec3 vec3_one()
{
    return (vec3){1.0f, 1.0f, 1.0f};
}

RCINLINE vec3 vec3_left()
{
    return (vec3){-1.0f, 0.0f, 0.0f};
}

RCINLINE vec3 vec3_right()
{
    return (vec3){1.0f, 0.0f, 0.0f};
}

RCINLINE vec3 vec3_up()
{
    return (vec3){0.0f, 1.0f, 0.0f};
}

RCINLINE vec3 vec3_down()
{
    return (vec3){0.0f, -1.0f, 0.0f};
}

RCINLINE vec3 vec3_forward()
{
    return (vec3){0.0f, 0.0f, -1.0f};
}

RCINLINE vec3 vec3_backward()
{
    return (vec3){0.0f, 0.0f, 1.0f};
}

/**
 * @brief Adds vec_1 to vec_0 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @returns A copy of the result vector.
 */
RCINLINE vec3 vec3_add(vec3 vec_0, vec3 vec_1)
{
    return (vec3){
        vec_0.x + vec_1.x,
        vec_0.y + vec_1.y,
        vec_0.z + vec_1.z};
}

/**
 * @brief Subtracts vec_1 from vec_0 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @returns A copy of the result vector.
 */
RCINLINE vec3 vec3_sub(vec3 vec_0, vec3 vec_1)
{
    return (vec3){
        vec_0.x - vec_1.x,
        vec_0.y - vec_1.y,
        vec_0.z - vec_1.z};
}

/**
 * @brief Multiplies vec_1 by vec_0 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @returns A copy of the result vector.
 */
RCINLINE vec3 vec3_mul(vec3 vec_0, vec3 vec_1)
{
    return (vec3){
        vec_0.x * vec_1.x,
        vec_0.y * vec_1.y,
        vec_0.z * vec_1.z};
}

/**
 * @brief Divides vec_0 by vec_1 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @returns A copy of the result vector.
 */
RCINLINE vec3 vec3_div(vec3 vec_0, vec3 vec_1)
{
    return (vec3){
        vec_0.x / vec_1.x,
        vec_0.y / vec_1.y,
        vec_0.z / vec_1.z};
}

/**
 * @brief Multiplies all elements by a scalar and returns a copy of the result.
 *
 * @param vec The vector to be multiplied.
 * @param scalar The scalar value to multiply by.
 * @returns A copy of the result vector.
 */
RCINLINE vec3 vec3_mul_scalar(vec3 vec, f32 scalar)
{
    return (vec3){
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar};
}

/**
 * @brief Returns the squared length of the vector.
 *
 * @param vec The vector to retrieve the squared length of.
 * @returns The squared length.
 */
RCINLINE f32 vec3_length_squared(vec3 vec)
{
    return vec.x * vec.x + vec.y + vec.y + vec.z + vec.z;
}

/**
 * @brief Returns the length of the vector.
 *
 * @param vec The vector to retrieve the length of.
 * @returns The length.
 */
RCINLINE f32 vec3_length(vec3 vec)
{
    return rcsqrt(vec3_length_squared(vec));
}

/**
 * @brief Normalizes the provided vector in-place.
 *
 * @param vec A pointer to the vector to be normalized.
 */
RCINLINE void vec3_normalize(vec3 *vec)
{
    const f32 length = vec3_length(*vec);
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
}

/**
 * @brief Normalizes the provided vector and returns a copy of the result..
 *
 * @param vec A pointer to the vector to be normalized.
 * @return The normalized version of the provided vector.
 */
RCINLINE vec3 vec3_normalized(vec3 vec)
{
    vec3_normalize(&vec);
    return vec;
}

/**
 * @brief Returns the dot product between the two provided vectors.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @returns The dot product.
 */
RCINLINE f32 vec3_dot(vec3 vec_0, vec3 vec_1)
{
    f32 dot_product = 0;
    dot_product += vec_0.x * vec_1.x;
    dot_product += vec_0.y * vec_1.y;
    dot_product += vec_0.z * vec_1.z;
    return dot_product;
}

/**
 * @brief Calculates the cross product of the supplied vectors.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The resulting vector from the cross product of the two provided vectors.
 */
RCINLINE vec3 vec3_cross(vec3 vec_0, vec3 vec_1)
{
    return (vec3){
        vec_0.y * vec_1.z - vec_0.z * vec_1.y,
        vec_0.z * vec_1.x - vec_0.x * vec_1.z,
        vec_0.x * vec_1.y - vec_0.y * vec_1.x};
}

/**
 * @brief Compares all elements of vec_0 and vec_1 and ensures the difference is less than the tolerance.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @param tolerance The difference tolerance.
 * @return True if within tolerance; false otherwise.
 */
RCINLINE b8 vec3_compare(vec3 vec_0, vec3 vec_1, f32 tolerance)
{
    if (rcabs(vec_0.x - vec_1.x) > tolerance)
    {
        return FALSE;
    }

    if (rcabs(vec_0.y - vec_1.y) > tolerance)
    {
        return FALSE;
    }

    if (rcabs(vec_0.z - vec_1.z) > tolerance)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief Returns the distance between the two provided vectors.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 * @return The distance between vec_0 and vec_1.
 */
RCINLINE f32 vec3_distance(vec3 vec_0, vec3 vec_1)
{
    vec3 d = (vec3){
        vec_0.x - vec_1.x,
        vec_0.y - vec_1.y,
        vec_0.z - vec_1.z};

    return vec3_length(d);
}

/**
 * ****************************
 * Vec4 math functions
 * ****************************
 */

/**
 * @brief Creates and returns a new 4-element vector.
 *
 * @param x The first value.
 * @param y The second value.
 * @param z The third value.
 * @param w The fourth value.
 * @return A new 4-element vector.
 */
RCINLINE vec4 vec4_create(f32 x, f32 y, f32 z, f32 w)
{
    vec4 out_vector;
#if defined(RCUSE_SIMD)
    out_vector.data = _mm_setr_ps(x, y, z, w);
#else
    out_vector.x = x;
    out_vector.y = y;
    out_vector.z = z;
    out_vector.w = w;
#endif
    return out_vector;
}

/**
 * @brief Returns a new vec3 containing the x, y, z components of
 * the provided vec4.
 *
 * @param vec The 4-component vector to extract from.
 * @return A new vec3.
 */
RCINLINE vec3 vec4_to_vec3(vec4 vec)
{
    return (vec3){vec.x, vec.y, vec.z};
}

/**
 * @brief Returns a new vec4 using the provided vec3's x, y and z components and
 * the provided w for the w component.
 *
 * @param vec The 3-component vector.
 * @param w The w component.
 * @return The new vec4.
 */
RCINLINE vec4 vec4_from_vec3(vec3 vec, f32 w)
{
#if defined(RCUSE_SIMD)
    vec4 out_vector;
    out_vector.data = _mm_setr_ps(vec.x, vec.y, vec.z, w); // TODO: look at this again later if you're having issues with vec4 conversions.
    return out_vector;
#else
    return (vec4){vec.x, vec.y, vec.z, w};
#endif
}

RCINLINE vec4 vec4_zero()
{
    return (vec4){0.0f, 0.0f, 0.0f, 0.0f};
}

RCINLINE vec4 vec4_one()
{
    return (vec4){1.0f, 1.0f, 1.0f, 1.0f};
}

/**
 * @brief Adds vec_0 and vec_1 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 *
 * @return The resulting vector.
 */
RCINLINE vec4 vec4_add(vec4 vec_0, vec4 vec_1)
{
    return (vec4){
        vec_0.x + vec_1.x,
        vec_0.y + vec_1.y,
        vec_0.z + vec_1.z,
        vec_0.w + vec_1.w};
}

/**
 * @brief Subtracts vec_1 from vec_0 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 *
 * @return The resulting vector.
 */
RCINLINE vec4 vec4_sub(vec4 vec_0, vec4 vec_1)
{
    return (vec4){
        vec_0.x - vec_1.x,
        vec_0.y - vec_1.y,
        vec_0.z - vec_1.z,
        vec_0.w - vec_1.w};
}

/**
 * @brief Multiplies vec_0 and vec_1 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 *
 * @return The resulting vector.
 */
RCINLINE vec4 vec4_mul(vec4 vec_0, vec4 vec_1)
{
    return (vec4){
        vec_0.x * vec_1.x,
        vec_0.y * vec_1.y,
        vec_0.z * vec_1.z,
        vec_0.w * vec_1.w};
}

/**
 * @brief Divides vec_0 by vec_1 and returns a copy of the result.
 *
 * @param vec_0 The first vector.
 * @param vec_1 The second vector.
 *
 * @return The resulting vector.
 */
RCINLINE vec4 vec4_div(vec4 vec_0, vec4 vec_1)
{
    return (vec4){
        vec_0.x / vec_1.x,
        vec_0.y / vec_1.y,
        vec_0.z / vec_1.z,
        vec_0.w / vec_1.w};
}

/**
 * @brief Acquires the squared length of the provided vec4.
 *
 * @param vec vec4 to retrieve the squared length of.
 * @return The squared length.
 */
RCINLINE f32 vec4_length_squared(vec4 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

/**
 * @brief Returns the length of the given vec4.
 *
 * @param vec vec4 to get the length of.
 * @return The length of the provided vec4.
 */
RCINLINE f32 vec4_length(vec4 vec)
{
    return rcsqrt(vec4_length_squared(vec));
}

/**
 * @brief Normalizes the provided vec4 in-place.
 *
 * @param vec A pointer to the vec4 to be normalized.
 */
RCINLINE void vec4_normalize(vec4 *vec)
{
    f32 length = vec4_length(*vec);
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
    vec->w /= length;
}

/**
 * @brief Normalizes the provided vec4 and returns a copy of the result.
 *
 * @param vec The vec4 to be normalized.
 * @return The normalized vector.
 */
RCINLINE vec4 vec4_normalized(vec4 vec)
{
    vec4_normalize(&vec);
    return vec;
}

RCINLINE f32 vec4_dot_f32(
    f32 a0, f32 a1, f32 a2, f32 a3,
    f32 b0, f32 b1, f32 b2, f32 b3)
{
    f32 dot;
    dot =
        a0 * b0 +
        a1 * b1 +
        a2 * b2 +
        a3 * b3;

    return dot;
}