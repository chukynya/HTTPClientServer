#pragma once
#include <cstdint>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
class Socket {
public:
    Socket() = delete;
    explicit Socket(const std::string& hostname, int port);
    ~Socket();
    void link();
    void send();
    void receive();

private:
    const std::string &hostname;
    int         portno{};
    int         sockfd{};
};
// so the users can do Socket socket{<hostname(str)>, <port(int)>}
// when the user do socket.connect() -> we do connect to server;
