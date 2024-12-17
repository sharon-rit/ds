// =========================
// Prim's Algorithm Program
// =========================
#include <stdio.h>
#include <limits.h>
#define V 5  // Number of vertices

// Utility function prototypes
int minKey(int key[], int mstSet[]);
void printMST(int parent[], int graph[V][V]);
void primMST(int graph[V][V]);

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    printf("\n=========== PRIM'S ALGORITHM ===========\n");
    primMST(graph);
    return 0;
}

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    printf("\nEdge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[V][V]) {
    int parent[V], key[V], mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    printMST(parent, graph);
}

// =========================
// Kruskal's Algorithm Program
// =========================
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Structures and function prototypes
struct Edge {
    int src, dest, weight;
};
struct Graph {
    int V, E;
    struct Edge* edges;
};

int parent[MAX];
struct Graph* createGraph(int V, int E);
int find(int i);
void unionSets(int x, int y);
int compareEdges(const void* a, const void* b);
void kruskalMST();

int main() {
    printf("\n=========== KRUSKAL'S ALGORITHM ===========\n");
    kruskalMST();
    return 0;
}

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    parent[rootX] = rootY;
}

int compareEdges(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight - e2->weight;
}

void kruskalMST() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V, E);
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    for (int i = 0; i < V; i++) parent[i] = i;
    qsort(graph->edges, E, sizeof(graph->edges[0]), compareEdges);

    printf("\nEdges in the Minimum Spanning Tree (Kruskal's):\n");
    int mstWeight = 0;
    for (int i = 0, count = 0; count < V - 1 && i < E; i++) {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int w = graph->edges[i].weight;

        if (find(u) != find(v)) {
            printf("%d - %d \t%d\n", u, v, w);
            unionSets(u, v);
            mstWeight += w;
            count++;
        }
    }
    printf("Total weight of MST: %d\n", mstWeight);
    free(graph->edges);
    free(graph);
}
