#include <cstdlib>

#include "ui/MainWindow.hpp"

using namespace std;

int main(int argc, char** argv) {
    auto app = Gtk::Application::create(argc, argv, "ccs.rocky");
    MainWindow window;
    return app->run(window);
}
