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

/* ================================================================================
 * PROBLEM 3: DELETE NODE IN A BINARY SEARCH TREE (LeetCode 450)
 * ================================================================================ */

/**
 * @brief Delete a node with a specific key from a Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * Given the root of a BST and an integer key, delete the node with the given key
 * in such a way that the BST property is maintained.
 * Return the root of the modified tree.
 *
 * EXAMPLE:
 * Input: root = [5,3,6,2,4,null,7], key = 3
 * Output: [5,4,6,2,null,null,7]
 *
 * APPROACH:
 * - Use standard BST traversal to locate the node.
 * - Once found, handle three cases:
 *   → Case 1: Node is a leaf → simply delete
 *   → Case 2: Node has one child → link parent to that child
 *   → Case 3: Node has two children → replace with inorder successor (min in right subtree)
 *
 * @param root Pointer to the root of the BST
 * @param key Value to delete from the BST
 * @return TreeNode* Updated root after deletion
 *
 * @complexity
 * Time: O(h) - h is the height of the tree (O(log n) for balanced, O(n) for skewed)
 * Space: O(h) - recursion stack
 */

 class Solution {
  public:
      // Utility function to find the minimum node in a subtree (used for inorder successor)
      TreeNode* findMin(TreeNode* root) {
          // Go to the leftmost node
          while (root && root->left != nullptr) {
              root = root->left;
          }
          return root;
      }

      // Main function to delete a node with given key from BST
      TreeNode* deleteNode(TreeNode* root, int key) {
          if (root == nullptr)
              return nullptr;

          // If key is smaller, go to left subtree
          if (key < root->val) {
              root->left = deleteNode(root->left, key);
          }
          // If key is larger, go to right subtree
          else if (key > root->val) {
              root->right = deleteNode(root->right, key);
          }
          // Found the node to be deleted
          else {
              // Case 1: Node has no children (leaf)
              if (root->left == nullptr && root->right == nullptr) {
                  delete root;
                  return nullptr;
              }

              // Case 2: Node has only right child
              else if (root->left == nullptr) {
                  TreeNode* temp = root->right;
                  delete root;
                  return temp;
              }

              // Case 2: Node has only left child
              else if (root->right == nullptr) {
                  TreeNode* temp = root->left;
                  delete root;
                  return temp;
              }

              // Case 3: Node has two children
              else {
                  // Find inorder successor (minimum in right subtree)
                  TreeNode* successor = findMin(root->right);
                  // Copy successor's value to current node
                  root->val = successor->val;
                  // Delete the successor node
                  root->right = deleteNode(root->right, successor->val);
              }
          }
          return root;
      }
  };

/* ===========================================================================================
 * PROBLEM 4: KTH SMALLEST ELEMENT IN A BINARY SEARCH TREE (LeetCode 230)
 * =========================================================================================== */

/**
 * @brief Find the kth smallest element in a Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary search tree and an integer k, return the kth smallest
 * value (1-indexed) among all the values of the nodes in the BST.
 *
 * EXAMPLE:
 * Input: root = [3,1,4,null,2], k = 1
 * Output: 1
 *
 * APPROACH:
 * - Use inorder traversal (Left → Root → Right) since it returns sorted values in a BST
 * - Store all values during traversal in a vector
 * - Return the (k-1)th index value from the vector
 *
 * @param root Pointer to the root of the BST
 * @param k The kth position (1-indexed) smallest element to find
 * @return int The kth smallest element value
 *
 * @complexity
 * Time: O(n) - Traverses all nodes
 * Space: O(n) - Stores all node values in a vector
 */

 class Solution {
  public:
      vector<int> temp; // Stores nodes in ascending order during inorder traversal

      // Inorder traversal: Left → Root → Right . Inorder always gives nodes in ascending order
      void inorder(TreeNode* root) {
          if (root == nullptr) return;

          inorder(root->left);             // Visit left subtree
          temp.push_back(root->val);       // Visit root
          inorder(root->right);            // Visit right subtree
      }

      int kthSmallest(TreeNode* root, int k) {
          inorder(root);                   // Fill vector with sorted node values
          return temp[k - 1];              // Return kth smallest (1-indexed)
      }
  };

