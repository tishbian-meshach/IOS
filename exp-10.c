//THREADING & SYNCHRONIZATION APPLICATIONS

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t threadIDs[2];  // Array to hold thread IDs

// Function to be executed by each thread
void* threadFunction(void *arg) {
    unsigned long i = 0;
    pthread_t currentThreadID = pthread_self();

    if (pthread_equal(currentThreadID, threadIDs[0])) {
        printf("\nFirst thread processing\n");
    } else {
        printf("\nSecond thread processing\n");
    }

    for (i = 0; i < (0xFFFFFFFF); i++);  // Simulate some work with a delay
    return NULL;
}

int main(void) {
    int i = 0;
    int threadCreationError;

    // Create two threads
    while (i < 2) {
        threadCreationError = pthread_create(&(threadIDs[i]), NULL, &threadFunction, NULL);
        if (threadCreationError != 0) {
            printf("\nCan't create thread: [%s]", strerror(threadCreationError));
        } else {
            printf("\nThread created successfully\n");
        }
        i++;
    }

    // Give enough time for the threads to finish their work
    sleep(5);

    return 0;
}
