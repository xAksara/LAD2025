#include "buf.h"
#include <check.h>
#include <stdio.h>
#include <stdint.h>


#suite Suite1
#tcase init

#test capacity_init_test
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);

#test size_init_test
    float *a = 0;
    ck_assert_uint_eq(buf_size(a), 0);

#test size1_test
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    buf_free(a);

#test value_test
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert(a[0] == 1.3f);
    buf_free(a);

#test clear_test
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_ne(a, 0);
    buf_free(a);

#test free_test
    float *a = 0;
    buf_push(a, 1.3f);
    buf_free(a);
    ck_assert_ptr_eq(a, 0);

#test clear_empty_test
    float *a = 0;
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_eq(a, 0);



#tcase push_pop

#test size_10000_test
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_uint_eq(buf_size(ai), 10000);
    int match = 0;
    for (size_t i = 0; i < buf_size(ai); i++)
        match += (ai[i] == i);
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#test grow_trunc_test
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);
    buf_free(ai);

#test pop_test
    float *a = 0;
    buf_push(a, 1.1f);
    buf_push(a, 1.2f);
    buf_push(a, 1.3f);
    buf_push(a, 1.4f);
    ck_assert_uint_eq(buf_size(a), 4);
    ck_assert(buf_pop(a) == 1.4f);
    buf_trunc(a, 3);
    ck_assert_uint_eq(buf_size(a), 3);
    ck_assert(buf_pop(a) == 1.3f);
    ck_assert(buf_pop(a) == 1.2f);
    ck_assert(buf_pop(a) == 1.1f);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_free(a);
