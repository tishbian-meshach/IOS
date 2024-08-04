//CPU SCHEDULING ALGORITHMS - FCFS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processID;  // Process ID
    int burstTime;  // Burst time required by the process
    int waitingTime; // Waiting time for the process
    int turnaroundTime; // Turnaround time for the process
} Process;

int main() {
    int i, numProcesses;
    int totalWaitingTime = 0, totalTurnaroundTime = 0, totalBurstTime = 0;
    Process processes[10]; // Array to store processes

    printf("\nFCFS Scheduling...\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (i = 0; i < numProcesses; i++) {
        processes[i].processID = i + 1;
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].waitingTime = 0;
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

    return 0;
}
