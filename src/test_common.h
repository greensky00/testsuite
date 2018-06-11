/**
 * Copyright (C) 2017-present Jung-Sang Ahn <jungsang.ahn@gmail.com>
 * All rights reserved.
 *
 * https://github.com/greensky00
 *
 * Test Suite
 * Version: 0.1.52
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef _CLM_DEFINED
#define _CLM_DEFINED (1)

#ifdef TESTSUITE_NO_COLOR
    #define _CLM_D_GRAY     ""
    #define _CLM_GREEN      ""
    #define _CLM_B_GREEN    ""
    #define _CLM_RED        ""
    #define _CLM_B_RED      ""
    #define _CLM_BROWN      ""
    #define _CLM_B_BROWN    ""
    #define _CLM_BLUE       ""
    #define _CLM_B_BLUE     ""
    #define _CLM_MAGENTA    ""
    #define _CLM_B_MAGENTA  ""
    #define _CLM_CYAN       ""
    #define _CLM_END        ""

    #define _CLM_WHITE_FG_RED_BG    ""
#else
    #define _CLM_D_GRAY     "\033[1;30m"
    #define _CLM_GREEN      "\033[32m"
    #define _CLM_B_GREEN    "\033[1;32m"
    #define _CLM_RED        "\033[31m"
    #define _CLM_B_RED      "\033[1;31m"
    #define _CLM_BROWN      "\033[33m"
    #define _CLM_B_BROWN    "\033[1;33m"
    #define _CLM_BLUE       "\033[34m"
    #define _CLM_B_BLUE     "\033[1;34m"
    #define _CLM_MAGENTA    "\033[35m"
    #define _CLM_B_MAGENTA  "\033[1;35m"
    #define _CLM_CYAN       "\033[36m"
    #define _CLM_B_GREY     "\033[1;37m"
    #define _CLM_END        "\033[0m"

    #define _CLM_WHITE_FG_RED_BG    "\033[37;41m"
#endif

#define _CL_D_GRAY(str)     _CLM_D_GRAY     str _CLM_END
#define _CL_GREEN(str)      _CLM_GREEN      str _CLM_END
#define _CL_RED(str)        _CLM_RED        str _CLM_END
#define _CL_B_RED(str)      _CLM_B_RED      str _CLM_END
#define _CL_MAGENTA(str)    _CLM_MAGENTA    str _CLM_END
#define _CL_BROWN(str)      _CLM_BROWN      str _CLM_END
#define _CL_B_BROWN(str)    _CLM_B_BROWN    str _CLM_END
#define _CL_B_BLUE(str)     _CLM_B_BLUE     str _CLM_END
#define _CL_B_MAGENTA(str)  _CLM_B_MAGENTA  str _CLM_END
#define _CL_CYAN(str)       _CLM_CYAN       str _CLM_END
#define _CL_B_GRAY(str)     _CLM_B_GREY     str _CLM_END

#define _CL_WHITE_FG_RED_BG(str)    _CLM_WHITE_FG_RED_BG    str _CLM_END

#endif

#define __COUT_STACK_INFO__                                                     \
       std::endl                                                                \
    << "      thread: " << _CLM_BROWN                                           \
    << std::hex << std::setw(4) << std::setfill('0') <<                         \
       (std::hash<std::thread::id>{}( std::this_thread::get_id() ) & 0xffff)    \
    << std::dec << _CLM_END << "\n"                                             \
    << "          in: " << _CLM_CYAN << __func__ << "()" _CLM_END << "\n"       \
    << "          at: " << _CLM_GREEN << __FILE__ << _CLM_END ":"               \
    << _CLM_B_MAGENTA << __LINE__ << _CLM_END << "\n"                           \

// exp_value == value
#define CHK_EQ(exp_value, value)                                        \
{                                                                       \
    auto _ev = (exp_value);                                             \
    decltype(_ev) _v = (decltype(_ev))(value);                          \
    if (_ev != _v) {                                                    \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << _ev << _CLM_END "\n"        \
        << "      actual: " _CLM_B_RED << _v << _CLM_END "\n";          \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }                                                                   \
}

// value == true
#define CHK_OK(value)                                                   \
    if (!(value)) {                                                     \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << "true" << _CLM_END "\n"     \
        << "      actual: " _CLM_B_RED << "false" << _CLM_END "\n";     \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }

// value == false
#define CHK_NOT(value)                                                  \
    if (value) {                                                        \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << "false" << _CLM_END "\n"    \
        << "      actual: " _CLM_B_RED << "true" << _CLM_END "\n";      \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }

// value == NULL
#define CHK_NULL(value)                                                 \
{                                                                       \
    auto _v = (value);                                                  \
    if (_v) {                                                           \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << "NULL" << _CLM_END "\n";    \
        printf("      actual: " _CLM_B_RED "%p" _CLM_END "\n", _v);     \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }                                                                   \
}

// value != NULL
#define CHK_NONNULL(value)                                              \
    if (!(value)) {                                                     \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << "non-NULL" << _CLM_END "\n" \
        << "      actual: " _CLM_B_RED << "NULL" << _CLM_END "\n";      \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }

// value == 0
#define CHK_Z(value)                                                    \
{                                                                       \
    auto _v = (value);                                                  \
    if ((0) != _v) {                                                    \
        std::cout                                                       \
        << __COUT_STACK_INFO__                                          \
        << "    value of: " _CLM_B_BLUE #value _CLM_END "\n"            \
        << "    expected: " _CLM_B_GREEN << "0" << _CLM_END "\n"        \
        << "      actual: " _CLM_B_RED << _v << _CLM_END "\n";          \
        TestSuite::failHandler();                                       \
        return -1;                                                      \
    }                                                                   \
}

// smaller < greater
#define CHK_SM(smaller, greater)                                \
{                                                               \
    auto _sm = (smaller);                                       \
    decltype(_sm) _gt = (decltype(_sm))(greater);               \
    if (!(_sm < _gt)) {                                         \
        std::cout                                               \
        << __COUT_STACK_INFO__                                  \
        << "    expected: "                                     \
        << _CLM_B_BLUE #smaller " < " #greater _CLM_END "\n"    \
        << "    value of "                                      \
        << _CLM_B_GREEN #smaller _CLM_END ": "                  \
        << _CLM_B_RED << _sm << _CLM_END "\n"                   \
        << "    value of "                                      \
        << _CLM_B_GREEN #greater _CLM_END ": "                  \
        << _CLM_B_RED << _gt << _CLM_END "\n";                  \
        TestSuite::failHandler();                               \
        return -1;                                              \
    }                                                           \
}

// smaller <= greater
#define CHK_SMEQ(smaller , greater)                             \
{                                                               \
    auto _sm = (smaller);                                       \
    decltype(_sm) _gt = (decltype(_sm))(greater);               \
    if (!(_sm <= _gt)) {                                        \
        std::cout                                               \
        << __COUT_STACK_INFO__                                  \
        << "    expected: "                                     \
        << _CLM_B_BLUE #smaller " <= " #greater _CLM_END "\n"   \
        << "    value of "                                      \
        << _CLM_B_GREEN #smaller _CLM_END ": "                  \
        << _CLM_B_RED << _sm << _CLM_END "\n"                   \
        << "    value of "                                      \
        << _CLM_B_GREEN #greater _CLM_END ": "                  \
        << _CLM_B_RED << _gt << _CLM_END "\n";                  \
        TestSuite::failHandler();                               \
        return -1;                                              \
    }                                                           \
}

// greater > smaller
#define CHK_GT(greater, smaller)                                \
{                                                               \
    auto _sm = (smaller);                                       \
    decltype(_sm) _gt = (decltype(_sm))(greater);               \
    if (!(_gt > _sm)) {                                         \
        std::cout                                               \
        << __COUT_STACK_INFO__                                  \
        << "    expected: "                                     \
        << _CLM_B_BLUE #greater " > " #smaller _CLM_END "\n"    \
        << "    value of "                                      \
        << _CLM_B_GREEN #greater _CLM_END ": "                  \
        << _CLM_B_RED << _gt << _CLM_END "\n"                   \
        << "    value of "                                      \
        << _CLM_B_GREEN #smaller _CLM_END ": "                  \
        << _CLM_B_RED << _sm << _CLM_END "\n";                  \
        TestSuite::failHandler();                               \
        return -1;                                              \
    }                                                           \
}

// greater >= smaller
#define CHK_GTEQ(greater, smaller)                              \
{                                                               \
    auto _sm = (smaller);                                       \
    decltype(_sm) _gt = (decltype(_sm))(greater);               \
    if (!(_gt >= _sm)) {                                        \
        std::cout                                               \
        << __COUT_STACK_INFO__                                  \
        << "    expected: "                                     \
        << _CLM_B_BLUE #greater " >= " #smaller _CLM_END "\n"   \
        << "    value of "                                      \
        << _CLM_B_GREEN #greater _CLM_END ": "                  \
        << _CLM_B_RED << _gt << _CLM_END "\n"                   \
        << "    value of "                                      \
        << _CLM_B_GREEN #smaller _CLM_END ": "                  \
        << _CLM_B_RED << _sm << _CLM_END "\n";                  \
        TestSuite::failHandler();                               \
        return -1;                                              \
    }                                                           \
}


using test_func = std::function<int()>;

class TestArgsBase;
using test_func_args = std::function<int(TestArgsBase*)>;

class TestSuite;
class TestArgsBase {
public:
    virtual ~TestArgsBase() { }
    void setCallback(std::string test_name,
                     test_func_args func,
                     TestSuite* test_instance) {
        testName = test_name;
        testFunction = func;
        testInstance = test_instance;
    }
    void testAll() { testAllInternal(0); }
    virtual void setParam(size_t param_no, size_t param_idx) = 0;
    virtual size_t getNumSteps(size_t param_no) = 0;
    virtual size_t getNumParams() = 0;
    virtual std::string toString() = 0;

private:
    inline void testAllInternal(size_t depth);
    std::string testName;
    test_func_args testFunction;
    TestSuite* testInstance;
};

class TestArgsWrapper {
public:
    TestArgsWrapper(TestArgsBase* _test_args) : test_args(_test_args) {}
    ~TestArgsWrapper() { delete test_args; }
    TestArgsBase* getArgs() const { return test_args; }
    operator TestArgsBase*() const { return getArgs(); }
private:
    TestArgsBase* test_args;
};

enum class StepType {
    LINEAR,
    EXPONENTIAL
};

template<typename T>
class TestRange {
public:
    TestRange() : type(RangeType::NONE), begin(), end(), step() {}

    // Constructor for given values
    TestRange(const std::vector<T>& _array)
        : type(RangeType::ARRAY), array(_array)
        , begin(), end(), step() {}

    // Constructor for regular steps
    TestRange(T _begin, T _end, T _step, StepType _type)
        : begin(_begin), end(_end), step(_step)
    {
        if (_type == StepType::LINEAR) {
            type = RangeType::LINEAR;
        } else {
            type = RangeType::EXPONENTIAL;
        }
    }

    T getEntry(size_t idx) {
        if (type == RangeType::ARRAY) {
            return array[idx];
        } else if (type == RangeType::LINEAR) {
            return begin + step * idx;
        } else if (type == RangeType::EXPONENTIAL) {
            ssize_t _begin = begin;
            ssize_t _step = step;
            ssize_t _ret = _begin * std::pow(_step, idx);
            return (T)(_ret);
        }

        return begin;
    }

    size_t getSteps() {
        if (type == RangeType::ARRAY) {
            return array.size();
        } else if (type == RangeType::LINEAR) {
            return ((end - begin) / step) + 1;
        } else if (type == RangeType::EXPONENTIAL) {
            ssize_t coe = ((ssize_t)end) / ((ssize_t)begin);
            double steps_double = (double)std::log(coe) / std::log(step);
            return steps_double + 1;
        }

        return 0;
    }

private:
    enum class RangeType {
        NONE,
        ARRAY,
        LINEAR,
        EXPONENTIAL
    };

    RangeType type;
    std::vector<T> array;
    T begin;
    T end;
    T step;
};

struct TestOptions {
    TestOptions()
        : printTestMessage(false)
        , abortOnFailure(false)
        , preserveTestFiles(false)
        {}
    bool printTestMessage;
    bool abortOnFailure;
    bool preserveTestFiles;
};

class TestSuite {
    friend TestArgsBase;
private:
    static std::mutex& getResMsgLock() {
        static std::mutex res_msg_lock;
        return res_msg_lock;
    }
    static std::string& getResMsg() {
        static std::string res_msg;
        return res_msg;
    }
    static std::string& getInfoMsg() {
        thread_local std::string info_msg;
        return info_msg;
    }
    static std::string& getTestName() {
        static std::string test_name;
        return test_name;
    }
    static TestSuite*& getCurTest() {
        static TestSuite* cur_test;
        return cur_test;
    }
public:
    static std::string getCurrentTestName() {
        return getTestName();
    }
    static bool isMsgAllowed() {
        TestSuite* cur_test = TestSuite::getCurTest();
        if ( cur_test &&
             (cur_test->options.printTestMessage || cur_test->displayMsg) &&
             !cur_test->suppressMsg ) {
            return true;
        }
        return false;
    }

    static void setInfo(const char* format, ...) {
        thread_local char info_buf[4096];
        size_t len = 0;
        va_list args;
        va_start(args, format);
        len += vsnprintf(info_buf + len, 4096 - len, format, args);
        va_end(args);
        getInfoMsg() = info_buf;
    }
    static void clearInfo() {
        getInfoMsg().clear();
    }

    static void failHandler() {
        if (!getInfoMsg().empty()) {
            std::cout << "        info: " << getInfoMsg() << std::endl;
        }
    }

    static void usage(int argc, char** argv) {
        printf("\n");
        printf("Usage: %s [-f <keyword>] [-r <parameter>] [-p]\n", argv[0]);
        printf("\n");
        printf("    -f, --filter\n");
        printf("        Run specific tests matching the given keyword.\n");
        printf("    -r, --range\n");
        printf("        Run TestRange-based tests using given parameter value.\n");
        printf("    -p, --preserve\n");
        printf("        Do not clean up test files.\n");
        printf("    --abort-on-failure\n");
        printf("        Immediately abort the test if failure happens.\n");
        printf("    --suppress-msg\n");
        printf("        Suppress test messages.\n");
        printf("\n");
    }

    static std::string usToString(uint64_t us) {
        std::stringstream ss;
        if (us < 1000) {
            // us
            ss << std::fixed << std::setprecision(0) << us << " us";
        } else if (us < 1000000) {
            // ms
            double tmp = static_cast<double>(us / 1000.0);
            ss << std::fixed << std::setprecision(1) << tmp << " ms";
        } else if (us < (uint64_t)600 * 1000000) {
            // second: 1 s -- 600 s (10 mins)
            double tmp = static_cast<double>(us / 1000000.0);
            ss << std::fixed << std::setprecision(1) << tmp << " s";
        } else {
            // minute
            double tmp = static_cast<double>(us / 60.0 / 1000000.0);
            ss << std::fixed << std::setprecision(0) << tmp << " m";
        }
        return ss.str();
    }

    static std::string countToString(uint64_t count) {
        std::stringstream ss;
        if (count < 1000) {
            ss << count;
        } else if (count < 1000000) {
            // K
            double tmp = static_cast<double>(count / 1000.0);
            ss << std::fixed << std::setprecision(1) << tmp << "K";
        } else if (count < (uint64_t)1000000000) {
            // M
            double tmp = static_cast<double>(count / 1000000.0);
            ss << std::fixed << std::setprecision(1) << tmp << "M";
        } else {
            // B
            double tmp = static_cast<double>(count / 1000000000.0);
            ss << std::fixed << std::setprecision(1) << tmp << "B";
        }
        return ss.str();
    }

private:
    struct TimeInfo {
        TimeInfo(std::tm* src)
            : year(src->tm_year + 1900)
            , month(src->tm_mon + 1)
            , day(src->tm_mday)
            , hour(src->tm_hour)
            , min(src->tm_min)
            , sec(src->tm_sec) {}
        int year;
        int month;
        int day;
        int hour;
        int min;
        int sec;
    };

public:
    TestSuite(int argc = 0, char **argv = nullptr)
        : cntPass(0)
        , cntFail(0)
        , useGivenRange(false)
        , preserveTestFiles(false)
        , forceAbortOnFailure(false)
        , suppressMsg(false)
        , displayMsg(false)
        , givenRange(0)
        , startTimeGlobal(std::chrono::system_clock::now())
    {
        for (int ii=1; ii<argc; ++ii) {
            // Filter.
            if ( ii < argc-1 &&
                 (!strcmp(argv[ii], "-f") ||
                  !strcmp(argv[ii], "--filter")) ) {
                filter = argv[++ii];
            }

            // Range.
            if ( ii < argc-1 &&
                 (!strcmp(argv[ii], "-r") ||
                  !strcmp(argv[ii], "--range")) ) {
                givenRange = atoi(argv[++ii]);
                useGivenRange = true;
            }

            // Do not clean up test files after test.
            if ( !strcmp(argv[ii], "-p") ||
                 !strcmp(argv[ii], "--preserve") ) {
                preserveTestFiles = true;
            }

            // Force abort on failure.
            if ( !strcmp(argv[ii], "--abort-on-failure") ) {
                forceAbortOnFailure = true;
            }

            // Suppress test messages.
            if ( !strcmp(argv[ii], "--suppress-msg") ) {
                suppressMsg = true;
            }

            // Display test messages.
            if ( !strcmp(argv[ii], "--display-msg") && !suppressMsg ) {
                displayMsg = true;
            }

            // Help
            if ( !strcmp(argv[ii], "-h") ||
                 !strcmp(argv[ii], "--help") ) {
                usage(argc, argv);
                exit(0);
            }
        }
    }

    ~TestSuite() {
        std::chrono::time_point<std::chrono::system_clock> cur_time =
                std::chrono::system_clock::now();;
        std::chrono::duration<double> elapsed = cur_time - startTimeGlobal;
        std::string time_str = usToString(elapsed.count() * 1000000);

        printf(_CL_GREEN("%zu") " tests passed", cntPass);
        if (cntFail) {
            printf(", " _CL_RED("%zu") " tests failed", cntFail);
        }
        printf(" out of " _CL_CYAN("%zu") " (" _CL_BROWN("%s") ")\n",
               cntPass+cntFail, time_str.c_str());
    }

    // === Helper functions ====================================
    static std::string getTestFileName(const std::string& prefix) {
        auto now = std::chrono::system_clock::now();
        std::time_t raw_time = std::chrono::system_clock::to_time_t(now);
        std::tm* lt_tm = std::localtime(&raw_time);
        TimeInfo lt(lt_tm);
        (void)lt;

        char time_char[64];
        sprintf(time_char, "%04d%02d%02d_%02d%02d%02d",
                lt.year, lt.month, lt.day, lt.hour, lt.min, lt.sec);

        std::string ret = prefix;
        ret += "_";
        ret += time_char;
        return ret;
    }

    static int mkdir(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) != 0) {
            return ::mkdir(path.c_str(), 0755);
        }
        return 0;
    }
    static int copyfile(const std::string& src,
                        const std::string& dst) {
        std::string cmd = "cp -R " + src + " " + dst;
        int rc = ::system(cmd.c_str());
        return rc;
    }

    enum TestPosition {
        BEGINNING_OF_TEST   = 0,
        MIDDLE_OF_TEST      = 1,
        END_OF_TEST         = 2,
    };
    static void clearTestFile( const std::string& prefix,
                               TestPosition test_pos = MIDDLE_OF_TEST ) {
        TestSuite*& cur_test = TestSuite::getCurTest();
        if ( test_pos == END_OF_TEST &&
             ( cur_test->preserveTestFiles ||
               cur_test->options.preserveTestFiles ) ) return;

        int r;
        std::string command = "rm -rf ";
        command += prefix;
        command += "*";
        r = system(command.c_str());
        (void)r;
    }

    static void setResultMessage(const std::string& msg) {
        TestSuite::getResMsg() = msg;
    }

    static void appendResultMessage(const std::string& msg) {
        std::lock_guard<std::mutex> l(TestSuite::getResMsgLock());
        TestSuite::getResMsg() += msg;
    }

    static size_t _msg(const char* format, ...) {
        size_t cur_len = 0;
        TestSuite* cur_test = TestSuite::getCurTest();
        if ( cur_test &&
             (cur_test->options.printTestMessage || cur_test->displayMsg) &&
             !cur_test->suppressMsg ) {
            va_list args;
            va_start(args, format);
            cur_len += vprintf(format, args);
            va_end(args);
        }
        return cur_len;
    }

    class Msg : public std::ostream {
    public:
        Msg() : std::ostream(&buf), buf(std::cout) {}
    private:
        class IntBuf : public std::stringbuf {
        public:
            IntBuf(std::ostream& o_stream) : oStream(o_stream) {}
            virtual int sync() {
                if (!TestSuite::isMsgAllowed()) return 0;
                oStream << str();
                oStream.flush();
                return 0;
            }
        private:
            std::ostream& oStream;
        };
        IntBuf buf;
    };

    static void sleep_us(size_t us, const std::string& msg = std::string()) {
        if (!msg.empty()) TestSuite::_msg("%s (%zu us)\n", msg.c_str(), us);
        std::this_thread::sleep_for(std::chrono::microseconds(us));
    }
    static void sleep_ms(size_t ms, const std::string& msg = std::string()) {
        if (!msg.empty()) TestSuite::_msg("%s (%zu ms)\n", msg.c_str(), ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
    static void sleep_sec(size_t sec, const std::string& msg = std::string()) {
        if (!msg.empty()) TestSuite::_msg("%s (%zu s)\n", msg.c_str(), sec);
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }
    static std::string lzStr(size_t digit, uint64_t num) {
        std::stringstream ss;
        ss << std::setw(digit) << std::setfill('0') << std::to_string(num);
        return ss.str();
    }
    static double calcThroughput(uint64_t ops, uint64_t elapsed_us) {
        return ops * 1000000.0 / elapsed_us;
    }
    static std::string throughputStr(uint64_t ops, uint64_t elapsed_us) {
        return countToString(ops * 1000000.0 / elapsed_us);
    }

    // === Timer things ====================================
    class Timer {
    public:
        Timer() : duration_ms(0) {
            reset();
        }
        Timer(size_t _duration_ms) : duration_ms(_duration_ms) {
            reset();
        }
        bool timeover() {
            auto cur = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed = cur - start;
            if (duration_ms < elapsed.count() * 1000) return true;
            return false;
        }
        uint64_t getTimeUs() {
            auto cur = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed = cur - start;
            return (uint64_t)(elapsed.count() * 1000000);
        }
        void reset() {
            start = std::chrono::system_clock::now();
        }
        void reset(size_t _duration_ms) {
            duration_ms = _duration_ms;
            reset();
        }
    private:
        std::chrono::time_point<std::chrono::system_clock> start;
        size_t duration_ms;
    };

    // === Workload generator things ====================================
    class WorkloadGenerator {
    public:
        WorkloadGenerator(double ops_per_sec = 0.0, uint64_t max_ops_per_batch = 0)
            : opsPerSec(ops_per_sec)
            , maxOpsPerBatch(max_ops_per_batch)
            , numOpsDone(0) {
            reset();
        }
        void reset() {
            start = std::chrono::system_clock::now();
            numOpsDone = 0;
        }
        size_t getNumOpsToDo() {
            if (opsPerSec <= 0) return 0;

            auto cur = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed = cur - start;

            double exp = opsPerSec * elapsed.count();
            if (numOpsDone < exp) {
                return std::min(maxOpsPerBatch, (uint64_t)exp - numOpsDone);
            }
            return 0;
        }
        void addNumOpsDone(size_t num) {
            numOpsDone += num;
        }
    private:
        std::chrono::time_point<std::chrono::system_clock> start;
        double opsPerSec;
        uint64_t maxOpsPerBatch;
        uint64_t numOpsDone;
    };

    // === Progress things ==================================
    class Progress {
    public:
        Progress(uint64_t _num,
                 const std::string& _comment = std::string(),
                 const std::string& _unit = std::string())
            : curValue(0)
            , num(_num)
            , timer(0)
            , lastPrintTimeUs(timer.getTimeUs())
            , comment(_comment)
            , unit(_unit) {}
        void update(uint64_t cur) {
            curValue = cur;
            uint64_t curTimeUs = timer.getTimeUs();
            if (curTimeUs - lastPrintTimeUs > 50000 ||
                cur == 0 || curValue >= num) {
                // Print every 0.05 sec (20 Hz).
                lastPrintTimeUs = curTimeUs;
                std::string _comment =
                    (comment.empty()) ? "" : comment + ": ";
                std::string _unit =
                    (unit.empty()) ? "" : unit + " ";

                _msg("\r%s%ld/%ld %s(%.1f%%)",
                     _comment.c_str(), curValue, num, _unit.c_str(),
                     (double)curValue*100/num);
                fflush(stdout);
            }
            if (curValue >= num) {
                _msg("\n");
                fflush(stdout);
            }
        }
        void done() { if (curValue < num) update(num); }
    private:
        uint64_t curValue;
        uint64_t num;
        Timer timer;
        uint64_t lastPrintTimeUs;
        std::string comment;
        std::string unit;
    };

    // === Displayer things ==================================
    class Displayer {
    public:
        Displayer(size_t num_raws, size_t num_cols)
            : numRaws(num_raws)
            , numCols(num_cols)
            , colWidth(num_cols, 20)
            , context(num_raws, std::vector<std::string>(num_cols)) {}
        void init() {
            for (size_t ii=0; ii<numRaws; ++ii) _msg("\n");
        }
        void setWidth(std::vector<size_t>& src) {
            size_t num_src = src.size();
            if (!num_src) return;

            for (size_t ii=0; ii<num_src; ++ii) {
                colWidth[ii] = src[ii];
            }
            for (size_t ii=num_src; ii<numCols; ++ii) {
                colWidth[ii] = src[num_src-1];
            }
        }
        void set(size_t raw_idx, size_t col_idx, const char* format, ...) {
            if (raw_idx >= numRaws || col_idx >= numCols) return;

            thread_local char info_buf[32];
            size_t len = 0;
            va_list args;
            va_start(args, format);
            len += vsnprintf(info_buf + len, 20 - len, format, args);
            va_end(args);
            context[raw_idx][col_idx] = info_buf;
        }
        void print() {
            _msg("\033[%zuA", numRaws);
            for (size_t ii=0; ii<numRaws; ++ii) {
                std::stringstream ss;
                for (size_t jj=0; jj<numCols; ++jj) {
                    ss << std::setw(colWidth[jj]) << context[ii][jj];
                }
                _msg("\r%s\n", ss.str().c_str());
            }
        }
    private:
        size_t numRaws;
        size_t numCols;
        std::vector<size_t> colWidth;
        std::vector< std::vector< std::string > > context;
    };

    // === Thread things ====================================
    struct ThreadArgs { /* Opaque. */ };
    using ThreadFunc = std::function< int(ThreadArgs*) >;
    using ThreadExitHandler = std::function< void(ThreadArgs*) >;

