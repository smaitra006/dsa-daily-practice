/* ==============================================================================
 * Topic: Segment Tree Basics
 *
 * What is a Segment Tree?
 * - A binary tree data structure used for answering range queries and performing updates efficiently.
 * - Can handle:
 *      - Range sum queries
 *      - Range minimum / maximum queries
 *      - Range GCD, LCM, XOR, etc.
 *
 * Why Segment Tree?
 * - Naive approach:
 *      - Query: O(N) for each range
 *      - Update: O(1)
 * - Segment Tree:
 *      - Query: O(log N)
 *      - Update: O(log N)
 * - Useful when:
 *      - Multiple queries & updates
 *      - Queries cover different subranges
 *
 * Structure:
 * - Each node stores an aggregate value (sum/min/max/etc.) for a specific segment [l, r].
 * - Root → segment [0, N-1]
 * - Left child → segment [l, mid]
 * - Right child → segment [mid+1, r]
 *
 * Implementation Steps:
 * 1. Build: Recursively build the tree from array.
 * 2. Query: Recursively return aggregate for the given range.
 * 3. Update: Recursively update one element and propagate changes.
 *
 * Time Complexity:
 * - Build:  O(N)
 * - Query:  O(log N)
 * - Update: O(log N)
 * Space Complexity:
 * - O(4 * N) (safe upper bound for segment tree size)
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> tree; // Stores segment tree nodes
    int n;

    /* --------------------------------------------------------------------------
     * Function: buildTree
     * Purpose : Build the segment tree from the input array
     * Params  :
     *      index → current tree node index
     *      l, r  → segment boundaries represented by current node
     *      arr   → original array
     * -------------------------------------------------------------------------- */
    void buildTree(int index, int l, int r, const vector<int> &arr) {
        if (l == r) {
            tree[index] = arr[l]; // Leaf node
            return;
        }
        int mid = (l + r) / 2;
        buildTree(2 * index + 1, l, mid, arr);       // Build left child
        buildTree(2 * index + 2, mid + 1, r, arr); // Build right child
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2]; // Merge results
    }

    /* --------------------------------------------------------------------------
     * Function: queryTree
     * Purpose : Query the sum over a given range [ql, qr]
     * Params  :
     *      index → current tree node index
     *      l, r  → segment boundaries represented by current node
     *      ql, qr → query range
     * -------------------------------------------------------------------------- */
    int queryTree(int index, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0; // Completely outside
        if (ql <= l && r <= qr) return tree[index]; // Completely inside
        int mid = (l + r) / 2;
        return queryTree(2 * index + 1, l, mid, ql, qr) +
               queryTree(2 * index + 2, mid + 1, r, ql, qr);
    }

    /* --------------------------------------------------------------------------
     * Function: updateTree
     * Purpose : Update a single element and propagate the changes
     * Params  :
     *      index → current tree node index
     *      l, r  → segment boundaries represented by current node
     *      pos   → position to update
     *      val   → new value
     * -------------------------------------------------------------------------- */
    void updateTree(int index, int l, int r, int pos, int val) {
        if (l == r) {
            tree[index] = val; // Leaf node updated
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) updateTree(2 * index + 1, l, mid, pos, val);
        else updateTree(2 * index + 2, mid + 1, r, pos, val);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2]; // Merge updates
    }

public:
    // Constructor
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(0, 0, n - 1, arr);
    }

    // Public query function
    int query(int ql, int qr) {
        return queryTree(0, 0, n - 1, ql, qr);
    }

    // Public update function
    void update(int pos, int val) {
        updateTree(0, 0, n - 1, pos, val);
    }
};

/* ==============================================================================
 * Example Usage
 * ==============================================================================
int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree seg(arr);

    cout << seg.query(1, 3) << "\n"; // Output: 15  (3+5+7)

    seg.update(1, 10);               // arr[1] = 10
    cout << seg.query(1, 3) << "\n"; // Output: 22  (10+5+7)
}
*/
