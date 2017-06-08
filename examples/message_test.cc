#include <stdio.h>

#include "test_common.h"

int message_test_example()
{
    printf("hello world!\n");

    return 0;
}

int main() {
    TestSuite test;

    test.options.printTestMessage = true;
    test.doTest("message test example", message_test_example);

    return 0;
}

