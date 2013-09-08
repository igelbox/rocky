#include "MainWindow.hpp"

#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>
#include <gtkmm/menu.h>

#include "../main.hpp"
#include "AboutDialog.hpp"
#include "../Node.hpp"
#include "ModuleWidget.hpp"

void on_file_exit(MainWindow *win) {
    win->hide();
}

void on_help_about() {
    AboutDialog about;
    about.run();
}

MainWindow::MainWindow() {
    set_title(Glib::ustring(APP_NAME) + " " + APP_VERSION_STRING);
    set_default_size(1024, 768);
    auto vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    auto ag = Gtk::ActionGroup::create();
    ag->add(Gtk::Action::create("file", "File"));
    ag->add(Gtk::Action::create("file.new", Gtk::Stock::NEW));
    ag->add(Gtk::Action::create("file.open", Gtk::Stock::OPEN));
    ag->add(Gtk::Action::create("file.save", Gtk::Stock::SAVE));
    ag->add(Gtk::Action::create("file.quit", Gtk::Stock::QUIT), sigc::bind(&on_file_exit, this));
    ag->add(Gtk::Action::create("edit", "Edit"));
    ag->add(Gtk::Action::create("edit.add", Gtk::Stock::ADD));
    ag->add(Gtk::Action::create("edit.delete", Gtk::Stock::DELETE), Gtk::AccelKey("Delete"));
    ag->add(Gtk::Action::create("help", "Help"));
    ag->add(Gtk::Action::create("help.about", Gtk::Stock::ABOUT), sigc::ptr_fun(&on_help_about));
    auto uim = Gtk::UIManager::create();
    uim->insert_action_group(ag);
    add_accel_group(uim->get_accel_group());
    uim->add_ui_from_string("<ui>"
            "  <menubar name='menu'>"
            "    <menu action='file'>"
            "      <menuitem action='file.new'/>"
            "      <menuitem action='file.open'/>"
            "      <menuitem action='file.save'/>"
            "      <separator/>"
            "      <menuitem action='file.quit'/>"
            "    </menu>"
            "    <menu action='edit' name='edit'>"
            "      <menu action='edit.add' name='add'/>"
            "      <menuitem action='edit.delete'/>"
            "    </menu>"
            "    <menu action='help'>"
            "      <menuitem action='help.about'/>"
            "    </menu>"
            "  </menubar>"
            "</ui>");
    vbox->pack_start(*(uim->get_widget("/menu")), Gtk::PACK_SHRINK);
    auto menu_add = dynamic_cast<Gtk::MenuItem*> (uim->get_widget("/menu/edit/add"));
    auto submenu_add = Gtk::manage(new Gtk::Menu());
    for (auto nd : NodeDescriptor::descriptors())
        submenu_add->add(*Gtk::manage(new Gtk::MenuItem(nd->name())));
    menu_add->set_submenu(*submenu_add);
    vbox->pack_start(*Gtk::manage(new ModuleWidget()), Gtk::PACK_EXPAND_WIDGET);
    add(*vbox);
    show_all_children();
}