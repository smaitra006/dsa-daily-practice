#include <bits/stdc++.h>
using namespace std;

/* ===================================================================
 * PROBLEM 542: 01 MATRIX (LeetCode)
 * =================================================================== */

 /**
  * @brief Return the distance of the nearest 0 for each cell in the matrix
  *
  * PROBLEM STATEMENT:
  * Given an `m x n` binary matrix `mat`, return a matrix where each cell
  * contains the distance to the nearest 0.
  * - Distance is calculated in terms of the number of steps (4-directional).
  *
  * EXAMPLE:
  * Input:
  *   mat = [[0,0,0],
  *          [0,1,0],
  *          [1,1,1]]
  * Output:
  *   [[0,0,0],
  *    [0,1,0],
  *    [1,2,1]]
  *
  * APPROACH:
  * - Use multi-source BFS from all 0s in the matrix.
  * - Initialize result matrix with -1.
  * - Start BFS from all cells with 0 and push their positions into queue.
  * - For each cell, update unvisited neighbors with distance +1.
  *
  * @param mat Input binary matrix
  * @return vector<vector<int>> Result matrix with distances to nearest 0
  *
  * @complexity
  * Time: O(m * n)
  * Space: O(m * n)
  */

class Solution
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
    {
        int m = mat.size();
        int n = mat[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> result(m, vector<int>(n, -1));

        // Directions for 4-neighbor movement (up, down, left, right)
        vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        // Step 1: Enqueue all 0s and set their distance to 0
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    result[i][j] = 0;
                    q.push({ i, j });
                }
            }
        }

        // Step 2: BFS to update distances for all 1s
        while (!q.empty()) {
            pair<int, int> cell = q.front();
            q.pop();
            int i = cell.first;
            int j = cell.second;

            for (int d = 0; d < 4; d++) {
                int new_i = i + directions[d].first;
                int new_j = j + directions[d].second;

                // If within bounds and not yet visited
                if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n && result[new_i][new_j] == -1) {
                    result[new_i][new_j] = result[i][j] + 1;
                    q.push({ new_i, new_j });
                }
            }
        }

        return result;
    }
};