private:
    struct ThreadInternalArgs {
        ThreadInternalArgs() : userArgs(nullptr), func(nullptr), rc(0) {}
        ThreadArgs* userArgs;
        ThreadFunc func;
        int rc;
    };

public:
    struct ThreadHolder {
        ThreadHolder(std::thread* _tid, ThreadExitHandler _handler)
            : tid(_tid), handler(_handler) {}
        ThreadHolder(ThreadArgs* u_args,
                     ThreadFunc t_func,
                     ThreadExitHandler t_handler)
            : handler(t_handler)
        {
            args.userArgs = u_args;
            args.func = t_func;
            tid = new std::thread(spawnThread, &args);
        }
        ~ThreadHolder() {
            if (!tid) return;
            if (tid->joinable()) {
                handler(args.userArgs);
                tid->join();
            }
            delete tid;
            tid = nullptr;
        }
        void join() {
            if (!tid) return;
            if (tid->joinable()) {
                tid->join();
            }
        }
        int getResult() const { return args.rc; }
        std::thread* tid;
        ThreadExitHandler handler;
        ThreadInternalArgs args;
    };


    // === doTest things ====================================

    // 1) Without parameter.
    void doTest( const std::string& test_name,
                 test_func func )
    {
        if (!matchFilter(test_name)) return;

        readyTest(test_name);
        TestSuite::getResMsg() = "";
        TestSuite::getInfoMsg() = "";
        TestSuite::getCurTest() = this;
        int ret = func();
        reportTestResult(test_name, ret);
    }

    // 2) Ranged parameter.
    template<typename T, typename F>
    void doTest( std::string test_name,
                 F func,
                 TestRange<T> range )
    {
        if (!matchFilter(test_name)) return;

        size_t n = (useGivenRange) ? 1 : range.getSteps();
        size_t i;

        for (i=0; i<n; ++i) {
            std::string actual_test_name = test_name;
            std::stringstream ss;


            T cur_arg = (useGivenRange)
                        ? givenRange
                        : range.getEntry(i);

            ss << cur_arg;
            actual_test_name += " (" + ss.str() + ")";
            readyTest(actual_test_name);

            TestSuite::getResMsg() = "";
            TestSuite::getInfoMsg() = "";
            TestSuite::getCurTest() = this;

            int ret = func(cur_arg);
            reportTestResult(actual_test_name, ret);
        }
    }

    // 3) Generic one-time parameters.
    template<typename T1, typename... T2, typename F>
    void doTest( const std::string& test_name,
                 F func,
                 T1 arg1,
                 T2... args )
    {
        if (!matchFilter(test_name)) return;

        readyTest(test_name);
        TestSuite::getResMsg() = "";
        TestSuite::getInfoMsg() = "";
        TestSuite::getCurTest() = this;
        int ret = func(arg1, args...);
        reportTestResult(test_name, ret);
    }

    // 4) Multi composite parameters.
    template<typename F>
    void doTest( const std::string& test_name,
                 F func,
                 TestArgsWrapper& args_wrapper )
    {
        if (!matchFilter(test_name)) return;

        TestArgsBase* args = args_wrapper.getArgs();
        args->setCallback(test_name, func, this);
        args->testAll();
    }

    TestOptions options;

