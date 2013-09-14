#pragma once

#include <gtkmm/applicationwindow.h>

#include "../utils.hpp"

#include "package.hpp"

package_begin

class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow();
    ~MainWindow() override;
private:
    struct Impl;
    rocky::pimpl<Impl> impl;
};

package_end
