/**
 * \file main.cpp
 * \author forlorn
 *
 * \brief Assteroids
 */

#include "exception/Exception.h"
#include "event/GameLoop.h"
#include "event/IngameKeyboardHandler.h"
#include "sdl/SDL.h"
#include "sdl/Window.h"
#include "entity/Spaceship.h"
#include "entity/Asteroid.h"
#include "entity/Bullet.h"
#include "world/World.h"
#include "config/FileProperties.h"
#include "config/Constants.h"
#include "util/Utilities.h"

#include <iostream>
#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <cstdlib>
#include <ctime>

#define TITLE "Assteroids v0.2"

using namespace event;
using namespace entity;
using namespace sdl;
using namespace config;
using boost::algorithm::ends_with;

/**
 * Prints an error message to stderr, or a default message when the reason is omitted.
 *
 * @param[in] reason the cause of the error
 */
void fatal(const std::string & reason = "unknown error") {
    std::cerr << "FATAL: " << reason << "\n";
}

void precacheImages(const Properties & settings) {
    foreach(const std::string & name, settings.names()) {
        if (ends_with(name, ".image")) {
            SDL::loadImage(settings[name], name != Constants::BACKGROUND_IMAGE);
        }
    }
}

/**
 * Gee.
 */
int main(int argc, char * argv[]) {
    std::cout << TITLE << " by forlorn\n";

    try {
        std::srand(unsigned(time(0))); // random number seed

        SDL sdl;

        char centered[] = "SDL_VIDEO_CENTERED=1";
        putenv(centered); // center the window

        boost::shared_ptr<const Properties> settings(new FileProperties(argc > 1 ? argv[1] : "settings.properties"));

        world::World world;

        boost::shared_ptr<SDL_Surface> screen(SDL::createScreen(world.width(), world.height(), 32, TITLE));
        precacheImages(*settings);
        boost::shared_ptr<SDL_Surface> background(SDL::loadImage((*settings)[Constants::BACKGROUND_IMAGE], false));

        Window window(world.width(), world.height(), screen, background, world, WidgetFactory(settings));

        GameLoop loop(world, window);
        boost::shared_ptr<KeyboardHandler> handler(new IngameKeyboardHandler(loop, world));

        loop.setKeyboardHandler(handler);
        loop.run();
   } catch (std::exception & e) {
        fatal(e.what());
        return EXIT_FAILURE;
    } catch (...) {
        fatal();
        return EXIT_FAILURE;
    }

    std::cout << "Goodbye.\n";

    return EXIT_SUCCESS;
}
