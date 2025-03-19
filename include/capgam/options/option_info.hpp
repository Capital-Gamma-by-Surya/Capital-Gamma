#include <memory>
#include <capgam/options/payoffs.hpp>

class OptionInfo {
    public:
        OptionInfo(std::unique_ptr<Payoff> payoff_type);
        double payoff(double spot) const;
    private:
        std::unique_ptr<Payoff> payoff_type_;
};
