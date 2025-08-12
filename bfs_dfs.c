#include <stdio.h>

#define MAX 50

int adj[MAX][MAX];
int visitedStart[MAX], visitedGoal[MAX];
int queueStart[MAX], queueGoal[MAX];
int frontS = -1, rearS = -1, frontG = -1, rearG = -1;

void enqueueS(int v) {
    if (rearS == MAX - 1) return;
    if (frontS == -1) frontS = 0;
    queueStart[++rearS] = v;
}

int dequeueS() {
    if (frontS == -1 || frontS > rearS) return -1;
    return queueStart[frontS++];
}

void enqueueG(int v) {
    if (rearG == MAX - 1) return;
    if (frontG == -1) frontG = 0;
    queueGoal[++rearG] = v;
}

int dequeueG() {
    if (frontG == -1 || frontG > rearG) return -1;
    return queueGoal[frontG++];
}

int isIntersect(int n) {
    for (int i = 0; i < n; i++) {
        if (visitedStart[i] && visitedGoal[i])
            return i;
    }
    return -1;
}

void bidirectionalBFS(int start, int goal, int n) {
    enqueueS(start);
    visitedStart[start] = 1;

    enqueueG(goal);
    visitedGoal[goal] = 1;

    while (frontS <= rearS && frontG <= rearG) {
        int currS = dequeueS();
        for (int i = 0; i < n; i++) {
            if (adj[currS][i] && !visitedStart[i]) {
                visitedStart[i] = 1;
                enqueueS(i);
            }
        }

        int currG = dequeueG();
        for (int i = 0; i < n; i++) {
            if (adj[currG][i] && !visitedGoal[i]) {
                visitedGoal[i] = 1;
                enqueueG(i);
            }
        }

        int meet = isIntersect(n);
        if (meet != -1) {
            printf("Path found! Searches meet at node %d\n", meet);
            return;
        }
    }
    printf("No path exists between start and goal.\n");
}

int main() {
    int n, i, j, start, goal;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        visitedStart[i] = 0;
        visitedGoal[i] = 0;
    }

    printf("Enter start vertex: ");
    scanf("%d", &start);

    printf("Enter goal vertex: ");
    scanf("%d", &goal);

    bidirectionalBFS(start, goal, n);

    return 0;
}
