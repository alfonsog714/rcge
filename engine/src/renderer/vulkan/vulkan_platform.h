#pragma once

#include "defines.h"

/**
 * Appends the names of required extensions for the host platform to the
 * names_darray variable.
 */
void platform_get_required_extension_names(const char ***names_darray);