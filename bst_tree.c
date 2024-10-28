#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in a binary tree using level-order insertion
void insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode; // If the tree is empty, set the new node as the root
        return;
    }

    // Queue for level-order traversal
    struct Node* queue[100]; // Assume maximum 100 nodes
    int front = 0, rear = 0;

    queue[rear++] = *root; // Start with the root node

    while (front < rear) {
        struct Node* temp = queue[front++]; // Dequeue a node

        // Check for left child
        if (temp->left == NULL) {
            temp->left = newNode; // Insert new node
            return;
        } else {
            queue[rear++] = temp->left; // Enqueue left child
        }

        // Check for right child
        if (temp->right == NULL) {
            temp->right = newNode; // Insert new node
            return;
        } else {
            queue[rear++] = temp->right; // Enqueue right child
        }
    }
}

// Function to find the minimum value node
struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node in a binary tree
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) return root; // Base case: tree is empty

    // Recursively find the node to delete
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);
        root->data = temp->data; // Copy the inorder successor's content to this node
        root->right = deleteNode(root->right, temp->data); // Delete the inorder successor
    }
    return root;
}

// Preorder Traversal: Root, Left, Right
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data); // Visit root
        preorderTraversal(root->left); // Traverse left subtree
        preorderTraversal(root->right); // Traverse right subtree
    }
}

// Inorder Traversal: Left, Root, Right
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left); // Traverse left subtree
        printf("%d ", root->data); // Visit root
        inorderTraversal(root->right); // Traverse right subtree
    }
}

// Postorder Traversal: Left, Right, Root
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left); // Traverse left subtree
        postorderTraversal(root->right); // Traverse right subtree
        printf("%d ", root->data); // Visit root
    }
}

// Main function to demonstrate the binary tree operations
int main() {
    struct Node* root = NULL;

    // Insertion
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);

    // Display traversals
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Deletion
    printf("Deleting node 30...\n");
    root = deleteNode(root, 30);

    // Display traversals after deletion
    printf("Inorder Traversal after deletion: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
