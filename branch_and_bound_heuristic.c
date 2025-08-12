#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 4  // Number of nodes in the graph

int graph[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int bestCost = INT_MAX;
int bestPath[N];

// Simple heuristic: minimum outgoing edge from a node
int heuristic(int node, int visited[]) {
    int minEdge = INT_MAX;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[node][i] != 0 && graph[node][i] < minEdge) {
            minEdge = graph[node][i];
        }
    }
    return (minEdge == INT_MAX) ? 0 : minEdge;
}

void branchBoundHeuristic(int level, int path[], int visited[], int cost) {
    if (level == N) {
        cost += graph[path[level - 1]][path[0]]; // Return to start
        if (cost < bestCost) {
            bestCost = cost;
            for (int i = 0; i < N; i++)
                bestPath[i] = path[i];
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int estimatedCost = cost + graph[path[level - 1]][i] + heuristic(i, visited);
            if (estimatedCost < bestCost) {
                visited[i] = 1;
                path[level] = i;
                branchBoundHeuristic(level + 1, path, visited, cost + graph[path[level - 1]][i]);
                visited[i] = 0;
            }
        }
    }
}

int main() {
    int visited[N] = {0};
    int path[N];
    
    visited[0] = 1;  // Start from node 0
    path[0] = 0;

    branchBoundHeuristic(1, path, visited, 0);

    printf("Optimal Path with Estimated Heuristic: ");
    for (int i = 0; i < N; i++)
        printf("%d ", bestPath[i]);
    printf("%d\n", bestPath[0]); // return to start

    printf("Minimum Cost: %d\n", bestCost);
    return 0;
}
