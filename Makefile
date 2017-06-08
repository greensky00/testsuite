LDFLAGS =

CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src -I./examples

CXXFLAGS += -Wall
#CXXFLAGS += -O3

BASIC_TEST = \
	examples/basic_test.o \

RANGE_TEST = \
	examples/range_test.o \

MULTI_ARGS_TEST = \
	examples/multi_args_test.o \

CLI_ARGS_TEST = \
	examples/cli_args_test.o \

MESSAGE_TEST = \
	examples/message_test.o \

VERIFY_MULTI_INCLUDE = \
	examples/verify_multi_include.o \
	examples/dummy.o \

PROGRAMS = \
	examples/basic_test \
	examples/range_test \
	examples/multi_args_test \
	examples/cli_args_test \
	examples/message_test \
	examples/verify_multi_include \

all: $(PROGRAMS)

examples/basic_test: $(BASIC_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples/range_test: $(RANGE_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples/multi_args_test: $(MULTI_ARGS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples/cli_args_test: $(CLI_ARGS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples/message_test: $(MESSAGE_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

examples/verify_multi_include: $(VERIFY_MULTI_INCLUDE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test:
	examples/basic_test
	examples/range_test
	examples/multi_args_test
	examples/cli_args_test
	examples/message_test

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so
