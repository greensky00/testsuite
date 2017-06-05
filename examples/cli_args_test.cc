#include <stdio.h>

#include <vector>

#include "test_common.h"

struct TestData {
    enum class Type{
        ARITHMETIC,
        FIBONACCI
    };

    TestData() {
        initialize(100, Type::FIBONACCI);
    }

    TestData(Type type) {
        initialize(100, type);
    }

    void initialize(size_t n, Type type) {
        series.resize(n);

        if (type == Type::FIBONACCI) {
            series[0] = series[1] = 1;
            for (size_t i=2; i<n; ++i) {
                series[i] = series[i-1] + series[i-2];
            }
        } else {
            for (size_t i=0; i<n; ++i) {
                series[i] = i;
            }
        }
    }

    size_t getSize() { return series.size(); }

    std::vector<size_t> series;
};

int sum_odd_fibonacci()
{
    TestData data(TestData::Type::FIBONACCI);
    size_t num = data.getSize();
    uint64_t sum = 0;

    for (size_t i=1; i<num; i+=2) {
        sum += data.series[i];
    }

    return 0;
}

int sum_even_fibonacci()
{
    TestData data(TestData::Type::FIBONACCI);
    size_t num = data.getSize();
    uint64_t sum = 0;

    for (size_t i=0; i<num; i+=2) {
        sum += data.series[i];
    }

    return 0;
}

int sum_odd_arithmetic()
{
    TestData data(TestData::Type::ARITHMETIC);
    size_t num = data.getSize();
    uint64_t sum = 0;

    for (size_t i=1; i<num; i+=2) {
        sum += data.series[i];
    }

    return 0;
}

int sum_even_arithmetic()
{
    TestData data(TestData::Type::ARITHMETIC);
    size_t num = data.getSize();
    uint64_t sum = 0;

    for (size_t i=0; i<num; i+=2) {
        sum += data.series[i];
    }

    return 0;
}


int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.doTest("sum odd numbers fibonacci", sum_odd_fibonacci);
    test.doTest("sum even numbers fibonacci", sum_even_fibonacci);
    test.doTest("sum odd numbers arithmetic", sum_odd_arithmetic);
    test.doTest("sum even numbers arithmetic", sum_even_arithmetic);

    return 0;
}

