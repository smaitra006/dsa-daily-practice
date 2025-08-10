/* ==============================================================================
 * Problem: Reverse Submatrix Rows
 *
 * Task:
 * - Given a 2D matrix `grid`, and integers `(x, y, k)`:
 *     • `(x, y)` represents the top-left corner of a `k x k` submatrix.
 *     • Reverse the rows of this submatrix vertically (top row ↔ bottom row).
 * - Return the modified matrix.
 *
 * Approach:
 * 1. Loop through the first half of the rows in the submatrix.
 * 2. Swap each row with its corresponding row from the bottom.
 * 3. Repeat until all rows in the submatrix are reversed.
 *
 * Time Complexity  : O(k²) — Each element in the submatrix is visited once.
 * Space Complexity : O(1)  — In-place swaps, no extra storage.
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k)
    {
        // Reverse rows in the k x k submatrix
        for (int i = 0; i < k / 2; i++) {
            int top = x + i;               // Current top row index
            int bottom = x + k - 1 - i;    // Corresponding bottom row index

            // Swap entire rows column by column
            for (int col = 0; col < k; col++) {
                swap(grid[top][y + col], grid[bottom][y + col]);
            }
        }
        return grid;
    }
};

/* ==============================================================================
 * Example Usage:
 *
 * int main() {
 *     vector<vector<int>> grid = {
 *         {1, 2, 3, 4},
 *         {5, 6, 7, 8},
 *         {9, 10, 11, 12},
 *         {13, 14, 15, 16}
 *     };
 *
 *     Solution sol;
 *     grid = sol.reverseSubmatrix(grid, 0, 0, 3);
 *
 *     // Output grid:
 *     //  9 10 11  4
 *     //  5  6  7  8
 *     //  1  2  3 12
 *     for (auto& row : grid) {
 *         for (int val : row) cout << val << " ";
 *         cout << endl;
 *     }
 *
 *     return 0;
 * }
 * ============================================================================== */
