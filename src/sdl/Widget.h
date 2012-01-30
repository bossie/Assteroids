#ifndef WIDGET_H
#define WIDGET_H

#include "../vector/Vector2D.h"
#include "../entity/Entity.h"

#include <boost/shared_ptr.hpp>
extern "C" {
#include <SDL/SDL.h>
}

namespace sdl {

class Widget {
public:
    virtual ~Widget() = 0;

    virtual void draw(boost::shared_ptr<SDL_Surface> screen, double interpolation) = 0; // non-const

protected:
    virtual bool dimensionsMatch(boost::shared_ptr<SDL_Surface> image, boost::shared_ptr<const entity::Entity> model) const;
};

} // namespace sdl

#endif // WIDGET_H
