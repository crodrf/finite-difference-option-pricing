cmake_minimum_required(VERSION 3.10)
project(OptionPricingFDM)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(include)

# Add source files
set(SOURCES
        src/main.cpp
)

# Add headers (optional, helps IDEs recognize header files in the project)
set(HEADERS
        include/euler_explicit_scheme.h
        include/fdm.h
        include/option.h
        include/payoff.h
        include/pde.h
)

# Create executable for main application
add_executable(OptionPricingFDM ${SOURCES} ${HEADERS})

# Google Test setup (assumes you have Google Test installed)
# Find GoogleTest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test files
set(TEST_SOURCES
        tests/test_boundary.cpp
        tests/test_fdm.cpp
        tests/test_payoff.cpp
)

# Create test executable
add_executable(OptionPricingFDM_tests ${TEST_SOURCES} ${HEADERS})
target_link_libraries(OptionPricingFDM_tests GTest::GTest GTest::Main)

# Enable testing and register tests
enable_testing()
add_test(NAME OptionPricingFDM_tests COMMAND OptionPricingFDM_tests)

