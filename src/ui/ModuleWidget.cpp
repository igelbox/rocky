#include "ModuleWidget.hpp"

ModuleWidget::ModuleWidget() {
    add_events(Gdk::POINTER_MOTION_MASK);
}

bool ModuleWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    cr->set_line_width(1);
    cr->move_to(0, _y);
    cr->line_to(width, _y);
    cr->move_to(_x, 0);
    cr->line_to(_x, height);
    cr->stroke();
    cr->set_line_width(5);
    cr->move_to(_x - 10, _y);
    cr->line_to(_x + 10, _y);
    cr->move_to(_x, _y - 10);
    cr->line_to(_x, _y + 10);
    cr->stroke();
    return true;
}

//#include <cstdio>

bool ModuleWidget::on_motion_notify_event(GdkEventMotion* event) {
    _x = event->x;
    _y = event->y;
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    //    printf("%f-%f\n", event->x, event->y);
    return false;
}