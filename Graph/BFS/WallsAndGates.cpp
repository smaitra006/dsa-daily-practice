#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Walls and Gates (LeetCode 286)
================================================================================
Task:
    You are given an m x n grid `rooms`:
        - -1 represents a wall or obstacle
        -  0 represents a gate
        -  INF (2^31 - 1) represents an empty room

    Fill each empty room with the distance to its nearest gate.
    If a gate is unreachable, leave the value as INF.

--------------------------------------------------------------------------------
Approach (Multi-Source BFS):
    1. Treat all gates (cells with value 0) as BFS sources and enqueue them.
    2. Perform BFS level by level:
        - For each cell, explore its 4 neighbors.
        - If a neighbor is an empty room (INF), update its distance as
          current distance + 1 and enqueue it.
    3. Continue until BFS finishes.

    Why BFS?
        - BFS ensures shortest distance to the nearest gate because we expand
          outward in layers from all gates simultaneously.

--------------------------------------------------------------------------------
Complexity Analysis:
    Time Complexity:  O(M * N)
        - Each cell is visited at most once.
    Space Complexity: O(M * N)
        - Queue may hold all cells in the worst case.
================================================================================
*/

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms)
    {
        int m = rooms.size();
        if (m == 0) return;
        int n = rooms[0].size();

        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = { {1,0}, {-1,0}, {0,1}, {0,-1} };

        // Step 1: Push all gates into the queue as BFS sources
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    q.push({ i, j });
                }
            }
        }

        // Step 2: BFS from all gates
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (auto [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                // If neighbor is within bounds and is an empty room (INF)
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && rooms[nr][nc] == INT_MAX) {
                    rooms[nr][nc] = rooms[r][c] + 1; // Update distance
                    q.push({ nr, nc });
                }
            }
        }
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    rooms = [
        [INF, -1,  0, INF],
        [INF, INF, INF, -1],
        [INF, -1, INF, -1],
        [  0, -1, INF, INF]
    ]

Output:
    [
        [ 3, -1,  0,  1],
        [ 2,  2,  1, -1],
        [ 1, -1,  2, -1],
        [ 0, -1,  3,  4]
    ]

Explanation:
    Distances are filled to the nearest gate (0).

--------------------------------------------------------------------------------
Notes:
    - If no gate is present, all INF values remain unchanged.
    - BFS ensures shortest distance is assigned without extra checks.
================================================================================
*/

