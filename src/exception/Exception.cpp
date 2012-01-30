#include "Exception.h"

namespace exception {

Exception::Exception(const std::string & message, const std::string & where):
    m_message(message),
    m_where(where) {
}

Exception::~Exception() throw () {}

const char * Exception::what() const throw() {
    return (m_message + (!m_where.empty() ? " at " + m_where : "")).c_str();
}

} // namespace exception
