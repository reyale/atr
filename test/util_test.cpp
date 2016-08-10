#include <gtest/gtest.h>

#include "util/pstring.h"
#include "util/fixedstring.h"
#include "util/tokenizer.h"

TEST(pstring, construct) {
  static const char raw_string[] = "12345";

  atr::util::pstring test(raw_string);
  
  std::string result;
  for(auto & e : test)
    result += e;

  ASSERT_EQ(result, raw_string); 
}

TEST(pstring, lower) {
  atr::util::pstring test("asDS");
  ASSERT_EQ(test.lower(), "asds");
}

TEST(pstring, upper) {
  atr::util::pstring test("asDS");
  ASSERT_EQ(test.upper(), "ASDS");
}

TEST(pstring, lstrip) {
  atr::util::pstring test("  asDS");
  auto result = test.lstrip(' ');
  ASSERT_EQ(result, "asDS");
  result = result.lstrip('a');
  ASSERT_EQ(result, "sDS");

  atr::util::pstring test2("12345");
  ASSERT_EQ(test2.lstrip('6'), "12345");
}

TEST(pstring, rstrip) {
  atr::util::pstring test("asDS  ");
  auto result = test.rstrip(' '); 
  ASSERT_EQ(result, "asDS");
  result = result.rstrip('S');
  ASSERT_EQ(result, "asD");

  atr::util::pstring test2("12345");
  ASSERT_EQ(test2.rstrip('6'), "12345");
}

TEST(pstring, split) {
  atr::util::pstring test("1234-abc");
  auto result = test.split('-');
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result[0], "1234");
  ASSERT_EQ(result[1], "abc");
}

TEST(pstring, indexer) {
  atr::util::pstring test("12345");
  ASSERT_EQ(test[-1], '5');
  ASSERT_EQ(test[-2], '4');
  ASSERT_EQ(test[0], '1');
  ASSERT_EQ(test[1], '2');

  ASSERT_EQ(test(-1), '5');
  ASSERT_EQ(test(-2), '4');
  ASSERT_EQ(test(0), '1');
  ASSERT_EQ(test(1), '2');
}

TEST(pstring, substr) {
  atr::util::pstring test("12345");

  auto result = test(-2,-1);
  ASSERT_EQ(result, "4");
  result = test(-4,-4);
  ASSERT_EQ(result, "");
  result = test(-4,-3);
  ASSERT_EQ(result, "2");
  result = test(1, 4);
  ASSERT_EQ(result, "234");
  result = test(1, -2);
  ASSERT_EQ(result, "23");
  result = test(-3,4);
  ASSERT_EQ(result, "34");
}

TEST(tokenizer, tests) {
  atr::util::string_tokenizer tokenizer('_');

  auto result = tokenizer.tokenize<atr::util::string_tokenizer::token>("abc_123"); 
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(result[0].to_string(), "abc");
  ASSERT_EQ(result[1].to_string(), "123");
  
  result = tokenizer.tokenize<atr::util::string_tokenizer::token>("abc");
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0].to_string(), "abc");

  result = tokenizer.tokenize<atr::util::string_tokenizer::token>("_");
  ASSERT_EQ(result.size(), 0);

  result = tokenizer.tokenize<atr::util::string_tokenizer::token>("_abc_123_4567_");
  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(result[0].to_string(), "abc");
  ASSERT_EQ(result[1].to_string(), "123");
  ASSERT_EQ(result[2].to_string(), "4567");
}

TEST(fixed_string, tests) {
  typedef atr::util::fixed_string<10> StringType;
  StringType test("12345");
  ASSERT_EQ(test, "12345");
  ASSERT_EQ(test.size(), 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
