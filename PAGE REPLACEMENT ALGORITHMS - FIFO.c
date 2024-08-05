//PAGE REPLACEMENT ALGORITHMS - FIFO

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 30
#define MAX_REF_STRING 30

int main() {
    int frames[MAX_FRAMES], referenceString[MAX_REF_STRING];
    int numFrames, numReferences = 0;
    int pageFaults = 0;
    int i, j, currentFrameIndex = 0;
    int isPageInFrame;

    printf("FIFO Page Replacement Algorithm\n");

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Input reference string
    printf("Enter the reference string (end with 0):\n");
    for (i = 0; i < MAX_REF_STRING; i++) {
        int page;
        scanf("%d", &page);
        if (page == 0) {
            break;
        }
        referenceString[numReferences++] = page;
    }

    // Initialize the frames
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;  // -1 indicates that the frame is empty
    }

    // FIFO Page Replacement
    for (i = 0; i < numReferences; i++) {
        isPageInFrame = 0;

        // Check if the page is already in one of the frames
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == referenceString[i]) {
                printf("Page %d is already in the frame.\n", referenceString[i]);
                isPageInFrame = 1;
                break;
            }
        }

        // If the page is not in any of the frames, replace it
        if (!isPageInFrame) {
            frames[currentFrameIndex] = referenceString[i];
            currentFrameIndex = (currentFrameIndex + 1) % numFrames;
            pageFaults++;

            // Print the current state of the frames
            printf("\nCurrent frames:\n");
            for (j = 0; j < numFrames; j++) {
                printf("Frame %d: %d", j + 1, frames[j]);
                if (frames[j] == referenceString[i]) {
                    printf(" *");
                }
                printf("\n");
            }
        }
    }

    // Output the total number of page faults
    printf("\nTotal number of page faults: %d\n", pageFaults);

    return 0;
}
