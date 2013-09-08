#include "MainWindow.hpp"

#include <gtkmm/box.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/stock.h>
#include <gtkmm/menu.h>

#include <gdlmm/init.h>
#include <gdlmm/dock.h>

#include "../main.hpp"
#include "AboutDialog.hpp"
#include "../Node.hpp"
#include "ProcessingGraphWidget.hpp"
#include "PropertiesWidget.hpp"
#include "ModuleWidget.hpp"

void on_file_exit(MainWindow *win) {
    win->hide();
}

void on_help_about() {
    AboutDialog about;
    about.run();
}

MainWindow::MainWindow() {
    Gdl::init();
    set_title(Glib::ustring(APP_NAME) + " " + APP_VERSION_STRING);
    set_default_size(1024, 768);
    auto vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    add(*vbox);
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
    for (auto nd : Node::Descriptor::descriptors())
        submenu_add->add(*Gtk::manage(new Gtk::MenuItem(nd->name())));
    menu_add->set_submenu(*submenu_add);

    auto dock = Gtk::manage(new Gdl::Dock());
    vbox->pack_start(*dock, Gtk::PACK_EXPAND_WIDGET);

    auto pg = Gtk::manage(new Gdl::DockItem("tabs.graph", "Processing graph", Gdl::DOCK_ITEM_BEH_CANT_ICONIFY | Gdl::DOCK_ITEM_BEH_CANT_CLOSE | Gdl::DOCK_ITEM_BEH_NO_GRIP));
    pg->add(*Gtk::manage(new ProcessingGraphWidget()));
    dock->add_item(*pg, Gdl::DOCK_CENTER);
    
    auto pw = Gtk::manage(new Gdl::DockItem("tabs.props", "Properties", Gdl::DOCK_ITEM_BEH_CANT_ICONIFY));
    pw->add(*Gtk::manage(new PropertiesWidget()));
    dock->add_item(*pw, Gdl::DOCK_RIGHT);

    for (int i = 0; i < 3; i++) {//test
        Glib::ustring name = Glib::ustring::compose("tabs.module%1", i);
        Glib::ustring long_name = Glib::ustring::compose("Module #%1", i);
        auto x = Gtk::manage(new Gdl::DockItem(name, long_name, Gdl::DOCK_ITEM_BEH_CANT_ICONIFY));
        x->add(*Gtk::manage(new ModuleWidget()));
        dock->add_item(*x, Gdl::DOCK_CENTER);
    }
    show_all_children();
}