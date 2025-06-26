#include <bits/stdc++.h>
using namespace std;

/*
 * BINARY TREE CONCEPTS:
 *
 * Tree: A hierarchical data structure where the top node is called the root node.
 * Contains parent nodes, children nodes, sibling nodes (nodes at same level),
 * and leaf nodes (nodes at the last level with no children).
 *
 * Binary Tree: A tree where each node has at most two children.
 *
 * TYPES OF BINARY TREES:
 * - Full Binary Tree: All nodes have either 0 or 2 children
 * - Complete Binary Tree: All levels are completely filled except possibly
 *   the last level, which is filled from left to right
 * - Perfect Binary Tree: All leaf nodes are at the same level
 * - Balanced Binary Tree: Height of the tree is at most log(n)
 * - Degenerate Binary Tree: Skew tree (like a straight line) where every
 *   node has only one child
 */

// Node structure for binary tree
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

/* ========================================================================
 * DEPTH FIRST SEARCH (DFS) TRAVERSALS
 * ======================================================================== */

/*
 * INORDER TRAVERSAL (Recursive): Left -> Root -> Right
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to recursion stack
 */
void inOrder(struct Node* root) {
    if (root == nullptr)
        return;

    inOrder(root->left);        // Traverse left subtree
    cout << root->data << " ";  // Visit root
    inOrder(root->right);       // Traverse right subtree
}

/*
 * INORDER TRAVERSAL (Iterative): Left -> Root -> Right
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to stack
 */
void iterativeInOrder(struct Node* root) {
    if (root == nullptr)
        return;

    stack<struct Node*> st;
    struct Node* curr = root;

    while (curr != nullptr || !st.empty()) {
        // Go as left as possible
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        // Backtrack to previous node
        curr = st.top();
        st.pop();

        // Visit current node
        cout << curr->data << " ";

        // Move to right subtree
        curr = curr->right;
    }
}

/*
 * PREORDER TRAVERSAL (Recursive): Root -> Left -> Right
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to recursion stack
 */
void preOrder(struct Node* root) {
    if (root == nullptr)
        return;

    cout << root->data << " ";  // Visit root
    preOrder(root->left);       // Traverse left subtree
    preOrder(root->right);      // Traverse right subtree
}

/*
 * PREORDER TRAVERSAL (Iterative): Root -> Left -> Right
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to stack
 */
void iterativePreOrder(struct Node* root) {
    if (root == nullptr)
        return;

    stack<struct Node*> st;
    st.push(root);

    while (!st.empty()) {
        struct Node* node = st.top();
        st.pop();

        cout << node->data << " ";

        // Push right child first so that left is processed first
        if (node->right)
            st.push(node->right);
        if (node->left)
            st.push(node->left);
    }
}

/*
 * POSTORDER TRAVERSAL (Recursive): Left -> Right -> Root
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to recursion stack
 */
void postOrder(struct Node* root) {
    if (root == nullptr)
        return;

    postOrder(root->left);      // Traverse left subtree
    postOrder(root->right);     // Traverse right subtree
    cout << root->data << " ";  // Visit root
}

/*
 * POSTORDER TRAVERSAL (Iterative): Left -> Right -> Root
 * Uses two stacks to simulate the recursive behavior
 * Time Complexity: O(n)
 * Space Complexity: O(n) - due to two stacks
 */
void iterativePostOrder(struct Node* root) {
    if (root == nullptr)
        return;

    stack<struct Node*> st1, st2;
    st1.push(root);

    // First stack processes nodes in reverse postorder
    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();
        st2.push(node);  // Store nodes in reverse postorder

        // Push left first, then right (opposite of preorder)
        if (node->left)
            st1.push(node->left);
        if (node->right)
            st1.push(node->right);
    }

    // Second stack gives us the correct postorder sequence
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

/* ========================================================================
 * BREADTH FIRST SEARCH (BFS) TRAVERSAL
 * ======================================================================== */

/*
 * LEVEL ORDER TRAVERSAL: Process nodes level by level from top to bottom
 * and left to right within each level
 * Time Complexity: O(n)
 * Space Complexity: O(w) where w is the maximum width of the tree
 */
void levelOrder(struct Node* root, vector<vector<int>>& result) {
    if (root == nullptr)
        return;

    queue<struct Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();  // Number of nodes at current level
        vector<int> currentLevel;

        // Process all nodes at current level
        for (int i = 0; i < levelSize; i++) {
            struct Node* node = q.front();
            q.pop();

            // Add children to queue for next level
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);

            // Store current node's data
            currentLevel.push_back(node->data);
        }

        // Add current level to result
        result.push_back(currentLevel);
    }
}

