//PAGE REPLACEMENT ALGORITHMS - LFU

#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int main() {
    int numFrames, numPages;
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int hitCount = 0, pageFrequency[MAX_PAGES] = {0}, pageTime[MAX_PAGES] = {0};
    int i, j, flag, leastFreq, minTime, replaceIndex;

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &numFrames);

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    // Initialize frames to -1 (indicating they are empty)
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    // Input page reference string
    printf("Enter page numbers:\n");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Process each page in the reference string
    for (i = 0; i < numPages; i++) {
        pageFrequency[pages[i]]++;
        pageTime[pages[i]] = i;
        flag = 1;
        leastFreq = frames[0];

        // Check if the page is already in one of the frames or if there is an empty frame
        for (j = 0; j < numFrames; j++) {
            if (frames[j] == -1 || frames[j] == pages[i]) {
                if (frames[j] != -1) {
                    hitCount++;
                }
                flag = 0;
                frames[j] = pages[i];
                break;
            }

            // Track the least frequently used page
            if (pageFrequency[leastFreq] > pageFrequency[frames[j]]) {
                leastFreq = frames[j];
            }
        }

        // If the page is not found and all frames are full, replace the least frequently used page
        if (flag) {
            minTime = MAX_PAGES;
            for (j = 0; j < numFrames; j++) {
                if (pageFrequency[frames[j]] == pageFrequency[leastFreq] && pageTime[frames[j]] < minTime) {
                    replaceIndex = j;
                    minTime = pageTime[frames[j]];
                }
            }
            pageFrequency[frames[replaceIndex]] = 0;
            frames[replaceIndex] = pages[i];
        }

        // Print the current state of frames
        for (j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    // Output the total number of page hits
    printf("Page hits = %d\n", hitCount);

    return 0;
}
