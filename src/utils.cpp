#include "utils.hpp"

#include <cstring>
#include <typeinfo>

namespace rocky {

    Exception::Exception(const char *what) {
        size_t l = strlen(what);
        _what = new char[l + 1];
        memcpy(_what, what, l + 1);
    }

    Exception::~Exception() {
        delete _what;
    }

    const char* Exception::what() const _GLIBCXX_USE_NOEXCEPT {
        return _what;
    }

    void Exception::dump(std::exception& e, std::string& out) throw () {
        out = out + typeid (e).name() + ": " + e.what();
    }
}