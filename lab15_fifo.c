#include <stdio.h>

#define MAX_FRAMES 10

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
    int nextFrameToReplace = 0; // To keep track of which frame to replace next

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
            frames[nextFrameToReplace] = currentPage; // Replace the page at nextFrameToReplace
            pageFaults++; // Increment page faults
            nextFrameToReplace = (nextFrameToReplace + 1) % frameCount; // Move to the next frame
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

