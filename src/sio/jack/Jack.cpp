#include "Jack.hpp"

#include <jack/jack.h>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

namespace rocky {
    namespace sio {
        namespace jack {
            class JackModule;

            static int on_process(jack_nframes_t nframes, void *arg);

            class JackPort : public Port {
            public:

                JackPort(jack_client_t *client, const char *name, JackPortFlags flags, std::vector<const Port*> &holder) : _holder(holder) {
                    if ((_port = jack_port_register(client, name, JACK_DEFAULT_AUDIO_TYPE, flags, 0)) == NULL)
                        throw rocky::Exception("jack_port_register");
                }

                ~JackPort() override {
                    auto e = _holder.end(), f = std::find(_holder.begin(), e, this);
                    if (f == e)
                        printf("warning: port not found in holder");
                    else
                        _holder.erase(f);
                }
            private:
                jack_port_t *_port;
                std::vector<const Port*> &_holder;
                friend int on_process(jack_nframes_t, void*);
            };

            class JackModule : public Module {
            public:

                JackModule(const char *name, ProcessCallback callback, void *arg, std::vector<const JackModule*> &holder) : _holder(holder), _callback(callback), _callbackArg(arg), _skipProcess(false) {
                    jack_status_t status;
                    if ((_client = jack_client_open(name, JackNoStartServer, &status, NULL)) == NULL) {
                        std::string msg = "jack_client_open::status=";
                        msg += (uint32_t)status;
                        throw Exception(msg.c_str());
                    }
                    jack_set_process_callback(_client, on_process, this);
                    int r = jack_activate(_client);
                    if (r != 0) {
                        std::string msg = "jack_activate=";
                        msg += r;
                        throw Exception(msg.c_str());
                    }
                }

                ~JackModule() {
                    int r = jack_client_close(_client);
                    if (r != 0)
                        printf("jack_client_close==%d", r);
                    std::vector<const Port*> inputsCopy(_inputs);
                    for (auto p : inputsCopy)
                        delete p;
                    std::vector<const Port*> outputsCopy(_inputs);
                    for (auto p : outputsCopy)
                        delete p;
                    auto e = _holder.end(), f = std::find(_holder.begin(), e, this);
                    if (f == e)
                        printf("warning: module not found in holder");
                    else
                        _holder.erase(f);
                }

                const std::vector<const Port*> inputs() const override {
                    return _inputs;
                }

                const std::vector<const Port*> outputs() const override {
                    return _outputs;
                }

                Port* createInput(const char *name) override {
                    Port *p = new JackPort(_client, name, JackPortIsInput, _inputs);
                    _inputs.push_back(p);
                    return p;
                }

                Port* createOutput(const char *name) override {
                    Port *p = new JackPort(_client, name, JackPortIsOutput, _outputs);
                    _outputs.push_back(p);
                    return p;
                }
            private:
                std::vector<const JackModule*> &_holder;
                std::vector<const Port*> _inputs;
                std::vector<const Port*> _outputs;
                jack_client_t *_client;
                const ProcessCallback _callback;
                const void *_callbackArg;
                volatile bool _skipProcess;
                const float *_inbuff[16], *_outbuff[16]; //TODO
                friend int on_process(jack_nframes_t, void*);
            };

            int on_process(jack_nframes_t nframes, void *arg) {
                JackModule *m = reinterpret_cast<JackModule*>(arg);
                if (m->_skipProcess)
                    return 0;
                int idx = 0;
                for (auto i : m->_inputs)
                    m->_inbuff[idx++] = (float*)jack_port_get_buffer(reinterpret_cast<const JackPort*>(i)->_port, nframes);
                idx = 0;
                for (auto i : m->_outputs)
                    m->_outbuff[idx++] = (float*)jack_port_get_buffer(reinterpret_cast<const JackPort*>(i)->_port, nframes);
                m->_callback({nframes, m->_inbuff, m->_outbuff, m->_callbackArg});
                return 0;
            }

            struct JackEngine::Impl {
                std::vector<const JackModule*> modules;
            };

            JackEngine::JackEngine() {
            }

            JackEngine::~JackEngine() {
                std::vector<const JackModule*> modulesCopy(impl->modules);
                for (auto m : modulesCopy)
                    delete m;
            }

            Module* JackEngine::createModule(const char *name, Module::ProcessCallback callback, void *arg) {
                std::string mname = "rocky [";
                mname += name;
                mname += ']';
                auto m = new JackModule(mname.c_str(), callback, arg, impl->modules);
                impl->modules.push_back(m);
                return m;
            }
        }
    }
}