#include "Node.hpp"

#include "package.hpp"

package_begin

class OpSum : public Node {
public:

    explicit OpSum(const Descriptor &d) : Node(d) {
    }

    class Descriptor : public Node::Descriptor {
    public:

        Descriptor() : Node::Descriptor("op.sum", "+", "ops/sum") {

        }

        Node& create() const override {
            return *(new OpSum(*this));
        }
    };
};
auto sum = Node::Descriptor::registerDescriptor(new OpSum::Descriptor());

class OpSub : public Node {
public:

    explicit OpSub(const Descriptor &d) : Node(d) {
    }

    class Descriptor : public Node::Descriptor {
    public:

        Descriptor() : Node::Descriptor("op.sub", "-", "ops/sub") {

        }

        Node& create() const override {
            return *(new OpSub(*this));
        }
    };
};
auto sub = Node::Descriptor::registerDescriptor(new OpSub::Descriptor());

package_end
