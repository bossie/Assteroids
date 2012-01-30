#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string>

namespace config {

class Constants {
 public:
    static const std::string BACKGROUND_IMAGE;

    static const std::string FPS_FONT;
    static const std::string FPS_FONT_SIZE;
    static const std::string FPS_PRECACHE;
    static const std::string FPS_UPDATE_PERIOD;

    static const std::string SPACESHIP_IMAGE;

    static const std::string ASTEROID_BIG_IMAGE;
    static const std::string ASTEROID_MEDIUM_IMAGE;
    static const std::string ASTEROID_SMALL_IMAGE;

    static const std::string BULLET_IMAGE;
};

} // namespace config

#endif // CONSTANTS_H_INCLUDED
