#include <stdio.h>

#include "test_common.h"

// Dual-parameters example: {bool, int}.

DEFINE_PARAMS_2(my_dual_args,
                // bool array 'arg_bool' {false, true}
                bool, arg_bool, ({false, true}),
                // int array 'arg_int' {32, 64, 128, 256}
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


// Triple-parameters example: {uint16_t, uint32_t, uint64_t}.

DEFINE_PARAMS_3(my_triple_args,
                // uint16_t array 'array_val' {1, 2}
                uint16_t, array_val, ({1, 2}),
                // linearly increasing uint32_t value 'linear',
                // where 1 <= 'linear' <= 5, step 1: 1, 2, 3, 4, 5.
                uint32_t, linear,    (1, 5, 1),
                // exponentially increasing uint64_t value 'exp',
                // where 2 <= 'exp' <= 20, multiplying by 2: 2, 4, 8, 16.
                uint64_t, exp,       (2, 20, 2, StepType::EXPONENTIAL) );

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

