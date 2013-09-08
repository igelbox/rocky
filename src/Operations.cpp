#include "Node.hpp"

class OpSum : public Node {
public:

    class Descriptor : public NodeDescriptor {
    public:

        Descriptor() : NodeDescriptor("op.sum", "+", "sum operation") {

        }

        Node* create() const override {
            return NULL;
        }
    };
};
auto sum = NodeDescriptor::registerDescriptor(new OpSum::Descriptor());

class OpSub : public Node {
public:

    class Descriptor : public NodeDescriptor {
    public:

        Descriptor() : NodeDescriptor("op.sub", "-", "sub operation") {

        }

        Node* create() const override {
            return NULL;
        }
    };
};
auto sub = NodeDescriptor::registerDescriptor(new OpSub::Descriptor());