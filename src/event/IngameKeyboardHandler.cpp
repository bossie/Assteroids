#include "IngameKeyboardHandler.h"
#include "GameLoop.h"
#include "../world/World.h"

#include <iostream>

namespace event {

IngameKeyboardHandler::IngameKeyboardHandler(GameLoop & gameLoop, world::World & world):
    m_gameLoop(gameLoop),
    m_world(world) {
}

void IngameKeyboardHandler::keyPressed(const SDL_KeyboardEvent & e) {
    switch (e.keysym.sym) {
        // spaceship controls
        case SDLK_UP        : m_world.accelerate(true); break;
        case SDLK_LEFT      : m_world.turnLeft(true); break;
        case SDLK_RIGHT     : m_world.turnRight(true); break;
        case SDLK_SPACE     : m_world.shoot(); break;

        // quit
        case SDLK_ESCAPE    :
        case SDLK_q         : m_gameLoop.stop(); break;

        // pause/unpause
        case SDLK_p         : m_gameLoop.togglePause(); break;

        // toggle interpolation
        case SDLK_i         : m_gameLoop.toggleInterpolation(); break;

        default: break;
    }
}

void IngameKeyboardHandler::keyReleased(const SDL_KeyboardEvent & e) {
    switch (e.keysym.sym) {
        // spaceship controls
        case SDLK_UP        : m_world.accelerate(false); break;
        case SDLK_LEFT      : m_world.turnLeft(false); break;
        case SDLK_RIGHT     : m_world.turnRight(false); break;

        default: break;
    }
}
} // namespace event
