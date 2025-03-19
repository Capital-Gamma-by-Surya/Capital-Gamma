#include <capgam/options/payoffs.hpp>
#include <algorithm>

CallPayoff::CallPayoff(double strike_price) : strike_price_{strike_price} {}

double CallPayoff::payoff(double price) const {
    return std::max(price - strike_price_, 0.0);
}

PutPayoff::PutPayoff(double strike_price) : strike_price_{strike_price} {}

double PutPayoff::payoff(double price) const {
    return std::max(strike_price_ - price, 0.0);
}
