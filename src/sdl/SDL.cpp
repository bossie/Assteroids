#include "SDL.h"
#include "SDLException.h"

extern "C" {
#include <SDL/SDL_image.h>
#include "SDL/SDL_rotozoom.h"
}

#include <string>
#include <stdexcept>
#include <boost/bind.hpp>

using boost::shared_ptr;
using std::string;

namespace sdl {

Cache<std::string, boost::shared_ptr<SDL_Surface> > SDL::m_image_cache;
log4cxx::LoggerPtr SDL::m_logger(log4cxx::Logger::getLogger("SDL"));

SDL::SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw SDLException(SDL_GetError(), HERE);

    LOG4CXX_INFO(m_logger, "SDL initialized.");

    if (TTF_Init() < 0)
        throw SDLException(SDL_GetError(), HERE);

    LOG4CXX_INFO(m_logger, "SDL_ttf initialized.");
}

SDL::~SDL() {
    TTF_Quit();
    LOG4CXX_INFO(m_logger, "SDL_ttf destroyed.");

    SDL_Quit();
    LOG4CXX_INFO(m_logger, "SDL destroyed.");
}

/**
 * @details Width, height and bits per pixel must be positive integers. Ownership to the screen is transferred
 * to a smart pointer so there is no need to delete it manually.
 */
shared_ptr<SDL_Surface> SDL::createScreen(int width, int height, int bpp, const std::string & title) {
    shared_ptr<SDL_Surface> s(SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE), &freeNothing);

    if (s == NULL)
        throw SDLException(SDL_GetError(), HERE);

    // window title
    SDL_WM_SetCaption(title.c_str(), title.c_str());

    LOG4CXX_INFO(m_logger, "Screen [" << title << "] set to " << width << "x" << height << " at " << bpp << " bpp.");

    return s;
}

shared_ptr<SDL_Surface> SDL::loadImage(const std::string & filename, bool alpha) {
    return m_image_cache.get(filename, boost::bind(&SDL::generate, _1, alpha));
}

shared_ptr<SDL_Surface> SDL::rotate(SDL_Surface & surface, double degrees, bool smoothing) {
    shared_ptr<SDL_Surface> image(
        rotozoomSurface(&surface, degrees, 1, smoothing ? SMOOTHING_ON : SMOOTHING_OFF), &freeSurface);

    if (image == NULL)
        throw SDLException(IMG_GetError(), HERE);

    return image;
}

shared_ptr<TTF_Font> SDL::loadFont(const string & filename, int size) {
    if (size < 0)
        throw std::invalid_argument("invalid font size");

	shared_ptr<TTF_Font> loadedFont(TTF_OpenFont(filename.c_str(), size), freeFont);

	if (loadedFont == NULL)
		throw SDLException(string("font ") + filename + " could not be loaded: " + SDL_GetError());

	return loadedFont;
}

shared_ptr<SDL_Surface> SDL::renderText(const string & text, TTF_Font & font, const SDL_Color & color) {
	shared_ptr<SDL_Surface> renderedText(TTF_RenderText_Solid(&font, text.c_str(), color), &freeSurface);

	if (renderedText == NULL)
			throw SDLException(string("text \"") + text + "\" could not be rendered: " + SDL_GetError());

	return renderedText;
}

SDL_Color SDL::toColor(const std::string & s) {
	if (s.length() != 6)
		throw std::invalid_argument(s + " is not a valid color string");

	unsigned int rgb[3];

	for (int i = 0; i < 3; ++i) {
		if (sscanf(s.substr(i * 2, 2).c_str(), "%x", &rgb[i]) != 1) {
			throw std::invalid_argument(s + " is not a valid color string");
		}
	}

	SDL_Color color = {rgb[0], rgb[1], rgb[2], 0};

	LOG4CXX_DEBUG(m_logger, "Parsed string " << s << " to RGB values (" << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << ").");

	return color;
}

shared_ptr<SDL_Surface> SDL::optimize(shared_ptr<SDL_Surface> surface, bool alpha) {
    return alpha ?
        shared_ptr<SDL_Surface>(SDL_DisplayFormatAlpha(surface.get()), &freeSurface) :
        shared_ptr<SDL_Surface>(SDL_DisplayFormatAlpha(surface.get()), &freeSurface);
}

shared_ptr<SDL_Surface> SDL::generate(const string & filename, bool alpha) {
    shared_ptr<SDL_Surface> image(IMG_Load(filename.c_str()), &freeSurface);

    if (image == NULL)
        throw SDLException(IMG_GetError(), HERE);

    shared_ptr<SDL_Surface> optimizedImage(optimize(image, alpha));

    if (optimizedImage == NULL)
        throw SDLException(IMG_GetError(), HERE);

    Uint32 flags = SDL_RLEACCEL;
    if (alpha)
        flags |= SDL_SRCALPHA;

    SDL_SetAlpha(optimizedImage.get(), flags, SDL_ALPHA_OPAQUE); // doubles the fps :o

    LOG4CXX_DEBUG(m_logger, "Image at " << filename << " loaded successfully. Alpha blending is " << (alpha ? "enabled." : "disabled."));

    return optimizedImage;
}

} // namespace sdl
