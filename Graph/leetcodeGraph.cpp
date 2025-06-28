// LeetCode questions on Graph
#include <bits/stdc++.h>
using namespace std;

/* ================================================================
 * PROBLEM 1: NUMBER OF PROVINCES (LeetCode 547)
 * ================================================================ */

/**
 * @brief Count the number of provinces (connected components) in a graph
 *
 * PROBLEM STATEMENT:
 * Given an `n x n` matrix `isConnected` representing an undirected graph
 * where `isConnected[i][j] == 1` means city `i` and city `j` are directly connected,
 * return the total number of provinces (groups of directly or indirectly connected cities).
 *
 * EXAMPLE:
 * Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
 * Output: 2
 *
 * APPROACH:
 * - Treat each city as a node in an undirected graph.
 * - A province is a connected component.
 * - Use DFS to explore all nodes in a component.
 * - Maintain a visited[] array to avoid revisiting nodes.
 * - For each unvisited node, start a DFS and count one province.
 *
 * @param isConnected 2D adjacency matrix representing connections
 * @return int Number of provinces (connected components)
 *
 * @complexity
 * Time: O(n^2) - Each cell in matrix may be visited once
 * Space: O(n)  - Visited array + recursion stack
 */

 class Solution {
    public:
        // DFS traversal to visit all cities in a province
        void dfs(vector<vector<int>>& isConnected, vector<bool>& visited, int node) {
            visited[node] = true;

            for (int neighbor = 0; neighbor < isConnected.size(); neighbor++) {
                if (isConnected[node][neighbor] == 1 && !visited[neighbor]) {
                    dfs(isConnected, visited, neighbor);
                }
            }
        }

        // Count number of connected components (provinces)
        int findCircleNum(vector<vector<int>>& isConnected) {
            int n = isConnected.size();
            vector<bool> visited(n, false);
            int provinces = 0;

            for (int node = 0; node < n; node++) {
                if (!visited[node]) {
                    dfs(isConnected, visited, node);
                    provinces++;
                }
            }

            return provinces;
        }
    };