/* =======================================================================================
 * PROBLEM 5: VALIDATE BINARY SEARCH TREE (LeetCode 98)
 * ======================================================================================= */

/**
 * @brief Check if a given binary tree is a valid Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, determine if it is a valid Binary Search Tree (BST).
 * A valid BST satisfies:
 * - Left subtree of a node contains only nodes with values < node's value
 * - Right subtree of a node contains only nodes with values > node's value
 * - Both left and right subtrees must also be BSTs
 *
 * EXAMPLE:
 * Input: root = [2,1,3]
 * Output: true
 *
 * APPROACH:
 * - Use recursion with value range checks (min and max bounds)
 * - Each node must lie strictly between min and max
 * - Recurse left with updated max, and right with updated min
 * - Use long instead of int to avoid integer overflow edge cases
 *
 * @param root Pointer to the root of the tree
 * @return bool True if the tree is a valid BST, False otherwise
 *
 * @complexity
 * Time: O(n) - Visit every node once
 * Space: O(h) - h is the height of the tree (due to recursion stack)
 */

 class Solution {
  public:
      // Helper function to validate BST within a value range
      bool isValid(TreeNode* node, long min, long max) {
          if (!node) return true; // Base case: null tree is valid
          if (node->val <= min || node->val >= max) return false; // Violation of BST rules

          // Check left and right subtrees recursively
          return isValid(node->left, min, node->val) &&
                 isValid(node->right, node->val, max);
      }

      // Main function
      bool isValidBST(TreeNode* root) {
          // Use long min/max to handle edge cases with INT_MIN/INT_MAX
          return isValid(root, LONG_MIN, LONG_MAX);
      }
  };

/* ===============================================================================================
 * PROBLEM 6: LOWEST COMMON ANCESTOR OF A BINARY SEARCH TREE (LeetCode 235)
 * =============================================================================================== */

/**
 * @brief Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree (BST)
 *
 * PROBLEM STATEMENT:
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes p and q.
 * The LCA of two nodes is the lowest (deepest) node in the BST that has both p and q as descendants.
 *
 * EXAMPLE:
 * Input: root = [6,2,8,0,4,7,9], p = 2, q = 8
 * Output: 6
 *
 * APPROACH:
 * - Use BST properties:
 *   → If root == p or q → current node is LCA
 *   → If one lies in left and one in right → current node is LCA
 *   → If both are less than root → move left
 *   → If both are greater than root → move right
 *
 * COMPLEXITY:
 * Time:  O(h) where h = height of BST (O(log n) for balanced, O(n) for skewed)
 * Space:
 *   - Recursive: O(h) due to recursion stack
 *   - Iterative: O(1) constant extra space
 */


/* ==============================
 * RECURSIVE IMPLEMENTATION
 * ============================== */

 class Solution {
  public:
      TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
          // If root is either p or q → root is LCA
          if (root == p || root == q) return root;

          // If one value is less and one is greater → root is LCA
          if ((root->val < p->val && root->val > q->val) ||
              (root->val > p->val && root->val < q->val))
              return root;

          // If both values are less → move to left subtree
          if (root->val > p->val && root->val > q->val)
              return lowestCommonAncestor(root->left, p, q);

          // If both values are greater → move to right subtree
          return lowestCommonAncestor(root->right, p, q);
      }
  };


  /* ==============================
   * ITERATIVE IMPLEMENTATION
   * ============================== */

  class Solution {
  public:
      TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
          while (root != nullptr) {
              // If both p and q are smaller → move left
              if (root->val > p->val && root->val > q->val) {
                  root = root->left;
              }
              // If both p and q are greater → move right
              else if (root->val < p->val && root->val < q->val) {
                  root = root->right;
              }
              // Found the split point → current node is LCA
              else {
                  return root;
              }
          }
          return nullptr; // Not found (edge case)
      }
  };

/* ================================================================================================
 * PROBLEM 7: CONSTRUCT BINARY SEARCH TREE FROM PREORDER TRAVERSAL (LeetCode 1008)
 * ================================================================================================ */

