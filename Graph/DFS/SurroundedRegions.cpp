#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 130: SURROUNDED REGIONS (LeetCode)
 * =================================================================== */

 /**
  * @brief Capture all regions surrounded by 'X'
  *
  * PROBLEM STATEMENT:
  * Given an `m x n` board containing 'X' and 'O', capture all regions that are
  * 4-directionally surrounded by 'X'. Flip all surrounded 'O' into 'X'.
  *
  * Any 'O' connected to a boundary 'O' should **not** be flipped.
  *
  * EXAMPLE:
  * Input:
  *   board = [["X","X","X","X"],
  *            ["X","O","O","X"],
  *            ["X","X","O","X"],
  *            ["X","O","X","X"]]
  * Output:
  *   [["X","X","X","X"],
  *    ["X","X","X","X"],
  *    ["X","X","X","X"],
  *    ["X","O","X","X"]]
  *
  * APPROACH:
  * - Start DFS from all boundary 'O's to mark them as safe.
  * - Then flip all unvisited 'O's (surrounded) to 'X'.
  *
  * @complexity
  * Time: O(m * n)
  * Space: O(m * n) for visited array + recursion stack
  */

class Solution
{
public:
    void dfs(vector<vector<char>>& board, int sr, int sc, vector<vector<bool>>& visited)
    {
        int m = board.size();
        int n = board[0].size();

        // Out of bounds or already visited or not an 'O'
        if (sr < 0 || sr >= m || sc < 0 || sc >= n || visited[sr][sc] || board[sr][sc] == 'X')
            return;

        visited[sr][sc] = true;

        // Directions: up, down, left, right
        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        for (auto dir : directions) {
            int new_sr = sr + dir.first;
            int new_sc = sc + dir.second;
            dfs(board, new_sr, new_sc, visited);
        }
    }

    void solve(vector<vector<char>>& board)
    {
        int m = board.size();
        if (m == 0)
            return;
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 1. Start DFS from all boundary 'O's to mark safe regions

        // Top & Bottom row
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O' && !visited[0][j]) {
                dfs(board, 0, j, visited);
            }
            if (board[m - 1][j] == 'O' && !visited[m - 1][j]) {
                dfs(board, m - 1, j, visited);
            }
        }

        // Left & Right column
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O' && !visited[i][0]) {
                dfs(board, i, 0, visited);
            }
            if (board[i][n - 1] == 'O' && !visited[i][n - 1]) {
                dfs(board, i, n - 1, visited);
            }
        }

        // 2. Flip all unvisited 'O's to 'X'
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (board[i][j] == 'O' && !visited[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
