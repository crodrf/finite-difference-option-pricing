// File: payoff.h

#ifndef PAYOFF_H
#define PAYOFF_H

#include <algorithm>

// PayOff for Call Option
struct CallPayOff {
    static double calculate(double asset_price, double strike_price) {
        return std::max(asset_price - strike_price, 0.0);
    }
};

// PayOff for Put Option
struct PutPayOff {
    static double calculate(double asset_price, double strike_price) {
        return std::max(strike_price - asset_price, 0.0);
    }
};

#endif
