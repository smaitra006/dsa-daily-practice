#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 1091: SHORTEST PATH IN BINARY MATRIX (LeetCode)
 * =================================================================== */

 /**
  * @brief Find the shortest path from top-left to bottom-right in a binary matrix.
  *
  * PROBLEM:
  * - You are given an n x n binary matrix `grid` where 0 represents an empty cell
  *   and 1 represents an obstacle.
  * - Return the length of the shortest clear path from (0, 0) to (n-1, n-1) using 8 directions.
  * - Return -1 if no such path exists.
  *
  * APPROACH:
  * - Perform BFS starting from (0, 0).
  * - Track distance as you visit new cells.
  * - Use 8-directional movement.
  *
  * @complexity
  * Time: O(n^2)
  * Space: O(n^2)
  */

class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        int n = grid.size();

        // Check if start or end is blocked
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;

        vector<pair<int, int>> directions = {
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

        queue<pair<int, int>> q;
        q.push({ 0, 0 });
        grid[0][0] = 1; // Distance from start is 1

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            int dist = grid[x][y];

            if (x == n - 1 && y == n - 1)
                return dist; // Reached destination

            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 0) {
                    grid[nx][ny] = dist + 1;
                    q.push({ nx, ny });
                }
            }
        }

        return -1; // No path exists
    }
};

/**
 * @brief Solve the same problem using Dijkstra's Algorithm with a min-heap.
 *
 * NOTE: Although Dijkstra is generally used for weighted graphs, here we can
 * simulate it for uniform weights to demonstrate priority queue usage.
 *
 * @complexity
 * Time: O(n^2 * log n)
 * Space: O(n^2)
 */

class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;

        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        dist[0][0] = 1;

        vector<pair<int, int>> directions = {
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

        // Min-heap: {distance, {x, y}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        pq.push({ 1, {0, 0} });

        while (!pq.empty()) {
            auto [d, cell] = pq.top();
            pq.pop();
            int x = cell.first;
            int y = cell.second;

            if (x == n - 1 && y == n - 1)
                return d;

            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 0) {
                    if (d + 1 < dist[nx][ny]) {
                        dist[nx][ny] = d + 1;
                        pq.push({ dist[nx][ny], {nx, ny} });
                    }
                }
            }
        }

        return -1;
    }
};
