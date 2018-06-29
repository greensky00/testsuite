#include "test_common.h"

#include <atomic>
#include <string>

int progress_example() {
    TestSuite::Timer timer;
    timer.resetSec(1);

    TestSuite::Progress progress(1000, "Elapsed time", "ms");
    while (!timer.timeover()) {
        progress.update(timer.getTimeMs());
    }
    progress.done();
    return 0;
}

int unknown_progress_example() {
    TestSuite::Timer timer;
    timer.resetSec(1);

    TestSuite::UnknownProgress progress("Elapsed time", "ms");
    while (!timer.timeover()) {
        progress.update(timer.getTimeMs());
    }
    progress.done();
    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.options.printTestMessage = true;
    test.doTest("progress example", progress_example);
    test.doTest("unknown progress example", unknown_progress_example);

    return 0;
}

