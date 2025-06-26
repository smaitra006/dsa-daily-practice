// LeetCode Tree Questions

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

 /* ========================================================================
  * PROBLEM 1: MAXIMUM DEPTH OF BINARY TREE (LeetCode 104)
  * ======================================================================== */

 /**
  * @brief Find the maximum depth (height) of a binary tree
  *
  * PROBLEM STATEMENT:
  * Given the root of a binary tree, return its maximum depth.
  * A binary tree's maximum depth is the number of nodes along the longest
  * path from the root node down to the farthest leaf node.
  *
  * APPROACH:
  * Use recursive DFS to find height of left and right subtrees.
  * The maximum depth is 1 + max(left_depth, right_depth).
  *
  * @param root Pointer to the root of the binary tree
  * @return int Maximum depth of the tree
  *
  * @complexity
  * Time: O(n) - Visit each node once
  * Space: O(h) - Recursion stack, where h is height of tree
  *               O(log n) for balanced tree, O(n) for skewed tree
  */
 class MaxDepthSolution {
 public:
     int maxDepth(TreeNode* root) {
         // BASE CASE: Empty tree has depth 0
         if (root == nullptr) {
             return 0;
         }

         // RECURSIVE CASE: Get depths of left and right subtrees
         int leftDepth = maxDepth(root->left);   // Depth of left subtree
         int rightDepth = maxDepth(root->right); // Depth of right subtree

         // Return 1 (current node) + maximum of left and right depths
         return 1 + max(leftDepth, rightDepth);
     }
 };

 /* ========================================================================
  * PROBLEM 2: BALANCED BINARY TREE (LeetCode 110)
  * ======================================================================== */

 /**
  * @brief Check if a binary tree is height-balanced
  *
  * PROBLEM STATEMENT:
  * Given a binary tree, determine if it is height-balanced.
  * A height-balanced binary tree is defined as a binary tree in which
  * the depth of the two subtrees of every node never differs by more than one.
  *
  * APPROACH:
  * Use bottom-up approach with modified height calculation.
  * Return -1 if subtree is unbalanced, otherwise return actual height.
  * Check balance condition at each node during height calculation.
  *
  * @param root Pointer to the root of the binary tree
  * @return bool True if tree is balanced, false otherwise
  *
  * @complexity
  * Time: O(n) - Visit each node once
  * Space: O(h) - Recursion stack depth
  */
 class BalancedTreeSolution {
 public:
     /**
      * @brief Helper function to find height and check balance simultaneously
      * @param root Current node
      * @return int Height of subtree, or -1 if unbalanced
      */
     int findHeight(TreeNode* root) {
         // BASE CASE: Empty node has height 0
         if (root == nullptr) {
             return 0;
         }

         // Get heights of left and right subtrees
         int leftHeight = findHeight(root->left);
         int rightHeight = findHeight(root->right);

         // EARLY TERMINATION: If any subtree is unbalanced, propagate -1
         if (leftHeight == -1 || rightHeight == -1) {
             return -1;
         }

         // CHECK BALANCE CONDITION: Height difference > 1
         if (abs(leftHeight - rightHeight) > 1) {
             return -1; // Current subtree is unbalanced
         }

         // Return actual height if balanced
         return 1 + max(leftHeight, rightHeight);
     }

     bool isBalanced(TreeNode* root) {
         int height = findHeight(root);
         return height != -1; // Tree is balanced if height is not -1
     }
 };

 /* ========================================================================
  * PROBLEM 3: DIAMETER OF BINARY TREE (LeetCode 543)
  * ======================================================================== */

 /**
  * @brief Find the diameter of a binary tree
  *
  * PROBLEM STATEMENT:
  * Given the root of a binary tree, return the length of the diameter of the tree.
  * The diameter of a binary tree is the length of the longest path between
  * any two nodes in a tree. This path may or may not pass through the root.
  * The length of a path between two nodes is represented by the number of edges.
  *
  * APPROACH:
  * For each node, the longest path through it is leftHeight + rightHeight.
  * Use DFS to calculate height and update global diameter at each node.
  * The diameter can pass through any node, not necessarily the root.
  *
  * @param root Pointer to the root of the binary tree
  * @return int Diameter of the tree (number of edges)
  *
  * @complexity
  * Time: O(n) - Visit each node once
  * Space: O(h) - Recursion stack depth
  */
 class DiameterSolution {
 private:
     int diameter; // Global variable to track maximum diameter

 public:
     /**
      * @brief Helper function to calculate height and update diameter
      * @param root Current node
      * @return int Height of current subtree
      */
     int findHeight(TreeNode* root) {
         // BASE CASE: Empty node contributes 0 to height
         if (root == nullptr) {
             return 0;
         }

         // Get heights of left and right subtrees
         int leftHeight = findHeight(root->left);
         int rightHeight = findHeight(root->right);

         // UPDATE DIAMETER: Longest path through current node
         // is sum of left and right heights (number of edges)
         diameter = max(diameter, leftHeight + rightHeight);

         // Return height of current subtree
         return 1 + max(leftHeight, rightHeight);
     }

     int diameterOfBinaryTree(TreeNode* root) {
         diameter = 0; // Initialize diameter
         findHeight(root); // Calculate height and update diameter
         return diameter;
     }
 };

 /* ========================================================================
  * PROBLEM 4: BINARY TREE MAXIMUM PATH SUM (LeetCode 124)
  * ======================================================================== */

 /**
  * @brief Find the maximum path sum in a binary tree
  *
  * PROBLEM STATEMENT:
  * A path in a binary tree is a sequence of nodes where each pair of adjacent
  * nodes in the sequence has an edge connecting them. A node can only appear
  * in the sequence at most once. The path does not need to pass through the root.
  * The path sum is the sum of the node's values in the path.
  * Given the root of a binary tree, return the maximum path sum of any non-empty path.
  *
  * APPROACH:
  * Similar to diameter problem, but instead of counting edges, sum node values.
  * For each node, consider paths: through node, left-only, right-only.
  * Use max(0, subtree_sum) to ignore negative contributions.
  *
  * @param root Pointer to the root of the binary tree
  * @return int Maximum path sum
  *
  * @complexity
  * Time: O(n) - Visit each node once
  * Space: O(h) - Recursion stack depth
  */
 class MaxPathSumSolution {
 private:
     int maxSum; // Global variable to track maximum path sum

 public:
     /**
      * @brief Helper function to calculate max path sum ending at current node
      * @param root Current node
      * @return int Maximum path sum that can be extended to parent
      */
     int findSum(TreeNode* root) {
         // BASE CASE: Empty node contributes 0
         if (root == nullptr) {
             return 0;
         }

         // Get maximum path sums from left and right subtrees
         // Use max(0, sum) to ignore negative paths (don't include them)
         int leftSum = max(0, findSum(root->left));
         int rightSum = max(0, findSum(root->right));

         // UPDATE GLOBAL MAXIMUM: Consider path through current node
         // This path includes current node + best left path + best right path
         maxSum = max(maxSum, root->val + leftSum + rightSum);

         // RETURN PATH SUM THAT CAN BE EXTENDED TO PARENT:
         // Can only choose one direction (left OR right), not both
         // Include current node + best single path
         return root->val + max(leftSum, rightSum);
     }

     int maxPathSum(TreeNode* root) {
         maxSum = INT_MIN; // Initialize to handle negative values
         findSum(root);
         return maxSum;
     }
 };

 /* ========================================================================
  * PROBLEM 5: SAME TREE (LeetCode 100)
  * ======================================================================== */

 /**
  * @brief Check if two binary trees are identical
  *
  * PROBLEM STATEMENT:
  * Given the roots of two binary trees p and q, write a function to check
  * if they are the same or not. Two binary trees are considered the same
  * if they are structurally identical, and the nodes have the same value.
  *
  * APPROACH:
  * Use recursive comparison:
  * 1. Both null -> same
  * 2. One null, other not -> different
  * 3. Values different -> different
  * 4. Recursively check left and right subtrees
  *
  * @param p Root of first tree
  * @param q Root of second tree
  * @return bool True if trees are identical, false otherwise
  *
  * @complexity
  * Time: O(min(m,n)) - Visit nodes until difference found or smaller tree exhausted
  * Space: O(min(m,n)) - Recursion stack depth
  */
 class SameTreeSolution {
 public:
     bool isSameTree(TreeNode* p, TreeNode* q) {
         // CASE 1: Both nodes are null -> trees are same at this level
         if (p == nullptr && q == nullptr) {
             return true;
         }

         // CASE 2: One is null, other is not -> trees are different
         if (p == nullptr || q == nullptr) {
             return false;
         }

         // CASE 3: Both nodes exist but have different values -> different
         if (p->val != q->val) {
             return false;
         }

         // CASE 4: Current nodes are same, check left and right subtrees
         // Both left and right subtrees must be identical
         return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
     }
 };

 /* ========================================================================
 * PROBLEM 6: BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL (LeetCode 103)
 * ======================================================================== */

