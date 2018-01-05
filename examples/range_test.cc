#include <stdio.h>

#include "test_common.h"

int range_test_example(size_t arg) {
    CHK_SM(arg, 8);
    CHK_SMEQ(arg, 7);
    CHK_GT(arg, 0);
    CHK_GTEQ(arg, 1);
    return 0;
}

int main() {
    TestSuite test;

    test.doTest("range test example, linear step",
                range_test_example,
                // linearly increasing size_t value,
                // where 1 <= value <= 8, step 2: 1, 3, 5, 7.
                TestRange<size_t>(1, 8, 2, StepType::LINEAR) );

    test.doTest("range test example, array",
                range_test_example,
                // value: {1, 3, 5, 7}.
                TestRange<size_t>( {1, 3, 5, 7} ) );

    return 0;
}

