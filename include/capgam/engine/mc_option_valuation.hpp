#ifndef CAPGAM_ENGINE_MCOPTIONVALUATION_H
#define CAPGAM_ENGINE_MCOPTIONVALUATION_H

#include <capgam/instruments/option_info.hpp>

class MCOptionValuation {
   public:
    MCOptionValuation(OptionInfo&& opt, int time_steps, double vol,
                      double int_rate, double div_rate = 0.0);

    double calc_price(double spot, int num_scenarios, unsigned unif_start_seed);

   private:
    OptionInfo opt_;
    int time_steps_;
    double vol_, int_rate_, div_rate_;
};

#endif
