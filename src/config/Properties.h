#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <set>

namespace config {

class Properties {
public:
    virtual ~Properties() = 0;

    virtual const std::string operator[](const std::string & property) const = 0;
    virtual const std::set<std::string> names() const = 0;
};

} // namespace config

#endif // PROPERTIES_H
