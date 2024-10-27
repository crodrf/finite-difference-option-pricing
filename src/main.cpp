// File: main.cpp

#include <iostream>
#include <memory>
#include <fstream>
#include "payoff.h"
#include "option.h"
#include "pde.h"
#include "fdm.h"
#include "euler_explicit_scheme.h"

int main() {
    const double strike_price = 0.5;
    const double risk_free_rate = 0.05;
    const double volatility = 0.2;
    const double maturity_time = 1.0;

    const double max_asset_price = 1.0;
    const unsigned long num_spatial_points = 20;
    const unsigned long num_time_steps = 20;

    try {
        auto option = std::make_shared<VanillaOption<CallPayOff> >(strike_price, risk_free_rate, maturity_time,
                                                                   volatility);

        auto pde = std::make_unique<BlackScholesPDE>(option);

        FDM<EulerExplicitScheme> fdm(max_asset_price, num_spatial_points, maturity_time, num_time_steps,
                                     std::move(pde));

        fdm.step_march();

        std::cout << "Finite Difference Method completed. Results saved to 'fdm.csv'." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
