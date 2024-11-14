#include <stdio.h>
#include <stdlib.h>

void calculateSSTF(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    int visited[n];  // Array to keep track of visited requests
    int i, count = 0;

    // Initialize the visited array
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nDisk Scheduling using SSTF Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");
    
    while (count < n) {
        int min_seek_time = 10000; // Arbitrary large value
        int min_index = -1;

        // Find the closest request
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                int seek_time = abs(requests[i] - current_head);
                if (seek_time < min_seek_time) {
                    min_seek_time = seek_time;
                    min_index = i;
                }
            }
        }

        // Process the closest request
        if (min_index != -1) {
            total_seek_time += min_seek_time; // Update total seek time
            printf("|      %2d      |    %3d     |     %3d        |\n", count + 1, requests[min_index], min_seek_time);
            current_head = requests[min_index]; // Move head to the current request
            visited[min_index] = 1; // Mark this request as visited
            count++;
        }
    }

    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time); // Display total seek time
}

int main() {
    int n;
    int initial_head;

    // Accept number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Calculate and display the SSTF scheduling
    calculateSSTF(requests, n, initial_head);

    return 0;
}

