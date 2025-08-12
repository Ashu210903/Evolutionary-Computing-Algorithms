#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NEIGHBORS 10

// Function to generate a random value for a state
int getValue(int state) {
    // Example: a simple function where higher state means better value
    // Replace with your heuristic function
    return (100 - abs(50 - state));
}

// Function to generate neighbors of a state
void generateNeighbors(int current, int neighbors[], int *count) {
    *count = 0;
    for (int i = -2; i <= 2; i++) {
        if (i != 0 && current + i >= 0 && current + i <= 100) {
            neighbors[(*count)++] = current + i;
        }
    }
}

// Hill Climbing Algorithm
void hillClimb(int start) {
    int current = start;
    int currentValue = getValue(current);

    printf("Start State: %d | Value: %d\n", current, currentValue);

    while (1) {
        int neighbors[MAX_NEIGHBORS];
        int count = 0;
        generateNeighbors(current, neighbors, &count);

        int bestNeighbor = current;
        int bestValue = currentValue;

        // Evaluate all neighbors
        for (int i = 0; i < count; i++) {
            int val = getValue(neighbors[i]);
            if (val > bestValue) {
                bestValue = val;
                bestNeighbor = neighbors[i];
            }
        }

        // If no improvement, stop
        if (bestValue <= currentValue) {
            printf("Reached Peak at State: %d | Value: %d\n", current, currentValue);
            break;
        }

        // Move to best neighbor
        current = bestNeighbor;
        currentValue = bestValue;
        printf("Move to State: %d | Value: %d\n", current, currentValue);
    }
}

int main() {
    srand(time(NULL));

    int start;
    printf("Enter starting state (0-100): ");
    scanf("%d", &start);

    if (start < 0 || start > 100) {
        printf("Invalid start state!\n");
        return 1;
    }

    hillClimb(start);

    return 0;
}
