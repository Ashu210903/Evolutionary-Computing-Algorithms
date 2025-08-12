#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5  // Size of solution array
#define MAX_VALUE 9 // Max number allowed in solution

// Function to check if two arrays match
int isGoal(int arr[], int goal[]) {
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] != goal[i])
            return 0;
    }
    return 1;
}

// Function to generate a random solution
void generateRandom(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % (MAX_VALUE + 1);
    }
}

// Function to print an array
void printArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int goal[SIZE] = {1, 3, 5, 7, 9};  // Target solution
    int candidate[SIZE];
    long attempts = 0;

    srand(time(0)); // Random seed

    while (1) {
        generateRandom(candidate);
        attempts++;

        if (isGoal(candidate, goal)) {
            printf("Solution found after %ld attempts!\n", attempts);
            printf("Solution: ");
            printArray(candidate);
            break;
        }
    }

    return 0;
}
