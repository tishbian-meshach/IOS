//IPC USING SHARED MEMORY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHARED_MEMORY_SIZE 100  // Define the size of the shared memory segment

int main(int argc, char *argv[]) {
    int sharedMemoryId;
    key_t sharedMemoryKey;
    char *sharedMemoryPtr;
    char message[] = "poooda......";

    // Generate a unique key for the shared memory segment
    sharedMemoryKey = ftok(".", 's');
    if (sharedMemoryKey == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    if ((sharedMemoryId = shmget(sharedMemoryKey, SHARED_MEMORY_SIZE, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        // If segment exists, get the shared memory ID
        if ((sharedMemoryId = shmget(sharedMemoryKey, SHARED_MEMORY_SIZE, 0)) == -1) {
            perror("shmget");
            exit(1);
        }
    } else {
        printf("Creating a new shared memory segment\n");
        printf("Shared Memory ID: %d\n", sharedMemoryId);
    }

    // Display shared memory segments using the system command
    system("ipcs -m");

    // Attach the shared memory segment to the process's address space
    if ((sharedMemoryPtr = (char *)shmat(sharedMemoryId, 0, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Write data to the shared memory segment
    printf("Writing data to shared memory...\n");
    strcpy(sharedMemoryPtr, message);
    printf("DONE\n");

    // Read data from the shared memory segment
    printf("Reading data from shared memory...\n");
    printf("DATA: %s\n", sharedMemoryPtr);
    printf("DONE\n");

    // Detach the shared memory segment from the process's address space
    if (shmdt(sharedMemoryPtr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Remove the shared memory segment
    printf("Removing shared memory segment...\n");
    if (shmctl(sharedMemoryId, IPC_RMID, 0) == -1) {
        printf("Can't remove shared memory segment...\n");
    } else {
        printf("Removed successfully\n");
    }

    return 0;
}
