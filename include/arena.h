// arena.h -- extension of base.h
// public domain
// https://tryh4rd.dev/

#pragma once

#include "base.h"
#include <stdlib.h>
#include <string.h>

typedef struct Arena {
    u8* ptr;
    u64 capacity;
    u64 last_offset;
    u64 current_offset;
} Arena;

#ifndef BASE_NO_ARENA_IMPLEMENTATION

Arena* arena_init(u64 size) {
    Arena* arena = malloc(sizeof(Arena) + size);
    if (unlikely(!arena)) {
        log("[arena] alloc failed\n");
        panick;
    }
    arena->capacity = size;
    arena->current_offset = 0;
    arena->last_offset = 0;
    arena->ptr = (u8*)(arena + 1);
    memset(arena->ptr, 0, size);
    return arena;
}

void arena_free(Arena* arena) {
    free(arena);
}

void arena_reset(Arena* arena) {
    arena->last_offset = arena->current_offset;
    arena->current_offset = 0;
}

void* arena_push(Arena* arena, u64 size) {
    u64 aligned_size = (size + 7) & ~7;
    assert(arena->current_offset + aligned_size <= arena->capacity);

    void* result = arena->ptr + arena->current_offset;
    arena->last_offset = arena->current_offset;
    arena->current_offset += aligned_size;

    return result;
}

#endif
