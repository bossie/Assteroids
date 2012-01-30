#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

extern "C" {
#include <SDL/SDL.h>
}

namespace event {

class KeyboardHandler {
public:
    virtual ~KeyboardHandler() = 0;

    virtual void keyPressed(const SDL_KeyboardEvent & e) = 0;
    virtual void keyReleased(const SDL_KeyboardEvent & e) = 0;
};

} // namespace event

#endif // KEYBOARD_HANDLER_H
