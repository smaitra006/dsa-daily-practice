#include <bits/stdc++.h>
using namespace std;

/* ==============================================================================
 * Problem: 54. Spiral Matrix (Leetcode)
 *
 * Task:
 * - Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Approach:
 * 1. Maintain four boundaries: top, bottom, left, right.
 * 2. Traverse in four directions:
 *    - Left → Right   (along the top row)
 *    - Top → Bottom   (along the right column)
 *    - Right → Left   (along the bottom row, if still valid)
 *    - Bottom → Top   (along the left column, if still valid)
 * 3. Shrink the boundaries after traversing each direction.
 * 4. Continue until all elements are visited.
 *
 * Time Complexity  : O(m * n) — each element visited exactly once.
 * Space Complexity : O(1) extra (excluding output vector).
 * ============================================================================== */

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> ans;
        int m = matrix.size();
        int n = matrix[0].size();

        // Define boundaries
        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;

        while (top <= bottom && left <= right) {
            // Traverse from left → right
            for (int i = left; i <= right; i++)
                ans.push_back(matrix[top][i]);
            top++;

            // Traverse from top → bottom
            for (int i = top; i <= bottom; i++)
                ans.push_back(matrix[i][right]);
            right--;

            // Traverse from right → left (if still valid)
            if (top <= bottom) {
                for (int i = right; i >= left; i--)
                    ans.push_back(matrix[bottom][i]);
                bottom--;
            }

            // Traverse from bottom → top (if still valid)
            if (left <= right) {
                for (int i = bottom; i >= top; i--)
                    ans.push_back(matrix[i][left]);
                left++;
            }
        }

        return ans;
    }
};

