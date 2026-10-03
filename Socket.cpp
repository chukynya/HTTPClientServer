#include <algorithm>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include "Socket.h"

Socket::Socket(const std::string& host, int port)
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
Socket::link()
{
    struct hostent *server = gethostbyname(hostname.c_str());
    if(server == nullptr)
        throw std::runtime_error("hostent");

    struct sockaddr_in serv_addr {
        .sin_port       = htons(portno),
        .sin_addr       = AF_INET,
    };
    std::memcpy(&serv_addr.sin_addr.s_addr,
    server->h_addr_list[0],
    server->h_length);
    if(connect(sockfd,
               (struct sockaddr *) &serv_addr,
               sizeof(serv_addr)) < 0)
        throw std::runtime_error("connect");
}

void
Socket::send()
{
    std::cout << "Please enter the message: ";
    std::string buffer{};
    std::cin >> buffer;
    int n = write(sockfd, buffer.data(), buffer.size());
    if (n < 0)
        throw std::runtime_error("send");
}

void
Socket::receive()
{
    std::string buff(1024, '\0');
    int n = read(sockfd, buff.data(), buff.size());
    if(n < 0)
        throw std::runtime_error("receive");
    n = read(sockfd, buff.data(), buff.size());
}
