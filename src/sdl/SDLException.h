#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H

#include "../exception/Exception.h"

namespace sdl {

class SDLException: public exception::Exception {
public:
    SDLException(const std::string & message, const std::string & where = "");
};

} // namespace sdl

#endif // SDL_EXCEPTION_H
