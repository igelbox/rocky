#pragma once

#include <gtkmm/drawingarea.h>

#include "../utils.hpp"

class ModuleWidget : public Gtk::DrawingArea {
public:
    ModuleWidget();
    ~ModuleWidget() override;
private:
    struct Impl;
    rocky::pimpl<Impl> impl;
};
