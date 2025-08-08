#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 1329. Sort the Matrix Diagonally (Leetcode)
 *
 * Task:
 * - A matrix diagonal is a sequence of cells starting from some (i, j) and moving
 *   to (i+1, j+1) until out of bounds.
 * - Sort each diagonal in ascending order.
 *
 * Key Idea:
 * - All cells in the same diagonal share the same value of (i - j).
 * - Store elements by this diagonal key, sort each, then place them back.
 *
 * Approach:
 * 1. Traverse matrix and group elements by their (i - j) key in a map.
 * 2. Sort each group in ascending order.
 * 3. Fill back the matrix from bottom-right so we can pop_back() efficiently.
 *
 * Time Complexity  : O(m * n * log(min(m, n)))
 *      - Collecting takes O(m * n)
 *      - Sorting each diagonal takes O(L log L), summed across diagonals.
 * Space Complexity : O(m * n) for storing diagonals.
 * ============================================================================== */

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size();

        // Step 1: Map diagonal key (i - j) → elements in that diagonal
        unordered_map<int, vector<int>> diagMap;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                diagMap[i - j].push_back(mat[i][j]);
            }
        }

        // Step 2: Sort each diagonal's elements in ascending order
        for (auto& p : diagMap) {
            sort(p.second.begin(), p.second.end());
        }

        // Step 3: Fill matrix from bottom-right, popping largest available element
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                mat[i][j] = diagMap[i - j].back();
                diagMap[i - j].pop_back();
            }
        }

        return mat;
    }
};
