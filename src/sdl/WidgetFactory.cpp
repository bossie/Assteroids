#include "WidgetFactory.h"

#include "SpaceshipWidget.h"
#include "../entity/Spaceship.h"
#include "AsteroidWidget.h"
#include "../entity/Asteroid.h"
#include "BulletWidget.h"
#include "../entity/Bullet.h"

#include <string>
#include <stdexcept>

#define TRY_RETURN_WIDGET(ENTITY, PROPERTIES) \
    if (typeid(*e) == typeid(entity::ENTITY)) return shared_ptr<Widget>( \
        new ENTITY ## Widget(boost::dynamic_pointer_cast<const entity::ENTITY>(e), \
        PROPERTIES));

using entity::Entity;
using entity::Spaceship;
using entity::Asteroid;
using entity::Bullet;
using boost::shared_ptr;
using std::type_info;
using std::string;

namespace sdl {

WidgetFactory::WidgetFactory(boost::shared_ptr<const config::Properties> settings):
    m_settings(settings) {
}

WidgetFactory::~WidgetFactory() {}

shared_ptr<Widget> WidgetFactory::create(shared_ptr<const Entity> e) const {
    TRY_RETURN_WIDGET(Spaceship, m_settings)
    TRY_RETURN_WIDGET(Asteroid, m_settings)
    TRY_RETURN_WIDGET(Bullet, m_settings)

    throw std::invalid_argument(string("unknown type ") + typeid(*e).name());
}

} // namespace sdl
