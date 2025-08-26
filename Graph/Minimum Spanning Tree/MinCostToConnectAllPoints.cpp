#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem    : Min Cost to Connect All Points
// Leetcode   : 1584
// Algorithm  : Minimum Spanning Tree (Prim's Algorithm)
// Time Comp. : O(N^2 log N)  → Building adjacency O(N^2), PQ operations O(E log V)
// Space Comp.: O(N^2) for adjacency list + O(N) for PQ/inMST
//==============================================================================

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points)
    {
        int n = points.size();

        //------------------------------------------------------------------------------
        // Step 1: Build adjacency list with Manhattan distances
        //------------------------------------------------------------------------------
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int d = abs(points[i][0] - points[j][0]) +
                    abs(points[i][1] - points[j][1]);
                adj[i].push_back({ d, j });
                adj[j].push_back({ d, i });
            }
        }

        //------------------------------------------------------------------------------
        // Step 2: Apply Prim’s Algorithm
        //------------------------------------------------------------------------------
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> inMST(n, false);

        int min_cost = 0;
        pq.push({ 0, 0 }); // {cost, starting node}

        while (!pq.empty()) {
            int cost = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if (inMST[v]) continue;   // already included in MST

            inMST[v] = true;
            min_cost += cost;

            for (auto& neighbour : adj[v]) {
                int c = neighbour.first;
                int node = neighbour.second;
                if (!inMST[node]) {
                    pq.push({ c, node });
                }
            }
        }

        return min_cost;
    }
};

//==============================================================================
// Example Usage:
// Input : points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation: The cost of connecting all points with min total distance = 20
//==============================================================================
