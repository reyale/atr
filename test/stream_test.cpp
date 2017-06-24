#include <iostream>
#include <cstring>

#include <gtest/gtest.h>

#include "streams/gzip.h"
#include "streams/bz2.h"
#include "streams/streambuffer.h"

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

TEST(buffer_stream, tests) {
  atr::streams::buffer stream_buffer(100);
  static const char* test = "sdfsdfodshdosfdsoh2e23123asadsad21d2d22\nadsdsapdj2po2je2e\nasdsadsadsadasdasdsaodhondo2indo2ind2oi1dn2iod2n1do2i1nd12";

  ASSERT_EQ(stream_buffer.writeable_amount(), 100);

  //dont fill buffer
  ::mempcpy(stream_buffer.write_location(), test, 25);
  stream_buffer.mark_written(25);
  ASSERT_EQ(std::strncmp(stream_buffer.read_location(), test, 25), 0);

  //dont fill buffer
  ::mempcpy(stream_buffer.write_location(), test + 25, 25);
  stream_buffer.mark_written(25);
  ASSERT_EQ(std::strncmp(stream_buffer.read_location(), test, 50), 0);

  //finish the buffer
  ::mempcpy(stream_buffer.write_location(), test + 50, 50);
  stream_buffer.mark_written(50);
  ASSERT_EQ(std::strncmp(stream_buffer.read_location(), test, 100), 0);
 
  //mark some read
  stream_buffer.mark_read(33);
  ASSERT_EQ(std::strncmp(stream_buffer.read_location(), test + 33, 100 - 33), 0);
  
  //test reclaiming buffer space
  ASSERT_EQ(stream_buffer.writeable_amount(), 0);
  stream_buffer.shift_all();
  ASSERT_EQ(stream_buffer.writeable_amount(), 33);

  ::mempcpy(stream_buffer.write_location(), test + 100, stream_buffer.writeable_amount());
  stream_buffer.mark_written(stream_buffer.writeable_amount());
  ASSERT_EQ(std::strncmp(stream_buffer.read_location(), test + 33, 100), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
