#ifndef BULLETWIDGET_H
#define BULLETWIDGET_H

#include "Widget.h"
#include "../entity/Bullet.h"
#include "../config/Properties.h"

#include <boost/shared_ptr.hpp>
#include <map>
#include <log4cxx/logger.h>

namespace sdl {

class BulletWidget: public Widget {
    boost::shared_ptr<const entity::Bullet> m_model;
    boost::shared_ptr<SDL_Surface> m_image;

    boost::shared_ptr<const config::Properties> m_settings;

    static log4cxx::LoggerPtr m_logger;

public:
    BulletWidget(boost::shared_ptr<const entity::Bullet> e, boost::shared_ptr<const config::Properties> settings);
    virtual ~BulletWidget();

    virtual void draw(boost::shared_ptr<SDL_Surface> screen, double interpolation = 0.0);
};

} // namespace sdl

#endif // BULLETWIDGET_H
