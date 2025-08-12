#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STEPS 100
#define GOAL 42

// The oracle knows exactly how to reach the goal from any state
int oracle_move(int current) {
    if (current < GOAL) return current + 1;
    if (current > GOAL) return current - 1;
    return current;
}

int main() {
    srand(time(NULL));

    int current = rand() % 100; // random starting point
    int steps[MAX_STEPS];
    int step_count = 0;

    printf("Starting at: %d\n", current);

    while (current != GOAL && step_count < MAX_STEPS) {
        steps[step_count++] = current;
        current = oracle_move(current); // Oracle gives the best move
        printf("Oracle moves to: %d\n", current);
    }

    if (current == GOAL) {
        printf("Goal reached at %d in %d steps.\n", current, step_count);
    } else {
        printf("Max steps reached without goal.\n");
    }

    printf("\nPath followed:\n");
    for (int i = 0; i < step_count; i++) {
        printf("%d -> ", steps[i]);
    }
    printf("%d (Goal)\n", current);

    return 0;
}
