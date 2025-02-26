#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>
#include <chrono>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using namespace std::chrono;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}
uint64_t timeSinceEpochMillisec() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif