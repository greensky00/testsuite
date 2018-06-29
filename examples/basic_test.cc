#include "test_common.h"

#include <string>

int basic_test_example() {
    int count = 0;
    for (int i=0; i<10; ++i) {
        count += i;
    }

    int count_chk = 0;
    for (int i=9; i>=0; --i) {
        count_chk += i;
    }

    // count_chk == count
    CHK_EQ(count_chk, count);

    CHK_NEQ(count_chk+1, count);

    CHK_NOT(count_chk != count);
    CHK_FALSE(count_chk != count);

    CHK_OK(count_chk == count);
    CHK_TRUE(count_chk == count);

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

int test_directory_example() {
    std::string path;

    // Auto generate path name, and store it in `path`.
    TEST_SUITE_PREPARE_PATH(path);

    TestSuite::mkdir(path);

    // It will delete the directory.
    // `-p` option will prevent removing it, for debugging purpose.
    TEST_SUITE_CLEANUP_PATH();
    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.doTest("basic test example", basic_test_example);
    test.doTest("simple arguments example", simple_args_example, 1, "1");
    test.doTest("test directory example", test_directory_example);

    return 0;
}

