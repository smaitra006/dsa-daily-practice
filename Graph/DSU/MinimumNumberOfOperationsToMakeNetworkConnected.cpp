#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Number of Operations to Make Network Connected (LeetCode 1319)
================================================================================
Task:
    There are n computers numbered from 0 to n-1 connected by ethernet cables
    forming a network. The connections are given as an edge list.

    A connection [a, b] between computers a and b allows them to directly
    communicate. Any two computers are connected directly or indirectly if
    there is a path between them.

    We want to connect all the computers. You can extract an existing cable
    and place it between any two disconnected computers.

    Return the minimum number of operations needed to make all computers
    connected. If impossible, return -1.

--------------------------------------------------------------------------------
Key Insight:
    - To connect n nodes, at least (n - 1) edges are required.
    - If edges < n - 1 → impossible → return -1.
    - Use Disjoint Set Union (Union-Find) to count connected components.
    - To connect `components` groups, we need (components - 1) extra edges.

--------------------------------------------------------------------------------
Approach (DSU):
    1. Check if number of connections < n - 1 → return -1.
    2. Initialize DSU for n computers.
    3. Union all given connections.
    4. Count the number of connected components.
    5. Answer = components - 1.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of computers, m = number of connections.

    Time Complexity:  O(m * α(n))
        - DSU operations are almost O(1) (inverse Ackermann).
    Space Complexity: O(n)
        - DSU parent, rank arrays, and auxiliary set.
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
        if (parent[x] == x) return x;
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

    // Count connected components
    int getCompo()
    {
        unordered_set<int> s;
        for (int i = 0; i < parent.size(); i++) {
            s.insert(find(i));
        }
        return s.size();
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections)
    {
        int sz = connections.size();
        // If not enough edges, impossible
        if (sz < n - 1) return -1;

        DSU dsu(n);

        // Union all connections
        for (auto& edge : connections) {
            int x = edge[0];
            int y = edge[1];
            dsu.unite(x, y);
        }

        // Count components
        int components = dsu.getCompo();

        // Need (components - 1) edges to connect all
        return components - 1;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 4, connections = [[0,1],[0,2],[1,2]]

Output:
    1

Explanation:
    - 3 nodes are already connected in one component.
    - Node 3 is isolated.
    - Need 1 extra cable to connect node 3.
================================================================================
*/

