#ifndef UTILITIES_H
#define UTILITIES_H

#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

namespace util {

class Utilities {
 public:
    static double random(double lower, double upper);
};

} // namespace util

#endif // UTILITIES_H
