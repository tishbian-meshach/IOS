//PROGRAM FOR SIMULATION OF LS UNIX COMMANDS

#include <stdio.h>
#include <stdlib.h> // For exit function
#include <dirent.h> // For directory operations

int main(int argc, char **argv) {
    DIR *directoryPointer;
    struct dirent *entry;


    // Open the directory
    directoryPointer = opendir(argv[1]);
    if (directoryPointer == NULL) {
        printf("Unable to open directory: %s\n", argv[1]);
        exit(1);
    }

    // Print the contents of the directory
    printf("\nContents of the directory %s are:\n", argv[1]);
    while ((entry = readdir(directoryPointer)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directoryPointer);

    return 0;
}
