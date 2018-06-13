#include <stdlib.h>
#include <string.h>

#include "darray.h"


/**
 * Reallocs the array, expanding it if necessary.
 *
 * @param[in]   array         Array for realloc.
 * @param[in]   multiplier    The multiplier of the new DArray size.
 *
 * @return      DArrayThe     DArray.
 */
static DArray*
d_array_realloc(DArray*      array,
                unsigned int multiplier);

/**
 * Checks the array, expanding it if necessary.
 *
 * @param[in]   array       Array for realloc.
 */
static inline void
realloc_check(DArray* array)
{
    if ((array->current_size + 1) >= array->full_size)
        d_array_realloc(array, 2);
}

/**
 * Creates a new DArray.
 *
 * @param[in]   size        Size of new array.
 * @param[in]   type_size   The size of the type for each element of the array.
 *
 * @return      DArray      The new DArray.
 */
DArray*
d_array_new(unsigned int size,
            size_t       type_size)
{
    DArray* new_array = malloc(sizeof(DArray));
    new_array->current_size = 0;
    new_array->type_size = type_size;
    new_array->full_size = (size ? size : 4);
    new_array->array = calloc(size, sizeof(type_size));

    return (DArray*) new_array;
}

/**
 * Cleanup function. Frees the memory allocated for the DArray.
 *
 * @param[in]   array       The array for cleaning.
 */
void
d_array_free(DArray* array)
{
    free(array->array);
    free(array);
}

/**
 * Adds the value on to the end of the array. The array will grow in size automatically if necessary.
 *
 * @param[in]   array       Array to add.
 * @param[in]   item        The value to append to the DArray.
 *
 * @return      DArray      The new DArray.
 */
DArray*
d_array_append(DArray* array,
               CAny    item)
{
    realloc_check(array);

    memcpy(d_array_end(array, array->current_size),
           item,
           d_array_type_size(array, 1));

    array->current_size++;

    return (DArray*) array;
}

// DArray*
// d_array_prepend(DArray* array,
//                 CAny    item)
// {
//     realloc_check(array);
//
//     memcpy(d_array_first(array),
//            array->array,
//            d_array_type_size(array, array->current_size));
//     array->array[0] = item;
//     array->current_size++;
//
//     return (DArray*) array;
// }

static DArray*
d_array_realloc(DArray*      array,
                unsigned int multiplier)
{
    array->full_size *= multiplier;
    unsigned int new_full_size = array->full_size * array->type_size;
    array->array = realloc(array->array, new_full_size);

    return (DArray*) array;
}

/**
 * Resizes the size of the array, expanding it if necessary.
 *
 * @param[in]   array       Array for resizing.
 * @param[in]   new_size    The new size of the DArray.
 *
 * @return      DArray      The new DArray.
 */
DArray*
d_array_resize(DArray*      array,
               unsigned int new_size)
{
    array->full_size = new_size;
    array->current_size = new_size;
    array = d_array_realloc(array, 1);

    return (DArray*) array;
}
