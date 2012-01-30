#include "BulletWidget.h"
#include "SDL.h"
#include "../config/Constants.h"

#include <iostream>
#include <cmath>
#include <boost/bind.hpp>

using boost::shared_ptr;
using entity::Bullet;
using sdl::SDL;
using vector::Vector2D;
using config::Properties;
using config::Constants;

namespace sdl {

log4cxx::LoggerPtr BulletWidget::m_logger(log4cxx::Logger::getLogger("BulletWidget"));

BulletWidget::BulletWidget(shared_ptr<const Bullet> e, shared_ptr<const Properties> settings):
    m_model(e),
    m_image(SDL::loadImage((*settings)[Constants::BULLET_IMAGE])),
    m_settings(settings) {

    if (!dimensionsMatch(m_image, m_model))
        LOG4CXX_WARN(m_logger, "Dimensions don't match.");
}

BulletWidget::~BulletWidget() {}

void BulletWidget::draw(shared_ptr<SDL_Surface> screen, double interpolation) {
    shared_ptr<SDL_Surface> & image(m_image);

    const Vector2D & p(m_model->position());
    const Vector2D & v(m_model->velocity());

    SDL_Rect dst = {
        int(p.x() + v.x() * interpolation) + screen->w/2 - image->w/2,
        screen->h/2 - int(p.y() + v.y() * interpolation) - image->h/2,
        0, // ignored by SDL_BlitSurface
        0  // ditto
    };

    SDL_BlitSurface(image.get(), NULL, screen.get(), &dst);
}

} // namespace sdl