/**
 * @brief Traverse binary tree in zigzag level order
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, return the zigzag level order traversal
 * of its nodes' values (i.e., from left to right, then right to left for
 * the next level and alternate between).
 *
 * EXAMPLE:
 * Input: root = [3,9,20,null,null,15,7]
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * Output: [[3],[20,9],[15,7]]
 *
 * APPROACHES:
 * 1. Two Stack Approach - Use two stacks alternately for each level
 * 2. Queue + Reverse Approach - Use queue for level order, reverse alternate levels
 * 3. Deque Approach - Use deque to add elements from both ends
 */

class Solution {
  public:
      /* ====================================================================
       * APPROACH 1: TWO STACK APPROACH
       * ==================================================================== */

      /**
       * @brief Zigzag traversal using two stacks
       *
       * ALGORITHM:
       * - Use two stacks: s1 for odd levels (L->R), s2 for even levels (R->L)
       * - Odd levels: Pop from s1, push children L->R to s2
       * - Even levels: Pop from s2, push children R->L to s1
       * - Continue until both stacks are empty
       *
       * @param root Root of the binary tree
       * @return vector<vector<int>> Zigzag level order traversal
       *
       * @complexity
       * Time: O(n) - Visit each node once
       * Space: O(w) - Maximum width of tree for stacks
       */
      vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
          // Handle edge case: empty tree
          if (root == nullptr) {
              return {};  // Return empty vector, not {{}}
          }

