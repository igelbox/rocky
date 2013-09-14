#pragma once

#include <vector>
#include <sigc++/signal.h>

#include "Node.hpp"
#include "utils.hpp"

#include "package.hpp"

package_begin

class Module {
public:
    Module();
    ~Module();
    const std::vector<const Node*> nodes() const;
    void append(const Node &node);
    sigc::signal<void, const Node&> signal_node_add() const;
    sigc::signal<void, const Node&> signal_node_del() const;
private:
    struct Impl;
    pimpl<Impl> impl;
};

package_end
