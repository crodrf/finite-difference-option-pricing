// File: pde.h

#ifndef PDE_H
#define PDE_H

#include "option.h"
#include <memory>
#include <cmath>
#include <stdexcept>

class ConvectionDiffusionPDE {
public:
    virtual ~ConvectionDiffusionPDE() = default;

    virtual double diffusion_coefficient(double time, double asset_price) const = 0;

    virtual double convection_coefficient(double time, double asset_price) const = 0;

    virtual double zero_coefficient(double time, double asset_price) const = 0;

    virtual double source_coefficient(double time, double asset_price) const = 0;

    virtual double boundary_left(double time, double asset_price) const = 0;

    virtual double boundary_right(double time, double asset_price) const = 0;

    virtual double initial_condition(double asset_price) const = 0;
};

class BlackScholesPDE : public ConvectionDiffusionPDE {
public:
    explicit BlackScholesPDE(std::shared_ptr<VanillaOptionBase> option)
        : option(std::move(option)) {
        if (!this->option) {
            throw std::runtime_error("Option pointer is null");
        }
        risk_free_rate = this->option->get_risk_free_rate();
        volatility = this->option->get_volatility();
        strike_price = this->option->get_strike_price();
        maturity = this->option->get_maturity();
    }

    double diffusion_coefficient(double /*time*/, double asset_price) const override {
        if (!option) {
            throw std::runtime_error("Option pointer is null in diffusion_coefficient");
        }
        return 0.5 * volatility * volatility * asset_price * asset_price;
    }

    double convection_coefficient(double /*time*/, double asset_price) const override {
        if (!option) {
            throw std::runtime_error("Option pointer is null in convection_coefficient");
        }
        return risk_free_rate * asset_price;
    }

    double zero_coefficient(double /*time*/, double /*asset_price*/) const override {
        return -risk_free_rate;
    }

    double source_coefficient(double /*time*/, double /*asset_price*/) const override {
        return 0.0;
    }

    double boundary_left(double /*time*/, double /*asset_price*/) const override {
        return 0.0;
    }

    double boundary_right(double time, double asset_price) const override {
        if (!option) {
            throw std::runtime_error("Option pointer is null in boundary_right");
        }
        return asset_price - strike_price * std::exp(-risk_free_rate * (maturity - time));
    }

    double initial_condition(double asset_price) const override {
        if (!option) {
            throw std::runtime_error("Option pointer is null in initial_condition");
        }
        return option->calculate_price(asset_price);
    }

private:
    std::shared_ptr<VanillaOptionBase> option;
    double risk_free_rate;
    double volatility;
    double strike_price;
    double maturity;
};

#endif
