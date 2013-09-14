#include <string>

#include "Node.hpp"

package_begin

struct Node::Descriptor::Impl {
    std::string id, name, path;
};

Node::Descriptor::Descriptor(const char *id, const char *name, const char *path) {
    impl->id = id;
    impl->name = name;
    impl->path = path;
}

Node::Descriptor::~Descriptor() {
}

const char* Node::Descriptor::name() const {
    return impl->name.c_str();
}

const char* Node::Descriptor::path() const {
    return impl->path.c_str();
}

struct Node::Impl {
    const Node::Descriptor *descriptor;
};

Node::Node(const Node::Descriptor &descriptor) {
    impl->descriptor = &descriptor;
}

Node::~Node() {
}

const Node::Descriptor& Node::descriptor() const {
    return *(impl->descriptor);
}

std::vector<const Node::Descriptor*> _descriptors;

const std::vector<const Node::Descriptor*>& Node::Descriptor::descriptors() {
    return _descriptors;
}

const Node::Descriptor* Node::Descriptor::registerDescriptor(const Node::Descriptor *descriptor) {
    _descriptors.push_back(descriptor);
    return descriptor;
}

package_end
