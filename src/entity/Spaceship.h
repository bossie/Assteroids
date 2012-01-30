#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Entity.h"
#include "Direction.h"

namespace entity {

class Spaceship: public Entity {
    bool m_accelerating;
    const Direction * m_turning;

    static const double BULLET_SPEED = 16;

public:
    Spaceship(const std::string & id,
              world::World & world,
              const collision::Circle & shape = collision::Circle(vector::Vector2D::carth(0, 0), 0),
              const vector::Vector2D & dir = vector::Vector2D::polar(1, 0),
              const vector::Vector2D & vel = vector::Vector2D::carth(0, 0),
              double omega = 0.0);

    virtual void accelerate(bool b);
    virtual void turnLeft(bool b);
    virtual void turnRight(bool b);

    virtual void shoot();

protected:
    virtual void perform();

private:
    static const double MAX_SPEED = 5.0;
};

} // namespace entity

#endif // SPACESHIP_H
