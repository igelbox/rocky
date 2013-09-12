#pragma once

#include "../sio.hpp"
#include "../../utils.hpp"

namespace rocky {
    namespace sio {
        namespace jack {

            class JackEngine : public Engine {
            public:
                JackEngine();
                ~JackEngine() override;
                Module* createModule(const char *name, Module::ProcessCallback callback, void *arg) override;
            private:
                struct Impl;
                pimpl<Impl> impl;
            };
        }
    }
}