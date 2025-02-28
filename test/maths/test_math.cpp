#include <gtest/gtest.h>
#include <capgam/math/primative_operators.hpp>

TEST(MathTest, AddTest) {
	int result = summation::sum(4, 6);
	EXPECT_EQ(result, 10);
}