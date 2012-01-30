#ifndef ERASE_IF_H
#define ERASE_IF_H

#include <algorithm>

template<class Container, class Predicate>
void erase_if(Container & c, Predicate pred) {
    c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}

#endif // ERASE_IF_H
