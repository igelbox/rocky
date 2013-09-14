#pragma once

#include <gtkmm/drawingarea.h>

#include "../utils.hpp"
#include "../Module.hpp"

#include "package.hpp"

package_begin

class ModuleWidget : public Gtk::DrawingArea {
public:
    explicit ModuleWidget(rocky::Module *module);
    ~ModuleWidget() override;
private:
    struct Impl;
    rocky::pimpl<Impl> impl;
};

package_end
