#include "Widget.h"

namespace sdl {

Widget::~Widget() {}

bool Widget::dimensionsMatch(boost::shared_ptr<SDL_Surface> image, boost::shared_ptr<const entity::Entity> model) const {
    int halfWidth = image->w / 2;
    int halfHeight = image->h / 2;
    double r = model->radius();

    return 0.5 * r < halfWidth && halfWidth < 1.5 * r && 0.5 * r < halfHeight && halfHeight < 1.5 * r;
}

} // namespace sdl
