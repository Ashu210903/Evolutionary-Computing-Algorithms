#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NEIGHBORS 5
#define BEAM_WIDTH 3

// Simple heuristic function (example: closer to 50 is better)
int getValue(int state) {
    return (100 - abs(50 - state));
}

// Generate neighbors for a given state
void generateNeighbors(int state, int neighbors[], int *count) {
    *count = 0;
    for (int i = -2; i <= 2; i++) {
        if (i != 0 && state + i >= 0 && state + i <= 100) {
            neighbors[(*count)++] = state + i;
        }
    }
}

// Beam Search Algorithm
void beamSearch(int start) {
    int beam[BEAM_WIDTH];
    int beamValues[BEAM_WIDTH];

    // Initialize beam with the start state
    beam[0] = start;
    beamValues[0] = getValue(start);
    for (int i = 1; i < BEAM_WIDTH; i++) {
        beam[i] = -1; // unused slots
        beamValues[i] = -1;
    }

    printf("Initial Beam:\n");
    for (int i = 0; i < BEAM_WIDTH; i++) {
        if (beam[i] != -1)
            printf("State: %d | Value: %d\n", beam[i], beamValues[i]);
    }

    // Main loop
    while (1) {
        int allNeighbors[BEAM_WIDTH * MAX_NEIGHBORS];
        int allValues[BEAM_WIDTH * MAX_NEIGHBORS];
        int totalCount = 0;

        // Expand all states in the beam
        for (int i = 0; i < BEAM_WIDTH; i++) {
            if (beam[i] == -1) continue;

            int neighbors[MAX_NEIGHBORS];
            int count = 0;
            generateNeighbors(beam[i], neighbors, &count);

            for (int j = 0; j < count; j++) {
                allNeighbors[totalCount] = neighbors[j];
                allValues[totalCount] = getValue(neighbors[j]);
                totalCount++;
            }
        }

        // Select the top BEAM_WIDTH states
        int newBeam[BEAM_WIDTH];
        int newBeamValues[BEAM_WIDTH];
        for (int i = 0; i < BEAM_WIDTH; i++) {
            int bestIndex = -1;
            int bestValue = -1;

            for (int j = 0; j < totalCount; j++) {
                if (allValues[j] > bestValue) {
                    bestValue = allValues[j];
                    bestIndex = j;
                }
            }

            if (bestIndex != -1) {
                newBeam[i] = allNeighbors[bestIndex];
                newBeamValues[i] = bestValue;
                allValues[bestIndex] = -999; // mark as used
            } else {
                newBeam[i] = -1;
                newBeamValues[i] = -1;
            }
        }

        // Check if improvement happened
        int improvement = 0;
        for (int i = 0; i < BEAM_WIDTH; i++) {
            if (newBeamValues[i] > beamValues[i]) {
                improvement = 1;
                break;
            }
        }

        if (!improvement) {
            printf("\nBeam Search stopped. Final beam:\n");
            for (int i = 0; i < BEAM_WIDTH; i++) {
                if (beam[i] != -1)
                    printf("State: %d | Value: %d\n", beam[i], beamValues[i]);
            }
            break;
        }

        // Update beam
        for (int i = 0; i < BEAM_WIDTH; i++) {
            beam[i] = newBeam[i];
            beamValues[i] = newBeamValues[i];
        }

        // Print new beam
        printf("\nNew Beam:\n");
        for (int i = 0; i < BEAM_WIDTH; i++) {
            if (beam[i] != -1)
                printf("State: %d | Value: %d\n", beam[i], beamValues[i]);
        }
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

    beamSearch(start);

    return 0;
}
