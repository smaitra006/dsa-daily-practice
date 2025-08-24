#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Network Delay Time (LeetCode 743)
//
// Task:
// A network of n nodes is represented by a list of travel times along directed
// edges. Each edge times[i] = {u, v, w} represents a directed edge from u → v
// with weight w (time).
// A signal starts from node k. We need to determine the time it takes for all
// nodes to receive the signal. If not all nodes can be reached, return -1.
//
// Approach (Dijkstra’s Algorithm with Min-Heap):
// - Build adjacency list: adj[u] = {time, v}
// - Use a min-heap (priority_queue with greater) to always process the node
//   with the smallest current delay.
// - Relax edges: if a shorter time to reach v is found, update delay[v] and
//   push into heap.
// - Final answer is the maximum delay among all nodes. If any node remains
//   unreachable, return -1.
//
// Complexity:
// - Time: O((V + E) log V) → due to priority queue operations
// - Space: O(V + E) for adjacency list and distance array
//==============================================================================

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        // Min-heap {time, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Build adjacency list: adj[u] = {time, v}
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& it : times) {
            int u = it[0];
            int v = it[1];
            int time = it[2];
            adj[u].push_back({ time, v });
        }

        // Distance (delay) array
        vector<int> delay(n + 1, INT_MAX);
        delay[k] = 0;

        pq.push({ 0, k });  // {time, node}

        while (!pq.empty()) {
            int curr_time = pq.top().first;
            int curr = pq.top().second;
            pq.pop();

            // Explore all neighbors
            for (auto& neighbour : adj[curr]) {
                int time = neighbour.first;
                int v = neighbour.second;

                // Relaxation step
                if (delay[curr] + time < delay[v]) {
                    delay[v] = delay[curr] + time;
                    pq.push({ delay[v], v });
                }
            }
        }

        // Find maximum delay (ignore index 0 since nodes are 1-indexed)
        int max_delay = *max_element(delay.begin() + 1, delay.end());
        return (max_delay == INT_MAX) ? -1 : max_delay;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     vector<vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
//     int n = 4, k = 2;
//
//     cout << sol.networkDelayTime(times, n, k) << endl;
//     // Expected Output: 2
// }
//
// Explanation:
// Node 2 → Node 1 : time = 1
// Node 2 → Node 3 : time = 1
// Node 3 → Node 4 : time = 1
// Longest among all = 2
//==============================================================================
