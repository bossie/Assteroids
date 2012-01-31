#include "Entity.h"
#include "../world/World.h"

#include <typeinfo>

namespace entity {

using std::string;
using vector::Vector2D;
using collision::Circle;
using world::World;
using sigc::signal;

unsigned int Entity::m_count = 0;

Entity::Entity(const string & id, World & world, const Circle & shape, const Vector2D & dir, const Vector2D & vel, double omega):
    m_id(id),
    m_destroyed(false),
    m_index(m_count++),
    m_shape(shape),
    m_direction(dir),
    m_velocity(vel),
    m_angularVelocity(omega),
    m_world(world) {}

Entity::~Entity() {}

void Entity::update() {
    m_direction = m_direction.rotate(m_angularVelocity).unit();
    m_shape.move(m_velocity);
    perform();
}

void Entity::destroy() {
    m_destroyed = true;
    m_signalDestroyed.emit();
}

bool Entity::destroyed() const {
    return m_destroyed;
}

bool Entity::collidesWith(const Entity & that) const {
    return this->m_shape.overlaps(that.m_shape);
}

const Vector2D Entity::position() const {
    return m_shape.center();
}

double Entity::radius() const {
    return m_shape.radius();
}

const Vector2D Entity::direction() const {
    return m_direction;
}

const Vector2D Entity::velocity() const {
    return m_velocity;
}

double Entity::angularVelocity() const {
    return m_angularVelocity;
}

void Entity::move(const vector::Vector2D & offset) {
    m_shape.move(offset);
}

const string Entity::id() const {
    return m_id;
}

unsigned int Entity::index() const {
    return m_index;
}

bool Entity::target() const {
    return false;
}

signal<void> Entity::signalDestroyed() const {
    return m_signalDestroyed;
}

} // namespace entity
