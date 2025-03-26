#include <gtest/gtest.h>

#include <capgam/engine/mc_option_valuation.hpp>
#include <memory>

TEST(MC_Option_Valuation_Tests, Test_Returns_Double) {
    std::unique_ptr<CallPayoff> call_payoff =
        std::make_unique<CallPayoff>(CallPayoff{100.0});
    OptionInfo opt_info{std::move(call_payoff), 4.0};

    MCOptionValuation mc_opt_val{std::move(opt_info), 10, 3.0, 4.5, 0.0};
    double opt_price = mc_opt_val.calc_price(85.0, 100, 42);

    EXPECT_GT(opt_price, 0.0);
    EXPECT_LT(opt_price, 85.0);
}
