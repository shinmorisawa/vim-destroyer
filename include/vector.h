// vector.h -- yet another extension.. :(
// public domain
// https://tryh4rd.dev/

#pragma once

#include "base.h"
#include <stdlib.h>

#ifndef BASE_NO_VECTOR_IMPLEMENTATION

#    define DeclareVector(T)                                             \
        typedef struct {                                                 \
            T* data;                                                     \
            u64 count;                                                   \
            u64 capacity;                                                \
        } Vector##T;                                                     \
        Vector##T vector##T##_init(u64 size) {                           \
            Vector##T vector = {0};                                      \
            vector.capacity = size;                                      \
            vector.count = 0;                                            \
            vector.data = malloc(size * sizeof(T));                      \
            return vector;                                               \
        }                                                                \
        void vector##T##_push(Vector##T* vector, T data) {               \
            if (vector->count >= vector->capacity) {                     \
                u64 old_capacity = vector->capacity;                     \
                vector->capacity =                                       \
                    (old_capacity == 0) ? 8 : vector->capacity * 2;      \
                T* new_alloc =                                           \
                    realloc(vector->data, vector->capacity * sizeof(T)); \
                if (unlikely(!new_alloc)) return;                        \
                vector->data = new_alloc;                                \
            }                                                            \
            vector->data[vector->count++] = data;                        \
        }                                                                \
        void vector##T##_free(Vector##T* vector) {                       \
            free(vector->data);                                          \
        }

#endif
