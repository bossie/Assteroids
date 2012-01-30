#include "PropertiesException.h"

namespace config {

PropertiesException::PropertiesException(const std::string & message):
    Exception::Exception(message) {
}

} // namespace config
