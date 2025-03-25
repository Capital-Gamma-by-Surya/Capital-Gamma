#include <vector>

class EquityPriceGenerator {
   public:
    EquityPriceGenerator(double spot_price, int num_time_steps,
                         double time_to_exp, double volatility, double rf_rate,
                         double div_rate);

    std::vector<double> operator()(unsigned seed) const;

   private:
    double spot_;
    int num_time_steps_;
    double time_to_exp_;
    double volatility_;
    double rf_rate_;
    double div_rate_;
    double dt_;
};
