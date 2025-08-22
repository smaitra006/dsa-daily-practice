#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Most Stones Removed with Same Row or Column (LeetCode 947)
================================================================================
Task:
    On a 2D plane, we place n stones at integer coordinates (x[i], y[i]).
    A stone can be removed if there is another stone in the same row or column.
    Find the maximum number of stones that can be removed.

--------------------------------------------------------------------------------
Key Insight:
    - Stones in the same row or column belong to the same "connected component".
    - If a connected component has k stones, we can remove (k - 1) stones
      and leave just 1 behind.
    - Answer = total stones - number of connected components.

--------------------------------------------------------------------------------
Approach (Disjoint Set Union - Union by Rank + Path Compression):
    1. Treat each row index and column index as nodes in DSU.
    2. Since row and column indices can overlap, offset column indices by +10001
       to keep them disjoint.
    3. For each stone at (x, y):
        - Union (x) with (y + OFFSET).
    4. Count distinct connected components that have stones.
    5. Result = total stones - number of components.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of stones.

    Time Complexity:  O(N * α(N)) ≈ O(N)
        - Each union/find is nearly O(1).

    Space Complexity: O(N)
        - DSU parent and rank arrays.
================================================================================
*/

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones)
    {
        int OFFSET = 10001;  // To separate row indices and column indices
        DSU dsu(20005);

        unordered_set<int> seen;
        for (auto& s : stones) {
            int row = s[0];
            int col = s[1] + OFFSET;
            dsu.unite(row, col);
            seen.insert(row);
            seen.insert(col);
        }

        unordered_set<int> uniqueRoots;
        for (int node : seen) {
            uniqueRoots.insert(dsu.find(node));
        }

        // Answer = total stones - number of connected components
        return stones.size() - uniqueRoots.size();
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]

Output:
    5

Explanation:
    - All stones are connected, forming one big component.
    - Total stones = 6, components = 1 → removable stones = 6 - 1 = 5.
================================================================================
*/

