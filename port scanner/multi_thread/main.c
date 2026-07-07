#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_THREAD 10
pthread_mutex_t lock;
char* IP;
int counter;

void tcp_ping(int port) {
    char* message = "\x01";
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    if (sockfd < 0) {
        printf("socket creation failed for port %d\n", port);
        return;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP);
    servaddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection failed for port %d\n", port);
        return;
    }

    if (send(sockfd, message, strlen(message) + 1, 0) < 0)
        printf("port %d is closed\n", port);
    else
        printf("port %d is open\n", port);
    close(sockfd);
}

void* worker(void* end) {
    int finish = *(int*)end;
    while (counter <= finish) {
        int count;
        pthread_mutex_lock(&lock);
        count = counter++;
        pthread_mutex_unlock(&lock);
        tcp_ping(count);
    }

    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <ip addr> <ip range>\n", argv[0]);
        return 1;
    }

    IP = argv[1];
    int start, finish;
    sscanf(argv[2], "%d-%d", &start, &finish);

    pthread_mutex_init(&lock, NULL);
    counter = start;

    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)&finish);
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}