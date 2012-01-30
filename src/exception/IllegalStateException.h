#ifndef ILLEGAL_STATE_EXCEPTION_H
#define ILLEGAL_STATE_EXCEPTION_H

#include "Exception.h"

namespace exception {

class IllegalStateException: public Exception {
public:
    IllegalStateException(const std::string & message, const std::string & where = "");
};

} // namespace exception

#endif // ILLEGAL_STATE_EXCEPTION_H
