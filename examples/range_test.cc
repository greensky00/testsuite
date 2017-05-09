#include <stdio.h>

#include "test_common.h"

int range_test_example(size_t arg) {
    CHK_SM(arg, 5);
    CHK_SMEQ(arg, 4);
    CHK_GT(arg, 0);
    CHK_GTEQ(arg, 1);
    return 0;
}

int main() {
    TestSuite test;

    test.doTest("range test example",
                range_test_example,
                TestRange<size_t>(1, 4, 1));

    return 0;
}

