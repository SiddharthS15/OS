#include <stdio.h>

#define MAX_FRAMES 10

int findOptimal(int frames[], int frameCount, int pages[], int pageCount, int currentIndex) {
    int farthest = currentIndex, indexToReplace = -1;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    indexToReplace = i;
                }
                break;
            }
        }
        // If the frame is never going to be used again
        if (j == pageCount) {
            return i; // Replace this frame
        }
    }
    
    // If all pages are used in the future, replace the one that is used the farthest in the future
    return (indexToReplace != -1) ? indexToReplace : 0;
}

int isPageInFrames(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return 1; // Page found in frames
        }
    }
    return 0; // Page not found
}

int main() {
    int frameCount, pageCount;
    int pageFaults = 0;

    // Input: Number of frames and number of pages in the reference string
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);

    int pages[pageCount];
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    int frames[MAX_FRAMES];
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames as empty
    }

    // Processing each page in the reference string
    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i];

        // Check if the current page is already in the frames
        if (!isPageInFrames(frames, frameCount, currentPage)) {
            // Page fault occurs as the page is not in frames
            int indexToReplace = findOptimal(frames, frameCount, pages, pageCount, i); // Find the optimal frame to replace
            frames[indexToReplace] = currentPage; // Replace the optimal frame with the current page
            pageFaults++; // Increment page faults
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

