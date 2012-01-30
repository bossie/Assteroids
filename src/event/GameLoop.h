#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "KeyboardHandler.h"
#include "../world/World.h"
#include "../sdl/Window.h"

#include <boost/shared_ptr.hpp>
#include <log4cxx/logger.h>

namespace event {

class GameLoop {
    bool m_stopped;
    bool m_paused;
    bool m_interpolation;

    world::World & m_model;
    sdl::Window & m_view;

    boost::shared_ptr<KeyboardHandler> m_keyboardHandler;

    static log4cxx::LoggerPtr m_logger;

public:
    GameLoop(world::World & model, sdl::Window & view);
    virtual ~GameLoop();

    virtual void run();
    virtual void stop();

    virtual void pause(bool b);
    virtual void togglePause();

    virtual void interpolation(bool b);
    virtual void toggleInterpolation();

    virtual void setKeyboardHandler(boost::shared_ptr<KeyboardHandler> handler);

private:
    virtual void handleEvent(const SDL_Event & e);
    virtual void handleFocusEvent(const SDL_ActiveEvent & e);

    typedef void (KeyboardHandler::*keyboardHandlerCallback)(const SDL_KeyboardEvent & e);
    virtual void handleKeyEvent(keyboardHandlerCallback fn, const SDL_KeyboardEvent & e);
};

} // namespace event

#endif // GAME_LOOP_H
