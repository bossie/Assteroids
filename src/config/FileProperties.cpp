#include "FileProperties.h"
#include "PropertiesException.h"

#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../util/Utilities.h"
#include <sstream>

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::set;
using boost::trim_copy;

namespace config {

log4cxx::LoggerPtr FileProperties::m_logger(log4cxx::Logger::getLogger("FileProperties"));

FileProperties::FileProperties(const string & filename):
    m_props(parse(lines(filename))) {

    LOG4CXX_DEBUG(m_logger, "Read properties file " << filename << " successfully.");
}

FileProperties::~FileProperties() {}

const string FileProperties::operator[](const string & property) const {
	std::map<std::string, std::string>::const_iterator it = m_props.find(property);

	if (it != m_props.end())
        return it->second;

    throw PropertiesException(string("no value found for property ") + property + " at " + HERE);
}

const set<string> FileProperties::names() const {
    set<string> names;

    pair<string, string> p; // BOOST_FOREACH pitfall
    foreach(p, m_props)
        names.insert(p.first);

    return names;
}

vector<string> FileProperties::lines(const string & filename) const {
    std::ifstream in(filename.c_str());

	if (!in.good())
		throw PropertiesException(string("file ") + filename + " could not be read at " + HERE);

    vector<string> lines;

	for (string line; !in.eof();) {
		getline(in, line);
		lines.push_back(line);
    }

    return lines;
}

map<string, string> FileProperties::parse(const vector<string> & lines) const {
    map<string, string> result;

    foreach(string line, lines) {
        string trimmed = trim_copy(line);

        if (trimmed.length() > 0 && trimmed[0] != '#') { // empty lines and comments are ignored
			string::size_type pos = trimmed.find('=');

			if (pos == string::npos || pos == 0) { // not found or line starting with '='
				throw PropertiesException("invalid line: " + line + " at " + HERE);
			}

			string key = trim_copy(trimmed.substr(0, pos));
			string value = "";

			string::size_type next_pos = pos + 1;
			if (next_pos < trimmed.length()) { // values can be empty
				value = trim_copy(trimmed.substr(next_pos, trimmed.length() - key.length() - 1));
			}

			result.insert(make_pair(key, value));
		}
    }

    return result;
}

} // namespace config
