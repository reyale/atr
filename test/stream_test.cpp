#include <iostream>

#include <gtest/gtest.h>

#include "streams/gzip.h"

TEST(gzip_stream, tests) {
 atr::streams::gzip gzip_handle; 
 ASSERT_EQ(gzip_handle.open("./test/data/data.csv.gz"), true);

 char buffer[21];
 auto read_size = gzip_handle.read(buffer, sizeof(buffer));
 ASSERT_EQ(read_size > 0, true); 
 ASSERT_EQ(read_size, 21);
 auto string_result = std::string(buffer, read_size);
 ASSERT_EQ(string_result, "test,hey\n1232,sdfdsf\n");
 ASSERT_EQ(gzip_handle.close(), true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
