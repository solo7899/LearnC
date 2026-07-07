#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_THREAD 10
pthread_mutex_t lock;
char* IP;
int counter;

void tcp_ping(int port) {
    printf("Pinging port: %d\n", port);
    // Simulate some work with sleep

    sleep(1);
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