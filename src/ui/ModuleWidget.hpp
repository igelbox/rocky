#pragma once

#include <gtkmm/scrolledwindow.h>

#include "../utils.hpp"
#include "../Module.hpp"

#include "package.hpp"

package_begin

class ModuleWidget : public Gtk::ScrolledWindow {
public:
    explicit ModuleWidget(rocky::Module &module);
    ~ModuleWidget() override;
private:
    struct Impl;
    rocky::pimpl<Impl> impl;
};

package_end
