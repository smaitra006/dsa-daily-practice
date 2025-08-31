#include <bits/stdc++.h>
using namespace std;

//==============================================================================
// Problem: Word Search (LeetCode 79)
//
// Task:
// Given a 2D board and a word, determine if the word exists in the grid.
// The word can be constructed from letters of sequentially adjacent cells,
// where "adjacent" cells are horizontally or vertically neighboring.
// The same letter cell may not be used more than once.
//
// Example:
//   Input:  board = [["A","B","C","E"],
//                     ["S","F","C","S"],
//                     ["A","D","E","E"]], word = "ABCCED"
//   Output: true
//
//   Input:  board = [["A","B","C","E"],
//                     ["S","F","C","S"],
//                     ["A","D","E","E"]], word = "SEE"
//   Output: true
//
// Approach (DFS + Backtracking):
// 1. Iterate over each cell of the board.
// 2. If the cell matches the first character of word, start DFS from that cell.
// 3. In DFS:
//      - Mark cell as visited.
//      - Explore all 4 directions (up, down, left, right) recursively.
//      - If path leads to complete word → return true.
//      - Backtrack by unmarking visited cell.
// 4. If any DFS path succeeds → return true, else false.
//==============================================================================

class Solution {
public:
    vector<pair<int, int>> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int m, n;

    bool dfs(vector<vector<char>>& board, int r, int c, string word, int idx, vector<vector<bool>>& visited)
    {
        if (idx == word.size()) return true;

        visited[r][c] = true;
        int target = word[idx];

        for (auto dir : directions) {
            int nr = r + dir.first;
            int nc = c + dir.second;

            if (nr >= 0 && nr < m && nc >= 0 && nc < n
                && board[nr][nc] == target && !visited[nr][nc]) {
                if (dfs(board, nr, nc, word, idx + 1, visited)) return true;
            }
        }

        visited[r][c] = false; // backtrack
        return false;
    }

    bool exist(vector<vector<char>>& board, string word)
    {
        m = board.size();
        n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0] && !visited[i][j]) {
                    if (dfs(board, i, j, word, 1, visited)) return true;
                }
            }
        }

        return false;
    }
};

//==============================================================================
// Complexity Analysis:
// - Time: O(M * N * 4^L), M*N = board size, L = word length (DFS explores 4 directions for each letter).
// - Space: O(M * N + L), for visited array and recursion stack.
//
// Example Walkthrough:
// Input: word = "ABCCED"
// Start at (0,0) 'A' → DFS explores path "A->B->C->C->E->D" → found → return true
//==============================================================================
