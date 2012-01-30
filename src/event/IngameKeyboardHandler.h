#ifndef INGAME_KEYBOARD_HANDLER_H
#define INGAME_KEYBOARD_HANDLER_H

#include "KeyboardHandler.h"
#include "GameLoop.h"

namespace event {

class IngameKeyboardHandler: public KeyboardHandler {
    GameLoop & m_gameLoop;
    world::World m_world;

public:
    explicit IngameKeyboardHandler(GameLoop & loop, world::World & w);

    virtual void keyPressed(const SDL_KeyboardEvent & e);
    virtual void keyReleased(const SDL_KeyboardEvent & e);
};

} // namespace event

#endif // INGAME_KEYBOARD_HANDLER_H
