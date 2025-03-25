class Payoff {
 public:
  virtual double payoff(double price) const = 0;
  virtual ~Payoff() = default;
};

class CallPayoff final : public Payoff {
 public:
  CallPayoff(double strike_price);
  double payoff(double price) const final;

 private:
  double strike_price_;
};

class PutPayoff final : public Payoff {
 public:
  PutPayoff(double strike_price);
  double payoff(double price) const final;

 private:
  double strike_price_;
};
