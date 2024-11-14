#include <stdio.h>
#include <stdlib.h>

void calculateCSCAN(int requests[], int n, int initial_head, int disk_size, int direction) {
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

    // Find the starting index where the head should start servicing requests
    int start_index = 0;
    while (start_index < n && requests[start_index] < initial_head) {
        start_index++;
    }

    printf("\nDisk Scheduling using C-SCAN Algorithm:\n");
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

        // Move to the end of the disk, if not already there, and then jump to the start
        if (current_head < disk_size - 1) {
            int end_seek_time = abs(disk_size - 1 - current_head);
            total_seek_time += end_seek_time;
            printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, end_seek_time);
        }
        int reset_seek_time = disk_size - 1;  // Jump from end to start
        total_seek_time += reset_seek_time;
        printf("|      -       |     0     |     %3d        |\n", reset_seek_time);
        current_head = 0;

        // Continue servicing the remaining requests from the start
        for (int i = 0; i < start_index; i++) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", i + n - start_index + 1, requests[i], seek_time);
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

        // Move to the start of the disk and then jump to the end
        if (current_head > 0) {
            int start_seek_time = abs(current_head - 0);
            total_seek_time += start_seek_time;
            printf("|      -       |     0     |     %3d        |\n", start_seek_time);
        }
        int reset_seek_time = disk_size - 1;  // Jump from start to end
        total_seek_time += reset_seek_time;
        printf("|      -       |   %3d     |     %3d        |\n", disk_size - 1, reset_seek_time);
        current_head = disk_size - 1;

        // Continue servicing the remaining requests from the end
        for (int i = n - 1; i >= start_index; i--) {
            int seek_time = abs(requests[i] - current_head);
            total_seek_time += seek_time;
            printf("|      %2d      |    %3d     |     %3d        |\n", n - i, requests[i], seek_time);
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

    // Calculate and display the C-SCAN scheduling
    calculateCSCAN(requests, n, initial_head, disk_size, direction);

    return 0;
}

