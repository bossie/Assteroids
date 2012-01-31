#include "EntityManager.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "../util/erase_if.h"

#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/bind/placeholders.hpp>
#include <boost/foreach.hpp>
#include <iostream>

using collision::CollisionResponse;
using vector::Vector2D;

using std::remove_if;
using boost::shared_ptr;
using boost::bind;
using boost::mem_fn;

#define foreach BOOST_FOREACH

namespace entity {

/*
 * Constructor.
 */
EntityManager::EntityManager(const CollisionRegistry & registry, const Vector2D & upperLeft, const Vector2D & lowerRight):
    m_upperLeft(upperLeft),
    m_lowerRight(lowerRight),
    m_registry(registry) {

    m_registry.add(typeid(Spaceship), typeid(Asteroid), &spaceshipAsteroid);
    m_registry.add(typeid(Bullet), typeid(Asteroid), &bulletAsteroid);
}

void EntityManager::add(boost::shared_ptr<Entity> e) {
    m_entities.push_back(e);
}

/*
 * Updates the model (update entities, resolve collisions, remove destroyed entities).
 */
void EntityManager::update() {
    updateEntities();
    resolveCollisions();
    removeDestroyed(); // last because destruction is most likely a result of a collision (but not always)
}

/*
 * Returns the list of active entities.
 */
const EntityList EntityManager::entities() const {
    return m_entities;
}

/*
 * Returns the list of destroyed entities.
 */
const EntityList EntityManager::destroyed() const {
    return m_destroyed;
}

/*
 * Updates all active entities.
 */
void EntityManager::updateEntities() {
    foreach(shared_ptr<Entity> & e, m_entities) {
        e->update();
        wrapAround(*e);
    }
}

/*
 * Copies destroyed entities into a separate list, then removes them from the original list.
 */
void EntityManager::removeDestroyed() {
    m_destroyed.clear();

    copy(find_if(m_entities.begin(), m_entities.end(), mem_fn(&Entity::destroyed)), m_entities.end(), back_inserter(m_destroyed));

    erase_if(m_entities, mem_fn(&Entity::destroyed));
}

/*
 * Tests all entities against all other entities for collisions, then calls the appropriate collision response.
 */
void EntityManager::resolveCollisions() {
    if (m_entities.size() > 1) {
        for (EntityList::size_type i = 0; i < m_entities.size() - 1; ++i) {
            Entity & a = *m_entities[i];

            // skip this one because removal of destroyed entities happens after collision detection,
            // but there are other reasons for destruction (e.g. a disappearing power-up)
            if (a.destroyed())
                continue;

            for (EntityList::size_type j = i + 1; j < m_entities.size(); ++j) {
                Entity & b = *m_entities[j];

                // if spaceship a collides with asteroids b and c at the same time, collision(a, b) will destroy a,
                // but collision(a, c) will still be considered unless we check for a's destruction again
                if (a.destroyed() || b.destroyed())
                    continue;

                if (a.collidesWith(b)) { // hit!
                    CollisionResponse response = m_registry.lookUp(a, b);

                    if (response != 0)
                        response(a, b); // boom!
                }
            }
        }
    }
}

void EntityManager::wrapAround(Entity & e) {
    if (e.position().x() < m_upperLeft.x() - e.radius()) e.move(Vector2D::carth(m_lowerRight.x() - m_upperLeft.x() + 2 * e.radius(), 0)); // warp to right
    if (e.position().x() > m_lowerRight.x() + e.radius()) e.move(Vector2D::carth(m_upperLeft.x() - m_lowerRight.x() - 2 * e.radius(), 0)); // warp to left
    if (e.position().y() > m_upperLeft.y() + e.radius()) e.move(Vector2D::carth(0, m_lowerRight.y() - m_upperLeft.y() - 2 * e.radius())); // warp to bottom
    if (e.position().y() < m_lowerRight.y() - e.radius()) e.move(Vector2D::carth(0, m_upperLeft.y() - m_lowerRight.y() + 2 * e.radius())); // warp to top
}

void EntityManager::spaceshipAsteroid(Entity & a, Entity & b) {
    a.destroy();
}

void EntityManager::bulletAsteroid(Entity & a, Entity & b) {
    a.destroy();
    b.destroy();
}

} // namespace entity
