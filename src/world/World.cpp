#include "World.h"
#include "../entity/Asteroid.h"
#include "../entity/Bullet.h"
#include "../vector/Vector2D.h"
#include "../util/Utilities.h"

#include <cmath>

using entity::Entity;
using entity::Spaceship;
using entity::Asteroid;
using entity::Bullet;

using vector::Vector2D;
using collision::Circle;
using util::Utilities;

using boost::shared_ptr;

namespace world {

log4cxx::LoggerPtr World::m_logger(log4cxx::Logger::getLogger("World"));

World::World():
    m_entityManager(m_collisionRegistry, Vector2D::carth(-320, 240), Vector2D::carth(320, -240)),
    m_player(new Spaceship("player", *this, Circle(Vector2D::carth(-300, 0), 25))),
    m_targetCount(0) {

    spawn(boost::dynamic_pointer_cast<Entity>(m_player));

    for (int i = 0; i < 3; ++i)
        spawnAsteroid();
}

World::~World() {}

int World::width() const {
    return WIDTH;
}

int World::height() const {
    return HEIGHT;
}

void World::update() {
    m_entityManager.update();
}

const std::vector<shared_ptr<Entity> > World::entities() {
    std::vector<shared_ptr<Entity> > active(m_entityManager.entities());
    std::sort(active.begin(), active.end(), &sortByIndex);
    return active;
}

void World::accelerate(bool b) {
    m_player->accelerate(b);
}

void World::turnLeft(bool b) {
    m_player->turnLeft(b);
}

void World::turnRight(bool b) {
    m_player->turnRight(b);
}

void World::shoot() {
    m_player->shoot();
}

void World::spawnAsteroid() {
    double (*random)(double, double) = &util::Utilities::random;

    Vector2D pos = Vector2D::carth(random(-320, 320), random(-240, 240));
    Vector2D dir = Vector2D::polar(1, random(0, 2 * M_PI));
    Vector2D vel = Vector2D::carth(random(-4, 4), random(-4, 4));
    double omega = random(-0.25, 0.25);

    shared_ptr<Entity> asteroid(new Asteroid("asteroid", Asteroid::Type::NORMAL, *this, Circle(pos, 25), dir, vel, omega));

    spawn(asteroid);
}

void World::spawn(shared_ptr<Entity> e) {
    m_entityManager.add(e);

    if (e->target())
        ++m_targetCount;
}

void World::destroy(const Entity & e) {
    if (&e == m_player.get()) {
        LOG4CXX_INFO(m_logger, "GAME OVER");
    } else if (e.target() && --m_targetCount == 0) { // short-circuit evaluation
        LOG4CXX_INFO(m_logger, "WINNER!");
    }
}

} // namespace world
