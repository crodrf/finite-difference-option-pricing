// File: option.h

#ifndef OPTION_H
#define OPTION_H

// Base class for Vanilla Options (call, put)
class VanillaOptionBase {
public:
    virtual double calculate_price(double asset_price) const = 0;

    virtual double get_volatility() const = 0;

    virtual double get_risk_free_rate() const = 0;

    virtual double get_strike_price() const = 0;

    virtual double get_maturity() const = 0;

    virtual ~VanillaOptionBase() = default;
};

// Vanilla Option Template
template<typename PayOffType>
class VanillaOption : public VanillaOptionBase {
public:
    VanillaOption(double strike_price, double risk_free_rate, double maturity_time, double volatility)
        : strike_price(strike_price), risk_free_rate(risk_free_rate), maturity_time(maturity_time),
          volatility(volatility) {
    }

    double calculate_price(double asset_price) const override {
        return PayOffType::calculate(asset_price, strike_price);
    }

    double get_volatility() const override { return volatility; }
    double get_risk_free_rate() const override { return risk_free_rate; }
    double get_strike_price() const override { return strike_price; }
    double get_maturity() const override { return maturity_time; }

private:
    double strike_price;
    double risk_free_rate;
    double maturity_time;
    double volatility;
};

#endif
