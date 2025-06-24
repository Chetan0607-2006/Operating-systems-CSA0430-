#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function for thread execution
void* threadFunction1(void* arg) {
    printf("Thread 1 is running.\n");
    pthread_exit(NULL); // Explicit thread termination
}

void* threadFunction2(void* arg) {
    printf("Thread 2 is running.\n");
    return NULL; // Implicit thread termination
}

int main() {
    pthread_t tid1, tid2;
    int res;

    // (i) pthread_create
    res = pthread_create(&tid1, NULL, threadFunction1, NULL);
    if (res != 0) {
        printf("Failed to create thread 1\n");
        return 1;
    }

    res = pthread_create(&tid2, NULL, threadFunction2, NULL);
    if (res != 0) {
        printf("Failed to create thread 2\n");
        return 1;
    }

    // (iii) pthread_equal
    if (pthread_equal(tid1, tid2)) {
        printf("Thread 1 and Thread 2 are equal.\n");
    } else {
        printf("Thread 1 and Thread 2 are not equal.\n");
    }

    // (ii) pthread_join
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Both threads have finished execution.\n");

    return 0;
}

