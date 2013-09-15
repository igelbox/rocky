#pragma once

#include <gtkmm/aboutdialog.h>
#include "package.hpp"

package_begin

class AboutDialog : public Gtk::AboutDialog {
public:
    AboutDialog();
};

package_end
