#include <stdio.h>
#include <stdlib.h>

#include "darray.h"


int main(int argc, char const *argv[])
{
    DArray* darray = d_array_new(5, sizeof(int));


    DArray* darray2 = d_array_new(20, sizeof(char*));

    char* add = "testing";
    darray2 = d_array_append(darray2, TO_ANY(add));
    char* t = d_array_at(darray2, char*, 0);
    printf("---%s---\n", t);



    // printf("%d\n", darray->array[0]);
    for (int i = 0; i < 5; i++) {
        darray = d_array_append(darray, TO_ANY(i));
        // printf("%d\n", d_array_at(darray, int, i));
    }
    printf("full size before: %d\n", d_array_length_with_reserve(darray));
    d_array_shrink_to_fit(darray);
    printf("full size after: %d\n", d_array_length_with_reserve(darray));

    for (int i = 0; i < 12; i++) {
        // darray = d_array_append(darray, TO_ANY(i));
        printf("%d\n", d_array_at(darray, int, i));
    }
    //
    // // d_array_at(darray, int, 0) ;
    d_array_fill(darray2, char*, "|");
    // d_array_resize(darray, d_array_length_with_reserve(darray));
    // for (int i = 0; i < d_array_length(darray); i++)
    //     d_array_at(darray, int, i) = 2;

    printf("size: %d\n", d_array_length(darray));

    for (int i = 0; i < d_array_length(darray2); i++) {
        // darray = d_array_append(darray, INT_TO_ANY(i));

        printf("%d - %s\n", i, d_array_at(darray2, char*, i));
    }
    //
    // printf("length: %d length_with_reserve: %d\n",
    //        d_array_length(darray),
    //        d_array_length_with_reserve(darray));
    //
    // d_array_shrink_to_fit(darray);
    // printf("\nAfter d_array_shrink_to_fit:\n"
    //        "length: %d length_with_reserve: %d\n",
    //        d_array_length(darray),
    //        d_array_length_with_reserve(darray));
    //
    //
    // d_array_resize(darray, 5);
    //
    // for (int i = 0; i < d_array_length(darray); i++) {
    //     printf("%d\n", d_array_at(darray, int, i));
    // }
    //
    // // int num = 42;
    // // darray = d_array_append(darray, &num);
    // d_array_at(darray, int, 11) = 42;
    //
    printf("Is empty? %d\n", d_array_is_empty(darray2));
    printf("front: %s\n"
           "back:  %s\n",
           d_array_front(darray2, char*), d_array_back(darray2, char*));



    // DArray* array = d_array_append(array, 10);
    // int a = 5;
    // Any ap= INT_TO_ANY(a);
    // int r = ANY_TO_INT(ap);
    // printf("%d\n", r);
    d_array_free(darray);
    d_array_free(darray2);
}
