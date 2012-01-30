#include "Utilities.h"

namespace util {

double Utilities::random(double lower, double upper) {
    return double(rand()) / RAND_MAX * (upper - lower) + lower;
}

} // namespace util
