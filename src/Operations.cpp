#include "Node.hpp"

class OpSum : public Node {
public:

    class Descriptor : public Node::Descriptor {
    public:

        Descriptor() : Node::Descriptor("op.sum", "+", "sum operation") {

        }

        Node* create() const override {
            return NULL;
        }
    };
};
auto sum = Node::Descriptor::registerDescriptor(new OpSum::Descriptor());

class OpSub : public Node {
public:

    class Descriptor : public Node::Descriptor {
    public:

        Descriptor() : Node::Descriptor("op.sub", "-", "sub operation") {

        }

        Node* create() const override {
            return NULL;
        }
    };
};
auto sub = Node::Descriptor::registerDescriptor(new OpSub::Descriptor());