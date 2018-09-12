#include <check.h>
#include <stdlib.h>

#include "darray.h"


DArray* darray;

void setup()
{
    darray = d_array_new(5, sizeof(int));
}

void teardown()
{
    d_array_free(darray);
}

START_TEST(test_darray_creation)
{
    ck_assert_ptr_ne(darray, NULL);
}
END_TEST

START_TEST(test_d_array_append)
{
    int number = 42;

    darray = d_array_append(darray, NULL);
    darray = d_array_append(darray, TO_ANY(number));

    int test = d_array_at(darray, int, 0);
    ck_assert_int_eq(test, number);
}
END_TEST

START_TEST(test_d_array_prepend_if_empty)
{
    int number = 42;

    darray = d_array_prepend(darray, TO_ANY(number));

    int test = d_array_at(darray, int, 0);
    ck_assert_int_eq(test, number);
}
END_TEST

START_TEST(test_d_array_prepend)
{
    int number1 = 42;
    int number2 = 1;

    darray = d_array_append(darray, TO_ANY(number1));
    darray = d_array_prepend(darray, TO_ANY(number2));

    int test = d_array_at(darray, int, 0);
    ck_assert_int_eq(test, number2);
}
END_TEST

START_TEST(test_d_array_remove_index)
{
    int number1 = 1;
    int number2 = 2;
    int number3 = 3;
    int number4 = 4;

    darray = d_array_append(darray, TO_ANY(number1));
    darray = d_array_append(darray, TO_ANY(number2));
    darray = d_array_append(darray, TO_ANY(number3));
    darray = d_array_append(darray, TO_ANY(number4));

    d_array_remove_index(darray, 2);
    ck_assert_int_eq(d_array_length(darray), 3);

    // for (int i = 0; i < d_array_length(darray); i++)
    ck_assert_int_eq(d_array_at(darray, int, 0), 1);
    ck_assert_int_eq(d_array_at(darray, int, 1), 2);
    ck_assert_int_eq(d_array_at(darray, int, 2), 4);
}
END_TEST

START_TEST(test_darray_d_array_data)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    int* int_array = d_array_data(darray);

    ck_assert_int_eq(int_array[0], 0);
    ck_assert_int_eq(int_array[1], 1);
    ck_assert_int_eq(int_array[2], 2);
}
END_TEST

START_TEST(test_darray_d_array_size_in_byte)
{
    for (int i = 0; i < 6; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_size_in_byte(darray), 40);
}
END_TEST

START_TEST(test_darray_d_array_at)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_at(darray, int, 0), 0);
    ck_assert_int_eq(d_array_at(darray, int, 1), 1);
    ck_assert_int_eq(d_array_at(darray, int, 2), 2);
}
END_TEST

START_TEST(test_darray_d_array_front)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_at(darray, int, 0), 0);
    ck_assert_int_eq(d_array_front(darray, int), 0);
}
END_TEST

START_TEST(test_darray_d_array_back)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_at(darray, int, 2), 2);
    ck_assert_int_eq(d_array_back(darray, int), 2);
}
END_TEST

START_TEST(test_darray_d_array_length)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_length(darray), 3);
}
END_TEST

START_TEST(test_darray_d_array_length_with_reserve)
{
    ck_assert_int_eq(d_array_length_with_reserve(darray), 5);
}
END_TEST

START_TEST(test_darray_d_array_get_type_size)
{
    DArray* darray1 = d_array_new(5, sizeof(char));
    DArray* darray2 = d_array_new(5, sizeof(int));
    DArray* darray3 = d_array_new(5, sizeof(double));

    ck_assert_int_eq(d_array_get_type_size(darray1), sizeof(char));
    ck_assert_int_eq(d_array_get_type_size(darray2), sizeof(int));
    ck_assert_int_eq(d_array_get_type_size(darray3), sizeof(double));

    d_array_free(darray1);
    d_array_free(darray2);
    d_array_free(darray3);
}
END_TEST

START_TEST(test_darray_d_array_fill)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    d_array_fill(darray, int, 42);

    for (int i = 0; i < 3; i++)
        ck_assert_int_eq(d_array_at(darray, int, i), 42);
}
END_TEST

START_TEST(test_darray_d_array_shrink_to_fit)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert_int_eq(d_array_length_with_reserve(darray), 5);

    d_array_shrink_to_fit(darray);
    ck_assert_int_eq(d_array_length_with_reserve(darray), 3);
}
END_TEST

START_TEST(test_darray_d_array_remove)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    d_array_remove(darray, int, 1);
    ck_assert_int_eq(d_array_at(darray, int, 0), 0);
    ck_assert_int_eq(d_array_at(darray, int, 1), 2);
}
END_TEST

