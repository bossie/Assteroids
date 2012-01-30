#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"
#include "WidgetFactory.h"
#include "../world/World.h"
#include "FpsLabel.h"

#include <string>
#include <boost/shared_ptr.hpp>
#include <log4cxx/logger.h>
extern "C" {
#include <SDL/SDL.h>
}
#include <map>

namespace sdl {

class Window {
    boost::shared_ptr<SDL_Surface> m_screen;
    boost::shared_ptr<SDL_Surface> m_background;

    world::World & m_model;

    typedef std::map<unsigned int, boost::shared_ptr<Widget> > WidgetCache;
    WidgetCache m_widgetCache;
    WidgetFactory m_widgetFactory;

    FpsLabel fpsLabel;

    static log4cxx::LoggerPtr m_logger;

public:
    Window(int width, int height, boost::shared_ptr<SDL_Surface> screen, boost::shared_ptr<SDL_Surface> background, world::World & model, const WidgetFactory & widgetFactory);
    virtual ~Window();

    virtual void draw(double interpolation);

private:
    void drawBackground(boost::shared_ptr<SDL_Surface> screen);
    boost::shared_ptr<Widget> lookup(boost::shared_ptr<entity::Entity> e); // const?
};

} // namespace sdl;

#endif // WINDOW_H
