//PROGRAM FOR SYSTEM CALLS OF UNIX OPERATING SYSTEM(fork,getpid, exit)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int processID, parentProcessID, childProcessID;
    processID = fork();


    if (processID == -1) {
        printf("ERROR IN PROCESS CREATION\n");
        exit(1);
    }


    if (processID != 0) {
        parentProcessID = getpid();
        printf("The parent process ID is %d\n", parentProcessID);
    }

    else {
        childProcessID = getpid();
        printf("The child process ID is %d\n", childProcessID);
    }

    return 0;
}
