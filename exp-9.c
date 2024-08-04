//ALGORITHM FOR DEADLOCK DETECTION

#include <stdio.h>
#include <conio.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int maxResources[MAX_PROCESSES][MAX_RESOURCES];
int allocatedResources[MAX_PROCESSES][MAX_RESOURCES];
int neededResources[MAX_PROCESSES][MAX_RESOURCES];
int availableResources[MAX_RESOURCES];
int numProcesses, numResources;

void getInput();
void displayData();
void checkDeadlock();

int main() {
    printf("********** Deadlock Detection Algorithm ************\n");
    getInput();
    displayData();
    checkDeadlock();
    getch();
    return 0;
}

void getInput() {
    printf("Enter the number of Processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of Resource Instances: ");
    scanf("%d", &numResources);

    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &maxResources[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocatedResources[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int j = 0; j < numResources; j++) {
        scanf("%d", &availableResources[j]);
    }
}

void displayData() {
    printf("\nProcess\t\tAllocation\t\tMax\t\tAvailable\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t\t", i + 1);
        for (int j = 0; j < numResources; j++) {
            printf("%d ", allocatedResources[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < numResources; j++) {
            printf("%d ", maxResources[i][j]);
        }
        if (i == 0) {
            printf("\t\t");
            for (int j = 0; j < numResources; j++) {
                printf("%d ", availableResources[j]);
            }
        }
        printf("\n");
    }
}

void checkDeadlock() {
    int finish[MAX_PROCESSES] = {0};
    int deadlockedProcesses[MAX_PROCESSES];
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Calculate the need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            neededResources[i][j] = maxResources[i][j] - allocatedResources[i][j];
        }
    }

    while (1) {
        int found = 0;
        for (int i = 0; i < numProcesses; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (neededResources[i][j] > availableResources[j])
                        break;
                }
                if (j == numResources) {
                    for (int k = 0; k < numResources; k++) {
                        availableResources[k] += allocatedResources[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }

    int deadlock = 0;
    for (int i = 0; i < numProcesses; i++) {
        if (finish[i] == 0) {
            deadlockedProcesses[deadlock++] = i;
        }
    }

    if (deadlock > 0) {
        printf("\n\nSystem is in Deadlock. The Deadlocked processes are:\n");
        for (int i = 0; i < deadlock; i++) {
            printf("P%d\t", deadlockedProcesses[i]);
        }
    } else {
        printf("\nNo Deadlock Occurred");
    }
}
