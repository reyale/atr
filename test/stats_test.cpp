#include <gtest/gtest.h>

#include "stats/random.h"

static double TEST_SEED = 12345.0;

void validate_uniform(auto & dist) {
  for(int i = 0; i < 1000; ++i) {
    auto generated = dist.next();
    ASSERT_GT(generated-1.0, -0.000001);
    ASSERT_LT(generated, 5.0);
  }
}

TEST(stats, uniform_real_distribution) {
  atr::stats::uniform_real_distribution dist(1.0, 5.0);
  validate_uniform(dist);
}

TEST(stats, seeded_uniform_real_distribution) { 
  {
    atr::stats::uniform_real_distribution dist(1.0, 5.0, TEST_SEED); 
    validate_uniform(dist);
  }

  std::vector<double> results;
  {
    atr::stats::uniform_real_distribution dist(1.0, 5.0, TEST_SEED); 
    for(int i =0; i < 10; ++i)
      results.push_back(dist.next());
  }

  {
    atr::stats::uniform_real_distribution dist(1.0, 5.0, TEST_SEED); 
    for(int i =0; i < 10; ++i)
      ASSERT_EQ(results[i], dist.next());
  }
}

TEST(stats, choice) {
  atr::stats::choice<'A', 'B'> chooser(TEST_SEED);
  double a_count = 0;
  double b_count = 0;

  for(int i = 0; i < 100000; ++i) {
    auto selection = chooser.choose();
    if(selection == 'A')
      ++a_count;
    if(selection == 'B')
      ++b_count;
  }

  ASSERT_LT(std::fabs(1.0 - a_count/b_count), 0.01);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
