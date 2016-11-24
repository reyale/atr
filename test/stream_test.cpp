#include <iostream>

#include <gtest/gtest.h>

#include "streams/gzip.h"
#include "streams/bz2.h"

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

TEST(bz2_stream, tests) {
  atr::streams::bz2 bz2_handle;
  ASSERT_EQ(bz2_handle.open("./test/data/data.csv.bz2"), true);
  
  char buffer[21];
  std::string result;
  std::streamsize read_size;
  while(read_size = bz2_handle.read(buffer, sizeof(buffer))) {
    if(read_size <= 0) 
      break;
    result += std::string(buffer, read_size); 
  }
  ASSERT_EQ(result, "test,hey\n1232,sdfdsf\n");
  ASSERT_EQ(bz2_handle.close(), true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
