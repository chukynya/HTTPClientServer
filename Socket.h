#pragma once
#include <cstdint>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <string_view>
#include <sys/socket.h>
class Socket {
public:
    Socket() = delete;
    explicit Socket(std::string_view host,  int port);
    ~Socket();

    void link() const;
    void send(std::string_view msg) const;
    std::string receive() const;

private:
    std::string hostname{};
    int         portno{};
    int         sockfd{};
};
