#include <gtest/gtest.h>

#include "streams/gzip.h"

TEST(gzip_stream, tests) {
 atr::streams::gzip gzip_handle; 
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
