#include <capgam/instruments/option_info.hpp>

OptionInfo::OptionInfo(std::unique_ptr<Payoff> payoff_type, double time_to_exp)
    : payoff_type_{std::move(payoff_type)}, time_to_exp_{time_to_exp} {}

double OptionInfo::payoff(double spot) const {
  return payoff_type_->payoff(spot);
}

double OptionInfo::get_time_to_exp() const { return time_to_exp_; }
