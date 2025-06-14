#pragma once

#include <cmath>
#include<random>
#include <cmath>

class StandardGaussianGenerator {
public:
    // Constructor
    StandardGaussianGenerator()
        : _eng(_rd()), _dist(0., 1.) {}

    // Generate a random number following the standard normal distribution
    double generate() const {
        return _dist(_eng);
    }

private:
    // Non-deterministic random number generator
    std::random_device _rd;

    // Mersenne Twister pseudo-random generator
    mutable std::mt19937 _eng;

    // Normal distribution
    mutable std::normal_distribution<double> _dist;
};