#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Number of Provinces (LeetCode 547)
================================================================================
Task:
    You are given an n x n matrix isConnected where:
        - isConnected[i][j] = 1 if the ith and jth cities are directly connected
        - isConnected[i][j] = 0 otherwise.

    A province is a group of directly or indirectly connected cities.
    Return the total number of provinces.

--------------------------------------------------------------------------------
Approach (Disjoint Set Union - DSU with Union by Rank + Path Compression):
    1. Initialize DSU with n nodes, each city in its own set.
    2. Iterate over the upper triangle of isConnected matrix:
        - If cities i and j are connected, union them.
    3. Count the number of unique parents (provinces).

    Optimizations:
        - Path Compression in `find()`: Flattens the tree.
        - Union by Rank: Attaches smaller tree under the bigger one.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let N = number of cities.

    Time Complexity:  O(N^2 * α(N))
        - Iterating over matrix: O(N^2)
        - Each union/find operation ~ O(α(N)), inverse Ackermann (almost constant).

    Space Complexity: O(N)
        - Parent array, Rank array.
================================================================================
*/

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
public:
    // Constructor
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find(int x)
    {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    // Union by rank
    void unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        int n = isConnected.size();
        DSU dsu(n);

        // Step 1: Union all directly connected cities
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // only upper triangle
                if (isConnected[i][j] == 1) {
                    dsu.unite(i, j);
                }
            }
        }

        // Step 2: Count unique parents (provinces)
        unordered_set<int> provinces;
        for (int i = 0; i < n; i++) {
            provinces.insert(dsu.find(i));
        }

        return provinces.size();
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    isConnected = [[1,1,0],
                   [1,1,0],
                   [0,0,1]]

Output:
    2

Explanation:
    - Cities 0 and 1 form one province.
    - City 2 forms another province.
    - Total = 2 provinces.

--------------------------------------------------------------------------------
Notes:
    - This problem can also be solved using DFS/BFS on adjacency matrix.
    - DSU is more efficient and elegant for dynamic connectivity problems.
================================================================================
*/
