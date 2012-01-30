#ifndef FILE_PROPERTIES_H
#define FILE_PROPERTIES_H

#include "Properties.h"

#include <map>
#include <vector>
#include <string>
#include <log4cxx/logger.h>

namespace config {

class FileProperties: public Properties {
    std::map<std::string, std::string> m_props;

    static log4cxx::LoggerPtr m_logger;

public:
    /**
     * Instantiates a new Properties object by parsing the specified file.
     */
    FileProperties(const std::string & filename);
    virtual ~FileProperties(); // dtor

    /**
     * Returns a property value with the specified name.
     */
    virtual const std::string operator[](const std::string & property) const;

    /**
     * Returns the names of the properties.
     */
    virtual const std::set<std::string> names() const;

private:
    /**
     * Reads lines from a text file into a vector of strings.
     */
    std::vector<std::string> lines(const std::string & filename) const;

    /**
    * Parses a list of lines and returns them as a collection of key/value pairs.
    */
    std::map<std::string, std::string> parse(const std::vector<std::string> & lines) const;
};

} // namespace config

#endif // FILE_PROPERTIES_H
