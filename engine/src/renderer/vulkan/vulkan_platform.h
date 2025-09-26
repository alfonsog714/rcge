#pragma once

#include "defines.h"

struct platform_state;
struct vulkan_context;

/**
 * Appends the names of required extensions for the host platform to the
 * names_darray variable.
 */
void platform_get_required_extension_names(const char ***names_darray);

b8 platform_create_vulkan_surface(
    struct platform_state *plat_state,
    struct vulkan_context *context);