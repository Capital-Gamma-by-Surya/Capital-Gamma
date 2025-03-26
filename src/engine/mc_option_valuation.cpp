#include <capgam/engine/mc_option_valuation.hpp>
#include <capgam/models/equity_price_generator.hpp>
#include <numeric>
#include <random>

MCOptionValuation::MCOptionValuation(OptionInfo&& opt, int time_steps,
                                     double vol, double int_rate,
                                     double div_rate)
    : opt_{std::move(opt)},
      time_steps_{time_steps},
      vol_{vol},
      int_rate_{int_rate},
      div_rate_{div_rate} {}

double MCOptionValuation::calc_price(double spot, int num_scenarios,
                                     unsigned unif_start_seed) {
    if (opt_.get_time_to_exp() > 0.0) {
        std::mt19937_64 mt_unif{unif_start_seed};
        std::uniform_int_distribution<unsigned> unif_int_dist{};

        std::vector<double> discounted_payoffs;
        discounted_payoffs.reserve(num_scenarios);

        const double discount_factor =
            std::exp(-int_rate_ * opt_.get_time_to_exp());

        for (int i = 0; i < num_scenarios; ++i) {
            EquityPriceGenerator epg{spot, time_steps_, opt_.get_time_to_exp(),
                                     vol_, int_rate_,   div_rate_};

            std::vector<double> scenario = epg(unif_int_dist(mt_unif));

            discounted_payoffs.push_back(discount_factor *
                                         opt_.payoff(scenario.back()));
        }

        return (1 / (float)num_scenarios) *
               std::accumulate(discounted_payoffs.cbegin(),
                               discounted_payoffs.cend(), 0.0);

    } else {
        return opt_.payoff(spot);
    }
}
