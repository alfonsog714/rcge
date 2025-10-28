#pragma once

#include "defines.h"

typedef struct linear_allocator
{
    u64 total_size;
    u64 allocated;
    void *memory;
    b8 owns_memory;
} linear_allocator;

RCAPI void linear_allocator_create(u64 total_size, void *memory, linear_allocator *out_allocator);
RCAPI void linear_allocator_destroy(linear_allocator *allocator);

RCAPI void *linear_allocator_allocate(linear_allocator *allocator, u64 size);
RCAPI void linear_allocator_free_all(linear_allocator *allocator);