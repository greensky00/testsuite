#include "test_common.h"

#include <string>

#include <stdio.h>

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

    // count_chk == count
    CHK_EQ(count_chk, count);
    CHK_NOT(count_chk != count);
    CHK_OK(count_chk == count);

    void *ptr = nullptr;

    // ptr == NULL
    CHK_NULL(ptr);

    char a;
    ptr = &a;

    // ptr != NULL
    CHK_NONNULL(ptr);

    int smaller = 1, greater = 2;

    // smaller < greater
    CHK_SM(smaller, greater);

    // smaller <= greater
    CHK_SMEQ(smaller, greater);

    // greater > smaller
    CHK_GT(greater, smaller);

    // greater >= smaller
    CHK_GTEQ(greater, smaller);

    int zero = 0;

    // zero == 0
    CHK_Z(zero);

    return 0;
}

int simple_args_example(int a, const std::string& b) {
    int bb = atoi(b.c_str());
    CHK_EQ(a, bb);
    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.doTest("basic test example", basic_test_example);
    test.doTest("simple arguments example", simple_args_example, 1, "1");

    return 0;
}

