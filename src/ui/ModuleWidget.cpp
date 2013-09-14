#include "ModuleWidget.hpp"

package_begin

struct ModuleWidget::Impl {
    ModuleWidget *widget;
    Module *module;
    gdouble x, y;

    Impl* self() {
        return this;
    }

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
        auto allocation = widget->get_allocation();
        const int w = allocation.get_width(), h = allocation.get_height();
        cr->set_source_rgb(0, 0, 0);
        cr->rectangle(0, 0, w, h);
        cr->fill();
        cr->set_source_rgb(0.2, 0.2, 0.2);
        cr->move_to(0, 0);
        cr->line_to(x, y);
        cr->move_to(w, 0);
        cr->line_to(x, y);
        cr->move_to(w, h);
        cr->line_to(x, y);
        cr->move_to(0, h);
        cr->line_to(x, y);
        cr->set_line_width(1);
        cr->stroke();
        return true;
    }

    bool on_motion_notify_event(GdkEventMotion* event) {
        x = event->x;
        y = event->y;
        auto win = widget->get_window();
        if (win) {
            Gdk::Rectangle r(0, 0, widget->get_allocation().get_width(), widget->get_allocation().get_height());
            win->invalidate_rect(r, false);
        }
        return false;
    }
};

ModuleWidget::ModuleWidget(Module *module) {
    impl->widget = this;
    impl->module = module;
    add_events(Gdk::POINTER_MOTION_MASK);
    signal_draw().connect(sigc::mem_fun(impl->self(), &ModuleWidget::Impl::on_draw));
    signal_motion_notify_event().connect(sigc::mem_fun(impl->self(), &ModuleWidget::Impl::on_motion_notify_event));
}

ModuleWidget::~ModuleWidget() {
}

package_end
