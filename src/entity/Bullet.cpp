#include "Bullet.h"

using vector::Vector2D;
using collision::Circle;

namespace entity {

Bullet::Bullet(const std::string & id, world::World & world, const Circle & shape, const Vector2D & dir, const Vector2D & vel):
    Entity(id, world, shape, dir, vel),
    m_ttl(10) {}

void Bullet::perform() {
    if (m_ttl-- == 0)
        destroy();
}

} // namespace entity
