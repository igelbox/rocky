#pragma once

#include <vector>

#include "utils.hpp"

#include "package.hpp"

package_begin

class Node {
public:

    class Descriptor {
    public:
        Descriptor(const char *id, const char *name, const char *path = "");
        ~Descriptor();
        const char* name() const;
        const char* path() const;
        virtual Node& create() const = 0;
        static const std::vector<const Descriptor*>& descriptors();
        static const Descriptor* registerDescriptor(const Descriptor *descriptor);
    private:
        struct Impl;
        pimpl<Impl> impl;
    };

    explicit Node(const Descriptor &descriptor);
    ~Node();
    const Descriptor& descriptor() const;
private:
    struct Impl;
    pimpl<Impl> impl;
};

package_end
