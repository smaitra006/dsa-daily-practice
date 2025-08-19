#include <bits./stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 1020: NUMBER OF ENCLAVES (LeetCode) MULTI-SOURCE DFS
 * =================================================================== */

 /**
  * @brief Count land cells (1s) that cannot reach the boundary
  *
  * PROBLEM STATEMENT:
  * You are given an `m x n` binary matrix `grid`, where `0` represents sea and `1` represents land.
  * A land cell is considered **enclave** if it cannot reach any boundary of the matrix.
  * Return the number of enclave cells.
  *
  * EXAMPLE:
  * Input:
  *   grid = [[0,0,0,0],
  *           [1,0,1,0],
  *           [0,1,1,0],
  *           [0,0,0,0]]
  * Output: 3
  *
  * APPROACH:
  * - Perform DFS from boundary land cells (1s) to mark them as visited.
  * - Remaining unvisited 1s inside are enclave cells.
  *
  * @complexity
  * Time: O(m * n)
  * Space: O(m * n) for visited + recursion stack
  */

class Solution
{
public:
    void dfs(vector<vector<int>>& grid, int sr, int sc, vector<vector<bool>>& visited)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (sr < 0 || sr >= m || sc < 0 || sc >= n || visited[sr][sc] || grid[sr][sc] == 0)
            return;

        visited[sr][sc] = true;

        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        for (auto dir : directions) {
            int new_sr = sr + dir.first;
            int new_sc = sc + dir.second;
            dfs(grid, new_sr, new_sc, visited);
        }
    }

    int numEnclaves(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Step 1: Run DFS for all boundary cells having 1
        // Top and Bottom row
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1 && !visited[0][j]) {
                dfs(grid, 0, j, visited);
            }
            if (grid[m - 1][j] == 1 && !visited[m - 1][j]) {
                dfs(grid, m - 1, j, visited);
            }
        }

        // Left and Right column
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1 && !visited[i][0]) {
                dfs(grid, i, 0, visited);
            }
            if (grid[i][n - 1] == 1 && !visited[i][n - 1]) {
                dfs(grid, i, n - 1, visited);
            }
        }

        // Step 2: Count the unvisited land cells (enclaves)
        int result = 0;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    result++;
                }
            }
        }

        return result;
    }
};

/* ===================================================================
 * PROBLEM 1020: NUMBER OF ENCLAVES (LeetCode) MULTI-SOURCE BFS
 * =================================================================== */

 /**
  * @brief Count number of land cells that cannot reach the boundary using BFS
  *
  * PROBLEM STATEMENT:
  * You are given an `m x n` binary matrix `grid`, where:
  * - `0` represents sea, and
  * - `1` represents land.
  *
  * A land cell is an **enclave** if it cannot reach any boundary cell
  * (any cell on the edge of the grid) by moving 4-directionally through land.
  * Return the total count of enclave land cells.
  *
  * APPROACH:
  * - Use **Multi-source BFS** starting from all boundary land cells (1s).
  * - Mark all reachable land cells as visited.
  * - Count the remaining unvisited land cells as enclaves.
  *
  * @complexity
  * Time: O(m * n)
  * Space: O(m * n) for visited and queue
  */

class Solution
{
public:
    int numEnclaves(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;

        // Step 1: Add all boundary land cells to the queue
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1 && !visited[0][j]) {
                q.push({ 0, j });
                visited[0][j] = true;
            }
            if (grid[m - 1][j] == 1 && !visited[m - 1][j]) {
                q.push({ m - 1, j });
                visited[m - 1][j] = true;
            }
        }

        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1 && !visited[i][0]) {
                q.push({ i, 0 });
                visited[i][0] = true;
            }
            if (grid[i][n - 1] == 1 && !visited[i][n - 1]) {
                q.push({ i, n - 1 });
                visited[i][n - 1] = true;
            }
        }

        // Step 2: BFS traversal to mark reachable land cells
        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;

            for (auto dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    grid[nr][nc] == 1 && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({ nr, nc });
                }
            }
        }

        // Step 3: Count unvisited land cells as enclaves
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                }
            }
        }

        return count;
    }
};

