#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HISTORY 100
#define BEAM_WIDTH 3
#define GOAL 50

typedef struct {
    int state;
    int heuristic;
} Node;

// Calculate heuristic: lower means closer to goal
int heuristic_value(int state) {
    return abs(GOAL - state);
}

// Check if we already visited a state
int visited_before(int history[], int count, int state) {
    for (int i = 0; i < count; i++) {
        if (history[i] == state) {
            return 1;
        }
    }
    return 0;
}

// Compare two nodes for sorting
int compare_nodes(const void *a, const void *b) {
    Node *n1 = (Node *)a;
    Node *n2 = (Node *)b;
    return n1->heuristic - n2->heuristic; // ascending heuristic
}

int main() {
    srand(time(NULL));

    int history[MAX_HISTORY];
    int history_count = 0;

    Node beam[BEAM_WIDTH];
    // Initialize beam with random states
    for (int i = 0; i < BEAM_WIDTH; i++) {
        beam[i].state = rand() % 100;
        beam[i].heuristic = heuristic_value(beam[i].state);
        history[history_count++] = beam[i].state;
    }

    printf("Initial Beam:\n");
    for (int i = 0; i < BEAM_WIDTH; i++) {
        printf("State: %d (H: %d)\n", beam[i].state, beam[i].heuristic);
    }

    while (1) {
        Node candidates[BEAM_WIDTH * 2];
        int cand_count = 0;

        // Generate neighbors for each beam state
        for (int i = 0; i < BEAM_WIDTH; i++) {
            int step1 = beam[i].state + 1;
            int step2 = beam[i].state - 1;
            if (step2 < 0) step2 = 0;

            int neighbors[2] = {step1, step2};

            for (int j = 0; j < 2; j++) {
                if (!visited_before(history, history_count, neighbors[j])) {
                    candidates[cand_count].state = neighbors[j];
                    candidates[cand_count].heuristic = heuristic_value(neighbors[j]);
                    if (history_count < MAX_HISTORY) {
                        history[history_count++] = neighbors[j];
                    }
                    cand_count++;
                }
            }
        }

        // Sort candidates by heuristic
        qsort(candidates, cand_count, sizeof(Node), compare_nodes);

        // Pick best BEAM_WIDTH candidates
        for (int i = 0; i < BEAM_WIDTH && i < cand_count; i++) {
            beam[i] = candidates[i];
            printf("Selected: %d (H: %d)\n", beam[i].state, beam[i].heuristic);
            if (beam[i].heuristic == 0) {
                printf("Goal reached! State: %d\n", beam[i].state);
                return 0;
            }
        }
        printf("---- Next Iteration ----\n");
    }

    return 0;
}