          vector<vector<int>> result;
          stack<TreeNode*> s1;  // For odd levels (left to right)
          stack<TreeNode*> s2;  // For even levels (right to left)

          s1.push(root);  // Start with root in s1
          int level = 1;  // Track current level (1-indexed)

          // Continue while at least one stack has nodes
          while (!s1.empty() || !s2.empty()) {
              vector<int> currentLevel;

              if (level % 2 == 1) {
                  // ODD LEVEL: Process s1 (left to right)
                  int size = s1.size();
                  for (int i = 0; i < size; i++) {
                      TreeNode* node = s1.top();
                      s1.pop();
                      currentLevel.push_back(node->val);

                      // Push children to s2 in L->R order for next level (R->L processing)
                      if (node->left) s2.push(node->left);
                      if (node->right) s2.push(node->right);
                  }
              } else {
                  // EVEN LEVEL: Process s2 (right to left)
                  int size = s2.size();
                  for (int i = 0; i < size; i++) {
                      TreeNode* node = s2.top();
                      s2.pop();
                      currentLevel.push_back(node->val);

                      // Push children to s1 in R->L order for next level (L->R processing)
                      if (node->right) s1.push(node->right);
                      if (node->left) s1.push(node->left);
                  }
              }

              result.push_back(currentLevel);
              level++;
          }

          return result;
      }

      /* ====================================================================
       * APPROACH 2: QUEUE + REVERSE APPROACH (Alternative)
       * ==================================================================== */

      /**
       * @brief Zigzag traversal using queue and selective reversal
       *
       * ALGORITHM:
       * - Use standard level order traversal with queue
       * - For even levels (0-indexed), reverse the level before adding to result
       * - Simpler logic but requires additional reverse operation
       *
       * @param root Root of the binary tree
       * @return vector<vector<int>> Zigzag level order traversal
       *
       * @complexity
       * Time: O(n) - Visit each node once + O(w) for reverse operations
       * Space: O(w) - Queue space for maximum width
       */
      vector<vector<int>> zigzagLevelOrderAlternative(TreeNode* root) {
          if (root == nullptr) return {};

          vector<vector<int>> result;
          queue<TreeNode*> q;
          q.push(root);
          bool leftToRight = true;  // Flag to track direction

          while (!q.empty()) {
              int levelSize = q.size();
              vector<int> currentLevel;

              // Process all nodes at current level
              for (int i = 0; i < levelSize; i++) {
                  TreeNode* node = q.front();
                  q.pop();
                  currentLevel.push_back(node->val);

                  // Add children for next level
                  if (node->left) q.push(node->left);
                  if (node->right) q.push(node->right);
              }

              // Reverse if we need right to left order
              if (!leftToRight) {
                  reverse(currentLevel.begin(), currentLevel.end());
              }

              result.push_back(currentLevel);
              leftToRight = !leftToRight;  // Toggle direction
          }

          return result;
      }

      /* ====================================================================
       * APPROACH 3: DEQUE APPROACH (Most Elegant)
       * ==================================================================== */

      /**
       * @brief Zigzag traversal using deque for bidirectional insertion
       *
       * ALGORITHM:
       * - Use queue for level order traversal
       * - Use deque for current level to add elements from both ends
       * - Odd levels: add to back (left to right)
       * - Even levels: add to front (right to left effect)
       *
       * @param root Root of the binary tree
       * @return vector<vector<int>> Zigzag level order traversal
       *
       * @complexity
       * Time: O(n) - Visit each node once
       * Space: O(w) - Queue + deque space
       */
      vector<vector<int>> zigzagLevelOrderDeque(TreeNode* root) {
          if (root == nullptr) return {};

          vector<vector<int>> result;
          queue<TreeNode*> q;
          q.push(root);
          bool leftToRight = true;

          while (!q.empty()) {
              int levelSize = q.size();
              deque<int> currentLevel;

              for (int i = 0; i < levelSize; i++) {
                  TreeNode* node = q.front();
                  q.pop();

                  // Add to appropriate end based on direction
                  if (leftToRight) {
                      currentLevel.push_back(node->val);  // Add to back
                  } else {
                      currentLevel.push_front(node->val); // Add to front
                  }

                  // Add children for next level
                  if (node->left) q.push(node->left);
                  if (node->right) q.push(node->right);
              }

              // Convert deque to vector and add to result
              result.push_back(vector<int>(currentLevel.begin(), currentLevel.end()));
              leftToRight = !leftToRight;
          }

          return result;
      }
  };

  /* ========================================================================
 * PROBLEM 7: BINARY TREE RIGHT SIDE VIEW (LeetCode 199)
 * ======================================================================== */

