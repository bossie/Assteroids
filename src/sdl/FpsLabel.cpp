#include "FpsLabel.h"
#include "SDL.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

using boost::shared_ptr;
using std::string;

namespace sdl {

FpsLabel::FpsLabel(bool precache):
    m_model(500),

    m_font(SDL::loadFont("fonts/wendy.ttf", 16)),
    m_color(SDL::toColor("00FF00")),
    m_text(SDL::renderText("FPS: ", *m_font, m_color)) {

    if (precache) {
        for (int fps = 0; fps < 600; ++fps)
            image(fps);
    }
}

FpsLabel::~FpsLabel() {}

void FpsLabel::draw(shared_ptr<SDL_Surface> screen) {
    m_model.poke(); // poke each call to draw()

    SDL_Rect dst = {4, 4, 0, 0};
    SDL_BlitSurface(m_text.get(), NULL, screen.get(), &dst);

    dst.x += m_text->w + 4;

    int fps = int(m_model.value());
    SDL_BlitSurface(image(fps).get(), NULL, screen.get(), &dst);
}

shared_ptr<SDL_Surface> FpsLabel::generate(int fps) {
    return SDL::renderText(boost::lexical_cast<string>(fps), *m_font, m_color);
}

shared_ptr<SDL_Surface> FpsLabel::image(int fps) {
     // bind 'this' because generate is a member function
    return m_image_cache.get(fps, boost::bind(&FpsLabel::generate, this, _1));
}

} // namespace sdl