private:
    void doTestCB( const std::string& test_name,
                   test_func_args func,
                   TestArgsBase* args )
    {
        readyTest(test_name);
        TestSuite::getResMsg() = "";
        TestSuite::getInfoMsg() = "";
        TestSuite::getCurTest() = this;
        int ret = func(args);
        reportTestResult(test_name, ret);
    }

    static void spawnThread(ThreadInternalArgs* args) {
        args->rc = args->func(args->userArgs);
    }

    bool matchFilter(const std::string& test_name) {
        if (!filter.empty() &&
            test_name.find(filter) == std::string::npos) {
            // Doesn't match with the given filter.
            return false;
        }
        return true;
    }

    void readyTest(const std::string& test_name) {
        printf("[ " "...." " ] %s\n", test_name.c_str());
        if ( (options.printTestMessage || displayMsg) &&
             !suppressMsg ) {
            printf(_CL_D_GRAY("   === TEST MESSAGE (BEGIN) ===\n"));
        }
        fflush(stdout);

        getTestName() = test_name;
        startTimeLocal = std::chrono::system_clock::now();
    }

    void reportTestResult(const std::string& test_name,
                          int result)
    {
        std::chrono::time_point<std::chrono::system_clock> cur_time =
                std::chrono::system_clock::now();;
        std::chrono::duration<double> elapsed = cur_time - startTimeLocal;
        std::string time_str = usToString(elapsed.count() * 1000000);

        char msg_buf[1024];
        std::string res_msg = TestSuite::getResMsg();
        sprintf(msg_buf, "%s (" _CL_BROWN("%s") ")%s%s",
                test_name.c_str(),
                time_str.c_str(),
                (res_msg.empty() ? "" : ": "),
                res_msg.c_str() );

        if (result < 0) {
            printf("[ " _CL_RED("FAIL") " ] %s\n", msg_buf);
            cntFail++;
        } else {
            if ( (options.printTestMessage || displayMsg) &&
                 !suppressMsg ) {
                printf(_CL_D_GRAY("   === TEST MESSAGE (END) ===\n"));
            } else {
                // Move a line up.
                printf("\033[1A");
                // Clear current line.
                printf("\r");
                // And then overwrite.
            }
            printf("[ " _CL_GREEN("PASS") " ] %s\n", msg_buf);
            cntPass++;
        }

        if ( result != 0 &&
             (options.abortOnFailure || forceAbortOnFailure) ) {
            abort();
        }
        getTestName().clear();
    }

    size_t cntPass;
    size_t cntFail;
    std::string filter;
    bool useGivenRange;
    bool preserveTestFiles;
    bool forceAbortOnFailure;
    bool suppressMsg;
    bool displayMsg;
    int64_t givenRange;
    // Start time of each test.
    std::chrono::time_point<std::chrono::system_clock> startTimeLocal;
    // Start time of the entire test suite.
    std::chrono::time_point<std::chrono::system_clock> startTimeGlobal;
};

