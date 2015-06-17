CC=g++
CFLAGS=-c -Wall -std=c++11
SOURCES=$(shell find src -name '*.cc')
TESTS=$(shell find test -name '*.cc')
SOURCE_OBJS=$(SOURCES:.cc=.o)
TEST_OBJS=$(TESTS:.cc=.o)
TEST_EXECUTABLE=hikari_test

test: $(TESTS) $(SOURCES) $(TEST_EXECUTABLE)
$(TEST_EXECUTABLE): $(SOURCE_OBJS) $(TEST_OBJS)
	$(CC) $(LDFLAGS) $(SOURCE_OBJS) $(TEST_OBJS) -o $@
.cc.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm $(SOURCE_OBJS) $(TEST_OBJS) $(TEST_EXECUTABLE)
