#pragma once

#include <string>
#include <vector>

class Node {
public:

    class Descriptor {
    public:
        Descriptor(std::string id, std::string name, std::string descriptrion = "");

        const std::string& name() const {
            return _name;
        };

        const std::string& description() const {
            return _description;
        };
        virtual Node* create() const = 0;
        static const std::vector<const Descriptor*>& descriptors();
        static const Descriptor* registerDescriptor(const Descriptor *descriptor);
    private:
        std::string _id;
        std::string _name;
        std::string _description;
    };
};
