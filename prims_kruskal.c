//prims --------------------------------

//#include <stdio.h>
//#include <limits.h>
//
//#define MAX 100
//
//void primMST(int graph[MAX][MAX], int vertices) {
//    int parent[MAX]; // Array to store the MST
//    int key[MAX];    // Minimum weight edge for each vertex
//    int inMST[MAX];  // To check if a vertex is in MST
//
//    for (int i = 0; i < vertices; i++) {
//        key[i] = INT_MAX;
//        inMST[i] = 0;
//    }
//
//    key[0] = 0;      // Start from the first vertex
//    parent[0] = -1;  // First node is the root
//
//    for (int count = 0; count < vertices - 1; count++) {
//        int min = INT_MAX, u;
//
//        // Find the minimum key vertex not yet in MST
//        for (int v = 0; v < vertices; v++) {
//            if (!inMST[v] && key[v] < min) {
//                min = key[v];
//                u = v;
//            }
//        }
//
//        inMST[u] = 1;
//
//        // Update the key and parent for the adjacent vertices
//        for (int v = 0; v < vertices; v++) {
//            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
//                parent[v] = u;
//                key[v] = graph[u][v];
//            }
//        }
//    }
//
//    // Print the MST
//    printf("Edge \tWeight\n");
//    for (int i = 1; i < vertices; i++) {
//        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
//    }
//}
//
//int main() {
//    int vertices;
//    int graph[MAX][MAX];
//
//    printf("Enter the number of vertices: ");
//    scanf("%d", &vertices);
//
//    printf("Enter the adjacency matrix (use 0 for no edge):\n");
//    for (int i = 0; i < vertices; i++) {
//        for (int j = 0; j < vertices; j++) {
//            scanf("%d", &graph[i][j]);
//        }
//    }
//
//    printf("\nMinimum Spanning Tree (MST):\n");
//    primMST(graph, vertices);
//
//    return 0;
//}

// Kruskals -------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find the set of an element (uses path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform the union of two sets (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare two edges based on their weights
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Function to implement Kruskal's algorithm
void kruskalMST(int graph[MAX][MAX], int vertices) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            if (graph[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight
    qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);

    struct Subset subsets[MAX];
    for (int v = 0; v < vertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    struct Edge result[MAX]; // To store the MST
    int resultCount = 0, i = 0;

    while (resultCount < vertices - 1 && i < edgeCount) {
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[resultCount++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Print the MST
    printf("Edge \tWeight\n");
    for (int i = 0; i < resultCount; i++) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {
    int vertices;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nMinimum Spanning Tree (MST):\n");
    kruskalMST(graph, vertices);

    return 0;
}

