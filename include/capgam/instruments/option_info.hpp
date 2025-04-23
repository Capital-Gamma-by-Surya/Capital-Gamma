#ifndef CAPGAM_INSTRUMENTS_OPTIONINFO_H
#define CAPGAM_INSTRUMENTS_OPTIONINFO_H

#include <capgam/instruments/payoffs.hpp>
#include <memory>

class OptionInfo {
   public:
    OptionInfo(std::unique_ptr<Payoff> payoff_type, double time_to_exp);
    double payoff(double spot) const;
    double get_time_to_exp() const;

   private:
    std::unique_ptr<Payoff> payoff_type_;
    double time_to_exp_;
};

#endif
