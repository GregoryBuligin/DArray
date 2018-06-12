#include <stdlib.h>
#include <string.h>

#include "darray.h"


static DArray*
d_array_realloc(DArray*      array,
                unsigned int multiplier);

static inline void
realloc_check(DArray* array)
{
    if ((array->current_size + 1) >= array->full_size)
        d_array_realloc(array, 2);
}

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

void
d_array_free(DArray* array)
{
    free(array->array);
    free(array);
}

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

DArray*
d_array_resize(DArray*      array,
               unsigned int new_size)
{
    array->full_size = new_size;
    array->current_size = new_size;
    array = d_array_realloc(array, 1);

    return (DArray*) array;
}