// ===== Functor =====

struct TestArgsSetParamFunctor {
    template<typename T>
    void operator()(T* t, TestRange<T>& r, size_t param_idx) const {
        *t = r.getEntry(param_idx);
    }
};

template<std::size_t I = 0,
         typename FuncT,
         typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
TestArgsSetParamScan(int,
                     std::tuple<Tp*...> &,
                     std::tuple<TestRange<Tp>...> &,
                     FuncT,
                     size_t) { }

template<std::size_t I = 0,
         typename FuncT,
         typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
TestArgsSetParamScan(int index,
                     std::tuple<Tp*...>& t,
                     std::tuple<TestRange<Tp>...>& r,
                     FuncT f,
                     size_t param_idx) {
    if (index == 0) f(std::get<I>(t), std::get<I>(r), param_idx);
    TestArgsSetParamScan<I + 1, FuncT, Tp...>(index-1, t, r, f, param_idx);
}
struct TestArgsGetNumStepsFunctor {
    template<typename T>
    void operator()(T* t, TestRange<T>& r, size_t& steps_ret) const {
        (void)t;
        steps_ret = r.getSteps();
    }
};

template<std::size_t I = 0,
         typename FuncT,
         typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
TestArgsGetStepsScan(int,
                     std::tuple<Tp*...> &,
                     std::tuple<TestRange<Tp>...> &,
                     FuncT,
                     size_t) { }

