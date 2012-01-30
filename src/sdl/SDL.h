#ifndef SDL_H
#define SDL_H

#include "../util/Cache.h"

#include <log4cxx/logger.h>
#include <boost/shared_ptr.hpp>
#include <string>
extern "C" {
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
}

namespace sdl {

class SDL {
    static log4cxx::LoggerPtr m_logger;

    static Cache<std::string, boost::shared_ptr<SDL_Surface> > m_image_cache;

public:
    SDL();
    virtual ~SDL();

    /**
     * @brief Initializes a screen/window to paint in.
     *
     * @param[in] width window width
     * @param[in] height window height
     * @param[in] bpp bits per pixel
     * @param[in] title window title
     *
     * @return a pointer to the screen
     * @throw SDLException when the screen can't be initialized properly
     */
    static boost::shared_ptr<SDL_Surface> createScreen(int width, int height, int bpp, const std::string & title);

    static boost::shared_ptr<SDL_Surface> loadImage(const std::string & filename, bool alpha = true);
    static boost::shared_ptr<SDL_Surface> rotate(SDL_Surface & surface, double degrees, bool smoothing = true);
    static boost::shared_ptr<TTF_Font> loadFont(const std::string & filename, int size);
    static boost::shared_ptr<SDL_Surface> renderText(const std::string & text, TTF_Font & font, const SDL_Color & color);
    static SDL_Color toColor(const std::string & rrggbb);

private:
    static boost::shared_ptr<SDL_Surface> optimize(boost::shared_ptr<SDL_Surface> surface, bool alpha);
    static boost::shared_ptr<SDL_Surface> generate(const std::string & filename, bool alpha);

    static void freeNothing(SDL_Surface * surface) {}
    static void freeSurface(SDL_Surface * surface) { if (surface != NULL) SDL_FreeSurface(surface); }
    static void freeFont(TTF_Font * font) { if (font != NULL) TTF_CloseFont(font);}
};

} // namespace sdl;

#endif // SDL_H
