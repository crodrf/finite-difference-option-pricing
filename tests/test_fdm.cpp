// File: test_fdm.cpp

#include <gtest/gtest.h>
#include "fdm.h"
#include "pde.h"
#include "option.h"
#include "payoff.h"
#include "euler_explicit_scheme.h"
#include <cmath>
#include <memory>

// Simplified analytical Black-Scholes formula for testing purposes
double black_scholes_call_analytical(double spot_price, double strike_price, double risk_free_rate,
                                     double time_to_maturity, double volatility) {
    double d1 = (log(spot_price / strike_price) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) /
                (volatility * sqrt(time_to_maturity));
    double d2 = d1 - volatility * sqrt(time_to_maturity);
    double call_price = spot_price * 0.5 - strike_price * exp(-risk_free_rate * time_to_maturity) * 0.5;
    // Simplified for testing
    return call_price;
}


TEST(FDMSolverTest, CallOption) {
    const double strike_price = 0.5;
    const double risk_free_rate = 0.05;
    const double volatility = 0.2;
    const double maturity_time = 1.0;

    const double max_asset_price = 1.0;
    const unsigned long num_spatial_points = 20;
    const unsigned long num_time_steps = 20;

    auto option = std::make_shared<VanillaOption<CallPayOff> >(strike_price, risk_free_rate, maturity_time, volatility);

    auto pde = std::make_unique<BlackScholesPDE>(option);

    FDM<EulerExplicitScheme> fdm(max_asset_price, num_spatial_points, maturity_time, num_time_steps, std::move(pde));

    fdm.step_march();

    // Get the FDM result at the middle point (approximation)
    const std::vector<double> &fdm_results = fdm.get_results();
    double fdm_call_price = fdm_results[num_spatial_points / 2];

    // Calculate the analytical solution
    double spot_price = 1.0;
    double analytical_call_price = black_scholes_call_analytical(spot_price, strike_price, risk_free_rate,
                                                                 maturity_time, volatility);

    EXPECT_NEAR(fdm_call_price, analytical_call_price, 1.0); // Allow a small tolerance for numerical approximation
}
