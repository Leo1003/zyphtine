#include "vector.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 10

// Here are the hidden structure definition
struct zyp_vec {
    void *buffer;
    size_t element_size;
    size_t length;
    size_t capacity;
};

static inline void *_zyp_vec_fast_get(struct zyp_vec *vec, size_t index)
{
    return vec->buffer + (vec->element_size * index);
}

struct zyp_vec *zyp_vec_new(size_t element_size)
{
    return zyp_vec_with_capacity(element_size, DEFAULT_CAPACITY);
}

struct zyp_vec *zyp_vec_with_capacity(size_t element_size, size_t capacity)
{
    if (element_size == 0) {
        return NULL;
    }
    struct zyp_vec *vec = (struct zyp_vec *)malloc(sizeof(struct zyp_vec));
    if (!vec) {
        return NULL;
    }

    vec->buffer = malloc(element_size * capacity);
    if (!vec->buffer) {
        free(vec);
        return NULL;
    }
    vec->capacity = capacity;
    vec->element_size = element_size;
    vec->length = 0;

    return vec;
}

void zyp_vec_free(struct zyp_vec *vec)
{
    if (vec) {
        free(vec->buffer);
    }
    free(vec);
}

int zyp_vec_reserve(struct zyp_vec *vec, size_t capacity)
{
    if (!vec) {
        return 1;
    }
    if (vec->capacity >= capacity) {
        return 0;
    }

    void *newbuf = realloc(vec->buffer, vec->element_size * capacity);
    if (!newbuf) {
        return 1;
    }

    vec->buffer = newbuf;
    vec->capacity = capacity;
    return 0;
}

int zyp_vec_shrink(struct zyp_vec *vec, size_t capacity)
{
    if (!vec) {
        return 1;
    }
    if (vec->capacity <= capacity) {
        return 0;
    }
    if (capacity < vec->length) {
        capacity = vec->length;
    }

    void *newbuf = realloc(vec->buffer, vec->element_size * capacity);
    if (!newbuf) {
        return 1;
    }

    vec->buffer = newbuf;
    vec->capacity = capacity;
    return 0;
}

size_t zyp_vec_length(const struct zyp_vec *vec)
{
    if (!vec) {
        return 0;
    }
    return vec->length;
}

bool zyp_vec_is_empty(const struct zyp_vec *vec)
{
    if (!vec) {
        return true;
    }
    return vec->length == 0;
}

void zyp_vec_clear(struct zyp_vec *vec)
{
    if (!vec) {
        return;
    }
    vec->length = 0;
}

void *zyp_vec_insert(struct zyp_vec *vec, size_t index, const void *data)
{
    if (!vec || !data || (index > vec->length)) {
        return NULL;
    }

    if (vec->capacity <= vec->length) {
        if (zyp_vec_reserve(vec, vec->capacity * 2)) {
            return NULL;
        }
    }

    void *ins_ptr = _zyp_vec_fast_get(vec, index);
    // Check if need to move memory
    if (index < vec->length) {
        memmove(_zyp_vec_fast_get(vec, index + 1),
                ins_ptr,
                vec->element_size * (vec->length - index));
    }
    memcpy(ins_ptr, data, vec->element_size);
    vec->length++;

    return ins_ptr;
}

void *zyp_vec_remove(struct zyp_vec *vec, size_t index, void *dest)
{
    if (!vec || (index >= vec->length)) {
        return NULL;
    }

    void *rm_ptr = _zyp_vec_fast_get(vec, index);
    if (dest) {
        memcpy(dest, rm_ptr, vec->element_size);
    }
    // Check if need to move memory
    if (index < vec->length - 1) {
        memmove(rm_ptr,
                _zyp_vec_fast_get(vec, index + 1),
                vec->element_size * (vec->length - index - 1));
    }
    vec->length--;

    return dest;
}

void *zyp_vec_push(struct zyp_vec *vec, const void* data)
{
    if (!vec) {
        return NULL;
    }
    return zyp_vec_insert(vec, vec->length, data);
}

void *zyp_vec_pop(struct zyp_vec *vec, void *dest)
{
    if (!vec || vec->length == 0) {
        return NULL;
    }
    return zyp_vec_remove(vec, vec->length - 1, dest);
}

const void *zyp_vec_get(const struct zyp_vec *vec, size_t index)
{
    if (!vec || index >= vec->length) {
        return NULL;
    }
    return _zyp_vec_fast_get((struct zyp_vec *)vec, index);
}

void *zyp_vec_get_mut(struct zyp_vec *vec, size_t index)
{
    if (!vec || index >= vec->length) {
        return NULL;
    }
    return _zyp_vec_fast_get(vec, index);
}
