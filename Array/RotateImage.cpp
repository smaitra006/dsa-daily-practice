#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 48. Rotate Image (Leetcode)
 *
 * Task:
 * - You are given an n x n 2D matrix representing an image.
 * - Rotate the image by 90 degrees (clockwise) in-place.
 *
 * Approach: Transpose + Reverse
 * 1. **Transpose** the matrix (swap matrix[i][j] with matrix[j][i]).
 * 2. **Reverse** each row to complete the 90° clockwise rotation.
 *
 * Time Complexity  : O(n^2)  (n = dimension of matrix)
 * Space Complexity : O(1)    (in-place transformation)
 * ============================================================================== */

class Solution {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size(); // Square matrix, m = n

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
