#include "Window.h"
#include "../entity/Entity.h"
#include "../util/Utilities.h"

using world::World;
using entity::Entity;

using std::string;
using boost::shared_ptr;

namespace sdl {

log4cxx::LoggerPtr Window::m_logger(log4cxx::Logger::getLogger("Window"));

Window::Window(int width, int height, shared_ptr<SDL_Surface> screen, shared_ptr<SDL_Surface> background, World & model, const WidgetFactory & widgetFactory):
    m_screen(screen),
    m_background(background),
    m_model(model),
    m_widgetFactory(widgetFactory) {

    LOG4CXX_INFO(m_logger, "Window initialized.");
}

Window::~Window() {
    LOG4CXX_INFO(m_logger, "Window destroyed.");
}

void Window::draw(double interpolation) {
    drawBackground(m_screen);

    std::vector<shared_ptr<Entity> > entities = m_model.entities();
    foreach(shared_ptr<Entity> e, entities) {
        lookup(e)->draw(m_screen, interpolation);
    }

    fpsLabel.draw(m_screen);

    SDL_Flip(m_screen.get());
}

void Window::drawBackground(shared_ptr<SDL_Surface> screen) {
    SDL_BlitSurface(m_background.get(), NULL, screen.get(), NULL);
}

shared_ptr<Widget> Window::lookup(shared_ptr<Entity> e) {
    WidgetCache::iterator it = m_widgetCache.find(e->index());

    if (it == m_widgetCache.end()) {
        shared_ptr<Widget> widget(m_widgetFactory.create(e));
        m_widgetCache[e->index()] = widget;

        //LOG4CXX_DEBUG(m_logger, "Added Widget to cache for entity " << e->id() << " [" << e->index() << "]");

        return widget;
    }

    return it->second;
}

} // namespace sdl
