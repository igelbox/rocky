#include "MainWindow.hpp"

#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>

#include "../main.hpp"
#include "AboutDialog.hpp"

void on_file_exit(MainWindow *win) {
    win->hide();
}

void on_help_about() {
    AboutDialog about;
    about.run();
}

MainWindow::MainWindow() {
    set_title( Glib::ustring(APP_NAME) + " " + APP_VERSION_STRING );
    set_default_size(1024, 768);
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    Glib::RefPtr<Gtk::ActionGroup> ag = Gtk::ActionGroup::create();
    ag->add(Gtk::Action::create("file", "File"));
    ag->add(Gtk::Action::create("file.open", Gtk::Stock::QUIT));
    ag->add(Gtk::Action::create("file.save", Gtk::Stock::QUIT));
    ag->add(Gtk::Action::create("file.quit", Gtk::Stock::QUIT), sigc::bind(&on_file_exit, this));
    ag->add(Gtk::Action::create("edit", "Edit"));
    ag->add(Gtk::Action::create("edit.delete", Gtk::Stock::DELETE));
    ag->add(Gtk::Action::create("help", "Help"));
    ag->add(Gtk::Action::create("help.about", Gtk::Stock::ABOUT), sigc::ptr_fun(&on_help_about));
    Glib::RefPtr<Gtk::UIManager> uim = Gtk::UIManager::create();
    uim->insert_action_group(ag);
    add_accel_group(uim->get_accel_group());
    uim->add_ui_from_string("<ui>"
            "  <menubar name='MenuBar'>"
            "    <menu action='file'>"
            "      <menuitem action='file.quit'/>"
            "    </menu>"
            "    <menu action='edit'>"
            "      <menuitem action='edit.delete'/>"
            "    </menu>"
            "    <menu action='help'>"
            "      <menuitem action='help.about'/>"
            "    </menu>"
            "  </menubar>"
            "  <toolbar name='ToolBar'>"
            "    <toolitem action='file.quit'/>"
            "  </toolbar>"
            "</ui>");
    vbox->pack_start(*(uim->get_widget("/MenuBar")), Gtk::PACK_SHRINK);
    add(*vbox);
    show_all_children();
}