/**
 * @brief Return the right side view of a binary tree
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, imagine yourself standing on the right side
 * of it, return the values of the nodes you can see ordered from top to bottom.
 *
 * EXAMPLE:
 * Input: root = [1,2,3,null,5,null,4]
 *     1
 *    / \
 *   2   3
 *    \   \
 *     5   4
 * Output: [1,3,4]
 * Explanation: From the right side, you can see nodes 1, 3, and 4.
 *
 * APPROACH:
 * Use level order traversal (BFS) and capture the last (rightmost) node
 * at each level. The rightmost node at each level is visible from right side.
 *
 * @param root Pointer to the root of the binary tree
 * @return vector<int> Values visible from right side, top to bottom
 *
 * @complexity
 * Time: O(n) - Visit each node once in level order
 * Space: O(w) - Queue space, where w is maximum width of tree
 */
class RightSideViewSolution {
  public:
      vector<int> rightSideView(TreeNode* root) {
          // BASE CASE: Empty tree has no right side view
          if (root == nullptr) {
              return {};
          }

          vector<int> result;
          queue<TreeNode*> q;
          q.push(root);

          // Process each level of the tree
          while (!q.empty()) {
              int levelSize = q.size();  // Number of nodes at current level

              // Process all nodes at current level
              for (int i = 0; i < levelSize; i++) {
                  TreeNode* node = q.front();
                  q.pop();

                  // Add children to queue for next level (left to right order)
                  if (node->left) {
                      q.push(node->left);
                  }
                  if (node->right) {
                      q.push(node->right);
                  }

                  // CAPTURE RIGHTMOST NODE: Last node in current level
                  // This is the node visible from right side at this level
                  if (i == levelSize - 1) {
                      result.push_back(node->val);
                  }
              }
          }

          return result;
      }

      /**
       * @brief Alternative approach using DFS with level tracking
       *
       * APPROACH:
       * Use DFS traversal, prioritizing right subtree first.
       * Keep track of current level and only add first node seen at each level.
       * Since we go right first, the first node at each level is the rightmost.
       *
       * @param root Current node
       * @param level Current level (0-indexed)
       * @param result Reference to result vector
       */
      void dfsRightView(TreeNode* root, int level, vector<int>& result) {
          if (root == nullptr) return;

          // If this is the first node we're seeing at this level,
          // it must be the rightmost (since we traverse right first)
          if (level == result.size()) {
              result.push_back(root->val);
          }

          // Traverse right subtree first, then left
          dfsRightView(root->right, level + 1, result);
          dfsRightView(root->left, level + 1, result);
      }

      vector<int> rightSideViewDFS(TreeNode* root) {
          vector<int> result;
          dfsRightView(root, 0, result);
          return result;
      }
  };

/* ========================================================================
 * PROBLEM 8: SYMMETRIC TREE (LeetCode 101)
 * ======================================================================== */

/**
 * @brief Check if a binary tree is symmetric (mirror image of itself)
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 *
 * EXAMPLE:
 * Input: root = [1,2,2,3,4,4,3]
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * Output: true
 *
 * EXAMPLE 2:
 * Input: root = [1,2,2,null,3,null,3]
 *     1
 *    / \
 *   2   2
 *    \   \
 *     3   3
 * Output: false
 *
 * APPROACH:
 * Use a recursive helper function to compare the left and right subtrees.
 * The tree is symmetric if:
 *  - Both subtrees are null, or
 *  - Both subtrees are non-null and:
 *      * Their root values are equal
 *      * Left subtree of left matches right subtree of right, and vice versa
 *
 * @param root Pointer to the root of the binary tree
 * @return true if the tree is symmetric, false otherwise
 *
 * @complexity
 * Time: O(n) - Every node is visited once
 * Space: O(h) - Recursive stack space, where h is tree height
 */

class Solution {
  public:
      // Helper to compare two subtrees for mirror symmetry
      bool helper(TreeNode* rootLeft, TreeNode* rootRight) {
          if (rootLeft == nullptr && rootRight == nullptr) return true;

          if ((rootLeft == nullptr && rootRight != nullptr) ||
              (rootLeft != nullptr && rootRight == nullptr)) return false;

          if (rootLeft->val != rootRight->val) return false;

          // Check mirror symmetry of subtrees
          return helper(rootLeft->left, rootRight->right) &&
                 helper(rootLeft->right, rootRight->left);
      }

      bool isSymmetric(TreeNode* root) {
          if (root == nullptr) return true;  // Empty tree is symmetric
          return helper(root->left, root->right);
      }
  };


/* ========================================================================
 * PROBLEM 9: LOWEST COMMON ANCESTOR OF A BINARY TREE (LeetCode 236)
 * ======================================================================== */

