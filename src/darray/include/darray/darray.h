#ifndef __DARRAY_H__
#define __DARRAY_H__

#include <stdbool.h>

typedef void*         Any;
typedef const void*   CAny;
typedef struct darray DArray;

typedef int (*compare_function) (CAny a,
                                 CAny b);

struct darray
{
    unsigned int current_size;
    unsigned int full_size;
    Any          array;
    size_t       type_size;
};

#define TO_ANY(v)                   ((Any) &(v))
#define ANY_TO(v, t)                (*((t*) (v)))
// #define ANY_TO_INT(v)               (*((int*) (v)))
#define d_array_data(a)             ((a)->array)
#define d_array_size_in_byte(a)     ((a)->full_size * (a)->type_size)
#define d_array_at(a, t, i)         (((t*) (Any) d_array_data(a))[(i)])
#define d_array_front(a, t)         (((t*) (Any) d_array_data(a))[0])
#define d_array_back(a, t)          (((t*) (Any) \
                                     d_array_data(a))[d_array_length(a)-1])
#define d_array_type_size(a, i)     ((a)->type_size * (i))
#define d_array_first(a)            (d_array_data(a) + d_array_type_size(a, 1))
#define d_array_end(a, i)           (d_array_data(a) + d_array_type_size(a, i))
#define d_array_length(a)           ((a)->current_size)
#define d_array_is_empty(a)         (d_array_length(a) ? false : true)
#define d_array_length_with_reserve(a) ((a)->full_size)
#define d_array_get_type_size(a)    ((a)->type_size)

#define d_array_fill(a, t, v) do {                      \
    d_array_resize(a, d_array_length_with_reserve(a));  \
    for (int i = 0; i < d_array_length(a); i++)         \
        d_array_at(a, t, i) = (t) (v);                  \
} while(0)

#define d_array_shrink_to_fit(a) do {   \
    (a)->full_size = (a)->current_size; \
    d_array_resize(a, (a)->full_size);  \
} while(0)

DArray*
d_array_new(unsigned int count,
            size_t       type_size);

void
d_array_free(DArray* array);

DArray*
d_array_append(DArray* array,
               CAny    item);

// TO DO
DArray*
d_array_prepend(DArray* array,
                CAny    item);

// TO DO
DArray*
d_array_insert(DArray*      array,
               unsigned int index,
               CAny         item,
               unsigned int length);

// TO DO
DArray*
d_array_remove_index(DArray*      array,
                     unsigned int index);

DArray*
d_array_resize(DArray*      array,
               unsigned int new_size);

// TO DO
void
d_array_sort(DArray*          array,
             compare_function func);

#endif
