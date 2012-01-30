#include "Spaceship.h"
#include "Bullet.h"
#include "../world/World.h"

#include <boost/shared_ptr.hpp>

using entity::Direction;
using vector::Vector2D;
using collision::Circle;
using entity::Bullet;
using boost::shared_ptr;

namespace entity {

Spaceship::Spaceship(const std::string & id, world::World & world, const Circle & shape, const Vector2D & dir, const Vector2D & vel, double omega):
    Entity(id, world, shape, dir, vel, omega),
    m_accelerating(false),
    m_turning(0) {
}

void Spaceship::perform() {
    // acceleration/braking
    m_velocity += m_accelerating ? 1.0 * m_direction : -0.1 * m_velocity;

    // turning
	if (m_turning == &Direction::LEFT) {
		m_angularVelocity = 0.2;
	} else if (m_turning == &Direction::RIGHT) {
		m_angularVelocity = -0.2;
	} else {
		m_angularVelocity = 0;
	}
}

void Spaceship::accelerate(bool b) {
    m_accelerating = b;
}

void Spaceship::turnLeft(bool b) {
    if (!b && m_turning == &Direction::LEFT)
        m_turning = 0;

    if (b && m_turning != &Direction::LEFT)
        m_turning = &Direction::LEFT;
}

void Spaceship::turnRight(bool b) {
    if (!b && m_turning == &Direction::RIGHT)
        m_turning = 0;

    if (b && m_turning != &Direction::RIGHT)
        m_turning = &Direction::RIGHT;
}

void Spaceship::shoot() {
    shared_ptr<Entity> bullet(new Bullet("bullet", m_world, Circle(m_shape.center() + m_direction * m_shape.radius(), 6), m_direction, m_velocity + m_direction * BULLET_SPEED));

    m_world.spawn(bullet);
}

} // namespace entity
