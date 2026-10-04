#include <exception>
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
    int portno{std::stoi(argv[2])};
    try {
        Socket socket{argv[1], portno};
        socket.link();
        socket.send("Hello from C++");
        std::string msg = socket.receive();
        std::cout << msg << '\n';
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "error occurs";
    }

    return 0;
}