/**
 * @brief Find the lowest common ancestor (LCA) of two nodes in a binary tree
 *
 * PROBLEM STATEMENT:
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes p and q.
 * The lowest common ancestor is the lowest node in the tree that has both p and q
 * as descendants (where a node can be a descendant of itself).
 *
 * EXAMPLE:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of nodes 5 and 1 is 3.
 *
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5, as a node can be a descendant of itself.
 *
 * APPROACH:
 * - Traverse the tree recursively.
 * - If either p or q is found at the current node, return that node.
 * - Otherwise, recurse on both left and right subtrees.
 * - If both sides return non-null, current node is the LCA.
 * - If only one side returns non-null, propagate it upward.
 *
 * @param root Pointer to the root of the binary tree
 * @param p Pointer to the first node
 * @param q Pointer to the second node
 * @return TreeNode* Pointer to the lowest common ancestor
 *
 * @complexity
 * Time: O(n) - Visit each node once
 * Space: O(h) - Recursive stack space, where h is the height of the tree
 */

 class Solution {
  public:
      TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
          // Base case: if current node is null or matches p or q, return it
          if (root == nullptr || root == p || root == q) {
              return root;
          }

          // Recurse into left and right subtrees
          TreeNode* left = lowestCommonAncestor(root->left, p, q);
          TreeNode* right = lowestCommonAncestor(root->right, p, q);

          // If one side returns null, LCA is on the other side
          if (left == nullptr) {
              return right;
          } else if (right == nullptr) {
              return left;
          }

          // If both sides return non-null, current node is the LCA
          return root;
      }
  };

/**
 * @brief Find the maximum width of a binary tree
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, return the maximum width of the tree.
 * The width of one level is defined as the length between the leftmost
 * and rightmost non-null nodes, including null nodes in between.
 * The answer should be the maximum width among all levels.
 *
 * EXAMPLE:
 * Input: root = [1,3,2,5,3,null,9]
 *     1
 *    / \
 *   3   2
 *  / \    \
 * 5   3    9
 * Output: 4
 * Explanation: Maximum width is between 5 and 9 at level 3.
 *
 * APPROACH:
 * - Use level order traversal (BFS) with a queue.
 * - Store nodes along with their positional index (like in a complete binary tree).
 * - At each level, compute width using the indices of the first and last nodes.
 * - Normalize indices at each level to prevent integer overflow.
 *
 * @param root Pointer to the root of the binary tree
 * @return int Maximum width of any level in the tree
 *
 * @complexity
 * Time: O(n) - Every node is visited once
 * Space: O(n) - Queue holds up to n nodes in worst case
 */

 class Solution {
  public:
      int widthOfBinaryTree(TreeNode* root) {
          if(root == NULL) // if root is null
              return 0;   // simply return zero
          int ans = 0; // variable to store answer
          // queue for level order traveral
          queue<pair<TreeNode*, int>> q; // pair contain { node, index}
          q.push({root, 1}); // intially push root node
          // Implementing BFS
          while(q.empty() == false) // until queue is not empty
          {
              int size = q.size(); // take size of the queue
              // tells us minimum index at particular level
              int minAtLevel = q.front().second;
              // declaring minimum and maximum variable used for finding width
              int mn, mx;
              // traverse from the queue
              for(int i= 0; i < size; i++)
              {
                  // changes index of level by decreasing minimum index
                  int curr_index = q.front().second - minAtLevel + 1; //+ 1 because we are using 1 based indexing,
                  // take out current node
                  TreeNode* node = q.front().first;
                  q.pop(); // pop from the queue

                  // remember the formula we discussed
              //width = (maximum index at level) - (minimum index at level) + 1
                  if(i == 0)
                      mn = curr_index; // minimum index at level
                  if(i == size - 1)
                      mx = curr_index; //maximum index at level
                  // push left and right for further calculation
                  if(node -> left != NULL) //2   * i
                      q.push({node -> left, 2LL * curr_index});
                  if(node -> right != NULL) //2   * i  + 1
                      q.push({node -> right, 2LL * curr_index + 1});
              }
              ans = max(ans, mx - mn + 1); // update our answer
          }
          return ans; // finally return our answer

      }
  };

/* ========================================================================
 * PROBLEM 10: ALL NODES DISTANCE K IN BINARY TREE (LeetCode 863)
 * ======================================================================== */

