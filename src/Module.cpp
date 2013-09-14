#include "Module.hpp"

package_begin

struct Module::Impl {
    std::vector<const Node*> nodes;
    sigc::signal<void, const Node&> sig_node_added, sig_node_deleted;
};

Module::Module() {
}

Module::~Module() {
}

const std::vector<const Node*> Module::nodes() const {
    return impl->nodes;
}

void Module::append(const Node &node) {
    impl->nodes.push_back(&node);
    impl->sig_node_added(node);
}

sigc::signal<void, const Node&> Module::signal_node_add() const {
    return impl->sig_node_added;
}

sigc::signal<void, const Node&> Module::signal_node_del() const {
    return impl->sig_node_deleted;
}

package_end
