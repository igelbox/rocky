#include "ProcessingGraphWidget.hpp"

ProcessingGraphWidget::ProcessingGraphWidget() {
}

bool ProcessingGraphWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    auto allocation = get_allocation();
    cr->set_source_rgb(0, 0, 0);
    cr->rectangle(0, 0, allocation.get_width(), allocation.get_height());
    cr->fill();
    return true;
}
