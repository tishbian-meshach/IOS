//MEMORY ALLOCATION METHODS FOR FIXED PARTITION - BEST FIT

#include <stdio.h>

#define MAX_SIZE 25

void main() {
    int fragment[MAX_SIZE], blockSize[MAX_SIZE], fileSize[MAX_SIZE];
    int i, j, numberOfBlocks, numberOfFiles, temp, largestFragment = 10000;
    static int blockFlag[MAX_SIZE], fileFlag[MAX_SIZE];

    printf("\nEnter the number of blocks: ");
    scanf("%d", &numberOfBlocks);
    printf("Enter the number of files: ");
    scanf("%d", &numberOfFiles);

    // Input the size of each block
    printf("\nEnter the size of the blocks:\n");
    for (i = 1; i <= numberOfBlocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &blockSize[i]);
    }

    // Input the size of each file
    printf("Enter the size of the files:\n");
    for (i = 1; i <= numberOfFiles; i++) {
        printf("File %d: ", i);
        scanf("%d", &fileSize[i]);
    }

    // Worst Fit allocation
    for (i = 1; i <= numberOfFiles; i++) {
        for (j = 1; j <= numberOfBlocks; j++) {
            if (blockFlag[j] != 1) {  // Check if the block is not allocated
                temp = blockSize[j] - fileSize[i];
                if (temp >= 0 && largestFragment < temp) {
                    fileFlag[i] = j;  // Allocate block j to file i
                    largestFragment = temp;
                }
            }
        }
        fragment[i] = largestFragment;  // Calculate the fragment size
        blockFlag[fileFlag[i]] = 1;  // Mark block as allocated
        largestFragment = 10000;  // Reset largestFragment for the next file
    }
    // Print the allocation result
    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= numberOfFiles; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t%d", i, fileSize[i], fileFlag[i], blockSize[fileFlag[i]], fragment[i]);
    }

}
