#ifndef _ZYP_VECTOR_H
#define _ZYP_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @file
 * This header defines a dynamic array and its related functions
 */

/**
 * @brief An dynamic array
 * This data structure will allocate a continous memory area as an array to
 * store elements. It will auto increase the capacity when needed, but won't
 * decrease it automatic.
 * Since this is an opaque structure, use zyp_vec_*() functions to access the
 * data.
 * @see zyp_vec_new()
 * @see zyp_vec_with_capacity()
 */
struct zyp_vec;
// TODO: hide the actual definition
struct zyp_vec {
    void *buffer;
    size_t element_size;
    size_t length;
    size_t capacity;
};

/**
 * @brief Create a new vector
 * This function will allocate a memory area to create a vector
 * with default capacity.
 * @see zyp_vec_with_capacity()
 *
 * @param element_size size in bytes for each element, must greater than 0
 * @retval NULL fail to allocate memory
 * @return newly created vector
 */
struct zyp_vec *zyp_vec_new(size_t element_size);

/**
 * @brief Create a new vector with specifed capacity
 * This function will allocate a memory area to create a vector
 * with specifed capacity being able to hold certain amount of elements.
 * @see zyp_vec_new()
 *
 * @param element_size size in bytes for each element, must greater than 0
 * @param capacity initial capacity in element counts
 * @retval NULL fail to allocate memory
 * @return newly created vector
 */
struct zyp_vec *zyp_vec_with_capacity(size_t element_size, size_t capacity);

/**
 * @brief Increase the capacity of the vector
 * This function will increase the capacity to the requested size.
 * If the capacity is less than or equal to the current capacity, it will be
 * a no-op, otherwise, the memory will reallocate and copy.
 *
 * @param vec vector object
 * @param capacity capacity in element counts
 */
void zyp_vec_reserve(struct zyp_vec *vec, size_t capacity);

/**
 * @brief Decrease the capacity of the vector
 * This function will decrease the capacity to the requested size.
 * If the capacity is greater than or equal to the current capacity, it will be
 * a no-op.
 * Otherwise, the memory will reallocate and copy.
 * @note If the requested size is smaller than the used size, then it will make
 * the capacity to fit the currently hold elements.
 *
 * @param vec vector object
 * @param capacity capacity in element counts
 */
void zyp_vec_shrink(struct zyp_vec *vec, size_t capacity);

/**
 * @brief Return the total element count in the vector
 */
size_t zyp_vec_length(const struct zyp_vec *vec);

bool zyp_vec_is_empty(const struct zyp_vec *vec);

void zyp_vec_clear(struct zyp_vec *vec);

void *zyp_vec_insert(struct zyp_vec *vec, size_t index, const void* data);

void *zyp_vec_remove(struct zyp_vec *vec, size_t index, void *dest);

void *zyp_vec_push(struct zyp_vec *vec, const void* data);

void *zyp_vec_pop(struct zyp_vec *vec, void *dest);

const void *zyp_vec_get(const struct zyp_vec *vec, size_t index);

void *zyp_vec_get_mut(struct zyp_vec *vec, size_t index);

#endif