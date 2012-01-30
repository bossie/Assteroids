#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include "Widget.h"
#include "../entity/Entity.h"
#include "../config/Properties.h"

#include <typeinfo>
#include <boost/shared_ptr.hpp>

namespace sdl {

class WidgetFactory {
    boost::shared_ptr<const config::Properties> m_settings;

public:
    explicit WidgetFactory(boost::shared_ptr<const config::Properties> settings);
    virtual ~WidgetFactory();

    virtual boost::shared_ptr<Widget> create(boost::shared_ptr<const entity::Entity> e) const;
};

} // namespace sdl

#endif // WIDGETFACTORY_H
