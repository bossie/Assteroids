#include "Asteroid.h"

#include "../world/World.h"
#include "../util/Utilities.h"

#include <boost/shared_ptr.hpp>

using vector::Vector2D;
using collision::Circle;
using boost::shared_ptr;

namespace entity {

const Asteroid::Type Asteroid::Type::NORMAL(35, 4), Asteroid::Type::MEDIUM(25, 6), Asteroid::Type::SMALL(15, 8);

Asteroid::Asteroid(const std::string & id, const Type & type, world::World & world, const Circle & shape, const Vector2D & dir, const Vector2D & vel, double omega):
    Entity(id, world, shape, dir, vel, omega),
    m_type(type) {}

const Asteroid::Type & Asteroid::type() const {
    return m_type;
}

void Asteroid::perform() {}

void Asteroid::destroy() {
    if (m_type == Type::NORMAL) {
        spawn(Type::MEDIUM, 2);
    } else if (m_type == Type::MEDIUM) {
        spawn(Type::SMALL, 2);
    }

    Entity::destroy(); // order is important because of target counting in World
}

bool Asteroid::target() const {
    return true;
}

void Asteroid::spawn(const Type & type, int number) const {
    double max = type.maxSpeed();
    double (*random)(double, double) = &util::Utilities::random;

    for (; number > 0; --number) {
        shared_ptr<Entity> smaller(new Asteroid(
            "asteroid",
            type,
            m_world,
            Circle(m_shape.center(), type.radius()),
            Vector2D::polar(1, 0),
            Vector2D::carth(random(-max, max), random(-max, max)),
            random(0, 0.2))
        );

        m_world.spawn(smaller);
    }
}

} // namespace entity
