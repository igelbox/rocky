#include "PropertiesWidget.hpp"

#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treestore.h>

PropertiesWidget::PropertiesWidget() {
    set_size_request(128, 256);
    auto tree = Gtk::manage(new Gtk::TreeView());
    add(*tree);
    auto columns = new Gtk::TreeModelColumnRecord();
    auto col_name = new Gtk::TreeModelColumn<Glib::ustring>();
    auto col_value = new Gtk::TreeModelColumn<Glib::ustring>();
    columns->add(*col_name);
    columns->add(*col_value);
    auto model = Gtk::TreeStore::create(*columns);
    tree->set_model(model);
    tree->append_column("Name", *col_name);
    tree->append_column_editable("Value", *col_value);
    {auto row = *model->append();
    row[*col_name] = "prop1";
    row[*col_value] = "val1";}
    auto row = *model->append();
    row[*col_name] = "prop2";
    row[*col_value] = "val2";
    {auto rc = *model->append(row->children());
    rc[*col_name] = "pc1";
    rc[*col_value] = "vc1";}
    {auto rc = *model->append(row->children());
    rc[*col_name] = "pc2";
    rc[*col_value] = "vc2";}
}