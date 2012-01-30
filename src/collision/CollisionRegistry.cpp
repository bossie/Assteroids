#include "CollisionRegistry.h"

#include <sstream>
#include <functional>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/bind/placeholders.hpp>

using entity::Entity;
using std::string;
using std::stringstream;
using std::invalid_argument;
using boost::function;
using boost::bind;

namespace collision {

log4cxx::LoggerPtr CollisionRegistry::m_logger(log4cxx::Logger::getLogger("CollisionRegistry"));

/*
 * Adds a (symmetrical) collision response for two entity types A and B.
 */
void CollisionRegistry::add(const TypeInfo & A, const TypeInfo & B, CollisionFunction response) {
    if (response == 0)
        throw invalid_argument("response cannot be 0");

    m_hitmap[std::make_pair(A, B)] = bind(response, _1, _2); // the regular one
    m_hitmap[std::make_pair(B, A)] = bind(response, _2, _1); // two types reversed

    LOG4CXX_DEBUG(m_logger, "Registered symmetrical collision response for [" << A.id() << ", " << B.id() << "]");
}

/*
 * Returns the appropriate collision response for the specified pair of entities, or 0 if none is found.
 */
const CollisionResponse CollisionRegistry::lookUp(const Entity & a, const Entity & b) const {
    hitmap::const_iterator it = m_hitmap.find(std::make_pair(TypeInfo(typeid(a)), TypeInfo(typeid(b))));

    return it != m_hitmap.end() ? it->second : 0;
}

/*
 * Returns a list of registered collision responses.
 */
const string CollisionRegistry::toString() const {
    stringstream out;

    for (hitmap::const_iterator it = m_hitmap.begin(); it != m_hitmap.end();) {
        out << "[" << it->first.first.id() << ", " << it->first.second.id() << "]";

        if (++it != m_hitmap.end())
            out << "\n";
    }

    return out.str();
}

} // namespace collision
