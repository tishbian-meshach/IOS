//PAGE REPLACEMENT ALGORITHMS-LRU

#include <stdio.h>

#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 20

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int pageFaults = 0, numPages, numFrames;
    int i, j, k=0, r, leastRecentlyUsed[MAX_FRAMES], temp;

    // Initialize frames
    for (i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    // Input reference string
    printf("Enter the reference string:\n");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Process pages
    for (i = 0; i < numPages; i++) {
        int pageFound = 0;

        // Check if page is already in one of the frames
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found in frames, replace one
        if (!pageFound) {
            pageFaults++;

            if (k < numFrames) {
                // Fill up the frames initially
                frames[k] = pages[i];
                k++;
            } else {
                // Find the least recently used page
                int useTimes[MAX_FRAMES] = {0};
                for (r = 0; r < numFrames; r++) {
                    useTimes[r] = 0;
                    for (j = i - 1; j >= 0; j--) {
                        if (frames[r] == pages[j]) {
                            useTimes[r] = i - j;
                            break;
                        }
                    }
                }

                // Replace the least recently used page
                int maxIndex = 0;
                for (r = 1; r < numFrames; r++) {
                    if (useTimes[r] > useTimes[maxIndex]) {
                        maxIndex = r;
                    }
                }

                frames[maxIndex] = pages[i];
            }

            // Print the current state of frames
            printf("\nCurrent frames:\n");
            for (j = 0; j < numFrames; j++) {
                printf("\t%d", frames[j]);
            }
            printf("\n");
        }
    }

    // Output the total number of page faults
    printf("\nThe number of page faults is %d\n", pageFaults);

    return 0;
}
