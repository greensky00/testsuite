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

int main() {
    TestSuite test;

    test.doTest("basic test example", basic_test_example);

    return 0;
}

