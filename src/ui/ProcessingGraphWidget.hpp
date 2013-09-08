#pragma once

#include <gtkmm/drawingarea.h>

class ProcessingGraphWidget : public Gtk::DrawingArea {
public:
    ProcessingGraphWidget();
private:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};
