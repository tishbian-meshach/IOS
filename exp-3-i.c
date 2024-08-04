#include <stdio.h>
#include <stdlib.h> // For exit function

int main(int argc, char *argv[]) {
    FILE *filePointer;
    char character;
    int spaceCount = 0;


    // Open the file in read mode
    filePointer = fopen(argv[1], "r");
    if (filePointer == NULL) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    // Read the file character by character and count spaces
    while ((character = fgetc(filePointer)) != EOF) {
        if (character == ' ') {
            spaceCount++;
        }
    }

    // Print the number of spaces
    printf("Number of spaces: %d\n", spaceCount);

    // Close the file
    fclose(filePointer);

    return 0;
}
