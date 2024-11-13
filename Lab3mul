#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX 3  // Size of the matrix (MAX x MAX)
#define NUM_THREADS MAX * MAX  // Number of threads


int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX]; // Matrices for operations
int D[MAX][MAX]; // Result matrix for addition
int E[MAX][MAX]; // Result matrix for multiplication


// Structure to pass data to threads
typedef struct {
    int row;
    int col;
} ThreadData;


// Function for matrix addition
void *matrix_addition(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;
    int col = data->col;


    D[row][col] = A[row][col] + B[row][col];


    pthread_exit(0);
}


// Function for matrix multiplication
void *matrix_multiplication(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;
    int col = data->col;


    E[row][col] = 0;
    for (int k = 0; k < MAX; k++) {
        E[row][col] += A[row][k] * B[k][col];
    }


    pthread_exit(0);
}


int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];


    // Initialize matrices A and B
    printf("Matrix A:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }


    printf("Matrix B:\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }


    // Create threads for matrix addition
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;
            thread_data[i * MAX + j].col = j;
            pthread_create(&threads[i * MAX + j], NULL, matrix_addition, (void *)&thread_data[i * MAX + j]);
        }
    }


    // Join threads for matrix addition
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }


    // Display result of matrix addition
    printf("Result of Matrix Addition (D = A + B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }


    // Create threads for matrix multiplication
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            thread_data[i * MAX + j].row = i;
            thread_data[i * MAX + j].col = j;
            pthread_create(&threads[i * MAX + j], NULL, matrix_multiplication, (void *)&thread_data[i * MAX + j]);
        }
    }


    // Join threads for matrix multiplication
    for (int i = 0; i < MAX * MAX; i++) {
        pthread_join(threads[i], NULL);
    }


    // Display result of matrix multiplication
    printf("Result of Matrix Multiplication (E = A * B):\n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", E[i][j]);
        }
        printf("\n");
    }


    return 0;
}

