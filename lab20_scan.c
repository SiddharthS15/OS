#include <stdio.h>
#include <stdlib.h>

void calculateSCAN(int requests[], int n, int initial_head, int disk_size, int direction) {
    int total_seek_time = 0;
    int current_head = initial_head;

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the starting point where the head should start servicing requests
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }

    printf("\nDisk Scheduling using SCAN Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");

    // Move in the selected direction
    if (direction == 1) {  // Moving right towards higher values
        // Service requests to the right of the initial head position
        for (int i = start_index; i < n; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", i - start_index + 1, requests[i], seek_time);
            current_head = requests[i];
        }

        // Move to the end of the disk
        int end_seek_time = abs(disk_size - 1 - current_head);
        total_seek_time += end_seek_time;
        printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, end_seek_time);
        current_head = disk_size - 1;

        // Reverse direction and service the remaining requests to the left
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", start_index - i + n - 1, requests[i], seek_time);
            current_head = requests[i];
        }
    } else {  // Moving left towards lower values
        // Service requests to the left of the initial head position
        for (int i = start_index - 1; i >= 0; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", start_index - i, requests[i], seek_time);
            current_head = requests[i];
        }

        // Move to the start of the disk
        int end_seek_time = abs(current_head - 0);
        total_seek_time += end_seek_time;
        printf("|      -       |    0      |     %3d        |\n", end_seek_time);
        current_head = 0;

        // Reverse direction and service the remaining requests to the right
        for (int i = start_index; i < n; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", i + 1, requests[i], seek_time);
            current_head = requests[i];
        }
    }

    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time); // Display total seek time
}

int main() {
    int n, initial_head, disk_size, direction;

    // Accept number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Calculate and display the SCAN scheduling
    calculateSCAN(requests, n, initial_head, disk_size, direction);

    return 0;
}

