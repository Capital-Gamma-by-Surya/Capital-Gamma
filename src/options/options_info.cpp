#include <capgam/options/option_info.hpp>

OptionInfo::OptionInfo(std::unique_ptr<Payoff> payoff_type) : payoff_type_{std::move(payoff_type)} {}

double OptionInfo::payoff(double spot) const {
    return payoff_type_->payoff(spot);
}
