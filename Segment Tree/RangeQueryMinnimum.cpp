/* ==============================================================================
 * Problem: Range Query Minimum (RMQ) using Segment Tree
 *
 * Task:
 * - You are given an integer array `arr[]` of size `n`.
 * - You need to perform two types of operations efficiently:
 *     1. Update: Update the value at a given index.
 *     2. Query: Return the minimum element in a specified index range [L, R].
 *
 * Approach: Segment Tree
 * - Build a Segment Tree on `arr[]` to enable:
 *     • Range minimum queries in O(log n)
 *     • Point updates in O(log n)
 * - Core operations include:
 *     • `buildTree`     — Construct the tree
 *     • `rangeQuery`    — Retrieve range minimum
 *     • `pointUpdate`   — Update a single element
 *
 * Time Complexity  : Build → O(n), Query → O(log n), Update → O(log n)
 * Space Complexity : O(4 * n) for the segment tree
 * ==============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> tree;

    void buildTree(int node, int start, int end, const vector<int>& arr)
    {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            buildTree(2 * node, start, mid, arr);
            buildTree(2 * node + 1, mid + 1, end, arr);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int rangeQuery(int node, int start, int end, int L, int R)
    {
        if (R < start || end < L) {
            return INT_MAX;  // Out of range, return max possible
        }
        if (L <= start && end <= R) {
            return tree[node];  // Completely inside range
        }
        int mid = (start + end) / 2;
        return min(
            rangeQuery(2 * node, start, mid, L, R),
            rangeQuery(2 * node + 1, mid + 1, end, L, R)
        );
    }

    void pointUpdate(int node, int start, int end, int index, int val)
    {
        if (start == end) {
            tree[node] = val;  // Update leaf
        }
        else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                pointUpdate(2 * node, start, mid, index, val);
            }
            else {
                pointUpdate(2 * node + 1, mid + 1, end, index, val);
            }
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

public:
    SegmentTree(const vector<int>& arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(1, 0, n - 1, arr);
    }

    int query(int L, int R)
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
 *     vector<int> arr = {4, 2, 5, 1, 6, 3};
 *     SegmentTree seg(arr);
 *
 *     cout << seg.query(1, 4) << endl; // Minimum from index 1 to 4 → min(2,5,1,6) = 1
 *     seg.update(3, 7);                // arr[3] = 7
 *     cout << seg.query(1, 4) << endl; // Now min(2,5,7,6) = 2
 *
 *     return 0;
 * }
 * ==============================================================================
 */
