LDFLAGS =

CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src -I./examples

CXXFLAGS += -Wall
#CXXFLAGS += -O3

BASIC_EXAMPLE = \
	examples/basic_example.o \

PROGRAMS = \
	examples/basic_example \

all: $(PROGRAMS)

examples/basic_example: $(BASIC_EXAMPLE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so