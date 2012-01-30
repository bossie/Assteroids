#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define HERE __FILE__ ":" TOSTRING(__LINE__)

namespace exception {

class Exception: public std::exception {
    std::string m_message;
    std::string m_where;

public:
	Exception(const std::string & message, const std::string & where = "");
	virtual ~Exception() throw ();

	virtual const char * what() const throw();
};

} // namespace exception

#endif // EXCEPTION_H