/**
 * @brief Find all nodes that are exactly K distance away from a target node
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, a target node, and an integer K,
 * return a list of the values of all nodes that are a distance K from the target.
 * The answer can be returned in any order.
 *
 * EXAMPLE:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 * Output: [7, 4, 1]
 *
 * APPROACH:
 * - First, mark all parent nodes using BFS and store them in a map.
 * - Then, perform a BFS starting from the target node and traverse outward
 *   in all directions (left, right, parent).
 * - Stop the BFS when the level equals K and collect all node values at that level.
 *
 * @param root Pointer to the root of the binary tree
 * @param target Pointer to the target node
 * @param k Distance from the target node
 * @return vector<int> List of node values at distance K
 *
 * @complexity
 * Time: O(n) - Visit each node once to build parent map and again in BFS
 * Space: O(n) - For parent map, visited set, and BFS queue
 */

 class Solution {
  public:
      // Helper function to mark each node's parent using BFS
      void markParents(TreeNode* root,
                       unordered_map<TreeNode*, TreeNode*>& parent_map) {
          queue<TreeNode*> q;
          q.push(root);

          while (!q.empty()) {
              TreeNode* node = q.front();
              q.pop();

              if (node->left) {
                  parent_map[node->left] = node;
                  q.push(node->left);
              }
              if (node->right) {
                  parent_map[node->right] = node;
                  q.push(node->right);
              }
          }
      }

      vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
          unordered_map<TreeNode*, TreeNode*> parent_map;
          markParents(root, parent_map);  // Step 1: build parent links

          unordered_map<TreeNode*, bool> visited;
          queue<TreeNode*> q;
          q.push(target);
          visited[target] = true;
          int level = 0;

          // Step 2: BFS outward from the target node
          while (!q.empty()) {
              if (level++ == k) break;

              int size = q.size();
              for (int i = 0; i < size; i++) {
                  TreeNode* node = q.front();
                  q.pop();

                  // Explore left child
                  if (node->left && !visited[node->left]) {
                      q.push(node->left);
                      visited[node->left] = true;
                  }

                  // Explore right child
                  if (node->right && !visited[node->right]) {
                      q.push(node->right);
                      visited[node->right] = true;
                  }

                  // Explore parent node
                  if (parent_map[node] && !visited[parent_map[node]]) {
                      q.push(parent_map[node]);
                      visited[parent_map[node]] = true;
                  }
              }
          }

          // Collect result from the final queue state
          vector<int> result;
          while (!q.empty()) {
              result.push_back(q.front()->val);
              q.pop();
          }

          return result;
      }
  };

/* ========================================================================
 * PROBLEM 11: COUNT COMPLETE TREE NODES (LeetCode 222)
 * ======================================================================== */

/**
 * @brief Count the number of nodes in a complete binary tree
 *
 * PROBLEM STATEMENT:
 * Given the root of a complete binary tree, return the number of nodes in the tree.
 *
 * A complete binary tree is a binary tree in which every level, except possibly the last,
 * is completely filled, and all nodes are as far left as possible.
 *
 * EXAMPLE:
 * Input: root = [1,2,3,4,5,6]
 * Output: 6
 *
 * APPROACH:
 * - If the height of the left-most path equals the height of the right-most path,
 *   the subtree is a full binary tree and the number of nodes is (2^h - 1).
 * - Otherwise, recursively count nodes in left and right subtrees.
 *
 * OPTIMIZATION:
 * Reduces time complexity to O(log^2 n) by avoiding full traversal of all nodes.
 *
 * @param root Pointer to the root of the complete binary tree
 * @return int Total number of nodes in the tree
 *
 * @complexity
 * Time: O(log^2 n) - For each level (log n), we traverse height (log n) again
 * Space: O(log n) - Recursive stack space
 */

 class Solution {
  public:
      // Helper to compute height of the left-most path
      int findLeftHeight(TreeNode* root) {
          int height = 0;
          while (root != nullptr) {
              root = root->left;
              height++;
          }
          return height;
      }

      // Helper to compute height of the right-most path
      int findRightHeight(TreeNode* root) {
          int height = 0;
          while (root != nullptr) {
              root = root->right;
              height++;
          }
          return height;
      }

      int countNodes(TreeNode* root) {
          if (root == nullptr) return 0;

          int leftHeight = findLeftHeight(root);
          int rightHeight = findRightHeight(root);

          // If left height equals right height, it's a full binary tree
          if (leftHeight == rightHeight) {
              return (1 << leftHeight) - 1;  // 2^height - 1
          }

          // Otherwise, recursively count nodes in left and right subtrees
          return 1 + countNodes(root->left) + countNodes(root->right);
      }
  };

/* ============================================================================
 * PROBLEM 12: AMOUNT OF TIME FOR BINARY TREE TO BE INFECTED (LeetCode 2385)
 * ============================================================================ */

