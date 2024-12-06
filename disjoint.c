#include <stdio.h>
#include <stdlib.h>

// Structure to represent a Disjoint Set (Union-Find)
typedef struct {
    int *parent;
    int *rank;
    int size;
} DisjointSet;

// Function to create a Disjoint Set with n elements
DisjointSet* createSet(int n) {
    DisjointSet* set = (DisjointSet*)malloc(sizeof(DisjointSet));
    set->size = n;
    set->parent = (int*)malloc(n * sizeof(int));
    set->rank = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        set->parent[i] = i;  // Initially, each element is its own parent
        set->rank[i] = 0;     // Initial rank of each element is 0
    }

    return set;
}

// Find function with path compression
int find(DisjointSet* set, int x) {
    if (set->parent[x] != x) {
        set->parent[x] = find(set, set->parent[x]);  // Path compression
    }
    return set->parent[x];
}

// Union function with union by rank
void unionSets(DisjointSet* set, int x, int y) {
    int rootX = find(set, x);
    int rootY = find(set, y);

    // If they are already in the same set, no need to do anything
    if (rootX != rootY) {
        // Union by rank: attach the smaller tree under the larger tree
        if (set->rank[rootX] < set->rank[rootY]) {
            set->parent[rootX] = rootY;
        } else if (set->rank[rootX] > set->rank[rootY]) {
            set->parent[rootY] = rootX;
        } else {
            set->parent[rootY] = rootX;
            set->rank[rootX]++;
        }
    }
}

// Function to check if two elements are in the same set
int areInSameSet(DisjointSet* set, int x, int y) {
    return find(set, x) == find(set, y);
}

// Function to free the memory allocated for the Disjoint Set
void destroySet(DisjointSet* set) {
    free(set->parent);
    free(set->rank);
    free(set);
}

int main() {
    int n, choice, x, y;
    DisjointSet* set = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create a Disjoint Set\n");
        printf("2. Perform Union operation\n");
        printf("3. Perform Find operation\n");
        printf("4. Check if two elements are in the same set\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements: ");
                scanf("%d", &n);
                set = createSet(n);
                printf("Disjoint Set created with %d elements.\n", n);
                break;

            case 2:
                if (set == NULL) {
                    printf("Disjoint Set not created yet!\n");
                    break;
                }
                printf("Enter two elements to union: ");
                scanf("%d %d", &x, &y);
                if (x >= n || y >= n || x < 0 || y < 0) {
                    printf("Invalid elements! Please enter elements between 0 and %d.\n", n-1);
                } else {
                    unionSets(set, x, y);
                    printf("Union of %d and %d performed.\n", x, y);
                }
                break;

            case 3:
                if (set == NULL) {
                    printf("Disjoint Set not created yet!\n");
                    break;
                }
                printf("Enter element to find: ");
                scanf("%d", &x);
                if (x >= n || x < 0) {
                    printf("Invalid element! Please enter an element between 0 and %d.\n", n-1);
                } else {
                    printf("The representative of %d is %d.\n", x, find(set, x));
                }
                break;

            case 4:
                if (set == NULL) {
                    printf("Disjoint Set not created yet!\n");
                    break;
                }
                printf("Enter two elements to check if they are in the same set: ");
                scanf("%d %d", &x, &y);
                if (x >= n || y >= n || x < 0 || y < 0) {
                    printf("Invalid elements! Please enter elements between 0 and %d.\n", n-1);
                } else {
                    if (areInSameSet(set, x, y)) {
                        printf("Yes, %d and %d are in the same set.\n", x, y);
                    } else {
                        printf("No, %d and %d are not in the same set.\n", x, y);
                    }
                }
                break;

            case 5:
                if (set != NULL) {
                    destroySet(set);
                }
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
