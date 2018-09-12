#ifndef __DARRAY_H__
#define __DARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Guard C code in headers, while including them from C++ */
#ifndef __cplusplus
#   define INCLUSION_GUARDS_BEGIN
#   define INCLUSION_GUARDS_END
#else
#   define INCLUSION_GUARDS_BEGIN extern "C" {
#   define INCLUSION_GUARDS_END   }
#endif /* __cplusplus */

/*
 * Provide definitions for some commonly used macros.
 * Some of them are only provided if they haven't already
 * been defined. It is assumed that if they are already
 * defined then the current definition is correct.
 */
#ifndef NULL
#   ifdef __cplusplus
#       define NULL             (0L)
#   else
#       define NULL             ((void*) 0)
#   endif /* __cplusplus */
#endif /* NULL */

typedef void*         Any;
typedef const void*   CAny;
typedef struct darray DArray;

typedef int  (*compare_function)   (CAny a,
                                    CAny b);

typedef bool (*predicate_function) (CAny item);

/**
 * @struct darray
 *
 * The struct of arrays of arbitrary elements
 * which grow automatically as elements are added.
 */
struct darray
{
    /** The current number of elements in the DArray. */
    unsigned int current_size;
    /**
     * The maximum number of items that a DArray can hold until
     * necessary memory reallocating.
     */
    unsigned int full_size;
    /** Pointer to the underlying array serving as element storage. */
    Any          array;
    // /** Pointer to the array end. */
    // Any          array_end_ptr;
    /** The size of the element type in the DArray. */
    size_t       type_size;
}; /* struct darray */

#define TO_ANY(v)                   ((Any) &(v))
#define ANY_TO(v, t)                (*((t*) (v)))
// #define ANY_TO_INT(v)               (*((int*) (v)))

/**
 * @def d_array_data
 *
 * Returns pointer to the underlying array serving as element storage.
 *
 * @param[in]   a       a DArray.
 *
 * @return              pointer to the underlying element storage.
 */
#define d_array_data(a)             ((a)->array)

/**
 * @def d_array_size_in_byte
 *
 * Returns the length of the array in bytes.
 *
 * @param[in]   a       a DArray.
 *
 * @return              the length of the array in bytes.
 */
#define d_array_size_in_byte(a)     ((a)->full_size * (a)->type_size)

/**
 * @def d_array_at
 *
 * Returns the element of a DArray at the given index.
 * The return value is cast to the given type.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 * @param[in]   i       the index of the element to return.
 *
 * @return              the element of the DArray at the index given by i.
 */
#define d_array_at(a, t, i)         (((t*) (Any) d_array_data(a))[(i)])

/**
 * @def d_array_front
 *
 * Returns the first element in the container.
 * Calling front on an empty DArray is undefined.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 *
 * @return              the first element in the DArray.
 */
#define d_array_front(a, t)         (((t*) (Any) d_array_data(a))[0])

/**
 * @def d_array_back
 *
 * Returns the last element in the container.
 * Calling back on an empty DArray is undefined.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 *
 * @return              the last element in the DArray.
 */
#define d_array_back(a, t)          (((t*) (Any) \
                                     d_array_data(a))[d_array_length(a)-1])

/**
 * @def d_array_type_size
 *
 * Returns the size of the element type in the DArray.
 *
 * @param[in]   a       a DArray.
 *
 * @return              the element type in the DArray.
 */
#define d_array_type_size(a, i)     ((a)->type_size * (i))


#define d_array_first(a)            (d_array_data(a) + d_array_type_size(a, 1))
#define d_array_end(a, i)           (d_array_data(a) + d_array_type_size(a, i))

/**
 * @def d_array_length
 *
 * Returns the number of elements in the DArray.
 *
 * @param[in]   a       a DArray.
 *
 * @return              the count of elements in the DArray.
 */
#define d_array_length(a)           ((a)->current_size)

/**
 * @def d_array_is_empty
 *
 * Checks if the container has no elements.
 *
 * @param[in]   a       a DArray.
 *
 * @return              true if the DArray is empty, false otherwise.
 */
