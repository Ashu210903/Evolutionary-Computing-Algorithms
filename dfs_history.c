#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];   // adjacency matrix
int visited[MAX];
int history[MAX];
int historyIndex = 0;
int nodes;

// DFS function with history tracking
void dfsHistory(int current) {
    visited[current] = 1;
    history[historyIndex++] = current;

    for (int i = 0; i < nodes; i++) {
        if (graph[current][i] && !visited[i]) {
            dfsHistory(i);
        }
    }
}

int main() {
    int edges, u, v;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    // Initialize adjacency matrix
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected
    }

    // Mark all unvisited
    for (int i = 0; i < nodes; i++)
        visited[i] = 0;

    int start;
    printf("Enter start node: ");
    scanf("%d", &start);

    dfsHistory(start);

    printf("\nDFS with history:\n");
    for (int i = 0; i < historyIndex; i++) {
        printf("%d ", history[i]);
    }
    printf("\n");

    return 0;
}
