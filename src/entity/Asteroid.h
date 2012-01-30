#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

namespace entity {

class Asteroid: public Entity {
 public:
    class Type;

    Asteroid(const std::string & id,
             const Type & type,
             world::World & world,
             const collision::Circle & shape = collision::Circle(vector::Vector2D::carth(0, 0), 0),
             const vector::Vector2D & dir = vector::Vector2D::polar(1, 0),
             const vector::Vector2D & vel = vector::Vector2D::carth(0, 0),
             double omega = 0);

    virtual const Type & type() const;
    virtual void destroy();

    virtual bool target() const;

    class Type {
     public:
        static const Type NORMAL, MEDIUM, SMALL;

        virtual int radius() const { return m_radius; }
        virtual double maxSpeed() const { return m_maxSpeed; }
        virtual bool operator==(const Type & that) const { return this == &that; }

     private:
        int m_radius;
        double m_maxSpeed;

        Type(int radius, double maxSpeed): m_radius(radius), m_maxSpeed(maxSpeed) {}
    };

 protected:
    virtual void perform();

 private:
    const Type & m_type;

    void spawn(const Type & type, int number) const;
};

} // namespace entity

#endif // ASTEROID_H
