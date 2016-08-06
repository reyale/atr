#include <gtest/gtest.h>

#include "util/pstring.h"
#include "util/tokenizer.h"

TEST(pstring, lower) {
  atr::util::pstring test("asDS");
  ASSERT_EQ(test.lower(), "asds");
}

TEST(pstring, upper) {
  atr::util::pstring test("asDS");
  ASSERT_EQ(test.upper(), "ASDS");
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
}

TEST(tokenizer, tests) {
  atr::util::string_tokenizer tokenizer('_');

  auto result = tokenizer.tokenize("abc_123");
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(atr::util::token_to_string(result[0]), "abc");
  ASSERT_EQ(atr::util::token_to_string(result[1]), "123");
  
  result = tokenizer.tokenize("abc");
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(atr::util::token_to_string(result[0]), "abc");

  result = tokenizer.tokenize("_");
  ASSERT_EQ(result.size(), 0);

  result = tokenizer.tokenize("_abc_123_4567_");
  ASSERT_EQ(result.size(), 3);
  ASSERT_EQ(atr::util::token_to_string(result[0]), "abc");
  ASSERT_EQ(atr::util::token_to_string(result[1]), "123");
  ASSERT_EQ(atr::util::token_to_string(result[2]), "4567");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
