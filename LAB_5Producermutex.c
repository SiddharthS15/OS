#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

int *buffer;
int buffer_size;
int count = 0;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < buffer_size; i++) {
        item = rand() % 100;
        pthread_mutex_lock(&mutex);
        while (count == buffer_size)
            pthread_cond_wait(&not_full, &mutex);
        buffer[count++] = item;
        printf("Producer produced: %d\n", item);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
       // sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < buffer_size; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);
        item = buffer[--count];
        printf("Consumer consumed: %d\n", item);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        //sleep(1);
    }
    return NULL;
}

int main() {
    int prod_items, cons_items;
    
    // Take user input for buffer size, number of items to produce and consume
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    printf("Enter the number of items to be produced: ");
    scanf("%d", &prod_items);

    printf("Enter the number of items to be consumed: ");
    scanf("%d", &cons_items);

    // Dynamically allocate buffer based on user input
    buffer = (int*) malloc(buffer_size * sizeof(int));

    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up resources
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    free(buffer);  // Free dynamically allocated memory

    return 0;
}
