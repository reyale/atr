GCC=/usr/bin/g++ -std=gnu++14

INCLUDES = -I./

TEST_UTIL_SRC=test/util_test.cpp
TEST_UTIL_OBJS=$(subst .cpp,.o,$(TEST_UTIL_SRC))

TEST_STREAM_SRC=test/stream_test.cpp
TEST_STREAM_OBJS=$(subst .cpp,.o,$(TEST_STREAM_SRC))
TEST_STREAM_LIBS= -lz -lbz2

TEST_DATA_SRC=test/data_test.cpp
TEST_DATA_OBJS=$(subst .cpp,.o,$(TEST_DATA_SRC))

GTEST_LIBS=/usr/lib/libgtest.a -lpthread

%.o : %.cpp
	$(GCC) $(INCLUDES) -c $< -o $@

all: test_util test_stream test_data

test_util: $(TEST_UTIL_OBJS)
	$(GCC) $(INCLUDES) -o util_test $(TEST_UTIL_OBJS) $(GTEST_LIBS)

test_stream: $(TEST_STREAM_OBJS)
	$(GCC) $(INCLUDES) -o stream_test $(TEST_STREAM_OBJS) $(GTEST_LIBS) $(TEST_STREAM_LIBS)

test_data: $(TEST_DATA_OBJS)
	$(GCC) $(INCLUDES) -o data_test $(TEST_DATA_OBJS) $(GTEST_LIBS)

#all: test_util test_stream

clean:
	rm $(TEST_UTIL_OBJS)
	rm $(TEST_STREAM_OBJS)
	rm $(TEST_DATA_OBJS)
	rm util_test
	rm stream_test
	rm data_test
