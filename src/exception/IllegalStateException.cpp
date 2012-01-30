#include "IllegalStateException.h"

namespace exception {

IllegalStateException::IllegalStateException(const std::string & message, const std::string & where):
    Exception(message, where) {
}

} // namespace exception
