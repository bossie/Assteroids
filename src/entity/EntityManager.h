#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../collision/CollisionRegistry.h"
#include "../vector/Vector2D.h"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace entity {

using collision::CollisionRegistry;

typedef std::vector<boost::shared_ptr<Entity> > EntityList;

class EntityManager {
    vector::Vector2D m_upperLeft, m_lowerRight;

    EntityList m_entities, m_destroyed;

    CollisionRegistry m_registry;

public:
    EntityManager(const CollisionRegistry & registry, const vector::Vector2D & upperLeft, const vector::Vector2D & lowerRight);

    void add(boost::shared_ptr<Entity> e);
    void update();

    const EntityList entities() const;
    const EntityList destroyed() const;

private:
    void updateEntities();
    void removeDestroyed();
    void resolveCollisions();

    static bool destroyed(boost::shared_ptr<Entity> & e) { return e->destroyed(); }
    void wrapAround(Entity & e);

    static void spaceshipAsteroid(Entity & a, Entity & b);
    static void bulletAsteroid(Entity & a, Entity & b);
};

} // namespace entity

#endif // ENTITY_MANAGER_H
