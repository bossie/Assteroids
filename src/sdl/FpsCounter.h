#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <log4cxx/logger.h>
#include <stdint.h>

namespace sdl {

class FpsCounter {
public:
	explicit FpsCounter(int period);
	virtual ~FpsCounter();

    virtual void poke();
	virtual double value() const;

private:
	int m_period;
	int m_frames;

	double m_fps, m_minFps, m_maxFps;
	uint32_t m_lastUpdateTime;
	uint32_t m_startTime;

	double calculateFps(int frames, int period);

	static log4cxx::LoggerPtr m_logger;
};

#endif /* FPSCOUNTER_H_ */

} // namespace sdl
