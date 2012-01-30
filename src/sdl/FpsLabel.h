#ifndef FPSWIDGET_H
#define FPSWIDGET_H

#include "FpsCounter.h"
#include "../util/Cache.h"

#include <boost/shared_ptr.hpp>
extern "C" {
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
}

namespace sdl {

class FpsLabel {
    FpsCounter m_model;

    boost::shared_ptr<TTF_Font> m_font;
    SDL_Color m_color;
    boost::shared_ptr<SDL_Surface> m_text;

    Cache<int, boost::shared_ptr<SDL_Surface> > m_image_cache;

public:
    explicit FpsLabel(bool precache = true);
    virtual ~FpsLabel();

    virtual void draw(boost::shared_ptr<SDL_Surface> screen);

private:
    boost::shared_ptr<SDL_Surface> generate(int fps);
    boost::shared_ptr<SDL_Surface> image(int fps);
};

} // namespace sdl

#endif // FPSWIDGET_H
