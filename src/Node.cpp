#include "Node.hpp"

Node::Descriptor::Descriptor(std::string id, std::string name, std::string descriptrion) : _id(id), _name(name), _description(descriptrion) {

}

std::vector<const Node::Descriptor*> _descriptors;

const std::vector<const Node::Descriptor*>& Node::Descriptor::descriptors() {
    return _descriptors;
}

const Node::Descriptor* Node::Descriptor::registerDescriptor(const Node::Descriptor *descriptor) {
    _descriptors.push_back(descriptor);
    return descriptor;
}
