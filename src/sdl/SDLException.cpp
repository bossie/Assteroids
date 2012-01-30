#include "SDLException.h"

namespace sdl {

SDLException::SDLException(const std::string & message, const std::string & where):
    Exception(message, where) {
}

} // namespace sdl
