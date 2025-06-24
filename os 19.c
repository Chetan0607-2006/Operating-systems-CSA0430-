#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0; // shared variable
pthread_mutex_t lock;

void* increment(void* arg) {
	int i;
    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock); // enter critical section

        int temp = counter;
        printf("Thread %ld incrementing counter from %d to %d\n",
               (long)pthread_self(), temp, temp + 1);
        counter = temp + 1;

        pthread_mutex_unlock(&lock); // exit critical section
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }

    // Create threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter Value: %d\n", counter);

    // Destroy mutex
    pthread_mutex_destroy(&lock);
    return 0;
}

