
# Finite Difference Option Pricing

This project implements a Finite Difference Method (FDM) solver to calculate option prices for vanilla European call and put options using the Black-Scholes model. The project is structured in C++ with Python for data visualization, and includes unit tests and continuous integration with GitHub Actions.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Visualization](#visualization)
- [Continuous Integration](#continuous-integration)
- [License](#license)

## Project Overview
This project numerically solves the Black-Scholes Partial Differential Equation (PDE) for European options using the explicit Euler finite difference scheme. The FDM solution computes the option prices and writes results to a CSV file, which is later visualized using a Python 3D surface plot.

### Key Components
1. **Finite Difference Method Solver**: Computes option prices over a discrete grid of asset prices and times to maturity.
2. **Black-Scholes PDE**: Models the option price evolution over time.
3. **Payoff Functions**: Calculates payoff for call and put options.
4. **Visualization**: Plots the option pricing surface using Python’s `matplotlib`.

## Features
- **Finite Difference Method**: Uses an explicit Euler scheme to solve the Black-Scholes PDE.
- **Boundary and Initial Conditions**: Implements boundary conditions for the FDM grid, supporting option payoff and Black-Scholes requirements.
- **Unit Testing**: Validates FDM solver, payoff calculations, and boundary conditions.
- **Continuous Integration**: Automated testing via GitHub Actions.
- **Data Visualization**: Generates 3D plots of option prices.

## Project Structure
```
├── src
│   ├── main.cpp                  # Main program entry
│   ├── fdm.h                     # Finite Difference Method class template
│   ├── euler_explicit_scheme.h   # Euler Explicit Scheme for FDM
│   ├── option.h                  # Vanilla Option classes (call/put)
│   ├── payoff.h                  # Payoff functions (CallPayOff, PutPayOff)
│   └── pde.h                     # Black-Scholes PDE
├── tests
│   ├── test_boundary.cpp         # Boundary condition tests
│   ├── test_fdm.cpp              # FDM solver tests
│   └── test_payoff.cpp           # Payoff function tests
├── plot_option_pricing_surface.py # Python script to plot option prices
├── .github/workflows
│   └── ci.yml                    # GitHub Actions workflow for CI
└── README.md                     # Project documentation
```

## Installation
### Prerequisites
- **C++ compiler** (supports C++11 or later)
- **CMake** (for build management)
- **Python 3.x** (for visualization)
- **gtest** (for unit testing)

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/crodrf/finite-difference-option-pricing.git
   cd finite-difference-option-pricing
   ```
2. Build the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

## Usage
Run the main program:
```bash
./build/main
```
This will execute the finite difference method and save results to `fdm.csv`.

## Testing
Run unit tests with Google Test:
```bash
./build/tests/test_boundary
./build/tests/test_fdm
./build/tests/test_payoff
```

## Visualization
To visualize the results, run the Python script:
```bash
python plot_option_pricing_surface.py
```
Ensure `fdm.csv` is in the same directory as the Python script.

## Continuous Integration
This repository includes a GitHub Actions workflow for continuous integration. The CI pipeline automatically:
1. Builds the project.
2. Runs the unit tests.

## License
This project is licensed under the MIT License.
