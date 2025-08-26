#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM: MINIMUM SPANNING TREE (MST) USING PRIM'S ALGORITHM
 * =================================================================== */

 /**
  * @brief Find the minimum cost to connect all nodes in an undirected, weighted graph
  *
  * PROBLEM STATEMENT:
  * Given an undirected graph with `n` nodes (0 to n-1) and weighted edges,
  * find the weight of the **Minimum Spanning Tree (MST)**.
  *
  * Input:
  * - Number of nodes `n`
  * - Adjacency list `adj[]` where:
  *   adj[u] = vector of pairs {v, wt} representing an edge u — v with weight wt
  *
  * Output:
  * - Integer `minCost` representing the total weight of the MST
  *
  * ALGORITHM (Prim's using Min-Heap):
  * - Start from any node (usually node 0)
  * - Use a priority queue to always pick the minimum weight edge
  * - Maintain a visited array to avoid cycles
  * - Add the edge to MST if it connects a new node
  *
  * COMPLEXITY:
  * - Time: O(E * log V) using Min-Heap
  * - Space: O(V + E)
  */

int primsMST(int n, vector<vector<pair<int, int>>>& adj)
{
    // Min-heap: {weight, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<bool> inMST(n, false); // To mark included nodes
    int minCost = 0;

    // Start from node 0
    pq.push({ 0, 0 });

    while (!pq.empty()) {
        auto [wt, u] = pq.top();
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;
        minCost += wt;

        // Traverse neighbors
        for (auto [v, w] : adj[u]) {
            if (!inMST[v]) {
                pq.push({ w, v });
            }
        }
    }

    return minCost;
}
