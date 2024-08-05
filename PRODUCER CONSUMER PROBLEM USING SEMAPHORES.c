//PRODUCER CONSUMER PROBLEM USING SEMAPHORES

#include <stdio.h>
#include <stdlib.h>

// Semaphore variables
int mutex = 1;   // Mutual exclusion semaphore
int full = 0;    // Counts the number of full slots in the buffer
int empty = 3;   // Counts the number of empty slots in the buffer
int itemCount = 0; // Number of produced items

void producer();
void consumer();
int wait(int);
int signal(int);

int main() {
    int choice;

    printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\n");

    while (1) {
        printf("\nENTER YOUR CHOICE\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    printf("BUFFER IS FULL\n");
                }
            break;

            case 2:
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    printf("BUFFER IS EMPTY\n");
                }
            break;

            case 3:
                exit(0);

            default:
                printf("INVALID CHOICE\n");
        }
    }

    return 0;
}

int wait(int semaphore) {
    return (--semaphore);
}

int signal(int semaphore) {
    return (++semaphore);
}

void producer() {
    mutex = wait(mutex);   // Lock critical section
    full = signal(full);   // Increase count of full slots
    empty = wait(empty);   // Decrease count of empty slots
    itemCount++;
    printf("\nProducer produces item %d\n", itemCount);
    mutex = signal(mutex); // Unlock critical section
}

void consumer() {
    mutex = wait(mutex);   // Lock critical section
    full = wait(full);     // Decrease count of full slots
    empty = signal(empty); // Increase count of empty slots
    printf("\nConsumer consumes item %d\n", itemCount);
    itemCount--;
    mutex = signal(mutex); // Unlock critical section
}
