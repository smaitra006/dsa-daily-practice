#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * LEETCODE 1926: NEAREST EXIT FROM ENTRANCE IN MAZE
 * =================================================================== */

 /**
  * @brief Find the minimum number of steps to reach the nearest exit from the entrance
  *
  * PROBLEM STATEMENT:
  * You are given a `m x n` maze represented by a 2D grid of characters:
  * - '.' = open cell
  * - '+' = wall
  *
  * Also given is the `entrance` coordinate in the maze.
  * An **exit** is any cell on the boundary of the maze that is an open cell ('.') and **not** the entrance.
  *
  * Return the **minimum number of steps** required to reach the nearest exit.
  * If there is no possible exit, return -1.
  *
  * Input:
  * - vector<vector<char>> maze: 2D maze grid
  * - vector<int> entrance: starting position {row, col}
  *
  * Output:
  * - Integer: Minimum steps to nearest exit, or -1 if unreachable
  *
  * EXAMPLE:
  * Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
  * Output: 1
  *
  * ALGORITHM (BFS - Shortest Path in Unweighted Grid):
  * - Use BFS to explore all possible paths
  * - Track visited cells to avoid cycles
  * - First time we reach an exit cell, return the number of steps
  *
  * COMPLEXITY:
  * - Time: O(M * N) where M = rows, N = cols
  * - Space: O(M * N) for visited tracking
  */

class Solution
{
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance)
    {
        int m = maze.size();
        int n = maze[0].size();

        // Queue for BFS: {row, col}
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 4 directions: down, right, up, left
        vector<pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

        int er = entrance[0];
        int ec = entrance[1];

        visited[er][ec] = true;
        q.push({ er, ec });

        int step = 0; // Number of steps from entrance

        while (!q.empty()) {
            int size = q.size();

            while (size--) {
                auto [r, c] = q.front();
                q.pop();

                // If current cell is on boundary and not the entrance, return step
                if ((r == 0 || r == m - 1 || c == 0 || c == n - 1) && (r != er || c != ec)) {
                    return step;
                }

                // Explore 4 directions
                for (auto [dr, dc] : directions) {
                    int nr = r + dr;
                    int nc = c + dc;

                    // If next cell is valid and not visited and is open
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                        maze[nr][nc] == '.' && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({ nr, nc });
                    }
                }
            }

            step++; // Move to next level
        }

        return -1; // No exit found
    }
};
