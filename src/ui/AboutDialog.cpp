#include "AboutDialog.hpp"

#include <vector>

#include "../main.hpp"

AboutDialog::AboutDialog() {
    set_program_name(APP_NAME);
    set_version(APP_VERSION_STRING);
    set_copyright("Vakhurin Sergey");
    set_comments("This is just an application.");
    //  set_license("LGPL");

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Vakhurin Sergey");
    set_authors(list_authors);
}