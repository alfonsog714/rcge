#pragma once
#include "vulkan_types.inl"

/**
 * Returns the strings representation of a VkResult.
 * @param result VkResult to get the string for.
 * @param get_extended boolean that indicates whether or not to return an extended result.
 * @returns The error code and/or extended error message as a string.
 */
const char *vulkan_result_string(VkResult result, b8 get_extended);

/**
 * Indicates if the passed VkResult is a success or not based on the Vulkan spec.
 * @returns True if success; otherwise false.
 */
b8 vulkan_result_is_success(VkResult result);