#include <SDL/SDL.h>
#include "FpsCounter.h"

namespace sdl {

log4cxx::LoggerPtr FpsCounter::m_logger(log4cxx::Logger::getLogger("FpsCounter"));

FpsCounter::FpsCounter(int period):
	m_period(period),
	m_frames(0),
	m_fps(0.0),
	m_minFps(0.0),
	m_maxFps(0.0),
	m_lastUpdateTime(SDL_GetTicks()),
	m_startTime(m_lastUpdateTime){

	LOG4CXX_DEBUG(m_logger, "FPS counter initialized with a period of " << period << " ms.");
}

FpsCounter::~FpsCounter() {
	LOG4CXX_DEBUG(m_logger, "Minimum FPS " << m_minFps << ", maximum FPS " << m_maxFps << ".");
}

void FpsCounter::poke() {
	++m_frames;

    uint32_t currentTime = SDL_GetTicks();

	if (currentTime >= m_lastUpdateTime + m_period) { // time for an update
		m_fps = calculateFps(m_frames, currentTime - m_lastUpdateTime); // actual delta

		if (m_fps < m_minFps || m_minFps == 0.0)
            m_minFps = m_fps;

        if (m_fps > m_maxFps)
            m_maxFps = m_fps;

		m_frames = 0;
		m_lastUpdateTime = currentTime;
	}
}

double FpsCounter::value() const {
    return m_fps;
}

double FpsCounter::calculateFps(int frames, int period) {
	return double(frames) / period * 1000; // period is in ms
}

} // namespace sdl
