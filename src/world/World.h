#ifndef WORLD_H
#define WORLD_H

#include "../entity/Spaceship.h"
#include "../entity/EntityManager.h"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace world {

class World {
    collision::CollisionRegistry m_collisionRegistry;
    entity::EntityManager m_entityManager;
    boost::shared_ptr<entity::Spaceship> m_player;

    int m_targetCount;

    static const int WIDTH = 640;
    static const int HEIGHT = 480;

    static log4cxx::LoggerPtr m_logger;

public:
    World();
    virtual ~World();

    virtual int width() const;
    virtual int height() const;

    virtual void update();
    virtual const std::vector<boost::shared_ptr<entity::Entity> > entities();

    virtual void accelerate(bool b);
    virtual void turnLeft(bool b);
    virtual void turnRight(bool b);
    virtual void shoot();

    virtual void spawn(boost::shared_ptr<entity::Entity> e); // to spawn new entities
    virtual void onPlayerDestroyed();
    virtual void onTargetDestroyed();

private:
    virtual void spawnAsteroid();
    static bool sortByIndex(boost::shared_ptr<entity::Entity> a, boost::shared_ptr<entity::Entity> b) { return a->index() < b->index(); }
};

} // namespace world

#endif // WORLD_H
