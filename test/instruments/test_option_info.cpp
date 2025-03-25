#include <gtest/gtest.h>

#include <capgam/instruments/option_info.hpp>
#include <memory>

TEST(OptionInfoTest, CallOptionTest) {
  OptionInfo call_option{std::make_unique<CallPayoff>(CallPayoff{100.0}), 5.0};
  double payoff_result = call_option.payoff(120.0);

  EXPECT_EQ(payoff_result, 20.0);
}

TEST(OptionInfoTest, PutOptionTest) {
  OptionInfo put_option{std::make_unique<PutPayoff>(PutPayoff{100.0}), 5.0};
  double payoff_results = put_option.payoff(80.0);

  EXPECT_EQ(payoff_results, 20.0);
}
