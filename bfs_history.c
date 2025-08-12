#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Queue structure for BFS
typedef struct {
    int items[MAX_NODES];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_NODES - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// BFS with History
void bfsWithHistory(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    int visited[MAX_NODES] = {0};
    int history[MAX_NODES] = {0};  // store visit order
    int step = 0;

    Queue q;
    initQueue(&q);

    visited[start] = 1;
    history[step++] = start;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("Visited node: %d\n", current);

        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                history[step++] = i;
                enqueue(&q, i);
            }
        }
    }

    // Print history
    printf("\nTraversal History Order: ");
    for (int i = 0; i < step; i++) {
        printf("%d ", history[i]);
    }
    printf("\n");
}

int main() {
    int nodes;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    int graph[MAX_NODES][MAX_NODES];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int start;
    printf("Enter start node: ");
    scanf("%d", &start);

    bfsWithHistory(graph, nodes, start);

    return 0;
}
