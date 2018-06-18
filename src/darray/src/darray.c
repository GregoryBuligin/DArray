#include <stdlib.h>
#include <string.h>

#include "darray.h"


/**
 * Reallocs the array, expanding it if necessary.
 *
 * @param[in]   array         a DArray.
 * @param[in]   multiplier    the multiplier of the new DArray size.
 *
 * @return      DArray        the DArray.
 */
static DArray*
_d_array_realloc(DArray*      array,
                unsigned int multiplier);

/**
 * Checks the array, expanding it if necessary.
 *
 * @param[in]   array       a DArray.
 */
static inline void
_realloc_check(DArray* array)
{
    if ((array->current_size + 1) >= array->full_size)
        _d_array_realloc(array, 2);
}

/**
 * Creates a new DArray.
 *
 * @param[in]   size        a size of new array.
 * @param[in]   type_size   the size of the type for each element of the array.
 *
 * @return      DArray      the new DArray.
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
 * @param[in]   array       a DArray.
 */
void
d_array_free(DArray* array)
{
    free(array->array);

    array->current_size = 0;
    array->full_size = 0;
    array->array = NULL;
    array->type_size = 0;

    free(array);
}

/**
 * Adds the value on to the end of the array. The array will grow in size automatically if necessary.
 *
 * @param[in]   array       a DArray.
 * @param[in]   item        the value to append to the DArray.
 *
 * @return      DArray      the DArray.
 */
DArray*
d_array_append(DArray* array,
               CAny    item)
{
    if (array == NULL) {
        perror("In d_array_append: DArray is NULL");
        return (DArray*) NULL;
    }

    _realloc_check(array);

    if (item == NULL)
        return (DArray*) array;

    memcpy(d_array_end(array, array->current_size),
           item,
           d_array_type_size(array, 1));

    array->current_size++;

    return (DArray*) array;
}

/**
 * Adds the value on to the start of the array.
 * The array will grow in size automatically if necessary.
 *
 * @param[in]   array       a DArray.
 * @param[in]   item        the value to prepend to the DArray.
 *
 * @return      DArray      the DArray.
 */
DArray*
d_array_prepend(DArray* array,
                CAny    item)
{
    if (array == NULL) {
        perror("In d_array_prepend: DArray is NULL");
        return (DArray*) NULL;
    }

    _realloc_check(array);

    if (d_array_is_empty(array))
        return d_array_append(array, item);

    if (item == NULL)
        return (DArray*) array;

    memmove(d_array_end(array, array->current_size),
            d_array_data(array),
            d_array_type_size(array, array->current_size));

    memcpy(d_array_end(array, 0),
           item,
           d_array_type_size(array, array->current_size));

    array->current_size++;

    return (DArray*) array;
}

/**
 * Removes the element at the given index from a DArray. The following elements are moved down one place.
 *
 * @param[in]   array       a DArray.
 * @param[in]   index       the index to place the elements at.
 * @param[in]   item        the value to insert.
 *
 * @return      DArray      the DArray.
 */
DArray*
d_array_insert(DArray*      array,
               unsigned int index,
               CAny         item)
{
    return (DArray*) array;
}

/**
 * Removes the element at the given index from a DArray. The following elements are moved down one place.
 *
 * @param[in]   array       a DArray.
 * @param[in]   item        the index of the element to remove
 *
 * @return      DArray      the DArray.
 */
DArray*
d_array_remove_index(DArray*      array,
                     unsigned int index)
{
    if (array == NULL) {
        perror("In d_array_remove_index: DArray is NULL");
        return (DArray*) NULL;
    }

    if (index < 0)
        return (DArray*) array;

    memmove(d_array_end(array, index),
            d_array_end(array, index + 1),
            d_array_type_size(array, (array->current_size - index - 1)));

    array->current_size--;

    return (DArray*) array;
}

static DArray*
_d_array_realloc(DArray*      array,
                unsigned int multiplier)
{
    if (array == NULL) {
        perror("In _d_array_realloc: DArray is NULL");
        return (DArray*) NULL;
    }

    if (multiplier <= 0) {
        perror("In _d_array_realloc: multiplier is equial or less 0");
        return (DArray*) NULL;
    }

    array->full_size *= multiplier;
    unsigned int new_full_size = array->full_size * array->type_size;
    array->array = realloc(array->array, new_full_size);

    return (DArray*) array;
}

/**
 * Resizes the size of the array, expanding it if necessary.
 *
 * @param[in]   array       a DArray.
 * @param[in]   new_size    the new size of the DArray.
 *
 * @return      DArray      the DArray.
 */
DArray*
d_array_resize(DArray*      array,
               unsigned int new_size)
{
    if (array == NULL) {
        perror("In d_array_resize: DArray is NULL");
        return (DArray*) NULL;
    }

    array->full_size = new_size;
    array->current_size = new_size;
    array = _d_array_realloc(array, 1);

    return (DArray*) array;
}
