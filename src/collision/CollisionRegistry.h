#ifndef COLLISION_REGISTRY_H
#define COLLISION_REGISTRY_H

#include "../entity/Entity.h"
#include "TypeInfo.h"

#include <map>
#include <string>
#include <stdexcept>
#include <boost/function.hpp>
#include <log4cxx/logger.h>

namespace collision {

typedef void (* CollisionFunction)(entity::Entity &, entity::Entity &);
typedef boost::function<void (entity::Entity &, entity::Entity &)> CollisionResponse;
typedef std::map<std::pair<TypeInfo, TypeInfo>, CollisionResponse> hitmap;

class CollisionRegistry {
    hitmap m_hitmap;

    static log4cxx::LoggerPtr m_logger;

public:
    void add(const TypeInfo & A, const TypeInfo & B, CollisionFunction response); // "register" is a reserved word! Craaaaap
    const CollisionResponse lookUp(const entity::Entity & a, const entity::Entity & b) const;

    const std::string toString() const;
};

} // namespace collision

#endif // COLLISION_REGISTRY_H
