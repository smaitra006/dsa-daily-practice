#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// Problem: Shortest Path with Alternating Colors
// Link: https://leetcode.com/problems/shortest-path-with-alternating-colors/
//
// Approach:
// - Build adjacency list with colored edges: (neighbor, color).
//   (Let red = 1, blue = 0)
// - BFS from node 0, but keep track of (node, color) state.
//   Because alternating paths require the next edge color != last edge color.
// - Maintain distances separately for paths ending with red and blue.
// - Answer for each node is the minimum of the two distances.
//
// Complexity: O(N + E) time, O(N + E) space
// ============================================================================

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges)
    {
        vector<vector<pair<int, int>>> adj(n);

        // Build graph with colored edges
        for (auto& e : redEdges) adj[e[0]].push_back({ e[1], 1 }); // red = 1
        for (auto& e : blueEdges) adj[e[0]].push_back({ e[1], 0 }); // blue = 0

        // Distance arrays: dist[node][color]
        vector<vector<int>> dist(n, vector<int>(2, -1));
        queue<pair<int, int>> q;

        // Start from node 0, with both "red" and "blue" as valid next steps
        q.push({ 0, 0 });
        q.push({ 0, 1 });
        dist[0][0] = dist[0][1] = 0;

        while (!q.empty()) {
            auto [node, color] = q.front();
            q.pop();

            for (auto [nei, neiColor] : adj[node]) {
                if (neiColor != color && dist[nei][neiColor] == -1) {
                    dist[nei][neiColor] = dist[node][color] + 1;
                    q.push({ nei, neiColor });
                }
            }
        }

        // Final result: min distance of red/blue paths for each node
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            if (dist[i][0] == -1 && dist[i][1] == -1) result[i] = -1;
            else if (dist[i][0] == -1) result[i] = dist[i][1];
            else if (dist[i][1] == -1) result[i] = dist[i][0];
            else result[i] = min(dist[i][0], dist[i][1]);
        }

        return result;
    }
};
