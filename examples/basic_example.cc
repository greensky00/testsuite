#include <stdio.h>

#include "test_common.h"

int basic_test_example()
{
    int count = 0;
    int i = 0;

    for (i=0; i<10; ++i) {
        count += i;
    }

    int count_chk = 0;
    for (i=9; i>=0; --i) {
        count_chk += i;
    }

    CHK_EQ(count_chk, count);
    CHK_NOT(count_chk != count);
    CHK_OK(count_chk == count);

    void *ptr = nullptr;
    CHK_NULL(ptr);

    char a;
    ptr = &a;
    CHK_NONNULL(ptr);

    return 0;
}

int range_test_example(size_t arg) {
    CHK_SM(arg, 5);
    CHK_SMEQ(arg, 4);
    CHK_GT(arg, 0);
    CHK_GTEQ(arg, 1);
    return 0;
}


DEFINE_PARAMS_2(my_dual_args,
                bool, arg_bool, ({false, true}),
                int,  arg_int,  ({32, 64, 128, 256}) );

int dual_args_test(PARAM_BASE) {
    GET_PARAMS(my_dual_args);
    if (my_dual_args->arg_bool) {
        CHK_GTEQ(my_dual_args->arg_int, 32);
    } else {
        CHK_SMEQ(my_dual_args->arg_int, 256);
    }
    return 0;
}


DEFINE_PARAMS_3(my_triple_args,
                uint16_t, array_val, ({1, 2}),
                uint32_t, linear,    (1, 5, 1),
                uint64_t, exp,       (2, 16, 2, StepType::EXPONENTIAL) );

int triple_args_test(PARAM_BASE) {
    GET_PARAMS(my_triple_args);
    uint64_t mtp = my_triple_args->array_val
                   * my_triple_args->linear
                   * my_triple_args->exp;
    CHK_SMEQ(mtp, 160);
    CHK_GTEQ(mtp, 2);

    return 0;
}

int main() {
    TestSuite test;

    test.doTest("basic test example", basic_test_example);

    test.doTest("range test example",
                range_test_example,
                TestRange<size_t>(1, 4, 1));

    SET_PARAMS(my_dual_args);
    test.doTest("dual arguments test example",
                dual_args_test,
                my_dual_args);

    SET_PARAMS(my_triple_args);
    test.doTest("triple arguments test example",
                triple_args_test,
                my_triple_args);

    return 0;
}

