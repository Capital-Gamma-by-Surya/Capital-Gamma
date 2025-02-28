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