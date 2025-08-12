/*
  branch_and_bound_heuristic_history.c
  Branch and Bound + estimated heuristic + history tracking (student style)
  - Solves small TSP-like problem (returns to start)
  - Keeps a log of exploration events (level, node) in history arrays
  - Uses a simple heuristic: minimum outgoing edge from candidate node
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10        // maximum number of nodes
#define MAXHISTORY 1000

int N;                       // number of nodes
int graph[MAXN][MAXN];       // adjacency matrix (0 if no edge)
int bestPath[MAXN];          // stores best found path
int bestCost = INT_MAX;

// history arrays: each event records (level, node)
int historyLevel[MAXHISTORY];
int historyNode[MAXHISTORY];
int historyCount = 0;

// helper: append an exploration event to history
void record_event(int level, int node) {
    if (historyCount < MAXHISTORY) {
        historyLevel[historyCount] = level;
        historyNode[historyCount] = node;
        historyCount++;
    }
}

// simple heuristic: minimum outgoing edge weight from node to any unvisited node
int heuristic_min_outgoing(int node, int visited[]) {
    int minv = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (!visited[j] && graph[node][j] != 0 && graph[node][j] < minv) {
            minv = graph[node][j];
        }
    }
    if (minv == INT_MAX) return 0;
    return minv;
}

// copy current path to bestPath
void copy_best(int path[], int len) {
    for (int i = 0; i < len; i++) bestPath[i] = path[i];
}

// Branch & Bound with simple estimated heuristic pruning.
// level : next index to fill in path (starts at 1 since path[0] = start)
// path[] : current partial path of length 'level'
// visited[] : visited flags
// costSoFar : accumulated cost for the partial path
void bnb_heuristic_history(int level, int path[], int visited[], int costSoFar) {
    // If we reached full depth, complete tour by returning to start (0)
    if (level == N) {
        int last = path[level - 1];
        if (graph[last][0] != 0) { // if return edge exists
            int totalCost = costSoFar + graph[last][0];
            // record final attempt in history
            record_event(level, last);
            if (totalCost < bestCost) {
                bestCost = totalCost;
                copy_best(path, N);
                // record that we found a new best (use level -1 as signal)
                record_event(-1, totalCost); // node field used to store cost for best-found
            }
        }
        return;
    }

    // Try all unvisited nodes as next candidate
    for (int candidate = 0; candidate < N; candidate++) {
        if (!visited[candidate] && graph[path[level - 1]][candidate] != 0) {
            // compute estimated lower bound = costSoFar + cost to candidate + heuristic from candidate
            int estimated = costSoFar + graph[path[level - 1]][candidate] + heuristic_min_outgoing(candidate, visited);

            // record that we're considering this candidate at this level
            record_event(level, candidate);

            if (estimated < bestCost) {
                // choose candidate
                visited[candidate] = 1;
                path[level] = candidate;

                bnb_heuristic_history(level + 1, path, visited, costSoFar + graph[path[level - 1]][candidate]);

                // backtrack
                visited[candidate] = 0;
                // record backtrack event (optional) with level and negative node id
                record_event(level, -candidate - 1); // negative indicates backtrack
            } else {
                // pruned by estimated bound; record pruning as special event (use node = -candidate - 100)
                record_event(level, -candidate - 100);
            }
        }
    }
}

int main() {
    printf("Branch & Bound + Estimated Heuristic + History\n");
    printf("Enter number of nodes (N, max %d): ", MAXN);
    if (scanf("%d", &N) != 1 || N <= 1 || N > MAXN) {
        printf("Invalid N. Exiting.\n");
        return 1;
    }

    printf("Enter adjacency matrix (use 0 for no edge). %d x %d values:\n", N, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &graph[i][j]);

    // init visited and path
    int visited[MAXN];
    int path[MAXN];
    for (int i = 0; i < N; i++) visited[i] = 0;

    path[0] = 0;       // start at node 0
    visited[0] = 1;

    // record start event
    record_event(0, 0);

    // run branch and bound
    bnb_heuristic_history(1, path, visited, 0);

    // print results
    if (bestCost == INT_MAX) {
        printf("No complete tour found (graph may be disconnected).\n");
    } else {
        printf("\nBest tour cost: %d\nBest tour path: ", bestCost);
        for (int i = 0; i < N; i++) printf("%d ", bestPath[i]);
        printf("%d\n", bestPath[0]); // return to start
    }

    // Print a readable exploration history
    printf("\n--- Exploration History (level, node) ---\n");
    printf("Interpretation: positive node = visited/considered; negative node = special:\n");
    printf("  -node-1  => backtrack from node\n");
    printf("  -node-100 => pruning of node\n");
    printf("  level -1, node = cost => new best found with that cost\n\n");

    for (int i = 0; i < historyCount; i++) {
        int lvl = historyLevel[i];
        int nd  = historyNode[i];
        if (lvl == -1) {
            printf("[EVENT] Found new best cost = %d\n", nd);
        } else if (nd >= 0) {
            printf("[Level %d] Consider node %d\n", lvl, nd);
        } else if (nd <= -100) {
            int cand = -nd - 100;
            printf("[Level %d] Pruned candidate %d (bound)\n", lvl, cand);
        } else {
            int cand = -nd - 1;
            printf("[Level %d] Backtrack from candidate %d\n", lvl, cand);
        }
    }

    return 0;
}