START_TEST(test_darray_d_array_reverse)
{
    for (int i = 0; i < 10; i++)
        darray = d_array_append(darray, TO_ANY(i));

    d_array_reverse(darray, int);

    ck_assert_int_eq(d_array_at(darray, int, 0), 9);
    ck_assert_int_eq(d_array_at(darray, int, 1), 8);

    DArray* ar = d_array_new(5, sizeof(char));

    char ch1 = 'a';
    char ch2 = 'b';

    ar = d_array_append(ar, TO_ANY(ch1));
    ar = d_array_append(ar, TO_ANY(ch2));

    d_array_reverse(ar, char);

    ck_assert_int_eq(d_array_at(ar, char, 0), 'b');
    ck_assert_int_eq(d_array_at(ar, char, 1), 'a');
}
END_TEST

int
cmp_function_with_int(CAny a,
                      CAny b)
{
    return ( *(int*)a - *(int*)b );
}

START_TEST(test_darray_d_array_sort_with_int)
{
    int number1 = 88;
    int number2 = 56;
    int number3 = 100;
    int number4 = 2;
    int number5 = 25;

    darray = d_array_append(darray, TO_ANY(number1));
    darray = d_array_append(darray, TO_ANY(number2));
    darray = d_array_append(darray, TO_ANY(number3));
    darray = d_array_append(darray, TO_ANY(number4));
    darray = d_array_append(darray, TO_ANY(number5));

    d_array_qsort(darray, int, cmp_function_with_int);
    ck_assert_int_eq(d_array_at(darray, int, 0), 2);
    ck_assert_int_eq(d_array_at(darray, int, 1), 25);
    ck_assert_int_eq(d_array_at(darray, int, 2), 56);
    ck_assert_int_eq(d_array_at(darray, int, 3), 88);
    ck_assert_int_eq(d_array_at(darray, int, 4), 100);
}
END_TEST

int
cmp_function_with_char(CAny a,
                       CAny b)
{
    return *(char*)a - *(char*)b;
}

START_TEST(test_darray_d_array_sort_with_char)
{
    int char1 = 'c';
    int char2 = 'd';
    int char3 = 'a';
    int char4 = 'b';
    int char5 = 'e';

    darray = d_array_append(darray, TO_ANY(char1));
    darray = d_array_append(darray, TO_ANY(char2));
    darray = d_array_append(darray, TO_ANY(char3));
    darray = d_array_append(darray, TO_ANY(char4));
    darray = d_array_append(darray, TO_ANY(char5));

    d_array_qsort(darray, int, cmp_function_with_char);
    ck_assert_int_eq(d_array_at(darray, int, 0), 'a');
    ck_assert_int_eq(d_array_at(darray, int, 1), 'b');
    ck_assert_int_eq(d_array_at(darray, int, 2), 'c');
    ck_assert_int_eq(d_array_at(darray, int, 3), 'd');
    ck_assert_int_eq(d_array_at(darray, int, 4), 'e');
}
END_TEST

START_TEST(test_darray_d_array_is_empty)
{
    for (int i = 0; i < 3; i++)
        darray = d_array_append(darray, TO_ANY(i));

    ck_assert(!d_array_is_empty(darray));
}
END_TEST

Suite*
darray_suite()
{
    Suite* suite = suite_create("darray");

    // Creation test
    TCase* tc_creation = tcase_create("Creation");
    tcase_add_checked_fixture(tc_creation, setup, teardown);
    tcase_add_test(tc_creation, test_darray_creation);
    suite_add_tcase(suite, tc_creation);

    // Functions tests
    TCase* tc_functions = tcase_create("Functions");
    tcase_add_checked_fixture(tc_functions, setup, teardown);
    tcase_add_test(tc_functions, test_d_array_append);
    tcase_add_test(tc_functions, test_d_array_prepend_if_empty);
    tcase_add_test(tc_functions, test_d_array_prepend);
    tcase_add_test(tc_functions, test_d_array_remove_index);
    suite_add_tcase(suite, tc_functions);

    // Macroses tests
    TCase* tc_macroses = tcase_create("Macroses");
    tcase_add_checked_fixture(tc_macroses, setup, teardown);

    tcase_add_test(tc_macroses, test_darray_d_array_data);
    tcase_add_test(tc_macroses, test_darray_d_array_size_in_byte);
    tcase_add_test(tc_macroses, test_darray_d_array_at);
    tcase_add_test(tc_macroses, test_darray_d_array_front);
    tcase_add_test(tc_macroses, test_darray_d_array_back);
    tcase_add_test(tc_macroses, test_darray_d_array_length);
    tcase_add_test(tc_macroses, test_darray_d_array_is_empty);
    tcase_add_test(tc_macroses, test_darray_d_array_length_with_reserve);
    tcase_add_test(tc_macroses, test_darray_d_array_get_type_size);
    tcase_add_test(tc_macroses, test_darray_d_array_fill);
    tcase_add_test(tc_macroses, test_darray_d_array_shrink_to_fit);
    tcase_add_test(tc_macroses, test_darray_d_array_remove);
    tcase_add_test(tc_macroses, test_darray_d_array_reverse);
    tcase_add_test(tc_macroses, test_darray_d_array_sort_with_int);
    tcase_add_test(tc_macroses, test_darray_d_array_sort_with_char);

    suite_add_tcase(suite, tc_macroses);

    return suite;
}

int main()
{
    Suite* suite = darray_suite();
    SRunner* runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    int number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}
