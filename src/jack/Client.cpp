#include "Client.hpp"

#include <cstdint>
#include <cstdio>
#include <jack/jack.h>
#include <string.h>

namespace rocky {
    namespace jack {

        struct Client::Port::Impl {

            Impl() {
            }
            const Client *client;
            std::string name;
        };

        Client::Port::Port(const Client *client, const std::string& name) {
            impl->client = client;
            impl->name = name;
        }

        Client::Port::~Port() {
        }

        const char* Client::Port::name() const {
            return impl->name.c_str();
        }

        const Client& Client::Port::client() const {
            return *(impl->client);
        }

        struct Client::Impl {

            Impl() {
            }

            ~Impl() {
                for (auto p : ports)
                    delete p;
            }
            std::string name;
            std::vector<Client::Port*> ports;

            Client::Port* findPort(const char *name) {
                for (auto p : ports)
                    if (p->impl->name == name)
                        return p;
                return NULL;
            }
        };

        Client::Client(const std::string& name) {
            impl->name = name;
        }

        Client::~Client() {
        }

        const char* Client::name() const {
            return impl->name.c_str();
        }

        const std::vector<Client::Port*>& Client::ports() const {
            return impl->ports;
        }

        struct RealClient::Impl {

            Impl() : client(NULL) {
            }

            ~Impl() {
                for (auto c : clients)
                    delete c;
            }
            jack_client_t *client;
            std::vector<Client*> clients;

            Client* findClient(const char *name) {
                for (auto c : clients)
                    if (c->impl->name == name)
                        return c;
                return NULL;
            }
        };
        //

        RealClient::RealClient(const std::string& name) throw (Exception)
        : Client(name) {
            jack_status_t status;
            if ((impl->client = jack_client_open(name.c_str(), (jack_options_t)(JackNoStartServer | JackUseExactName), &status, NULL)) == NULL) {
                char what[12];
                sprintf(what, "status=%x", (uint32_t)status);
                throw Exception(what);
            }
            const char **ports = jack_get_ports(impl->client, NULL, NULL, 0);
            if (ports) {
                const char **port = ports;
                while (*port) {
                    std::string sport = *port;
                    const char *pn = sport.c_str();
                    char *sc = strchr(pn, ':');
                    if (sc == NULL)
                        throw Exception(pn);
                    *sc = 0;
                    sc++;
                    Client *c = impl->findClient(pn);
                    if (c == NULL)
                        impl->clients.push_back(c = new Client(pn));
                    Client::Port *p = c->impl->findPort(sc);
                    if (p == NULL)
                        c->impl->ports.push_back(p = new Client::Port(c, sc));
                    port++;
                }
                jack_free(ports);
            }
        }

        RealClient::~RealClient() {
            if (impl->client)
                jack_client_close(impl->client);
        }

        static void client_callback(const char* client, int yn, void* arg) {
            printf("Client %s %s\n", client, (yn ? "registered" : "unregistered"));
        }

        void RealClient::activate() throw (Exception) {
            //            auto output_port1 = jack_port_register(priv->client, "output1",
            //                    JACK_DEFAULT_AUDIO_TYPE,
            //                    JackPortIsOutput, 0);
            //
            //            auto output_port2 = jack_port_register(priv->client, "output2",
            //                    JACK_DEFAULT_AUDIO_TYPE,
            //                    JackPortIsOutput, 0);
            //            jack_set_client_registration_callback(priv->client, client_callback, NULL);
            int ec = jack_activate(impl->client);
            if (ec != 0) {
                char what[10];
                sprintf(what, "code=%x", (uint32_t)ec);
                throw Exception(what);
            }
        }

        const std::vector<Client*>& RealClient::clients() const {
            return impl->clients;
        }
    }
}