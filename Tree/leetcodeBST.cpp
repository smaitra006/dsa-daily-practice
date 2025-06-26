// LeetCode Binary Search Tree

#include <bits/stdc++.h>
using namespace std;

 /**
  * @brief Definition for a binary tree node (LeetCode standard)
  */
 struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  // Default constructor
  TreeNode() : val(0), left(nullptr), right(nullptr) {}

  // Constructor with value
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  // Constructor with value and children
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

/* ================================================================
 * PROBLEM 1: SEARCH IN A BINARY SEARCH TREE (LeetCode 700)
 * ================================================================ */

/**
 * @brief Search for a node with a given value in a Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * You are given the root of a binary search tree (BST) and an integer val.
 * Return the subtree rooted with the node having the value equal to val.
 * If such a node does not exist, return nullptr.
 *
 * EXAMPLE:
 * Input: root = [4,2,7,1,3], val = 2
 * Output: [2,1,3]
 *
 * APPROACH:
 * - Use the BST property:
 *   → If val == root->val → return root
 *   → If val < root->val → search in left subtree
 *   → If val > root->val → search in right subtree
 *
 * @param root Pointer to the root of the BST
 * @param val Target value to search
 * @return TreeNode* Subtree rooted at node with value `val`, or nullptr if not found
 *
 * @complexity
 * Time: O(h) - h is the height of the tree (log n for balanced BST, n for skewed)
 * Space: O(h) - Recursion stack
 */

 class Solution {
  public:
      TreeNode* searchBST(TreeNode* root, int val) {
          // BASE CASE: Not found (null node)
          if (!root) {
              return nullptr;
          }

          // TARGET FOUND
          if (root->val == val) {
              return root;
          }

          // If target is smaller, search in left subtree
          if (val < root->val) {
              return searchBST(root->left, val);
          }

          // If target is larger, search in right subtree
          return searchBST(root->right, val);
      }
  };

/* ============================================================================
 * PROBLEM 2: INSERT INTO A BINARY SEARCH TREE (LeetCode 701)
 * ============================================================================ */

/**
 * @brief Insert a value into a Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * You are given the root of a binary search tree (BST) and an integer val.
 * Insert the value into the BST such that the tree remains a valid BST.
 * Return the root of the updated BST.
 *
 * EXAMPLE:
 * Input: root = [4,2,7,1,3], val = 5
 * Output: [4,2,7,1,3,5]
 *
 * APPROACH:
 * - If the root is null, create and return a new node
 * - If val < root->val → insert in left subtree
 * - If val > root->val → insert in right subtree
 * - BST property ensures correct placement
 *
 * @param root Pointer to the root of the BST
 * @param val Integer value to insert
 * @return TreeNode* Root of the modified BST
 *
 * @complexity
 * Time: O(h) - where h is the height of the BST (log n for balanced, n for skewed)
 * Space: O(h) - due to recursion stack
 */

 class Solution {
  public:
      TreeNode* insertIntoBST(TreeNode* root, int val) {
          if (root == nullptr) {
              // Base case: create and return a new node
              return new TreeNode(val);
          }

          // Recursively insert in left or right subtree based on value
          if (val < root->val) {
              root->left = insertIntoBST(root->left, val);
          } else {
              root->right = insertIntoBST(root->right, val);
          }

          // Return the unchanged root pointer
          return root;
      }
  };
