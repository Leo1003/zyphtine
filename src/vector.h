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
 * @brief Free the vector
 * Free all the memory used by the buffer and the struct itself.
 * After calling this function, the element in the vector should not be accessed.
 *
 * @param vec vector object
 */
void zyp_vec_free(struct zyp_vec *vec);

/**
 * @brief Increase the capacity of the vector
 * This function will increase the capacity to the requested size.
 * If the capacity is less than or equal to the current capacity, it will be
 * a no-op, otherwise, the memory will be reallocated.
 *
 * @param vec vector object
 * @param capacity capacity in element counts
 * @return 0 if successful, 1 otherwise
 */
int zyp_vec_reserve(struct zyp_vec *vec, size_t capacity);

/**
 * @brief Decrease the capacity of the vector
 * This function will decrease the capacity to the requested size.
 * If the capacity is greater than or equal to the current capacity, it will be
 * a no-op.
 * Otherwise, the memory will be reallocated.
 * @note If the requested size is smaller than the used size, then it will make
 * the capacity to fit the currently hold elements.
 *
 * @param vec vector object
 * @param capacity capacity in element counts
 * @return 0 if successful, 1 otherwise
 */
int zyp_vec_shrink(struct zyp_vec *vec, size_t capacity);

/**
 * @brief Get the element count of the vector
 *
 * @param vec vector object
 * @return Return the total element count in the vector
 */
size_t zyp_vec_length(const struct zyp_vec *vec);

/**
 * @brief Determine if the vector is empty
 *
 * @param vec vector object
 * @return Return true if the vector has no element in it, false otherwise
 */
bool zyp_vec_is_empty(const struct zyp_vec *vec);

/**
 * @brief Clear elements in the vector
 * This function won't shrink the capacity, or wipe out the content.
 * It just set the count number to 0.
 *
 * @param vec vector object
 */
void zyp_vec_clear(struct zyp_vec *vec);

/**
 * @brief Insert an element into the vector
 * Copy the specific data to the requested position, it would move the data or
 * reallocate if needed. After successful operation, it will return a pointer
 * to the inserted element.
 *
 * @see zyp_vec_push()
 * @param vec vector object
 * @param index index number to place the item
 * @param data item to be inserted
 * @retval NULL fail to allocate memory, or the index is not valid
 * @return Pointer to the newly inserted item
 */
void *zyp_vec_insert(struct zyp_vec *vec, size_t index, const void* data);

/**
 * @brief Remove the element at the index
 * Delete the element and do memory moving to fill the empty.
 * If dest is not NULL, then this function would copy the content to the pointer
 * before delete it, and return dest pointer.
 *
 * @see zyp_vec_pop()
 * @param vec vector object
 * @param index index number to be removed
 * @param dest destination to place the being removed element
 * @retval NULL No dest provided, or the index is not valid
 * @return Pointer to the copied out element
 */
void *zyp_vec_remove(struct zyp_vec *vec, size_t index, void *dest);

/**
 * @brief Insert an element at the end of the vector
 * Copy the specific data to the end of the vector, it may reallocate if
 * the capacity is not enough. After successful operation, it will return a
 * pointer to the inserted element.
 *
 * @see zyp_vec_insert()
 * @param vec vector object
 * @param data item to be inserted
 * @retval NULL fail to allocate memory
 * @return Pointer to the newly inserted item
 */
void *zyp_vec_push(struct zyp_vec *vec, const void* data);

/**
 * @brief Remove the element at the end of the vector
 * Delete the element at the end of the vector. But different to zyp_vec_remove(),
 * it just make count number minus 1. So this is faster than remove!
 * If dest is not NULL, then this function would copy the content to the pointer
 * before delete it, and return dest pointer.
 *
 * @see zyp_vec_remove()
 * @param vec vector object
 * @param dest destination to place the being removed element
 * @retval NULL No dest provided
 * @return Pointer to the copied out element
 */
void *zyp_vec_pop(struct zyp_vec *vec, void *dest);

/**
 * @brief Get the pointer to the element at the index
 * Return a constant pointer to the element inside the vector.
 * If you want to modify the content, better use zyp_vec_get_mut().
 *
 * @see zyp_vec_get_mut()
 * @param vec vector object
 * @param index index number of the element
 * @retval NULL Invalid index
 * @return Pointer to the element
 */
const void *zyp_vec_get(const struct zyp_vec *vec, size_t index);

/**
 * @brief Get the mutable pointer to the element at the index
 * Return a mutable pointer to the element inside the vector.
 * If you don't have to modify the content, better use zyp_vec_get().
 *
 * @see zyp_vec_get()
 * @param vec vector object
 * @param index index number of the element
 * @retval NULL Invalid index
 * @return Pointer to the element
 */
void *zyp_vec_get_mut(struct zyp_vec *vec, size_t index);

#endif
