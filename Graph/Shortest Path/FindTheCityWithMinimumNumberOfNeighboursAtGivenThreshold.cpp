#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance
// (Leetcode 1334)
//
// Task:
// Given n cities numbered from 0 to n-1, edges[] where edges[i] = [u,v,w]
// represents a bidirectional road of length w, and a distanceThreshold.
// Return the city with the smallest number of neighbors reachable within
// distanceThreshold. If multiple cities have the same count, return the
// city with the greatest index.
//
// Approach (Floyd-Warshall):
// 1. Build distance matrix and initialize with edge weights.
// 2. Run Floyd-Warshall to compute shortest paths between all pairs.
// 3. For each city, count how many cities are reachable within threshold.
// 4. Track the city with minimum reachable count (if tie, choose larger index).
//
// Complexity:
// - Time: O(V^3), where V = number of cities
// - Space: O(V^2) for distance matrix
//==============================================================================

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold)
    {
        // Step 1: Initialize distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }
        for (int i = 0; i < n; i++) dist[i][i] = 0;

        // Step 2: Floyd-Warshall to compute all-pairs shortest paths
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // Step 3: Count reachable cities within distanceThreshold
        int minCount = INT_MAX;
        int cityIndex = -1;

        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (dist[i][j] <= distanceThreshold) {
                    count++;
                }
            }
            // Step 4: Choose city with smallest count (if tie, larger index)
            if (count <= minCount) {
                minCount = count;
                cityIndex = i;
            }
        }

        return cityIndex;
    }
};

//==============================================================================
// Example Usage:
//
// int main() {
//     Solution sol;
//     int n = 4;
//     vector<vector<int>> edges = {
//         {0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}
//     };
//     int threshold = 4;
//
//     cout << sol.findTheCity(n, edges, threshold) << endl;
//     // Expected Output: 3
// }
//==============================================================================
