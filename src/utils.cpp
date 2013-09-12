#include "utils.hpp"

#include <cstring>
#include <typeinfo>
#include <cxxabi.h>

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
        char demangled[1024];
        size_t size = sizeof (demangled);
        int status;
        char *typname = abi::__cxa_demangle(typeid (e).name(), demangled, &size, &status);
        demangled[sizeof (demangled) - 1] = 0;
        out = out + typname + ": " + e.what();
    }
}