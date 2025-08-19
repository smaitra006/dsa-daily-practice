#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 841: KEYS AND ROOMS
 * =================================================================== */

 /**
  * @brief Determine if all rooms can be visited starting from room 0
  *
  * PROBLEM STATEMENT:
  * There are `n` rooms labeled from 0 to n - 1. Each room contains a list of keys to other rooms.
  * Initially, you are in room 0 and can enter it freely. You can use any key found in a room to enter other rooms.
  *
  * Return `true` if you can visit **all rooms**, otherwise return `false`.
  *
  * Input:
  * - vector<vector<int>> rooms: rooms[i] contains a list of keys to other rooms
  *
  * Output:
  * - Boolean: true if all rooms can be visited, false otherwise
  *
  * EXAMPLE:
  * Input: rooms = [[1], [2], [3], []]
  * Output: true
  * Explanation: Room 0 -> 1 -> 2 -> 3
  *
  * ALGORITHM (DFS Traversal):
  * - Treat rooms as nodes and keys as edges
  * - Perform DFS starting from room 0
  * - Track visited rooms
  * - If all rooms are visited after DFS, return true
  *
  * COMPLEXITY:
  * - Time: O(N + E) where N = number of rooms, E = total number of keys
  * - Space: O(N) for visited array and call stack
  */

class Solution
{
public:
    /**
     * @brief DFS to explore all rooms accessible from current room
     */
    void dfs(vector<vector<int>>& adj, int node, vector<bool>& visited)
    {
        visited[node] = true;

        for (auto neighbour : adj[node]) {
            if (!visited[neighbour]) {
                dfs(adj, neighbour, visited);
            }
        }
    }

    /**
     * @brief Main function to check if all rooms can be visited
     */
    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        int n = rooms.size();

        // Construct adjacency list (rooms -> graph)
        vector<vector<int>> adj(n);
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {
            for (auto key : rooms[i]) {
                adj[i].push_back(key);
            }
        }

        // Perform DFS from room 0
        dfs(adj, 0, visited);

        // Check if all rooms were visited
        for (int i = 0; i < n; i++) {
            if (!visited[i])
                return false;
        }

        return true;
    }
};
