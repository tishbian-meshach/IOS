//FILE ALLOCATION STRATEGIES - INDEXED

#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

int blocks[MAX_BLOCKS], indexBlocks[MAX_BLOCKS];

int main() {
    int indexBlock, numFiles, choice, i, j;

    // Initialize all blocks as free
    for (i = 0; i < MAX_BLOCKS; i++)
        blocks[i] = 0;

    while (1) {
        printf("Enter index block: ");
        scanf("%d", &indexBlock);

        if (blocks[indexBlock] == 0) {
            blocks[indexBlock] = 1;
            printf("Enter number of files on index: ");
            scanf("%d", &numFiles);

            printf("Enter the blocks for files:\n");
            for (i = 0; i < numFiles; i++)
                scanf("%d", &indexBlocks[i]);

            // Check if the blocks are already allocated
            for (i = 0; i < numFiles; i++) {
                if (blocks[indexBlocks[i]] == 1) {
                    printf("Block %d already allocated. Please try again.\n", indexBlocks[i]);
                    blocks[indexBlock] = 0; // Reset the index block
                    goto end;
                }
            }

            // Allocate the blocks
            for (j = 0; j < numFiles; j++)
                blocks[indexBlocks[j]] = 1;

            printf("\nBlocks allocated successfully.\n");
            printf("File indexed:\n");
            for (j = 0; j < numFiles; j++)
                printf("%d -> %d\n", indexBlock, indexBlocks[j]);
        } else {
            printf("Index block %d is already allocated. Please try again.\n", indexBlock);
        }

        end:
        printf("Enter 1 to enter more files or 0 to exit: ");
        scanf("%d", &choice);
        if (choice == 0)
            break;
    }

    return 0;
}
