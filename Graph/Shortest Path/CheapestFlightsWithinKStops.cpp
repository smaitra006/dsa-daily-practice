#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Cheapest Flights Within K Stops (LeetCode 787)
//
// Task:
// Given n cities numbered from 0 to n-1 and a list of flights where each
// flight [u, v, w] represents a flight from u → v with cost w, find the
// cheapest price from src to dst with at most k stops. Return -1 if no such
// route exists.
//
// Approach (Modified Dijkstra with Stops Tracking):
// - Build adjacency list: adj[u] = {v, cost}.
// - Use a min-heap priority_queue storing {totalCost, currentNode, stopsUsed}.
// - For each popped node, skip if stopsUsed > k.
// - Relax edges: update dist[v][stops+1] if new cost is smaller, and push to heap.
// - Return the cost when dst is reached. If heap empties without reaching dst, return -1.
//
// Complexity:
// - Time: O(E * log(V*(k+1))) → each node with each stop level can be pushed into heap
// - Space: O(V * (k+2)) for distance table + adjacency list
//==============================================================================

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
    {
        // Build adjacency list: adj[u] = {v, cost}
        vector<vector<pair<int, int>>> adj(n);
        for (auto& x : flights) {
            adj[x[0]].push_back({ x[1], x[2] });
        }

        // Distance table: dist[v][stops] = minimum cost to reach v using `stops` stops
        vector<vector<int>> dist(n, vector<int>(k + 2, INT_MAX));
        dist[src][0] = 0;

        // Min-heap: {totalCost, node, stopsUsed}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.push({ 0, src, 0 });

        while (!pq.empty()) {
            auto [cost, u, stops] = pq.top();
            pq.pop();

            // Reached destination
            if (u == dst) return cost;

            // Exceeded allowed stops
            if (stops > k) continue;

            // Explore neighbors
            for (auto& [v, price] : adj[u]) {
                int newCost = cost + price;
                if (newCost < dist[v][stops + 1]) {
                    dist[v][stops + 1] = newCost;
                    pq.push({ newCost, v, stops + 1 });
                }
            }
        }

        return -1; // No valid route within k stops
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
//     int n = 3, src = 0, dst = 2, k = 1;
//
//     cout << sol.findCheapestPrice(n, flights, src, dst, k) << endl;
//     // Expected Output: 200
//
// Explanation:
// Route: 0 -> 1 -> 2, total cost = 100 + 100 = 200, stops = 1 ≤ k
//==============================================================================
