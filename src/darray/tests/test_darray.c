#include <stdbool.h>
#include <check.h>

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

START_TEST(test_darray_append)
{
    int number = 42;
    darray = d_array_append(darray, TO_ANY(number));
    int test = d_array_at(darray, int, 0);
    ck_assert_int_eq(test, number);
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
    tcase_add_test(tc_functions, test_darray_append);
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
    tcase_add_test(tc_macroses, test_darray_d_array_get_type_size);
    tcase_add_test(tc_macroses, test_darray_d_array_fill);
    tcase_add_test(tc_macroses, test_darray_d_array_shrink_to_fit);
    tcase_add_test(tc_macroses, test_darray_d_array_is_empty);

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