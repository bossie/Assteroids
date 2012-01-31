#ifndef ENTITY_H
#define ENTITY_H

#include "../vector/Vector2D.h"
#include "../collision/Circle.h"

#include <string>
#include <sigc++/sigc++.h>

namespace world { class World; } // can't include "../world/World.h" because of cross-referencing, I guess

namespace entity {

class Entity {
    std::string m_id;
    bool m_destroyed;

    static unsigned int m_count;
    const unsigned int m_index; // serves as both a key into a map and a z-index

    sigc::signal<void> m_signalDestroyed;

protected:
    collision::Circle m_shape;
    vector::Vector2D m_direction;
    vector::Vector2D m_velocity;
    double m_angularVelocity;

    world::World & m_world;

    virtual void perform() = 0;

public:
    Entity(const std::string & id,
           world::World & world,
           const collision::Circle & shape = collision::Circle(vector::Vector2D::carth(0, 0), 0),
           const vector::Vector2D & dir = vector::Vector2D::polar(1, 0),
           const vector::Vector2D & vel = vector::Vector2D::carth(0, 0),
           double omega = 0);

    virtual ~Entity() = 0;

    virtual void update();
    virtual void destroy();
    virtual bool destroyed() const;
    virtual bool collidesWith(const Entity & that) const;

    virtual const vector::Vector2D position() const;
    virtual double radius() const;
    virtual const vector::Vector2D direction() const;
    virtual const vector::Vector2D velocity() const;
    virtual double angularVelocity() const;

    virtual void move(const vector::Vector2D & offset);

    virtual const std::string id() const;
    virtual unsigned int index() const;
    virtual bool target() const;

    virtual sigc::signal<void> signalDestroyed() const;
};

} // namespace entity

#endif // ENTITY_H
