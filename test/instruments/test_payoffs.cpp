#include <gtest/gtest.h>

#include <capgam/instruments/payoffs.hpp>

TEST(PayoffTest, CallPayoffPositiveTest) {
    double strike_price = 100.0;
    double price = 120.0;

    CallPayoff call_payoff{strike_price};
    double payoff_result = call_payoff.payoff(price);

    EXPECT_EQ(payoff_result, 20.0);
}

TEST(PayoffTest, CallPayoffZeroTest) {
    double strike_price = 100.0;
    double price = 80.0;

    CallPayoff call_payoff{strike_price};
    double payoff_result = call_payoff.payoff(price);

    EXPECT_EQ(payoff_result, 0.0);
}

TEST(PayoffTest, PutPayoffPositiveTest) {
    double strike_price = 100.0;
    double price = 85.0;

    PutPayoff put_payoff{strike_price};
    double payoff_result = put_payoff.payoff(price);

    EXPECT_EQ(payoff_result, 15.0);
}

TEST(PayoffTest, PutPayoffZeroTest) {
    double strike_price = 100.0;
    double price = 110.0;

    PutPayoff put_payoff{strike_price};
    double payoff_result = put_payoff.payoff(price);

    EXPECT_EQ(payoff_result, 0.0);
}
