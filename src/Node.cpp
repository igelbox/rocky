#include "Node.hpp"

NodeDescriptor::NodeDescriptor(std::string id, std::string name, std::string descriptrion) : _id(id), _name(name), _description(descriptrion) {

}

std::vector<const NodeDescriptor*> _descriptors;

const std::vector<const NodeDescriptor*>& NodeDescriptor::descriptors() {
    return _descriptors;
}

const NodeDescriptor* NodeDescriptor::registerDescriptor(const NodeDescriptor *descriptor) {
    _descriptors.push_back(descriptor);
    return descriptor;
}
