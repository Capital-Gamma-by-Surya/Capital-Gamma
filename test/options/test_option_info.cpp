#include <memory>
#include <gtest/gtest.h>
#include <capgam/options/option_info.hpp>

TEST(OptionInfoTest, CallOptionTest) {
    OptionInfo call_option{std::make_unique<CallPayoff>(CallPayoff{100.0})};
    double payoff_result = call_option.payoff(120.0);

    EXPECT_EQ(payoff_result, 20.0);
}
