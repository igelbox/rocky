#include <cstdlib>
#include <cstdio>
#include <exception>

#include "utils.hpp"
#include "ui/MainWindow.hpp"
#include "jack/Client.hpp"

int main(int argc, char** argv) {
    try {
        rocky::jack::RealClient client("rocky");
        for (auto c : client.clients()) {
            printf("client:%s\n", c->name());
            for (auto p : c->ports())
                printf("\tport:%s\n", p->name());
        }
        auto app = Gtk::Application::create(argc, argv, "ccs.rocky");
        MainWindow window;
        return app->run(window);
    } catch (std::exception& e) {
        std::string buff = "uncaught exception: ";
        rocky::Exception::dump(e, buff);
        fputs(buff.c_str(), stderr);
    }
}
