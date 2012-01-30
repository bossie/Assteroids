#ifndef ASTEROIDWIDGET_H
#define ASTEROIDWIDGET_H

#include "Widget.h"
#include "../entity/Asteroid.h"
#include "../util/Cache.h"
#include "../config/Properties.h"

#include <boost/shared_ptr.hpp>
#include <map>
#include <log4cxx/logger.h>

namespace sdl {

class AsteroidWidget: public Widget {
    boost::shared_ptr<const entity::Asteroid> m_model;
    boost::shared_ptr<SDL_Surface> m_image;

    Cache<int, boost::shared_ptr<SDL_Surface> > m_image_cache;

    boost::shared_ptr<const config::Properties> m_settings;

    static log4cxx::LoggerPtr m_logger;

public:
    AsteroidWidget(boost::shared_ptr<const entity::Asteroid> e, boost::shared_ptr<const config::Properties> settings);
    virtual ~AsteroidWidget();

    virtual void draw(boost::shared_ptr<SDL_Surface> screen, double interpolation = 0.0);

private:
    static double toDegrees(double radians);

    boost::shared_ptr<SDL_Surface> generate(int degrees);
    boost::shared_ptr<SDL_Surface> getImage(int degrees);
};

} // namespace sdl

#endif // ASTEROIDWIDGET_H
