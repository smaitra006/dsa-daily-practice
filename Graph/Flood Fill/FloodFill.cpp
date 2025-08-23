#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
Problem: Flood Fill (LeetCode 733)
================================================================================
Task:
    An image is represented by an m x n integer grid, where image[i][j]
    represents the pixel value of the image.

    You are given three integers sr, sc, and color. Perform a "flood fill"
    starting from pixel (sr, sc):
        - Replace the color of pixel (sr, sc) and all 4-directionally connected
          pixels having the same initial color with the new given color.

    Return the modified image after performing the flood fill.

--------------------------------------------------------------------------------
Key Insight:
    - Use DFS (or BFS) to explore all connected pixels with the same initial color.
    - Ensure boundaries are respected and already-colored pixels are skipped.
    - Avoid infinite recursion by marking cells as we recolor them.

--------------------------------------------------------------------------------
Approach (DFS):
    1. Record the original color at (sr, sc).
    2. If it's already the new color, return the image directly.
    3. Perform DFS from (sr, sc), recoloring connected pixels with the new color.
    4. Explore 4 directions recursively.
    5. Return the modified image.

--------------------------------------------------------------------------------
Complexity Analysis:
    Let m = rows, n = columns.
    - Time Complexity:  O(m * n)
        Each pixel is visited at most once.
    - Space Complexity: O(m * n) (worst-case recursion stack depth).
================================================================================
*/

class Solution {
public:
    int m, n;
    vector<pair<int,int>> directions = {{1,0}, {0,1}, {-1,0}, {0,-1}};

    // DFS helper function
    void dfs(vector<vector<int>>& image, int sr, int sc, int initial_color, int color) {
        image[sr][sc] = color;  // Recolor current pixel

        for (auto dir : directions) {
            int nr = sr + dir.first;
            int nc = sc + dir.second;

            // Check boundaries and whether the neighbor has the same initial color
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && image[nr][nc] == initial_color) {
                dfs(image, nr, nc, initial_color, color);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        m = image.size();
        n = image[0].size();
        int initial_color = image[sr][sc];

        // If the starting pixel already has the target color → no change
        if (initial_color == color) return image;

        dfs(image, sr, sc, initial_color, color);
        return image;
    }
};

/*
================================================================================
Example Usage:
--------------------------------------------------------------------------------
Input:
    image = [[1,1,1],[1,1,0],[1,0,1]]
    sr = 1, sc = 1, color = 2

Output:
    [[2,2,2],[2,2,0],[2,0,1]]

Explanation:
    The region connected to (1,1) with color 1 is filled with 2.
================================================================================
*/