/**
 * @brief Return the total time to infect the entire binary tree starting from a given node
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree and an integer `start`, representing the node where
 * the infection starts, return the total time in minutes it takes to infect the entire tree.
 * Infection spreads to adjacent nodes (left, right, and parent) each minute.
 *
 * EXAMPLE:
 * Input: root = [1,5,3,null,4,10,6,9,2], start = 3
 * Output: 4
 *
 * APPROACH:
 * - Use DFS (`inorder`) to build a map of child → parent pointers.
 * - Locate the starting node using a separate DFS (`find`).
 * - Then perform a BFS from the start node and simulate infection spread to:
 *   * left child, right child, and parent (if they exist and are not visited).
 * - Count the number of levels (minutes) until the entire tree is infected.
 *
 * @param root Pointer to the root of the binary tree
 * @param start Value of the node where infection starts
 * @return int Time taken to infect the entire tree
 *
 * @complexity
 * Time: O(n) - Visit each node once to build parent map and simulate infection
 * Space: O(n) - For map, visited set, and queue
 */

 class Solution {
  public:
      unordered_map<TreeNode*, TreeNode*> mp;  // Child → Parent mapping

      // Step 1: Create parent mapping using DFS
      void inorder(TreeNode* root) {
          if (root == nullptr) return;

          if (root->left) {
              mp[root->left] = root;
          }
          inorder(root->left);

          if (root->right) {
              mp[root->right] = root;
          }
          inorder(root->right);
      }

      // Step 2: Find the TreeNode* corresponding to the value `start`
      TreeNode* find(TreeNode* root, int start) {
          if (root == nullptr || root->val == start) return root;

          TreeNode* left = find(root->left, start);
          if (left) return left;

          return find(root->right, start);
      }

      int amountOfTime(TreeNode* root, int start) {
          TreeNode* starting = find(root, start);  // Locate the starting node
          inorder(root);  // Build parent links

          unordered_set<TreeNode*> visited;
          queue<TreeNode*> q;
          q.push(starting);
          visited.insert(starting);

          int time = -1;

          // Step 3: BFS to simulate infection spread
          while (!q.empty()) {
              int levelSize = q.size();
              while (levelSize--) {
                  TreeNode* node = q.front();
                  q.pop();

                  // Spread to left child
                  if (node->left && !visited.count(node->left)) {
                      q.push(node->left);
                      visited.insert(node->left);
                  }

                  // Spread to right child
                  if (node->right && !visited.count(node->right)) {
                      q.push(node->right);
                      visited.insert(node->right);
                  }

                  // Spread to parent
                  if (mp.count(node) && !visited.count(mp[node])) {
                      q.push(mp[node]);
                      visited.insert(mp[node]);
                  }
              }
              time++;
          }

          return time;
      }
  };

/* ============================================================================
 * PROBLEM 13: CONSTRUCT BINARY TREE FROM PREORDER AND INORDER (LeetCode 105)
 * ============================================================================ */

/**
 * @brief Construct a binary tree from preorder and inorder traversal
 *
 * PROBLEM STATEMENT:
 * Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder
 * traversal of a binary tree and `inorder` is the inorder traversal, construct and return
 * the binary tree.
 *
 * EXAMPLE:
 * Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * Output: [3,9,20,null,null,15,7]
 *
 * APPROACH:
 * - The first element in preorder is always the root.
 * - In inorder traversal, elements to the left of the root are part of the left subtree,
 *   and elements to the right are part of the right subtree.
 * - Use a helper function with an index pointer to build the tree recursively.
 *
 * @param preorder Preorder traversal vector
 * @param inorder Inorder traversal vector
 * @return TreeNode* Root of the constructed binary tree
 *
 * @complexity
 * Time: O(n^2) - For each node, we do a linear search in inorder (can be optimized)
 * Space: O(n) - Recursive stack in worst case (unbalanced tree)
 */

 class Solution {
  public:
      // Helper function to recursively build tree
      TreeNode* solve(vector<int>& preorder, vector<int>& inorder, int& idx, int start, int end) {
          if (start > end) return nullptr;

          // Current node is root from preorder
          TreeNode* root = new TreeNode(preorder[idx]);

          // Find the index of the root in inorder
          int inIndex;
          for (int i = start; i <= end; i++) {
              if (inorder[i] == preorder[idx]) {
                  inIndex = i;
                  break;
              }
          }

          idx++;  // Move to next element in preorder

          // Build left and right subtrees recursively
          root->left = solve(preorder, inorder, idx, start, inIndex - 1);
          root->right = solve(preorder, inorder, idx, inIndex + 1, end);

          return root;
      }

      TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
          int idx = 0;
          return solve(preorder, inorder, idx, 0, preorder.size() - 1);
      }
  };

/* =========================================================================================
 * PROBLEM 14: CONSTRUCT BINARY TREE FROM INORDER AND POSTORDER TRAVERSAL (LeetCode 106)
 * ========================================================================================= */

/**
 * @brief Construct a binary tree from inorder and postorder traversal
 *
 * PROBLEM STATEMENT:
 * Given two integer arrays `inorder` and `postorder` where `inorder` is the inorder
 * traversal of a binary tree and `postorder` is the postorder traversal, construct and
 * return the binary tree.
 *
 * EXAMPLE:
 * Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 * Output: [3,9,20,null,null,15,7]
 *
 * APPROACH:
 * - The last element in postorder is always the root of the current subtree.
 * - Locate this root in inorder to divide the array into left and right subtrees.
 * - Recurse first for the right subtree, then the left (reverse of postorder).
 *
 * @param inorder Inorder traversal vector
 * @param postorder Postorder traversal vector
 * @return TreeNode* Root of the constructed binary tree
 *
 * @complexity
 * Time: O(n^2) - For each node, we perform a linear search in the inorder array
 * Space: O(n) - Stack space for recursion (height of the tree)
 */

 class Solution {
  public:
      // Helper function to build the tree recursively
      TreeNode* solve(vector<int>& inorder, vector<int>& postorder, int& idx, int start, int end) {
          if (start > end) return nullptr;

          // Create the root from current postorder index
          TreeNode* root = new TreeNode(postorder[idx]);

          // Find the root's index in inorder array
          int inIndex;
          for (int i = start; i <= end; i++) {
              if (inorder[i] == postorder[idx]) {
                  inIndex = i;
                  break;
              }
          }

          idx--;  // Move to the next postorder element (right to left)

          // Important: Build right subtree first, then left
          root->right = solve(inorder, postorder, idx, inIndex + 1, end);
          root->left = solve(inorder, postorder, idx, start, inIndex - 1);

          return root;
      }

      TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
          int idx = postorder.size() - 1;
          return solve(inorder, postorder, idx, 0, inorder.size() - 1);
      }
  };

