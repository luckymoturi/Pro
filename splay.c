#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Right rotate the given node
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotate the given node
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        // Key is in the left subtree
        if (root->left == NULL) return root;
        if (key < root->left->key) {
            // Zig-Zig (Left Left)
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->key) {
            // Zig-Zag (Left Right)
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    } else {
        // Key is in the right subtree
        if (root->right == NULL) return root;
        if (key > root->right->key) {
            // Zag-Zag (Right Right)
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        } else if (key < root->right->key) {
            // Zag-Zig (Right Left)
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Function to insert a new key into the splay tree
Node* insert(Node* root, int key) {
    if (root == NULL) return newNode(key);
    root = splay(root, key);
    if (root->key == key) return root; // Key already exists

    Node* NewNode = newNode(key);
    if (key < root->key) {
        NewNode->left = root->left;
        NewNode->right = root;
        root->left = NULL;
    } else {
        NewNode->right = root->right;
        NewNode->left = root;
        root->right = NULL;
    }
    return NewNode;
}

// Function to perform an in-order traversal of the tree
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 70);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    printf("In-order traversal of the splay tree is: \n");
    inorder(root);

    return 0;
}