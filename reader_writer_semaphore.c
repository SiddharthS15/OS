#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// Shared resource
int shared_data = 0;

// Counter for readers
int readcnt = 0;  // Equivalent to read_count in the original code

// Semaphores
sem_t mutex;    // Protects readcnt (equivalent to read_count_mutex)
sem_t wrt;      // Controls writers (equivalent to wrt in the pseudocode)
sem_t read_lock;  // Semaphore to control access to readcnt (reader synchronization)

int MAX_ITERATIONS = 5;  // Max iterations for readers and writers

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);  // Dereference the pointer to get the value of id
    free(arg);  // Free the dynamically allocated memory

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Reader wants to enter the critical section
        sem_wait(&read_lock);  // Ensure mutual exclusion for readcnt
        readcnt++;
        if (readcnt == 1) {
            // First reader locks wrt to block writers
            sem_wait(&wrt);  // Equivalent to wait(wrt)
        }
        sem_post(&read_lock);  // Allow other readers to enter by unlocking read_lock

        // Reader is reading the shared resource
        printf("Reader %d is reading shared data: %d\n", id, shared_data);

        // Reader finished reading
        sem_wait(&read_lock);  // Lock to update readcnt
        readcnt--;
        if (readcnt == 0) {
            // Last reader unlocks wrt to allow writers
            sem_post(&wrt);  // Equivalent to signal(wrt)
        }
        sem_post(&read_lock);  // Allow other readers/writers to proceed
    }

    return NULL;
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);  // Dereference the pointer to get the value of id
    free(arg);  // Free the dynamically allocated memory

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // Writer wants to write
        sem_wait(&wrt);  // Equivalent to wait(wrt)

        // Writer is writing to the shared resource
        shared_data += 10;  // Modifying the shared resource
        printf("Writer %d is writing new shared data: %d\n", id, shared_data);

        sem_post(&wrt);  // Equivalent to signal(wrt) to allow other readers/writers
    }

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);        // Binary semaphore for mutual exclusion (not used directly in this version)
    sem_init(&wrt, 0, 1);          // Semaphore for controlling access to writers (1 means writer access is allowed)
    sem_init(&read_lock, 0, 1);    // Semaphore for controlling access to the read count (ensures mutual exclusion)

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;  // Set the reader's ID
        pthread_create(&readers[i], NULL, reader, id);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;  // Set the writer's ID
        pthread_create(&writers[i], NULL, writer, id);
    }

    // Wait for threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&read_lock);

    printf("All readers and writers have finished their operations.\n");

    return 0;
}
