#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include <gtest/gtest.h>

#include "collections/vec.h"


TEST(vec, construct) { 
  atr::collections::data::vec_int int_data{1,2,3,4,5};
  atr::collections::data::vec_double double_data{1.0,2.0,3.0,4.0};
  atr::collections::data::vec_obj obj_data{"one", "two", "three", "two"};

  auto compare_one = int_data == 3;
  ASSERT_EQ(compare_one.size(), int_data.size());
  ASSERT_EQ(std::accumulate(compare_one.begin(), compare_one.end(), 0), 1);
  
  auto compare_three = obj_data == "two";
  ASSERT_EQ(compare_three.size(), obj_data.size());
  ASSERT_EQ(std::accumulate(compare_three.begin(), compare_three.end(), 0), 2);

  //ISIN
  atr::collections::data::vec_double isin_double{2.0, 3.0, 2.0, 1.0};
  auto isin_double_result = isin_double.isin(std::vector<double>{2.0,1.0});
  ASSERT_EQ(std::accumulate(isin_double_result.begin(), isin_double_result.end(), 0.0), 3);
  ASSERT_EQ(isin_double_result[0], true);
  ASSERT_EQ(isin_double_result[1], false);
  ASSERT_EQ(isin_double_result[2], true);
  ASSERT_EQ(isin_double_result[3], true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
