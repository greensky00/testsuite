#include "test_common.h"

int message_test_example()
{
    TestSuite::_msg("hello world!\n");

    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.options.printTestMessage = true;
    test.doTest("message test example", message_test_example);

    return 0;
}

