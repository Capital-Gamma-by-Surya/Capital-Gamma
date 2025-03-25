#include <gtest/gtest.h>

#include <capgam/models/equity_price_generator.hpp>

TEST(EquityPriceGeneratorTest, GeneratorTest) {
    EquityPriceGenerator generator{100.0, 20, 20.0, 3.0, 4.5, 0.0};
    std::vector<double> prices = generator(100);

    size_t num_prices = prices.size();
    size_t expected_sizes = 21;

    EXPECT_EQ(num_prices, expected_sizes);
}
