#include <bits/stdc++.h>
using namespace std;

/*
 * BINARY SEARCH TREE (BST) CONCEPTS:
 *
 * BST: A special kind of binary tree where each node follows this rule:
 * - Left subtree contains only nodes with values less than the node’s value
 * - Right subtree contains only nodes with values greater than the node’s value
 * - Both left and right subtrees are also BSTs
 *
 * PROPERTIES OF BST:
 * - Inorder Traversal of a BST gives sorted (increasing) order
 * - Time complexity for Search, Insert, Delete is:
 *      * Average Case: O(log n)  (for balanced BSTs)
 *      * Worst Case: O(n)       (for skewed BSTs)
 *
 * BST OPERATIONS:
 * - Search: Traverse left or right depending on value
 * - Insertion: Follow BST property to find correct spot
 * - Deletion: Three cases:
 *      1. Node has no child (leaf) – remove node
 *      2. Node has one child – link parent to child
 *      3. Node has two children – replace with inorder successor/predecessor
 */

// Node structure for binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;

    // Constructor to initialize a new node
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Insert a node into the BST
Node* insertBST(Node* root, int val) {
    if (root == nullptr) {
        // Base case: create and return a new node
        return new Node(val);
    }

    // Recursively insert in left or right subtree
    if (val < root->data) {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }

    return root;
}

// Search a value in BST
bool searchBST(Node* root, int key) {
    if (root == nullptr) return false; // Base case: not found
    if (root->data == key) return true; // Found the key

    // Search in left or right subtree based on comparison
    if (key < root->data)
        return searchBST(root->left, key);
    else
        return searchBST(root->right, key);
}

// Inorder traversal (Left -> Root -> Right)
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);          // Visit left subtree
    cout << root->data << " ";    // Visit root
    inorder(root->right);         // Visit right subtree
}

// Find minimum node in BST (used to find inorder successor)
Node* findMin(Node* root) {
    // Minimum is the leftmost node
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Delete a node from BST
Node* deleteBST(Node* root, int key) {
    if (root == nullptr) return nullptr;

    if (key < root->data) {
        // Recur to the left subtree
        root->left = deleteBST(root->left, key);
    } else if (key > root->data) {
        // Recur to the right subtree
        root->right = deleteBST(root->right, key);
    } else {
        // Node with the key found

        // Case 1: No child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        // Case 2: One child
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two children
        else {
            // Find inorder successor (minimum in right subtree)
            Node* successor = findMin(root->right);
            root->data = successor->data; // Replace data
            // Delete successor node recursively
            root->right = deleteBST(root->right, successor->data);
        }
    }
    return root;
}
