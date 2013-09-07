#include <cstdlib>

#include "ui/MainWindow.hpp"

using namespace std;

int main(int argc, char** argv) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "ccs.test");
    MainWindow window;
    return app->run(window);
}
