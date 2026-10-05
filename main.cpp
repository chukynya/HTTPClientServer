#include <exception>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <utility>
#include "Http.h"
#include "Socket.h"
int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "usage ./" << argv[0] << " hostname port\n";
        return 1;
    }
    try {
        Socket socket{argv[1], argv[2]};
        socket.link();
        socket.send(
            "GET / HTTP/1.1\r\n"
            "Host: " + std::string{argv[1]} + "\r\n"
            "Connection: close\r\n"
            "\r\n"
        );
        Http http{std::move(socket.receive())};
        http();
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "error occurs";
    }

    return 0;
}
