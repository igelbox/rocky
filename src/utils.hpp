#pragma once

#include <exception>
#include <string>

namespace rocky {
    template<class T> struct pimpl {
        pimpl() {
            value = new T();
        }
        ~pimpl() {
            delete value;
        }
        T* operator ->() {
            return value;
        }
        const T* operator ->() const {
            return value;
        }
    private:
        T *value;
    };
    class Exception : public std::exception {
    public:
        Exception(const char *what);
        ~Exception() override;
        const char* what() const _GLIBCXX_USE_NOEXCEPT override;
        static void dump(std::exception& e, std::string& out) throw ();
    private:
        char *_what;
    };
}