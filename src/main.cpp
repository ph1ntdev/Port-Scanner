#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

enum class eIsOpen { SockError, IPConvertError, Connected, NotConnected };

eIsOpen isOpen(const std::string& ip, ushort port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("socket");
        return eIsOpen::SockError;
    }

    sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &sa.sin_addr) != 1) { close(fd); return eIsOpen::IPConvertError; }

    if (connect(fd, (sockaddr*)&sa, sizeof(sa)) == 0) { close(fd); return eIsOpen::Connected; }

    close(fd);
    return eIsOpen::NotConnected;
}

int main() {
    for (ushort port = 1; port <= 9000; port ++) {
        switch (isOpen("127.0.0.1", port)) {
            case eIsOpen::SockError:
                std::cout << "Problem with opening port\n";
                break;
            case eIsOpen::IPConvertError:
                std::cout << "Problem with IP addres convert\n";
                break;
            case eIsOpen::Connected:
                std::cout << "Successfully connected to port " << port << '\n';
                break;
            case eIsOpen::NotConnected:
                break;
        }
    }
    return 0;
}
