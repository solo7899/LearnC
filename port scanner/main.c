#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef enum _conType { TCP, UDP } conType;

typedef struct port {
    enum { TYPE_INT, TYPE_RANGE } type;
    union {
        int portNum;
        int portRange[2];
    } value;
} port;

int sock_create(conType type);
int check_tcp_port(int sockfd, struct sockaddr_in* target, int port,
                   char* buffer);
int tcp_scan(port port, struct sockaddr_in* target, char* buffer);
void tcp_conditional_wrapper(int sockfd, struct sockaddr_in* target, int port,
                             char* buffer);

int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Usage: ./port_scanner <ip_address> <port>");
        return 1;
    }

    char* buffer;
    char* ipaddr = argv[1];
    port port;

    // let's do just a simple tcp scanning for now and move on
    struct sockaddr_in* target;
    target = malloc(sizeof(struct sockaddr_in));

    target->sin_family = AF_INET;
    inet_pton(AF_INET, ipaddr, &target->sin_addr.s_addr);

    if (strchr(argv[2], '-')) {
        if (sscanf(argv[2], "%d-%d", &port.value.portRange[0],
                   &port.value.portRange[1]) != 2) {
            fprintf(stderr, "Invalid port range\n");
            return 1;
        }
        port.type = TYPE_RANGE;
    } else {
        port.value.portNum = atoi(argv[2]);
        port.type = TYPE_INT;
    }

    tcp_scan(port, &target, buffer);

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

int check_tcp_port(int sockfd, struct sockaddr_in* target, int port,
                   char* buffer) {
    target->sin_port = htons(port);
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

int tcp_scan(port port, struct sockaddr_in* target, char* buffer) {
    switch (port.type) {
        case TYPE_INT:
            int sockfd = sock_create(TCP);
            if (sockfd < 0) {
                perror("socket creation failed");
                return -1;
            }

            tcp_conditional_wrapper(sockfd, target, port.value.portNum, buffer);
            close(sockfd);

            break;
        case TYPE_RANGE:

            for (int i = port.value.portRange[0]; i <= port.value.portRange[1];
                 i++) {
                int sockfd = sock_create(TCP);
                if (sockfd < 0) {
                    perror("socket creation failed");
                    return -1;
                }

                tcp_conditional_wrapper(sockfd, target, i, buffer);
                close(sockfd);
            }

            break;
    }
}

void tcp_conditional_wrapper(int sockfd, struct sockaddr_in* target, int port,
                             char* buffer) {
    if (check_tcp_port(sockfd, target, port, buffer) < 0)
        fprintf(stderr, "Port %d is closed\n", port);
    else
        printf("Port %d is open\n", port);
}