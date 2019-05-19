#include "test_common.h"

#include <atomic>
#include <string>

struct MyArgs : TestSuite::ThreadArgs {
    MyArgs() : durationSec(1), stopSignal(false) {}

    int durationSec;
    std::atomic<bool> stopSignal;
};

int example_thread(TestSuite::ThreadArgs* _args) {
    MyArgs* args = static_cast<MyArgs*>(_args);
    TestSuite::Timer timer;
    timer.resetSec(args->durationSec);
    do {
        TestSuite::sleep_ms(1);
    } while ( !(timer.timeover() || args->stopSignal) );
    return 0;
}

void test_fail_handler(TestSuite::ThreadArgs* _args) {
    MyArgs* args = static_cast<MyArgs*>(_args);
    args->stopSignal = true;
}

int thread_holder_wait_example() {
    MyArgs args;
    TestSuite::ThreadHolder holder(&args, example_thread, test_fail_handler);

    holder.join();
    CHK_Z(holder.getResult());

    return 0;
}

int thread_holder_fail_example() {
    MyArgs args;
    TestSuite::ThreadHolder holder(&args, example_thread, test_fail_handler);

    // Main thread will fail here, thread should be stopped immediately.
    TestSuite::setInfo("This is an intentional failure.");
    CHK_Z(1);

    holder.join();
    CHK_Z(holder.getResult());

    return 0;
}

int main(int argc, char** argv) {
    TestSuite test(argc, argv);

    test.doTest("thread holder successful wait example", thread_holder_wait_example);
    test.doTest("thread holder failure example", thread_holder_fail_example);

    return 0;
}

