//CPU SCHEDULING ALGORITHMS - PRIORITY

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processNumber; // Process number
    int priority;      // Priority of the process
    int burstTime;     // Burst time required by the process
    int waitingTime;   // Waiting time of the process
} Process;

int main() {
    int i, j, numProcesses;
    int totalBurstTime = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process *processArray, tempProcess;

    printf("\nPRIORITY SCHEDULING.\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    // Allocate memory for 'numProcesses' processes
    processArray = (Process *)malloc(numProcesses * sizeof(Process));
    if (processArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the burst time and priority for each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process %d:\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &processArray[i].burstTime);
        printf("Priority: ");
        scanf("%d", &processArray[i].priority);
        processArray[i].processNumber = i + 1;
        processArray[i].waitingTime = 0; // Initial waiting time is 0
    }

    // Sort processes by priority
    for (i = 0; i < numProcesses - 1; i++) {
        for (j = i + 1; j < numProcesses; j++) {
            if (processArray[i].priority > processArray[j].priority) {
                tempProcess = processArray[i];
                processArray[i] = processArray[j];
                processArray[j] = tempProcess;
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < numProcesses; i++) {
        if (i == 0) {
            processArray[i].waitingTime = 0; // First process has 0 waiting time
        } else {
            processArray[i].waitingTime = totalBurstTime;
        }
        totalBurstTime += processArray[i].burstTime;
        totalWaitingTime += processArray[i].waitingTime;

        printf("%d\t%d\t\t%d\t\t%d\n", processArray[i].processNumber, processArray[i].burstTime,
               processArray[i].waitingTime, processArray[i].waitingTime + processArray[i].burstTime);
    }

    totalTurnaroundTime = totalBurstTime + totalWaitingTime;

    printf("\nTotal Waiting Time: %d", totalWaitingTime);
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / numProcesses);
    printf("\nTotal Turnaround Time: %d", totalTurnaroundTime);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / numProcesses);

    // Free allocated memory
    free(processArray);

    return 0;
}
