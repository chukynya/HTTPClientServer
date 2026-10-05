#include "Http.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
Http::Http(std::string &&msg)
{
    /*
     * In HTTP/1.x, the header section ends at 
     * the first empty line: "\r\n\r\n". 
     */
    std::size_t headernpos = msg.find("\r\n\r\n");
    if(headernpos == std::string::npos)
        throw std::runtime_error("Invalid HTTP response: no header/body seperator");
    header = msg.substr(0, headernpos);
    body = msg.substr(headernpos + 4);

    std::string statusline{header.substr(0, header.find("\r\n"))};
    std::istringstream stream{statusline};
    stream >> version >> stc;

    date = header.substr(header.find("Date") + 6, 28);

}

std::string_view
Http::getheader() const { return header; }

std::string_view
Http::getbody() const { return body; }

std::string_view
Http::getversion() const { return version; }

int
Http::getstc() const { return stc; } 

void
Http::operator()() const
{
    std::cout << "HTTP VERSION      : " << version << '\n';
    std::cout << "HTTP STATUS-CODE  : " << stc << '\n';
    std::cout << "===== HEADERS =====\n";
    std::cout << header << '\n';
    std::cout << "===== BODY =====\n";
    std::cout << body << '\n';
}
