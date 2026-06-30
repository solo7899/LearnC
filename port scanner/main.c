#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

typedef enum _conType { TCP, UDP } conType;

typedef struct port {
    enum { TYPE_INT, TYPE_RANGE } type;
    union {
        int portNum;
        int portRange[2];
    } value;
} port;

int sock_create(conType type);
int check_tcp_port(int sockfd, struct sockaddr_in* target, port port,
                   char* buffer);

int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Usage: ./port_scanner <ip_address> <port>");
        return 1;
    }

    char* ipaddr = argv[1];
    port port;

    // let's do just a simple tcp scanning for now and move on
    struct sockaddr_in target;
    char buffer[1024] = {0};

    int sockfd = sock_create(TCP);
    if (sockfd < 0) {
        perror("socket creation failed");
        return 1;
    }

    target.sin_family = AF_INET;
    inet_pton(AF_INET, ipaddr, &target.sin_addr.s_addr);

    if (check_tcp_port(sockfd, &target, port, buffer) < 0) {
        fprintf(stderr, "Port 80 is closed\n");
    } else {
        printf("Port 80 is open\n");
    }

    close(sockfd);
    return 0;
}

int sock_create(conType type) {
    int sockfd;

    switch (type) {
        case TCP:
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            break;
        case UDP:
            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            break;
    }

    return sockfd;
}

int check_tcp_port(int sockfd, struct sockaddr_in* target, port port,
                   char* buffer) {
    target->sin_port = htons(port.value.portNum);
    char* message = "\x01";

    if (connect(sockfd, (struct sockaddr*)target, sizeof(*target)) < 0) {
        perror("tcp handshake failed [connect]\n");
        return -1;
    }

    if (send(sockfd, message, sizeof(message), 0) < 0) {
        perror("send failed");
        return -1;
    }

    return recv(sockfd, buffer, sizeof(buffer), 0);
}