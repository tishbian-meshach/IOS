//CPU SCHEDULING ALGORITHMS - SJF SCHEDULING
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processID;  // Process ID
    int burstTime;  // Burst time required by the process
    int waitingTime; // Waiting time for the process
} Process;

int main() {
    int i, j, numProcesses;
    int totalBurstTime = 0, totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process *processes, tempProcess;

    printf("\nSJF Scheduling...\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    // Allocate memory for processes
    processes = (Process *)malloc(numProcesses * sizeof(Process));
    if (processes == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].processID = i + 1;
        processes[i].waitingTime = 0;
    }

    // Sort processes by burst time
    for (i = 0; i < numProcesses - 1; i++) {
        for (j = i + 1; j < numProcesses; j++) {
            if (processes[i].burstTime > processes[j].burstTime) {
                tempProcess = processes[i];
                processes[i] = processes[j];
                processes[j] = tempProcess;
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < numProcesses; i++) {
        if (i == 0) {
            processes[i].waitingTime = 0; // First process has 0 waiting time
        } else {
            processes[i].waitingTime = totalBurstTime;
        }
        totalBurstTime += processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;

        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime,
               processes[i].waitingTime, processes[i].waitingTime + processes[i].burstTime);
    }

    totalTurnaroundTime = totalBurstTime + totalWaitingTime;

    printf("\nTotal Waiting Time: %d", totalWaitingTime);
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / numProcesses);
    printf("\nTotal Turnaround Time: %d", totalTurnaroundTime);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / numProcesses);
    // Free allocated memory
    free(processes);

    return 0;
}