template<std::size_t I = 0,
         typename FuncT,
         typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
TestArgsGetStepsScan(int index,
                     std::tuple<Tp*...>& t,
                     std::tuple<TestRange<Tp>...>& r,
                     FuncT f,
                     size_t& steps_ret) {
    if (index == 0) f(std::get<I>(t), std::get<I>(r), steps_ret);
    TestArgsGetStepsScan<I + 1, FuncT, Tp...>(index-1, t, r, f, steps_ret);
}

#define TEST_ARGS_CONTENTS()                               \
    void setParam(size_t param_no, size_t param_idx) {     \
        TestArgsSetParamScan(param_no, args, ranges,       \
                             TestArgsSetParamFunctor(),    \
                             param_idx); }                 \
    size_t getNumSteps(size_t param_no) {                  \
        size_t ret = 0;                                    \
        TestArgsGetStepsScan(param_no, args, ranges,       \
                             TestArgsGetNumStepsFunctor(), \
                             ret);                         \
        return ret; }                                      \
    size_t getNumParams() {                                \
        return std::tuple_size<decltype(args)>::value;     \
    }


// ===== TestArgsBase =====

void TestArgsBase::testAllInternal(size_t depth) {
    size_t i;
    size_t n_params = getNumParams();
    size_t n_steps = getNumSteps(depth);

    for (i=0; i<n_steps; ++i) {
        setParam(depth, i);
        if (depth+1 < n_params) {
            testAllInternal(depth+1);
        } else {
            std::string test_name;
            std::string args_name = toString();
            if (!args_name.empty()) {
                test_name = testName + " (" + args_name + ")";
            }
            testInstance->doTestCB(test_name,
                                   testFunction,
                                   this);
        }
    }
}

