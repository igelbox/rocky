#include <gtkmm/drawingarea.h>
#include <gtkmm/scrollable.h>

#include "ModuleWidget.hpp"

package_begin

class SceneNode {
public:

    SceneNode(const rocky::Node &node) : _node(node), _bounds(10, 10, 32, 32) {
    }

    const Gdk::Rectangle& bounds() {
        return _bounds;
    }

    void draw(const Cairo::RefPtr<Cairo::Context> &cr) {
        const Gdk::Rectangle &b = bounds();
        cr->rectangle(b.get_x(), b.get_y(), b.get_width(), b.get_height());
        cr->set_source_rgb(0.5, 0.5, 0.5);
        cr->fill();
        std::string txt = _node.descriptor().name();
        Cairo::TextExtents te;
        cr->get_text_extents(txt, te);
        cr->move_to(b.get_x() + b.get_width() / 2 - te.x_bearing - te.width / 2.0, b.get_y() + b.get_height() / 2 - te.y_bearing - te.height / 2.0);
        cr->set_source_rgb(0, 0, 0);
        cr->show_text(txt);
    }

    void move(int x, int y) {
        _bounds.set_x(x);
        _bounds.set_y(y);
    }
private:
    const rocky::Node &_node;
    Gdk::Rectangle _bounds;
};

class SceneWidget : public Gtk::DrawingArea {
public:

    SceneWidget() : _drag(NULL) {
        add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK);
    }

    ~SceneWidget() {
        for (auto n : _nodes)
            delete n;
    }

    void addNode(const rocky::Node &node) {
        auto n = new SceneNode(node);
        _nodes.push_back(n);
        auto win = get_window();
        if (win)
            win->invalidate_rect(n->bounds(), false);
    }
protected:
    typedef Gtk::Widget super;

    struct DragInfo {
        SceneNode &node;
        int ox, oy;

        DragInfo(SceneNode &n, int x, int y) : node(n), ox(x), oy(y) {
        }
    };

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        auto allocation = get_allocation();
        const int w = allocation.get_width(), h = allocation.get_height();
        cr->rectangle(0, 0, w, h);
        cr->set_source_rgb(0, 0, 0);
        cr->fill();
        for (int y = 0; y < h; y += 8)
            for (int x = 0; x < w; x += 8)
                cr->rectangle(x, y, 1, 1);
        cr->set_source_rgb(0.25, 0.25, 0.25);
        cr->fill();
        for (auto n : _nodes)
            n->draw(cr);
        return true;
    }

    bool on_button_press_event(GdkEventButton *event) override {
        if (event->button == 1) {
            int x = event->x, y = event->y;
            for (auto n : _nodes) {
                const Gdk::Rectangle &r = n->bounds();
                if ((r.get_x() <= x) && (r.get_y() <= y) && (x <= (r.get_x() + r.get_width())) && (y <= (r.get_y() + r.get_height()))) {
                    _drag = new DragInfo(*n, x - r.get_x(), y - r.get_y());
                    break;
                }
            }
        }
        return true;
    }

    bool on_button_release_event(GdkEventButton *event) override {
        delete _drag;
        _drag = NULL;
        return true;
    }

    bool on_motion_notify_event(GdkEventMotion *event) override {
        if (_drag) {
            auto win = get_window();
            if (win)
                win->invalidate_rect(_drag->node.bounds(), false);
            int x = (int)event->x, y = (int)event->y;
            _drag->node.move(x - _drag->ox, y - _drag->oy);
            if (win)
                win->invalidate_rect(_drag->node.bounds(), false);
        }
        return true;
    }
    std::vector<SceneNode*> _nodes;
    DragInfo *_drag;
};

struct ModuleWidget::Impl {
    SceneWidget scene;

    Impl* self() {
        return this;
    }

    void on_node_del(const Node &node) {

    }

    void on_node_add(const Node &node) {
        scene.addNode(node);
    }
};

ModuleWidget::ModuleWidget(Module &module) {
    add(impl->scene);
    module.signal_node_add().connect(sigc::mem_fun(impl->self(), &ModuleWidget::Impl::on_node_add));
    module.signal_node_del().connect(sigc::mem_fun(impl->self(), &ModuleWidget::Impl::on_node_del));
}

ModuleWidget::~ModuleWidget() {
}

package_end
