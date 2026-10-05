#pragma once
#include <cstddef>
#include <string>
#include <string_view>
class Http {
public:
    Http() = delete;
    Http(std::string &&msg);

    std::string_view getheader() const;
    std::string_view getbody() const;
    std::string_view getversion() const;
    int getstc() const;
    void operator()() const;

private:
    std::string header{};
    std::string body{};
    std::string date{};
    std::string content_t{};
    std::string tfencoding{};
    std::string version{};
    int         stc{};
};