#define d_array_is_empty(a)         (d_array_length(a) ? false : true)

/**
 * @def d_array_length_with_reserve
 *
 * Returns the maximum number of items that a DArray can hold until
 * necessary memory reallocating.
 *
 * @param[in]   a       a DArray.
 *
 * @return              the maximum number of items in the DArray.
 */
#define d_array_length_with_reserve(a) ((a)->full_size)

/**
 * @def d_array_get_type_size
 *
 * Returns the size of the element type in the DArray from struct.
 *
 * @param[in]   a       a DArray.
 *
 * @return              the element type in the DArray from struct.
 */
#define d_array_get_type_size(a)    ((a)->type_size)

/**
 * @def d_array_fill
 *
 * Assigns the given value value to all elements in the DArray.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 * @param[in]   v       the value to assign to the elements.
 */
#define d_array_fill(a, t, v) do {                                          \
    d_array_resize(a, d_array_length_with_reserve(a));                      \
    for (unsigned int i = 0; i < d_array_length(a); i++)                    \
        d_array_at(a, t, i) = (t) (v);                                      \
} while(0)

/**
 * @def d_array_shrink_to_fit
 *
 * Requests the DArray to reduce its capacity to fit its size.
 *
 * @param[in]   a       a DArray.
 */
#define d_array_shrink_to_fit(a) do {                                       \
    (a)->full_size = (a)->current_size;                                     \
    d_array_resize(a, (a)->full_size);                                      \
} while(0)

/**
 * @def d_array_qsort
 *
 * Sorts the elements in the list, altering their position within the GArray
 * using standard qsort function.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 * @param[in]   f       the comparison function of compare_function type.
 */
#define d_array_qsort(a, t, f) do {                                         \
    qsort((a)->array, (a)->current_size, sizeof(t), f);                     \
} while(0)

/**
 * @def d_array_remove
 *
 * Removes all items that meet certain criteria.
 * Removes all items that are equal to a value.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 * @param[in]   v       value of the elements to remove.
 */
#define d_array_remove(a, t, v) do {                                        \
    for (unsigned int i = 0; i < d_array_length(a); i++)                    \
        if (d_array_at(a, t, i) == (t) v)                                   \
            d_array_remove_index(a, i);                                     \
} while(0)

/**
 * @def d_array_reverse
 *
 * Removes all items that meet certain criteria.
 * Removes all items that are equal to a value.
 *
 * @param[in]   a       a DArray.
 * @param[in]   t       the type of the elements.
 */
#define d_array_reverse(a, t) do {                                          \
    for (unsigned int i = 0; i < d_array_length(a) / 2; i++) {              \
        t tmp = d_array_at(a, t, i);                                        \
        d_array_at(a, t, i) = d_array_at(a, t, d_array_length(a) - 1 - i);  \
        d_array_at(a, t, d_array_length(a) - 1 - i) = tmp;                  \
    }                                                                       \
} while(0)

INCLUSION_GUARDS_BEGIN

DArray*
d_array_new(unsigned int count,
            size_t       type_size);

void
d_array_free(DArray* array);

DArray*
d_array_append(DArray* array,
               CAny    item);

DArray*
d_array_prepend(DArray* array,
                CAny    item);

// TO DO
DArray*
d_array_insert(DArray*      array,
               unsigned int index,
               CAny         item);

DArray*
d_array_remove_index(DArray*      array,
                     unsigned int index);

DArray*
d_array_resize(DArray*      array,
               unsigned int new_size);

// TO DO
DArray*
d_array_swap(DArray* array,
             DArray* other_array);

// TO DO
DArray*
d_array_unique(DArray* array);

// TO DO
DArray*
d_array_merge(DArray* array,
              DArray* other_array);

// TO DO
DArray*
d_array_remove_if(DArray*            array,
                  predicate_function func);

INCLUSION_GUARDS_END

#endif /* __DARRAY_H__ */
