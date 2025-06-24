#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
	int i;
    int item;
    for ( i = 0; i < 10; i++) {
        item = rand() % 100;
        sem_wait(&empty); // wait if buffer is full
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // signal that buffer has data

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
	int i;
    int item;
    for ( i = 0; i < 10; i++) {
        sem_wait(&full); // wait if buffer is empty
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // signal empty space

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

