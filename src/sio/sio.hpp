#pragma once

#include <cstdint>
#include <vector>

namespace rocky {
    namespace sio {

        class Port {
        public:
            virtual ~Port();
        };

        class Module {
        public:

            struct ProcessCallbackArg {
                const uint32_t nframes;
                const float **inputs, **outputs;
                const void *argument;
            };
            typedef void(*ProcessCallback) (const ProcessCallbackArg &arg);
            virtual ~Module();
            virtual const std::vector<const Port*> inputs() const = 0;
            virtual const std::vector<const Port*> outputs() const = 0;
            virtual Port* createInput(const char *name) = 0;
            virtual Port* createOutput(const char *name) = 0;
        };

        class Engine {
        public:
            virtual ~Engine();
            virtual Module* createModule(const char *name, Module::ProcessCallback callback, void *arg) = 0;
        };
    }
}