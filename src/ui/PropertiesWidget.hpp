#pragma once

#include <gtkmm/scrolledwindow.h>

#include "package.hpp"

package_begin

class PropertiesWidget : public Gtk::ScrolledWindow {
public:
    PropertiesWidget();
};

package_end
