#pragma once

#include <gtkmm/drawingarea.h>

class ModuleWidget : public Gtk::DrawingArea {
public:
    ModuleWidget();
private:
    gdouble _x, _y;
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    virtual bool on_motion_notify_event(GdkEventMotion* event) override;
};
