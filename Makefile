GCC=/usr/bin/g++ -std=gnu++14

INCLUDES = -I./

TEST_SRC=test/util_test.cpp
TEST_OBJS=$(subst .cpp,.o,$(TEST_SRC))

GTEST_LIBS=/usr/lib/libgtest.a -lpthread

%.o : %.cpp
	$(GCC) $(INCLUDES) -c $< -o $@

test: $(TEST_OBJS) 
	$(GCC) $(INCLUDES) -o util_test $(TEST_OBJS) $(GTEST_LIBS)

all:
	test

clean:
	rm $(TEST_OBJS)
	rm util_test
