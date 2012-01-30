#ifndef SPACESHIPWIDGET_H
#define SPACESHIPWIDGET_H

#include "Widget.h"
#include "../entity/Spaceship.h"
#include "../util/Cache.h"
#include "../config/Properties.h"

#include <boost/shared_ptr.hpp>
#include <map>
#include <log4cxx/logger.h>

namespace sdl {

class SpaceshipWidget: public Widget {
    boost::shared_ptr<const entity::Spaceship> m_model;
    boost::shared_ptr<SDL_Surface> m_image;

    Cache<int, boost::shared_ptr<SDL_Surface> > m_image_cache;
    boost::shared_ptr<const config::Properties> m_settings;

    static log4cxx::LoggerPtr m_logger;

public:
    SpaceshipWidget(boost::shared_ptr<const entity::Spaceship> e, boost::shared_ptr<const config::Properties> settings);
    virtual ~SpaceshipWidget();

    virtual void draw(boost::shared_ptr<SDL_Surface> screen, double interpolation = 0.0);

private:
    static double toDegrees(double radians);

    boost::shared_ptr<SDL_Surface> generate(int degrees);
};

} // namespace sdl

#endif // SPACESHIPWIDGET_H