/**
 * @brief Construct a Binary Search Tree (BST) from its preorder traversal
 *
 * PROBLEM STATEMENT:
 * Given an array representing the preorder traversal of a BST, construct the tree and return its root.
 *
 * EXAMPLE:
 * Input: preorder = [8,5,1,7,10,12]
 * Output: Root of the constructed BST
 *
 * APPROACH:
 * - The first element of preorder is always the root.
 * - All subsequent elements smaller than root go to the left subtree.
 * - All elements greater than root go to the right subtree.
 * - Recursively apply the logic for each subtree by finding the first index where value > root.
 *
 * @param preorder Vector containing preorder traversal of a BST
 * @return TreeNode* Root node of the constructed BST
 *
 * @complexity
 * Time: O(n^2) - In worst case, we may check every node to find the split point
 * Space: O(h)  - Recursive call stack (h = height of BST)
 */

 class Solution {
  public:
      // Helper function to recursively build BST from preorder[start...end]
      TreeNode* build(vector<int>& preorder, int start, int end) {
          if (start > end) return nullptr; // Base case: invalid range

          // First element is the root of current subtree
          TreeNode* root = new TreeNode(preorder[start]);

          // Find the split point where elements become greater than root->val
          int split = start + 1;
          while (split <= end && preorder[split] < root->val) {
              split++;
          }

          // Recursively build left and right subtrees
          root->left = build(preorder, start + 1, split - 1);  // Left subtree
          root->right = build(preorder, split, end);           // Right subtree

          return root;
      }

      // Main function
      TreeNode* bstFromPreorder(vector<int>& preorder) {
          return build(preorder, 0, preorder.size() - 1);
      }
  };

/* ============================================================================================
 * PROBLEM 8: TWO SUM IV - INPUT IS A BST (LeetCode 653)
 * ============================================================================================ */

/**
 * @brief Determine if there exist two elements in a BST that sum to a given target
 *
 * PROBLEM STATEMENT:
 * Given the root of a Binary Search Tree (BST) and an integer k, return true if there exist
 * two elements in the BST such that their sum is equal to k. Otherwise, return false.
 *
 * EXAMPLE:
 * Input: root = [5,3,6,2,4,null,7], k = 9
 * Output: true
 *
 * APPROACH 1: INORDER + TWO POINTERS
 * - Perform an inorder traversal to get sorted elements of BST in a vector
 * - Use two-pointer approach (like in sorted array) to find if any pair sums to k
 *
 * @param root Pointer to root of BST
 * @param k Target sum value
 * @return bool True if any two nodes' values sum to k, else false
 *
 * @complexity
 * Time: O(n) - Full traversal + two-pointer search
 * Space: O(n) - For storing all node values in a vector
 */

 class Solution {
  public:
      // Inorder traversal to get sorted values from BST
      void inorder(TreeNode* root, vector<int>& ans) {
          if (!root) return;
          inorder(root->left, ans);
          ans.push_back(root->val);
          inorder(root->right, ans);
      }

      bool findTarget(TreeNode* root, int k) {
          if (!root) return false;

          vector<int> ans;
          inorder(root, ans); // Store sorted elements

          // Two pointer technique
          int l = 0, r = ans.size() - 1;
          while (l < r) {
              int sum = ans[l] + ans[r];
              if (sum == k) return true;
              else if (sum < k) l++;
              else r--;
          }

          return false; // No pair found
      }
  };


  /* ============================================================================================
   * ALTERNATIVE APPROACH: HASHSET + DFS (O(n) Time, O(n) Space, No sorting)
   * ============================================================================================ */

  /**
   * @brief Use DFS and a HashSet to check complement (k - node->val) on the fly
   *
   * - At each node, check if (k - current_value) exists in the set
   * - If yes, return true
   * - Else insert current_value and move to children
   *
   * Time:  O(n)
   * Space: O(n)
   */

  class Solution {
  public:
      bool dfs(TreeNode* root, unordered_set<int>& seen, int k) {
          if (!root) return false;

          if (seen.count(k - root->val)) return true; // Pair found
          seen.insert(root->val);                     // Mark current value

          return dfs(root->left, seen, k) || dfs(root->right, seen, k);
      }

      bool findTarget(TreeNode* root, int k) {
          unordered_set<int> seen;
          return dfs(root, seen, k);
      }
  };

