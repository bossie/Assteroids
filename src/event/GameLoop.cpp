#include "GameLoop.h"

extern "C" {
#include <SDL/SDL.h>
}

#include <iostream>

#define CALL_MEMBER_FN(object, function) ((object).*(function))

namespace event {

log4cxx::LoggerPtr GameLoop::m_logger(log4cxx::Logger::getLogger("GameLoop"));

GameLoop::GameLoop(world::World & model, sdl::Window & view):
    m_stopped(true),
    m_paused(false),
    m_interpolation(true),
    m_model(model),
    m_view(view) {
}

GameLoop::~GameLoop() {}

void GameLoop::run() {
    const unsigned int TICKS_PER_SECOND = 25;
	const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const unsigned int MAX_FRAME_SKIP = 5; // tweak

    SDL_Event event; // every event ends up in here

    Uint32 next_tick = SDL_GetTicks();
	unsigned int loops; // how many times the model was updated without redrawing the view
	double interpolation;

	m_stopped = false;

	LOG4CXX_INFO(m_logger, "Game loop running at "<< TICKS_PER_SECOND << " Hz.");

    while (!m_stopped) {
        loops = 0;

        // SDL_GetTicks() > next_tick: model needs an update.
        // loops < MAX_FRAME_SKIP: allow an update, albeit with a frame skip.
        // while (SDL_GetTicks() > next_tick && loops < MAX_FRAME_SKIP): keep trying to update if you have to,
        // but force redraw if too many frames were skipped.
        while (SDL_GetTicks() > next_tick && loops < MAX_FRAME_SKIP) {
            if (!m_paused)
                m_model.update();

            next_tick += SKIP_TICKS;
            loops++;
        }

        if (!m_paused) {
            interpolation = m_interpolation ? double(SDL_GetTicks() + SKIP_TICKS - next_tick) / SKIP_TICKS : 0.0;
            m_view.draw(interpolation);
        }

        // handle user input
        while (SDL_PollEvent(&event) != 0) {
            handleEvent(event);
        }
	}

	LOG4CXX_INFO(m_logger, "Game loop stopped.");
}

void GameLoop::stop() {
    m_stopped = true;
}

void GameLoop::pause(bool b) {
    m_paused = b;
    LOG4CXX_INFO(m_logger, "Game loop " << (m_paused ? "paused." : "resumed."));
}

void GameLoop::togglePause() {
    pause(!m_paused);
}

void GameLoop::interpolation(bool b) {
    m_interpolation = b;
    LOG4CXX_INFO(m_logger, "Interpolation " << (m_interpolation ? "enabled." : "disabled."));
}

void GameLoop::toggleInterpolation() {
    interpolation(!m_interpolation);
}

void GameLoop::handleEvent(const SDL_Event & e) {
    switch (e.type) {
        case SDL_KEYDOWN    : handleKeyEvent(&KeyboardHandler::keyPressed, e.key); break;
        case SDL_KEYUP      : handleKeyEvent(&KeyboardHandler::keyReleased, e.key); break;

        case SDL_ACTIVEEVENT: handleFocusEvent(e.active); break;
        case SDL_QUIT       : stop(); break;

        default             : break;
    }
}

void GameLoop::handleFocusEvent(const SDL_ActiveEvent & e) {
    static const Uint8 LOST = 0;

    if ((e.state == SDL_APPINPUTFOCUS || e.state == SDL_APPACTIVE) && e.gain == LOST) {
        LOG4CXX_DEBUG(m_logger, "Window focus lost.");
        pause(true);
    }
}

void GameLoop::handleKeyEvent(keyboardHandlerCallback fn, const SDL_KeyboardEvent & e) {
    if (m_keyboardHandler != NULL)
        CALL_MEMBER_FN(*m_keyboardHandler, fn)(e);
}

void GameLoop::setKeyboardHandler(boost::shared_ptr<KeyboardHandler> handler) {
    m_keyboardHandler = handler;

    LOG4CXX_DEBUG(m_logger, "Registered keyboard handler.");
}

} // namespace event
