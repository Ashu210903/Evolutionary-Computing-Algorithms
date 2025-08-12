#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HISTORY 50
#define STEP_SIZE 1
#define GOAL 50

// Function to evaluate the "score" of a state
int heuristic(int state) {
    return abs(GOAL - state); // lower is better
}

// Function to check if a state was already visited
int visited_before(int history[], int count, int state) {
    for (int i = 0; i < count; i++) {
        if (history[i] == state) {
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int current = rand() % 100; // starting state
    int history[MAX_HISTORY];
    int history_count = 0;

    history[history_count++] = current;

    printf("Initial State: %d (Heuristic: %d)\n", current, heuristic(current));

    while (heuristic(current) > 0) {
        int next = current + ((rand() % 2) ? STEP_SIZE : -STEP_SIZE);

        // Prevent negative numbers
        if (next < 0) next = 0;

        // If we've visited this state, skip it
        if (visited_before(history, history_count, next)) {
            printf("State %d already visited. Skipping...\n", next);
            continue;
        }

        // Record this state
        if (history_count < MAX_HISTORY) {
            history[history_count++] = next;
        }

        // Accept if heuristic is better
        if (heuristic(next) < heuristic(current)) {
            current = next;
            printf("Moved to State: %d (Heuristic: %d)\n", current, heuristic(current));
        } else {
            printf("Rejected State: %d (Worse heuristic)\n", next);
        }
    }

    printf("Goal reached! State: %d\n", current);

    return 0;
}
