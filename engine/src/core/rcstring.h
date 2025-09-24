#pragma once

#include "defines.h"

RCAPI u64 string_length(const char *str);
RCAPI char *string_duplicate(const char *str);
RCAPI b8 strings_equal(const char *str0, const char *str1);