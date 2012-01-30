#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "../vector/Vector2D.h"

namespace entity {

class Bullet: public Entity {
    int m_ttl;

 public:
    Bullet(const std::string & id,
           world::World & world,
           const collision::Circle & shape = collision::Circle(vector::Vector2D::carth(0, 0), 0),
           const vector::Vector2D & dir = vector::Vector2D::polar(1, 0),
           const vector::Vector2D & vel = vector::Vector2D::carth(0, 0));

 protected:
    virtual void perform();
};

} // namespace entity

#endif // BULLET_H
