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

/* 
 * Prepare socked fd
 */
Socket::Socket(std::string_view host, std::string_view port)
    : hostname{host}, portno{port}, sockfd{-1}
{
}

Socket::~Socket()
{
    if (sockfd >= 0)
        close(sockfd);
}

/*
 * Resolve hostname and establish a TCP connetion
 */
void
Socket::link()
{
    struct addrinfo req {
        .ai_family      = AF_INET,      // IPv4
        .ai_socktype    = SOCK_STREAM,  // TCP stream sockets
    };
    struct addrinfo *res{nullptr};
    int status = getaddrinfo(hostname.c_str(),
                             portno.c_str(),
                             &req,
                             &res);
    if (status != 0)
        throw std::runtime_error("getaddrinfo error: ");

    /*
     * Loop through results and try to
     * connect to the first availableaddress   
     */
    for (struct addrinfo *p{res}; p != nullptr; p = p->ai_next) {
        int sock = socket(p->ai_family,
                          p->ai_socktype,
                          p->ai_protocol);
        if(sock == -1)
            continue;
        if(connect(sock,
                   p->ai_addr,
                   p->ai_addrlen) == 0) {
            sockfd = sock;
            break;
        }
        close(sock);
    }
    freeaddrinfo(res);
    if(sockfd < 0)
        throw std::runtime_error("Failed to connect to host");
}

void
Socket::send(std::string_view msg) const
{
    std::size_t total_send{0};
    while (total_send < msg.size()) {
        ssize_t n = write(sockfd,
                          msg.data() + total_send,
                          msg.size() - total_send);
        if (n < 0)
            throw std::runtime_error("send, parm: msg");
        total_send += static_cast<std::size_t>(n);
        std::cout << "sending msg(p:1)..." << '\n';
    }
}

/* 
 * Receive bytes from the TCP stream
 * keep reading until the peer closes the connection
 */
std::string
Socket::receive() const
{
    std::string chunks{};
    std::string chunk{};
    chunk.resize(Socket::chunksize);

    while (true) {
        ssize_t n = read(sockfd, chunk.data(), chunk.size());

        std::cout << "read() returned: " << n << '\n';

        if(n < 0)
            throw std::runtime_error("receive");
        if(n == 0)
            break;

        chunks.append(chunk.data(), static_cast<std::size_t>(n));
    }
    return chunks;
}
