// File: euler_explicit_scheme.h

#ifndef EULER_EXPLICIT_SCHEME_H
#define EULER_EXPLICIT_SCHEME_H

#include "pde.h"
#include <vector>
#include <cassert>

class EulerExplicitScheme {
public:
    static void set_initial_conditions(ConvectionDiffusionPDE *pde, const std::vector<double> &asset_prices,
                                       std::vector<double> &values) {
        assert(pde != nullptr && "PDE pointer is null");
        assert(asset_prices.size() == values.size() && "Vector sizes do not match");

        for (size_t i = 0; i < asset_prices.size(); ++i) {
            values[i] = pde->initial_condition(asset_prices[i]);
        }
    }

    static void calculate_boundary_conditions(ConvectionDiffusionPDE *pde, double prev_t,
                                              const std::vector<double> &asset_prices, std::vector<double> &values) {
        assert(pde != nullptr && "PDE pointer is null");
        assert(asset_prices.size() == values.size() && values.size() >= 2 && "Vector size mismatch or too small");

        values.front() = pde->boundary_left(prev_t, asset_prices.front());
        values.back() = pde->boundary_right(prev_t, asset_prices.back());
    }

    static void calculate_inner_points(ConvectionDiffusionPDE *pde, double delta_t, double delta_x, double prev_t,
                                       const std::vector<double> &asset_prices,
                                       const std::vector<double> &previous_values,
                                       std::vector<double> &current_values) {
        assert(pde != nullptr && "PDE pointer is null");
        assert(
            asset_prices.size() == previous_values.size() && previous_values.size() == current_values.size() &&
            "Vector sizes do not match");
        assert(delta_x > 0 && delta_t > 0 && "Invalid time or space step size");

        for (size_t j = 1; j < asset_prices.size() - 1; ++j) {
            double alpha, beta, gamma;
            calculate_coefficients(pde, delta_t, delta_x, prev_t, asset_prices[j], alpha, beta, gamma);
            current_values[j] = alpha * previous_values[j - 1] + beta * previous_values[j] + gamma * previous_values[
                                    j + 1];
        }
    }

private:
    static void calculate_coefficients(ConvectionDiffusionPDE *pde, double delta_t, double delta_x, double prev_t,
                                       double asset_price, double &alpha, double &beta, double &gamma) {
        assert(pde != nullptr && "PDE pointer is null");

        double sigma = pde->diffusion_coefficient(prev_t, asset_price);
        double mu = pde->convection_coefficient(prev_t, asset_price);
        double r = pde->zero_coefficient(prev_t, asset_price);
        const double dx2 = delta_x * delta_x;

        alpha = delta_t * (sigma / dx2 - mu / (2.0 * delta_x));
        beta = 1.0 - delta_t * (2.0 * sigma / dx2 - r);
        gamma = delta_t * (sigma / dx2 + mu / (2.0 * delta_x));
    }
};

#endif
