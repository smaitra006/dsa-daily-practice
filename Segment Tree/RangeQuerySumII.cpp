/* ==============================================================================
 * Problem: Range Query Sum II (GFG)
 *
 * Task:
 * - You are given an integer array `arr[]` of size `n`.
 * - You need to perform two types of operations efficiently:
 *     1. Update: Update the value at a given index.
 *     2. Query: Return the sum of elements in a specified index range [L, R].
 *
 * Approach: Segment Tree
 * - Build a Segment Tree on `arr[]` to enable:
 *     • Range sum queries in O(log n)
 *     • Point updates in O(log n)
 * - Core operations include:
 *     • `buildTree`     — Construct the tree
 *     • `rangeQuery`    — Retrieve range sum
 *     • `pointUpdate`   — Update a single element
 *
 * Time Complexity  : Build → O(n), Query → O(log n), Update → O(log n)
 * Space Complexity : O(4 * n) for the segment tree
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<long long> tree;  // Use long long for safe sum operations

    void buildTree(int node, int start, int end, const vector<int>& arr)
    {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            buildTree(2 * node, start, mid, arr);
            buildTree(2 * node + 1, mid + 1, end, arr);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    long long rangeQuery(int node, int start, int end, int L, int R)
    {
        if (R < start || end < L) {
            return 0;  // Out of current segment
        }
        if (L <= start && end <= R) {
            return tree[node];  // Totally inside range
        }
        int mid = (start + end) / 2;
        return rangeQuery(2 * node, start, mid, L, R)
            + rangeQuery(2 * node + 1, mid + 1, end, L, R);
    }

    void pointUpdate(int node, int start, int end, int index, int val)
    {
        if (start == end) {
            tree[node] = val;  // Leaf updated
        }
        else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                pointUpdate(2 * node, start, mid, index, val);
            }
            else {
                pointUpdate(2 * node + 1, mid + 1, end, index, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

public:
    SegmentTree(const vector<int>& arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(1, 0, n - 1, arr);
    }

    long long query(int L, int R)
    {
        return rangeQuery(1, 0, n - 1, L, R);
    }

    void update(int index, int value)
    {
        pointUpdate(1, 0, n - 1, index, value);
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<int> arr = {2, 5, 1, 4, 9};
 *     SegmentTree seg(arr);
 *
 *     cout << seg.query(1, 3) << endl; // Sum from indices 1 to 3 → 5 + 1 + 4 = 10
 *     seg.update(2, 7);                // arr[2] = 7
 *     cout << seg.query(1, 3) << endl; // Now → 5 + 7 + 4 = 16
 *
 *     return 0;
 * }
 * ============================================================================== */