/* =======================================================================
 * PROBLEM 15: SERIALIZE AND DESERIALIZE BINARY TREE (LeetCode 297)
 * ======================================================================= */

/**
 * @brief Serialize and deserialize a binary tree
 *
 * PROBLEM STATEMENT:
 * Design an algorithm to serialize and deserialize a binary tree.
 * Serialization is the process of converting a data structure into a format
 * that can be stored or transmitted. Deserialization is the reverse process.
 * You must implement these methods:
 *   - string serialize(TreeNode* root)
 *   - TreeNode* deserialize(string data)
 * The encoded string should be able to be deserialized to the original tree.
 *
 * EXAMPLE:
 * Input: root = [1,2,3,null,null,4,5]
 * Output: "1,2,3,#,#,4,5,#,#,#,#"
 *
 * APPROACH:
 * - For serialization, use level-order (BFS) traversal.
 *   Represent null nodes using "#".
 * - For deserialization, read values in BFS order and rebuild the tree using a queue.
 *
 * @complexity
 * Time: O(n) - Both serialize and deserialize traverse the tree once
 * Space: O(n) - Queue and result string size is proportional to number of nodes
 */

 class Codec {
  public:
      // Encodes a tree to a single string using BFS
      string serialize(TreeNode* root) {
          if (!root) return "";

          string result;
          queue<TreeNode*> q;
          q.push(root);

          while (!q.empty()) {
              TreeNode* node = q.front();
              q.pop();

              if (node) {
                  result += to_string(node->val) + ",";
                  q.push(node->left);
                  q.push(node->right);
              } else {
                  result += "#,";
              }
          }

          return result;
      }

      // Decodes your encoded data to tree using BFS
      TreeNode* deserialize(string data) {
          if (data.empty()) return nullptr;

          stringstream ss(data);
          string val;
          getline(ss, val, ',');  // First value is the root

          TreeNode* root = new TreeNode(stoi(val));
          queue<TreeNode*> q;
          q.push(root);

          while (!q.empty()) {
              TreeNode* node = q.front();
              q.pop();

              // Deserialize left child
              if (getline(ss, val, ',')) {
                  if (val != "#") {
                      node->left = new TreeNode(stoi(val));
                      q.push(node->left);
                  }
              }

              // Deserialize right child
              if (getline(ss, val, ',')) {
                  if (val != "#") {
                      node->right = new TreeNode(stoi(val));
                      q.push(node->right);
                  }
              }
          }

          return root;
      }
  };


/* ============================================================================
 * PROBLEM 16: FLATTEN BINARY TREE TO LINKED LIST (LeetCode 114)
 * ============================================================================ */

/**
 * @brief Flatten a binary tree to a linked list in-place (right-skewed tree)
 *
 * PROBLEM STATEMENT:
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * - The "linked list" should use the right pointers in the tree.
 * - The left child of all nodes should be NULL.
 * - The list should follow the preorder traversal of the binary tree.
 *
 * EXAMPLE:
 * Input: root = [1,2,5,3,4,null,6]
 * Output: [1,null,2,null,3,null,4,null,5,null,6]
 *
 * APPROACH:
 * - Traverse the tree using an iterative approach.
 * - For each node, if it has a left child:
 *     → Find the rightmost node of the left subtree.
 *     → Attach the current node’s right subtree to that node’s right.
 *     → Move the left subtree to the right and set left to NULL.
 * - Move to the right child and repeat.
 *
 * @param root Root of the binary tree
 * @return void (modifies the tree in-place)
 *
 * @complexity
 * Time: O(n) - Each node is visited once
 * Space: O(1) - No extra space used
 */

 class Solution {
  public:
      void flatten(TreeNode* root) {
          TreeNode* curr = root;

          while (curr != nullptr) {
              // If current node has a left subtree
              if (curr->left != nullptr) {
                  TreeNode* prev = curr->left;

                  // Find the rightmost node of the left subtree
                  while (prev->right != nullptr) {
                      prev = prev->right;
                  }

                  // Connect the original right subtree to the right of this rightmost node
                  prev->right = curr->right;

                  // Move the left subtree to the right and nullify the left
                  curr->right = curr->left;
                  curr->left = nullptr;
              }

              // Move to the right in the flattened tree
              curr = curr->right;
          }
      }
  };
