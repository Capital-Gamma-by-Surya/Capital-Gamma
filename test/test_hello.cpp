#include <gtest/gtest.h>
#include <capgam/hello.hpp>

TEST(HelloTest, CheckHelloMessage) {
	std::string message = capgam::get_hello_world();
	EXPECT_EQ(message, "Hello Finance world!");
}