#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }

    sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr) != 1) {
        return 1;
    }

    if (connect(fd, (sockaddr*)&sa, sizeof(sa)) == 0) {
        printf("Successfully connected to port 8080!\n");
        return 0;
    }
    else {
        printf("Port 8080 is closed!\n");
        return 1;
    }

    close(fd);

    return 0;
}
