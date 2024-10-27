#include "pde.h"
#include "payoff.h"
#include "option.h"
#include <gtest/gtest.h>

TEST(BoundaryConditionsTest, CallOptionBoundary) {
    const double strike_price = 0.5;
    const double risk_free_rate = 0.05;
    const double volatility = 0.2;
    const double maturity_time = 1.0;

    // Create a Call option
    auto call_option = std::make_shared<VanillaOption<CallPayOff> >(strike_price, risk_free_rate, maturity_time,
                                                                    volatility);

    // Create the Black-Scholes PDE
    BlackScholesPDE bs_pde(call_option);

    // Test the boundary conditions
    EXPECT_DOUBLE_EQ(bs_pde.boundary_left(0.0, 0.0), 0.0); // Call option is worthless when stock price is 0

    // Expected right boundary value with discount factor
    double expected_boundary_right = 1000.0 - strike_price * std::exp(-risk_free_rate * maturity_time);
    EXPECT_NEAR(bs_pde.boundary_right(0.0, 1000.0), expected_boundary_right, 1e-6);
}