/* ========================================================================
 * MORRIS TRAVERSALS (Inorder, Preorder, Postorder)
 * ======================================================================== */

/**
 * @brief Inorder traversal using Morris Traversal (O(1) space)
 *
 * Morris Traversal allows tree traversal without recursion or stack.
 * It uses threaded binary trees by modifying pointers during traversal.
 *
 * TIME: O(n)
 * SPACE: O(1) [excluding output]
 */
vector<int> morrisInorder(Node* root) {
  vector<int> result;
  Node* curr = root;

  while (curr != nullptr) {
      if (curr->left == nullptr) {
          result.push_back(curr->data);  // Visit the node
          curr = curr->right;            // Move to right subtree
      } else {
          // Find the rightmost node in left subtree (predecessor)
          Node* pred = curr->left;
          while (pred->right && pred->right != curr) {
              pred = pred->right;
          }

          if (pred->right == nullptr) {
              pred->right = curr;      // Create thread
              curr = curr->left;       // Move left
          } else {
              pred->right = nullptr;   // Remove thread
              result.push_back(curr->data);  // Visit after left is done
              curr = curr->right;      // Move right
          }
      }
  }

  return result;
}


/**
* @brief Preorder traversal using Morris Traversal (O(1) space)
*
* Similar to Morris Inorder, but visit the node *before* going left.
*
* TIME: O(n)
* SPACE: O(1) [excluding output]
*/
vector<int> morrisPreorder(Node* root) {
  vector<int> result;
  Node* curr = root;

  while (curr != nullptr) {
      if (curr->left == nullptr) {
          result.push_back(curr->data);  // Visit node
          curr = curr->right;
      } else {
          Node* pred = curr->left;
          while (pred->right && pred->right != curr) {
              pred = pred->right;
          }

          if (pred->right == nullptr) {
              result.push_back(curr->data);  // Visit before threading
              pred->right = curr;
              curr = curr->left;
          } else {
              pred->right = nullptr;  // Remove thread
              curr = curr->right;
          }
      }
  }

  return result;
}


/**
* @brief Postorder traversal using Morris Traversal (O(1) space)
*
* Uses a dummy node and reverse path trick to simulate postorder.
*
* TIME: O(n)
* SPACE: O(1) [excluding output]
*/
void reversePath(Node* start, Node* end) {
  if (start == end) return;
  Node* x = start;
  Node* y = start->right;
  Node* z;

  while (x != end) {
      z = y->right;
      y->right = x;
      x = y;
      y = z;
  }
}

void collectReverse(Node* start, Node* end, vector<int>& result) {
  reversePath(start, end);

  Node* node = end;
  while (true) {
      result.push_back(node->data);
      if (node == start) break;
      node = node->right;
  }

  reversePath(end, start);  // Restore original structure
}

vector<int> morrisPostorder(Node* root) {
  vector<int> result;
  Node* dummy;
  dummy->left = root;
  Node* curr = dummy;

  while (curr) {
      if (curr->left == nullptr) {
          curr = curr->right;
      } else {
          Node* pred = curr->left;
          while (pred->right && pred->right != curr) {
              pred = pred->right;
          }

          if (pred->right == nullptr) {
              pred->right = curr;
              curr = curr->left;
          } else {
              collectReverse(curr->left, pred, result);
              pred->right = nullptr;
              curr = curr->right;
          }
      }
  }

  return result;
}


int main() {
    // Create a sample binary tree
    //       1
    //      / \
    //     2   3
    //    / \ /
    //   4  5 6

    struct Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);

    cout << "Tree structure:" << endl;
    cout << "       1" << endl;
    cout << "      / \\" << endl;
    cout << "     2   3" << endl;
    cout << "    / \\ /" << endl;
    cout << "   4  5 6" << endl << endl;

    // Demonstrate different traversals
    // cout << "Inorder (Recursive):   ";
    // inOrder(root);
    // cout << endl;

    // cout << "Inorder (Iterative):   ";
    // iterativeInOrder(root);
    // cout << endl;

    // cout << "Preorder (Recursive):  ";
    // preOrder(root);
    // cout << endl;

    // cout << "Preorder (Iterative):  ";
    // iterativePreOrder(root);
    // cout << endl;

    // cout << "Postorder (Recursive): ";
    // postOrder(root);
    // cout << endl;

    // cout << "Postorder (Iterative): ";
    // iterativePostOrder(root);
    // cout << endl;

    // cout << "Level Order Traversal:" << endl;
    // vector<vector<int>> result;
    // levelOrder(root, result);
    // for (int i = 0; i < result.size(); i++) {
    //     cout << "Level " << i + 1 << ": ";
    //     for (int j = 0; j < result[i].size(); j++) {
    //         cout << result[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
