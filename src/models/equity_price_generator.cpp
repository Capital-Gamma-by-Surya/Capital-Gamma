#include <capgam/models/equity_price_generator.hpp>
#include <cmath>
#include <random>

EquityPriceGenerator::EquityPriceGenerator(double spot_price,
                                           int num_time_steps,
                                           double time_to_exp,
                                           double volatility, double rf_rate,
                                           double div_rate)
    : spot_{spot_price},
      num_time_steps_{num_time_steps},
      time_to_exp_{time_to_exp},
      volatility_{volatility},
      rf_rate_{rf_rate},
      div_rate_{div_rate},
      dt_{time_to_exp / num_time_steps} {}

std::vector<double> EquityPriceGenerator::operator()(unsigned seed) const {
    std::vector<double> prices;
    prices.reserve(num_time_steps_ + 1);

    std::mt19937_64 mt(seed);
    std::normal_distribution<> nd;

    auto new_price = [this](double previous_equity_price, double norm) {
        double price = 0.0;

        double exp_arg_01 =
            (rf_rate_ - div_rate_ - (volatility_ * volatility_) / 2.0) * dt_;
        double exp_arg_02 = volatility_ * norm * std::sqrt(dt_);

        price = previous_equity_price * std::exp(exp_arg_01 + exp_arg_02);

        return price;
    };

    double equity_price = spot_;
    prices.push_back(equity_price);

    for (size_t i = 0; i < num_time_steps_; ++i) {
        equity_price = new_price(equity_price, nd(mt));
        prices.push_back(equity_price);
    }

    return prices;
}