// ===== Parameter macros =====

#define DEFINE_PARAMS_2(name,                                  \
                        type1, param1, range1,                 \
                        type2, param2, range2)                 \
    class name ## _class : public TestArgsBase {               \
    public:                                                    \
        name ## _class() {                                     \
            args = std::make_tuple(&param1, &param2);          \
            ranges = std::make_tuple(                          \
                         TestRange<type1>range1,               \
                         TestRange<type2>range2 );             \
        }                                                      \
        std::string toString() {                               \
            std::stringstream ss;                              \
            ss << param1 << ", " << param2;                    \
            return ss.str();                                   \
        }                                                      \
        TEST_ARGS_CONTENTS()                                   \
        type1 param1;                                          \
        type2 param2;                                          \
    private:                                                   \
        std::tuple<type1*, type2*> args;                       \
        std::tuple<TestRange<type1>, TestRange<type2>> ranges; \
    };

#define DEFINE_PARAMS_3(name,                                  \
                        type1, param1, range1,                 \
                        type2, param2, range2,                 \
                        type3, param3, range3)                 \
    class name ## _class : public TestArgsBase {               \
    public:                                                    \
        name ## _class() {                                     \
            args = std::make_tuple(&param1, &param2, &param3); \
            ranges = std::make_tuple(                          \
                         TestRange<type1>range1,               \
                         TestRange<type2>range2,               \
                         TestRange<type3>range3 );             \
        }                                                      \
        std::string toString() {                               \
            std::stringstream ss;                              \
            ss << param1 << ", " << param2 << ", " << param3;  \
            return ss.str();                                   \
        }                                                      \
        TEST_ARGS_CONTENTS()                                   \
        type1 param1;                                          \
        type2 param2;                                          \
        type3 param3;                                          \
    private:                                                   \
        std::tuple<type1*, type2*, type3*> args;               \
        std::tuple<TestRange<type1>,                           \
                   TestRange<type2>,                           \
                   TestRange<type3>> ranges;                   \
    };

#define SET_PARAMS(name) \
    TestArgsWrapper name(new name ## _class())

#define GET_PARAMS(name) \
    name ## _class* name = static_cast<name ## _class*>(TEST_args_base__)

#define PARAM_BASE TestArgsBase* TEST_args_base__

#define TEST_SUITE_AUTO_PREFIX __func__

#define TEST_SUITE_PREPARE_PATH(path)                               \
    const std::string _ts_auto_prefiix_ = TEST_SUITE_AUTO_PREFIX;   \
    TestSuite::clearTestFile(_ts_auto_prefiix_);                    \
    path = TestSuite::getTestFileName(_ts_auto_prefiix_);

#define TEST_SUITE_CLEANUP_PATH()                       \
    TestSuite::clearTestFile( _ts_auto_prefiix_,        \
                              TestSuite::END_OF_TEST );

