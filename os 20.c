#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readCount = 0;      // number of readers currently accessing
int data = 0;           // shared data (resource)

sem_t mutex;            // for updating readCount
sem_t writeBlock;       // blocks writers when readers are active

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);           // lock to update readCount
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeBlock);  // first reader blocks writers
        }
        sem_post(&mutex);           // unlock

        // Reading section
        printf("Reader %d: read data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);           // lock to update readCount
        readCount--;
        if (readCount == 0) {
            sem_post(&writeBlock);  // last reader unblocks writers
        }
        sem_post(&mutex);           // unlock

        sleep(1);  // simulate other work
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&writeBlock);      // writer waits for access

        // Writing section
        data++;
        printf("Writer %d: wrote data = %d\n", id, data);
        sleep(1);

        sem_post(&writeBlock);      // writer releases access

        sleep(2);  // simulate other work
    }
    return NULL;
}

int main() {
	int i;
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3};
    int w_id[2] = {1, 2};
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    for (i = 0; i < 3; i++) {
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    }
    for (i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }
    for (i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
    }

    for (i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}
