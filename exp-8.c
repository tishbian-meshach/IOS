//BANKERS ALGORITHM FOR DEADLOCK AVOIDANCE

#include <stdio.h>
#include <stdlib.h>
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
void calculateSafety();

int main() {
    printf("********** Banker's Algorithm ************\n");
    getInput();
    displayData();
    calculateSafety();
    getch();
    return 0;
}

void getInput() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resource instances: ");
    scanf("%d", &numResources);

    printf("Enter the Max Matrix:\n");
    for(int i = 0; i < numProcesses; i++) {
        for(int j = 0; j < numResources; j++) {
            scanf("%d", &maxResources[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for(int i = 0; i < numProcesses; i++) {
        for(int j = 0; j < numResources; j++) {
            scanf("%d", &allocatedResources[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for(int j = 0; j < numResources; j++) {
        scanf("%d", &availableResources[j]);
    }
}

void displayData() {
    printf("\nProcess\tAllocation\tMax\t\tAvailable\n");
    for(int i = 0; i < numProcesses; i++) {
        printf("P%d\t", i + 1);
        for(int j = 0; j < numResources; j++) {
            printf("%d ", allocatedResources[i][j]);
        }
        printf("\t");
        for(int j = 0; j < numResources; j++) {
            printf("%d ", maxResources[i][j]);
        }
        printf("\t");
        if(i == 0) {
            for(int j = 0; j < numResources; j++) {
                printf("%d ", availableResources[j]);
            }
        }
        printf("\n");
    }
}

void calculateSafety() {
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    int count = 0;

    for(int i = 0; i < numResources; i++) {
        work[i] = availableResources[i];
    }

    for(int i = 0; i < numProcesses; i++) {
        for(int j = 0; j < numResources; j++) {
            neededResources[i][j] = maxResources[i][j] - allocatedResources[i][j];
        }
    }

    while(count < numProcesses) {
        int found = 0;
        for(int i = 0; i < numProcesses; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < numResources; j++) {
                    if(neededResources[i][j] > work[j])
                        break;
                }
                if(j == numResources) {
                    for(int k = 0; k < numResources; k++) {
                        work[k] += allocatedResources[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0) {
            printf("\nThe system is in an unsafe state.\n");
            return;
        }
    }

    printf("\nThe system is in a safe state.\nSafe sequence is: ");
    for(int i = 0; i < numProcesses; i++) {
        printf("P%d ", safeSequence[i] + 1);
    }
    printf("\n");
}
