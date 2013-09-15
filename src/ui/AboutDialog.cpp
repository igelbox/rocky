#include "../main.hpp"

#include "AboutDialog.hpp"

package_begin

AboutDialog::AboutDialog() {
    set_program_name(APP_NAME);
    set_version(APP_VERSION_STRING);
    set_copyright("Vakhurin Sergey");
    set_comments("This is just an application.");
    //  set_license("LGPL");

    set_authors({"Vakhurin Sergey"});
}
package_end
