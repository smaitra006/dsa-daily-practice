#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Remove Max Number of Edges to Keep Graph Fully Traversable (LeetCode 1579)
================================================================================
Task:
    Alice and Bob have an undirected graph with n nodes (1-indexed).
    Each edge is of one of three types:
        - Type 1: Only Alice can traverse.
        - Type 2: Only Bob can traverse.
        - Type 3: Both Alice and Bob can traverse.

    You want to remove as many edges as possible while ensuring:
        - The graph remains fully traversable for BOTH Alice and Bob.
        - Fully traversable means all nodes are connected for Alice and Bob.

    Return the maximum number of edges that can be removed.
    If impossible, return -1.

--------------------------------------------------------------------------------
Key Insight:
    - Use DSU to maintain connectivity for Alice and Bob separately.
    - Priority: Keep as many Type 3 edges as possible since both can use them.
    - Then, add Type 1 edges for Alice and Type 2 edges for Bob.
    - If either Alice or Bob's DSU ends up with more than one component,
      return -1 (impossible).
    - Answer = total_edges - used_edges.

--------------------------------------------------------------------------------
Approach (DSU):
    1. Initialize two DSUs: one for Alice, one for Bob.
    2. First process all Type 3 edges:
         - Try to union in both DSUs.
         - If new edge connects, count it as used.
    3. Process Type 1 edges (only Alice’s DSU).
    4. Process Type 2 edges (only Bob’s DSU).
    5. If both DSUs have exactly 1 component → return removable edges.
       Otherwise, return -1.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let n = number of nodes, m = number of edges.

    Time Complexity:  O(m * α(n))
        - Each DSU operation is nearly O(1).
    Space Complexity: O(n)
        - Parent + Rank arrays for DSU.
================================================================================
*/

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    int components;

public:
    // Constructor
    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        components = n;
        for (int i = 1; i <= n; i++) {
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
    bool unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);
        if (px == py) return false;

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

        components--;
        return true;
    }

    int getCompo()
    {
        return components;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges)
    {
        // Create DSUs for Alice and Bob
        DSU alice(n), bob(n);

        int used_edges = 0;

        // Step 1: Process type 3 edges (shared)
        for (auto& e : edges) {
            if (e[0] == 3) {
                bool a = alice.unite(e[1], e[2]);
                bool b = bob.unite(e[1], e[2]);
                if (a || b) used_edges++;
            }
        }

        // Step 2: Process type 1 edges (Alice only)
        for (auto& e : edges) {
            if (e[0] == 1) {
                if (alice.unite(e[1], e[2])) used_edges++;
            }
        }

        // Step 3: Process type 2 edges (Bob only)
        for (auto& e : edges) {
            if (e[0] == 2) {
                if (bob.unite(e[1], e[2])) used_edges++;
            }
        }

        // Step 4: Check if both Alice and Bob are fully connected
        if (alice.getCompo() != 1 || bob.getCompo() != 1) return -1;

        // Removable edges = total - used
        return edges.size() - used_edges;
    }
};


/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    n = 4
    edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]

Output:
    2

Explanation:
    - Keep edges [3,1,2], [3,2,3], [1,2,4], [2,3,4].
    - Remove [1,1,3], [1,1,2].
    - Both Alice and Bob can still traverse entire graph.
================================================================================
*/
