#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_THREAD 10
pthread_mutex_t lock;
int counter;

void tcp_ping(int port) {
    printf("Pinging port: %d\n", port);
    // Simulate some work with sleep
    sleep(1);
}

void* worker() {
    while (counter < 100) {
        int count;
        pthread_mutex_lock(&lock);
        count = counter++;
        pthread_mutex_unlock(&lock);
        tcp_ping(count);
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);
    counter = 50;

    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}