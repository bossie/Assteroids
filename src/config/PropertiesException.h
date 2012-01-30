#ifndef PROPERTIES_EXCEPTION_H
#define PROPERTIES_EXCEPTION_H

#include "../exception/Exception.h"

namespace config {

class PropertiesException: public exception::Exception {
public:
	PropertiesException(const std::string & message);
};

} // namespace config

#endif // PROPERTIES_EXCEPTION_H
