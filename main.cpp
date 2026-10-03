#include <iostream>
#include <string>
#include <sys/socket.h>
#include"Socket.h"
int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "usage ./" << argv[0] << " hostname port\n";
        return 1;
    }
    std::string hostname{argv[1]};
    int portno{std::stoi(argv[2])};
    Socket socket{hostname, portno};
    socket.link();
    socket.send();
    socket.receive();
}
