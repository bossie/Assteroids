#include "SpaceshipWidget.h"
#include "SDL.h"
#include "../config/Constants.h"

#include <iostream>
#include <cmath>
#include <boost/bind.hpp>

using boost::shared_ptr;
using entity::Spaceship;
using sdl::SDL;
using vector::Vector2D;
using config::Properties;
using config::Constants;

namespace sdl {

log4cxx::LoggerPtr SpaceshipWidget::m_logger(log4cxx::Logger::getLogger("SpaceshipWidget"));

SpaceshipWidget::SpaceshipWidget(shared_ptr<const Spaceship> e, shared_ptr<const Properties> settings):
    m_model(e),
    m_image(SDL::loadImage((*settings)[Constants::SPACESHIP_IMAGE])),
    m_settings(settings) {

    if (!dimensionsMatch(m_image, m_model))
        LOG4CXX_WARN(m_logger, "Dimensions don't match.");
}

SpaceshipWidget::~SpaceshipWidget() {}

void SpaceshipWidget::draw(shared_ptr<SDL_Surface> screen, double interpolation) {
    int degrees = int(toDegrees(m_model->direction().angle() + m_model->angularVelocity() * interpolation));

    shared_ptr<SDL_Surface> image(generate(degrees));

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

// TODO: move this somewhere else
double SpaceshipWidget::toDegrees(double radians) {
    double degrees = radians * 180 / M_PI;

    if (degrees < 0)
        degrees += 360;

    return degrees;
}

shared_ptr<SDL_Surface> SpaceshipWidget::generate(int degrees) {
    // nice
    return m_image_cache.get(degrees, boost::bind(&SDL::rotate, boost::ref(*m_image), _1, true));
}

} // namespace sdl
