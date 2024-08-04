// CPU SCHEDULING ALGORITHMS - ROUND ROBIN SCHEDULING

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int processNumber; // Process number
    int burstTime;     // Original burst time
    int remainingBurstTime; // Remaining burst time
    int waitingTime;   // Waiting time
    int lastStartTime; // Last start time for the process
} Process;

int main() {
    int previousProcessIndex = -1;
    int timeSlice, flag, count;
    int currentTime = 0;
    int numProcesses;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process processes[MAX_PROCESSES];

    printf("\nRound Robin Scheduling...\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    if (numProcesses > MAX_PROCESSES) {
        printf("Number of processes exceeds the maximum allowed (%d).\n", MAX_PROCESSES);
        return 1;
    }

    printf("Enter the time slice (quantum): ");
    scanf("%d", &timeSlice);

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingBurstTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].lastStartTime = 0;
        processes[i].processNumber = i + 1;
    }

    printf("Scheduling...\n");
    do {
        flag = 0;
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].remainingBurstTime > 0) {
                flag = 1;
                count = (processes[i].remainingBurstTime > timeSlice) ? timeSlice : processes[i].remainingBurstTime;

                printf("\nProcess %d from %d to %d", processes[i].processNumber, currentTime, currentTime + count);

                currentTime += count;
                processes[i].remainingBurstTime -= count;

                if (previousProcessIndex != i) {
                    processes[i].waitingTime += currentTime - processes[i].lastStartTime - count;
                    processes[i].lastStartTime = currentTime;
                }

                previousProcessIndex = i;
            }
        }
    } while (flag);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++) {
        int turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += turnaroundTime;

        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processNumber, processes[i].burstTime,
               processes[i].waitingTime, turnaroundTime);
    }

    printf("\nTotal Waiting Time: %d", totalWaitingTime);
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / numProcesses);
    printf("\nTotal Turnaround Time: %d", totalTurnaroundTime);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / numProcesses);

    return 0;
}
