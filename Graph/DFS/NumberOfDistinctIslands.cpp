#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Number of Distinct Islands (LeetCode 694)
================================================================================
Task:
    Given an m x n 2D binary grid, where:
        - 0 represents water
        - 1 represents land
    An island is a group of connected 1’s (land) connected 4-directionally.

    Two islands are considered **the same** if one can be translated (shifted) to
    equal the other (rotation/reflection not allowed).

    Return the number of distinct islands.

--------------------------------------------------------------------------------
Key Insight:
    - We must compare island *shapes*, not absolute positions.
    - Translation invariance:
        - Capture the path/relative moves (DFS encoding) starting from each island.
        - The shape signature uniquely identifies the island.

--------------------------------------------------------------------------------
Approach (DFS Encoding):
    1. Traverse grid.
    2. When land cell (1) found, run DFS:
        - Record movement directions (e.g., "up", "down", etc.).
        - Append "backtrack" markers to differentiate paths.
    3. Store each island’s signature (string) in a set.
    4. Result = size of the set.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.
    - Time Complexity:  O(m * n)
        Each cell is visited once, DFS runs linear in number of land cells.
    - Space Complexity: O(m * n)
        For recursion stack + storing signatures.
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };
    vector<char> dirChar = { 'D', 'R', 'U', 'L' }; // direction encoding

    // DFS to generate unique island shape signature
    void dfs(vector<vector<int>>& grid, int sr, int sc, string& path, char move)
    {
        // mark visited
        grid[sr][sc] = 0;
        path.push_back(move);

        for (int d = 0; d < 4; d++) {
            int nr = sr + directions[d].first;
            int nc = sc + directions[d].second;

            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                dfs(grid, nr, nc, path, dirChar[d]);
            }
        }

        // mark end of path (backtracking)
        path.push_back('B');
    }

    int numDistinctIslands(vector<vector<int>>& grid)
    {
        m = grid.size();
        n = grid[0].size();
        set<string> shapes;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    string path;
                    dfs(grid, i, j, path, 'S'); // S = start marker
                    shapes.insert(path);
                }
            }
        }

        return (int)shapes.size();
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    grid = [[1,1,0,0,0],
            [1,1,0,0,0],
            [0,0,0,1,1],
            [0,0,0,1,1]]

Output:
    1

Explanation:
    - There are 2 islands.
    - Both islands have identical shape, so only 1 distinct island.
================================================================================
*/

