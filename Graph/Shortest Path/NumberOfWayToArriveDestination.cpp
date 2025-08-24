#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Number of Ways to Arrive at Destination (LeetCode 1976)
//
// Task:
// Given n cities (0 to n-1) and an array `roads` where each road is
// [u, v, time], representing a bidirectional road between u and v with travel
// time `time`, return the number of different ways to arrive at city n-1 from
// city 0 in the shortest time. Since the number can be large, return it modulo 1e9+7.
//
// Approach (Modified Dijkstra to Count Paths):
// - Use a min-heap priority_queue to always process the node with current
//   shortest distance.
// - Maintain two arrays:
//      1. dist[i] = shortest distance from 0 to i
//      2. count[i] = number of shortest paths to reach i
// - For each neighbor v of current node:
//      - If new distance < dist[v], update dist[v] and set count[v] = count[curr].
//      - Else if new distance == dist[v], increment count[v] by count[curr] modulo MOD.
//
// Complexity:
// - Time: O(E * log V) → standard Dijkstra on a graph with V nodes and E edges
// - Space: O(V + E) for adjacency list + arrays
//==============================================================================

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads)
    {
        const long long MOD = 1e9 + 7;

        // Min-heap: {current_time, node}
        priority_queue<pair<long long, long long>,
            vector<pair<long long, long long>>,
            greater<pair<long long, long long>>> pq;

        // Build adjacency list: adj[u] = {time, v}
        vector<vector<pair<long long, long long>>> adj(n);
        for (auto& it : roads) {
            long long u = it[0];
            long long v = it[1];
            long long time = it[2];
            adj[u].push_back({ time, v });
            adj[v].push_back({ time, u });
        }

        // Distance and path count arrays
        vector<long long> dist(n, LLONG_MAX);
        vector<long long> count(n, 0);
        dist[0] = 0;
        count[0] = 1;

        pq.push({ 0, 0 });

        while (!pq.empty()) {
            auto [curr_time, curr] = pq.top();
            pq.pop();

            if (curr_time > dist[curr]) continue;

            for (auto& [time, v] : adj[curr]) {
                long long newDist = curr_time + time;

                // Found shorter path to v
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    count[v] = count[curr];
                    pq.push({ newDist, v });
                }
                // Found another shortest path to v
                else if (newDist == dist[v]) {
                    count[v] = (count[v] + count[curr]) % MOD;
                }
            }
        }

        return count[n - 1] % MOD;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     vector<vector<int>> roads = {{0,1,1},{0,2,1},{1,2,1},{1,3,1},{2,3,1}};
//     int n = 4;
//
//     cout << sol.countPaths(n, roads) << endl;
//     // Expected Output: 2
//
// Explanation:
// Two shortest paths from 0 → 3: 0→1→3 and 0→2→3
//==============================================================================
