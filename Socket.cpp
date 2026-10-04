#include <cstddef>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/socket.h>
#include <unistd.h>
#include "Socket.h"

Socket::Socket(std::string_view host, int port)
    : hostname{host}, portno{port}
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        throw std::runtime_error("sockfd error");
}

Socket::~Socket()
{
    close(sockfd);
}

void
Socket::link() const
{
    struct hostent *server = gethostbyname(hostname.c_str());
    if(server == nullptr)
        throw std::runtime_error("hostent");

    struct sockaddr_in serv_addr {
        .sin_family     = AF_INET,
        .sin_port       = htons(portno),
    };
    std::memcpy(&serv_addr.sin_addr.s_addr,
    server->h_addr_list[0],
    server->h_length);
    if(connect(sockfd,
               (struct sockaddr *) &serv_addr,
               sizeof(serv_addr)) < 0)
        throw std::runtime_error("connect");
    std::cout << "connected to server " << server->h_name << '\n';
}

void
Socket::send(std::string_view msg) const
{
    ssize_t n = write(sockfd,msg.data(), msg.size());
    if (n < 0)
        throw std::runtime_error("send, parm: msg");
    std::cout << "sending msg(p:1)..." << '\n';
}

std::string
Socket::receive() const
{
    std::string buff{};
    buff.resize(4096);

    ssize_t n = read(sockfd, buff.data(), buff.size());

    if(n < 0)
        throw std::runtime_error("receive");

    buff.resize(static_cast<std::size_t>(n));
    return buff;
}
