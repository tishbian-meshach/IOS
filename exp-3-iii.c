//PROGRAM FOR SIMULATION OF GREP UNIX COMMANDS

#include <stdio.h>
#include <stdlib.h> // For exit function
#include <string.h> // For string functions

#define MAX 1024


int main(int argc, char *argv[]) {
    FILE *filePointer;
    char line[MAX];
    char *newline;
    int lineCount = 0;
    int occurrences = 0;


    // Open the file for reading
    if ((filePointer = fopen(argv[1], "r")) == NULL) {
        printf("grep: could not open file: %s\n", argv[1]);
        exit(1);
    }

    // Read each line from the file
    while (fgets(line, MAX, filePointer) != NULL) {
        lineCount++;

        // Remove the newline character if present
        if ((newline = strchr(line, '\n')) != NULL) {
            *newline = '\0';
        }

        // Check if the word is in the current line
        if (strstr(line, argv[2]) != NULL) {
            printf("%s: %d %s\n", argv[1], lineCount, line);
            occurrences++;
        }
    }

    // Close the file
    fclose(filePointer);

    // Optional: Print the number of occurrences found
    if (occurrences == 0) {
        printf("No occurrences found.\n");
    }

    return 0;
}
