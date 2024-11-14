#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>




#define N 5




sem_t forks[N];




void *philosopher(void *arg) {
    int id = *((int *)arg);




    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(100000);




        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);




        printf("Philosopher %d is eating.\n", id);
        usleep(100000);




        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);




        printf("Philosopher %d finished eating.\n", id);
        usleep(100000);
    }
    return NULL;
}




int main() {
    pthread_t philosophers[N];
    int ids[N];




    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);




    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }




    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);




    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);




    return 0;
}
