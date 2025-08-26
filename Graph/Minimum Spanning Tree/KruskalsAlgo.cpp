#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * TOPIC: KRUSKAL'S ALGORITHM (Minimum Spanning Tree - MST)
 * =================================================================== */

 /**
  * @brief Find the Minimum Spanning Tree (MST) of a connected, undirected,
  *        and weighted graph using Kruskal's algorithm.
  *
  * PROBLEM STATEMENT:
  * Given a graph with `V` nodes and `E` weighted edges,
  * find a subset of edges that connects all vertices (spanning tree),
  * and the sum of edge weights is minimized.
  *
  * Kruskal's algorithm is **greedy**, always picking the minimum weight edge
  * that does **not** form a cycle (using Union-Find to detect cycles).
  *
  * INPUT:
  * - Integer `n`: Number of nodes (0-indexed or 1-indexed)
  * - vector<vector<int>> edges: List of edges {u, v, weight}
  *
  * OUTPUT:
  * - Integer: Total weight of the Minimum Spanning Tree
  *
  * ALGORITHM:
  * 1. Sort all edges in ascending order of weights
  * 2. Initialize Disjoint Set Union (Union-Find) for cycle detection
  * 3. Traverse sorted edges:
  *    - If the edge connects two different components, add it to MST
  *    - Merge the two components using union operation
  * 4. Stop when MST contains (V - 1) edges
  *
  * COMPLEXITY:
  * - Time: O(E * log E) for sorting + union-find operations
  * - Space: O(V) for DSU data structures
  */

class DSU
{
public:
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int node)
    {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    // Union by rank
    bool unionSets(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return false;

        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        }
        else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        }
        else {
            parent[pu] = pv;
            rank[pv]++;
        }

        return true;
    }
};

class Solution
{
public:
    /**
     * @brief Kruskal's algorithm implementation
     * @param n: number of nodes
     * @param edges: list of {u, v, weight}
     * @return total weight of MST
     */
    int kruskalMST(int n, vector<vector<int>>& edges)
    {
        // Step 1: Sort edges by weight
        sort(edges.begin(), edges.end(), [](auto& a, auto& b)
            { return a[2] < b[2]; });

        DSU dsu(n);
        int mstWeight = 0;
        int edgesUsed = 0;

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            // If u and v are in different components
            if (dsu.unionSets(u, v)) {
                mstWeight += wt;
                edgesUsed++;
                if (edgesUsed == n - 1)
                    break;
            }
        }

        return mstWeight;
    }
};
