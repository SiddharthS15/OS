#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared resource
int shared_data = 0;

// Counter for readers
int readcnt = 0;  // Equivalent to `read_count` in the original code

// Mutex for controlling access to the shared resource and reader count
pthread_mutex_t mutex;             // Protects readcnt (equivalent to read_count_mutex)
pthread_mutex_t wrt;               // Equivalent to wrt in the pseudocode, controls writers

// Global variable for MAX_ITERATIONS
int MAX_ITERATIONS = 5;  // Default value, can be updated in the main function

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);
    free(arg);

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Reader wants to enter the critical section
        pthread_mutex_lock(&mutex);  // Equivalent to wait(mutex)
        readcnt++;
        if (readcnt == 1) {
            // First reader locks wrt to block writers
            pthread_mutex_lock(&wrt);  // Equivalent to wait(wrt)
        }
        pthread_mutex_unlock(&mutex);  // Allow other readers to enter by unlocking mutex

        // Reader is reading the shared resource
        printf("Reader %d is reading shared data: %d\n", id, shared_data);
        sleep(1);  // Simulating read time

        // Reader finished reading
        pthread_mutex_lock(&mutex);  // Lock to update readcnt
        readcnt--;
        if (readcnt == 0) {
            // Last reader unlocks wrt to allow writers
            pthread_mutex_unlock(&wrt);  // Equivalent to signal(wrt)
        }
        pthread_mutex_unlock(&mutex);  // Allow other readers/writers to proceed

        sleep(1);  // Simulating delay between reads
    }

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);
    free(arg);

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Writer wants to write
        pthread_mutex_lock(&wrt);  // Equivalent to wait(wrt)

        // Writer is writing to the shared resource
        shared_data += 10;  // Modifying the shared resource
        printf("Writer %d is writing new shared data: %d\n", id, shared_data);

        pthread_mutex_unlock(&wrt);  // Equivalent to signal(wrt) to allow other readers/writers
        sleep(2);  // Simulating write time
    }

    return NULL;
}

int main() {
    int num_readers, num_writers, max_iterations;

    // Take input from the user
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    printf("Enter number of iterations for each reader and writer: ");
    scanf("%d", &max_iterations);

    // Update MAX_ITERATIONS with the user input
    MAX_ITERATIONS = max_iterations;

    pthread_t *readers = malloc(num_readers * sizeof(pthread_t));
    pthread_t *writers = malloc(num_writers * sizeof(pthread_t));

    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);  // For protecting readcnt
    pthread_mutex_init(&wrt, NULL);    // For controlling writers

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    // Wait for threads to complete
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);

    printf("All readers and writers have finished their operations.\n");

    // Free allocated memory
    free(readers);
    free(writers);

    return 0;
}
