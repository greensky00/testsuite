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
                // uint16_t array 'array_u16l' {1, 2}
                uint16_t, array_u16, ({1, 2}),
                // linearly increasing uint32_t value 'arg_l_u32',
                // where 1 <= 'arg_l_u32' <= 5, step 1: 1, 2, 3, 4, 5.
                uint32_t, arg_l_u32, (1, 5, 1, StepType::LINEAR),
                // exponentially increasing uint64_t value 'arg_e_u64',
                // where 2 <= 'arg_e_u64' <= 20, multiplying by 2: 2, 4, 8, 16.
                uint64_t, arg_e_u64, (2, 20, 2, StepType::EXPONENTIAL) );

int triple_args_test(PARAM_BASE) {
    GET_PARAMS(my_triple_args);
    uint64_t mtp = my_triple_args->array_u16
                   * my_triple_args->arg_l_u32
                   * my_triple_args->arg_e_u64;
    CHK_SMEQ(mtp, 160);
    CHK_GTEQ(mtp, 2);

    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

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

