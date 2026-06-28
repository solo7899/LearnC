#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

typedef enum _conType { TCP, UDP } conType;

int main() {
    printf("starting the project after some research\n");
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

    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket\n");
        return -1;
    }

    return sockfd;
}