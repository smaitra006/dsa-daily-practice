#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Surrounded Regions (LeetCode 130)
================================================================================
Task:
    Given an m x n matrix `board` containing 'X' and 'O':
    - Capture all regions that are surrounded by 'X'.
    - A region is captured by flipping all 'O's into 'X's in that surrounded region.

    An 'O' region is **not captured** if it is connected to the boundary.

--------------------------------------------------------------------------------
Key Insight:
    - Any 'O' connected to the border cannot be flipped.
    - Instead of directly finding surrounded regions, we:
        1. Traverse border cells and run DFS to mark all connected 'O's as safe.
        2. Safe 'O's are temporarily marked as 'T'.
        3. After DFS, flip:
            - Remaining 'O' → 'X' (surrounded ones)
            - 'T' → 'O' (safe ones)

--------------------------------------------------------------------------------
Approach (DFS):
    1. Scan all boundary cells:
        - If an 'O' is found, run DFS to mark it and all connected 'O's as safe ('T').
    2. Traverse the board:
        - Flip 'O' → 'X'
        - Flip 'T' → 'O'
    3. Return the modified board.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.
    - Time Complexity:  O(m * n)
        Each cell is visited at most once.
    - Space Complexity: O(m * n) in worst case (recursion stack).
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };

    // DFS to mark safe 'O's as 'T'
    void dfs(vector<vector<char>>& board, int sr, int sc)
    {
        board[sr][sc] = 'T';

        for (auto dir : directions) {
            int nr = sr + dir.first;
            int nc = sc + dir.second;

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'O') {
                dfs(board, nr, nc);
            }
        }
    }

    void solve(vector<vector<char>>& board)
    {
        m = board.size();
        n = board[0].size();

        // Step 1: Mark border-connected 'O's as 'T'
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') dfs(board, i, 0);
            if (board[i][n - 1] == 'O') dfs(board, i, n - 1);
        }
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') dfs(board, 0, j);
            if (board[m - 1][j] == 'O') dfs(board, m - 1, j);
        }

        // Step 2: Flip remaining 'O' → 'X', and 'T' → 'O'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == 'T') board[i][j] = 'O';
            }
        }
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    board = [["X","X","X","X"],
             ["X","O","O","X"],
             ["X","X","O","X"],
             ["X","O","X","X"]]

Output:
    [["X","X","X","X"],
     ["X","X","X","X"],
     ["X","X","X","X"],
     ["X","O","X","X"]]

Explanation:
    - The 'O' at (3,1) is connected to the border, so it remains 'O'.
    - All other 'O's are surrounded and flipped to 'X'.
================================================================================
*/
