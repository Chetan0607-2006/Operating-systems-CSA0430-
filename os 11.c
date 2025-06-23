#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_even(void* arg) {
	int i;
    for ( i = 0; i <= 10; i++) {
        if (i % 2 == 0) {
            printf("Even Thread: %d\n", i);
        }
    }
    pthread_exit(NULL);
}

void* print_odd(void* arg) {
	int i;
    for (i = 0; i <= 10; i++) {
        if (i % 2 != 0) {
            printf("Odd Thread: %d\n", i);
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main Thread: Both threads finished execution.\n");

    return 0;
}

