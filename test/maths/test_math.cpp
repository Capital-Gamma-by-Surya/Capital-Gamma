#include <gtest/gtest.h>
#include <capgam/math/primative_operators.hpp>

TEST(MathTest, AddTest) {
	int result = calculate::int_sum(4, 6);
	EXPECT_EQ(result, 10);
}

TEST(MathTest, MultiplyTest) {
	int result = calculate::int_multiply(2, 4);
	EXPECT_EQ(result, 8);
}

TEST(MathTest, VecAddTest) {
	std::vector<int> a{ 1, 2 };
	std::vector<int> b{ 4, 5 };
	std::vector<int> result = calculate::int_vec_sum(a, b);
	std::vector<int> exp_result{ 5, 7 };
	EXPECT_EQ(result, exp_result);
}