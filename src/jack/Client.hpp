#pragma once

#include <vector>
#include "../utils.hpp"

namespace rocky {
    namespace jack {
        class RealClient;

        class Client {
        public:

            class Port {
            public:
                Port(const Client *client, const std::string& name);
                ~Port();
                const char* name() const;
                const Client& client() const;
            protected:
                struct Impl;
                pimpl<Impl> impl;
                friend class Client;
            };
        public:
            Client(const std::string& name);
            ~Client();
            const char* name() const;
            const std::vector<Port*>& ports() const;
        protected:
            struct Impl;
            pimpl<Impl> impl;
            friend class RealClient;
        };

        class RealClient : public Client {
        public:
            RealClient(const std::string& name) throw (Exception);
            ~RealClient();
            void activate() throw (Exception);
            const std::vector<Client*>& clients() const;
        private:
            struct Impl;
            pimpl<Impl> impl;
        };
    }
}
