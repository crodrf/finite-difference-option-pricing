// File: fdm.h

#ifndef FDM_H
#define FDM_H

#include "pde.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>

template<typename Scheme>
class FDM {
public:
    FDM(double max_asset_price, unsigned long num_spatial_points, double maturity_time, unsigned long num_time_steps,
        std::unique_ptr<ConvectionDiffusionPDE> pde)
        : max_asset_price(max_asset_price), num_spatial_points(num_spatial_points), maturity_time(maturity_time),
          num_time_steps(num_time_steps), pde(std::move(pde)) {
        if (num_spatial_points < 2 || num_time_steps < 1) {
            throw std::invalid_argument("num_spatial_points must be >= 2 and num_time_steps must be >= 1.");
        }

        if (!this->pde) {
            throw std::runtime_error("PDE pointer is null");
        }

        initialize_grid();
        Scheme::set_initial_conditions(this->pde.get(), asset_prices, previous_values);
    }

    void step_march() {
        std::ofstream output("../fdm.csv");
        if (!output.is_open()) {
            throw std::runtime_error("Error: Unable to open fdm.csv file");
        }

        prev_t = 0.0;
        for (unsigned long n = 0; n < num_time_steps; ++n) {
            Scheme::calculate_boundary_conditions(pde.get(), prev_t, asset_prices, current_values);
            Scheme::calculate_inner_points(pde.get(), delta_t, delta_x, prev_t, asset_prices, previous_values,
                                           current_values);

            if (output) {
                // Write to file only if output is valid
                for (size_t i = 0; i < num_spatial_points; ++i) {
                    output << asset_prices[i] << " " << prev_t << " " << current_values[i] << "\n";
                }
            }

            previous_values = current_values;
            prev_t += delta_t;
        }
    }

    const std::vector<double> &get_results() const {
        return current_values;
    }

private:
    void initialize_grid() {
        delta_x = max_asset_price / (num_spatial_points - 1);
        delta_t = maturity_time / (num_time_steps - 1);
        asset_prices.resize(num_spatial_points);
        previous_values.resize(num_spatial_points, 0.0);
        current_values.resize(num_spatial_points, 0.0);

        for (unsigned long i = 0; i < num_spatial_points; ++i) {
            asset_prices[i] = i * delta_x;
        }
    }

    double max_asset_price, maturity_time, delta_x, delta_t, prev_t;
    unsigned long num_spatial_points, num_time_steps;
    std::unique_ptr<ConvectionDiffusionPDE> pde;
    std::vector<double> asset_prices;
    std::vector<double> previous_values, current_values;
};

#endif
