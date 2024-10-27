#include "payoff.h"
#include <gtest/gtest.h>

TEST(PayOffTest, CallPayOffBoundary) {
    double strike_price = 0.5;
    double asset_price_zero = 0.0;
    double asset_price_high = 1000.0;

    // CallPayOff calculates payoff as max(asset_price - strike_price, 0.0)
    EXPECT_DOUBLE_EQ(CallPayOff::calculate(asset_price_zero, strike_price), 0.0); // Boundary: worthless if asset price is 0
    EXPECT_NEAR(CallPayOff::calculate(asset_price_high, strike_price), asset_price_high - strike_price, 1e-6); // Approaches asset_price - strike_price at high asset prices
}

TEST(PayOffTest, PutPayOffBoundary) {
    double strike_price = 0.5;
    double asset_price_zero = 0.0;
    double asset_price_high = 1000.0;

    // PutPayOff calculates payoff as max(strike_price - asset_price, 0.0)
    EXPECT_DOUBLE_EQ(PutPayOff::calculate(asset_price_high, strike_price), 0.0); // Boundary: worthless if asset price is very high
    EXPECT_NEAR(PutPayOff::calculate(asset_price_zero, strike_price), strike_price, 1e-6); // Approaches strike_price if asset price is 0
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
