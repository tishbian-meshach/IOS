//PROGRAM FOR SYSTEM CALLS OF UNIX OPERATING SYSTEMS (OPENDIR,READDIR, CLOSEDIR)
#include <stdio.h>
#include <stdlib.h> // For exit function
#include <dirent.h> // For directory operations

int main() {
    char directoryName[100];
    DIR *directoryPointer;
    struct dirent *entry;

    // Prompt the user to enter the directory name
    printf("\n\nENTER DIRECTORY NAME: ");
    scanf("%s", directoryName);

    // Try to open the directory
    if ((directoryPointer = opendir(directoryName)) == NULL) {
        // If the directory does not exist, print an error message and exit
        printf("The given directory does not exist\n");
        exit(1);
    }

    // Read and print the names of the files and directories within the directory
    while ((entry = readdir(directoryPointer)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directoryPointer);

    return 0;
}
