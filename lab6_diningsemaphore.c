#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM_PHILOSOPHERS 5


// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];


// Philosopher function
void *philosopher(void *num) {
    int id = *(int *)num;


    // Each philosopher thinks, picks up forks, eats, and then puts down forks
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
       // sleep(1);


        // Pick up left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up fork %d (left fork).\n", id, id);


        // Pick up right fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up fork %d (right fork).\n", id, (id + 1) % NUM_PHILOSOPHERS);


        // Eating
        printf("Philosopher %d is eating.\n", id);
        //sleep(2);


        // Put down right fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down fork %d (right fork).\n", id, (id + 1) % NUM_PHILOSOPHERS);


        // Put down left fork
        sem_post(&forks[id]);
        printf("Philosopher %d put down fork %d (left fork).\n", id, id);


        // Thinking
        printf("Philosopher %d is thinking again.\n", id);
        //sleep(1);
    }
    return NULL;
}


int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];


    // Initialize semaphores (one for each fork)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }


    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }


    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }


    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }


    return 0;
}






