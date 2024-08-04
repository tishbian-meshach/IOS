//PAGING TECHNIQUE OF MEMORY MANAGEMENT

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define ITERATIONS 0xFFFFFFFF  // Number of iterations for the job

pthread_t threadIds[2];  // Array to hold thread IDs
int jobCounter;  // Shared counter to keep track of the number of jobs
pthread_mutex_t mutexLock;  // Mutex to synchronize thread access

void* performJob(void *arg) {
    pthread_mutex_lock(&mutexLock);  // Lock the mutex

    unsigned long i = 0;
    jobCounter += 1;  // Increment the job counter
    printf("\n Job %d started\n", jobCounter);

    for (i = 0; i < ITERATIONS; i++);  // Simulate work with a loop

    printf("\n Job %d finished\n", jobCounter);

    pthread_mutex_unlock(&mutexLock);  // Unlock the mutex
    return NULL;
}

int main(void) {
    int i = 0;
    int result;

    // Initialize the mutex
    if (pthread_mutex_init(&mutexLock, NULL) != 0) {
        printf("\n Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    while (i < 2) {
        result = pthread_create(&threadIds[i], NULL, &performJob, NULL);
        if (result != 0) {
            printf("\n Can't create thread : [%s]", strerror(result));
            return 1;
        }
        i++;
    }

    // Wait for threads to finish
    pthread_join(threadIds[0], NULL);
    pthread_join(threadIds[1], NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutexLock);

    return 0;
}
